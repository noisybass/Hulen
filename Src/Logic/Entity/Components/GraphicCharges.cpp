#include "GraphicCharges.h"
#include "MousePointerFollower.h"
#include "Logic/Server.h"
#include "PlayerManager.h"
#include <iostream>

namespace Logic 
{
	IMP_FACTORY(CGraphicCharges);
	
	bool CGraphicCharges::spawn(const std::string& name, CEntity *entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		if (entityInfo->hasAttribute("graphicChargeVelocity"))
			_graphicChargeVelocity = entityInfo->getFloatAttribute("graphicChargeVelocity");

		if (entityInfo->hasAttribute("thrownChargeVelocity"))
			_thrownChargeVelocity = entityInfo->getFloatAttribute("thrownChargeVelocity");

		if (entityInfo->hasAttribute("graphicChargeRadius"))
			_graphicChargeRadius = entityInfo->getFloatAttribute("graphicChargeRadius");

		if (entityInfo->hasAttribute("graphicChargeRotationBar"))
			_graphicChargeRotationBar = entityInfo->getFloatAttribute("graphicChargeRotationBar");

		if (entityInfo->hasAttribute("graphicChargesDeltaSeparation"))
			_graphicChargesDeltaSeparation = entityInfo->getFloatAttribute("graphicChargesDeltaSeparation");

		if (entityInfo->hasAttribute("graphicChargesDeltaSeparationToFirstCharge"))
			_graphicChargesDeltaSeparationToFirstCharge = entityInfo->getFloatAttribute("graphicChargesDeltaSeparationToFirstCharge");

		// if there are 3 charges
		_graphicChargeDistanceBetweenThem = _graphicChargeRadius + _graphicChargeRadius * 0.5 + _graphicChargeRadius * 0.25;

		return true;

	} // spawn

	bool CGraphicCharges::activate()
	{
		CPlayerManager* playerManager = (CPlayerManager*)Logic::CServer::getSingletonPtr()->getPlayer()->getComponent("CPlayerManager");
		_numCharges =  playerManager->howManyCharges();

		if (_numCharges != _graphicCharges.size())
		{
			for (int i = 0; i < _numCharges; ++i)
			{
				std::stringstream ss;
				ss << i << " " << i << " " << i;
				std::string chargePosition = ss.str();
				CGameObject* newCharge = Logic::CMap::instantiatePrefab(_graphicChargeName, "GraphicCharge_" + std::to_string(i), chargePosition);
				_graphicCharges.push_back(newCharge);
			}
		}
	
		return true;
	} // activate

	void CGraphicCharges::deactivate()
	{
		//_graphicCharges.clear();
	} // deactivate

	void CGraphicCharges::tick(float msecs)
	{
		IComponent::tick(msecs);
		unsigned int size = _graphicCharges.size();
		for (int i = 0; i < size; ++i)
		{
			Vector3 mousePosition = ((CMousePointerFollower*)_entity->getComponent("CMousePointerFollower"))->getMousePosition();

			Vector3 directorVector = mousePosition - _graphicCharges[i]->getBody()->getPosition();
			// Go to Mouse Position
			float length = directorVector.length();
			if (length > _graphicChargeRadius)
			{
				directorVector.normalise();
				directorVector *= msecs * _graphicChargeVelocity * length / 2;
				Vector3 newPosition = _graphicCharges[i]->getBody()->getPosition() + directorVector;
				_graphicCharges[i]->getBody()->setPosition(newPosition);
			}
			else if (length < _graphicChargeRadius - _graphicChargeRotationBar)
			{
				directorVector.normalise();
				directorVector *= msecs * _graphicChargeVelocity * length / 2;
				Vector3 newPosition = _graphicCharges[i]->getBody()->getPosition() - directorVector;
				_graphicCharges[i]->getBody()->setPosition(newPosition);
			}
			// Loop around mouse position
			else {
				directorVector = Math::rotationVector3ZAxis(directorVector, -90);
				directorVector.normalise();

				if (equilateralTriangle(i, _graphicChargeDistanceBetweenThem))
					directorVector *= msecs * _graphicChargeVelocity;
				else
				{
					directorVector *= msecs * _graphicChargeVelocity / 2;
				}
					
				Vector3 newPosition = _graphicCharges[i]->getBody()->getPosition() + directorVector;
				_graphicCharges[i]->getBody()->setPosition(newPosition);
			}
		}

		// Put Charges
		unsigned int throughtOutSize = _thrownOutCharges.size();
		bool deleteCharges[3] = {false, false, false};

		for (int i = 0; i < throughtOutSize; ++i)
		{
			Vector3 mousePosition = ((CMousePointerFollower*)_entity->getComponent("CMousePointerFollower"))->getMousePosition();

			Vector3 directorVector = mousePosition - _thrownOutCharges[i]->getBody()->getPosition();
			// Go to Mouse Position
			float length = directorVector.length();
			if (length > 0.1)
			{
				Ogre::Real length = directorVector.length();
				directorVector.normalise();
				directorVector *= msecs * _thrownChargeVelocity * length / 2;
				Vector3 newPosition = _thrownOutCharges[i]->getBody()->getPosition() + directorVector;
				_thrownOutCharges[i]->getBody()->setPosition(newPosition);
			}
			else
			{
				TMessage m;
				m._type = Message::PUT_CHARGE;
				m.setArg<bool>("chargeOnMouseposition", true);
				m.setArg<Vector3>(std::string("instancePosition"), mousePosition);
				Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(m);
				
				deleteCharges[i] = true;
			}
		}

		// We do another for because we won't delete the charges in the same
		// could give some bugs.
		for (int i = 0; i < throughtOutSize; ++i)
		{
			if (deleteCharges[i])
			{
				// erase it from map
				Logic::CEntityFactory::getSingletonPtr()->deleteGameObject(_thrownOutCharges.back());
				_thrownOutCharges.pop_back();
			}
		}
		
	} // tick

	bool CGraphicCharges::equilateralTriangle(int chargeNum, float sideOfTriangle)
	{

		bool result = true;
		
		if (chargeNum > 0)
		{
			Vector3 distance = _graphicCharges[chargeNum]->getBody()->getPosition() - _graphicCharges[chargeNum - 1]->getBody()->getPosition();
			result = result && sideOfTriangle + _graphicChargesDeltaSeparation > distance.length() && sideOfTriangle - _graphicChargesDeltaSeparation < distance.length();

			if (_numCharges >= 3 && chargeNum == _numCharges - 1)
			{
				Vector3 distance = _graphicCharges[chargeNum]->getBody()->getPosition() - _graphicCharges[0]->getBody()->getPosition();
				result = result && sideOfTriangle + _graphicChargesDeltaSeparationToFirstCharge > distance.length() && sideOfTriangle - _graphicChargesDeltaSeparationToFirstCharge < distance.length();
			}
		}
		
		
		return result;
	} // equilateralTriangle

	bool CGraphicCharges::accept(const TMessage &message)
	{
		return message._type == Message::PICK_CHARGE ||
			   message._type == Message::PUT_CHARGE;
	} // accept

	void CGraphicCharges::process(const TMessage &message)
	{
		std::string chargePosition;
		CGameObject* newCharge;
		Vector3 position;
		std::stringstream ss;

		switch (message._type)
		{
		case Message::PICK_CHARGE:
			
			position = message.getArg<Vector3>("position");
			ss << position.x << " " << position.y << " " << position.z;
			chargePosition = ss.str();
			newCharge = Logic::CMap::instantiatePrefab(_graphicChargeName, "GraphicCharge_" + std::to_string(_numCharges), chargePosition);
			_graphicCharges.push_back(newCharge);
			newCharge->activate();
			++_numCharges;

			if (_numCharges == 3)
				_graphicChargeDistanceBetweenThem = _graphicChargeRadius + _graphicChargeRadius * 0.5 + _graphicChargeRadius * 0.25;

			break;
		case Message::PUT_CHARGE:
			if (_numCharges > 0)
			{
				_thrownOutCharges.push_back(_graphicCharges.back());
				_graphicCharges.pop_back();

				--_numCharges;

				if (_graphicCharges.size() == 2)
					_graphicChargeDistanceBetweenThem = (_graphicChargeRadius * 2) * 0.97;
			}
			break;
		}
	} // process
	
} // namespace Logic


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

		if (entityInfo->hasAttribute("graphicChargeRadius"))
			_graphicChargeRadius = entityInfo->getFloatAttribute("graphicChargeRadius");

		if (entityInfo->hasAttribute("graphicChargeRotationBar"))
			_graphicChargeRotationBar = entityInfo->getFloatAttribute("graphicChargeRotationBar");

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
			float lenght = directorVector.length();
			if (directorVector.length() > _graphicChargeRadius)
			{
				Ogre::Real length = directorVector.length();
				directorVector.normalise();
				directorVector *= msecs * _graphicChargeVelocity * length/2;
				Vector3 newPosition = _graphicCharges[i]->getBody()->getPosition() + directorVector;
				_graphicCharges[i]->getBody()->setPosition(newPosition);
			}
			// Loop around mouse position
			else if (directorVector.length() < _graphicChargeRadius - _graphicChargeRotationBar)
			{
				Ogre::Real length = directorVector.length();
				directorVector.normalise();
				directorVector *= msecs * _graphicChargeVelocity * length / 2;
				Vector3 newPosition = _graphicCharges[i]->getBody()->getPosition() - directorVector;
				_graphicCharges[i]->getBody()->setPosition(newPosition);
			}
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
		
	} // tick

	bool CGraphicCharges::equilateralTriangle(int chargeNum, float sideOfTriangle)
	{

		bool result = true;
		
		if (chargeNum > 0)
		{
			Vector3 distance = _graphicCharges[chargeNum]->getBody()->getPosition() - _graphicCharges[chargeNum - 1]->getBody()->getPosition();
			result = result && sideOfTriangle + 0.15 > distance.length() && sideOfTriangle - 0.15 < distance.length();

			if (_numCharges >= 3 && chargeNum == _numCharges - 1)
			{
				Vector3 distance = _graphicCharges[chargeNum]->getBody()->getPosition() - _graphicCharges[0]->getBody()->getPosition();
				result = result && sideOfTriangle + 0.85 > distance.length() && sideOfTriangle - 0.85 < distance.length();
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
			if (!_graphicCharges.empty())
			{
				// erase it from map
				Logic::CEntityFactory::getSingletonPtr()->deleteGameObject(_graphicCharges.back());
				_graphicCharges.pop_back();
				--_numCharges;

				if (_graphicCharges.size() == 2)
					_graphicChargeDistanceBetweenThem = (_graphicChargeRadius * 2) * 0.97;
			}
			
			break;
		}
	} // process
	
} // namespace Logic


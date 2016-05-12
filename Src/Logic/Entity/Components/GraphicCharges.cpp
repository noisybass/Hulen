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

		//for (CGameObject* go : _graphicCharges)
		for (int i = 0; i < _graphicCharges.size(); ++i)
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
			else {
				directorVector = Math::rotationVector3ZAxis(directorVector, -90);
				directorVector.normalise();

				if (equilateralTriangle(i, _graphicChargeDistanceBetweenThem))
					directorVector *= msecs * _graphicChargeVelocity;
				else
					directorVector *= msecs * _graphicChargeVelocity/2;
					
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
			Vector3 distance = _graphicCharges[chargeNum-1]->getBody()->getPosition() - _graphicCharges[chargeNum]->getBody()->getPosition();
			result = result && sideOfTriangle + 0.2 > distance.length() && sideOfTriangle - 0.2 < distance.length();
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
		int numCharges;
		Vector3 position;
		std::stringstream ss;

		switch (message._type)
		{
		case Message::PICK_CHARGE:
			numCharges = _graphicCharges.size();
			position = message.getArg<Vector3>("position");
			ss << position.x << " " << position.y << " " << position.z;
			chargePosition = ss.str();
			newCharge = Logic::CMap::instantiatePrefab(_graphicChargeName, "GraphicCharge_" + std::to_string(numCharges), chargePosition);
			_graphicCharges.push_back(newCharge);
			newCharge->activate();

			if (numCharges + 1 == 3)
				_graphicChargeDistanceBetweenThem = _graphicChargeRadius + _graphicChargeRadius * 0.5 + _graphicChargeRadius * 0.25;

			break;
		case Message::PUT_CHARGE:
			if (!_graphicCharges.empty())
			{
				// erase it from map
				Logic::CEntityFactory::getSingletonPtr()->deleteGameObject(_graphicCharges.back());
				_graphicCharges.pop_back();

				if (_graphicCharges.size() == 2)
					_graphicChargeDistanceBetweenThem = (_graphicChargeRadius * 2) * 0.97;
			}
			
			break;
		}
	} // process
	
} // namespace Logic


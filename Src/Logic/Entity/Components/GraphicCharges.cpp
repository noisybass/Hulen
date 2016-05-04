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
				CGameObject* newCharge = Logic::CMap::instantiatePrefab(_graphicChargeName, "GraphicCharge_" + i, chargePosition);
				_graphicCharges.push_back(newCharge);
				_graphicChargesLoopingMouse.push_back(false);
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
		return message._type == Message::HOW_MANY_CHARGES;
	} // accept

	void CGraphicCharges::process(const TMessage &message)
	{
		switch (message._type)
		{
		case Message::HOW_MANY_CHARGES:

			break;
		}
	} // process
	


} // namespace Logic


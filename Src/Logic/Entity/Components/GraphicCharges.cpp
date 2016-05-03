#include "GraphicCharges.h"
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

		for (CGameObject* go : _graphicCharges)
		{

			// Mouse in -10, 0, 0
			// radius 3
			int radius = 3;
			Vector3 directorVector = Vector3(-10 , 0, 0) - go->getBody()->getPosition();
			if (directorVector.length() > radius)
			{
				directorVector.normalise();
				directorVector *= msecs * 2;
				Vector3 newPosition = go->getBody()->getPosition() + directorVector;
				go->getBody()->setPosition(newPosition);
			}
			else {
			
				directorVector = Math::rotationVector3ZAxis(directorVector, 90);
				directorVector.normalise();
				directorVector *= msecs * 2;
				Vector3 newPosition = go->getBody()->getPosition() + directorVector;
				go->getBody()->setPosition(newPosition);
			}
		}
		
	} // tick

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


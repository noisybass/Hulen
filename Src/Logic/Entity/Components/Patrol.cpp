#include "Patrol.h"
#include "Logic\Entity\Entity.h"
#include "Physics\Server.h"
#include "Map\MapEntity.h"
#include "Logic/Entity/Components/MoveController.h"
#include <iostream>


namespace Logic 
{
	IMP_FACTORY(CPatrol);
	
	bool CPatrol::spawn(const std::string& name, CEntity *entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		assert(entityInfo->hasAttribute("patrolPosition1") && entityInfo->hasAttribute("patrolPosition2") && "Te has olvidado de iniclizar patrolPosition1 y patrolPosition2");

		if (entityInfo->hasAttribute("patrolPosition1"))
			_patrolPosition1 = entityInfo->getVector3Attribute("patrolPosition1");

		if (entityInfo->hasAttribute("patrolPosition2")){
			_patrolPosition2 = entityInfo->getVector3Attribute("patrolPosition2");

			// Hacemos esto para poder empezar por la posicion1 en el tick
			_arrivedDestination = entityInfo->getVector3Attribute("patrolPosition2");
		}
			

		return true;

	} // spawn

	bool CPatrol::accept(const TMessage &message)
	{
		return message._type == Message::ARRIVED_TO_DESTINATION;

	} // accept

	void CPatrol::process(const TMessage &message)
	{
		switch (message._type)
		{
		case Message::ARRIVED_TO_DESTINATION:
			_arrivedToDestination = true;
			_arrivedDestination = message.getArg<Vector3>(std::string("arrivedDestination"));
			break;
		}

	} // process

	void CPatrol::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		if (_arrivedToDestination)
		{
			CMoveController* moveController = (CMoveController*)_entity->getComponent("CMoveController");
			if (_arrivedDestination == _patrolPosition1) 
				moveController->nextPosition(_patrolPosition2);
			else if (_arrivedDestination == _patrolPosition2)
				moveController->nextPosition(_patrolPosition1);
			_arrivedToDestination = false;
		}
	} // tick

	
	
} // namespace Logic

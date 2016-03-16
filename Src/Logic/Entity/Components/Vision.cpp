/**
@file SwitchTrigger.cpp

Contiene la declaración del componente que envia un mensaje SWITCH a otra
entidad cuando recibe un mensaje TOUCHED / UNTOUCHED.
 
@see Logic::CSwitchTrigger
@see Logic::IComponent

@author David Llansó
@date Octubre, 2010
*/

#include "Vision.h"
#include "Logic\Entity\Entity.h"
#include "Physics\Server.h"
#include "Map\MapEntity.h"
#include "Graphics\Server.h"
#include "Graphics\DebugDrawing.h"
#include <iostream>

namespace Logic 
{
	IMP_FACTORY(CVision);
	
	bool CVision::spawn(const std::string& name, CEntity *entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		if (entityInfo->hasAttribute("defaultVision"))
			_defaultVision = entityInfo->getFloatAttribute("defaultVision");

		return true;

	} // spawn

	void CVision::tick(unsigned int msecs)
	{
		Logic::CEntity* entity = visionRay();
		Ogre::Vector3 startPosition = _entity->getPosition();
		Ogre::Vector3 endPosition = _entity->getPosition();
		endPosition.x += _defaultVision * _entity->getDirection();
		Graphics::CServer::getSingletonPtr()->getDebugDrawing()->drawLine("Linea", startPosition, endPosition, Ogre::ColourValue::Green);

		if (entity != nullptr){
			std::cout << "He tocado " + entity->getName() << std::endl;
		}
	}

	Logic::CEntity* CVision::visionRay(const float maxDistance)
	{
		// Inicializamos el rayo
		_ray.setOrigin(_entity->getPosition());
		_ray.setDirection(Vector3(_entity->getDirection(), 0, 0));

		return Physics::CServer::getSingletonPtr()->raycastClosest(_ray, maxDistance);
	}

	Logic::CEntity* CVision::visionRay()
	{
		// Inicializamos el rayo
		_ray.setOrigin(_entity->getPosition());
		_ray.setDirection(Vector3(_entity->getDirection(), 0, 0));

		return Physics::CServer::getSingletonPtr()->raycastClosest(_ray, _defaultVision);
	}

	bool CVision::accept(const TMessage &message)
	{
		return false;
	} // accept

	void CVision::process(const TMessage &message)
	{
	
	} // process
	


} // namespace Logic


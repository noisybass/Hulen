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
#include "BaseSubsystems/Math.h"
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

		if (entityInfo->hasAttribute("xRaySeparation"))
			_xRaySeparation = entityInfo->getIntAttribute("xRaySeparation");

		if (entityInfo->hasAttribute("yRaySeparation"))
			_yRaySeparation = entityInfo->getIntAttribute("yRaySeparation");

		return true;

	} // spawn

	void CVision::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		Logic::CEntity* entity = visionRay();

		Ogre::Vector3 startPosition = _entity->getPosition();
		// Actualizamos la x para que no choque con la propia malla.
		if (_entity->getDirection() == 1) startPosition.x += _xRaySeparation;
		else if (_entity->getDirection() == -1) startPosition.x -= _xRaySeparation;
		startPosition.y += _yRaySeparation; // Actualizo la y para ver el rayo un poco más arriba, y no desde el pivote del personaje

		Ogre::Vector3 endPosition = _entity->getPosition();
		endPosition.y += _yRaySeparation;
		endPosition.x += _defaultVision * _entity->getDirection();

		Graphics::CServer::getSingletonPtr()->getDebugDrawing()->drawLine(_entity->getName() + "_Line", startPosition, endPosition, Ogre::ColourValue::Green);

		if (entity != nullptr){
			std::cout << "He tocado " + entity->getName() << std::endl;
		}
		
	}

	Logic::CEntity* CVision::visionRay(const float maxDistance)
	{
		if (_entity->getDirection() == 0) return nullptr;

		// Inicializamos el rayo
		Vector3 origin = _entity->getPosition();
		if (_entity->getDirection() == 1) origin.x += _xRaySeparation;
		else if (_entity->getDirection() == -1) origin.x -= _xRaySeparation;
		origin.y += _yRaySeparation;
		_ray.setOrigin(origin);
		_ray.setDirection(Vector3(_entity->getDirection(), 0, 0));

		return Physics::CServer::getSingletonPtr()->raycastClosest(_ray, maxDistance);
	}

	Logic::CEntity* CVision::visionRay()
	{
		if (_entity->getDirection() == 0) return nullptr;

		// Inicializamos el rayo
		Vector3 origin = _entity->getPosition();
		if (_entity->getDirection() == 1) origin.x += _xRaySeparation;
		else if (_entity->getDirection() == -1) origin.x -= _xRaySeparation;
		origin.y += _yRaySeparation;
		_ray.setOrigin(origin);
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


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
#include "Logic/Entity/Entity.h"
#include "Physics/Server.h"
#include "Map/MapEntity.h"
#include "Graphics/Server.h"
#include "Graphics/DebugDrawing.h"
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

	bool CVision::activate()
	{
		// Si tenemos un componente responsable del agente de IA tendremos que actualizar su información
		_fsm = (Logic::CFSMEntity*)(_entity->getComponent("CFSMEntity"));

		if (_fsm)
		{
			_fsm->setValue<bool>("seeing_entity", false);

			if (_lastSeenEntity) _fsm->setValue<std::string>("seen_entity_name", _lastSeenEntity->getName());
		}

		return true;
	}

	void CVision::deactivate()
	{

	}

	void CVision::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		// PINTADO DE LA VISION
		Ogre::Vector3 startPosition = _entity->getPosition();
		// Actualizamos la x para que no choque con la propia malla.
		if (_entity->getDirection() == 1) startPosition.x += _xRaySeparation;
		else if (_entity->getDirection() == -1) startPosition.x -= _xRaySeparation;
		startPosition.y += _yRaySeparation; // Actualizo la y para ver el rayo un poco más arriba, y no desde el pivote del personaje

		Ogre::Vector3 endPosition = _entity->getPosition();
		endPosition.y += _yRaySeparation;
		endPosition.x += _defaultVision * _entity->getDirection();

		Graphics::CServer::getSingletonPtr()->getDebugDrawing()->drawLine(_entity->getName() + "_Line", startPosition, endPosition, Ogre::ColourValue::Green);

		// LOGICA DE LA VISION
		Logic::CEntity* entity = visionRay();

		if (entity){
			_seeingEntity = true;
			_lastSeenEntity = entity;
		}
		else
		{
			_seeingEntity = false;
		}

		if (_fsm)
		{
			_fsm->setValue<bool>("seeing_entity", _seeingEntity);
			if (_lastSeenEntity) _fsm->setValue<std::string>("seen_entity_name", _lastSeenEntity->getName());
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


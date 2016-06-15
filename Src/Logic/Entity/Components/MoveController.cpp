#include "MoveController.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/GameObject.h"
#include "Map/MapEntity.h"


namespace Logic 
{
	IMP_FACTORY(CMoveController);
	
	//---------------------------------------------------------

	bool CMoveController::spawn(const std::string& name, CEntity *entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if(!IComponent::spawn(name, entity,map,entityInfo))
			return false;

		// Init positions
		_positionToGo = entity->getPosition();
		_nextPositionToGo = entity->getPosition();

		if (entityInfo->hasAttribute("positionToGo")){
			_positionToGo = entityInfo->getVector3Attribute("positionToGo");
			_nextPositionToGo = entityInfo->getVector3Attribute("positionToGo");
		}
			
		if (entityInfo->hasAttribute("speed"))
			_speed = entityInfo->getFloatAttribute("speed");

		if (entityInfo->hasAttribute("gravity"))
			_gravity = entityInfo->getFloatAttribute("gravity");

		/**
		Animations
		*/
		if (entityInfo->hasAttribute("walkAnimation"))
			_walkRightAnimation = (entityInfo->getPairStringFloat("walkAnimation")).first;

		if (entityInfo->hasAttribute("idle1Animation"))
			_idleAnimation = (entityInfo->getPairStringFloat("idle1Animation")).first;

		if (entityInfo->hasAttribute("changeDirectionAnimation"))
			_changeDirectionAnimation = (entityInfo->getPairStringFloat("changeDirectionAnimation")).first;

		return true;

	} // spawn
	
	
	//---------------------------------------------------------

	bool CMoveController::accept(const TMessage &message)
	{
		return message._type == Message::ANIMATION_WITHOUT_LOOP_FINISHED;

	} // accept
	
	//---------------------------------------------------------

	void CMoveController::process(const TMessage &message)
	{
		switch (message._type)
		{
		case Message::ANIMATION_WITHOUT_LOOP_FINISHED:

			if (message.getArg<std::string>("name") == _changeDirectionAnimation)
			{
				if (_changingDirection)
				{
					_entity->rollNode(180);
					_changingDirection = false;
				}
				
			}
				

			break;
		}

	} // process
	
	//---------------------------------------------------------

	void CMoveController::calculateDirection()
	{
		// Nos movemos hacia la derecha
		if (_entity->getPosition().x < _positionToGo.x)
		{
			if (_entity->getDirection() == Logic::CEntity::ENTITY_DIRECTION::LEFT)
			{
				/*TMessage message;
				message._type = Message::SET_ANIMATION;
				message.setArg<std::string>(std::string("animation"), std::string(_changeDirectionAnimation));
				message.setArg<bool>(std::string("loop"), false);
				message.setArg<bool>(std::string("nextAnimation"), false);
				_entity->emitMessage(message, this);
				_changingDirection = true;*/

				_entity->rollNode(180);
			}
				
			_entity->setDirection(Logic::CEntity::ENTITY_DIRECTION::RIGHT);
		}
			
		else if (_entity->getPosition().x > _positionToGo.x)
		{
			if (_entity->getDirection() == Logic::CEntity::ENTITY_DIRECTION::RIGHT)
			{
				/*TMessage message;
				message._type = Message::SET_ANIMATION; 
				message.setArg<std::string>(std::string("animation"), std::string(_changeDirectionAnimation));
				message.setArg<bool>(std::string("loop"), false);
				message.setArg<bool>(std::string("nextAnimation"), false);
				_entity->emitMessage(message, this);
				_changingDirection = true;*/

				_entity->rollNode(180);
			}

			_entity->setDirection(Logic::CEntity::ENTITY_DIRECTION::LEFT);
		}
			
	}

	bool CMoveController::destinationReached()
	{
		return _entity->getPosition().x > _positionToGo.x - 0.5 && _entity->getPosition().x < _positionToGo.x + 0.5;
	}

	void CMoveController::nextPosition(const Vector3 &position)
	{
		_nextPositionToGo = position;
	}

	void CMoveController::tick(float msecs)
	{
		IComponent::tick(msecs);
		Vector3 movement(Vector3::ZERO);

		// Si no estamos giramos, nos movemos
		if (!_changingDirection)
		{

			// Nos movemos porque no hemos llegado a nuestro destino.
			if (!destinationReached())
			{
				calculateDirection();
				movement += Vector3(_entity->getDirection(), 0, 0) * _speed * msecs;
			}
			else
			{

				// Notificamos que hemos llegado a
				// la posición objetivo.
				TMessage msg;
				msg._type = Message::ARRIVED_TO_DESTINATION;
				msg.setArg<Vector3>(std::string("arrivedDestination"), _positionToGo);

				_entity->emitMessage(msg);

				// Esperamos a recibir una posicion a la que movernos
				_positionToGo = _nextPositionToGo;
			}

			// Acción de la gravedad
			movement += msecs * Vector3(0.0f, -_gravity, 0.0f);

			TMessage message;
			message._type = Message::AVATAR_WALK;
			message.setArg<Vector3>(std::string("movement"), movement);

			_entity->emitMessage(message);

		}
		

	} // tick

	/*
	Animations
	*/

	void CMoveController::walk()
	{
		// Cambiamos la animación
		TMessage message;
		message._type = Message::SET_ANIMATION;
		message.setArg<std::string>(std::string("animation"), std::string(_walkRightAnimation));
		message.setArg<bool>(std::string("loop"), true);

		_entity->emitMessage(message, this);

	} // walk

	void CMoveController::stop()
	{
		TMessage message;
		message._type = Message::SET_ANIMATION;
		message.setArg<std::string>(std::string("animation"), std::string(_idleAnimation));
		message.setArg<bool>(std::string("loop"), true);

		_entity->emitMessage(message, this);

	} // stop

} // namespace Logic


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
		_entity->setDirection(Logic::CEntity::ENTITY_DIRECTION::NONE);

		if (entityInfo->hasAttribute("positionToGo")){
			_positionToGo = entityInfo->getVector3Attribute("positionToGo");
			_nextPositionToGo = entityInfo->getVector3Attribute("positionToGo");
		}
			
		if (entityInfo->hasAttribute("speed"))
			_speed = entityInfo->getFloatAttribute("speed");

		if (entityInfo->hasAttribute("gravity"))
			_gravity = entityInfo->getFloatAttribute("gravity");

		return true;

	} // spawn
	
	
	//---------------------------------------------------------

	bool CMoveController::accept(const TMessage &message)
	{
		return false;

	} // accept
	
	//---------------------------------------------------------

	void CMoveController::process(const TMessage &message)
	{
		

	} // process
	
	//---------------------------------------------------------

	void CMoveController::calculateDirection()
	{
		// Nos movemos hacia la derecha
		if (_entity->getPosition().x < _positionToGo.x)
			_entity->setDirection(Logic::CEntity::ENTITY_DIRECTION::RIGHT);
		else if (_entity->getPosition().x > _positionToGo.x)
			_entity->setDirection(Logic::CEntity::ENTITY_DIRECTION::LEFT);
	}

	bool CMoveController::destinationReached()
	{
		return _entity->getPosition().x > _positionToGo.x - 0.5 && _entity->getPosition().x < _positionToGo.x + 0.5;
	}

	void CMoveController::nextPosition(const Vector3 &position)
	{
		_nextPositionToGo = position;
	}

	void CMoveController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		Vector3 movement(Vector3::ZERO);

		// Nos movemos porque no hemos llegado a nuestro destino.
		if (!destinationReached())
		{
			if (_entity->getDirection() == 0){
				calculateDirection();
				// Change animations
				if (_entity->getDirection() == 1) walkRight();
				else if (_entity->getDirection() == -1) walkLeft();
			}
			movement += Vector3(_entity->getDirection(), 0, 0) * _speed * msecs;
		}
		else
		{	
			// Hemos llegado al destino, solo lo ejecutamos
			// nada mas llegar al destino.
			if (_entity->getDirection() != 0)
			{
				_entity->setDirection(Logic::CEntity::ENTITY_DIRECTION::NONE);
				// Idle animation
				stop();

				// Notificamos que hemos llegado a
				// la posici�n objetivo.
				TMessage msg;
				msg._type = Message::ARRIVED_TO_DESTINATION;
				msg.setArg<Vector3>(std::string("arrivedDestination"), _positionToGo);

				_entity->emitMessage(msg);
			}

			// Esperamos a recibir una posicion a la que movernos
			_positionToGo = _nextPositionToGo;
		}

		// Acci�n de la gravedad
		movement += msecs * Vector3(0.0f, -_gravity, 0.0f);

		TMessage message;
		message._type = Message::AVATAR_WALK;
		message.setArg<Vector3>(std::string("movement"), movement);

		_entity->emitMessage(message);

	} // tick

	/*
	Animations
	*/

	void CMoveController::walkLeft()
	{
		// Cambiamos la animaci�n
		TMessage message;
		message._type = Message::SET_ANIMATION;
		message.setArg<std::string>(std::string("animation"), std::string("Walk"));
		message.setArg<bool>(std::string("loop"), true);

		_entity->emitMessage(message, this);

	} // walk

	void CMoveController::walkRight()
	{
		// Cambiamos la animaci�n
		TMessage message;
		message._type = Message::SET_ANIMATION;
		message.setArg<std::string>(std::string("animation"), std::string("WalkBack"));
		message.setArg<bool>(std::string("loop"), true);

		_entity->emitMessage(message, this);

	} // walkBack

	void CMoveController::stop()
	{
		TMessage message;
		message._type = Message::SET_ANIMATION;
		message.setArg<std::string>(std::string("animation"), std::string("Idle"));
		message.setArg<bool>(std::string("loop"), true);

		_entity->emitMessage(message, this);

	} // stopWalkingLeft

} // namespace Logic

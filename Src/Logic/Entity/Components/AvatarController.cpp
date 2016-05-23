/**
@file AvatarController.cpp

Contiene la implementación del componente que controla el movimiento 
de la entidad.
 
@see Logic::CAvatarController
@see Logic::IComponent

@author David Llansó
@date Agosto, 2010
*/

#include "AvatarController.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "PhysicController.h"


namespace Logic 
{
	IMP_FACTORY(CAvatarController);
	
	//---------------------------------------------------------

	bool CAvatarController::spawn(const std::string& name, CEntity *entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if(!IComponent::spawn(name, entity,map,entityInfo))
			return false;
		
		if(entityInfo->hasAttribute("speed"))
			_speed = entityInfo->getFloatAttribute("speed");

		if (entityInfo->hasAttribute("jump_speed"))
			_jumpSpeed = entityInfo->getFloatAttribute("jump_speed");

		if (entityInfo->hasAttribute("jump_height"))
			_jumpHeight = entityInfo->getFloatAttribute("jump_height");

		if (entityInfo->hasAttribute("gravity"))
			_gravity = entityInfo->getFloatAttribute("gravity");

		/**
		Animations
		*/
		if (entityInfo->hasAttribute("walkAnimation"))
			_walkRightAnimation = (entityInfo->getPairStringFloat("walkAnimation")).first;

		if (entityInfo->hasAttribute("idle1Animation"))
			_idleAnimation = (entityInfo->getPairStringFloat("idle1Animation")).first;

		if (entityInfo->hasAttribute("jump1Animation"))
			_jumpAnimation = entityInfo->getPairStringFloat("jump1Animation").first;

		if (entityInfo->hasAttribute("fall1Animation"))
			_fallAnimation = entityInfo->getPairStringFloat("fall1Animation").first;

		if (entityInfo->hasAttribute("land1Animation"))
			_landAnimation = entityInfo->getPairStringFloat("land1Animation").first;

		if (entityInfo->hasAttribute("deathAnimation"))
			_deathAnimation = entityInfo->getPairStringFloat("deathAnimation").first;

		if (entityInfo->hasAttribute("pickObjectAnimation"))
			_pickObjectAnimation = entityInfo->getPairStringFloat("pickObjectAnimation").first;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CAvatarController::activate()
	{
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CAvatarController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CAvatarController::accept(const TMessage &message)
	{
		return message._type == Message::CONTROL ||
			message._type == Message::SEND_STATE ||
			message._type == Message::RECEIVE_AVATAR_STATE ||
			message._type == Message::ANIMATION_WITHOUT_LOOP_STARTED ||
			message._type == Message::ANIMATION_WITHOUT_LOOP_FINISHED;

	} // accept
	
	//---------------------------------------------------------

	void CAvatarController::process(const TMessage &message)
	{
		std::string arg;

		TMessage m;
		switch(message._type)
		{
		case Message::ANIMATION_WITHOUT_LOOP_STARTED:
			if (message.getArg<std::string>("name") == _pickObjectAnimation ||
				message.getArg<std::string>("name") == _landAnimation ||
				message.getArg<std::string>("name") == _deathAnimation)
				_blockedAnimationWithoutLoopStarted = true;
			break;

		case Message::ANIMATION_WITHOUT_LOOP_FINISHED:
			_blockedAnimationWithoutLoopStarted = false;
			if (message.getArg<std::string>("name") == _jumpAnimation)
			{
				m._type = Message::SET_ANIMATION;
				m.setArg<std::string>(std::string("animation"), std::string(_fallAnimation));
				m.setArg<bool>(std::string("loop"), true);

				_entity->emitMessage(m);
			}
			else if (message.getArg<std::string>("name") == _landAnimation)
			{
				// we have to call again to walk to run de animation
				if (_walkingLeft) walkLeft();
				else if (_walkingRight) walkRight();
			}
			break;
		
		case Message::CONTROL:
			if (!_blockedAnimationWithoutLoopStarted)
			{
				arg = message.getArg<std::string>("control");

				if (!arg.compare("walkLeft"))
					walkLeft();
				else if (!arg.compare("walkRight"))
					walkRight();
				else if (!arg.compare("stopWalkingRight"))
					stopWalkingRight();
				else if (!arg.compare("stopWalkingLeft"))
					stopWalkingLeft();
				else if (!arg.compare("jump"))
					jump();
			}
				break;
			
		case Message::SEND_STATE:
			std::cout << "Mandando estado..." << std::endl;
			m._type = Message::RECEIVE_AVATAR_STATE;
			m.setArg<bool>("walkingRight", _walkingRight);
			m.setArg<bool>("walkingLeft", _walkingLeft);
			m.setArg<bool>("jump", _jump);
			m.setArg<float>("currentHeight", _currentHeight);

			message.getArg<CEntity*>("receiver")->emitMessage(m);
			break;
		case Message::RECEIVE_AVATAR_STATE:
			std::cout << "Recibiendo estado..." << std::endl;
			_walkingRight = message.getArg<bool>("walkingRight");
			_walkingLeft = message.getArg<bool>("walkingLeft");
			_jump = message.getArg<bool>("jump");
			_currentHeight = message.getArg<float>("currentHeight");

			break;
			
		}

	} // process
	
	//---------------------------------------------------------

	void CAvatarController::walkLeft() 
	{
			_walkingLeft = true;
			_walkingRight = false;

			if (!_jumping)
				walkAnimation();

			if (_entity->getDirection() == Logic::CEntity::ENTITY_DIRECTION::RIGHT)
			{
				changeDirection(Logic::CEntity::ENTITY_DIRECTION::LEFT);
			}

	} // walk
	
	//---------------------------------------------------------

	void CAvatarController::walkRight() 
	{
			_walkingRight = true;
			_walkingLeft = false;

			if (!_jumping)
				walkAnimation();

			if (_entity->getDirection() == Logic::CEntity::ENTITY_DIRECTION::LEFT)
			{
				changeDirection(Logic::CEntity::ENTITY_DIRECTION::RIGHT);
			}
	} // walkRight

	void CAvatarController::changeDirection(const Logic::CEntity::ENTITY_DIRECTION direction)
	{
		TMessage msg;
		msg._type = Message::ROLL_ENTITY_NODE;
		msg.setArg<int>(("degrees"), 180);

		_entity->setDirection(direction);

		_entity->emitMessage(msg, this);
	}


	void CAvatarController::walkAnimation()
	{
		// change animation
		TMessage message;
		message._type = Message::SET_ANIMATION;
		message.setArg<std::string>(std::string("animation"), std::string(_walkRightAnimation));
		message.setArg<bool>(std::string("loop"), true);

		_entity->emitMessage(message, this);
	}
	
	//---------------------------------------------------------

	void CAvatarController::stopWalkingRight() 
	{
		_walkingRight = false;

		// Si tampoco estamos moviendonos hacia la izquierda cambiamos la animacion
		if (!_walkingLeft)
		{
			TMessage message;
			message._type = Message::SET_ANIMATION;
			message.setArg<std::string>(std::string("animation"), std::string(_idleAnimation));
			message.setArg<bool>(std::string("loop"), true);

			_entity->emitMessage(message, this);
		}
	} // stopWalkingRight

	//---------------------------------------------------------

	void CAvatarController::stopWalkingLeft()
	{
		_walkingLeft = false;

		// Si tampoco estamos moviendonos hacia la derecha cambiamos la animacion
		if (!_walkingRight)
		{
			TMessage message;
			message._type = Message::SET_ANIMATION;
			message.setArg<std::string>(std::string("animation"), std::string(_idleAnimation));
			message.setArg<bool>(std::string("loop"), true);

			_entity->emitMessage(message, this);
		}
	} // stopWalkingLeft

	//---------------------------------------------------------

	void CAvatarController::jump()
	{
		CPhysicController* controller = (CPhysicController*)(_entity->getComponent("CPhysicController"));
		if (!controller->_falling)
		{
			_jump = true;

			TMessage message;
			message._type = Message::SET_ANIMATION;
			message.setArg<std::string>(std::string("animation"), std::string(_jumpAnimation));
			message.setArg<bool>(std::string("loop"), false);

			_entity->emitMessage(message, this);
		}
			
	}
	
	//---------------------------------------------------------

	void CAvatarController::tick(float msecs)
	{
		IComponent::tick(msecs);

		Vector3 movement(Vector3::ZERO);

		/**
		Attribute to know if the entity is falling.
		true indicates the entity is falling.
		false in the other case.
		*/
		bool falling = ((CPhysicController*) _entity->getComponent("CPhysicController"))->_falling;

		if (!_blockedAnimationWithoutLoopStarted)
		{
			if (_initJumpTime == 0 || _initJumpTime == 0.5)
			{
				if (_walkingRight)  movement += Vector3(1, 0, 0) * _speed * msecs;
				else if (_walkingLeft)   movement += Vector3(-1, 0, 0) * _speed * msecs;
			}
			
			if (_jump) // Jump to max height
			{
				_jumping = true;
				_initJumpTime += msecs;
				if (_initJumpTime >= 0.5)
				{
					_initJumpTime = 0.5;
					movement += Vector3::UNIT_Y * _jumpSpeed * msecs;
					_currentHeight += _jumpSpeed * msecs;
					if (_currentHeight >= _jumpHeight)
					{
						_jump = false;
						_currentHeight = 0;
						_initJumpTime = 0;
						//_falling = true;
					}
				}
			}
			else if (falling) //Falling from max height or falling without jump
			{
				//_jumping = true;
			}
			else if (!falling && _jumping) // falling on ground
			{
				_jumping = false;
				TMessage message;
				message._type = Message::SET_ANIMATION;
				message.setArg<std::string>(std::string("animation"), std::string(_landAnimation));
				message.setArg<bool>(std::string("loop"), false);

				_entity->emitMessage(message, this);
			}
			
		}
		
		// Acción de la gravedad
		movement += msecs * Vector3(0.0f, -_gravity, 0.0f);

		TMessage message;
		message._type = Message::AVATAR_WALK;
		message.setArg<Vector3>(std::string("movement"), movement);

		_entity->emitMessage(message);

	} // tick

} // namespace Logic


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
#include "Sounds\api\SoundsResources.h"


namespace Logic 
{
	IMP_FACTORY(CAvatarController);
	
	//---------------------------------------------------------

	CAvatarController::~CAvatarController()
	{
		Sounds::CSoundsResources* sounds = Sounds::CSoundsResources::getSingletonPtr();
		sounds->deleteSound(_channelWalkSound);
	}

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

		if (entityInfo->hasAttribute("delayinitJump"))
			_delayinitJump = entityInfo->getFloatAttribute("delayinitJump");

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

		/**
		Sounds
		*/
		if (entityInfo->hasAttribute("walkSound") && entityInfo->hasAttribute("walkVolume") 
			&& entityInfo->hasAttribute("walkPitch"))
		{
			_walkSound = entityInfo->getStringAttribute("walkSound");
			_channelWalkSound = _entity->getName() + "Walk";
			Sounds::CSoundsResources* sounds = Sounds::CSoundsResources::getSingletonPtr();
			sounds->createSound(_channelWalkSound, _walkSound);
			sounds->setSoundVolume(_channelWalkSound, entityInfo->getFloatAttribute("walkVolume"));
			sounds->setSoundPitch(_channelWalkSound, entityInfo->getFloatAttribute("walkPitch"));
		}

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
			if (message.getArg<std::string>("name") == _deathAnimation)
				_blockedAnimationWithoutLoopStarted = true;
			break;

		case Message::ANIMATION_WITHOUT_LOOP_FINISHED:
			_blockedAnimationWithoutLoopStarted = false;
			if (message.getArg<std::string>("name") == _jumpAnimation && _jumping)
			{
				m._type = Message::SET_ANIMATION;
				m.setArg<std::string>(std::string("animation"), std::string(_fallAnimation));
				m.setArg<bool>(std::string("loop"), true);
				m.setArg<bool>(std::string("nextAnimation"), false); // Not play default animation 

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
				else if (!arg.compare("jump"))
					jump();
			}
				
			if (!arg.compare("stopWalkingRight"))
				stopWalkingRight();
			else if (!arg.compare("stopWalkingLeft"))
				stopWalkingLeft();
			
				break;
		}

	} // process

	void CAvatarController::sendState(CAvatarController* receiver)
	{
		//std::cout << "AvatarController mandando estado..." << std::endl;
		receiver->changeDirection((Logic::CEntity::ENTITY_DIRECTION)_entity->getDirection());
		receiver->_walkingRight = _walkingRight;
		receiver->_walkingLeft = _walkingLeft;
		receiver->_jump = _jump;
		receiver->_jumping = _jumping;
		receiver->_initJumpTime = _initJumpTime;
		receiver->_currentHeight = _currentHeight;
		receiver->_blockedAnimationWithoutLoopStarted = _blockedAnimationWithoutLoopStarted;
		
		Sounds::CSoundsResources* sounds = Sounds::CSoundsResources::getSingletonPtr();
		if (!sounds->getPausedSound(_channelWalkSound))
		{
			sounds->pauseSound(_channelWalkSound);
			sounds->playSound(receiver->_channelWalkSound);
		}
		
		//_walkingRight = false;
		//_walkingLeft = false;
		//_jump = false;
		//_jumping = false;
		//_currentHeight = 0.0f;
	}
	
	//---------------------------------------------------------

	void CAvatarController::walkLeft() 
	{
			_walkingLeft = true;
			_walkingRight = false;

			if (!_jumping)
			{
				walkAnimation();
				Sounds::CSoundsResources::getSingletonPtr()->playSound(_channelWalkSound);
			}
				

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
			{
				walkAnimation();
				Sounds::CSoundsResources::getSingletonPtr()->playSound(_channelWalkSound);
			}
				

			if (_entity->getDirection() == Logic::CEntity::ENTITY_DIRECTION::LEFT)
			{
				changeDirection(Logic::CEntity::ENTITY_DIRECTION::RIGHT);
			}
	} // walkRight

	void CAvatarController::changeDirection(const Logic::CEntity::ENTITY_DIRECTION direction)
	{
		if (direction != _entity->getDirection())
		{
			TMessage msg;
			msg._type = Message::ROLL_ENTITY_NODE;
			msg.setArg<int>(("degrees"), 180);

			_entity->setDirection(direction);

			_entity->emitMessage(msg, this);
		}
		
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
		if (!_walkingLeft && !_jumping)
		{
			TMessage message;
			message._type = Message::SET_ANIMATION;
			message.setArg<std::string>(std::string("animation"), std::string(_idleAnimation));
			message.setArg<bool>(std::string("loop"), true);

			_entity->emitMessage(message, this);

			Sounds::CSoundsResources::getSingletonPtr()->pauseSound(_channelWalkSound);
		}
	} // stopWalkingRight

	//---------------------------------------------------------

	void CAvatarController::stopWalkingLeft()
	{
		_walkingLeft = false;

		// Si tampoco estamos moviendonos hacia la derecha cambiamos la animacion
		if (!_walkingRight && !_jumping)
		{
			TMessage message;
			message._type = Message::SET_ANIMATION;
			message.setArg<std::string>(std::string("animation"), std::string(_idleAnimation));
			message.setArg<bool>(std::string("loop"), true);

			_entity->emitMessage(message, this);

			Sounds::CSoundsResources::getSingletonPtr()->pauseSound(_channelWalkSound);
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
			message.setArg<bool>(std::string("nextAnimation"), false); // Not play default animation 

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
			if (_initJumpTime == 0 || _initJumpTime == _delayinitJump)
			{
				if (_walkingRight)  movement += Vector3(1, 0, 0) * _speed * msecs;
				else if (_walkingLeft)   movement += Vector3(-1, 0, 0) * _speed * msecs;
			}
			
			if (_jump) // Jump to max height
			{
				//std::cout << "[" << _entity->getName() << "] currentHeight : " << _entity->getPosition().y << std::endl;
				_jumping = true;
				_initJumpTime += msecs;
				if (_initJumpTime >= _delayinitJump)
				{
					_initJumpTime = _delayinitJump;
					movement += Vector3::UNIT_Y * _jumpSpeed * msecs;
					_currentHeight += _jumpSpeed * msecs;
					if (_currentHeight >= _jumpHeight)
					{
						_jump = false;
						_currentHeight = 0;
						_initJumpTime = 0;
					}
				}
			}
			else if (falling) //Falling from max height or falling without jump
			{
				//std::cout << "[" << _entity->getName() << "] currentHeight : " << _entity->getPosition().y << std::endl;
				// if player don't jump and fall from a height.
				if (!_jumping)
				{
					_jumping = true;
					TMessage m;
					m._type = Message::SET_ANIMATION;
					m.setArg<std::string>(std::string("animation"), std::string(_fallAnimation));
					m.setArg<bool>(std::string("loop"), true);
					m.setArg<bool>(std::string("nextAnimation"), false); // Not play default animation 

					_entity->emitMessage(m);
				}

			}
			else if (!falling && _jumping) // falling on ground
			{
				//std::cout << "[" << _entity->getName() << "] currentHeight : " << _entity->getPosition().y << std::endl;
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

		/*TMessage message;
		message._type = Message::AVATAR_WALK;
		message.setArg<Vector3>(std::string("movement"), movement);

		_entity->emitMessage(message);*/

		static_cast<CPhysicController*>(_entity->getComponent(std::string("CPhysicController")))->setMovement(movement);


		// Update music position
		// It goes with one frame behind, but doesn't matter, not noticed at all.
		Sounds::CSoundsResources* sounds = Sounds::CSoundsResources::getSingletonPtr();
		sounds->setPositionAndVelocity(_channelWalkSound, _entity->getPosition());

	} // tick

} // namespace Logic


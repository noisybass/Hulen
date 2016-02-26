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
			message._type == Message::RECEIVE_AVATAR_STATE;

	} // accept
	
	//---------------------------------------------------------

	void CAvatarController::process(const TMessage &message)
	{
		std::string arg;

		TMessage m;
		switch(message._type)
		{
		case Message::CONTROL:
			arg = message.getArg<std::string>("control");

			if (!arg.compare("walkLeft"))
				walkLeft();
			else if (!arg.compare("walkRight"))
				walkRight();
			else if (!arg.compare("stopWalkingRight"))
				stopWalkingRight();
			else if (!arg.compare("stopWalkingLeft"))
				stopWalkingLeft();
			break;
		case Message::SEND_STATE:
			std::cout << "Mandando estado..." << std::endl;
			m._type = Message::RECEIVE_AVATAR_STATE;
			m.setArg<bool>("walkingRight", _walkingRight);
			m.setArg<bool>("walkingLeft", _walkingLeft);
			m.setArg<float>("speed", _speed);

			message.getArg<CEntity*>("receiver")->emitMessage(m);
			break;
		case Message::RECEIVE_AVATAR_STATE:
			std::cout << "Recibiendo estado..." << std::endl;
			_walkingRight = message.getArg<bool>("walkingRight");
			_walkingLeft = message.getArg<bool>("walkingLeft");
			_speed = message.getArg<float>("speed");
			
			break;
		}

	} // process
	
	//---------------------------------------------------------

	void CAvatarController::walkLeft() 
	{
		_walkingLeft = true;

		// Cambiamos la animación
		TMessage message;
		message._type = Message::SET_ANIMATION;
		message.setArg<std::string>(std::string("animation"), std::string("Walk"));
		message.setArg<bool>(std::string("loop"), true);

		_entity->emitMessage(message,this);

	} // walk
	
	//---------------------------------------------------------

	void CAvatarController::walkRight() 
	{
		_walkingRight = true;

		// Cambiamos la animación
		TMessage message;
		message._type = Message::SET_ANIMATION;
		message.setArg<std::string>(std::string("animation"), std::string("WalkBack"));
		message.setArg<bool>(std::string("loop"), true);

		_entity->emitMessage(message,this);

	} // walkBack
	
	//---------------------------------------------------------

	void CAvatarController::stopWalkingRight() 
	{
		_walkingRight = false;

		// Si tampoco estamos moviendonos hacia la izquierda cambiamos la animacion
		if (!_walkingLeft)
		{
			TMessage message;
			message._type = Message::SET_ANIMATION;
			message.setArg<std::string>(std::string("animation"), std::string("Idle"));
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
			message.setArg<std::string>(std::string("animation"), std::string("Idle"));
			message.setArg<bool>(std::string("loop"), true);

			_entity->emitMessage(message, this);
		}
	} // stopWalkingLeft
	
	//---------------------------------------------------------

	void CAvatarController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		if(_walkingLeft || _walkingRight)
		{

			Vector3 movement;
			if (_walkingRight)  movement = Vector3(1, 0, 0);
			else if (_walkingLeft)   movement = Vector3(-1, 0, 0);
			
			movement *= msecs * _speed;

			// Enviar un mensaje para que el componente físico mueva el personaje
			TMessage message;
			message._type = Message::AVATAR_WALK;
			message.setArg<Vector3>(std::string("movement"), movement);

			_entity->emitMessage(message);
		}

		//CPhysicController* controller = (CPhysicController*)(_entity->getComponent("CPhysicController"));


	} // tick

} // namespace Logic


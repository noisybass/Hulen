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


namespace Logic 
{
	IMP_FACTORY(CAvatarController);
	
	//---------------------------------------------------------

	bool CAvatarController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
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
			else if (!arg.compare("stopWalk"))
				stopWalk();
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

	void CAvatarController::stopWalk() 
	{
		_walkingLeft = _walkingRight = false;

		TMessage message;
		message._type = Message::SET_ANIMATION;
		message.setArg<std::string>(std::string("animation"), std::string("Idle"));
		message.setArg<bool>(std::string("loop"), true);

		_entity->emitMessage(message,this);
		

	} // stopWalk
	
	//---------------------------------------------------------

	void CAvatarController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		// Si nos estamos desplazando calculamos la próxima posición
		// Calculamos si hay vectores de dirección de avance y strafe,
		// hayamos la dirección de la suma y escalamos según la
		// velocidad y el tiempo transcurrido.
		if(_walkingLeft || _walkingRight)
		{
			Vector3 direction(Vector3::ZERO);
			Vector3 directionStrafe(Vector3::ZERO);

			if(_walkingLeft || _walkingRight)
			{
				directionStrafe = 
						Math::getDirection(_entity->getYaw() + Math::PI/2);
				if(_walkingRight)
					directionStrafe *= -1;
			}

			direction += directionStrafe;
			direction.normalise();
			direction *= msecs * _speed;

			// Enviar un mensaje para que el componente físico mueva el personaje
			TMessage message;
			message._type = Message::AVATAR_WALK;
			message.setArg<Vector3>(std::string("direction"), direction);

			_entity->emitMessage(message);
		}

	} // tick

} // namespace Logic


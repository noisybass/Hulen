/**
@file SwitchPosition.cpp

Contiene la implementación del componente que controla el movimiento de
una entidad que tiene dos estado (posiciones) para ir de una a otra.
 
@see Logic::CSwitchPosition
@see Logic::IComponent

@author David Llansó
@date Octubre, 2010
*/

#include "SwitchPosition.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

namespace Logic 
{
	IMP_FACTORY(CSwitchPosition);
	
	//---------------------------------------------------------

	CSwitchPosition::CSwitchPosition() : IComponent(), _targetPosition(Vector3::ZERO), 
										_speed(0.05f), _loop(false), _lastMovement(Vector3::ZERO)
	{
		_position[0] = Vector3::ZERO;
		_position[1] = Vector3::ZERO;
	}

	//---------------------------------------------------------

	bool CSwitchPosition::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("speed"))
			_speed = entityInfo->getFloatAttribute("speed");

		if(entityInfo->hasAttribute("loop"))
			_loop = entityInfo->getBoolAttribute("loop");

		if(entityInfo->hasAttribute("position")) {
			_position[0] = entityInfo->getVector3Attribute("position");
			_targetPosition = _position[0];
		}

		if(entityInfo->hasAttribute("position2")) 
			_position[1] = entityInfo->getVector3Attribute("position2");

		return true;

	} // spawn

	
	//---------------------------------------------------------

	bool CSwitchPosition::accept(const TMessage &message)
	{
		return message._type == Message::SWITCH;

	} // accept
	
	//---------------------------------------------------------

	void CSwitchPosition::process(const TMessage &message)
	{
		switch(message._type)
		{
		case Message::SWITCH:
			assert((message._int >= 0) && (message._int <= 1));
			_targetPosition = _position[message._int];
			break;
		}

	} // process
	
	//---------------------------------------------------------

	void CSwitchPosition::tick(unsigned int msecs)
	{
		// Invocamos al método de la clase padre
		IComponent::tick(msecs);

		// Calcular la dirección en la que debemos mover la entidad
		Vector3 displ = _targetPosition - _entity->getPosition();
	
		// Si estamos en loop y nos hemos pasado del objetivo, cambiamos de objetivo
		if (_loop && displ.dotProduct(_lastMovement) <= 0) {
			if(_targetPosition == _position[0])
				_targetPosition = _position[1];
			else
				_targetPosition = _position[0];		

			displ = _targetPosition - _entity->getPosition();
		}

		// Calcular la distancia a la que está el objetivo
		float distance = displ.length();
		
		// Calcular desplazamiento en función del tiempo transcurrido
		displ.normalise();
		displ *= msecs * _speed;
		
		// Si nos pasamos del objetivo ajustamos para llegar justo hasta él 
		if (displ.length() > distance) {
			displ.normalise();
			displ *= distance;
		}

		// Notificamos el movimiento que deseamos realizar
		TMessage m;
		m._type = Message::KINEMATIC_MOVE;
		m._vector3 = displ;
		bool accepted = _entity->emitMessage(m);

		// Si nadie captura el mensaje significa que no hay componente físico,
		// así que movemos la entidad nosotros
		if (!accepted) {
			_entity->setPosition(_entity->getPosition() + displ);
		}

		// Actualizamos el último movimiento realizado
		_lastMovement = displ;

	} // tick

} // namespace Logic


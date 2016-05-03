#include "MousePointerFollower.h"

#include "Logic/Entity/Entity.h"

namespace Logic
{
	IMP_FACTORY(CMousePointerFollower);

	bool CMousePointerFollower::accept(const TMessage& message)
	{
		return message._type == Message::MOUSE_POINTER_MOVE;

	} // accept

	void CMousePointerFollower::process(const TMessage& message)
	{
		TMessage m;
		switch (message._type)
		{
		case Message::MOUSE_POINTER_MOVE:
			m._type = Message::LIGHT_SET_POSITION;
			newPosition = message.getArg<Vector3>("newPosition");
			m.setArg<Vector3>(std::string("newPosition"), newPosition);
			_entity->emitMessage(m);

			m._type = Message::KINEMATIC_MOVE;
			m.setArg<Vector3>(std::string("movement"), newPosition - _entity->getPosition());

			// Si nadie captura el mensaje significa que no hay componente físico,
			// así que movemos la entidad nosotros
			if (!_entity->emitMessage(m))
			{
				_entity->setPosition(newPosition);
			}
			break;
		}

	} // process

} // namespace Logic
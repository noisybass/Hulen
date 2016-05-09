#include "DeathPlane.h"

#include "Logic\Server.h"
#include "Logic\Entity\GameObject.h"

namespace Logic 
{
	IMP_FACTORY(CDeathPlane);

	bool CDeathPlane::spawn(const std::string& name, CEntity *entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if(!IComponent::spawn(name, entity,map,entityInfo))
			return false;

		return true;
	} // spawn

	bool CDeathPlane::accept(const TMessage &message)
	{
		return message._type == Message::TOUCHED;

	} // accept

	void CDeathPlane::process(const TMessage &message)
	{
		TMessage msg;
		switch(message._type)
		{
		/*case Message::SHAPE_HIT:
			msg._type = Message::PLAYER_EVENT;
			msg.setArg<std::string>(std::string("playerEvent"), std::string("die"));
			Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(msg);
			break;*/
		case Message::TOUCHED:
			CEntity* entity = message.getArg<CEntity*>("entity");
			msg._type = Message::DEATH_PLANE;
			if (entity->getBlueprint() == "Player")
				entity->getGameObject()->emitMessage(msg);
			else
				entity->emitMessage(msg);
			break;
		}

	} // process

} // namespace Logic


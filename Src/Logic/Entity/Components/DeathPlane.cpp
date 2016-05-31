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
			
			// If the player hits to death plane, we send
			// a player event to PlayerManager
			if (entity->getBlueprint() == "Player")
			{
				msg._type = Message::PLAYER_DEATH_BY_DEATH_PLANE;
				entity->emitMessage(msg);
			}
			// Else qwe notify that another thing that isn't 
			// the player hit the death plane
			else
			{
				msg._type = Message::DEATH_PLANE;
				entity->emitMessage(msg);
			}
				
			break;
		}

	} // process

} // namespace Logic


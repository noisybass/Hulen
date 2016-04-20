#include "Spike.h"
#include "Logic\Server.h"
#include "Logic\Entity\GameObject.h"

namespace Logic 
{
	IMP_FACTORY(CSpike);


	CSpike::~CSpike()
	{
		

	} // ~CGraphics
	

	bool CSpike::spawn(const std::string& name, CEntity *entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if(!IComponent::spawn(name, entity,map,entityInfo))
			return false;
		
		return true;

	} // spawn
	

	bool CSpike::accept(const TMessage &message)
	{
		return message._type == Message::SHAPE_HIT;

	} // accept


	void CSpike::process(const TMessage &message)
	{
		switch(message._type)
		{
		case Message::SHAPE_HIT:
			TMessage msg;
			msg._type = Message::PLAYER_EVENT;
			msg.setArg<std::string>(std::string("playerEvent"), std::string("die"));
			Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(msg);
			break;
		}

	} // process

} // namespace Logic


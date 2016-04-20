#include "EndLevel.h"
#include "Logic\Server.h"
#include "Logic\Entity\GameObject.h"
#include "Logic\Events\Event.h"

namespace Logic 
{
	IMP_FACTORY(CEndLevel);


	CEndLevel::~CEndLevel()
	{
		
	} // ~CGraphics
	

	bool CEndLevel::spawn(const std::string& name, CEntity *entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if(!IComponent::spawn(name, entity,map,entityInfo))
			return false;
		
		return true;

	} // spawn
	

	bool CEndLevel::accept(const TMessage &message)
	{
		return message._type == Message::TOUCHED;

	} // accept


	void CEndLevel::process(const TMessage &message)
	{
		switch(message._type)
		{
		case Message::TOUCHED:
			TMessage msg;
			msg._type = Message::PLAYER_EVENT;
			msg.setArg<std::string>(std::string("playerEvent"), std::string("endLevel"));
			Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(msg);
			break;
		}

	} // process

} // namespace Logic


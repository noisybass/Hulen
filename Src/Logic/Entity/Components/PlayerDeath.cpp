#include "PlayerDeath.h"
#include "Logic/Server.h"

namespace Logic
{

	bool CPlayerDeath::spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		if (entityInfo->hasAttribute("deathAnimation"))
			_deathAnimation = (entityInfo->getPairStringFloat("deathAnimation")).first;

		return true;
	} // spawn
	
	bool CPlayerDeath::accept(const TMessage &message)
	{
		return message._type == Message::PLAYER_DEATH ||
			   message._type == Message::PLAYER_DEATH_BY_DEATH_PLANE ||
			   message._type == Message::ANIMATION_WITHOUT_LOOP_FINISHED;
	} // accept

	void CPlayerDeath::process(const TMessage &message)
	{
		TMessage msg;
		switch (message._type)
		{
		case Message::PLAYER_DEATH_BY_DEATH_PLANE:

			msg._type = Message::PLAYER_EVENT;
			msg.setArg<std::string>(std::string("playerEvent"), std::string("die"));
			_entity->getGameObject()->emitMessage(msg);

			break;
		case Message::PLAYER_DEATH:

			// death animation
			msg._type = Message::SET_ANIMATION;
			msg.setArg<std::string>(std::string("animation"), std::string(_deathAnimation));
			msg.setArg<bool>(std::string("loop"), false);
			msg.setArg<bool>(std::string("nextAnimation"), false);
			_entity->emitMessage(msg);

			/*
			Cuando se pulsa un interruptor hace el zoomIn. Al acabar el zoomIn hace un zoomOut.
			Por ahora se deja así para demostrar que funciona. En el caso de que se desee separar el
			zoomIn del zoomOut, se debe cambiar un poco la función zoomIn.
			*/
			CServer::getSingletonPtr()->getCamera()->zoomIn();
			
			break;
		case Message::ANIMATION_WITHOUT_LOOP_FINISHED:

			// When finish the death animation,
			// we send a message to the state.
			if (message.getArg<std::string>("name") == _deathAnimation)
			{
				msg._type = Message::PLAYER_EVENT;
				msg.setArg<std::string>(std::string("playerEvent"), std::string("die"));
				_entity->getGameObject()->emitMessage(msg);
			}
			break;
		default:
			break;
		}
	} // process

	IMP_FACTORY(CPlayerDeath);

} // namespace CPlayerDeath
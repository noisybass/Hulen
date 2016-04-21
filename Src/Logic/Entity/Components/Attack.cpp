#include "Attack.h"

#include "Logic/Server.h"

namespace Logic
{

	IMP_FACTORY(CAttack);

	bool CAttack::spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		_active = false;

	} // spawn

	bool CAttack::activate()
	{
		IComponent::activate();

		std::cout << "ACTIVANDO ATTACK..." << std::endl;

		TMessage msg;
		msg._type = Message::PLAYER_EVENT;
		msg.setArg<std::string>(std::string("playerEvent"), std::string("die"));
		Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(msg);

		return true;

	} // activate

	void CAttack::deactivate()
	{
		IComponent::deactivate();

		std::cout << "DESACTIVANDO ATTACK..." << std::endl;

	} // deactivate

} // namespace Logic
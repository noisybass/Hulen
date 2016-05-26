#include "Attack.h"

#include "Logic/Server.h"

namespace Logic
{

	IMP_FACTORY(CAttack);

	void CAttack::enterState()
	{
		std::cout << "ACTIVANDO ATTACK..." << std::endl;

		CState::enterState();

		TMessage msg;
		msg._type = Message::PLAYER_DEATH;
		Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(msg);

	} // enterState

	void CAttack::exitState()
	{
		std::cout << "DESACTIVANDO ATTACK..." << std::endl;

		CState::exitState();

	} // exitState

} // namespace Logic
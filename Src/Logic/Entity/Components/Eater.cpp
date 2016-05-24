#include "Eater.h"

#include "Logic/Entity/Components/FSMEntity.h"
#include "Logic/Server.h"

namespace Logic
{

	IMP_FACTORY(CEater);

	void CEater::enterState()
	{
		std::cout << "ACTIVANDO EATER..." << std::endl;

		CState::enterState();

		Logic::CFSMEntity* fsm = (Logic::CFSMEntity*)(_entity->getComponent("CFSMEntity"));

		if (fsm->getValue<bool>("touching_entity"))
		{
			std::string chargeName = fsm->getValue<std::string>("touched_go_name");

			// Tenemos que avisar al player de que hay una carga menos en el mapa
			TMessage msg;
			msg._type = Message::CHARGE_ERASED;
			msg.setArg<std::string>(std::string("chargeName"), chargeName);
			Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(msg);
		}

	} // enterState

	void CEater::exitState()
	{
		std::cout << "DESACTIVANDO EATER..." << std::endl;

		CState::exitState();

		Logic::CFSMEntity* fsm = (Logic::CFSMEntity*)(_entity->getComponent("CFSMEntity"));
		fsm->setValue<bool>("touching_entity", false);

	} // exitState


} // namespace Logic
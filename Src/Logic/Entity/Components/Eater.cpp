#include "Eater.h"

#include "Logic/Entity/Components/FSMEntity.h"
#include "Logic/Server.h"

namespace Logic
{

	IMP_FACTORY(CEater);

	bool CEater::spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		_active = false;

	} // spawn

	bool CEater::activate()
	{
		IComponent::activate();

		std::cout << "ACTIVANDO EATER..." << std::endl;

		Logic::CFSMEntity* fsm = (Logic::CFSMEntity*)(_entity->getComponent("CFSMEntity"));

		if (fsm->getValue<bool>("touching_entity"))
		{
			std::string chargeName = fsm->getValue<std::string>("touched_go_name");

			fsm->setValue<bool>("touching_entity", false);
			fsm->setValue<bool>("seeing_entity", false);

			// Tenemos que avisar al player de que hay una carga menos en el mapa
			TMessage msg;
			msg._type = Message::CHARGE_ERASED;
			msg.setArg<std::string>(std::string("chargeName"), chargeName);
			Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(msg);


			return true;
		}

		return false;

	} // activate

	void CEater::deactivate()
	{
		IComponent::deactivate();

		std::cout << "DESACTIVANDO EATER..." << std::endl;

	} // deactivate


} // namespace Logic
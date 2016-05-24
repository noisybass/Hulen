#include "Chase.h"

#include "Logic/Entity/Components/MoveController.h"
#include "Logic/Entity/Components/FSMEntity.h"

namespace Logic
{

	IMP_FACTORY(CChase);

	CChase::CChase() : CState(), _target(nullptr)
	{

	} // CChase

	void CChase::enterState()
	{
		std::cout << "ACTIVANDO CHASE..." << std::endl;

		CState::enterState();

		Logic::CFSMEntity* fsm = (Logic::CFSMEntity*)(_entity->getComponent("CFSMEntity"));
		std::string targetName = fsm->getValue<std::string>("seen_go_name");
		_target = _entity->getGameObject()->getMap()->getGameObjectByName(targetName)->getBody();

	} // enterState

	void CChase::exitState()
	{
		std::cout << "DESACTIVANDO CHASE..." << std::endl;

		CState::exitState();

		_target = nullptr;

	} // exitState

	void CChase::tick(float msecs)
	{
		if (_executing)
		{
			CMoveController* moveController = (CMoveController*)_entity->getComponent("CMoveController");

			moveController->nextPosition(_target->getPosition());
		}

	} // tick

} // namespace Logic
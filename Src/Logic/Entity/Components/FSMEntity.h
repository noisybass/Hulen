#ifndef LOGIC_FSM_ENTITY_H
#define LOGIC_FSM_ENTITY_H

#include "Logic\Entity\Component.h"
#include "BaseSubsystems\StateMachine.h"

namespace Logic
{
	class CFSMEntity : public IComponent
	{
		DEC_FACTORY(CFSMEntity);
	public:

		bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;

		bool activate() override;

		void tick(unsigned int msecs) override;

		void sayHello();

		void registerFSMEntity();

		void loadStates();

		AI::StateMachine<CFSMEntity>* getFSM() const { return _FSM; }

	protected:

		AI::StateMachine<CFSMEntity>* _FSM;

	}; // class CFSMEntity

	REG_FACTORY(CFSMEntity);

} // namespace Logic

#endif // LOGIC_FSM_ENTITY_H
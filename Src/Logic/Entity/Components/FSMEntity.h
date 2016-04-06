#ifndef LOGIC_FSM_ENTITY_H
#define LOGIC_FSM_ENTITY_H

#include "Logic\Entity\Component.h"
#include "BaseSubsystems\FSMAgent.h"

namespace Logic
{
	class CFSMEntity : public IComponent
	{
		DEC_FACTORY(CFSMEntity);

		AI::FSMAgent*  _agent;

	public:

		CFSMEntity();

		void tick(unsigned int msecs) override;

	}; // class CFSMEntity

	REG_FACTORY(CFSMEntity);

} // namespace Logic

#endif // LOGIC_FSM_ENTITY_H
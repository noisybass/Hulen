#ifndef LOGIC_FSM_ENTITY_H
#define LOGIC_FSM_ENTITY_H

#include "Logic/Entity/Component.h"
#include "BaseSubsystems/FSMAgent.h"

namespace Logic
{
	class CFSMEntity : public IComponent
	{
		DEC_FACTORY(CFSMEntity);

		AI::FSMAgent*  _agent;

	public:

		CFSMEntity();

		~CFSMEntity();

		bool spawn(const std::string& name, CEntity *entity, CMap *map, const Map::CEntity *entityInfo) override;

		void tick(unsigned int msecs) override;

	}; // class CFSMEntity

	REG_FACTORY(CFSMEntity);

} // namespace Logic

#endif // LOGIC_FSM_ENTITY_H
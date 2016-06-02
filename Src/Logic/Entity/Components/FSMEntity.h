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

		void tick(float msecs) override;

		template<typename T>
		T getValue(const std::string& id) const { return _agent->getValue<T>(id); }

		template<typename T>
		void setValue(const std::string& id, const T& value) { _agent->setValue<T>(id, value);}

		void setAnimation(const std::string& animationName, bool loop, bool nextAnimation) { _agent->setAnimation(animationName, loop, nextAnimation); };

	private:
		void setAnimationNames(const Map::CEntity *entityInfo);

	}; // class CFSMEntity

	REG_FACTORY(CFSMEntity);

} // namespace Logic

#endif // LOGIC_FSM_ENTITY_H
#ifndef LOGIC_CHASE_H
#define LOGIC_CHASE_H

#include "Logic/Entity/Component.h"

namespace Logic
{

	class CChase : public IComponent
	{
		DEC_FACTORY(CChase);

	public:

		CChase() : IComponent(), _active(false), _target(nullptr) {}

		bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;

		bool activate() override;

		void deactivate() override;

		void tick(unsigned int msecs) override;

	private:

		CEntity* _target;

		bool _active;

	}; // class CChase

	REG_FACTORY(CChase);

} //namespace Logic

#endif // LOGIC_CHASE_H
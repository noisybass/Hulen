#ifndef LOGIC_EATER_H
#define LOGIC_EATER_H

#include "Logic/Entity/Component.h"

namespace Logic
{

	class CEater : public IComponent
	{
		DEC_FACTORY(CEater);

		bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;

		bool activate() override;

		void deactivate() override;

	}; // class CEater

	REG_FACTORY(CEater);

} // namespace Logic

#endif // LOGIC_EATER
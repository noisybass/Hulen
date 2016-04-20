#ifndef LOGIC_ATTACK_H
#define LOGIC_ATTACK_H

#include "Logic/Entity/Component.h"

namespace Logic
{

	class CAttack : public IComponent
	{
		DEC_FACTORY(CAttack);

		bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;

		bool activate() override;

		void deactivate() override;

	}; // class CAttack

	REG_FACTORY(CAttack);

} //namespace Logic

#endif // LOGIC_ATTACK_H
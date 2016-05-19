#ifndef LOGIC_PLAYER_DEATH_H
#define LOGIC_PLAYER_DEATH_H

#include "Logic/Entity/Component.h"

namespace Logic
{
	class CPlayerDeath : public IComponent
	{
		DEC_FACTORY(CPlayerDeath);
	public:
		bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;
		bool accept(const TMessage &message) override;
		void process(const TMessage &message) override;
	private:
		std::string _deathAnimation;

	}; // class CPlayerDeath

	REG_FACTORY(CPlayerDeath);

} // namespace Logic

#endif // LOGIC_PLAYER_DEATH_H
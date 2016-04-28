#ifndef LOGIC_CHARGER_H
#define LOGIC_CHARGER_H

#include "Logic/Entity/Component.h"

namespace Logic
{

	class CCharger : public IComponent
	{
		DEC_FACTORY(CCharger);
	public:

		CCharger();

		bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;

		bool activate() override;

		void deactivate() override;

		void tick(float msecs) override;

	private:

		float _speed;

		float _gravity;

	}; // class CCharger

	REG_FACTORY(CCharger);

} // namespace Logic

#endif // LOGIC_CHARGER_H
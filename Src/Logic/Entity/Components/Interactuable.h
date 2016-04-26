#ifndef LOGIC_INTERACTUABLE_H
#define LOGIC_INTERACTUABLE_H

#include "Logic\Entity\Component.h"

namespace Logic
{
	class CInteractuable : public IComponent
	{
		DEC_FACTORY(CInteractuable);
	public:

		CInteractuable();

		~CInteractuable();

		bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;

		bool activate() override;

		void tick(float msecs) override;

	protected:

		friend class CPlayerManager;

		/**
		Nombre del player.
		*/
		std::string _playerName;

		/**
		Referencia al player.
		*/
		CGameObject* _player;

		/**
		Radio del rango de interacción.
		*/
		float _radius;

	}; // class CInteractuable

	REG_FACTORY(CInteractuable);

} // namespace Logic

#endif // LOGIC_INTERACTUABLE_H
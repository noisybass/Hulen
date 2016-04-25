#ifndef LOGIC_LIGHTING_AREA_H
#define LOGIC_LIGHTING_AREA_H

#include "Logic\Entity\Component.h"

namespace Logic
{
	class CLightingArea : public IComponent
	{
		DEC_FACTORY(CLightingArea);
	public:

		CLightingArea();

		~CLightingArea();

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
		Indica si el player esta dentro del rango de luz.
		*/
		bool _playerInside;

		/**
		Radio del rango de luz.
		*/
		float _radius;

	}; // class CLightingArea

	REG_FACTORY(CLightingArea);

} // namespace Logic

#endif // LOGIC_LIGHTING_AREA_H
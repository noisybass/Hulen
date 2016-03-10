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

		void tick(unsigned int msecs) override;

		bool accept(const TMessage &message) override;

		void process(const TMessage &message) override;

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
		Indica si el player esta dentro del rango de interacción.
		*/
		bool _canInteract;

		/**
		Radio del rango de interacción.
		*/
		float _radius;

	}; // class CInteractuable

	REG_FACTORY(CInteractuable);

} // namespace Logic

#endif // LOGIC_INTERACTUABLE_H
#ifndef LOGIC_CHARGEINTERACTUABLE_H
#define LOGIC_CHARGEINTERACTUABLE_H

#include "Logic\Entity\Component.h"
#include "Logic/Entity/Components/Graphics.h"

namespace Logic
{
	class CChargeInteractuable : public IComponent
	{
		DEC_FACTORY(CChargeInteractuable);
	public:

		CChargeInteractuable();

		~CChargeInteractuable();

		bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;

		bool accept(const TMessage &message) override;

		void process(const TMessage &message) override;

	protected:

		friend class CPlayerManager;

		/**
		Indica si el player esta dentro del rango de interacción.
		*/
		bool _canInteract;

		/**
		Referencia al componente grafico.		
		*/
		CGraphics* _graphics;


	}; // class CInteractuable

	REG_FACTORY(CChargeInteractuable);

} // namespace Logic

#endif // LOGIC_CHARGEINTERACTUABLE_H
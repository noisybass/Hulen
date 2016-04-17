#ifndef LOGIC_LEVERINTERACTUABLE_H
#define LOGIC_LEVERINTERACTUABLE_H

#include "Logic\Entity\Component.h"
#include "Logic/Entity/Components/Graphics.h"

namespace Logic
{
	class CLeverInteractuable : public IComponent
	{
		DEC_FACTORY(CLeverInteractuable);
	public:

		CLeverInteractuable();

		~CLeverInteractuable();

		bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;

		void tick(unsigned int msecs) override;

		virtual bool activate() override;

		virtual void deactivate() override;

		bool accept(const TMessage &message) override;

		void process(const TMessage &message) override;

	protected:

		//friend class CPlayerManager;

		/**
		Indica si el player esta dentro del rango de interacción.
		*/
		bool _canInteract;

		/**
		Shows if the player press the button to interact with the lever.
		*/
		bool _pressLeverButton;

		/**
		By the moment the target is only the body entity, specified when get the
		body entity in the spawn method.
		*/
		CEntity* _target;

		/**
		This boolean show the state of the lever, if it is on or off.
		*/
		bool _leverSwitch;

		/**
		Change the lever color.
		*/
		CGraphics* _graphics;


	}; // class CInteractuable

	REG_FACTORY(CLeverInteractuable);

} // namespace Logic

#endif // LOGIC_LEVERINTERACTUABLE_H
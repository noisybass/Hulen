#ifndef LOGIC_LIGHTLEVER_H
#define LOGIC_LIGHTLEVER_H

#include "Logic\Entity\Component.h"
#include "Logic/Entity/Components/Graphics.h"

namespace Logic
{
	class CLightLever : public IComponent
	{
		DEC_FACTORY(CLightLever);
	public:

		CLightLever();

		~CLightLever();

		bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;

		virtual bool init(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		void tick(float msecs) override;

		virtual bool activate() override;

		virtual void deactivate(bool isDeletingMap) override;

		bool accept(const TMessage &message) override;

		void process(const TMessage &message) override;

	protected:

		//friend class CPlayerManager;

		/**
		Indica si ha colisionado una carga con la palanca de luz.
		*/
		bool _chargeAbove;

		/**
		By the moment the target is only the body entity, specified when get the
		body entity in the spawn method.
		*/
		CEntity* _target;
		CEntity* _shadowTarget;

		/**
		This boolean show the state of the lever, if it is on or off.
		*/
		bool _leverSwitch;
		bool _saverLight;

		/**
		Change the lever color.
		*/
		CGraphics* _graphics;


	}; // class CLightLever

	REG_FACTORY(CLightLever);

} // namespace Logic

#endif // LOGIC_LIGHTLEVER_H
#ifndef LOGIC_LEVERTARGETEXAMPLE_H
#define LOGIC_LEVERTARGETEXAMPLE_H

#include "Logic\Entity\Component.h"
#include "Logic/Entity/Components/Graphics.h"

namespace Logic
{
	class CLeverTargetExample : public IComponent
	{
		DEC_FACTORY(CLeverTargetExample);
	public:

		CLeverTargetExample();

		~CLeverTargetExample();

		bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;

		void tick(unsigned int msecs) override;

		bool accept(const TMessage &message) override;

		void process(const TMessage &message) override;

	protected:

		/**
		Change the lever color.
		*/
		CGraphics* _graphics;

		/**
		Lever Switch
		*/
		bool _leverSwitch;


	}; // class CInteractuable

	REG_FACTORY(CLeverTargetExample);

} // namespace Logic

#endif // LOGIC_LEVERTARGETEXAMPLE_H
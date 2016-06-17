#ifndef LOGIC_LEVERTARGETDOOR_H
#define LOGIC_LEVERTARGETDOOR_H

#include "Logic\Entity\Component.h"
#include "Logic/Entity/Components/Graphics.h"

namespace Logic
{
	class CLeverTargetDoor : public IComponent
	{
		DEC_FACTORY(CLeverTargetDoor);
	public:

		CLeverTargetDoor();

		~CLeverTargetDoor();

		bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;

		bool accept(const TMessage &message) override;

		void process(const TMessage &message) override;

	protected:

		void switchOn();
		void switchOff();

		/**
		Change the lever color.
		*/
		CGraphics* _graphics;

		// Sounds
		std::string _soundName;
		float _soundVolume;
		float _soundPitch;


	}; // class CLeverTargetDoor

	REG_FACTORY(CLeverTargetDoor);

} // namespace Logic

#endif // LOGIC_LEVERTARGETDOOR_H
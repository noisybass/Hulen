#ifndef LOGIC_MOUSE_POINTER_FOLLOWER_H
#define LOGIC_MOUSE_POINTER_FOLLOWER_H

#include "Logic\Entity\Component.h"

namespace Logic
{
	class CMousePointerFollower : public IComponent
	{
		DEC_FACTORY(CMousePointerFollower);
	public:

		bool accept(const TMessage& message) override;

		void process(const TMessage& message) override;

	}; // class CMousePointerFollower

	REG_FACTORY(CMousePointerFollower);

} // namespace Logic

#endif // LOGIC_MOUSE_POINTER_FOLLOWER_H
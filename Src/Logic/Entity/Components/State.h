#ifndef LOGIC_STATE_H
#define LOGIC_STATE_H

#include "Logic/Entity/Component.h"

namespace Logic
{

	class CState : public IComponent
	{
	public:

		virtual void enterState() { _executing = true; }

		virtual void exitState() { _executing = false; }

	protected:

		bool _executing = false;

	}; // class CState

} // namespace Logic

#endif // LOGIC_STATE_H
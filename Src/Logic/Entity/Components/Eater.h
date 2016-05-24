#ifndef LOGIC_EATER_H
#define LOGIC_EATER_H

#include "State.h"

namespace Logic
{

	class CEater : public CState
	{
		DEC_FACTORY(CEater);

		void enterState() override;

		void exitState() override;

	}; // class CEater

	REG_FACTORY(CEater);

} // namespace Logic

#endif // LOGIC_EATER
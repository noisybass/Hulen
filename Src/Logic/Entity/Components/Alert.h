#ifndef LOGIC_ALERT_H
#define LOGIC_ALERT_H

#include "Logic/Entity/Component.h"

namespace Logic
{
	class CAlert : public IComponent
	{
		DEC_FACTORY(CAlert);

	}; // class CAlert

	REG_FACTORY(CAlert);

} // namespace Logic

#endif // LOGIC_ALERT_H
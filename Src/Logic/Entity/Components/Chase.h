#ifndef LOGIC_CHASE_H
#define LOGIC_CHASE_H

#include "Logic/Entity/Component.h"

namespace Logic
{

	class CChase : public IComponent
	{
		DEC_FACTORY(CChase);

	}; // class CChase

	REG_FACTORY(CChase);

} //namespace Logic

#endif // LOGIC_CHASE_H
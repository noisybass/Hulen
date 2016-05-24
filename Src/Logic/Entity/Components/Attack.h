#ifndef LOGIC_ATTACK_H
#define LOGIC_ATTACK_H

#include "State.h"

namespace Logic
{

	class CAttack : public CState
	{
		DEC_FACTORY(CAttack);

		void enterState() override;

		void exitState() override;

	}; // class CAttack

	REG_FACTORY(CAttack);

} //namespace Logic

#endif // LOGIC_ATTACK_H
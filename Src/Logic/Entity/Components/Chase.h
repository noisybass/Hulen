#ifndef LOGIC_CHASE_H
#define LOGIC_CHASE_H

#include "State.h"

namespace Logic
{

	class CChase : public CState
	{
		DEC_FACTORY(CChase);

	public:

		CChase();

		void enterState() override;

		void exitState() override;

		void tick(float msecs) override;

	private:

		CEntity* _target;

	}; // class CChase

	REG_FACTORY(CChase);

} //namespace Logic

#endif // LOGIC_CHASE_H
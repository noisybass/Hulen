#ifndef AI_FSM_AGENT_H
#define AI_FSM_AGENT_H

#include "BaseSubsystems/StateMachine.h"

namespace AI
{

	class FSMAgent
	{
		AI::StateMachine<FSMAgent>* _FSM;

	public:

		FSMAgent();

		~FSMAgent();

		void update();

		StateMachine<FSMAgent>* getFSM() const;

		void sayHello();
	};

} //namespace AI

#endif // AI_FSM_AGENT_H
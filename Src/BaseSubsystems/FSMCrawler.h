#ifndef AI_FSM_CRAWLER_H
#define AI_FSM_CRAWLER_H

#include "BaseSubsystems/StateMachine.h"

namespace AI
{

	class FSMCrawler
	{
		AI::StateMachine<FSMCrawler>* _FSM;

		bool _seeingPlayer;

	public:

		FSMCrawler();

		~FSMCrawler();

		void update();

		StateMachine<FSMCrawler>* getFSM() const;

		bool seeingPlayer() const;

		void setSeeingPlayer(bool newValue);

	}; // class FSMCrawler

} // namespace AI

#endif // AI_FSM_CRAWLER_H
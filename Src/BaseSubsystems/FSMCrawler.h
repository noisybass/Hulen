#ifndef AI_FSM_CRAWLER_H
#define AI_FSM_CRAWLER_H

#include "BaseSubsystems/StateMachine.h"
#include "Logic/Entity/Entity.h"

namespace AI
{

	class FSMCrawler
	{
		AI::StateMachine<FSMCrawler>* _FSM;
		Logic::CEntity* _entity;

		bool _seeingPlayer;

	public:

		FSMCrawler(Logic::CEntity* entity);

		~FSMCrawler();

		void update();

		void changeState(const luabind::object& newState, const std::string& componentToDeactivate, const std::string& componentToActivate);

		StateMachine<FSMCrawler>* getFSM() const;

		bool seeingPlayer() const;

		void setSeeingPlayer(bool newValue);

	}; // class FSMCrawler

} // namespace AI

#endif // AI_FSM_CRAWLER_H
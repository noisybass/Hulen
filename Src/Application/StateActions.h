#ifndef STATEACTIONS_H
#define STATEACTIONS_H

namespace Application 
{
	enum States
	{
		NONE,
		MenuState,
		GameState,
		OptionsState,
		PauseState,
		LoadingState,
		ExitState,
		ControlsState,
		CreditsState,
	};

	enum StateAction
	{
		POP, PUSH, SET_GAME_STATE_MAP, SET_LOADING_NEXT_STATE
	};


	///  StateActions 
	class CStateActions{
	public:
		CStateActions();
		
		CStateActions(const StateAction &stateAction) : stateAction(stateAction) {}

		virtual ~CStateActions() = default;
	
		StateAction stateAction;
	};



	///  PopAction
	class CPopAction : public CStateActions{
	public:

		CPopAction() : CStateActions(StateAction::POP), release(false) {}

		CPopAction(const bool release) : CStateActions(StateAction::POP), release(release) {}

		~CPopAction() = default;
		
		bool release;
	};



	/// PushAction
	class CPushAction : public CStateActions{
	public:

		CPushAction(const States &state) : CStateActions(StateAction::PUSH), state(state), init(false) {}

		CPushAction(const States &state, const bool init, const bool passInstance = false) : CStateActions(StateAction::PUSH), state(state), init(init), passInstance(passInstance) {}

		~CPushAction() = default;

		States state;
		bool init;
		bool passInstance;
	};
	


	/// SetGameStateMap
	class CSetGameStateMapAction : public CStateActions{
	public:

		CSetGameStateMapAction(const std::string& map) : CStateActions(StateAction::SET_GAME_STATE_MAP), map(map) {}

		std::string map;
	};




	/// SetLoadingNextState
	class CSetLoadingNextState : public CStateActions{
	public:
		CSetLoadingNextState(const std::string& nextState) : CStateActions(StateAction::SET_LOADING_NEXT_STATE), nextState(nextState) {}

		std::string nextState;
	};

} // namespace Application

#endif //  STATEACTIONS_H

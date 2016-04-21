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
	};

	enum StateAction
	{
		POP, PUSH
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

		CPushAction(const States &state, const bool init) : CStateActions(StateAction::PUSH), state(state), init(init) {}

		~CPushAction() = default;

		States state;
		bool init;
	};

} // namespace Application

#endif //  STATEACTIONS_H

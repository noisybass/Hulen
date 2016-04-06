#include "FSMAgent.h"

#include "BaseSubsystems\ScriptManager.h"

namespace AI
{

	FSMAgent::FSMAgent()
	{
		_FSM = new AI::StateMachine<FSMAgent>(this);

		lua_State* lua = ScriptManager::CScriptManager::GetPtrSingleton()->getNativeInterpreter();

		luabind::object states = luabind::globals(lua);

		if (luabind::type(states) == LUA_TTABLE)
		{
			luabind::object state = states["State_Prueba"];
			_FSM->setCurrentState(states["State_Prueba"]);

			state["Probando"]();
		}

	} // FSMAgent

	FSMAgent::~FSMAgent()
	{
		delete _FSM;

	} // ~FSMAgent

	void FSMAgent::update()
	{
		_FSM->update();

	} // update

	StateMachine<FSMAgent>* FSMAgent::getFSM() const
	{
		return _FSM;

	} // getFSM

	void FSMAgent::sayHello()
	{
		std::cout << "Hello!!" << std::endl;

	} // sayHello

} // namespace AI
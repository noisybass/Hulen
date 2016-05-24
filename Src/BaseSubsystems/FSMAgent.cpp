#include "FSMAgent.h"

#include "BaseSubsystems/ScriptManager.h"

#include "Logic/Entity/Components/State.h"

namespace AI
{

	FSMAgent::FSMAgent(Logic::CEntity* entity, const std::string& initialState) : _seeingPlayer(false), _entity(entity)
	{
		_agentValues = new TValues();

		_FSM = new AI::FSM<FSMAgent>(this);

		lua_State* lua = ScriptManager::CScriptManager::GetPtrSingleton()->getNativeInterpreter();

		luabind::object states = luabind::globals(lua);

		if (luabind::type(states) == LUA_TTABLE)
		{
			_FSM->setCurrentState(states[initialState]);
		}

	} // Crawler

	FSMAgent::~FSMAgent()
	{
		delete _agentValues;
		delete _FSM;

	} // ~Crawler

	void FSMAgent::update(float msecs)
	{
		_FSM->update(msecs);

	} // update

	void FSMAgent::changeState(const luabind::object& newState)
	{
		_FSM->changeState(newState);

	} // changeState

	void FSMAgent::activate(const std::string& component)
	{
		Logic::CState* stateComponent = (Logic::CState*)_entity->getComponent(component);

		stateComponent->enterState();

	} // activate

	void FSMAgent::deactivate(const std::string& component)
	{
		Logic::CState* stateComponent = (Logic::CState*)_entity->getComponent(component);

		stateComponent->exitState();

	} // deactivate

} // namespace AI
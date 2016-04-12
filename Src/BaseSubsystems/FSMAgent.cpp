#include "FSMAgent.h"

#include "BaseSubsystems\ScriptManager.h"

namespace AI
{

	FSMAgent::FSMAgent(Logic::CEntity* entity) : _seeingPlayer(false), _entity(entity)
	{
		_agentValues = new TValues();

		_FSM = new AI::FSM<FSMAgent>(this);

		lua_State* lua = ScriptManager::CScriptManager::GetPtrSingleton()->getNativeInterpreter();

		luabind::object states = luabind::globals(lua);

		if (luabind::type(states) == LUA_TTABLE)
		{
			_FSM->setCurrentState(states["State_Patrol"]);
		}

	} // Crawler

	FSMAgent::~FSMAgent()
	{
		delete _agentValues;
		delete _FSM;

	} // ~Crawler

	void FSMAgent::update()
	{
		_FSM->update();

	} // update

	void FSMAgent::changeState(const luabind::object& newState, const std::string& componentToDeactivate, const std::string& componentToActivate)
	{
		_entity->getComponent(componentToDeactivate)->deactivate();
		_entity->getComponent(componentToActivate)->activate();

		_FSM->changeState(newState);

	} // changeState

	FSM<FSMAgent>* FSMAgent::getFSM() const
	{
		return _FSM;

	} // getFSM

	TValues* FSMAgent::getValues()
	{
		return _agentValues;

	} // getValues

} // namespace AI
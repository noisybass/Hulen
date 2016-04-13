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

	void FSMAgent::changeState(const luabind::object& newState)
	{
		_FSM->changeState(newState);

	} // changeState

	void FSMAgent::activate(const std::string& component)
	{
		_entity->getComponent(component)->activate();

	} // activate

	void FSMAgent::deactivate(const std::string& component)
	{
		_entity->getComponent(component)->deactivate();

	} // deactivate

	FSM<FSMAgent>* FSMAgent::getFSM() const
	{
		return _FSM;

	} // getFSM

	TValues* FSMAgent::getValues()
	{
		return _agentValues;

	} // getValues

	bool FSMAgent::getBoolValue(const std::string& id) const
	{
		return _agentValues->getValue<bool>(id);

	} // getBoolValue

	float FSMAgent::getFloatValue(const std::string& id) const
	{
		return _agentValues->getValue<float>(id);

	} // getFloatValue

	void FSMAgent::setBoolValue(const std::string& id, bool value)
	{
		_agentValues->setValue<bool>(id, value);

	} // setBoolValue

	void FSMAgent::setFloatValue(const std::string& id, float value)
	{
		_agentValues->setValue<float>(id, value);

	} // setFloatValue

} // namespace AI
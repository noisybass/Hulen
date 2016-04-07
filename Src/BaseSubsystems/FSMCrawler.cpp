#include "FSMCrawler.h"

#include "BaseSubsystems\ScriptManager.h"

namespace AI
{

	FSMCrawler::FSMCrawler() : _seeingPlayer(false)
	{
		_FSM = new AI::StateMachine<FSMCrawler>(this);

		lua_State* lua = ScriptManager::CScriptManager::GetPtrSingleton()->getNativeInterpreter();

		luabind::object states = luabind::globals(lua);

		if (luabind::type(states) == LUA_TTABLE)
		{
			_FSM->setCurrentState(states["State_Patrol"]);
		}

	} // Crawler

	FSMCrawler::~FSMCrawler()
	{
		delete _FSM;

	} // ~Crawler

	void FSMCrawler::update()
	{
		_FSM->update();

	} // update

	StateMachine<FSMCrawler>* FSMCrawler::getFSM() const
	{
		return _FSM;

	} // getFSM

	bool FSMCrawler::seeingPlayer() const
	{
		return _seeingPlayer;

	} // seeingPlayer

	void FSMCrawler::setSeeingPlayer(bool newValue)
	{
		_seeingPlayer = newValue;

	} // setSeeingPlayer

} // namespace AI
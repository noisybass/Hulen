#include "FSMEntity.h"

#include "BaseSubsystems\ScriptManager.h"

extern "C"
{
#include <lua.h>
}

#include <luabind\luabind.hpp>

namespace Logic
{
	IMP_FACTORY(CFSMEntity);

	bool CFSMEntity::spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		// Creamos la máquina de estados
		_FSM = new AI::StateMachine<CFSMEntity>(this);

		// Registramos las funciones de esta clase que se van a usar
		// desde los estados
		registerFSMEntity();

		// Cargamos el script con las definiciones de los estados
		loadStates();

		return true;

	} // spawn

	bool CFSMEntity::activate()
	{
		// Al activar el componenente es cuando le asignamos a la máquina 
		// de estados el estado inicial

		lua_State* lua = ScriptManager::CScriptManager::GetPtrSingleton()->getNativeInterpreter();

		luabind::object states = luabind::globals(lua);

		if (luabind::type(states) == LUA_TTABLE)
		{
			_FSM->setCurrentState(states["State_Prueba"]);

			return true;
		}

		return false;

	} // activate

	void CFSMEntity::tick(unsigned int msecs)
	{
		_FSM->update();

	} // tick

	void CFSMEntity::sayHello()
	{
		std::cout << "Hello!!" << std::endl;

	} // sayHello

	void CFSMEntity::registerFSMEntity()
	{
		std::cout << "Registrando funciones del componente..." << std::endl;

		lua_State* lua = ScriptManager::CScriptManager::GetPtrSingleton()->getNativeInterpreter();

		luabind::module(lua)
			[
				luabind::class_<CFSMEntity>("CFSMEntity")
				.def("SayHello", &CFSMEntity::sayHello)
				.def("GetFSM", &CFSMEntity::getFSM)
			];

	} // registerFSMEntity

	void CFSMEntity::loadStates()
	{
		std::cout << "Cargando el script de los estados..." << std::endl;

		ScriptManager::CScriptManager::GetPtrSingleton()->loadScript("media/lua/states.lua");

	} // loadStates

} // namespace Logic
#include "FSMEntity.h"

#include "BaseSubsystems\ScriptManager.h"

#include <iostream>

//extern "C"
//{
//#include <lua.h>
//}
//
//#include <luabind\luabind.hpp>

namespace Logic
{
	/*IMP_FACTORY(CFSMEntity);*/

	CFSMEntity::CFSMEntity()
		/*: IComponent()*/
	{
		// Creamos la máquina de estados
		_FSM = new AI::StateMachine<CFSMEntity>(this);
	}

	bool CFSMEntity::activate()
	{
		// Al activar el componenente es cuando le asignamos a la máquina 
		// de estados el estado inicial
		lua_State* lua = ScriptManager::CScriptManager::GetPtrSingleton()->getNativeInterpreter();

		luabind::object states = luabind::globals(lua);

		if (luabind::type(states) == LUA_TTABLE)
		{
			luabind::object state = states["State_Prueba"];
			_FSM->setCurrentState(states["State_Prueba"]);

			state["Probando"]();

			//state["ProbandoConArgumentos"](*this);

			return true;
		}

		return false;

	} // activate

	void CFSMEntity::tick(unsigned int msecs)
	{
		/*IComponent::tick(msecs);*/

		_FSM->update();

	} // tick

	void CFSMEntity::sayHello()
	{
		std::cout << "Hello!!" << std::endl;

	} // sayHello

} // namespace Logic
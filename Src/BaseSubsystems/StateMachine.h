#ifndef AI_STATE_MACHINE_H
#define AI_STATE_MACHINE_H

#include "Logic\Entity\Components\FSMEntity.h"

extern "C"
{
#include <lua.h>
}

#include <luabind\luabind.hpp>

namespace AI
{
	template <class T>
	class StateMachine
	{
	private:
		
		// Puntero al agente que posee la FSM
		T* _owner;

		// El estado actual es una tabla de funciones en Lua, que 
		// representaremos en C++ con un luabind::object
		luabind::object _currentState;

	public:

		StateMachine(T* owner)
			: _owner(owner) 
		{
			std::cout << "Registrando funciones de la maquina de estados..." << std::endl;

			/*lua_State* lua = ScriptManager::CScriptManager::GetPtrSingleton()->getNativeInterpreter();

			luabind::module(lua)
				[
					luabind::class_<StateMachine<T> >("State Machine")
					.def("ChangeState", &StateMachine<T>::changeState)
					.def("GetCurrentState", &StateMachine<T>::getCurrentState)
					.def("SetCurrentState", &StateMachine<T>::setCurrentState)
				];*/

		} // StateMachine

		void setCurrentState(const luabind::object& state)
		{
			_currentState = state;

		} // setCurrentState

		void update()
		{
			std::cout << "UPDATE" << std::endl;

			//// Nos aseguramos de que el estado es válido antes de llamar
			//// a execute()
			/*if (_currentState.is_valid())
			{
				_currentState["Execute"](_owner);
			}*/

		} // update

		void changeState(const luabind::object& newState)
		{
			// Llamamos al método de salida del estado actual
			_currentState["Exit"](_owner);

			// Cambiamos el estado
			_currentState = newState;

			// Llamamos al método de entrada del nuevo estado
			_currentState["Enter"](_owner);

		} // changeState

		const luabind::object& getCurrentState() const
		{
			return _currentState;

		} // currentState

	}; // class StateMachine

} // namespace AI

#endif // AI_STATE_MACHINE_H
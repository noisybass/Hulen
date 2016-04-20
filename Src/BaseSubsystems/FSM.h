#ifndef AI_FSM_H
#define AI_FSM_H

extern "C"
{
#include <lua.h>
}

#include <luabind\luabind.hpp>

#include <iostream>

namespace AI
{
	template <class T>
	class FSM
	{
	private:
		
		// Puntero al agente que posee la FSM
		T* _owner;

		// El estado actual es una tabla de funciones en Lua, que 
		// representaremos en C++ con un luabind::object
		luabind::object _currentState;

	public:

		FSM(T* owner)
			: _owner(owner) 
		{

		} // FSM

		void setCurrentState(const luabind::object& state)
		{
			_currentState = state;

		} // setCurrentState

		void update(unsigned int msecs)
		{
			// Nos aseguramos de que el estado es válido antes de llamar
			// a execute()
			if (_currentState.is_valid())
			{
				_currentState["Execute"](_owner, msecs);
			}

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

	}; // class FSM

} // namespace AI

#endif // AI_FSM_H
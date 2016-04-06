#ifndef AI_STATE_MACHINE_H
#define AI_STATE_MACHINE_H

extern "C"
{
#include <lua.h>
}

#include <luabind\luabind.hpp>

#include <iostream>

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

		} // StateMachine

		void setCurrentState(const luabind::object& state)
		{
			_currentState = state;

		} // setCurrentState

		void update()
		{
			//// Nos aseguramos de que el estado es válido antes de llamar
			//// a execute()
			if (_currentState.is_valid())
			{
				std::cout << "UPDATE" << std::endl;
				//Logic::CFSMEntity* entidadPrueba = new Logic::CFSMEntity();
				//_currentState["ProbandoConArgumentos"](entidadPrueba);
				_currentState["Execute"](_owner);
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

	}; // class StateMachine

} // namespace AI

#endif // AI_STATE_MACHINE_H
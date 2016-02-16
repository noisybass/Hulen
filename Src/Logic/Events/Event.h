#ifndef LOGIC_EVENT_H
#define LOGIC_EVENT_H

#include <vector>
#include <assert.h>

#include "Application/GameState.h"

namespace Logic{

	template <typename classType, typename functionType, typename... ARGS>
	struct CEventValues{
	public:
		static const classType    dieClass    = Application::CGameState;
		static const functionType dieFunction = void (Application::CGameState::*) (std::string&);
	};
	

	/**
	Esta clase sirve para mandar eventos principalmente de la parte de la logica 
	a la aplicación.

	Como Funciona:
	La idea de 
	*/
	template <typename classType, typename functionType, typename... ARGS>
	class CEventSystem {
	public:

		template <typename classType, typename functionType>
		CEventSystem(classType& _class, functionType _fun){

			assert(!_eventSystemInstance && "No puedes crear el mismo evento dos veces");

			_instance = _class;
			_functions.push_back(_fun);
			_eventSystemInstance = this;
		}

		template <typename classType, typename functionType>
		static CEventSystem<classType, functionType>* getInstance(){ return _eventSystemInstance; }
		
		/**
		Lanza el evento
		*/
		template<typename... ARGS>
		void fireEvent(ARGS... args){
			unsigned int size = _functions.size();
			for (unsigned int i = 0; i < size; ++i){
				(*_instance.*(_functions[i])) (args...);
			}
		}

		void clearEvents(){
			_eventSystemInstance = nullptr;
			_instance = nullptr;
			while (!_functions.empty()){
				_functions.pop_back();
			}
		}

	private:
		classType* _instance;
		std::vector<functionType> _functions;
		static CEventSystem<classType, functionType, ARGS...>* _eventSystemInstance;
	};

	// Definiendo _eventSystemInstance
	template <typename classType, typename functionType, typename... ARGS>
	CEventSystem<classType, functionType, ARGS...>* CEventSystem<classType, functionType, ARGS...>::_eventSystemInstance;
	
}



#endif // LOGIC_EVENT_H
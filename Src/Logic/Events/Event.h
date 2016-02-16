#ifndef LOGIC_EVENT_H
#define LOGIC_EVENT_H

#include <vector>

namespace Logic{
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
			_instance = _class;
			_functions.push_back(_fun);
			//_eventSystemInstance = this;
		}


		//CEventSystem* getInstance{ return _eventSystemInstance; }
		
		/**
		Lanza el evento
		*/
		template<typename... ARGS>
		void fireEvent(ARGS... args){
			unsigned int size = _functions.size();
			for (unsigned int i = 0; i < size; ++i){
				(_instance.*(_functions[i])) (args...);
			}

		}

	private:
		classType* _instance;
		std::vector<functionType> _functions;
		//static EventSystem* _eventSystemInstance;
	};

}



#endif // LOGIC_EVENT_H
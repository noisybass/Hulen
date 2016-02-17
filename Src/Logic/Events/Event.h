#ifndef LOGIC_EVENT_H
#define LOGIC_EVENT_H

#include <vector>
#include <assert.h>


namespace Application
{
	class CGameState;
}

namespace Logic{


	/**
	El siguiente espacio de nombre es basicamente para que el 
	codigo sea más legible, y así en vez de tener una llamada de este tipo:

		<Code> Logic::CEventSystem<Application::CGameState, void (Application::CGameState::*) (std::string&)>::
				       getInstance<Application::CGameState, void (Application::CGameState::*) (std::string&)>()
					   ->fireEvent(string);  </Code>
		
		Tenemos lo siguiente:

		<Code> Logic::CEventSystem<Logic::Events::DieClass, Logic::Events::DieFunction>::
				       getInstance<Logic::Events::DieClass, Logic::Events::DieFunction>()
				       ->fireEvent(string);  </Code>

	Simplemente por hacer un poco más legible el código.
	*/
	namespace Events{

		/*Die Event*/
		typedef Application::CGameState DieClass;
		typedef void (Application::CGameState::* DieFunction) (std::string&);

		/*Next Event*/
	};
	

	/**
	Esta clase sirve para mandar eventos principalmente de la parte de la logica 
	a la aplicación.

	Resumen:
	Basicamente si tenemos las siguientes clases: CGameState, PlayerManager y CEventSystem el 
	procedimiento es el siguiente

		-------------------									-------------------	
		|	CGameState    |<-------------					| CPlayerManager  |
		-------------------			(3)	|					-------------------
				|						|							|
				|						|							|
				|	(1)			-------------------				(2)	|
				------------->  |   CEventSystem  |	<----------------
								-------------------
								
	(1) : Nos subscribimos al evento diciendo que clase somos y que funcion queremos
		  que se llame cuando se produzca el evento.

	(2) : Cuando queramos lanzar el evento, lo lanzamos desde cualquier clase
		  accediendo a la instancia de ella.

	(3) : Por ultimo al haber lanzado el evento, la clase CEventSystem se encarga de 
		  llamar a los metodos de las clases que se han subscrito al evento.

	Como Funciona (Lo que hay que hacer para que funcione):
	Imaginemos que cuando el jugador muere queremos decirle a la aplicación que cambie
	su estado actual, lo hariamos de la siguiente manera:
		1 - En la clase CGameState, que es la que maneja los estados de nuestra applicación,
		nos creamos una variable de esta clase de la siguiente manera:
			<Code> Logic::CEventSystem <Logic::Events::DieClass, Logic::Events::DieFunction> dieEvent; </Code>

		Siendo DieClass el tipo de la clase que se subscribe al evento (En este caso nuestro CGameState)
		y la función que se ejecutara cuando se dispare el evento.

		2 - Despues de esto lo inicializamos en el metodo init de CGameState:
			<Code> dieEvent.initEvent(this, &Application::CGameState::playerListener); </Code>

		3 - Una vez hecho esto lo unico que nos queda es que cuando el player muera, 
		avisemos al CGameState de este evento, para ello, en nuestro caso lo realizamos 
		en la clase PlayerManager de la siguiente manera:
			<Code> Logic::CEventSystem<Logic::Events::DieClass, Logic::Events::DieFunction>::
				           getInstance<Logic::Events::DieClass, Logic::Events::DieFunction>()
				           ->fireEvent(string);    </Code>

		basicamente obtenemos la referencia de esa clase y llamamos al fireEvent (En este caso
		lo llamamos con argumentos porque la funcion a la que nos hemos registrado tiene un
		argumento de tipo std::string).
	*/
	template <typename classType, typename functionType, typename... ARGS>
	class CEventSystem {
	public:

		/**
		Constructor por defecto.
		*/
		CEventSystem() = default;

		/**
		Constructor de la clase en el cual crearemos un evento con la referencia a la clase y 
		una funcion que querremos que se llame cuando se lance el evento.

		OJO: si creamos dos eventos de la sioguiente manera:

		<Code> Logic::CEventSystem <Logic::Events::DieClass, Logic::Events::DieFunction> dieEvent;
		Logic::CEventSystem <Logic::Events::DieClass, Logic::Events::DieFunction> FinishEvent; </Code>

		no funciona, porque no puede haber dos instancias iguales, pero por lo tanto podemos hacer lo siguiente:

		<Code> Logic::CEventSystem <Logic::Events::DieClass, Logic::Events::DieClass> dieEvent;
		Logic::CEventSystem <Logic::Events::FinishClass, Logic::Events::FinishClass> FinishEvent; </Code>

		Son dos instancias diferentes ya que los tipos de los dos eventos son diferentes.
		*/
		template <typename classType, typename functionType>
		void initEvent(classType& _class, functionType _fun){
			assert(!_eventSystemInstance && "No puedes crear el mismo evento dos veces");

			_instance = _class;
			_functions.push_back(_fun);
			_eventSystemInstance = this;
		}

		/**
		Obtenemos la referencia a la clase.
		*/
		template <typename classType, typename functionType>
		static CEventSystem<classType, functionType>* getInstance(){ return _eventSystemInstance; }
		
		/**
		Al llamar a fireEvent se llamaran, en el orden en el que se fueron subscribiendo las
		funciones, a todas las funciones subscritas de esa clase.
		*/
		template<typename... ARGS>
		void fireEvent(ARGS... args){
			unsigned int size = _functions.size();
			for (unsigned int i = 0; i < size; ++i){
				(*_instance.*(_functions[i])) (args...);
			}
		}

		/**
		Limpiamos los restos que pudiesen quedar.
		*/
		void clearEvents(){
			// No hacemos delete de ninguna referencia, si lo hacemos
			// nos cargamos las verdaderas instancias.
			_eventSystemInstance = nullptr;
			_instance = nullptr;

			// Eliminamos lo que hubiese en el vector, no hace falta eliminarlo
			// ya que son referencias a las funciones.
			while (!_functions.empty()){
				_functions.pop_back();
			}
		}

	private:
		
		classType* _instance; // Instancia de la clase que se subscribira al evento.

		std::vector<functionType> _functions; // Funciones de la clase que se subcribira al evento, las cuales
											  // se llamaran cuando se llame a fireEvent.
		static CEventSystem<classType, functionType, ARGS...>* _eventSystemInstance; // Referencia a la propia clase
	};

	// Definiendo _eventSystemInstance
	template <typename classType, typename functionType, typename... ARGS>
	CEventSystem<classType, functionType, ARGS...>* CEventSystem<classType, functionType, ARGS...>::_eventSystemInstance;
	
}

#endif // LOGIC_EVENT_H
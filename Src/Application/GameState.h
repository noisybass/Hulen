//---------------------------------------------------------------------------
// GameState.h
//---------------------------------------------------------------------------

/**
@file GameState.h

Contiene la declaración del estado de juego.

@see Application::CApplicationState
@see Application::CGameState

@author David Llansó
@date Agosto, 2010
*/

#ifndef __Application_GameState_H
#define __Application_GameState_H

#include "ApplicationState.h"
#include "Logic\Events\Event.h"
#include "Sounds\api\SoundsResources.h"


// Predeclaración de clases para ahorrar tiempo de compilación
namespace Application 
{
	class CBaseApplication;
}

namespace Graphics 
{
	class CScene;
	class CCamera;
	class CEntity;
	class CStaticEntity;
	class CAnimatedEntity;
}

namespace CEGUI
{
	class Window;
}

namespace Application 
{
	/**
	Clase CGameState; representa el estado de juego de la aplicación.
	Se encarga de la preparación y la carga del mapa lógico del juego.
	Tiene cableados los nombres de ficheros de mapa y de blueprints por
	simplicidad. En la activación y desactivación se encarga de activar
	y desactivar el módulo que se encarga de manejar al jugador leyendo 
	eventos de entrada de periféricos y de activar y desactivar el mapa 
	de Logic::CServer. En el tick() también se actualiza el módulo de 
	lógica.
	<p>
	Como ejemplo de Ventana 2D para el GUI se tiene una pequeña ventana 
	que muestra el tiempo transcurrido. 
	Esto provoca que este estado sea CEGUI dependiente, lo cual no es 
	deseable. La aplicación	debería ser independiente de las tecnologías 
	usadas.

	@ingroup applicationGroup

	@author David Llansó
	@date Agosto, 2010
	*/
	class CGameState : public CApplicationState 
	{
	public:
		/** 
		Constructor de la clase 
		*/
		CGameState(CBaseApplication *app) : CApplicationState(app), 
			_scene(0), _time(0), _isMapLoaded(false), _mapName("map.lua") 
		{
			_soundResources = Sounds::CSoundsResources::getSingletonPtr();

			_levels.insert({ 1, "sublevelOne.lua" });
			_levels.insert({ 2, "sublevelTwo.lua" });
			_levels.insert({ 3, "sublevelThree.lua" });
			_levels.insert({ 4, "sublevelFour.lua" });
			_levels.insert({ 5, "twoSublevelOne.lua" });

			_levelsNames.insert({ "sublevelOne.lua", 1 });
			_levelsNames.insert({ "sublevelTwo.lua", 2 });
			_levelsNames.insert({ "sublevelThree.lua", 3 });
			_levelsNames.insert({ "sublevelFour.lua", 4 });
			_levelsNames.insert({ "twoSublevelOne.lua", 5 });
		}

		/** 
		Destructor 
		*/
		virtual ~CGameState() { _soundResources = nullptr; }

		/**
		Función llamada cuando se crea el estado (se "engancha" en la
		aplicación, para que inicialice sus elementos.

		@return true si todo fue bien.
		*/
		virtual bool init();

		/**
		Función llamada cuando se elimina ("desengancha") el
		estado de la aplicación.
		*/
		virtual void release();

		/**
		Función llamada por la aplicación cuando se activa
		el estado.
		*/
		virtual void activate();

		/**
		Función llamada por la aplicación cuando se desactiva
		el estado.
		*/
		virtual void deactivate();

		/**
		Función llamada por la aplicación para que se ejecute
		la funcionalidad del estado.

		@param msecs Número de milisegundos transcurridos desde
		la última llamada (o desde la áctivación del estado, en caso
		de ser la primera vez...).
		*/
		virtual void tick(float msecs);

		/**
		Método que cambia el fichero del mapa a cargar. 
		Comprueba que existe el mapa con el nombre que le llega por parámetro.  
		*/
		bool setMap(const std::string &mapname);

		// Métodos de CKeyboardListener
		
		/**
		Método que será invocado siempre que se pulse una tecla. 
		Será la aplicación quién llame a este método cuando el 
		estado esté activo. Esta clase NO se registra en el 
		InputManager sino que es la aplicación quien lo hace y 
		delega en los estados.

		@param key Código de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamará a otros listeners.
		*/
		virtual bool keyPressed(GUI::TKey key);
		
		/**
		Método que será invocado siempre que se termine la pulsación
		de una tecla. Será la aplicación quién llame a este método 
		cuando el estado esté activo. Esta clase NO se registra en
		el InputManager sino que es la aplicación quien lo hace y 
		delega en los estados.

		@param key Código de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamará a otros listeners.
		*/
		virtual bool keyReleased(GUI::TKey key);

		// Métodos de CMouseListener
		
		/**
		Método que será invocado siempre que se mueva el ratón. La
		aplicación avisa de este evento al estado actual.

		@param mouseState Estado del ratón cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamará a otros listeners.
		*/
		virtual bool mouseMoved(const GUI::CMouseState &mouseState);
		
		/**
		Método que será invocado siempre que se pulse un botón. La
		aplicación avisa de este evento al estado actual.

		@param mouseState Estado del ratón cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamará a otros listeners.
		*/
		virtual bool mousePressed(const GUI::CMouseState &mouseState);

		/**
		Método que será invocado siempre que se termine la pulsación
		de un botón. La aplicación avisa de este evento al estado 
		actual.

		@param mouseState Estado del ratón cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamará a otros listeners. 
		*/
		virtual bool mouseReleased(const GUI::CMouseState &mouseState);

		/**
		Metodo que utilizaremos para escuchar los eventos de muerte del player
		*/
		void playerListener(std::string &action);

	protected:

		/**
		Indica si el mapa se ha cargado o no.
		*/
		bool _isMapLoaded;

		/**
		Nombre del mapa a cargar.
		*/
		std::string _mapName;

		/**
		Escena del estado.
		*/
		Graphics::CScene* _scene;

		/**
		Ventana que muestra el tiempo de juego transcurrido.
		*/
		//CEGUI::Window* _timeWindow;

		/**
		Tiempo de juego en milisegundos.
		*/
		float _time;

		/**
		Player events.
		*/
		Logic::CEventSystem <Logic::Events::GameStateClass, Logic::Events::PlayerEventFunction> playerEvent;

		/**
		To play sounds
		*/
		Sounds::CSoundsResources* _soundResources;

		/**
		Game Levels
		We have two to get O(1) searches, and I think that doesn't matter 
		have another table wit these values, taht I don't think 
		*/
		std::unordered_map<int, std::string> _levels;
		std::unordered_map<std::string, int> _levelsNames;

	}; // CGameState

} // namespace Application

#endif //  __Application_GameState_H

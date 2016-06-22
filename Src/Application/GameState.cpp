//---------------------------------------------------------------------------
// GameState.cpp
//---------------------------------------------------------------------------

/**
@file GameState.cpp

Contiene la implementación del estado de juego.

@see Application::CApplicationState
@see Application::CGameState

@author David Llansó
@date Agosto, 2010
*/

#include "GameState.h"

#include "Logic/Server.h"
#include "Logic/Maps/EntityFactory.h"
#include "Logic/Maps/Map.h"
#include "Logic\Events\Event.h"

#include "Map\MapParser.h"

#include "GUI/Server.h"
#include "GUI/PlayerController.h"
#include "GUI/LightController.h"

#include "Physics/Server.h"

#include <CEGUI/System.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/Window.h>

namespace Application {

	bool CGameState::init() 
	{
		CApplicationState::init();

		// Crear la escena física.
		//Physics::CServer::getSingletonPtr()->setGroupCollisions(0,1,false);
		Physics::CServer::getSingletonPtr()->createScene();

		// Cargamos el archivo con las definiciones de las entidades del nivel.
		if (!Logic::CEntityFactory::getSingletonPtr()->loadBluePrints("blueprints.lua"))
			return false;

		// Cargamos el nivel a partir del nombre del mapa. 
		if (!Logic::CServer::getSingletonPtr()->loadLevel(_mapName, "prefabs.lua"))
			return false;

		// Cargamos la ventana que muestra el tiempo de juego transcurrido.
		//_timeWindow = CEGUI::WindowManager::getSingletonPtr()->loadLayoutFromFile("Time.layout");

		// Init the events
		playerEvent.initEvent(this, &Application::CGameState::playerListener);

		_isMapLoaded = true;

		// Start the sound
		_soundResources->createInstance(std::string("GameInstance"), std::string("MainMenuEvent"));
		_soundResources->setInstanceParameterValue(std::string("GameInstance"), std::string("Intensidad"), 80);

		return true;

	} // init

	//--------------------------------------------------------

	void CGameState::release() 
	{
		Logic::CServer::getSingletonPtr()->unLoadLevel();

		Logic::CEntityFactory::getSingletonPtr()->unloadBluePrints();

		// Liberamos la escena física.
		Physics::CServer::getSingletonPtr()->destroyScene();

		// Erase the gameSound
		_soundResources->deleteInstance(std::string("GameInstance"));

		// Liberamos el evento
		playerEvent.clearEvents();

		Map::CMapParser::getSingletonPtr()->releaseEntityList();
		Map::CMapParser::getSingletonPtr()->releasePrefabList();

		_isMapLoaded = false;

		CApplicationState::release();
	} // release

	//--------------------------------------------------------

	void CGameState::activate() 
	{
		CApplicationState::activate();
		
		// Activamos el mapa que ha sido cargado para la partida.
		Logic::CServer::getSingletonPtr()->activateMap();

		// Queremos que el GUI maneje al jugador.
		GUI::CServer::getSingletonPtr()->getPlayerController()->activate();

		// Queremos que el GUI maneje a la luz.
		GUI::CServer::getSingletonPtr()->getLightController()->activate();

		// We want the objects can receive messages from the input.
		GUI::CServer::getSingletonPtr()->getObjectsController()->activate();

		// Activamos la ventana que nos muestra el tiempo transcurrido.
		/*CEGUI::System::getSingletonPtr()->getDefaultGUIContext().setRootWindow(_timeWindow);
		_timeWindow->setVisible(true);
		_timeWindow->activate();*/

		_soundResources->playInstance(std::string("GameInstance"));
		

	} // activate

	//--------------------------------------------------------

	void CGameState::deactivate() 
	{
		_soundResources->pauseInstance(std::string("GameInstance"));
		
		// Desactivamos la ventana de tiempo.
		//_timeWindow->deactivate();
		//_timeWindow->setVisible(false);

		// Desactivamos la clase que procesa eventos de entrada para 
		// controlar al jugador.
		GUI::CServer::getSingletonPtr()->getPlayerController()->deactivate();

		// Desactivamos la luz
		GUI::CServer::getSingletonPtr()->getLightController()->deactivate();

		// Deactivate the objects
		GUI::CServer::getSingletonPtr()->getObjectsController()->deactivate();
		
		// Desactivamos el mapa de la partida.
		Logic::CServer::getSingletonPtr()->deactivateMap();
		
		CApplicationState::deactivate();

	} // deactivate

	//--------------------------------------------------------

	void CGameState::tick(float msecs) 
	{
		CApplicationState::tick(msecs);

		// Simulación física
		Physics::CServer::getSingletonPtr()->tick(msecs);

		// Actualizamos la lógica de juego.
		Logic::CServer::getSingletonPtr()->tick(msecs);

		/*_time += msecs;
		
		std::stringstream text;
		text << "Time: " << (int)_time;
		_timeWindow->setText(text.str());*/

	} // tick

	//--------------------------------------------------------

	bool CGameState::keyPressed(GUI::TKey key)
	{
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CGameState::keyReleased(GUI::TKey key)
	{
		switch(key.keyId)
		{
		case GUI::Key::ESCAPE:

			// Push PauseState (activation)

			_app->addAction(new CPushAction(States::PauseState));
			break;
//#ifdef _DEBUG
		case GUI::Key::R:
			_app->reloadState();
			break;
//#endif
		default:
			return false;
		}
		return true;

	} // keyReleased

	//--------------------------------------------------------

	bool CGameState::setMap(const std::string &mapname){
		if (!_isMapLoaded){

			// Comprobamos que existe un fichero de mapa con ese nombre.
			if (!Logic::CServer::getSingletonPtr()->checkMapExists(mapname))
				return false;
			
			_mapName = mapname;
			return true;
		}
		else{
			return false;
		}

	} // setMapName

	//--------------------------------------------------------
	
	bool CGameState::mouseMoved(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CGameState::mousePressed(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mousePressed

	//--------------------------------------------------------


	bool CGameState::mouseReleased(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseReleased

	//--------------------------------------------------------

	void CGameState::playerListener(std::string &action){
		if (action == "die"){
			std::cout << "He muerto" << std::endl;
			_app->reloadState();
		}
		else if (action == "endLevel"){
			std::cout << "End level" << std::endl;

			// Pop GameState
			_app->addAction(new CPopAction(true));

			// Intenta cambiar el fichero del mapa a cargar
			unsigned int levelNumber = _levelsNames.at(_mapName) + 1;

			// There is more levels
			if (_levels.find(levelNumber) != _levels.end())
			{
	
				std::string newLevel = _levels.at(levelNumber);
				_app->addAction(new CSetGameStateMapAction(newLevel));

				// Le decimos al estado de loading que la siguiente escena a cargar es la de game
				//_app->setLoadingNextState("game");
				_app->addAction(new CSetLoadingNextState(std::string("game")));

				// Push LoadingState
				_app->addAction(new CPushAction(States::LoadingState, true));

			}
			else
			{
				// Push MenuState
				_app->addAction(new CPushAction(States::MenuState, true));
			}
		}

	} // playerListener

} // namespace Application

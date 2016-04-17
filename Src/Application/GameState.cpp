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

#include "Sounds\Server.h"

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
		if (!Logic::CServer::getSingletonPtr()->loadLevel(_mapName, "Prefabs.lua"))
			return false;

		// Cargamos la ventana que muestra el tiempo de juego transcurrido.
		_timeWindow = CEGUI::WindowManager::getSingletonPtr()->loadLayoutFromFile("Time.layout");

		// Inicializamos el evento
		dieEvent.initEvent(this, &Application::CGameState::playerListener);

		_isMapLoaded = true;

		return true;

	} // init

	//--------------------------------------------------------

	void CGameState::release() 
	{
		Logic::CServer::getSingletonPtr()->unLoadLevel();

		Logic::CEntityFactory::getSingletonPtr()->unloadBluePrints();

		// Liberamos la escena física.
		Physics::CServer::getSingletonPtr()->destroyScene();

		CApplicationState::release();

		// Liberamos el evento
		dieEvent.clearEvents();


		Map::CMapParser::getSingletonPtr()->releaseEntityList();
		Map::CMapParser::getSingletonPtr()->releasePrefabList();

		_isMapLoaded = false;

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
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().setRootWindow(_timeWindow);
		_timeWindow->setVisible(true);
		_timeWindow->activate();

		/*
		Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		soundServer->getSoundsPtr()->loadSound("TemaPrincipal", "Hulen-Textura1.wav", Sounds::Loop_Normal && Sounds::Sound_3D);
		soundServer->getChannelsPtr()->loadChannel("CanalMenu", "TemaPrincipal");
		soundServer->getChannelsPtr()->setVolume("CanalMenu", 0.3);
		Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		*/
		//soundServer->getEventInstancesPtr()->setParameterValue("Instancia1", "Intensidad", 80);


	} // activate

	//--------------------------------------------------------

	void CGameState::deactivate() 
	{

		Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		//soundServer->getEventInstancesPtr()->setParameterValue("Instancia1", "Intensidad", 1);

		/*Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		soundServer->getChannelsPtr()->stop("CanalMenu");
		soundServer->getSoundsPtr()->unloadSound("TemaPrincipal");*/

		// Desactivamos la ventana de tiempo.
		_timeWindow->deactivate();
		_timeWindow->setVisible(false);

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

	void CGameState::tick(unsigned int msecs) 
	{
		CApplicationState::tick(msecs);

		// Simulación física
		Physics::CServer::getSingletonPtr()->tick(msecs);

		// Actualizamos la lógica de juego.
		Logic::CServer::getSingletonPtr()->tick(msecs);

		_time += msecs;
		
		std::stringstream text;
		text << "Time: " << _time/1000;
		_timeWindow->setText(text.str());

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

			_app->pushState("pause");
			break;
		case GUI::Key::R:
			_app->reloadState();
			break;
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
		if (action == "Die"){
			std::cout << "He muerto" << std::endl;
			_app->reloadState();
		}

	}

} // namespace Application

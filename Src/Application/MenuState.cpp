//---------------------------------------------------------------------------
// MenuState.cpp
//---------------------------------------------------------------------------

/**
@file MenuState.cpp

Contiene la implementación del estado de menú.

@see Application::CApplicationState
@see Application::CMenuState

@author David Llansó
@date Agosto, 2010
*/

#include "MenuState.h"

#include "GUI/Server.h"
#include "Sounds\Server.h"

#include <CEGUI/CEGUI.h>

#include <regex>

namespace Application {

	CMenuState::~CMenuState() 
	{
	} // ~CMenuState

	//--------------------------------------------------------

	bool CMenuState::init() 
	{
		CApplicationState::init();

		// Cargamos la ventana que muestra el menú
		_menuWindow = CEGUI::WindowManager::getSingletonPtr()->loadLayoutFromFile("Menu.layout");
		
		// Asociamos los botones del menú con las funciones que se deben ejecutar.
		_menuWindow->getChildElement("Start")->
			subscribeEvent(CEGUI::PushButton::EventClicked, 
				CEGUI::SubscriberSlot(&CMenuState::startReleased, this));
		
		_menuWindow->getChildElement("Exit")->
			subscribeEvent(CEGUI::PushButton::EventClicked, 
				CEGUI::SubscriberSlot(&CMenuState::exitReleased, this));

		_menuWindow->getChildElement("Options")->
			subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::SubscriberSlot(&CMenuState::optionsReleased, this));

		// Sonido en el menu principal
		/*
		Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		soundServer->getSoundsPtr()->loadSound("TemaPrincipal", "Hulen-Textura1.wav", Sounds::Loop_Normal && Sounds::Sound_3D);
		soundServer->getChannelsPtr()->loadChannel("CanalMenu", "TemaPrincipal");
		soundServer->getChannelsPtr()->setVolume("CanalMenu", 0.3);
		*/
		
		/*
		Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		soundServer->getBanksPtr()->loadBank("Banco1", "Master Bank.bank");
		soundServer->getBanksPtr()->loadBank("Banco2", "Master Bank.strings.bank");
		soundServer->getBanksPtr()->loadBank("Banco3", "Ambiente.bank");
		soundServer->getEventDescriptionsPtr()->loadEventDescription("Evento1", "event:/Ambientes");
		*/
		
		
		//soundServer->getEventInstancesPtr()->loadInstance("Instancia1", "Evento1");
		//soundServer->getEventInstancesPtr()->setPaused("Instancia1", false);
		//soundServer->getEventInstancesPtr()->setParameterValue("Instancia1", "RPM", 650);
		//soundServer->getEventInstancesPtr()->start("Instancia1");
		//*/
		return true;

	} // init

	//--------------------------------------------------------

	void CMenuState::release() 
	{

		/*
		Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		soundServer->getChannelsPtr()->stop("CanalMenu");
		soundServer->getSoundsPtr()->unloadSound("TemaPrincipal");
		*/
		
		//Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		//soundServer->getEventInstancesPtr()->stop("Instancia1");
		
		CApplicationState::release();

	} // release

	//--------------------------------------------------------

	void CMenuState::activate() 
	{
		CApplicationState::activate();

		// Activamos la ventana que nos muestra el menú y activamos el ratón.
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().setRootWindow(_menuWindow);
		_menuWindow->setVisible(true);
		_menuWindow->activate();
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().show();

		/*
		Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		soundServer->getChannelsPtr()->setPaused("CanalMenu", false);

		*/
		//Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		//soundServer->getEventInstancesPtr()->setPaused("Instancia1", false);
		//*/

	} // activate

	//--------------------------------------------------------

	void CMenuState::deactivate() 
	{		
		// Desactivamos la ventana GUI con el menú y el ratón.
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().hide();
		_menuWindow->deactivate();
		_menuWindow->setVisible(false);
		
		/*
		Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		soundServer->getChannelsPtr()->setPaused("CanalMenu", true);
		*/
		//Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		//soundServer->getEventInstancesPtr()->setPaused("Instancia1", true);
		
		/**/
		
		CApplicationState::deactivate();
	} // deactivate

	//--------------------------------------------------------

	void CMenuState::tick(unsigned int msecs) 
	{
		CApplicationState::tick(msecs);

	} // tick

	//--------------------------------------------------------

	bool CMenuState::keyPressed(GUI::TKey key)
	{
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CMenuState::keyReleased(GUI::TKey key)
	{
		std::string mapName;

		switch(key.keyId)
		{
		case GUI::Key::ESCAPE:
			_app->exitRequest();
			break;
		case GUI::Key::RETURN:

			mapName = _menuWindow->getChild("MapName")->getText().c_str();

			if (!std::regex_match(mapName, std::regex("[a-zA-Z]+.lua"))){
				std::cout << "ERROR!! The entered name does not match the .lua format" << std::endl;
				return false;
			}

			// Intenta cambiar el fichero del mapa a cargar
			if (!_app->setGameStateMap(mapName))
				return false;

			// Pop MenuState
			_app->popState(true);

			// Push GameState
			_app->pushState("game", true);

			// Push PauseState
			_app->pushState("pause", true);

			// Pop PauseState (deactivation)
			_app->popState();

			return true;

			break;
		default:
			return false;
		}
		return true;

	} // keyReleased

	//--------------------------------------------------------
	
	bool CMenuState::mouseMoved(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CMenuState::mousePressed(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mousePressed

	//--------------------------------------------------------


	bool CMenuState::mouseReleased(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseReleased
			
	//--------------------------------------------------------
		
	bool CMenuState::startReleased(const CEGUI::EventArgs& e)
	{

		std::string mapName = _menuWindow->getChild("MapName")->getText().c_str();

		if (!std::regex_match(mapName, std::regex("[a-zA-Z]+.lua"))){
			std::cout << "ERROR!! The entered name does not match the .lua format" << std::endl;
			return false;
		}

		// Intenta cambiar el fichero del mapa a cargar
		if (!_app->setGameStateMap(mapName))
			return false;
	
		// Pop MenuState
		_app->popState(true);

		// Push GameState
		_app->pushState("game", true);

		// Push PauseState
		_app->pushState("pause", true);

		// Pop PauseState (deactivation)
		_app->popState();

		return true;

	} // startReleased
			
	//--------------------------------------------------------

	bool CMenuState::exitReleased(const CEGUI::EventArgs& e)
	{
		_app->exitRequest();
		return true;

	} // exitReleased

	bool CMenuState::optionsReleased(const CEGUI::EventArgs& e)
	{
		_app->pushState("options",true);
		return true;

	} // exitReleased

} // namespace Application

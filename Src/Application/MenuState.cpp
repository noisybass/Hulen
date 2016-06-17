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
#include "LoadingState.h"

#include <CEGUI/CEGUI.h>

#include <regex>

namespace Application {

	CMenuState::~CMenuState()
	{
		_soundResources = nullptr;
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
		_soundResources->createInstance(std::string("MainMenuInstance"), std::string("MainMenuEvent"));
		
		return true;

	} // init

	//--------------------------------------------------------

	void CMenuState::release() 
	{
		_soundResources->deleteInstance(std::string("MainMenuInstance"));

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

		_soundResources->playInstance(std::string("MainMenuInstance"));

	} // activate

	//--------------------------------------------------------

	void CMenuState::deactivate() 
	{		
		// Desactivamos la ventana GUI con el menú y el ratón.
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().hide();
		_menuWindow->deactivate();
		_menuWindow->setVisible(false);
		
		CApplicationState::deactivate();
	} // deactivate

	//--------------------------------------------------------

	void CMenuState::tick(float msecs)
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

			//mapName = _menuWindow->getChild("MapName")->getText().c_str();

			if (!std::regex_match(_mapName, std::regex("[a-zA-Z]+.lua"))){
				std::cout << "ERROR!! The entered name does not match the .lua format" << std::endl;
				return false;
			}

			// Intenta cambiar el fichero del mapa a cargar
			//if (!_app->setGameStateMap(mapName))
				//return false;
			_app->addAction(new CSetGameStateMapAction(_mapName));

			// Pop MenuState
			_app->addAction(new CPopAction(true));

			// Le decimos al estado de loading que la siguiente escena a cargar es la de game
			//_app->setLoadingNextState("game");
			_app->addAction(new CSetLoadingNextState(std::string("game")));

			// Push LoadingState
			_app->addAction(new CPushAction(States::LoadingState, true));

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

		//std::string mapName = _menuWindow->getChild("MapName")->getText().c_str();

		if (!std::regex_match(_mapName, std::regex("[a-zA-Z]+.lua"))){
			std::cout << "ERROR!! The entered name does not match the .lua format" << std::endl;
			return false;
		}

		// Intenta cambiar el fichero del mapa a cargar
		//if (!_app->setGameStateMap(mapName))
			//return false;
		_app->addAction(new CSetGameStateMapAction(_mapName));

		// Pop MenuState
		_app->addAction(new CPopAction(true));

		// Le decimos al estado de loading que la siguiente escena a cargar es la de game
		//_app->setLoadingNextState("game");
		_app->addAction(new CSetLoadingNextState(std::string("game")));

		// Push LoadingState
		_app->addAction(new CPushAction(States::LoadingState, true));

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
		_app->addAction(new CPushAction(States::OptionsState, true, true));
		return true;

	} // exitReleased

} // namespace Application

//---------------------------------------------------------------------------
// PauseState.cpp
//---------------------------------------------------------------------------

/**
@file PauseState.cpp

Contiene la implementación del estado de pausa.

@see Application::CApplicationState
@see Application::CPauseState

@author Daniel Ruiz
@date Abril, 2016
*/

#include "PauseState.h"

#include "GUI/Server.h"
#include "Sounds\Server.h"

#include <CEGUI/CEGUI.h>

namespace Application {

	CPauseState::~CPauseState()
	{
	} // ~CPauseState

	//--------------------------------------------------------

	bool CPauseState::init()
	{
		CApplicationState::init();

		// Cargamos la ventana que muestra la pausa
		_PauseWindow = CEGUI::WindowManager::getSingletonPtr()->loadLayoutFromFile("Pause.layout");

		// Asociamos los botones de la pausa con las funciones que se deben ejecutar.
		_PauseWindow->getChildElement("Resume")->
			subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::SubscriberSlot(&CPauseState::startReleased, this));

		_PauseWindow->getChildElement("Menu")->
			subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::SubscriberSlot(&CPauseState::exitReleased, this));

		// Sonido en el Pause principal
		/*
		Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		soundServer->getSoundsPtr()->loadSound("TemaPrincipal", "Hulen-Textura1.wav", Sounds::Loop_Normal && Sounds::Sound_3D);
		soundServer->getChannelsPtr()->loadChannel("CanalPause", "TemaPrincipal");
		soundServer->getChannelsPtr()->setVolume("CanalPause", 0.3);

		/*
		Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		soundServer->getBanksPtr()->loadBank("Banco1", "Master Bank.bank");
		soundServer->getBanksPtr()->loadBank("Banco2", "Master Bank.strings.bank");
		soundServer->getBanksPtr()->loadBank("Banco3", "Ambiente.bank");
		soundServer->getEventDescriptionsPtr()->loadEventDescription("Evento1", "event:/Ambientes");


		soundServer->getEventInstancesPtr()->loadInstance("Instancia1", "Evento1");
		soundServer->getEventInstancesPtr()->setPaused("Instancia1", false);
		//soundServer->getEventInstancesPtr()->setParameterValue("Instancia1", "RPM", 650);
		soundServer->getEventInstancesPtr()->start("Instancia1");
		*/
		return true;

	} // init

	//--------------------------------------------------------

	void CPauseState::release()
	{

		/*
		Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		soundServer->getChannelsPtr()->stop("CanalPause");
		soundServer->getSoundsPtr()->unloadSound("TemaPrincipal");

		/*
		Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		soundServer->getEventInstancesPtr()->stop("Instancia1");
		*/
		CApplicationState::release();

	} // release

	//--------------------------------------------------------

	void CPauseState::activate()
	{
		CApplicationState::activate();

		// Activamos la ventana que nos muestra la pausa y activamos el ratón.
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().setRootWindow(_PauseWindow);
		_PauseWindow->setVisible(true);
		_PauseWindow->activate();
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().show();

		/*
		Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		soundServer->getChannelsPtr()->setPaused("CanalPause", false);

		Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		soundServer->getEventInstancesPtr()->setPaused("Instancia1", false);
		*/

	} // activate

	//--------------------------------------------------------

	void CPauseState::deactivate()
	{
		// Desactivamos la ventana GUI con la pausa y el ratón.
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().hide();
		_PauseWindow->deactivate();
		_PauseWindow->setVisible(false);
		/*
		Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		soundServer->getChannelsPtr()->setPaused("CanalPause", true);

		Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		soundServer->getEventInstancesPtr()->setPaused("Instancia1", true);
		*/
		/**/

		CApplicationState::deactivate();
	} // deactivate

	//--------------------------------------------------------

	void CPauseState::tick(unsigned int msecs)
	{
		CApplicationState::tick(msecs);

	} // tick

	//--------------------------------------------------------

	bool CPauseState::keyPressed(GUI::TKey key)
	{
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CPauseState::keyReleased(GUI::TKey key)
	{
		switch (key.keyId)
		{
		case GUI::Key::ESCAPE:
			// Pop PauseState
			_app->popState();
			break;
		case GUI::Key::RETURN:
			// Pop PauseState
			_app->popState();
			break;
		default:
			return false;
		}
		return true;

	} // keyReleased

	//--------------------------------------------------------

	bool CPauseState::mouseMoved(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseMoved

	//--------------------------------------------------------

	bool CPauseState::mousePressed(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mousePressed

	//--------------------------------------------------------


	bool CPauseState::mouseReleased(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseReleased

	//--------------------------------------------------------

	bool CPauseState::startReleased(const CEGUI::EventArgs& e)
	{
		_app->popState();
		return true;

	} // startReleased

	//--------------------------------------------------------

	bool CPauseState::exitReleased(const CEGUI::EventArgs& e)
	{
		// Pop PauseState
		_app->popState(true);

		// Pop GameState
		_app->popState(true);

		// Push MenuState
		_app->pushState("menu",true);
		return true;

	} // exitReleased

} // namespace Application

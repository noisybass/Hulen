#include "OptionsState.h"

#include "MenuState.h"
#include <CEGUI\EventArgs.h>
#include <CEGUI\Window.h>
#include <regex>

namespace Application {

	COptionsState::~COptionsState()
	{
	} // ~CMenuState

	//--------------------------------------------------------

	bool COptionsState::init()
	{
		CApplicationState::init();

		// Cargamos la ventana que muestra el menú
		_menuWindow = CEGUI::WindowManager::getSingletonPtr()->loadLayoutFromFile("Options.layout");
		
		// Asociamos los botones del menú con las funciones que se deben ejecutar.
		_menuWindow->getChildElement("Controls")->
			subscribeEvent(CEGUI::PushButton::EventClicked, 
			CEGUI::SubscriberSlot(&COptionsState::controlReleased, this));

		_menuWindow->getChildElement("Back")->
			subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::SubscriberSlot(&COptionsState::backReleased, this));

		_menuWindow->getChildElement("Level1")->
			subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::SubscriberSlot(&COptionsState::levelButtonReleased, this));

		_menuWindow->getChildElement("Level1")->
			subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::SubscriberSlot(&COptionsState::levelButtonReleased, this));

		_menuWindow->getChildElement("Level2")->
			subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::SubscriberSlot(&COptionsState::levelButtonReleased, this));

		_menuWindow->getChildElement("Level3")->
			subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::SubscriberSlot(&COptionsState::levelButtonReleased, this));

		_menuWindow->getChildElement("Level4")->
			subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::SubscriberSlot(&COptionsState::levelButtonReleased, this));

		_menuWindow->getChildElement("Level5")->
			subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::SubscriberSlot(&COptionsState::levelButtonReleased, this));

		_menuWindow->getChildElement("Level6")->
			subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::SubscriberSlot(&COptionsState::levelButtonReleased, this));

		_menuWindow->getChildElement("Level7")->
			subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::SubscriberSlot(&COptionsState::levelButtonReleased, this));

		_menuWindow->getChildElement("Level8")->
			subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::SubscriberSlot(&COptionsState::levelButtonReleased, this));

		_menuWindow->getChildElement("Level9")->
			subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::SubscriberSlot(&COptionsState::levelButtonReleased, this));

		return true;

	} // init

	//--------------------------------------------------------

	void COptionsState::release()
	{

		CApplicationState::release();

	} // release

	//--------------------------------------------------------

	void COptionsState::activate()
	{
		CApplicationState::activate();

		// Activamos la ventana que nos muestra el menú y activamos el ratón.
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().setRootWindow(_menuWindow);
		_menuWindow->setVisible(true);
		_menuWindow->activate();
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().show();

		if (_previousState)
		{
			static_cast<CEGUI::Editbox*>(_menuWindow->getChild("MapName"))->setText(static_cast<CMenuState*>(_previousState)->getMapName());
		}

	} // activate

	//--------------------------------------------------------

	void COptionsState::deactivate()
	{		
		// Desactivamos la ventana GUI con el menú y el ratón.
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().hide();
		_menuWindow->deactivate();
		_menuWindow->setVisible(false);
		
		CApplicationState::deactivate();
	} // deactivate

	//--------------------------------------------------------

	void COptionsState::tick(float msecs)
	{
		CApplicationState::tick(msecs);

	} // tick

	//--------------------------------------------------------

	bool COptionsState::keyPressed(GUI::TKey key)
	{
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool COptionsState::keyReleased(GUI::TKey key)
	{
		switch(key.keyId)
		{
		case GUI::Key::ESCAPE:

			if (_previousState)
				static_cast<CMenuState*>(_previousState)->setMapName(_menuWindow->getChild("MapName")->getText().c_str());

			_app->addAction(new CPopAction());
			break;
		default:
			return false;
		}
		return true;

	} // keyReleased

	//--------------------------------------------------------
	
	bool COptionsState::mouseMoved(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool COptionsState::mousePressed(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mousePressed

	//--------------------------------------------------------


	bool COptionsState::mouseReleased(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseReleased

	bool COptionsState::controlReleased(const CEGUI::EventArgs& e)
	{
		std::string mapName = _menuWindow->getChild("MapName")->getText().c_str();

		if (_previousState)
			static_cast<CMenuState*>(_previousState)->setMapName(mapName);

		_app->addAction(new CPushAction(States::ControlsState, true));

		return true;
	} // controlReleased

	bool COptionsState::backReleased(const CEGUI::EventArgs& e)
	{

		std::string mapName = _menuWindow->getChild("MapName")->getText().c_str();

		if (_previousState)
			static_cast<CMenuState*>(_previousState)->setMapName(mapName);

		_app->addAction(new CPopAction());

		return true;
	} // backReleased

	bool COptionsState::levelButtonReleased(const CEGUI::EventArgs& e)
	{
		
		const CEGUI::WindowEventArgs* args = static_cast<const CEGUI::WindowEventArgs*>(&e);
		std::string name = args->window->getName().c_str();

		if (name == "Level1")
			static_cast<CEGUI::Editbox*>(_menuWindow->getChild("MapName"))->setText("sublevelOne.lua");
		else if (name == "Level2")
			static_cast<CEGUI::Editbox*>(_menuWindow->getChild("MapName"))->setText("sublevelTwo.lua");
		else if (name == "Level3")
			static_cast<CEGUI::Editbox*>(_menuWindow->getChild("MapName"))->setText("sublevelThree.lua");
		else if (name == "Level4")
			static_cast<CEGUI::Editbox*>(_menuWindow->getChild("MapName"))->setText("sublevelFour.lua");
		else if (name == "Level5")
			static_cast<CEGUI::Editbox*>(_menuWindow->getChild("MapName"))->setText("twoSublevelOne.lua");
		else if (name == "Level6")
			static_cast<CEGUI::Editbox*>(_menuWindow->getChild("MapName"))->setText("twoSublevelTwo.lua");
		else if (name == "Level7")
			static_cast<CEGUI::Editbox*>(_menuWindow->getChild("MapName"))->setText("twoSublevelThree.lua");
		else if (name == "Level8")
			static_cast<CEGUI::Editbox*>(_menuWindow->getChild("MapName"))->setText("twoSublevelFour.lua");
		else if (name == "Level9")
			static_cast<CEGUI::Editbox*>(_menuWindow->getChild("MapName"))->setText("twoSublevelFive.lua");

		return true;
	} // levelButtonReleased
	

} // namespace Application

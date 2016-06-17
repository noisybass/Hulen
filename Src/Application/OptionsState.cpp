#include "OptionsState.h"

#include "MenuState.h"
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
	

} // namespace Application

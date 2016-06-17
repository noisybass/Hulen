#include "ControlsState.h"

namespace Application {

	CControlsState::~CControlsState()
	{
	} // ~CMenuState

	//--------------------------------------------------------

	bool CControlsState::init()
	{
		CApplicationState::init();

		// Cargamos la ventana que muestra el menú
		_menuWindow = CEGUI::WindowManager::getSingletonPtr()->loadLayoutFromFile("Controls.layout");

		// Asociamos los botones del menú con las funciones que se deben ejecutar.
		_menuWindow->getChildElement("Back")->
			subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::SubscriberSlot(&CControlsState::backReleased, this));

		return true;

	} // init

	//--------------------------------------------------------

	void CControlsState::release()
	{

		CApplicationState::release();

	} // release

	//--------------------------------------------------------

	void CControlsState::activate()
	{
		CApplicationState::activate();

		// Activamos la ventana que nos muestra el menú y activamos el ratón.
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().setRootWindow(_menuWindow);
		_menuWindow->setVisible(true);
		_menuWindow->activate();
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().show();

	} // activate

	//--------------------------------------------------------

	void CControlsState::deactivate()
	{
		// Desactivamos la ventana GUI con el menú y el ratón.
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().hide();
		_menuWindow->deactivate();
		_menuWindow->setVisible(false);

		CApplicationState::deactivate();
	} // deactivate

	//--------------------------------------------------------

	void CControlsState::tick(float msecs)
	{
		CApplicationState::tick(msecs);

	} // tick

	//--------------------------------------------------------

	bool CControlsState::keyPressed(GUI::TKey key)
	{
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CControlsState::keyReleased(GUI::TKey key)
	{
		switch (key.keyId)
		{
		case GUI::Key::ESCAPE:
			_app->addAction(new CPopAction(true));
			break;
		default:
			return false;
		}
		return true;

	} // keyReleased

	//--------------------------------------------------------

	bool CControlsState::mouseMoved(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseMoved

	//--------------------------------------------------------

	bool CControlsState::mousePressed(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mousePressed

	//--------------------------------------------------------


	bool CControlsState::mouseReleased(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseReleased

	bool CControlsState::backReleased(const CEGUI::EventArgs& e){
		_app->addAction(new CPopAction(true));

		return true;
	} // backReleased

	bool CControlsState::controlsMenu(const CEGUI::EventArgs& e){

		return true;
	} // controlsMenu


} // namespace Application

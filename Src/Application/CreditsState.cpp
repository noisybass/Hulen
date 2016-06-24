#include "CreditsState.h"

namespace Application {

	CCreditsState::~CCreditsState()
	{
	} // ~CMenuState

	//--------------------------------------------------------

	bool CCreditsState::init()
	{
		CApplicationState::init();

		// Cargamos la ventana que muestra el menú
		_menuWindow = CEGUI::WindowManager::getSingletonPtr()->loadLayoutFromFile("Credits.layout");

		// Asociamos los botones del menú con las funciones que se deben ejecutar.
		_menuWindow->getChildElement("Back")->
			subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::SubscriberSlot(&CCreditsState::backReleased, this));

		return true;

	} // init

	//--------------------------------------------------------

	void CCreditsState::release()
	{

		CApplicationState::release();

	} // release

	//--------------------------------------------------------

	void CCreditsState::activate()
	{
		CApplicationState::activate();

		// Activamos la ventana que nos muestra el menú y activamos el ratón.
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().setRootWindow(_menuWindow);
		_menuWindow->setVisible(true);
		_menuWindow->activate();
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().show();

	} // activate

	//--------------------------------------------------------

	void CCreditsState::deactivate()
	{
		// Desactivamos la ventana GUI con el menú y el ratón.
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().hide();
		_menuWindow->deactivate();
		_menuWindow->setVisible(false);

		CApplicationState::deactivate();
	} // deactivate

	//--------------------------------------------------------

	void CCreditsState::tick(float msecs)
	{
		CApplicationState::tick(msecs);

	} // tick

	//--------------------------------------------------------

	bool CCreditsState::keyPressed(GUI::TKey key)
	{
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CCreditsState::keyReleased(GUI::TKey key)
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

	bool CCreditsState::mouseMoved(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseMoved

	//--------------------------------------------------------

	bool CCreditsState::mousePressed(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mousePressed

	//--------------------------------------------------------


	bool CCreditsState::mouseReleased(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseReleased

	bool CCreditsState::backReleased(const CEGUI::EventArgs& e){
		_app->addAction(new CPopAction(true));

		return true;
	} // backReleased

	bool CCreditsState::controlsMenu(const CEGUI::EventArgs& e){

		return true;
	} // controlsMenu


} // namespace Application

//---------------------------------------------------------------------------
// LoadingState.cpp
//---------------------------------------------------------------------------

/**
@file LoadingState.cpp

Contiene la implementación del estado de la pantalla de loading.

@see Application::CApplicationState
@see Application::CLoadingState

@author Daniel Ruiz
@date Abril, 2016
*/

#include "LoadingState.h"

#include "GUI/Server.h"
#include "Sounds\Server.h"

#include <CEGUI/CEGUI.h>

namespace Application {

	CLoadingState::~CLoadingState()
	{
	} // ~CLoadingState

	//--------------------------------------------------------

	bool CLoadingState::init()
	{
		CApplicationState::init();

		// Cargamos la ventana que muestra el menú
		_menuWindow = CEGUI::WindowManager::getSingletonPtr()->loadLayoutFromFile("Loading.layout");

		// Reajustamos flag _isLoading
		_isLoading = false;

		return true;

	} // init

	//--------------------------------------------------------

	void CLoadingState::release()
	{

		CApplicationState::release();

		// Reajustamos flag _isLoading
		_isLoading = false;

	} // release

	//--------------------------------------------------------

	void CLoadingState::activate()
	{
		CApplicationState::activate();

		// Activamos la ventana que nos muestra el menú y activamos el ratón.
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().setRootWindow(_menuWindow);
		_menuWindow->setVisible(true);
		_menuWindow->activate();
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().show();

	} // activate

	//--------------------------------------------------------

	void CLoadingState::deactivate()
	{
		// Desactivamos la ventana GUI con el menú y el ratón.
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().hide();
		_menuWindow->deactivate();
		_menuWindow->setVisible(false);

		CApplicationState::deactivate();
	} // deactivate

	//--------------------------------------------------------

	void CLoadingState::tick(float msecs)
	{
		CApplicationState::tick(msecs);

		if (!_isLoading){
			_isLoading = true;

			// Pop LoadingState
			_app->addAction(new CPopAction());

			if (_nextState == "game"){

				// Push GameState
				_app->addAction(new CPushAction(States::GameState, true));

				// Push PauseState
				_app->addAction(new CPushAction(States::PauseState, true));
			}

			// Pop PauseState (deactivation)
			_app->addAction(new CPopAction());
		}

	} // tick

	//--------------------------------------------------------

	void CLoadingState::setNextState(const std::string & nextState)
	{
		_nextState = nextState;
	} // setNextState

} // namespace Application

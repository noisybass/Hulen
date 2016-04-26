//---------------------------------------------------------------------------
// GaleonApplication.cpp
//---------------------------------------------------------------------------

/**
@file GaleonApplication.cpp

Contiene la implementación de la clase aplicacion para aplicaciones
basadas en Ogre. Esta clase maneja la ejecución de todo el juego.

@see Application::CGaleonApplication
@see Application::C3DApplication

@author David Llansó
@date Septiembre, 2010
*/
#include "GaleonApplication.h"

#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "OptionsState.h"
#include "LoadingState.h"
#include "ExitState.h"
#include "Logic\Events\Event.h"
#include "SoundsResources.h"


namespace Application {

	CGaleonApplication::CGaleonApplication() : C3DApplication()
	{

	} // CGaleonApplication

	//--------------------------------------------------------

	CGaleonApplication::~CGaleonApplication()
	{

	} // ~CGaleonApplication

	//--------------------------------------------------------

	bool CGaleonApplication::init() 
	{
		// Inicializamos la clase de la que heredamos.
		if (!C3DApplication::init())
			return false;

		// Load all sounds
		if (!Application::CSoundsResources::init())
			return false;
		Application::CSoundsResources::loadAll();

		// Creamos los estados. La aplicación se hace responsable de
		// destruirlos.
		addState(States::MenuState, new CMenuState(this));

		addState(States::GameState, new CGameState(this));

		addState(States::PauseState, new CPauseState(this));

		addState(States::OptionsState, new COptionsState(this));

		addState(States::LoadingState, new CLoadingState(this));

		addState(States::ExitState, new CExitState(this));

		if (!pushState(States::MenuState, true))
			return false;

		return true;

	} // init

	//--------------------------------------------------------

	void CGaleonApplication::release()
	{
		// Desactivamos y eliminamos todos los estados.
		releaseAllStates();

		// Unload all sounds
		Application::CSoundsResources::unloadAll();
		Application::CSoundsResources::release();

		C3DApplication::release();

	} // release

} // namespace Application

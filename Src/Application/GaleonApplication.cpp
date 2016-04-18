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
		addState("menu", new CMenuState(this));

		addState("game", new CGameState(this));

		addState("pause", new CPauseState(this));

		addState("options", new COptionsState(this));

		addState("exit", new CExitState(this));

		if(!pushState("menu",true))
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

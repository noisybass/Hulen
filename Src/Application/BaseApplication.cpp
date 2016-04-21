//---------------------------------------------------------------------------
// BaseApplication.cpp
//---------------------------------------------------------------------------

/**
@file BaseApplication.cpp

Contiene la implementación de la clase aplicacion, que maneja la ejecución
de todo el juego.

@see Application::CBaseApplication
@see Application::CApplicationState

@author Marco Antonio Gómez Martín & David Llansó
@date Julio, 2010
*/

#include "BaseApplication.h"
#include "ApplicationState.h"
#include "Clock.h"

#include "Map\MapParser.h"
#include "GameState.h"
#include "LoadingState.h"

#include <assert.h>

namespace Application {

	CBaseApplication *CBaseApplication::_instance = 0;

	CBaseApplication::CBaseApplication() :
		_initialized(false),
		_currentState(nullptr),
		_exit(false),
		_clock(0),
		_reloadState(false)
	{
		assert(!_instance && "No puede crearse más de una aplicación");

		_instance = this;

	} // CBaseApplication

	//--------------------------------------------------------

	CBaseApplication::~CBaseApplication()
	{
		_instance = 0;

	} // ~CBaseApplication

	//--------------------------------------------------------

	bool CBaseApplication::init() 
	{
		assert(!_initialized && "La aplicación ya está inicializada");

		_initialized = true;

		return true;

	} // init

	//--------------------------------------------------------

	void CBaseApplication::release()
	{
		assert(_initialized && "La aplicación no está inicializada");

		// Desactivamos y eliminamos todos los estados.
		releaseAllStates();

		_initialized = false;

	} // release

	//--------------------------------------------------------
	
	void CBaseApplication::releaseAllStates()
	{
		// Desactivamos y liberamos todos los estados que hay en la pila
		while (!_states.empty()){
			CApplicationState* currentState = _states.top();
			currentState->deactivate();
			currentState->release();
			currentState = 0;
			_states.pop();
		}		

		// Eliminamos los estados
		TStateTable::const_iterator it, end;

		for (it = _stateTable.begin(), end = _stateTable.end();
			 it != end; ++it) 
		{
			//it->second->release();
			delete it->second;
		}
		_stateTable.clear();

	} // releaseAllStates

	//--------------------------------------------------------
	
	void CBaseApplication::addState(const States &name,
					   CApplicationState *newState) 
	{
		TStateTable::const_iterator it;

#ifdef _DEBUG
		// Comprobamos que no existe un estado con ese nombre.
		// Otra posibilidad es no hacerlo en Debug, sino siempre,
		// y, en caso de que ya exista, eliminarlo (pues la aplicación
		// acepta la responsabilidad de borrar los estados que contiene).
		// Sin embargo, en ese caso, habría que comprobar que no es
		// el estado actual, ni el estado siguiente al que se espera ir...
		it = _stateTable.find(name);
		assert(it == _stateTable.end());
#endif
		_stateTable[name] = newState;
		//return newState->init();

	} // addState

	//--------------------------------------------------------

	void CBaseApplication::addAction(CStateActions* action){
		_actions.push(action);
	} // addAction

	//--------------------------------------------------------

	void CBaseApplication::executeActions(){
		while (!_actions.empty()){
			CStateActions* temp = _actions.front();
			if (temp->stateAction == StateAction::POP){
				CPopAction* pop = (CPopAction*) temp;
				popState(pop->release);
			}
			else if (temp->stateAction == StateAction::PUSH){
				CPushAction* push = (CPushAction*)temp;
				pushState(push->state, push->init);
			}
			delete temp;
			_actions.pop();
		}
	} // executeActions

	//--------------------------------------------------------

	bool CBaseApplication::pushState(const States &name, bool init)
	{
		// Buscamos el estado.
		TStateTable::const_iterator it;

		it = _stateTable.find(name);

		// Si no hay ningún estado con ese nombre, no hacemos nada
		if (it == _stateTable.end())
			return false;

		// Desactivamos el estado y liberamos si habia un estado en la pila.
		if (!_states.empty())
			_states.top()->deactivate();

		// Inicializamos el estado a cargar si se indica
		if (init)
			it->second->init();

		// Activamos el estado que vamos a meter en la pila
		it->second->activate();

		// Lo insertamos en la pila.
		_states.push(it->second);

		return true;

	} // pushState

	//--------------------------------------------------------

	bool CBaseApplication::popState(bool release)
	{
		// Si no hay ningún elemento, no hacemos nada.
		if (_states.empty())
			return false;

		// Desactivamos el estado.
		_states.top()->deactivate();

		if (release)
			_states.top()->release();

		// Sacamos el estado de la pila
		_states.pop();

		// Activamos el estado que teniamos en la pila si existe
		if (!_states.empty())
			_states.top()->activate();

		return true;
	} // popState

	//--------------------------------------------------------

	void CBaseApplication::reloadState(){

		_reloadState = true;

	} // reloadState

	//--------------------------------------------------------

	bool CBaseApplication::setGameStateMap(const std::string &newStateMapName){

		// Buscamos el estado.
		TStateTable::const_iterator it;

		it = _stateTable.find(States::GameState);

		// Si no hay ningún estado con ese nombre, no hacemos nada
		if (it == _stateTable.end())
			return false;

		return ((CGameState *)it->second)->setMap(newStateMapName);
	} // setGameStateMap

	//--------------------------------------------------------

	bool CBaseApplication::setLoadingNextState(const std::string &loadingNextState){

		// Buscamos el estado.
		TStateTable::const_iterator it;

		it = _stateTable.find(States::LoadingState);

		// Si no hay ningún estado con ese nombre, no hacemos nada.
		if (it == _stateTable.end())
			return false;

		//  Cambiamos la escena a cargar del estado loading.
		((CLoadingState *)it->second)->setNextState(loadingNextState);

		return true;
	} // setLoadingNextState

	//--------------------------------------------------------

	void CBaseApplication::run() 
	{
		assert(_clock && "Asegurate de haber creado un reloj en el init de la clase de tu aplicacion!");

		// Actualizamos una primera vez el tiempo, antes de
		// empezar, para que el primer frame tenga un tiempo
		// de frame razonable.
		_clock->updateTime();

		// Ejecución del bucle principal. Simplemente miramos si
		// tenemos que hacer una transición de estado, y si no hay que
		// hacerla, ejecutamos la vuelta
		while (!exitRequested()) 
		{
			// Recargamos el estado actual
			if (_reloadState){

				_currentState->deactivate();
				_currentState->release();
				_currentState->init();
				_currentState->activate();
				_reloadState = false;
			}

			// Execute the pending actions
			executeActions();

			if (!_currentState ||
				_currentState != _states.top())
				changeState();

			_clock->updateTime();

			tick(_clock->getLastFrameDuration());
		}

	} // run

	//--------------------------------------------------------

	unsigned int CBaseApplication::getAppTime() 
	{
		return _clock->getTime();

	} // getAppTime

	//--------------------------------------------------------

	void CBaseApplication::changeState() 
	{
		// Establecemos el estado actual como la cima de pila.
		_currentState = _states.top();

	} // changeState

	//--------------------------------------------------------

	void CBaseApplication::tick(unsigned int msecs) 
	{
		// Aparentemente esta función es sencilla. Aquí se pueden
		// añadir otras llamadas que sean comunes a todos los estados
		// de todas las aplicaciones.
		// El método es virtual. Si para una aplicación concreta, se
		// identifican cosas comunes a todos los estados, se pueden
		// añadir en la implementación del método de esa aplicación.

		if (_currentState)
			_currentState->tick(msecs);

	} // tick

	//--------------------------------------------------------

	bool CBaseApplication::keyPressed(GUI::TKey key)
	{
		// Avisamos al estado actual de la pulsación.
		if (_currentState)
			return _currentState->keyPressed(key);
		
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CBaseApplication::keyReleased(GUI::TKey key)
	{
		// Avisamos al estado actual del fin de la pulsación.
		if (_currentState)
			return _currentState->keyReleased(key);
		
		return false;

	} // keyReleased

	//--------------------------------------------------------
	
	bool CBaseApplication::mouseMoved(const GUI::CMouseState &mouseState)
	{
		// Avisamos al estado actual del movimiento.
		if (_currentState)
			return _currentState->mouseMoved(mouseState);
		
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CBaseApplication::mousePressed(const GUI::CMouseState &mouseState)
	{
		// Avisamos al estado actual de la pulsación.
		if (_currentState)
			return _currentState->mousePressed(mouseState);
		
		return false;

	} // mousePressed

	//--------------------------------------------------------


	bool CBaseApplication::mouseReleased(const GUI::CMouseState &mouseState)
	{
		// Avisamos al estado actual del fin de la pulsación.
		if (_currentState)
			return _currentState->mouseReleased(mouseState);
		
		return false;

	} // mouseReleased

} // namespace Application

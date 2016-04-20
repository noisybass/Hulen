//---------------------------------------------------------------------------
// LoadingState.h
//---------------------------------------------------------------------------

/**
@file LoadingState.h

Contiene la declaración del estado de menú.

@see Application::CApplicationState
@see Application::CLoadingState

@author Daniel Ruiz
@date Abril, 2016
*/

#ifndef __Application_LoadingState_H
#define __Application_LoadingState_H

#include "ApplicationState.h"
#include "AsyncTask.h"

// Predeclaración de clases para ahorrar tiempo de compilación
namespace Application
{
	class CBaseApplication;
}

namespace CEGUI
{
	class EventArgs;
	class Window;
}

namespace Application
{
	/**
	Como su nombre indica, esta clase es la clase de la pantalla de carga
	del juego. Es muy sencilla y lo único que hace es cargar
	un layout de CEGUI al inicio y activarlo y desactivarlo cuando
	se activa o desactiva el estado (haciéndo visible/invisible también
	el puntero del ratón). También asocia los eventos de los botones
	del menú a las funciones C++ que se deben invocar cuando los botones
	son pulsados.
	<p>
	Este estado es CEGUI dependiente, lo cual no es deseable, la aplicación
	debería ser independiente de las tecnologías usadas.

	@ingroup applicationGroup

	@author David Llansó
	@date Agosto, 2010
	*/
	class CLoadingState : public CApplicationState, public AsyncTaskData, public OnAsyncTaskFinished
	{
	public:
		/**
		Constructor de la clase
		*/
		CLoadingState(CBaseApplication *app) : CApplicationState(app),
			_nextState(""), _asyncTask(NULL) , _isLoadingAysnc(false){}

		/**
		Destructor
		*/
		virtual ~CLoadingState();

		/**
		Función llamada cuando se crea el estado (se "engancha" en la
		aplicación, para que inicialice sus elementos.

		@return true si todo fue bien.
		*/
		virtual bool init();

		/**
		Función llamada cuando se elimina ("desengancha") el
		estado de la aplicación.
		*/
		virtual void release();

		/**
		Función llamada por la aplicación cuando se activa
		el estado.
		*/
		virtual void activate();

		/**
		Función llamada por la aplicación cuando se desactiva
		el estado.
		*/
		virtual void deactivate();

		/**
		Función llamada por la aplicación para que se ejecute
		la funcionalidad del estado.

		@param msecs Número de milisegundos transcurridos desde
		la última llamada (o desde la áctivación del estado, en caso
		de ser la primera vez...).
		*/
		virtual void tick(unsigned int msecs);

		virtual void setNextState(const std::string & nextState);

		// Métodos correspondientes para la carga asíncrona de las tareas.

		virtual void run();

		virtual void onAsyncTaskListener();

	private:

		/**
		Ventana CEGUI que muestra el menú.
		*/
		CEGUI::Window* _menuWindow;

		/**
		Referencia del siguiente estado a cargar.
		*/
		std::string _nextState;

		/*
		Tarea asíncrona que gestiona el estado de Loading.
		*/
		AsyncTask * _asyncTask;

		/*
		Flag que indica si se está realizando la carga asíncrona.
		*/
		bool _isLoadingAysnc;

	}; // CLoadingState

} // namespace Application

#endif //  __Application_LoadingState_H

//---------------------------------------------------------------------------
// AsyncTask.h
//---------------------------------------------------------------------------

/**
@file AsyncTask.h

Contiene la funcionalidad para poder ejecutar tareas asíncronas.

@see Application::CAsyncTask
@see Application::CAsyncTask

@author Daniel Ruiz
@date Abril, 2016
*/

#ifndef __Application_AsyncTask_H
#define __Application_AsyncTask_H

#include <vector>
#include <thread>        

// Predeclaración de clases para ahorrar tiempo de compilación

namespace Application
{

	class AsyncTaskData {

	public:

		virtual void run() = 0;
	};

	class OnAsyncTaskFinished {

	public:

		virtual void onAsyncTaskListener() = 0;
	};

	

	class AsyncTask
	{

	public:

		/**
		Constructor de la clase
		*/
		AsyncTask(AsyncTaskData * asyncTaskData);

		/**
		Destructor de la aplicación
		*/
		virtual ~AsyncTask();

		void attach(OnAsyncTaskFinished * onAsyncTaskFinished);

		void notify();

		void run();


		/**
		Hilo de ejecución que va a ejecutar la tarea asíncrona.
		*/
		std::thread * _thread;

	private:

		void runAsyncData();

		/**
		Tipo de datos lista de OnAsyncTaskFinished. Es un vector de las STL.
		*/
		typedef std::vector<class OnAsyncTaskFinished *> OnAsyncTaskFinishedList;

		/**
		Lista de objetos los cuales van a recibir la notificación cuando acabe la tarea.
		*/
		OnAsyncTaskFinishedList * _onAsyncTaskFinishedList;

		/*
		Objeto que tiene la función que va a ejecutar la tarea asíncrona.
		*/
		AsyncTaskData * _asyncTaskData;


	}; // namespace Application

}
#endif //  __Application_AsyncTask_H
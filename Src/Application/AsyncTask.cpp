//---------------------------------------------------------------------------
// AsyncTask.cpp
//---------------------------------------------------------------------------

/**
@file AsyncTask.cpp

Contiene la implementación de las tareas asíncronas.

@see Application::CAsyncTask

@author Daniel Ruiz
@date Abril, 2016
*/

#include "AsyncTask.h"

// Predeclaración de clases para ahorrar tiempo de compilación
namespace Application
{
	class OnAsyncTaskFinished;
}

namespace Application {



	AsyncTask::AsyncTask(AsyncTaskData * asyncTaskData){
		_asyncTaskData = asyncTaskData;
		_onAsyncTaskFinishedList = new OnAsyncTaskFinishedList();
	}

	AsyncTask::~AsyncTask(){
		delete _onAsyncTaskFinishedList;
		_onAsyncTaskFinishedList = NULL;
		delete _thread;
		_thread = NULL;
	}

	void AsyncTask::attach(OnAsyncTaskFinished * onAsyncTaskFinished){
		_onAsyncTaskFinishedList->push_back(onAsyncTaskFinished);
	}

	void AsyncTask::notify(){
		for (OnAsyncTaskFinishedList::iterator it = _onAsyncTaskFinishedList->begin();
				it != _onAsyncTaskFinishedList->end(); ++it) {
			OnAsyncTaskFinished * on = ((OnAsyncTaskFinished*)*it);
			on->onAsyncTaskListener();
		}

		//delete this;
	}

	void AsyncTask::run(){
		if (!_asyncTaskData == NULL){

			// Creamos el thread
			_thread = new std::thread(&AsyncTask::runAsyncData, this);
		}
	}

	void AsyncTask::runAsyncData(){
		_asyncTaskData->run();

		notify();
	}

} // namespace Application

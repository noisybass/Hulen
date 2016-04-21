//---------------------------------------------------------------------------
// AsyncTask.cpp
//---------------------------------------------------------------------------

/**
@file AsyncTask.cpp

Contiene la implementación de la clase AsyncTask.

@see Application::CAsyncTask

@author Daniel Ruiz
@date Abril, 2016
*/

#include "AsyncTask.h"

namespace Application {

	CAsyncTask::CAsyncTask(IAsyncTaskData * asyncTaskData){
		_asyncTaskData = asyncTaskData;
		_onAsyncTaskFinishedList = new OnAsyncTaskFinishedList();
		_thread = NULL;
	}

	CAsyncTask::~CAsyncTask(){
		delete _onAsyncTaskFinishedList;
		_onAsyncTaskFinishedList = NULL;

		if (_thread != NULL){
			_thread->detach();
			delete _thread;
			_thread = NULL;
		}
	}

	void CAsyncTask::attach(IOnAsyncTaskFinished * onAsyncTaskFinished){
		_onAsyncTaskFinishedList->push_back(onAsyncTaskFinished);
	}

	void CAsyncTask::join(){
		if (_thread != NULL)
			_thread->join();
	}

	void CAsyncTask::run(){
		if (!_asyncTaskData == NULL){
			_thread = new std::thread(&CAsyncTask::runAsyncData, this);
		}
	}

	void CAsyncTask::notify(){
		for (OnAsyncTaskFinishedList::iterator it = _onAsyncTaskFinishedList->begin();
			it != _onAsyncTaskFinishedList->end(); ++it) {
			IOnAsyncTaskFinished * on = ((IOnAsyncTaskFinished*)*it);
			on->onAsyncTaskListener();
		}

		// Tras realizar la AsyncTask, se borra así misma
		this->~CAsyncTask();
	}

	void CAsyncTask::runAsyncData(){
		_asyncTaskData->run();
		notify();
	}

} // CAsyncTask

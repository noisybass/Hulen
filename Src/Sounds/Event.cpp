#include "Sounds\Event.h"
#include "Sounds\Server.h"
#include <assert.h>


namespace Sounds{


	CEvent::CEvent()
	{
		// Obtenemos el sistema de bajo nivel
		_fmod_studio_system = Sounds::CServer::getSingletonPtr()->_fmod_studio_system;

		// Inicializamos la estuctura de datos
		_events = new tEvents();
	}

	CEvent::~CEvent()
	{
		_fmod_studio_system = nullptr;

		delete _events;
	}

	bool CEvent::getEvent(std::string eventName, std::string eventPath)
	{
		FMOD::Studio::EventDescription* eventDescription = nullptr;

		FMOD_RESULT result = _fmod_studio_system->getEvent(eventPath.c_str(), &eventDescription);

		FMOD::Studio::EventInstance* eventInstance = nullptr;
		eventDescription->createInstance(&eventInstance);


		FMOD::Studio::ParameterInstance* rpm = NULL;
		eventInstance->getParameter("RPM", &rpm);
		rpm->setValue(650);

		eventInstance->start();
		/*tEvent *eventDesc = new tEvent;
		eventDesc->_eventDescription = eventDescription;	

		_events->insert({eventName, eventDesc});*/
		
		return result == FMOD_OK;
	}

	
};

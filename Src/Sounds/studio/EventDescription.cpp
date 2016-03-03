#include "Sounds\studio\EventDescription.h"
#include "Sounds\Server.h"
#include <assert.h>


namespace Sounds{


	CEventDescription::CEventDescription()
	{
		// Obtenemos el sistema de bajo nivel
		_fmod_studio_system = Sounds::CServer::getSingletonPtr()->_fmod_studio_system;

		// Inicializamos la estuctura de datos
		_eventDescriptions = new tEventDescription();
	}

	CEventDescription::~CEventDescription()
	{
		_fmod_studio_system = nullptr;

		delete _eventDescriptions;
	}

	bool CEventDescription::loadEventDescription(std::string descriptionName, std::string eventPath)
	{
		assert(_eventDescriptions->find(descriptionName) == _eventDescriptions->end() && "No se puede cargar el mismo evento 2 veces");
		FMOD::Studio::EventDescription* eventDescription = nullptr;

		FMOD_RESULT result = _fmod_studio_system->getEvent(eventPath.c_str(), &eventDescription);
		assert(result == FMOD_OK && "Error al cargar la descripcion del evento. CEventDescription::getEvent");

		_eventDescriptions->insert({ descriptionName, eventDescription });
		
		return result == FMOD_OK;
	}

	FMOD::Studio::EventDescription* CEventDescription::getEventDescription(std::string descriptionName)
	{
		FMOD::Studio::EventDescription* eventDescription = _eventDescriptions->at(descriptionName);
		assert(eventDescription && "No existe el sonido para crear el canal");

		return eventDescription;
	}

	
};

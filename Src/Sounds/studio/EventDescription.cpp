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
		assert(_eventDescriptions->find(descriptionName) == _eventDescriptions->end() && "No se puede cargar el mismo evento 2 veces. Sounds::CEventDescription::loadEventDescription");
		FMOD::Studio::EventDescription* eventDescription = nullptr;

		FMOD_RESULT result = _fmod_studio_system->getEvent(eventPath.c_str(), &eventDescription);
		assert(result == FMOD_OK && "Error al cargar la descripcion del evento. Sounds::CEventDescription::loadEventDescription");

		_eventDescriptions->insert({ descriptionName, eventDescription });
		
		return result == FMOD_OK;
	}

	FMOD::Studio::EventDescription* CEventDescription::getEventDescription(std::string descriptionName)
	{
		FMOD::Studio::EventDescription* eventDescription = _eventDescriptions->at(descriptionName);
		assert(eventDescription && "No existe el descriptor de evento. Sounds::CEventDescription::getEventDescription");

		return eventDescription;
	}

	bool CEventDescription::unloadEventDescription(std::string descriptionName)
	{
		FMOD::Studio::EventDescription* eventDescription = _eventDescriptions->at(descriptionName);
		assert(eventDescription && "No existe el descriptor de evento. Sounds::CEventDescription::unloadEventDescription");

		FMOD_RESULT result = eventDescription->releaseAllInstances();
		assert(result == FMOD_OK && "Error al descargar la descripcion del evento. Sounds::CEventDescription::unloadEventDescription");

		return result == FMOD_OK;
	}
	
};

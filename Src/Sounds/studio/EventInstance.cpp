#include "Sounds\studio\EventInstance.h"
#include "Sounds\Server.h"
#include <assert.h>


namespace Sounds{


	CEventInstance::CEventInstance()
	{
		// Obtenemos el sistema de bajo nivel
		_fmod_studio_system = Sounds::CServer::getSingletonPtr()->_fmod_studio_system;

		// Inicializamos la estuctura de datos
		_eventInstances = new tEventInstance();
	}

	CEventInstance::~CEventInstance()
	{
		_fmod_studio_system = nullptr;

		delete _eventInstances;
	}

	bool CEventInstance::loadInstance(std::string instanceName, std::string descriptionName)
	{
		assert(_eventInstances->find(instanceName) == _eventInstances->end() && "No se pueden crear dos instancias con el mismo nombre. CEventInstance::loadInstance.");
		FMOD::Studio::EventInstance* eventInstance = nullptr;
		FMOD::Studio::EventDescription* eventDescription = 
			CServer::getSingletonPtr()->getEventDescriptionsPtr()->getEventDescription(descriptionName);

		FMOD_RESULT result = eventDescription->createInstance(&eventInstance);
		assert(result == FMOD_OK && "Error al crear la instancia. CEventInstance::createInstance");

		_eventInstances->insert({instanceName, eventInstance});

		return result == FMOD_OK;
	}

	bool CEventInstance::start(std::string instanceName)
	{
		FMOD::Studio::EventInstance* eventInstance = _eventInstances->at(instanceName);
		assert(eventInstance && "No existe la instancia especificado. CEventInstance::start");

		FMOD_RESULT result = eventInstance->start();
		assert(result == FMOD_OK && "Error al iniciar la instancia. CEventInstance::start");

		return result == FMOD_OK;
	}

	bool CEventInstance::stop(std::string instanceName)
	{
		FMOD::Studio::EventInstance* eventInstance = _eventInstances->at(instanceName);
		assert(eventInstance && "No existe la instancia para poder eliminarla. CEventInstance::stop");

		FMOD_RESULT result = eventInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE);
		assert(result == FMOD_OK && "Error al parar la instancia. CEventInstance::stop");

		if (result == FMOD_OK){
			_eventInstances->erase(instanceName);
		}

		return result == FMOD_OK;
	}

	bool CEventInstance::setPaused(std::string instanceName, bool paused)
	{
		FMOD::Studio::EventInstance* eventInstance = _eventInstances->at(instanceName);
		assert(eventInstance && "No existe la instancia para poder pausarla. CEventInstance::setPaused");

		FMOD_RESULT result = eventInstance->setPaused(paused);
		assert(result == FMOD_OK && "Error al pausar la instancia. CEventInstance::setPaused");

		return result == FMOD_OK;
	}

	float CEventInstance::getParameter(std::string instanceName, std::string parameterName)
	{
		FMOD::Studio::EventInstance* eventInstance = _eventInstances->at(instanceName);
		assert(eventInstance && "No existe la instancia especificado. CEventInstance::getParameter");

		FMOD::Studio::ParameterInstance* parameterInstance;
		FMOD_RESULT result = eventInstance->getParameter(parameterName.c_str(), &parameterInstance);
		assert(result == FMOD_OK && "Error al obtener el parametro de la instancia. CEventInstance::getParameter");
		
		float value;
		FMOD_RESULT resultValue = parameterInstance->getValue(&value);
		assert(resultValue == FMOD_OK && "Error al obtener el valor del parametro de la instancia. CEventInstance::getParameter");
		
		return value;
	}

	bool CEventInstance::setParameterValue(std::string instanceName, std::string parameterName, float parameterValue)
	{
		FMOD::Studio::EventInstance* eventInstance = _eventInstances->at(instanceName);
		assert(eventInstance && "No existe la instancia especificado. CEventInstance::setParameterValue");

		FMOD::Studio::ParameterInstance* parameterInstance;
		FMOD_RESULT result = eventInstance->getParameter(parameterName.c_str(), &parameterInstance);
		assert(result == FMOD_OK && "Error al obtener el parametro de la instancia. CEventInstance::setParameterValue");

		FMOD_RESULT resultValue = parameterInstance->setValue(parameterValue);
		assert(resultValue == FMOD_OK && "Error al establecer el valor del parametro de la instancia. CEventInstance::setParameterValue");

		return result == FMOD_OK && resultValue == FMOD_OK;
	}
	
};

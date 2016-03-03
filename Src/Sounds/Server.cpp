#include "Sounds\Server.h"
#include <assert.h>
#include "fmod\lowlevel\fmod.hpp"

namespace Sounds{

	// Única instancia del servidor
	CServer *CServer::_instance = nullptr;
	std::string CServer::_soundPath = "media/sounds/";

	CServer::CServer() : _fmod_studio_system(nullptr)
	{

		_instance = this;

		// Creamos el objeto del Studio System
		FMOD_RESULT result = FMOD::Studio::System::create(&_fmod_studio_system);
		assert(result == FMOD_OK && "No se ha creado el objeto Studio System correctamente. Sounds::CServer::CServer");

		// Inicializamos FMOD studio.
		// esto tambien inicializa FMOD low-level
		result = _fmod_studio_system->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);
		assert(result == FMOD_OK && "No se ha inicializado el objeto Studio System correctamente. Sounds::CServer::CServer");

		// Obtenemos el sistema de bajo nivel
		_fmod_studio_system->getLowLevelSystem(&_fmod_lowLevel_system);

		// Inicializamos los manejadores
		_sounds = new Sounds::CSound();
		_channels = new Sounds::CChannel();
		_banks = new Sounds::CBank();
		_eventDescriptions = new Sounds::CEventDescription();
		_eventInstances = new Sounds::CEventInstance();

	}

	CServer::~CServer()
	{
		// Liberamos fmod
		FMOD_RESULT result = _fmod_studio_system->release();
		assert(result == FMOD_OK && "FMOD no se ha liberado correctamente. Sounds::CServer::~CServer");
		_fmod_studio_system = nullptr;
		_fmod_lowLevel_system = nullptr;

		// Liberamos los manejadores
		delete _sounds;
		delete _channels;
		delete _banks;
		delete _eventDescriptions;
		delete _eventInstances;
		_sounds = nullptr;
		_channels = nullptr;
		_banks = nullptr;
		_eventDescriptions = nullptr;
		_eventInstances = nullptr;

		// Reseteamos la instancia de la clase
		assert(_instance);
		_instance = nullptr;
	}

	bool CServer::Init()
	{
		assert(!_instance && "Segunda inicialización de Sounds::CServer no permitida!. Sounds::CServer::Init");

		if (!_instance){
			new CServer();
		}
		return true;
	}

	void CServer::Release()
	{
		
		if (_instance){
			delete _instance;
			_instance = nullptr;
		}

	}

	bool CServer::tick(unsigned int msecs)
	{
		
		// LLamamos al tick de fmod
		_fmod_studio_system->update();

		return true;
	}

};

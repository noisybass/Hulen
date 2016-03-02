#include "Sounds\Server.h"
#include <assert.h>
#include "fmod\lowlevel\fmod.hpp"

namespace Sounds{

	// Única instancia del servidor
	CServer *CServer::_instance = nullptr;

	CServer::CServer() : _fmod_system(nullptr), _soundPath("media/sounds/")
	{

		// Creamos el objeto del Studio System
		FMOD_RESULT result = FMOD::Studio::System::create(&_fmod_system);

		assert(result == FMOD_OK && "No se ha creado el objeto Studio System correctamente");

		// Inicializamos FMOD studio.
		// esto tambien inicializa FMOD low-level
		result = _fmod_system->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);

		assert(result == FMOD_OK && "No se ha inicializado el objeto Studio System correctamente");

		// Obtenemos el sistema de bajo nivel
		_fmod_system->getLowLevelSystem(&_fmod_lowLevel_system);

		// Inicializamos las estructuras de datos
		_sounds = new tSounds();
		_channels = new tChannels();

	}

	CServer::~CServer()
	{
		// Liberamos fmod
		FMOD_RESULT result = _fmod_system->release();
		assert(result == FMOD_OK && "FMOD no se ha liberado correctamente");

		// Liberamos las estructuras de datos
		delete _sounds;
		delete _channels;

		_sounds = nullptr;
		_channels = nullptr;

		// Reseteamos la instancia de la clase
		assert(_instance);
		_instance = nullptr;
	}

	bool CServer::Init()
	{
		assert(!_instance && "Segunda inicialización de Sounds::CServer no permitida!");

		if (!_instance){
			_instance = new CServer();
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
		
		// LLamamos al tick del Studio System
		_fmod_system->update();

		return true;
	}

	bool CServer::loadSound(std::string name, std::string fileSound)
	{
		std::string file = _soundPath + fileSound;
		FMOD::Sound* sound;

		FMOD_RESULT result = _fmod_lowLevel_system->createSound(file.c_str(), FMOD_DEFAULT, 0, &sound);
		
		_sounds->insert({ name, sound });

		return result == FMOD_OK;
	}

	bool CServer::loadChannel(std::string soundName, std::string channelName, bool sleep)
	{
		FMOD::Channel* channel;
		
		FMOD::Sound* sound = _sounds->at(soundName);

		assert(sound && "No existe el sonido para crear el canal");

		FMOD_RESULT result = _fmod_lowLevel_system->playSound(sound, 0, sleep, &channel);

		_channels->insert({ channelName, channel });

		return result == FMOD_OK;
	}

	bool CServer::setVolume(std::string channelName, float volume)
	{
		FMOD::Channel* channel = _channels->at(channelName);

		assert(channel && "No existe el canal para poder ajustar el volumen");

		FMOD_RESULT result = channel->setVolume(volume);

		return result == FMOD_OK;
	}

	bool CServer::stop(std::string channelName)
	{
		FMOD::Channel* channel = _channels->at(channelName);

		assert(channel && "No existe el canal para poder eliminarlo");

		FMOD_RESULT result = channel->stop();

		if (result == FMOD_OK){
			_channels->erase(channelName);
		}

		return result == FMOD_OK;
	}

	bool CServer::setPaused(std::string channelName, bool paused)
	{
		FMOD::Channel* channel = _channels->at(channelName);

		assert(channel && "No existe el canal para poder cambiar el estado del canal");

		FMOD_RESULT result = channel->setPaused(paused);

		return result == FMOD_OK;
	}

};

#include "Sounds\Sound.h"
#include "Sounds\Server.h"
#include <assert.h>


namespace Sounds{


	CSound::CSound() 
	{
		// Obtenemos el sistema de bajo nivel
		_fmod_lowLevel_system = Sounds::CServer::getSingletonPtr()->_fmod_lowLevel_system;

		// Inicializamos la estuctura de datos
		_sounds = new tSounds();
	}

	CSound::~CSound()
	{
		_fmod_lowLevel_system = nullptr;

		delete _sounds;
	}

	bool CSound::loadSound(std::string name, std::string fileSound)
	{

		assert(_sounds->find(name) == _sounds->end() && "No se puede cargar el mismo sonido 2 veces");

		std::string file = CServer::getSoundsPath() + fileSound;
		FMOD::Sound* sound;

		FMOD_RESULT result = _fmod_lowLevel_system->createSound(file.c_str(), FMOD_DEFAULT, 0, &sound);

		_sounds->insert({ name, sound });

		return result == FMOD_OK;
	}

	FMOD::Sound* CSound::getSound(std::string name)
	{
		FMOD::Sound* sound = _sounds->at(name);

		assert(sound && "No existe el sonido para crear el canal");

		return sound;
	}

};

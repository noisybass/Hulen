#include "Sounds\Sound.h"
#include "Sounds\Server.h"
#include <assert.h>


namespace Sounds{


	CSound::CSound() 
	{
		// Obtenemos el sistema de bajo nivel
		_fmod_lowLevel_system = Sounds::CServer::getSingletonPtr()->_fmod_lowLevel_system;
	}

	CSound::~CSound()
	{
		_fmod_lowLevel_system = nullptr;
	}

	bool CSound::loadSound(std::string name, std::string fileSound)
	{

		assert(_sounds->find(name) == _sounds->end() && "No se puede cargar el mismo sonido 2 veces");

		std::string file = Sounds::CServer::getSingletonPtr()->_soundPath + fileSound;
		FMOD::Sound* sound;

		FMOD_RESULT result = _fmod_lowLevel_system->createSound(file.c_str(), FMOD_DEFAULT, 0, &sound);

		_sounds->insert({ name, sound });

		return result == FMOD_OK;
	}

};

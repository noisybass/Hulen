#include "Sounds\lowLevel\Sound.h"
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

	bool CSound::loadSound(std::string name, std::string fileSound, FMOD_MODE mode, bool streaming)
	{

		assert(_sounds->find(name) == _sounds->end() && "No se puede cargar el mismo sonido 2 veces. Sounds::CSound::loadSound");

		std::string file = CServer::getSoundsPath() + fileSound;
		FMOD::Sound* sound;
		FMOD_RESULT result;

		// Lo cargamos en memoria
		if (!streaming){
			result = _fmod_lowLevel_system->createSound(file.c_str(), mode, 0, &sound);
			assert(result == FMOD_OK && "Error al cargar el sonido en memoria. Sounds::CSound::loadSound");
		}
		// Hacemos la carga del audio dinamicamente
		else{
			result = _fmod_lowLevel_system->createStream(file.c_str(), mode, 0, &sound);
			assert(result == FMOD_OK && "Error al cargar el sonido con streaming. Sounds::CSound::loadSound");
		}
		
		_sounds->insert({ name, sound });

		return result == FMOD_OK;
	}

	bool CSound::unloadSound(std::string name)
	{
		FMOD::Sound* sound = _sounds->at(name);
		assert(sound && "No existe el sonido especificado. Sounds::CSound::unloadSound");

		FMOD_RESULT result = sound->release();
		assert(result == FMOD_OK && "Error al eliminar el sonido. Sounds::CSound::unloadSound");

		if (result == FMOD_OK)
			_sounds->erase(name);

		return result == FMOD_OK;
	}

	FMOD::Sound* CSound::getSound(std::string name)
	{
		FMOD::Sound* sound = _sounds->at(name);
		assert(sound && "No existe el sonido especificado. Sounds::CSound::getSound");

		return sound;
	}

};
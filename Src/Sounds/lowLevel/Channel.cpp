#include "Sounds\lowLevel\Channel.h"
#include "Sounds\Server.h"
#include <assert.h>

namespace Sounds{


	CChannel::CChannel()
	{
		// Obtenemos el sistema de bajo nivel
		_fmod_lowLevel_system = Sounds::CServer::getSingletonPtr()->_fmod_lowLevel_system;

		// Inicializamos la estuctura de datos
		_channels = new tChannels();
	}

	CChannel::~CChannel()
	{
		_fmod_lowLevel_system = nullptr;

		delete _channels;
	}

	bool CChannel::loadChannel(std::string channelName, std::string soundName, bool sleep)
	{
		assert(_channels->find(channelName) == _channels->end() && "No se puede cargar dos canales con el mismo nombre. Sounds::CChannel::loadChannel");

		FMOD::Channel* channel;
		FMOD::Sound* sound = CServer::getSingletonPtr()->_sounds->getSound(soundName);

		FMOD_RESULT result = _fmod_lowLevel_system->playSound(sound, 0, sleep, &channel);
		assert(result == FMOD_OK && "Error al cargar el canal. Sounds::CChannel::loadChannel");

		_channels->insert({ channelName, channel });

		return result == FMOD_OK;
	}

	bool CChannel::loadChannelAndDestroy(std::string soundName, float volume)
	{
		FMOD::Channel* channel;
		FMOD::Sound* sound = CServer::getSingletonPtr()->_sounds->getSound(soundName);

		FMOD_RESULT result = _fmod_lowLevel_system->playSound(sound, 0, false, &channel);
		assert(result == FMOD_OK && "Error al cargar el canal. Sounds::CChannel::loadChannelAndDestroy");

		FMOD_RESULT result1 = channel->setVolume(volume);
		assert(result == FMOD_OK && "Error al ajustar el volumen del canal. Sounds::CChannel::loadChannelAndDestroy");

		return result == FMOD_OK && result1 == FMOD_OK;
	}

	bool CChannel::setVolume(std::string channelName, float volume)
	{
		FMOD::Channel* channel = _channels->at(channelName);
		assert(channel && "No existe el canal para poder ajustar el volumen. Sounds::CChannel::setVolume");

		FMOD_RESULT result = channel->setVolume(volume);
		assert(result == FMOD_OK && "Error al ajustar el volumen del canal. Sounds::CChannel::setVolume");

		return result == FMOD_OK;
	}

	bool CChannel::stop(std::string channelName)
	{
		FMOD::Channel* channel = _channels->at(channelName);
		assert(channel && "No existe el canal para poder eliminarlo. Sounds::CChannel::stop");

		FMOD_RESULT result = channel->stop();
		assert(result == FMOD_OK && "Error al parar el canal. Sounds::CChannel::stop");

		if (result == FMOD_OK){
			_channels->erase(channelName);
		}

		return result == FMOD_OK;
	}

	bool CChannel::setPaused(std::string channelName, bool paused)
	{
		FMOD::Channel* channel = _channels->at(channelName);
		assert(channel && "No existe el canal para poder cambiar el estado del canal. Sounds::CChannel::setPaused");

		FMOD_RESULT result = channel->setPaused(paused);
		assert(result == FMOD_OK && "Error al pausar el canal. Sounds::CChannel::setPaused");

		return result == FMOD_OK;
	}

};

#include "Sounds\Channel.h"
#include "Sounds\Server.h"
#include <assert.h>

namespace Sounds{


	CChannel::CChannel()
	{
		// Obtenemos el sistema de bajo nivel
		_fmod_lowLevel_system = Sounds::CServer::getSingletonPtr()->_fmod_lowLevel_system;
	}

	CChannel::~CChannel()
	{
		_fmod_lowLevel_system = nullptr;
	}

	bool CServer::loadChannel(std::string soundName, std::string channelName, bool sleep)
	{

		assert(_channels->find(channelName) == _channels->end() && "No se puede cargar dos canales con el mismo nombre");

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

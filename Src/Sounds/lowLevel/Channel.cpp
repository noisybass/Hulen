#include "Sounds\lowLevel\Channel.h"
#include "Sounds\Server.h"
#include <assert.h>
#include <iostream>
namespace Sounds{


	CChannel::CChannel()
	{
		// Obtenemos el sistema de bajo nivel
		_fmod_lowLevel_system = Sounds::CServer::getSingletonPtr()->_fmod_lowLevel_system;

		// Inicializamos la estuctura de datos
		_channels = new tChannels();
		_channelSounds = new std::unordered_map<std::string, std::string>();

	} // CChannel

	CChannel::~CChannel()
	{
		_fmod_lowLevel_system = nullptr;

		delete _channels;
		delete _channelSounds;
	} // ~CChannel

	bool CChannel::loadChannel(std::string &channelName, std::string &soundName, bool sleep)
	{
		assert(_channels->find(channelName) == _channels->end() && "No se puede cargar dos canales con el mismo nombre. Sounds::CChannel::loadChannel");

		FMOD::Channel* channel;
		FMOD::Sound* sound = CServer::getSingletonPtr()->_sounds->getSound(soundName);
		_channelSounds->insert({channelName, soundName});

		FMOD_RESULT result = _fmod_lowLevel_system->playSound(sound, 0, sleep, &channel);
		assert(result == FMOD_OK && "Error al cargar el canal. Sounds::CChannel::loadChannel");

		_channels->insert({ channelName, channel });

		return result == FMOD_OK;
	} // loadChannel

	bool CChannel::playChannelAndDestroy(std::string &channelName)
	{
		assert(_channels->find(channelName) != _channels->end() && "No existe dicho canal. Sounds::CChannel::playChannel");
		
		FMOD::Channel* channel = _channels->at(channelName);
		FMOD::Sound* sound = CServer::getSingletonPtr()->_sounds->getSound(_channelSounds->at(channelName));
		
		float volume;
		channel->getVolume(&volume);

		float pitch;
		channel->getPitch(&pitch);

		FMOD_VECTOR position;
		FMOD_VECTOR velocity;
		channel->get3DAttributes(&position, &velocity);


		return loadChannelAndDestroy(_channelSounds->at(channelName), &volume, &pitch, &position, &velocity);
	} // playChannel

	void CChannel::copyChannelAttributes(FMOD::Channel* channelTo, FMOD::Channel* channelFrom)
	{
		float volume;
		float pitch;
		FMOD_VECTOR position;
		FMOD_VECTOR velocity;

		channelFrom->getVolume(&volume);
		channelTo->setVolume(volume);

		channelFrom->getPitch(&pitch);
		channelTo->setVolume(pitch);

		channelFrom->get3DAttributes(&position, &velocity);
		channelTo->set3DAttributes(&position, &velocity);

	} // copyChannelAttributes

	bool CChannel::loadChannelAndDestroy(std::string &soundName, float *volume, float *pitch, FMOD_VECTOR *position, FMOD_VECTOR *velocity)
	{
		FMOD::Channel* channel;
		FMOD::Sound* sound = CServer::getSingletonPtr()->_sounds->getSound(soundName);

		FMOD_RESULT result = _fmod_lowLevel_system->playSound(sound, 0, false, &channel);
		assert(result == FMOD_OK && "Error al cargar el canal. Sounds::CChannel::loadChannelAndDestroy");
		
		FMOD_RESULT result1 = FMOD_OK;
		FMOD_RESULT result2 = FMOD_OK;
		FMOD_RESULT result3 = FMOD_OK;

		if (volume != nullptr)
		{
			result1 = channel->setVolume(*volume);
			assert(result1 == FMOD_OK && "Error al ajustar el volumen del canal. Sounds::CChannel::loadChannelAndDestroy");
		}
		
		if (pitch != nullptr)
		{
			result2 = channel->setPitch(*pitch);
			assert(result2 == FMOD_OK && "Error al ajustar el pitch del canal. Sounds::CChannel::loadChannelAndDestroy");
		}

		if (position != nullptr || velocity != nullptr)
		{
			result3 = channel->set3DAttributes(position, velocity);
			assert(result3 == FMOD_OK && "Error al ajustar el pitch del canal. Sounds::CChannel::loadChannelAndDestroy");
		}

		return result == FMOD_OK && result1 == FMOD_OK && result2 == FMOD_OK && result3 == FMOD_OK;
	} // loadChannelAndDestroy

	bool CChannel::setVolume(std::string &channelName, float volume)
	{
		FMOD::Channel* channel = _channels->at(channelName);
		assert(channel && "No existe el canal para poder ajustar el volumen. Sounds::CChannel::setVolume");

		FMOD_RESULT result = channel->setVolume(volume);
		assert(result == FMOD_OK && "Error al ajustar el volumen del canal. Sounds::CChannel::setVolume");

		return result == FMOD_OK;
	} // setVolume

	bool CChannel::stop(std::string &channelName)
	{
		FMOD::Channel* channel = _channels->at(channelName);
		assert(channel && "No existe el canal para poder eliminarlo. Sounds::CChannel::stop");

		FMOD_RESULT result = channel->stop();
		assert(result == FMOD_OK && "Error al parar el canal. Sounds::CChannel::stop");

		if (result == FMOD_OK){
			_channels->erase(channelName);
		}

		return result == FMOD_OK;
	} // stop

	bool CChannel::setPaused(std::string &channelName, bool paused)
	{
		FMOD::Channel* channel = _channels->at(channelName);
		assert(channel && "No existe el canal para poder cambiar el estado del canal. Sounds::CChannel::setPaused");

		FMOD_RESULT result = channel->setPaused(paused);
		assert(result == FMOD_OK && "Error al pausar el canal. Sounds::CChannel::setPaused");

		return result == FMOD_OK;
	} // setPaused

	bool CChannel::getPaused(std::string &channelName)
	{
		FMOD::Channel* channel = _channels->at(channelName);
		assert(channel && "No existe el canal para poder obtener el estado del canal. Sounds::CChannel::getPaused");

		bool paused;
		FMOD_RESULT result = channel->getPaused(&paused);
		assert(result == FMOD_OK && "Error al obtener el estado del canal. Sounds::CChannel::getPaused");

		return paused;
	} // getPaused

	bool CChannel::setPitch(std::string &channelName, float pitch)
	{
		FMOD::Channel* channel = _channels->at(channelName);
		assert(channel && "No existe el canal para poder cambiar el pitch del canal. Sounds::CChannel::setPitch");

		FMOD_RESULT result = channel->setPitch(pitch);
		assert(result == FMOD_OK && "Error al establecer el pitch. Sounds::CChannel::setPitch");

		return result == FMOD_OK;
	} // setPitch

	bool CChannel::set3DAttributes(std::string &channelName, FMOD_VECTOR &position, FMOD_VECTOR &velocity)
	{

		FMOD::Channel* channel = _channels->at(channelName);
		assert(channel && "No existe el canal para poder cambiar los atributos 3d del canal. Sounds::CChannel::set3DAttributes");
		
		FMOD_RESULT result = channel->set3DAttributes(&position, &velocity);
		assert(result == FMOD_OK && "Error al establecer los atributos 3d del canal. Sounds::CChannel::set3DAttributes");

		return result == FMOD_OK;
	} // set3DAttributes

	bool CChannel::isLoop(std::string &channelName)
	{
		FMOD::Channel* channel = _channels->at(channelName);
		assert(channel && "No existe el canal comprobar si es un loop. Sounds::CChannel::isLoop");

		FMOD_MODE mode;
		FMOD_RESULT result = channel->getMode(&mode);

		return mode & SoundMode::Loop_Normal;
	} // isLoop
};

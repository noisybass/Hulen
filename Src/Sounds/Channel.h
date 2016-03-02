#ifndef SOUNDS_CHANNEL_H
#define SOUNDS_CHANNEL_H

#include <unordered_map>

namespace Sounds{

	class CChannel{

	public:

		/**
		Constructor de la clase.
		*/
		CChannel();

		/**
		Destructor de la clase.
		*/
		~CChannel();

		/**
		Establecemos un canal con un sonido que ya ha sido cargado previamente.

		@params soundName nombre del sonido que queremos cargar en el canal.
		@params channelName nombre de canal.
		@params sleep indica si el canal reproduce o no la cancion nada más cargar el canal,
		por defecto la canción no se reproduce.

		@return Valor booleano indicando si todo fue bien
		*/
		bool loadChannel(std::string soundName, std::string channelName, bool sleep = true);

		/**
		Asigna un volumen al canal especificado.

		@params channelName nombre del canal
		@params volume Volumen que queremos que tenga nuestro canal, los valores estan
		comprendidos entre 0 y 1.

		@return Valor booleano indicando si todo fue bien
		*/
		bool setVolume(std::string channelName, float volume);

		/**
		Nos deshacemos del canal para que fmod pueda reutilizarlo para
		asignarlo a otro canal. Por lo tanto llamaremos a este metodo cuando
		no querramos utilizar más un canal.

		@params channelName nombre del canal

		@return Valor booleano indicando si todo fue bien
		*/
		bool stop(std::string channelName);

		/**
		Detiene o continua la reproduccion del canal especificado.

		@params channelName nombre del canal.
		@params paused Valor booleano que indica si queremos detener la
		reproducción del canal o no.

		@return Valor booleano indicando si todo fue bien
		*/
		bool setPaused(std::string channelName, bool paused);
		
	
	private:

		// Instancia de low level
		FMOD::System* _fmod_lowLevel_system;

		typedef std::unordered_map<std::string, FMOD::Channel*> tChannels;
		tChannels *_channels;

	}; // class CChannel

} // namespace Sounds
#endif SOUNDS_CHANNEL_H

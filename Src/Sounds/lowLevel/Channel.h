#ifndef SOUNDS_CHANNEL_H
#define SOUNDS_CHANNEL_H

#include <unordered_map>
#include "fmod\lowlevel\fmod.hpp"

namespace Sounds{

	/**
	Para poder reproducir un sonido, tenemos que crearnos un canal para 
	poder reproducir este. Además de reproducir el sonido, los canales 
	pueden alterar atributos de estos, como por ejemplo alterar el pitch
	el volumen, la posición (si nuestro sonido es 3D) etc...

	@see Sounds::CSound para crear un sonido.
	*/
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
		bool loadChannel(std::string &channelName, std::string &soundName, bool sleep = true);

		/**
		Reproducimos el canal que hemos creado previamente.

		@params channelName nombre de canal.

		@return Valor booleano indicando si todo fue bien
		*/
		bool playChannelAndDestroy(std::string &channelName);

		/**
		Dejamos que FMOD se encargue de manejar los canales, por lo tanto creamos un 
		canal y FMOD cuando el vea necesario lo borrara.

		@params soundName nombre del sonido que queremos cargar en el canal.
		@params volume volumen del sonido que cargamos.

		@return Valor booleano indicando si todo fue bien
		*/
		bool loadChannelAndDestroy(std::string &soundName, float *volume, float *pitch, FMOD_VECTOR *position, FMOD_VECTOR *velocity);

		/**
		Asigna un volumen al canal especificado.

		@params channelName nombre del canal
		@params volume Volumen que queremos que tenga nuestro canal, los valores estan
		comprendidos entre 0 y 1.

		@return Valor booleano indicando si todo fue bien
		*/
		bool setVolume(std::string &channelName, float volume);

		/**
		Nos deshacemos del canal para que fmod pueda reutilizarlo para
		asignarlo a otro canal. Por lo tanto llamaremos a este metodo cuando
		no querramos utilizar más un canal.

		@params channelName nombre del canal

		@return Valor booleano indicando si todo fue bien
		*/
		bool stop(std::string &channelName);

		/**
		Detiene o continua la reproduccion del canal especificado.

		@params channelName nombre del canal.
		@params paused Valor booleano que indica si queremos detener la
		reproducción del canal o no.

		@return Valor booleano indicando si todo fue bien
		*/
		bool setPaused(std::string &channelName, bool paused);

		/**
		Devuelve si la reproducción esta en pausa o no.

		@params channelName nombre del canal.

		@return si la reproducción esta en pausa o no.
		*/
		bool getPaused(std::string &channelName);

		/**
		Escala la frecuencia con el valor del pitch.

		@params channelName nombre del canal.
		@params pitch valor del pitch.

		@return Valor booleano indicando si todo fue bien
		*/
		bool setPitch(std::string &channelName, float pitch);

		/**
		Establece una posicion y una velocidad al canal

		@params channelName nombre del canal.
		@params position posición del canal.
		@params velocity velocidad del canal.

		@return Valor booleano indicando si todo fue bien
		*/
		bool set3DAttributes(std::string &channelName, FMOD_VECTOR &position, FMOD_VECTOR &velocity);

		/**
		Devuelve si el sonido es un loop o no.

		@params channelName nombre del canal.

		@return si el sonido es un loop o no.
		*/
		bool isLoop(std::string &channelName);
	
	private:

		void copyChannelAttributes(FMOD::Channel* channelTo, FMOD::Channel* channelFrom);

		// Instancia de low level
		FMOD::System* _fmod_lowLevel_system;

		typedef std::unordered_map<std::string, FMOD::Channel*> tChannels;
		tChannels *_channels;

		std::unordered_map<std::string, std::string>* _channelSounds;

	}; // class CChannel

} // namespace Sounds
#endif SOUNDS_CHANNEL_H

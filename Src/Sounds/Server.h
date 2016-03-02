#ifndef SOUNDS_SERVER_H
#define SOUNDS_SERVER_H

#include "fmod\studio\fmod_studio.hpp"
#include <string>
#include <unordered_map>

namespace Sounds{

	class CServer{

	public:
	
		/**
		Devuelve la única instancia de la clase.

		@return Puntero al servidor físico.
		*/
		static CServer *getSingletonPtr() { return _instance; }

		/**
		Inicializa el servidor de la musica. Esta operación sólo es necesario realizarla
		una vez durante la inicialización de la aplicación.

		@return Devuelve false si no se ha podido inicializar.
		*/
		static bool Init();

		/**
		Libera el servidor de la musica. Debe llamarse al finalizar la aplicación.
		*/
		static void Release();

		/**
		Actualiza la musica.

		@param secs Millisegundos transcurridos desde la última actualización.
		@return Valor booleano indicando si todo fue bien.
		*/
		bool tick(unsigned int msecs);

		/**
		Cargamos un fichero de musica desde el servidor de bajo nivel
		de fmod. 

		@params name Nombre que recibe el sonido al que podremos referirnos
		más tarde para cambiar sus propiedades en los canales. Tambien de esta
		manera podremos reutilizar el sonido para cargarlo en diferentes canales.
		@params fileSound ruta del fichero de musica a cargar. Fmod se encarga 
		de diferenciar el tipo de archivo que es (mp3, wav, ogg etc..).

		@return Valor booleano indicando si todo fue bien
		*/
		bool loadSound(std::string name, std::string fileSound);

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

		/**
		Constructor de la clase.
		*/
		CServer();

		/**
		Destructor de la clase.
		*/
		virtual ~CServer();

		// Instancia única de la clase.
		static CServer *_instance;

		// Instancia de Studio System
		FMOD::Studio::System* _fmod_system;

		// Instancia de low level
		FMOD::System* _fmod_lowLevel_system;

		// Ruta de donde se encuentran los ficheros de audio.
		std::string _soundPath;

		typedef std::unordered_map<std::string, FMOD::Sound*> tSounds;
		typedef std::unordered_map<std::string, FMOD::Channel*> tChannels;

		tSounds *_sounds;
		tChannels *_channels;

	};

}


#endif SOUNDS_SERVER_H

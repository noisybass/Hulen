#ifndef SOUNDS_SERVER_H
#define SOUNDS_SERVER_H

#include "fmod\studio\fmod_studio.hpp"
#include <string>
#include <unordered_map>
#include "Sounds\Sound.h"
#include "Sounds\Channel.h"

namespace Sounds{

	class CServer{

	public:

		/**
		Devuelve la única instancia de la clase.

		@return Puntero al servidor físico.
		*/
		static CServer* getSingletonPtr() { return _instance; }

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
		Devuelve la instancia al manejador de sonidos,
		que es quien carga los sonidos en memoria.

		@return Puntero al manejador de sonidos.
		*/
		CSound* getSoundsPtr() { return _sounds; }

		/**
		Devuelve la instancia del manejador de canales,
		en el cual se reproduciran los sonidos y podremos cambiar
		parametros como la posicion del sonido, el pitch etc...

		@return Puntero al manejador de canales.
		*/
		CChannel* getChannelsPtr() { return _channels; }

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

		friend class Sounds::CSound;
		friend class Sounds::CChannel;

		Sounds::CSound* _sounds;
		Sounds::CChannel* _channels;

	};

}


#endif SOUNDS_SERVER_H
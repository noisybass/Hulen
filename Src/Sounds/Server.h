#ifndef SOUNDS_SERVER_H
#define SOUNDS_SERVER_H

// std
#include <string>
#include <unordered_map>

// Fmod
#include "fmod\studio\fmod_studio.hpp"

// lowLevel
#include "Sounds\lowLevel\Sound.h"
#include "Sounds\lowlevel\Channel.h"

// Studio
#include "Sounds\studio\Bank.h"
#include "Sounds\studio\EventDescription.h"
#include "Sounds\studio\EventInstance.h"

namespace Sounds{

	/**
	Servidor que controla todo lo relacionado con los sonidos en 
	la aplicación. Para ello utilizamos la libreria FMOD que nos 
	falicita mucho el trabajo.

	A la hora de trabajar con FMOD tenemos dos maneras de interactuar:

		* FMOD Studio: Esta parte de la libreria se encarga de crear los 
		sonidos previamente diseñados desde la aplicación de escritorio
		de fmod. La información nos llegara a partir de bancos (ficheros
		.bank). Los bancos además contienen más información además de lo 
		que son los sonidos, esto se trata de los eventos, con los eventos
		podremos simular alteraciones o cambios de musica dependiendo de lo 
		que pase en nuestro juego. Basicamente es una manera facil para
		que los programadores y los diseñadores de sonido se comuniquen.
	
		* FMOD Low Level: Básicamente es cargar archivos de audio directamente
		desde código (mp3, ogg, wav etc...). De esta manera el programador se encarga
		de todo y no hace falta para nada el uso de la aplicacion de escritorio
		para poder cargar audio y reproducirlo. 
	*/
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
		Devuelve la ruta donde se encuentran los archivos de audio
		*/
		static std::string const getSoundsPath() { return _soundPath; }

		/**
		Actualiza la musica.

		@param secs Millisegundos transcurridos desde la última actualización.
		@return Valor booleano indicando si todo fue bien.
		*/
		bool tick(float msecs);

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

		/**
		Devuelve la instancia del manejador de bancos,
		que contiene los metadatos de los eventos y los sonidos utilizados.

		@return Puntero al manejador de bancos.
		*/
		CBank* getBanksPtr(){ return _banks; }

		/**
		Devuelve la instancia del manejador de descriptores de evento.

		@return Puntero al manejador de descriptores de evento.
		*/
		CEventDescription* getEventDescriptionsPtr() { return _eventDescriptions; }

		/**
		Devuelve la instancia del manejador de las instancias de evento.

		@return Puntero al manejador de las instancias de evento.
		*/
		CEventInstance* getEventInstancesPtr() { return _eventInstances; }

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

		// Ruta de donde se encuentran los ficheros de audio.
		static std::string _soundPath;

		// Instancia de Studio System
		FMOD::Studio::System* _fmod_studio_system;

		// Instancia de low level
		FMOD::System* _fmod_lowLevel_system;

		// Clases Amigas
		friend class Sounds::CSound;
		friend class Sounds::CChannel;
		friend class Sounds::CBank;
		friend class Sounds::CEventDescription;
		friend class Sounds::CEventInstance;

		// Manejadores
		Sounds::CSound* _sounds;
		Sounds::CChannel* _channels;
		Sounds::CBank* _banks;
		Sounds::CEventDescription* _eventDescriptions;
		Sounds::CEventInstance* _eventInstances;

	}; // class CServer

} // namespace Sounds
#endif SOUNDS_SERVER_H
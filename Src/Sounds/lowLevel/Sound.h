#ifndef SOUNDS_SOUND_H
#define SOUNDS_SOUND_H

#include <unordered_map>
#include "fmod\lowlevel\fmod.hpp"

namespace Sounds{

	/**
	Modos para inicializar el audio
	*/
	enum SoundMode {
		Default = FMOD_DEFAULT,
		Loop_Off = FMOD_LOOP_OFF,
		Loop_Normal = FMOD_LOOP_NORMAL,
		Loop_Bidi = FMOD_LOOP_BIDI,
		Sound_2D = FMOD_2D,
		Sound_3D = FMOD_3D,
		CreateStream = FMOD_CREATESTREAM,
		CreateSample = FMOD_CREATESAMPLE,
		CreateCompressedSample = FMOD_CREATECOMPRESSEDSAMPLE,
		OpenUser = FMOD_OPENUSER,
		OpenMemory = FMOD_OPENMEMORY,
		OpenMemoryPoint = FMOD_OPENMEMORY_POINT,
		OpenRaw = FMOD_OPENRAW,
		OpenOnly = FMOD_OPENONLY,
		AccurateTime = FMOD_ACCURATETIME,
		MPEG_Search = FMOD_MPEGSEARCH,
		NonBlocking = FMOD_NONBLOCKING,
		Unique = FMOD_UNIQUE,
		Sound_3D_HeadRelative = FMOD_3D_HEADRELATIVE,
		Sound_3D_WorldRelative = FMOD_3D_WORLDRELATIVE,
		Sound_3D_InverseRollOff = FMOD_3D_INVERSEROLLOFF,
		Sound_3D_LinearRollOff = FMOD_3D_LINEARROLLOFF,
		Sound_3D_LinearSquareRollOff = FMOD_3D_LINEARSQUAREROLLOFF,
		Sound_3D_InverseTaperedRollOff = FMOD_3D_INVERSETAPEREDROLLOFF,
		Sound_3D_CustomRollOff = FMOD_3D_CUSTOMROLLOFF,
		Sound_3D_IgnoreGeometry = FMOD_3D_IGNOREGEOMETRY,
		IgnoreTags = FMOD_IGNORETAGS,
		LowMem = FMOD_LOWMEM,
		LoadSecondaryRAM = FMOD_LOADSECONDARYRAM,
		PlayFromStart = FMOD_VIRTUAL_PLAYFROMSTART,
	};

	/**
	Esta clase controla todos los sonidos que se han cargado en fmod.
	Estos sonidos pueden ser utilizados varias veces al crear diferentes canales.

	@see Sounds::CChannel para crear un canal.
	*/
	class CSound{

	public:

		/**
		Constructor de la clase.
		*/
		CSound();

		/**
		Destructor de la clase.
		*/
		~CSound();

		/**
		Cargamos un fichero de musica desde el servidor de bajo nivel
		de fmod. 

		@params name Nombre que recibe el sonido al que podremos referirnos
		más tarde para cambiar sus propiedades en los canales. Tambien de esta
		manera podremos reutilizar el sonido para cargarlo en diferentes canales.
		@params fileSound ruta del fichero de musica a cargar. Fmod se encarga 
		de diferenciar el tipo de archivo que es (mp3, wav, ogg etc..).
		@params mode Con esto asignamos el modo con el que queremos iniciar 
		nuestro audio, para ello utilizar Sounds::SoundMode

		OJO!! Por defecto fmod intentará cargar y descomprimir el sonido entero en 
		memoria! usar "streaming = true" para abrirlo y reproducirlo en tiempo real.

		@return Valor booleano indicando si todo fue bien
		*/
		bool loadSound(std::string name, std::string fileSound, FMOD_MODE mode, bool streaming = false);

		/**
		Descarga el sonido que hemos cargado previamente.

		@params name nombre del sonido que queremos descargar

		@return Valor booleano indicando si todo fue bien
		*/
		bool unloadSound(std::string name);

		/**
		Nos devuelve el sonido si ha sido previamente cargado.

		@params name Nombre del sonido a cargar.
		@return el sonido
		*/
		FMOD::Sound* getSound(std::string name);
	
	private:

		// Instancia de low level
		FMOD::System* _fmod_lowLevel_system;

		typedef std::unordered_map<std::string, FMOD::Sound*> tSounds;
		tSounds *_sounds;

	}; // class CSound

} // namespace Sounds
#endif SOUNDS_SOUND_H

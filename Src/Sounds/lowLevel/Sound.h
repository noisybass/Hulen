#ifndef SOUNDS_SOUND_H
#define SOUNDS_SOUND_H

#include <unordered_map>
#include "fmod\lowlevel\fmod.hpp"

namespace Sounds{

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

		OJO!! Por defecto fmod intentará cargar y descomprimir el sonido entero en 
		memoria! usar "streaming = true" para abrirlo y reproducirlo en tiempo real.

		@return Valor booleano indicando si todo fue bien
		*/
		bool loadSound(std::string name, std::string fileSound, bool streaming = false);

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

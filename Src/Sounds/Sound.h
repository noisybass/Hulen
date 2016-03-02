#ifndef SOUNDS_SOUND_H
#define SOUNDS_SOUND_H

#include <unordered_map>
#include "fmod\lowlevel\fmod.hpp"

namespace Sounds{

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
		memoria! usar el siguiente metodo "##Introducir metodo" para abrirlo
		y reproducirlo en tiempo real.

		@return Valor booleano indicando si todo fue bien
		*/
		bool loadSound(std::string name, std::string fileSound);

		FMOD::Sound* getSound(std::string name);
	
	private:

		// Instancia de low level
		FMOD::System* _fmod_lowLevel_system;

		typedef std::unordered_map<std::string, FMOD::Sound*> tSounds;
		tSounds *_sounds;

	}; // class CSound

} // namespace Sounds
#endif SOUNDS_SOUND_H

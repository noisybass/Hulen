#ifndef SOUNDS_BANK_H
#define SOUNDS_BANK_H

#include <unordered_map>
#include "fmod\studio\fmod_studio.hpp"

namespace Sounds{

	/**
	Los bancos se encargan de inicializar los .bank que hemos
	obtenido de la aplicacion de escritorio de fmod. Por lo tanto
	si queremos reproducir los sonidos que nuestro diseñador de 
	sonidos a realizado con la aplicacion deberemos primero cargar
	un banco.
	
	Posteriormente tendremos que cargar los descriptores de evento y las
	instancias de evento. Para saber más mirar en la doc de las otras clases.

	@see CEventDescription para cargar los descriptores de evento.
	@see CEventInstance para cargar las instancias de evento.
	*/
	class CBank{

	public:

		/**
		Constructor de la clase.
		*/
		CBank();

		/**
		Destructor de la clase.
		*/
		~CBank();

		/**
		Al cargar el banco cargaremos todos los metadatos, que contienen
		informacion sobre todos los eventos, parametros, y otros datos 
		necesarios para los eventos asociados con ese banco.

		@params bankName nombre del banco que queremos cargar.
		@params fileName nombre del fichero.

		@return Valor booleano indicando si todo fue bien
		*/
		bool loadBank(std::string bankName, std::string fileName);

		/**
		Esto destruira todos los objetos creados desde el banco,
		descargar todos los sample data dentro del banco, y invalidar
		todos los manejadores del API del banco.

		@params bankName nombre del banco a descargar.

		@return Valor booleano indicando si todo fue bien
		*/
		bool unloadBank(std::string bankName);

		/**
		Obtiene el banco a traves de su nombre.

		@params bankName nombre de banco

		@return Valor Puntero al banco pedido.
		*/
		FMOD::Studio::Bank* getBank(std::string bankName);
	
	private:

		// Instancia de fmod studio
		FMOD::Studio::System* _fmod_studio_system;

		typedef std::unordered_map<std::string, FMOD::Studio::Bank*> tBanks;
		tBanks *_banks;

	}; // class CBank

} // namespace Sounds
#endif SOUNDS_BANK_H

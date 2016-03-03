#ifndef SOUNDS_EVENTDESCRIPTION_H
#define SOUNDS_EVENTDESCRIPTION_H

#include <unordered_map>
#include "fmod\studio\fmod_studio.hpp"

namespace Sounds{

	/**
	
	*/
	class CEventDescription{

	public:

		/**
		Constructor de la clase.
		*/
		CEventDescription();

		/**
		Destructor de la clase.
		*/
		~CEventDescription();

		/**
		Permite cargar eventos a traves de su ruta para despues utilizarlo en
		la instancia del evento.

		@params descriptionName Nombre del descriptor de evento.
		@params eventPath Ruta del evento a cargar. (Creo que la ruta se sabe a traves de
		la aplicación de escritorio de fmod)

		@return si la aplicacion fue bien.
		*/
		bool loadEventDescription(std::string descriptionName, std::string eventPath);

		/**
		Obtiene el descriptor del evento a traves de su nombre.

		@params descriptionName nombre del descriptor de evento.

		@return Puntero al descriptor de evento deseado.
		*/
		FMOD::Studio::EventDescription* getEventDescription(std::string descriptionName);

		/**
		Elimina el descriptor de evento que queremos

		OJO!!! Al eliminar el descriptor de evento eliminamos
		todas las instancias que se han creado a partir de ese descriptor.

		@params descriptionName Nombre del descriptor.

		@return si todo fue bien.
		*/
		bool unloadEventDescription(std::string descriptionName);
	
	private:

		// Instancia de fmod studio
		FMOD::Studio::System* _fmod_studio_system;

		typedef std::unordered_map<std::string, FMOD::Studio::EventDescription*> tEventDescription;
		tEventDescription* _eventDescriptions;

	}; // class CEventDescription

} // namespace Sounds
#endif SOUNDS_EVENTDESCRIPTION_H
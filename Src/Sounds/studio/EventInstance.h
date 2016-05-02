#ifndef SOUNDS_EVENTINSTANCE_H
#define SOUNDS_EVENTINSTANCE_H

#include <unordered_map>
#include "fmod\studio\fmod_studio.hpp"

namespace Sounds{

	/**
	Esta clase es la que se encarga de reproducir los audios
	que han sido diseñados con fmod. a parte de reproducir el audio
	podremos acceder a los parametros que los diseñadores han puesto
	en fmod y jugar con ellos para otorgar distintas sensaciones con 
	el audio.
	*/
	class CEventInstance{

	public:

		/**
		Constructor de la clase.
		*/
		CEventInstance();

		/**
		Destructor de la clase.
		*/
		~CEventInstance();

		/**
		Cargamos una instancia de un descriptor de evento. Para ejecutarla 
		utilizar el metodo Start despues de cargarla.

		@params instanceName nombre de la instancia
		@params descriptionName nombre del descriptor de evento.

		@return si todo fue bien.
		*/
		bool loadInstance(std::string instanceName, std::string descriptionName);

		/**
		Empezamos a reproducir.

		@params instanceName nombre de la instancia

		@return si todo fue bien.
		*/
		bool start(std::string instanceName);

		/**
		Paramos y eliminamos la instancia creada.

		@params instanceName nombre de la instancia

		@return si todo fue bien.
		*/
		bool stop(std::string instanceName);

		/**
		Pausar o despausar el audio.

		@params instanceName nombre de la instancia
		@params paused booleano para pausar o despausar el audio

		@return si todo fue bien.
		*/
		bool setPaused(std::string instanceName, bool paused);

		/**
		Obtener el parametro a traves de un nombre.

		@params instanceName nombre de la instancia
		@params parameterName nombre del parametro del que queremos 
		devolver el valor. (Parametro creado en fmod de escritorio)

		@return el valor deseado.
		*/
		float getParameter(std::string instanceName, std::string parameterName);

		/**
		Establecer un valor a un parametro

		@params instanceName nombre de la instancia
		@params parameterName nombre del parametro del que queremos
		establecer el valor. (Parametro creado en fmod de escritorio)
		@params parameterValue valor del parametro.

		@return si todo fue bien.
		*/
		bool setParameterValue(std::string instanceName, std::string parameterName, float parameterValue);

		/**
		Establece el volumen de la instancia.

		@params instanceName nombre de la instancia.
		@params volume volumen a estabecer entre 0 y 1. 0 = silencio, 1 = full volume.

		@return si todo fue bien.
		*/
		bool setVolume(std::string instanceName, float volume);
	
	private:

		// Instancia de fmod studio
		FMOD::Studio::System* _fmod_studio_system;

		typedef std::unordered_map<std::string, FMOD::Studio::EventInstance*> tEventInstance;
		tEventInstance* _eventInstances;

	}; // class CEventInstance

} // namespace Sounds
#endif SOUNDS_EVENTINSTANCE_H

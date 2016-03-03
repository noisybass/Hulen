#ifndef SOUNDS_EVENTINSTANCE_H
#define SOUNDS_EVENTINSTANCE_H

#include <unordered_map>
#include "fmod\studio\fmod_studio.hpp"

namespace Sounds{

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

		bool loadInstance(std::string instanceName, std::string descriptionName);

		bool start(std::string instanceName);

		bool stop(std::string instanceName);

		bool setPaused(std::string instanceName, bool paused);

		float getParameter(std::string instanceName, std::string parameterName);

		bool setParameterValue(std::string instanceName, std::string parameterName, float parameterValue);
	
	private:

		// Instancia de fmod studio
		FMOD::Studio::System* _fmod_studio_system;

		typedef std::unordered_map<std::string, FMOD::Studio::EventInstance*> tEventInstance;
		tEventInstance* _eventInstances;

	}; // class CEventInstance

} // namespace Sounds
#endif SOUNDS_EVENTINSTANCE_H

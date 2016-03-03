#ifndef SOUNDS_EVENTDESCRIPTION_H
#define SOUNDS_EVENTDESCRIPTION_H

#include <unordered_map>
#include "fmod\studio\fmod_studio.hpp"

namespace Sounds{

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

		bool loadEventDescription(std::string descriptionName, std::string eventPath);

		FMOD::Studio::EventDescription* getEventDescription(std::string descriptionName);
	
	private:

		// Instancia de fmod studio
		FMOD::Studio::System* _fmod_studio_system;

		typedef std::unordered_map<std::string, FMOD::Studio::EventDescription*> tEventDescription;
		tEventDescription* _eventDescriptions;

	}; // class CEventDescription

} // namespace Sounds
#endif SOUNDS_EVENTDESCRIPTION_H

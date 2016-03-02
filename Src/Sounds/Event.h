#ifndef SOUNDS_EVENT_H
#define SOUNDS_EVENT_H

#include <unordered_map>
#include "fmod\studio\fmod_studio.hpp"

namespace Sounds{

	class CEvent{

	public:

		/**
		Constructor de la clase.
		*/
		CEvent();

		/**
		Destructor de la clase.
		*/
		~CEvent();

		bool getEvent(std::string eventName, std::string eventPath);

		//bool createInstance(std::string eventName);
	
	private:

		// Instancia de fmod studio
		FMOD::Studio::System* _fmod_studio_system;

		typedef struct tEvent{
			FMOD::Studio::EventDescription* _eventDescription;
			FMOD::Studio::EventInstance* _eventInstance;
		};

		typedef std::unordered_map<std::string, tEvent*> tEvents;
		tEvents* _events;

	}; // class CEvent

} // namespace Sounds
#endif SOUNDS_EVENT_H

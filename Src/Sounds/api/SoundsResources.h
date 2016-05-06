#ifndef SOUNDS_RESOURCES_H
#define SOUNDS_RESOURCES_H

#include <string>
#include "Sounds\Server.h"

namespace Sounds 
{
	
	class CSoundsResources
	{
	public:
		
		// Constructor and Destructor
		CSoundsResources();
		virtual ~CSoundsResources();

		// Instances (For fmod studio audio "things exported from editor")
		static void createInstance(std::string instanceName, std::string descriptionName, bool paused = true);
		static void deleteInstance(std::string instanceName);
		static void playInstance(std::string instanceName);
		static void pauseInstance(std::string instanceName);
		static void setInstanceParameterValue(std::string instanceName, std::string parameterName, float parameterValue);
		static void setInstanceVolume(std::string instanceName, float volume);

		// Sounds (For fmod low level ".mp3, .wav etc...")
		static void createSound(std::string channelName, std::string soundName, bool paused = true);
		static void deleteSound(std::string channelName);
		static void playSound(std::string channelName);
		static void pauseSound(std::string channelName);
		static void setSoundVolume(std::string channelName, float volume);
		static void playAndDestroySound(std::string soundName, float volume);

		// Sounds Resources
		static bool init();
		static void release();
		static CSoundsResources *getSingletonPtr() { return _instance; }

		// Global sound
		static void loadAll();
		static void unloadAll();

	private:

		// Main Menu
		static void loadMainMenu();
		static void unloadMainMenu();

		// Prisoner
		static void loadPrisoner();
		static void unloadPrisoner();

	protected:

		static CSoundsResources* _instance;
		static Sounds::CServer* _soundServer;
	}; // SoundsResources

} // namespace Application

#endif //  SOUNDS_RESOURCES_H

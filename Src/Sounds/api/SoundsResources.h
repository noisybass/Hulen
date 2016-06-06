#ifndef SOUNDS_RESOURCES_H
#define SOUNDS_RESOURCES_H

#include <string>
#include "Sounds\Server.h"
#include "BaseSubsystems/Math.h"

namespace Sounds 
{
	
	class CSoundsResources
	{
	public:
		
		// Constructor and Destructor
		CSoundsResources();
		~CSoundsResources();

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
		static bool getPausedSound(std::string channelName);
		static void setSoundPitch(std::string channelName, float pitch);
		static void setSoundVolume(std::string channelName, float volume);
		static void playAndDestroySound(std::string soundName, float volume);
		static void setPositionAndVelocity(std::string channelName, Vector3 position, Vector3 velocity = Vector3::ZERO);

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

		// Objects
		static void loadObjects();
		static void unloadObjects();

		// Prisoner
		static void loadPrisoner();
		static void unloadPrisoner();

		// Centaur
		static void loadCentaur();
		static void unloadCentaur();

	protected:

		static CSoundsResources* _instance;
		static Sounds::CServer* _soundServer;
	}; // SoundsResources

} // namespace Application

#endif //  SOUNDS_RESOURCES_H

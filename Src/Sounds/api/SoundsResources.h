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
		

		//
		// Constructor and Destructor
		//-----------

		CSoundsResources();
		~CSoundsResources();


		//
		// Instances (For fmod studio audio "things exported from editor")
		//-----------

		/**
		Load an instance from fmod studio. The instance can start playing automaticaly or
		paused to play it in another moment. The default value is paused.

		@instanceName create a name for the new instance.
		@descriptionName name loaded in fmod studio.
		@paused indicates if the sound starts paused or not.
		*/
		static void createInstance(std::string &instanceName, std::string &descriptionName, bool paused = true);
		
		/**
		Delete an instance created before.

		@instanceName name of the instance.
		*/
		static void deleteInstance(std::string &instanceName);
		
		/**
		Play an instance. The sound starts where you paused before.

		TIP: In this moment play an instance means unpaused the sound. I think
		that only will work with loop sounds. If We want to play only a short sound
		we will have to do more logic.

		@instanceName name of the instance.
		*/
		static void playInstance(std::string &instanceName);

		/**
		Pause and instance.

		@instanceName name of the instance.
		*/
		static void pauseInstance(std::string &instanceName);

		/**
		Set a parameter defined in fmod studio.

		@instanceName name of the instance.
		*/
		static void setInstanceParameterValue(std::string &instanceName, std::string &parameterName, float parameterValue);
		
		/**
		Set the volume of the instance.

		@instanceName name of the instance.
		@volume volume to set.
		*/
		static void setInstanceVolume(std::string &instanceName, float volume);


		//
		// Sounds (For fmod low level ".mp3, .wav etc...")
		//-----------

		/**
		Load a channel from fmod low level system. The channel can start playing automaticaly or
		paused to play it in another moment. The default value is paused.

		@channelName create a name for the new channel.
		@soundName the sound to reproduce, it will be loaded before in fmod low level system.
		@paused indicates if the sound starts paused or not.
		*/
		static void createSound(std::string &channelName, std::string &soundName, bool paused = true);

		/**
		Delete the channel created before.

		@channelName name of the channel.
		*/
		static void deleteSound(std::string &channelName);

		/**
		Play a channel.
		There are two types of sounds that you can play.
			* Loopeable sounds
			* No loopeable sounds
		When you call "playSound" with a loopeable sound this only unpaused
		the sound and play the sound in the moment when you paused it
		By the other side, if you have a no loopeable sound, this create a new channel
		(with the attributes set to your old channel) and play it from the begining of the audio.

		@channelName name of the channel.
		*/
		static void playSound(std::string &channelName);

		/**
		Pause a channel.

		@channelName name of the channel.
		*/
		static void pauseSound(std::string &channelName);

		/**
		Get if the sound is paused or not.

		@channelName name of the channel.

		@return a boolean if the sound is paused or not.
		*/
		static bool getPausedSound(std::string &channelName);

		/**
		Set the pitch (frequency of the sound) of the channel.

		@channelName name of the channel.
		@pitch pitch to set.
		*/
		static void setSoundPitch(std::string &channelName, float pitch);

		/**
		Set the volume of the channel.

		@channelName name of the channel.
		@volume volume to set.
		*/
		static void setSoundVolume(std::string &channelName, float volume);

		/**
		Play a sound without control channels.
		This values are considered like null and not considered when
		setting attributes to the channel.
			* volume    --> 0
			* pitch     --> 0
			* position  --> Vector3(0,0,0)
			* velocity  --> Vector3(0,0,0)

		TIP: The position is done only for Hulen levels that its width are 60 and its height are 34
			* Width  (-30 --- 30)
			* Height (-17 --- 17) 

		@soundName name of the sound to play.
		@volume volume of the sound.
		@pitch pitch of the sound.
		@position 3d position of the sound.
		@velocity velocity of the sound.
		*/
		static void playAndDestroySound(std::string &soundName, float volume, float pitch, Vector3 &position, Vector3 &velocity);
		
		/**
		Set the 3d attributes to the channel.

		@channelName name of the channel.
		@position 3d position of the channel.
		@velocity velocity of the channel.
		*/
		static void setPositionAndVelocity(std::string &channelName, Vector3 &position, Vector3 &velocity);


		//
		// Sounds Resources
		//-----------

		/**
		Init SoundResources class
		*/
		static bool init();

		/**
		Release SoundResources class
		*/
		static void release();

		/**
		Get the singleton of SoundResources class
		*/
		static CSoundsResources *getSingletonPtr() { return _instance; }


		//
		// Global sound
		//-----------

		/**
		Load all sounds, fmod studio and low level system.
		*/
		static void loadAll();

		/**
		Unload all sounds, fmod studio and low level system.
		*/
		static void unloadAll();

	private:


		//
		// Main Menu
		//-----------

		static void loadMainMenu();
		static void unloadMainMenu();


		//
		// Objects
		//-----------

		static void loadObjects();
		static void unloadObjects();


		//
		// Prisoner
		//-----------

		static void loadPrisoner();
		static void unloadPrisoner();


		//
		// Centaur
		//-----------

		static void loadCentaur();
		static void unloadCentaur();

	protected:

		static CSoundsResources* _instance;
		static Sounds::CServer* _soundServer;
	}; // SoundsResources

} // namespace Application

#endif //  SOUNDS_RESOURCES_H

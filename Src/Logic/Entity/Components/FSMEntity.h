#ifndef LOGIC_FSM_ENTITY_H
#define LOGIC_FSM_ENTITY_H

#include "Logic/Entity/Component.h"
#include "BaseSubsystems/FSMAgent.h"

namespace Logic
{
	class CFSMEntity : public IComponent
	{
		DEC_FACTORY(CFSMEntity);

		AI::FSMAgent*  _agent;

	public:

		CFSMEntity();

		~CFSMEntity();

		bool spawn(const std::string& name, CEntity *entity, CMap *map, const Map::CEntity *entityInfo) override;

		void tick(float msecs) override;

		template<typename T>
		T getValue(const std::string& id) const { return _agent->getValue<T>(id); }

		template<typename T>
		void setValue(const std::string& id, const T& value) { _agent->setValue<T>(id, value);}

		void setAnimation(const std::string& animationName, bool loop, bool nextAnimation) { _agent->setAnimation(animationName, loop, nextAnimation); }

		// Instances (For fmod studio audio "things exported from editor")
		void createInstance(std::string instanceName, std::string descriptionName, bool paused){ _agent->createInstance(instanceName, descriptionName, paused); }
		void deleteInstance(std::string instanceName){ _agent->deleteInstance(instanceName); }
		void playInstance(std::string instanceName){ _agent->playInstance(instanceName); }
		void pauseInstance(std::string instanceName){ _agent->pauseInstance(instanceName); }
		void setInstanceParameterValue(std::string instanceName, std::string parameterName, float parameterValue){ _agent->setInstanceParameterValue(instanceName, parameterName, parameterValue); }
		void setInstanceVolume(std::string instanceName, float volume){ _agent->setInstanceVolume(instanceName, volume); }

		// Sounds (For fmod low level ".mp3, .wav etc...")
		void createSound(std::string channelName, std::string soundName, bool paused){ _agent->createSound(channelName, soundName, paused); }
		void deleteSound(std::string channelName){ _agent->deleteSound(channelName); }
		void playSound(std::string channelName){ _agent->playSound(channelName); }
		void pauseSound(std::string channelName){ _agent->pauseSound(channelName); }
		void setSoundVolume(std::string channelName, float volume){ _agent->setSoundVolume(channelName, volume); }
		void playAndDestroySound(std::string soundName, float volume){ _agent->playAndDestroySound(soundName, volume); }

	private:
		void setAnimationNames(const Map::CEntity *entityInfo);

	}; // class CFSMEntity

	REG_FACTORY(CFSMEntity);

} // namespace Logic

#endif // LOGIC_FSM_ENTITY_H
#ifndef AI_FSM_AGENT_H
#define AI_FSM_AGENT_H

#include "BaseSubsystems/FSM.h"
#include "Logic/Entity/Entity.h"

#include <unordered_map>

#include <boost/variant/variant.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/get.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>
#include "Sounds\api\SoundsResources.h"
namespace AI
{

	typedef boost::variant<bool, float, std::string> TAgentValue;

	typedef struct
	{

		std::unordered_map<std::string, TAgentValue> _values;

		template<typename T>
		T getValue(const std::string& id) const
		{
			return boost::get<T>(_values.at(id));
		}

		template<typename T>
		void setValue(const std::string& id, const T& value)
		{
			auto search = _values.find(id);

			if (search != _values.end())
			{
				_values[id] = value;
			}
			else
			{
				_values.emplace(std::make_pair(id, value));
			}
		}

	} TValues;

	class FSMAgent
	{
		AI::FSM<FSMAgent>* _FSM;
		Logic::CEntity* _entity;
		Sounds::CSoundsResources* _sounds;

		TValues* _agentValues;

		bool _seeingPlayer;

	public:

		FSMAgent(Logic::CEntity* entity, const std::string& initialState);

		~FSMAgent();

		void update(float msecs);

		void changeState(const luabind::object& newState);

		void activate(const std::string& component);

		void deactivate(const std::string& component);

		template<typename T>
		T getValue(const std::string& id) const { return _agentValues->getValue<T>(id); }

		template<typename T>
		void setValue(const std::string& id, const T& value){_agentValues->setValue<T>(id, value);};

		void setAnimation(const std::string& animationName, bool loop, bool nextAnimation);

		// Instances (For fmod studio audio "things exported from editor")
		void createInstance(std::string instanceName, std::string descriptionName, bool paused);
		void deleteInstance(std::string instanceName);
		void playInstance(std::string instanceName);
		void pauseInstance(std::string instanceName);
		void setInstanceParameterValue(std::string instanceName, std::string parameterName, float parameterValue);
		void setInstanceVolume(std::string instanceName, float volume);

		// Sounds (For fmod low level ".mp3, .wav etc...")
		void createSound(std::string channelName, std::string soundName, bool paused);
		void deleteSound(std::string channelName);
		void playSound(std::string channelName);
		void pauseSound(std::string channelName);
		bool getPausedSound(std::string channelName);
		void setSoundPitch(std::string channelName, float pitch);
		void setSoundVolume(std::string channelName, float volume);
		void playAndDestroySound(std::string soundName, float volume);
		void setPositionAndVelocity(std::string channelName, Vector3 position, Vector3 velocity);

	}; // class FSMAgent

} // namespace AI

#endif // AI_FSM_AGENT_H
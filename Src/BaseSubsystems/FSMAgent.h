#ifndef AI_FSM_AGENT_H
#define AI_FSM_AGENT_H

#include "BaseSubsystems/FSM.h"
#include "Logic/Entity/Entity.h"

#include <unordered_map>

#include <boost/variant/variant.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/get.hpp>

namespace AI
{

	typedef boost::variant<bool, float> TAgentValue;

	typedef struct
	{

		std::unordered_map<std::string, TAgentValue> _values;

		bool getBoolValue(const std::string& id) const
		{
			return boost::get<bool>(_values.at(id));
		}

		float getFloatValue(const std::string& id) const
		{
			return boost::get<float>(_values.at(id));
		}

		void setBoolValue(const std::string& id, bool value)
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

		void setFloatValue(const std::string& id, float value)
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

		bool simpleFunction()
		{
			std::cout << "asfagdsgda" << std::endl;
			return true;
		}

	} TValues;

	class FSMAgent
	{
		AI::FSM<FSMAgent>* _FSM;
		Logic::CEntity* _entity;

		TValues* _agentValues;

		bool _seeingPlayer;

	public:

		FSMAgent(Logic::CEntity* entity);

		~FSMAgent();

		void update();

		void changeState(const luabind::object& newState, const std::string& componentToDeactivate, const std::string& componentToActivate);

		FSM<FSMAgent>* getFSM() const;

		TValues* getValues();

	}; // class FSMAgent

} // namespace AI

#endif // AI_FSM_AGENT_H
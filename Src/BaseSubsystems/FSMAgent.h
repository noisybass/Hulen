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

		TValues* _agentValues;

		bool _seeingPlayer;

	public:

		FSMAgent(Logic::CEntity* entity);

		~FSMAgent();

		void update();

		void changeState(const luabind::object& newState);

		void activate(const std::string& component);

		void deactivate(const std::string& component);

		FSM<FSMAgent>* getFSM() const;

		TValues* getValues();

		bool getBoolValue(const std::string& id) const;

		float getFloatValue(const std::string& id) const;

		void setBoolValue(const std::string& id, bool value);

		void setFloatValue(const std::string& id, float value);

	}; // class FSMAgent

} // namespace AI

#endif // AI_FSM_AGENT_H
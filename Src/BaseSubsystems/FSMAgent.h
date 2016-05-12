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
		void setValue(const std::string& id, const T& value) { _agentValues->setValue<T>(id, value); }

	}; // class FSMAgent

} // namespace AI

#endif // AI_FSM_AGENT_H
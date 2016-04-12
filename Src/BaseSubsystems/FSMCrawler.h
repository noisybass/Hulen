#ifndef AI_FSM_CRAWLER_H
#define AI_FSM_CRAWLER_H

#include "BaseSubsystems/StateMachine.h"
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
			bool value = boost::get<bool>(_values.at(id));
			return value;
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

	class FSMCrawler
	{
		AI::StateMachine<FSMCrawler>* _FSM;
		Logic::CEntity* _entity;

		TValues* _agentValues;

		bool _seeingPlayer;

	public:

		FSMCrawler(Logic::CEntity* entity);

		~FSMCrawler();

		void update();

		void changeState(const luabind::object& newState, const std::string& componentToDeactivate, const std::string& componentToActivate);

		StateMachine<FSMCrawler>* getFSM() const;

		TValues* getValues();

	}; // class FSMCrawler

} // namespace AI

#endif // AI_FSM_CRAWLER_H
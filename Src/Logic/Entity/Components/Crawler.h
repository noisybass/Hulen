#ifndef LOGIC_CRAWLER_H
#define LOGIC_CRAWLER_H

#include "Logic/Entity/Component.h"
#include "BaseSubsystems/FSMCrawler.h"

namespace Logic
{
	class CCrawler : public IComponent
	{
		DEC_FACTORY(CCrawler);

		AI::FSMCrawler*  _agent;

	public:

		CCrawler();

		~CCrawler();

		void tick(unsigned int msecs) override;

	}; // class CCrawler

	REG_FACTORY(CCrawler);

} // namespace Logic

#endif // LOGIC_CRAWLER_H
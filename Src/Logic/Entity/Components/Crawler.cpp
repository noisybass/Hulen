#include "Crawler.h"

#include "Logic/Entity/Components/Vision.h"

namespace Logic
{
	IMP_FACTORY(CCrawler);

	CCrawler::CCrawler()
		: IComponent()
	{
		// Creamos la máquina de estados
		_agent = new AI::FSMCrawler();
	}


	void CCrawler::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		// Actualizamos los valores que necesita el agente
		CVision* crawlerVision = (CVision*)(_entity->getComponent("CVision"));
		if (crawlerVision->_seeingEntity && !crawlerVision->_lastSeenEntity->getName().compare("Player_Body"))
		{
			std::cout << "He visto al player" << std::endl;
			_agent->setSeeingPlayer(true);
		}
		else
		{
			_agent->setSeeingPlayer(false);
		}
			

		_agent->update();

	} // tick

} // namespace Logic
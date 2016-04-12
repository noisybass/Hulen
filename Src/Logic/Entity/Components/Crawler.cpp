#include "Crawler.h"

#include "Logic/Entity/Components/Vision.h"

namespace Logic
{
	IMP_FACTORY(CCrawler);

	CCrawler::CCrawler()
		: IComponent(), _agent(nullptr)
	{

	} // CCrawler

	CCrawler::~CCrawler()
	{
		if (_agent)
			delete _agent;

	} // ~CCrawler

	bool CCrawler::spawn(const std::string& name, CEntity *entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		_agent = new AI::FSMCrawler(_entity);

		return true;

	} // spawn


	void CCrawler::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		// Actualizamos los valores que necesita el agente
		CVision* crawlerVision = (CVision*)(_entity->getComponent("CVision"));
		if (crawlerVision->_seeingEntity && !crawlerVision->_lastSeenEntity->getName().compare("Player_Body"))
		{
			std::cout << "He visto al player" << std::endl;
			_agent->getValues()->setBoolValue("SeeingPlayer", true);
		}
		else
		{
			_agent->getValues()->setBoolValue("SeeingPlayer", false);
		}
			

		_agent->update();

	} // tick

} // namespace Logic
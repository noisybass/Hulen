#include "FSMEntity.h"

#include "Logic/Entity/Components/Vision.h"

namespace Logic
{
	IMP_FACTORY(CFSMEntity);

	CFSMEntity::CFSMEntity()
		: IComponent(), _agent(nullptr)
	{

	} // CCrawler

	CFSMEntity::~CFSMEntity()
	{
		if (_agent)
			delete _agent;

	} // ~CCrawler

	bool CFSMEntity::spawn(const std::string& name, CEntity *entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		_agent = new AI::FSMAgent(_entity);

		return true;

	} // spawn


	void CFSMEntity::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		// Actualizamos los valores que necesita el agente
		/*CVision* crawlerVision = (CVision*)(_entity->getComponent("CVision"));
		if (crawlerVision->_seeingEntity && !crawlerVision->_lastSeenEntity->getName().compare("Player_Body"))
		{
			_agent->setValue<bool>("SeeingPlayer", true);
		}
		else
		{
			_agent->setValue<bool>("SeeingPlayer", false);
		}*/
			

		_agent->update();

	} // tick

} // namespace Logic
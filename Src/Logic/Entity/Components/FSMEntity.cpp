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

		assert(entityInfo->hasAttribute("fsm_initial_state"));
		_agent = new AI::FSMAgent(_entity, entityInfo->getStringAttribute("fsm_initial_state"));

		return true;

	} // spawn


	void CFSMEntity::tick(float msecs)
	{
		IComponent::tick(msecs);

		_agent->update(msecs);

	} // tick

} // namespace Logic
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
		_agent = new AI::FSMAgent(_entity);
		_agent->init(entityInfo->getStringAttribute("fsm_initial_state"));
		setAnimationNames(entityInfo);

		return true;

	} // spawn

	void CFSMEntity::tick(float msecs)
	{
		IComponent::tick(msecs);

		_agent->update(msecs);

	} // tick

	void CFSMEntity::setAnimationNames(const Map::CEntity *entityInfo)
	{

		if (entityInfo->hasAttribute("idle1Animation"))
		{
			setValue<std::string>("idle1Animation", entityInfo->getPairStringFloat("idle1Animation").first);
			setValue<bool>("idle1AnimationFinish", false);
			setValue<bool>("idle1AnimationStarted", false);
		}

		if (entityInfo->hasAttribute("idle2Animation"))
		{
			setValue<std::string>("idle2Animation", entityInfo->getPairStringFloat("idle2Animation").first);
			setValue<bool>("idle2AnimationFinish", false);
			setValue<bool>("idle2AnimationStarted", false);
		}

		if (entityInfo->hasAttribute("walkAnimation"))
		{
			setValue<std::string>("walkAnimation", entityInfo->getPairStringFloat("walkAnimation").first);
			setValue<bool>("walkAnimationFinish", false);
			setValue<bool>("walkAnimationStarted", false);
		}

		if (entityInfo->hasAttribute("runAnimation"))
		{
			setValue<std::string>("runAnimation", entityInfo->getPairStringFloat("runAnimation").first);
			setValue<bool>("runAnimationFinish", false);
			setValue<bool>("runAnimationStarted", false);
		}

		if (entityInfo->hasAttribute("deathAnimation"))
		{
			setValue<std::string>("deathAnimation", entityInfo->getPairStringFloat("deathAnimation").first);
			setValue<bool>("deathAnimationFinish", false);
			setValue<bool>("deathAnimationStarted", false);
		}

		if (entityInfo->hasAttribute("jump1Animation"))
		{
			setValue<std::string>("jump1Animation", entityInfo->getPairStringFloat("jump1Animation").first);
			setValue<bool>("jump1AnimationFinish", false);
			setValue<bool>("jump1AnimationStarted", false);
		}

		if (entityInfo->hasAttribute("fall1Animation"))
		{
			setValue<std::string>("fall1Animation", entityInfo->getPairStringFloat("fall1Animation").first);
			setValue<bool>("fall1AnimationFinish", false);
			setValue<bool>("fall1AnimationStarted", false);
		}

		if (entityInfo->hasAttribute("land1Animation"))
		{
			setValue<std::string>("land1Animation", entityInfo->getPairStringFloat("land1Animation").first);
			setValue<bool>("land1AnimationFinish", false);
			setValue<bool>("land1AnimationStarted", false);
		}

		if (entityInfo->hasAttribute("jump2Animation"))
		{
			setValue<std::string>("jump2Animation", entityInfo->getPairStringFloat("jump2Animation").first);
			setValue<bool>("jump2AnimationFinish", false);
			setValue<bool>("jump2AnimationStarted", false);
		}

		if (entityInfo->hasAttribute("fall2Animation"))
		{
			setValue<std::string>("fall2Animation", entityInfo->getPairStringFloat("fall2Animation").first);
			setValue<bool>("fall2AnimationFinish", false);
			setValue<bool>("fall2AnimationStarted", false);
		}

		if (entityInfo->hasAttribute("land2Animation"))
		{
			setValue<std::string>("land2Animation", entityInfo->getPairStringFloat("land2Animation").first);
			setValue<bool>("land2AnimationFinish", false);
			setValue<bool>("land2AnimationStarted", false);
		}

		if (entityInfo->hasAttribute("pickObjectAnimation"))
		{
			setValue<std::string>("pickObjectAnimation", entityInfo->getPairStringFloat("pickObjectAnimation").first);
			setValue<bool>("pickObjectAnimationFinish", false);
			setValue<bool>("pickObjectAnimationStarted", false);
		}

		if (entityInfo->hasAttribute("changeDirectionAnimation"))
		{
			setValue<std::string>("changeDirectionAnimation", entityInfo->getPairStringFloat("changeDirectionAnimation").first);
			setValue<bool>("changeDirectionAnimationFinish", false);
			setValue<bool>("changeDirectionAnimationStarted", false);
		}

		if (entityInfo->hasAttribute("startRunAnimation"))
		{
			setValue<std::string>("startRunAnimation", entityInfo->getPairStringFloat("startRunAnimation").first);
			setValue<bool>("startRunAnimationFinish", false);
			setValue<bool>("startRunAnimationStarted", false);
		}

		if (entityInfo->hasAttribute("preparationAnimation"))
		{
			setValue<std::string>("preparationAnimation", entityInfo->getPairStringFloat("preparationAnimation").first);
			setValue<bool>("preparationAnimationFinish", false);
			setValue<bool>("preparationAnimationStarted", false);
		}

		if (entityInfo->hasAttribute("killScreamAnimation"))
		{
			setValue<std::string>("killScreamAnimation", entityInfo->getPairStringFloat("killScreamAnimation").first);
			setValue<bool>("killScreamAnimationFinish", false);
			setValue<bool>("killScreamAnimationStarted", false);
		}

		if (entityInfo->hasAttribute("eatLightAnimation"))
		{
			setValue<std::string>("eatLightAnimation", entityInfo->getPairStringFloat("eatLightAnimation").first);
			setValue<bool>("eatLightAnimationFinish", false);
			setValue<bool>("eatLightAnimationStarted", false);
		}

		if (entityInfo->hasAttribute("attackAnimation"))
		{
			setValue<std::string>("attackAnimation", entityInfo->getPairStringFloat("attackAnimation").first);
			setValue<bool>("attackAnimationFinish", false);
			setValue<bool>("attackAnimationStarted", false);
		}

	} // setAnimationNames

} // namespace Logic
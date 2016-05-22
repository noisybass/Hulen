#include "HulenControllerFilterCallback.h"

#include "Logic/Entity/Components/Physics.h"
#include "Logic/Entity/GameObject.h"

namespace Physics
{
	bool HulenControllerFilterCallback::filter(const PxController& a, const PxController& b)
	{
		Logic::IPhysics* aComponent = (Logic::IPhysics*)a.getActor()->userData;
		Logic::CGameObject* aGO = aComponent->getEntity()->getGameObject();

		Logic::IPhysics* bComponent = (Logic::IPhysics*)b.getActor()->userData;
		Logic::CGameObject* bGO = bComponent->getEntity()->getGameObject();

		if (aGO->getState() == bGO->getState())
			return true;

		return false;
	}
}
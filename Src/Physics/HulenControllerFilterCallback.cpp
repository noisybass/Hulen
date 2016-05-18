#include "HulenControllerFilterCallback.h"

#include "Logic/Entity/Components/Physics.h"

namespace Physics
{
	bool HulenControllerFilterCallback::filter(const PxController& a, const PxController& b)
	{
		Logic::IPhysics* aComponent = (Logic::IPhysics*)a.getActor()->userData;

		Logic::IPhysics* bComponent = (Logic::IPhysics*)b.getActor()->userData;

		if (!aComponent->isActive() || !bComponent->isActive())
			return false;

		return true;
	}
}
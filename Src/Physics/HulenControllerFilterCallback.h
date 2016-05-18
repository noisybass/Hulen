#ifndef PHYSICS_HULEN_CONTROLLER_FILTER_CALLBACK_H
#define PHYSICS_HULEN_CONTROLLER_FILTER_CALLBACK_H

#include <PxPhysicsAPI.h>
#include <extensions\PxExtensionsAPI.h>
#include <extensions\PxVisualDebuggerExt.h> 

using namespace physx;

namespace Physics
{
	class HulenControllerFilterCallback : PxControllerFilterCallback
	{
	public:
		bool filter(const PxController& a, const PxController& b) override;
	};
}

#endif
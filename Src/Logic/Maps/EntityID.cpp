#include "EntityID.h"

#include <cassert>

namespace Logic 
{
	TEntityID EntityID::_nextId = EntityID::FIRST_ID;

	//---------------------------------------------------------

	TEntityID EntityID::NextID() 
	{
		TEntityID ret = _nextId;
		assert(ret != EntityID::UNASSIGNED && "Se han asignado todos los identificadores posibles.");
		_nextId++;
		return ret;

	} // NextEntityId

}; // namespace Logic

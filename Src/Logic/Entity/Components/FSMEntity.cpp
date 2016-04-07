#include "FSMEntity.h"

namespace Logic
{
	IMP_FACTORY(CFSMEntity);

	CFSMEntity::CFSMEntity()
		: IComponent()
	{
		// Creamos la máquina de estados
		_agent = new AI::FSMAgent();
	}


	void CFSMEntity::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		_agent->update();

	} // tick

} // namespace Logic
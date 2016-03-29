#ifndef LOGIC_FSM_ENTITY_H
#define LOGIC_FSM_ENTITY_H

//#include "Logic\Entity\Component.h"
#include "BaseSubsystems\StateMachine.h"
#include "ClasePruebas.h"

namespace Logic
{
	class CFSMEntity /*: public IComponent*/ : public ClasePruebas
	{
		/*DEC_FACTORY(CFSMEntity);*/
	private:

		AI::StateMachine<CFSMEntity>* _FSM;

	public:

		CFSMEntity();

		bool activate()/* override*/;

		void tick(unsigned int msecs) /*override*/;

		void sayHello();

		AI::StateMachine<CFSMEntity>* getFSM() const { return _FSM; }

	}; // class CFSMEntity

	/*REG_FACTORY(CFSMEntity);*/

} // namespace Logic

#endif // LOGIC_FSM_ENTITY_H
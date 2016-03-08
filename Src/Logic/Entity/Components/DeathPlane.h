#ifndef __Logic_DeathPlane_H
#define __Logic_DeathPlane_H

#include "Logic/Entity/Component.h"

namespace Logic 
{

	class CDeathPlane : public IComponent
	{
		DEC_FACTORY(CDeathPlane);
	public:

		/**
		Constructor por defecto.
		*/
		CDeathPlane() : IComponent() {}
		
		virtual bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		virtual bool accept(const TMessage &message);

		virtual void process(const TMessage &message);


	protected:

		

	}; // class CDeathPlane

	REG_FACTORY(CDeathPlane);

} // namespace Logic

#endif // __Logic_DeathPlane_H

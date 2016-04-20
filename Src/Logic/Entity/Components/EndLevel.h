#ifndef __Logic_EndLevel_H
#define __Logic_EndLevel_H

#include "Logic/Entity/Component.h"

namespace Logic 
{

	class CEndLevel : public IComponent
	{
		DEC_FACTORY(CEndLevel);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CEndLevel() : IComponent(){}

		
		virtual ~CEndLevel();
		
		
		virtual bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		
		virtual bool accept(const TMessage &message);

		
		virtual void process(const TMessage &message);

	protected:

		

	}; // class CEndLevel

	REG_FACTORY(CEndLevel);

} // namespace Logic

#endif // __Logic_EndLevel_H

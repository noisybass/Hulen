#ifndef LOGIC_PATROL_H
#define LOGIC_PATROL_H

#include "State.h"

namespace Logic 
{
	class CPatrol : public CState
	{
		DEC_FACTORY(CPatrol);
	public:

		/**
		Constructor por defecto.
		*/
		CPatrol();
		
		/**
		Inicialización del componente usando la descripción de la entidad que hay en 
		el fichero de mapa.
		*/
		bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;

		void enterState() override;

		void exitState() override;
		
		bool accept(const TMessage &message) override;
		
		void process(const TMessage &message) override;

		void tick(float msecs) override;

	protected:
		
		Vector3 _patrolPosition1;

		Vector3 _patrolPosition2;
	private:

		bool _arrivedToDestination;
		Vector3 _arrivedDestination;

	}; // class CPatrol

	REG_FACTORY(CPatrol);

} // namespace Logic

#endif // LOGIC_PATROL_H

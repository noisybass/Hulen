#ifndef LOGIC_PATROL_H
#define LOGIC_PATROL_H

#include "Logic/Entity/Component.h"

namespace Logic 
{
	class CPatrol : public IComponent
	{
		DEC_FACTORY(CPatrol);
	public:

		/**
		Constructor por defecto.
		*/
		CPatrol() : IComponent(), _arrivedToDestination(true), _patrolPosition1(Vector3::ZERO),
			_patrolPosition2(Vector3::ZERO), _arrivedDestination(Vector3::ZERO), _active(true) {}
		
		/**
		Inicialización del componente usando la descripción de la entidad que hay en 
		el fichero de mapa.
		*/
		bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;

		bool activate() override;

		void deactivate() override;
		
		bool accept(const TMessage &message) override;
		
		void process(const TMessage &message) override;

		void tick(unsigned int msecs) override;

	protected:
		
		Vector3 _patrolPosition1;

		Vector3 _patrolPosition2;
	private:

		bool _arrivedToDestination;
		Vector3 _arrivedDestination;

		bool _active;

	}; // class CPatrol

	REG_FACTORY(CPatrol);

} // namespace Logic

#endif // LOGIC_PATROL_H

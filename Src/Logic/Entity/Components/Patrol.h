#ifndef PATROL_H
#define PATROL_H

#include "Logic/Entity/Component.h"

//declaración de la clase
namespace Logic 
{
/**
	Este componente procesa mensajes de tipo TOUCHED o UNTOUCHED (indican que la 
	entidad ha sido tocada o dejada de ser tocada) para enviar un mensaje SWITCH a 
	una entidad objetivo.
	<p>
	La entidad objetivo se especifica en el mapa con el atributo "target". Este 
	atributo <em>debe</em> ser especificado.
	
    @ingroup logicGroup

	@author David Llansó García
	@date Octubre, 2010
*/
	class CPatrol : public IComponent
	{
		DEC_FACTORY(CPatrol);
	public:

		/**
		Constructor por defecto.
		*/
		CPatrol() : IComponent(), _arrivedToDestination(true) {}
		
		/**
		Inicialización del componente usando la descripción de la entidad que hay en 
		el fichero de mapa.
		*/
		virtual bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo);
		
		virtual bool accept(const TMessage &message);
		
		virtual void process(const TMessage &message);

		virtual void tick(unsigned int msecs);

	protected:
		
		Vector3 _patrolPosition1;

		Vector3 _patrolPosition2;
	private:

		bool _arrivedToDestination;
		Vector3 _arrivedDestination;

	}; // class CPatrol

	REG_FACTORY(CPatrol);

} // namespace Logic

#endif // PATROL_H

/**
@file RayPerception.h

Contiene la declaración de un componente de percepción basado en lanzamiento de rayos.

@see Logic::CRayPerception
@see Logic::IComponent

@author Antonio A. Sánchez Ruiz-Granados
@date Noviembre, 2012
*/

#ifndef __Logic_RayPerception_H
#define __Logic_RayPerception_H

#include "Logic/Entity/Component.h"

// Los componentes se definen dentro del namespace Logica
namespace Logic 
{
	/**
	Este componente lanza un rayo en la dirección en la que mira la entidad para 
	comprobar si alguna otra entidad está cerca.

	@todo Ahora mismo este componente sólo escribe por consola los objetos que
	percibe. En el futuro habría que mandar un mensaje a la entidad para que los
	componentes	encargados del comportamiento reaccionen.
	
    @ingroup logicGroup

	@author Antonio A. Sánchez Ruiz-Granados
	@date Noviembre, 2012
	*/
	class CRayPerception : public IComponent
	{
		DEC_FACTORY(CRayPerception);
	public:

		/**
		Constructor por defecto.
		*/
		CRayPerception();

		/**
		Destructor.
		*/
		virtual ~CRayPerception();
		
		/**
		Inicializa el componente usando los atributos definidos en el fichero de mapa.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		En cada tick lanza un rayo en la dirección que mira la entidad para comprobar
		si hay alguna otra entidad en su rango de percepción.
		*/
		virtual void tick(unsigned int msecs);

	protected:

		/**
		Distancia máxima a la que se perciben las entidades.
		*/
		float _distance;

	}; // class CRayPerception

	REG_FACTORY(CRayPerception);

} // namespace Logic

#endif // __Logic_RayPerception_H
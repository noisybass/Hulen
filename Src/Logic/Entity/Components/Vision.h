#ifndef VISION_H
#define VISION_H

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
	class CVision : public IComponent
	{
		DEC_FACTORY(CVision);
	public:

		/**
		Constructor por defecto.
		*/
		CVision() : IComponent(), _ray(), _defaultVision(5), _xRaySeparation(0.7), _yRaySeparation(0.5) {}
		
		/**
		Inicialización del componente usando la descripción de la entidad que hay en 
		el fichero de mapa.
		*/
		virtual bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		Este componente sólo acepta mensaje de tipos TOUCHED y UNTOUCHED.
		*/
		virtual bool accept(const TMessage &message);

		/**
		Al recibir mensaje TOUCHED y UNTOUCHED emite mensajes SWITCH
		a la entidad objetivo para que cambie de posición.
		*/
		virtual void process(const TMessage &message);

		virtual void tick(unsigned int msecs);

		/**
		Devuelve la primera entidad vista. Utiliza
		la vision por defecto o que se ha proporcionado al crear
		el objeto.
		*/
		Logic::CEntity* visionRay();

		/**
		Devuelve la primera entidad vista. Se calcula dada la distancia 
		a la que se quiere calcular el rayo.
		*/
		Logic::CEntity* visionRay(const float maxDistance);

	protected:

		Ray _ray;

		float _defaultVision;

		float _xRaySeparation;
		float _yRaySeparation;
		

	}; // class CVision

	REG_FACTORY(CVision);

} // namespace Logic

#endif // VISION_H

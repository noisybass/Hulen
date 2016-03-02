#ifndef __Logic_Spike_H
#define __Logic_Spike_H

#include "Logic/Entity/Component.h"

namespace Logic 
{

	class CSpike : public IComponent
	{
		DEC_FACTORY(CSpike);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CSpike() : IComponent(){}

		/**
		Destructor (virtual); Quita de la escena y destruye la entidad gráfica.
		*/
		virtual ~CSpike();
		
		/**
		Inicialización del componente, utilizando la información extraída de
		la entidad leída del mapa (Maps::CEntity). Toma del mapa el atributo
		model con el modelo que se deberá cargar e invoca al método virtual
		createGraphicsEntity() para generar la entidad gráfica.

		@param entity Entidad a la que pertenece el componente.
		@param map Mapa Lógico en el que se registrará el objeto.
		@param entityInfo Información de construcción del objeto leído del
			fichero de disco.
		@return Cierto si la inicialización ha sido satisfactoria.
		*/
		virtual bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		Método virtual que elige que mensajes son aceptados. Son válidos
		SET_TRANSFORM.

		@param message Mensaje a chequear.
		@return true si el mensaje es aceptado.
		*/
		virtual bool accept(const TMessage &message);

		/**
		Método virtual que procesa un mensaje.

		@param message Mensaje a procesar.
		*/
		virtual void process(const TMessage &message);

	protected:

		

	}; // class CSpike

	REG_FACTORY(CSpike);

} // namespace Logic

#endif // __Logic_Spike_H

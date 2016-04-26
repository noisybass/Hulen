#ifndef MOVECONTROLLER_H
#define MOVECONTROLLER_H

#include "Logic/Entity/Component.h"
#include "Logic/Entity/Entity.h"

//declaración de la clase
namespace Logic 
{

	class CMoveController : public IComponent
	{
		DEC_FACTORY(CMoveController);
	public:

		/**
		Constructor por defecto; inicializa los atributos a su valor por 
		defecto.
		*/
		CMoveController() : IComponent(), _speed(0.01), _gravity(0.015) {}
	
		/**
		Inicialización del componente, utilizando la información extraída de
		la entidad leída del mapa (Maps::CEntity). Toma del mapa el atributo
		speed que indica a la velocidad a la que se moverá el jugador.

		@param entity Entidad a la que pertenece el componente.
		@param map Mapa Lógico en el que se registrará el objeto.
		@param entityInfo Información de construcción del objeto leído del
			fichero de disco.
		@return Cierto si la inicialización ha sido satisfactoria.
		*/
		virtual bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		Método llamado en cada frame que actualiza el estado del componente.
		
		Se encarga de mover la entidad en cada vuelta de ciclo cuando es
		necesario (cuando está andando o desplazándose lateralmente).

		@param msecs Milisegundos transcurridos desde el último tick.
		*/
		virtual void tick(float msecs);

		/**
		Método virtual que elige que mensajes son aceptados. Son válidos
		CONTROL.

		@param message Mensaje a chequear.
		@return true si el mensaje es aceptado.
		*/
		virtual bool accept(const TMessage &message);

		/**
		Método virtual que procesa un mensaje.

		@param message Mensaje a procesar.
		*/
		virtual void process(const TMessage &message);

		void nextPosition(const Vector3 &position);

	private:
		void calculateDirection();

		bool destinationReached();

		void walkLeft();

		void walkRight();

		void stop();

	protected:

		/**
		Atributo que indica la magnitud de velocidad de la entidad.
		*/
		float _speed;

		/**
		Gravedad
		*/
		float _gravity;

		Vector3 _positionToGo;

		Vector3 _nextPositionToGo;


	}; // class CAvatarController

	REG_FACTORY(CMoveController);

} // namespace Logic

#endif // MOVECONTROLLER_H

#ifndef LOGIC_KASAI_CONTROLLER_H
#define LOGIC_KASAI_CONTROLLER_H

#include "Logic/Entity/Component.h"

namespace Logic
{
	/**
	Este componente es el encargado de mover a Kasai, la luz que puede ser
	controlada por el jugador. El componente nos permite cambiar su posición o
	hacerla visible o invisible.
	*/
	class CKasaiController : public IComponent
	{
		DEC_FACTORY(CKasaiController);
	public:

		/**
		Constructor por defecto
		*/
		CKasaiController();

		/**
		Inicialización del componente, utilizando la información extraída de
		la entidad leída del mapa (Maps::CEntity).

		@param entity Entidad a la que pertenece el componente.
		@param map Mapa Lógico en el que se registrará el objeto.
		@param entityInfo Información de construcción del objeto leído del
		fichero de disco.
		@return Cierto si la inicialización ha sido satisfactoria.
		*/
		bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;

		/**
		Método que activa el componente; invocado cuando se activa
		el mapa donde está la entidad a la que pertenece el componente.

		@return true si todo ha ido correctamente.
		*/
		bool activate() override;

		/**
		Método que desactiva el componente; invocado cuando se
		desactiva el mapa donde está la entidad a la que pertenece el
		componente. Se invocará siempre, independientemente de si estamos
		activados o no.
		*/
		void deactivate() override;

		/**
		Método virtual que elige que mensajes son aceptados. Son válidos
		KASAI_MOVE, KASAI_SET_VISIBLE.

		@param message Mensaje a chequear.
		@return true si el mensaje es aceptado.
		*/
		bool accept(const TMessage &message) override;

		/**
		Método virtual que procesa un mensaje.

		@param message Mensaje a procesar.
		*/
		void process(const TMessage &message) override;

	protected:

		/**
		Atributo para saber si la entidad esta visible.
		*/
		bool _isVisible;

		/**
		Nombre del player.
		*/
		std::string _playerName;

		/**
		Referencia al player.
		*/
		CGameObject* _player;

	}; // class CKasaiController

	REG_FACTORY(CKasaiController);

} // namespace Logic

#endif // LOGIC_KASAI_CONTROLLER_H
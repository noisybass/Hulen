#ifndef LOGIC_GAME_OBJECT_H
#define LOGIC_GAME_OBJECT_H

#include "Logic\Entity\Entity.h"
#include "Logic\Entity\Component.h"
#include "Logic\Maps\Map.h"

namespace Logic
{

	class CGameObject
	{
	public:

		CGameObject(TEntityID gameObjectID);

		~CGameObject();

		bool spawn(CMap *map, const Map::CEntity *entityInfo);

		CEntity* getBody() const;

		CEntity* getShadow() const;

		void setBody(CEntity* body);

		void setShadow(CEntity* shadow);

		bool activate();

		void deactivate();

		bool isActivated();

		void tick(unsigned int msecs);

		void addComponent(IComponent* component);

		bool removeComponent(IComponent* component);

		void destroyAllComponents();

		bool emitMessage(const TMessage &message, IComponent* emitter = 0);

		/**
		Devuelve el identificador único del game object.

		@return Identificador.
		*/
		Logic::TEntityID getGameObjectID() const;

		/**
		Devuelve el mapa donde está el game object.

		@return Puntero al mapa que contiene el game object.
		*/
		CMap *getMap();

		/**
		Devuelve el nombre del game object.

		@return Nombre del game object.
		*/
		const std::string &getName() const;

		/**
		Devuelve el blueprint del game object. Este atributo es leido de
		la entidad del mapa en spawn().

		@return Blueprint del game object.
		*/
		const std::string &getBlueprint() const;

	protected:

		/**
		Clase amiga que puede modificar los atributos (en concreto se
		usa para modificar el mapa.
		*/
		friend class CMap;

		CEntity* _body;
		CEntity* _shadow;

		bool _activated;

		/**
		Identificador único del game object.
		*/
		Logic::TEntityID _gameObjectID;

		/**
		Tipo para la lista de componetes.
		*/
		typedef std::list<IComponent*> TComponentList;

		/**
		Lista de los componentes del game object.
		*/
		TComponentList _components;

		/**
		Tipo del game object declarado en el archivo blueprints.
		*/
		std::string _blueprint;

		/**
		Nombre del game object.
		*/
		std::string _name;

		/**
		Mapa lógico donde está el game object.
		*/
		Logic::CMap *_map;

	}; // class CGameObject

} // namespace Logic

#endif // LOGIC_GAME_OBJECT_H
#ifndef LOGIC_GAME_OBJECT_H
#define LOGIC_GAME_OBJECT_H

#include "Logic\Entity\Entity.h"
#include "Logic\Entity\Component.h"
#include "Logic\Maps\Map.h"

namespace Logic
{
	namespace GameObject
	{
		enum TState
		{
			BODY,
			SHADOW,
			BOTH
		};
	}

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
		Método que indica si el game object es o no el jugador.
		Seguro que hay formas mejores desde el punto de vista de
		diseño de hacerlo, pero esta es la más rápida: la entidad
		con la descripción de la entidad tiene esta descripción que
		establece en el spawn().

		@return true si la entidad es el jugador.
		*/
		bool isPlayer() { return _isPlayer; }

		/**
		Devuelve true si la luz que se controla por medio del
		raton se esta utilizando.
		*/
		bool isLight() { return _isLight; }

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

		/**
		Devuelve el nombre del material por defecto para una entidad, ya 
		sea de luz, o de sombra.
		*/
		const std::string& getDefaultMaterial(const std::string type) const;

	protected:

		/**
		Clase amiga que puede modificar los atributos (en concreto se
		usa para modificar el mapa.
		*/
		friend class CMap;

		friend class CPlayerManager;

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

		/**
		Atributo que indica si lael game object es el jugador; por defecto
		es false a no ser que se lea otra cosa de los atributos.
		*/
		bool _isPlayer;

		/**
		Atributo que indica el tiempo maximo que el jugador
		puede mantenerse en la oscuridad.
		*/
		float _playerDeathTime;

		/**
		Opcion de depuracion, si lo ponemos a true el jugador puede morir,
		si no por defecto no morira.
		*/
		bool _playerCanDie;

		/**
		Atributo que indica si la entidad es la luz que movemos con el raton.
		por defecto es false.
		*/
		bool _isLight;

		/**
		Atributo que indica el estado en el que se encuentra el game object.
		Puede ser BODY, SHADOW o BOTH
		*/
		GameObject::TState _state;

		/**
		Nombre del material por defecto para las sombras.
		*/
		std::string _defaultShadowMaterial;

		/**
		Nombre del material por defecto para el cuerpo.
		*/
		std::string _defaultBodyMaterial;

	}; // class CGameObject

} // namespace Logic

#endif // LOGIC_GAME_OBJECT_H
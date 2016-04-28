#ifndef LOGIC_ENTITY_H
#define LOGIC_ENTITY_H

#include "BaseSubsystems/Math.h"
#include "Logic/Maps/EntityID.h"
#include "Logic/Maps/Map.h"
#include "Logic/Maps/EntityFactory.h"
#include "Logic/Entity/GameObject.h"
#include "Logic/Entity/Component.h"
#include "Map/MapEntity.h"

// Mensaje
#include "Message.h"

#include <list>
#include <map>
#include <string>

// Declaración de la clase
namespace Logic 
{
	/**
	Clase que representa una entidad en el entorno virtual. Las entidades
	son meros contenedores de componentes, y su funcionamiento depende
	de cuáles tenga. Además, la clase contiene una serie de atributos que
	pueden ser accedidos desde los componentes (Id, nombre, etc.).
	<p>
	Tras la creación de la entidad, donde se inicializan los valores de la
	entidad a su valor por defecto, se invocará a su método spawn() en el
	que se inicializarán los atributos de la entidad con los valores leidos 
	del fichero del mapa. Tras esto, en algún momento, cuando se active
	el mapa se llamará al método activate() de la entidad. En este momento
	los componentes harán visibles los componentes gráficos y demás ya que 
	apartir de ahí es cuando la entidad empieza su función siendo actualizada 
	por el tick() en cada vuelta de bucle.

    @ingroup logicGroup
    @ingroup entityGroup

	@author David Llansó
	@date Agosto, 2010
	*/
	class CEntity 
	{
	protected:

		/**
		La factoria de entidades se encarga de crear las entidades
		pero cada game object es el responsable de eliminar sus entidades
		*/
		friend class CEntityFactory;
		friend class CGameObject;

		/**
		Constructor protegido de la clase (para crear CEntity debe
		utilizarse la factoría CEntityFactory). El constructor
		no hace más que poner el identificador único de la entidad
		, pues la inicialización efectiva se hace en el método spawn().
		
		@param entityID Identificador único de la entidad.
		*/
		CEntity();

		/**
		Destructor de la clase. Es un método protegido pues para
		eliminar CEntity debe utilizarse la factoría
		CEntityFactory. El destructor invoca al destructor de
		cada componente.
		Cuando el destructor es invocado, éste _ya ha sido desenganchado
		del mapa al que perteneció_, por lo que los destructores de los
		componentes no pueden utilizar el mapa.
		*/
		~CEntity();

		/**
		Inicialización del objeto Logic, utilizando la información extraída de
		la entidad leída del mapa (Map::CEntity). Avisará a los componentes
		de la entidad para que se inicialicen.

		@param map Mapa Logic en el que se registrará la entidad.
		@param entity Información de construcción de la entidad leída del
		fichero de disco.
		@return Cierto si la inicialización ha sido satisfactoria.
		*/
		bool spawn(CGameObject* gameObject, CMap *map, const Map::CEntity *entityInfo);

	public:

		/**
		Activa la entidad. Esto significa que el mapa ha sido activado.
		<p>
		El método llama al activate() de todos los componentes para que
		se den por enterados y hagan lo que necesiten.
		 
		@return Devuelve true si todo fue bien.
		*/
		bool activate();

		/**
		Desactiva la entidad. Esto significa que el mapa ha sido desactivado.
		<p>
		El método llama al deactivate() de todos los componentes para que
		se den por enterados y hagan lo que necesiten.
		*/
		void deactivate();

		/**
		Función llamada en cada frame para que se realicen las funciones
		de actualización adecuadas.
		<p>
		Llamará a los métodos tick() de todos sus componentes.

		@param msecs Milisegundos transcurridos desde el último tick.
		*/
		void tick(float msecs);

		/**
		Método que añade un nuevo componente a la lista de la entidad.

		@param component Componente a añadir.
		*/
		void addComponent(const std::string& name, IComponent* component);

		/**
		Método que quita un componente de la lista.

		El componente es eliminado de la lista de componentes de la
		entidad, pero <b>no</b> es desactivado ni eliminado (con delete);
		la responsabilidad de esa tarea se deja al invocante.

		@param component Componente a borrar.
		@return true si se borró el componente (false si el componente
		no estaba en el objeto).
		*/
		bool removeComponent(const std::string& name);
		
		/**
		Método que destruye todos los componentes de una entidad.
		*/
		void destroyAllComponents();

		/**
		Recibe un mensaje que envia a todos los componentes de la lista menos 
		al componente que lo envia, si éste se especifica en el segundo campo.

		@param message Mensaje a enviar.
		@param emitter Componente emisor, si lo hay. No se le enviará el mensaje.
		@return true si al menos un componente aceptó el mensaje
		*/
		bool emitMessage(const TMessage &message, IComponent* emitter = 0);
		
		/**
		Devuelve el nombre de la entidad.

		@return Nombre de la entidad.
		*/
		const std::string &getName() const { return _name; }

		/**
		Devuelve el blueprint de la entidad. Este atributo es leido de
		la entidad del mapa en spawn().

		@return Blueprint de la entidad.
		*/
		const std::string &getBlueprint() const { return _blueprint; }

		/**
		Establece la posición de la entidad. Avisa a los componentes
		del cambio.

		@param position Nueva posición.
		*/
		void setPosition(const Vector3 &position, IComponent* invoker = 0);

		/**
		Devuelve la posición de la entidad.
		<p>
		La posición es inicialmente leída del mapa (si no aparece,
		se colocará a (0, 0, 0)), aunque, obviamente, puede
		cambiar con el tiempo.

		@return Posición de la entidad en el entorno.
		*/
		Vector3 getPosition() const { return _position; }

		/**
		Indica si la entidad se encuentra activa.

		@return true si la entidad está activa.
		*/
		bool isActivated() { return _activated; }

		CGameObject* getGameObject() const;

		IComponent* getComponent(const std::string& name);

		/**
		Direction
		*/
		enum ENTITY_DIRECTION {
			RIGHT = 1,
			LEFT = -1
		};

		int getDirection() { return _direction; };

		void setDirection(ENTITY_DIRECTION direction){ _direction = direction;}

	protected:

		/**
		Game object al que pertenece la entidad.
		*/
		CGameObject* _gameObject;

		/**
		Tipo para la lista de componetes.
		*/
		typedef std::map<std::string, IComponent*> TComponentMap;

		/**
		Lista de los componentes de la entidad.
		*/
		TComponentMap _components;

		/**
		Indica si la entidad está activa.
		*/
		bool _activated;

		/**
		Tipo de la entidad declarado en el archivo blueprints.
		*/
		std::string _blueprint;

		/**
		Nombre de la entidad.
		*/
		std::string _name;

		/**
		Matriz de transformación de la entidad. Contiene posición y orientación.
		*/
		//Matrix4 _transform;

		bool _changeState;

		/**
		Entity direction.
		*/
		ENTITY_DIRECTION _direction;

		/**
		Entity position
		*/
		Vector3 _position;

	}; // class CEntity

} // namespace Logic

#endif // __Logic_Entity_H

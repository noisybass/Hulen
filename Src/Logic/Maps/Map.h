#ifndef LOGIC_MAP_H
#define LOGIC_MAP_H

#include "Map/MapEntity.h"
#include "Logic/Maps/EntityID.h"
#include "Logic/Entity/Message.h"
#include "Graphics/Scene.h"

#include <map>
#include <unordered_map>

// Predeclaración de clases para ahorrar tiempo de compilación
namespace Logic 
{
	class CEntity;
	class CGameObject;
}

// Declaración de la clase
namespace Logic
{
	/**
	Clase que representa un mapa lógico.
	<p>
	Esta clase se encarga de almacenar todas las entidades del mapa, tanto 
	aquellas que tienen representación gráfica y se ven como entidades
	puramente lógicas. Gestiona la activación y desactivación de éstas y
	tiene también métodos para buscar entidades, tanto por su nombre como 
	por su tipo y por su identificador.

	@ingroup logicGroup
	@ingroup mapGroup

	@author David Llansó
	@date Agosto, 2010
	*/
	class CMap
	{
	public:

		/**
		Método factoría que carga los prefabs. Tras el parseo de
		todas las entidades del mapa mediante CMapParser, genera todas las
		entidades con CEntityFactory.

		@param filename Nombre del archivo a cargar.
		@return Prefabs generado.
		*/
		static bool createPrefabsFromFile(const std::string &prefabFileName);

		/**
		Método factoría que carga un mapa de fichero. Tras el parseo de
		todas las entidades del mapa mediante CMapParser, genera todas las
		entidades con CEntityFactory.

		@param filename Nombre del archivo a cargar.
		@return Mapa generado.
		*/
		static CMap* createEntitiesFromFile(const std::string &filename);

		/**
		Comprueba si existe un fichero con el nombre indicado en el parámetro.

		@param filename Nombre del archivo que se quiere comprobar que existe.
		@return si existe o no el fichero.
		*/
		static bool checkFileExists(const std::string &filename);

		static Map::CEntity* getGameObjectFromPrefab(const std::string &prefabName);

		static Map::CEntity* getBodyFromPrefab(const std::string &prefabName);

		static Map::CEntity* getShadowFromPrefab(const std::string &prefabName);

		/**
		Crea una nueva instancia de un prefab.
		*/
		static CGameObject* instantiatePrefab(const std::string& prefabToInstantiate, const std::string& nameToNewInstance,
			const std::string& bodyPosition = "{0, 0, 0}", const std::string& shadowPosition = "{0, 0, 0}");

		/**
		Constructor.

		@param name Nombre que se le da a este mapa.
		*/
		CMap(const std::string &name);

		/**
		Destructor.
		*/
		~CMap();
		
		/**
		Activa el mapa. Invocará al método activate() de todas las 
		entidades para que se den por enterados y hagan lo que necesiten.
		 
		@return Devuelve true al invocador si todas las entidades se
		activaron sin problemas.
		*/
		bool activate();

		/**
		Desactiva el mapa. Invocará al método deactivate() de todas las 
		entidades para que se den por enterados y hagan lo que necesiten.
		*/
		void deactivate();

		/**
		Función llamada en cada frame para que se realicen las funciones
		de actualización adecuadas.
		<p>
		Llamará a los métodos tick() de todas las entidades.

		@param msecs Milisegundos transcurridos desde el último tick.
		*/
		void tick(float msecs);

		/**
		Añade una nueva entidad al mapa. Si la entidad ya estaba incluida
		no se hace nada.

		@param entity Entidad a añadir.
		*/
		void addGameObject(CGameObject *gameObject);

		/**
		Elimina una entidad del mapa. Si la entidad no estaba incluida
		no se hace nada. La función desactiva previamente la entidad si
		ésta se encontraba activa.

		@note El mapa no se hace responsable de eliminar (con delete) la
		entidad.

		@param entity Entidad a eliminar.
		*/
		void removeGameObject(CGameObject *gameObject);

		/**
		Elimina y destruye todas las entidades del mapa dejando la lista 
		de entidades vacía.
		*/
		void destroyAllGameObjects();

		/**
		Recupera una entidad del mapa a partir de su ID.

		@param entityID ID de la entidad a recuperar.
		@return Entidad con el ID pedido, NULL si no se encuentra.
		*/
		CGameObject* getGameObjectByID(TEntityID gameObjectID);

		/**
		Recupera una entidad del mapa a partir de su nombre.

		@param name nombre de la entidad a recuperar.
		@param start Entidad desde la que se debe empezar a buscar
		en la lista. Útil si se tienen varias entidades con el mismo
		nombre y desde fuera se quiere ir accediendo a ellas una a una.
		Si no se especifica se empieza desde el principio.
		@return Entidad con el nombre pedido, NULL si no se encuentra.
		*/
		CGameObject* getGameObjectByName(const std::string &name, CGameObject *start = 0);

		/**
		Recupera una entidad del mapa a partir de su tipo.

		@param type nombre del tipo de la entidad a recuperar.
		@param start Entidad desde la que se debe empezar a buscar
		en la lista. Útil si se tienen varias entidades del mismo tipo
		y desde fuera se quiere ir accediendo a ellas una a una.
		Si no se especifica se empieza desde el principio.
		@return Entidad con el nombre pedido, NULL si no se encuentra.
		*/
		CGameObject* getGameObjectByBlueprint(const std::string &blueprint, CGameObject *start = 0);

		/**
		Devuelve la escena gráfica correspondiente a este mapa.

		@return Escena con las entidades gráficas.
		*/
		Graphics::CScene *getScene() {return _scene;}

		/**
		Envia un mensaje a todas los gameobjects existentes.
		*/
		void sendMessageToGameObjects(Logic::TMessage m);

		/**
		Destruye todos los prefabs que se han creado.
		*/
		static void destroyAllPrefabs();


	private:

		

		/**
		Tipo tabla de entidades de mapa.
		*/
		typedef std::map<TEntityID,CGameObject*> TGameObjectMap;

		/**
		tabla con las entidades del mapa localizadas por su ID.
		*/
		TGameObjectMap _gameObjectMap;

		/**
		Nombre del mapa.
		*/
		std::string _name;

		/**
		Referencia al mapa con las entidades. lo guardamos para poder
		instaciar nuevas entidades con los prefabs.
		*/
		static CMap* _entitiesMap;

		/**
		Escena gráfica donde se encontrarán las representaciones gráficas de
		las entidades.
		*/
		Graphics::CScene* _scene;

		struct TPrefab{
			Map::CEntity* gameObject;
			Map::CEntity* bodyEntity;
			Map::CEntity* shadowEntity;
		};

		typedef std::unordered_map<std::string, TPrefab*> TPrefabList;

		static TPrefabList _prefabList;

	}; // class CMap

} // namespace Logic

#endif // __Logic_Map_H

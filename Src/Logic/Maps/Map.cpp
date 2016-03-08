/**
@file Map.cpp

Contiene la implementación de la clase CMap, Un mapa lógico.

@see Logic::Map

@author David Llansó
@date Agosto, 2010
*/

#include "Map.h"

#include "Logic/Entity/Entity.h"
#include "Logic\Entity\GameObject.h"
#include "EntityFactory.h"

#include "Map/MapParser.h"
#include "Map/MapEntity.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "GUI\Server.h"
#include "GUI\SceneController.h"

#include <cassert>

// HACK. Debería leerse de algún fichero de configuración
#define MAP_FILE_PATH "./media/maps/"

namespace Logic {

	// Definition
	CMap::TPrefabList CMap::_prefabList = CMap::TPrefabList();
	Logic::CMap* CMap::_entitiesMap = nullptr;

	CMap* CMap::createPrefabsFromFile(const std::string &prefabFileName)
	{
		// Completamos la ruta con el nombre proporcionado
		std::string prefabPath(MAP_FILE_PATH);
		prefabPath = prefabPath + prefabFileName;

		// Parseamos el fichero de prefab
		if (!Map::CMapParser::getSingletonPtr()->parseFile(prefabPath, "Prefab"))
		{
			assert(!"No se ha podido parsear los prefabs.");
			return false;
		}

		// Si se ha realizado con éxito el parseo creamos el mapa.
		CMap *map = new CMap(prefabFileName);

		// Extraemos las entidades del parseo.
		Map::CMapParser::TEntityList* prefabList =
			Map::CMapParser::getSingletonPtr()->getPrefabList();

		CEntityFactory* entityFactory = CEntityFactory::getSingletonPtr();

		Map::CMapParser::TEntityList::const_iterator it, end;
		it = prefabList->begin();
		end = prefabList->end();

		// Creamos todas las entidades lógicas.
		for (; it != end; it++)
		{
			assert((*it)->hasAttribute("type") && "Falta el atributo type");

			// Obtenemos el tipo
			std::string type = (*it)->getStringAttribute("type");

			if (!type.compare("Body") || !type.compare("Shadow"))
			{

				// La propia factoría se encarga de añadir la entidad a su GameObject
				CEntity* entity = entityFactory->createEntity((*it), map);
				assert(entity && "No se pudo crear una entidad perteneciente a un game object");

				std::string gameObjectName = (*it)->getStringAttribute("game_object");
				std::string type = (*it)->getStringAttribute("type");

				assert(_prefabList.find(gameObjectName) != _prefabList.end() && "No se encuentra ese gameObject");
				TPrefab* prefab = _prefabList.at(gameObjectName);

				if (type == "Body")
					prefab->bodyEntity = (*it);
				else if (type == "Shadow")
					prefab->shadowEntity = (*it);
			}
			else if (!type.compare("GameObject"))
			{
				// La propia factoría se encarga de añadir el GameObject al mapa
				CGameObject* gameObject = entityFactory->createGameObject((*it), map);
				assert(gameObject && "No se pudo crear un game object del mapa");

				TPrefab* prefab = new TPrefab();
				prefab->gameObject = (*it);
				std::string name = (*it)->getName();

				_prefabList.insert({name, prefab});
			}
		}

		return map;
	}

	CGameObject* CMap::instantiatePrefab(const std::string &prefabToInstantiate, const std::string &nameToNewInstance)
	{
		CEntityFactory* entityFactory = CEntityFactory::getSingletonPtr();

		assert(_prefabList.find(prefabToInstantiate) != _prefabList.end() && "No existe el prefab que quieres instanciar.");
		TPrefab* prefab = _prefabList.at(prefabToInstantiate);
	
		// Nos guardamos el nombre original del prefab y le ponemos el nombre 
		// que nos pasan por la funcion
		std::string gameObjectName = prefab->gameObject->getName();
		prefab->gameObject->setName(nameToNewInstance + "_GO");

		// La propia factoría se encarga de añadir el GameObject al mapa
		CGameObject* gameObject = entityFactory->createGameObject(prefab->gameObject, _entitiesMap);
		assert(gameObject && "No se pudo crear un game object del mapa");

		// Reseteamos el nombre del gameobject
		prefab->gameObject->setName(gameObjectName);

		if (prefab->bodyEntity){
			std::string bodyName = prefab->bodyEntity->getName();
			prefab->bodyEntity->setName(nameToNewInstance + "_Body");
			std::string gameObjectReferenceName = prefab->bodyEntity->getStringAttribute("game_object");
			prefab->bodyEntity->setAttribute("game_object", nameToNewInstance + "_GO");

			// La propia factoría se encarga de añadir la entidad a su GameObject
			CEntity* entity = entityFactory->createEntity(prefab->bodyEntity, _entitiesMap);
			assert(entity && "No se pudo crear una entidad perteneciente a un game object");

			prefab->bodyEntity->setName(bodyName);
			prefab->bodyEntity->setAttribute("game_object", gameObjectReferenceName);
		}

		if (prefab->shadowEntity){
			std::string shadowName = prefab->shadowEntity->getName();
			prefab->bodyEntity->setName(nameToNewInstance + "_Shadow");
			std::string gameObjectReferenceName = prefab->bodyEntity->getStringAttribute("game_object");
			prefab->bodyEntity->setAttribute("game_object", nameToNewInstance + "_GO");

			// La propia factoría se encarga de añadir la entidad a su GameObject
			CEntity* entity = entityFactory->createEntity(prefab->shadowEntity, _entitiesMap);
			assert(entity && "No se pudo crear una entidad perteneciente a un game object");

			prefab->bodyEntity->setName(shadowName);
			prefab->bodyEntity->setAttribute("game_object", gameObjectReferenceName);
		}

		return gameObject;
	}

	CMap* CMap::createEntitiesFromFile(const std::string &filename)
	{
		// Completamos la ruta con el nombre proporcionado
		std::string completePath(MAP_FILE_PATH);
		completePath = completePath + filename;

		// Parseamos el fichero de mapa
		if (!Map::CMapParser::getSingletonPtr()->parseFile(completePath, "Map"))
		{
			assert(!"No se ha podido parsear el mapa.");
			return false;
		}

		// Si se ha realizado con éxito el parseo creamos el mapa.
		_entitiesMap = new CMap(filename);

		// Extraemos las entidades del parseo.
		Map::CMapParser::TEntityList* entityList =
			Map::CMapParser::getSingletonPtr()->getEntityList();

		CEntityFactory* entityFactory = CEntityFactory::getSingletonPtr();

		Map::CMapParser::TEntityList::const_iterator it, end;
		it = entityList->begin();
		end = entityList->end();

		// Creamos todas las entidades lógicas.
		for (; it != end; it++)
		{
			assert((*it)->hasAttribute("type") && "Falta el atributo type");

			// Obtenemos el tipo
			std::string type = (*it)->getStringAttribute("type");

			if (!type.compare("Body") || !type.compare("Shadow"))
			{
				// La propia factoría se encarga de añadir la entidad a su GameObject
				CEntity* entity = entityFactory->createEntity((*it), _entitiesMap);
				assert(entity && "No se pudo crear una entidad perteneciente a un game object");
			}
			else if (!type.compare("GameObject"))
			{
				// La propia factoría se encarga de añadir el GameObject al mapa
				CGameObject* gameObject = entityFactory->createGameObject((*it), _entitiesMap);
				assert(gameObject && "No se pudo crear un game object del mapa");
			}
		}

		return _entitiesMap;
	}

	//--------------------------------------------------------

	CMap::CMap(const std::string &name)
	{
		_name = name;
		_scene = Graphics::CServer::getSingletonPtr()->createScene(name);

	} // CMap

	//--------------------------------------------------------

	CMap::~CMap()
	{
		destroyAllGameObjects();
		destroyAllPrefabs();
		//delete _prefabList;
		if(Graphics::CServer::getSingletonPtr())
			Graphics::CServer::getSingletonPtr()->removeScene(_scene);

	} // ~CMap

	//--------------------------------------------------------

	bool CMap::activate()
	{
		Graphics::CServer::getSingletonPtr()->setScene(_scene);

		TGameObjectMap::const_iterator it, end;
		end = _gameObjectMap.end();
		it = _gameObjectMap.begin();

		bool correct = true;

		// Activamos todas las entidades registradas en el mapa.
		for(; it != end; it++)
			correct = (*it).second->activate() && correct;

		GUI::CServer::getSingletonPtr()->getSceneController()->setControlledScene(this);
		GUI::CServer::getSingletonPtr()->getSceneController()->activate();

		return correct;

	} // getEntity

	//--------------------------------------------------------

	void CMap::deactivate()
	{
		TGameObjectMap::const_iterator it, end;
		end = _gameObjectMap.end();
		it = _gameObjectMap.begin();

		// Desactivamos todas las entidades activas registradas en el mapa.
		for(; it != end; it++)
			if((*it).second->isActivated())
				(*it).second->deactivate();

		Graphics::CServer::getSingletonPtr()->setScene(0);

		GUI::CServer::getSingletonPtr()->getSceneController()->deactivate();
		GUI::CServer::getSingletonPtr()->getSceneController()->setControlledScene(nullptr);

	} // getEntity

	//---------------------------------------------------------

	void CMap::tick(unsigned int msecs) 
	{
		TGameObjectMap::const_iterator it;

		for (it = _gameObjectMap.begin(); it != _gameObjectMap.end(); ++it)
			(*it).second->tick(msecs);

	} // tick

	//--------------------------------------------------------

	void CMap::addGameObject(CGameObject* gameObject)
	{
		if (_gameObjectMap.count(gameObject->getGameObjectID()) == 0)
		{
			std::pair<TEntityID, CGameObject*> elem(gameObject->getGameObjectID(), gameObject);
			_gameObjectMap.insert(elem);
		}

	} // addEntity

	//--------------------------------------------------------

	void CMap::removeGameObject(CGameObject *gameObject)
	{
		if (_gameObjectMap.count(gameObject->getGameObjectID()) != 0)
		{
			if (gameObject->isActivated())
				gameObject->deactivate();
			gameObject->_map = nullptr;
			_gameObjectMap.erase(gameObject->getGameObjectID());
		}

	} // removeEntity

	//--------------------------------------------------------

	void CMap::destroyAllGameObjects()
	{
		CEntityFactory* entityFactory = CEntityFactory::getSingletonPtr();

		TGameObjectMap::const_iterator it, end;
		it = _gameObjectMap.begin();
		end = _gameObjectMap.end();

		// Eliminamos todas las entidades. La factoría se encarga de
		// desactivarlas y sacarlas previamente del mapa.
		while(it != end)
		{
			CGameObject* gameObject = (*it).second;
			it++;
			entityFactory->deleteGameObject(gameObject);
		}

		_gameObjectMap.clear();

	} // destroyAllGameObjects

	void CMap::destroyAllPrefabs()
	{
		for (auto it : _prefabList)
		{
			TPrefab* prefab = it.second;
			delete prefab;
		}

		_prefabList.clear();
	}

	//--------------------------------------------------------

	CGameObject* CMap::getGameObjectByID(TEntityID gameObjectID)
	{
		if (_gameObjectMap.count(gameObjectID) == 0)
			return 0;
		return (*_gameObjectMap.find(gameObjectID)).second;

	} // getEntityByID

	//--------------------------------------------------------

	CGameObject* CMap::getGameObjectByName(const std::string &name, CGameObject *start)
	{
		TGameObjectMap::const_iterator it, end;
		end = _gameObjectMap.end();

		// Si se definió entidad desde la que comenzar la búsqueda 
		// cogemos su posición y empezamos desde la siguiente.
		if (start)
		{
			it = _gameObjectMap.find(start->getGameObjectID());
			// si la entidad no existe devolvemos NULL.
			if(it == end)
				return 0;
			it++;
		}
		else
			it = _gameObjectMap.begin();

		for(; it != end; it++)
		{
			// si hay coincidencia de nombres devolvemos la entidad.
			if (!(*it).second->getName().compare(name))
				return (*it).second;
		}
		// si no se encontró la entidad devolvemos NULL.
		return 0;

	} // getEntityByName

	//--------------------------------------------------------

	void CMap::sendMessageToGameObjects(TMessage m){
		TGameObjectMap::const_iterator it;

		for (it = _gameObjectMap.begin(); it != _gameObjectMap.end(); ++it)
			(*it).second->emitMessage(m);
	}

	//--------------------------------------------------------

	CGameObject* CMap::getGameObjectByBlueprint(const std::string &blueprint, CGameObject *start)
	{
		TGameObjectMap::const_iterator it, end;
		end = _gameObjectMap.end();

		// Si se definió entidad desde la que comenzar la búsqueda 
		// cogemos su posición y empezamos desde la siguiente.
		if (start)
		{
			it = _gameObjectMap.find(start->getGameObjectID());
			// si la entidad no existe devolvemos NULL.
			if(it == end)
				return 0;
			it++;
		}
		else
			it = _gameObjectMap.begin();

		for(; it != end; it++)
		{
			// si hay coincidencia de nombres devolvemos la entidad.
			if (!(*it).second->getBlueprint().compare(blueprint))
				return (*it).second;
		}
		// si no se encontró la entidad devolvemos NULL.
		return 0;

	} // getEntityByType

} // namespace Logic

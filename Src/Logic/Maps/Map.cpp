#include "Map.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/GameObject.h"
#include "Logic/Maps/EntityFactory.h"
#include "Map/MapParser.h"
#include "Graphics/Server.h"
#include "GUI/Server.h"
#include "GUI/SceneController.h"

#include <cassert>

// HACK. Debería leerse de algún fichero de configuración
#define MAP_FILE_PATH "./media/maps/"

namespace Logic {

	// Definition
	CMap::TPrefabList CMap::_prefabList = CMap::TPrefabList();
	Logic::CMap* CMap::_entitiesMap = nullptr;

	bool CMap::createPrefabsFromFile(const std::string &prefabFileName)
	{
		// Completamos la ruta con el nombre proporcionado
		std::string prefabPath(MAP_FILE_PATH);
		prefabPath = prefabPath + prefabFileName;

		// Parseamos el fichero de prefab
		if (!Map::CMapParser::getSingletonPtr()->parseFile(prefabPath, "Prefab"))
		{
			assert(!"No se han podido parsear los prefabs.");
			return false;
		}

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
				assert((*it)->hasAttribute("game_object") && "Falta el atributo game_object");

				std::string gameObjectName = (*it)->getStringAttribute("game_object");

				// Con el name.length() - 3, lo que hacemos es quitar _GO del nombre
				// Para poder llamar al prefab sin eso, así es menos lioso.
				gameObjectName = gameObjectName.substr(0, gameObjectName.length() - 3);
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
				TPrefab* prefab = new TPrefab();
				prefab->gameObject = (*it);
				std::string name = (*it)->getName();

				// Con el name.length() - 3, lo que hacemos es quitar _GO del nombre
				// Para poder llamar al prefab sin eso, así es menos lioso.
				_prefabList.insert({name.substr(0, name.length() - 3), prefab});
			}
		}

		return true;
	}

	CGameObject* CMap::instantiatePrefab(const std::string& prefabToInstantiate, const std::string& nameToNewInstance,
		const std::string& bodyPosition, const std::string& shadowPosition)
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

			prefab->bodyEntity->setAttribute("position", bodyPosition);

			std::cout << prefabToInstantiate << " " << nameToNewInstance << std::endl;
			// La propia factoría se encarga de añadir la entidad a su GameObject
			CEntity* entity = entityFactory->createEntity(prefab->bodyEntity, _entitiesMap);
			assert(entity && "No se pudo crear una entidad perteneciente a un game object. Body.");

			prefab->bodyEntity->setName(bodyName);
			prefab->bodyEntity->setAttribute("game_object", gameObjectReferenceName);
		}

		if (prefab->shadowEntity){
			std::string shadowName = prefab->shadowEntity->getName();
			prefab->bodyEntity->setName(nameToNewInstance + "_Shadow");
			std::string gameObjectReferenceName = prefab->bodyEntity->getStringAttribute("game_object");
			prefab->bodyEntity->setAttribute("game_object", nameToNewInstance + "_GO");

			prefab->shadowEntity->setAttribute("position", shadowPosition);

			// La propia factoría se encarga de añadir la entidad a su GameObject
			CEntity* entity = entityFactory->createEntity(prefab->shadowEntity, _entitiesMap);
			assert(entity && "No se pudo crear una entidad perteneciente a un game object. Shadow.");

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
			return nullptr;
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
			// Obtenemos el tipo
			assert((*it)->hasAttribute("type") && "Falta el atributo type");
			std::string type = (*it)->getStringAttribute("type");	

			if (!type.compare("Body") || !type.compare("Shadow"))
			{
				// La propia factoría se encarga de añadir la entidad a su GameObject
				CEntity* entity = entityFactory->createEntity((*it), _entitiesMap);

				/*if ((*it)->getName() == "Character_Body")
					std::cout << (*it)->getName().c_str() << std::endl;*/

				if (!entity)
				{
					std::cout << ">> ERROR AL CREAR: " << (*it)->getName() << std::endl;
				}

				assert(entity && "No se pudo crear una entidad perteneciente a un game object. Creacion. ");
			}
			else if (!type.compare("GameObject"))
			{
				// La propia factoría se encarga de añadir el GameObject al mapa
				CGameObject* gameObject = entityFactory->createGameObject((*it), _entitiesMap);
				//assert(gameObject && "No se pudo crear un game object del mapa");
				if (!gameObject)
				{
					std::cout << ">> ERROR AL CREAR: " << (*it)->getName() << std::endl;
				}
			}
		}

		return _entitiesMap;
	}

	bool CMap::checkFileExists(const std::string &filename){

		// Completamos la ruta con el nombre proporcionado
		std::string completePath(MAP_FILE_PATH);
		completePath = completePath + filename;

		std::ifstream f(completePath.c_str());
		if (f.good()) {
			f.close();
			return true;
		}
		else {
			std::cout << "ERROR!! The file: " + completePath + " does not exist." << std::endl;
			f.close();
			return false;
		}
	}

	Map::CEntity* CMap::getGameObjectFromPrefab(const std::string &prefabName)
	{
		assert(_prefabList.find(prefabName) != _prefabList.end() && "No existe el prefab del que quieres obtener su GameObject");
		return _prefabList.at(prefabName)->gameObject;
	}

	Map::CEntity* CMap::getBodyFromPrefab(const std::string &prefabName)
	{
		assert(_prefabList.find(prefabName) != _prefabList.end() && "No existe el prefab del que quieres obtener su Body");
		return _prefabList.at(prefabName)->bodyEntity;
	}

	Map::CEntity* CMap::getShadowFromPrefab(const std::string &prefabName)
	{
		assert(_prefabList.find(prefabName) != _prefabList.end() && "No existe el prefab del que quieres obtener su Shadow");
		return _prefabList.at(prefabName)->shadowEntity;
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

	void CMap::tick(float msecs)
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

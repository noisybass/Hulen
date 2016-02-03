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

#include <cassert>

// HACK. Debería leerse de algún fichero de configuración
#define MAP_FILE_PATH "./media/maps/"

namespace Logic {
		
	CMap* CMap::createMapFromFile(const std::string &filename)
	{
		// Completamos la ruta con el nombre proporcionado
		std::string completePath(MAP_FILE_PATH);
		completePath = completePath + filename;
		// Parseamos el fichero
		if(!Map::CMapParser::getSingletonPtr()->parseFile(completePath))
		{
			assert(!"No se ha podido parsear el mapa.");
			return false;
		}

		// Si se ha realizado con éxito el parseo creamos el mapa.
		CMap *map = new CMap(filename);

		// Extraemos las entidades del parseo.
		Map::CMapParser::TEntityList entityList = 
			Map::CMapParser::getSingletonPtr()->getEntityList();

		CEntityFactory* entityFactory = CEntityFactory::getSingletonPtr();

		Map::CMapParser::TEntityList::const_iterator it, end;
		it = entityList.begin();
		end = entityList.end();

		// Creamos todas las entidades lógicas.
		for(; it != end; it++)
		{	
			assert((*it)->hasAttribute("type") && "Falta el atributo type");

			// Obtenemos el tipo
			std::string type = (*it)->getStringAttribute("type");

			if (!type.compare("Body") || !type.compare("Shadow"))
			{
				
				// La propia factoría se encarga de añadir la entidad a su GameObject
				CEntity* entity = entityFactory->createEntity((*it), map);
				assert(entity && "No se pudo crear una entidad perteneciente a un game object");
			}
			else if (!type.compare("GameObject"))
			{
				// La propia factoría se encarga de añadir el GameObject al mapa
				CGameObject* gameObject = entityFactory->createGameObject((*it), map);
				assert(gameObject && "No se pudo crear un game object del mapa");
			}
		}

		return map;

	} // createMapFromFile

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

	} // removeEntity

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

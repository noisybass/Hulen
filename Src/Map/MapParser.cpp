/**
@file MapParser.cpp

Contiene la implementación de la clase que encapsula el parseo de mapas.

@see Map::CMapParser

@author David Llansó García
@date Agosto, 2010
*/

#include <fstream>
#include <sstream>
#include <cassert>

#include "MapEntity.h"
#include "MapParser.h"
#include "scanner.h"

#include "BaseSubsystems\ScriptManager.h"

extern "C"
{
#include <lua.h>
}

namespace
{
	/**
	Cargar el mapa
	*/
	int lua_beginMapEntity(lua_State* l)
	{
		Map::CMapParser::getSingletonPtr()->setEntityInProgress(new Map::CEntity(lua_tostring(l, -1)));

		return 0;
	}

	int lua_addEntityAttrib(lua_State* l)
	{
		Map::CEntity* e = Map::CMapParser::getSingletonPtr()->getEntityInProgress();
		std::string key = lua_tostring(l, -2);

		if (key == "type")
		{
			e->setType(lua_tostring(l, -1));
		}
		else if (key == "blueprint"){
			e->setBlueprint(lua_tostring(l, -1));
		}
		else
		{
			if (lua_isboolean(l, -1))
			{
				e->setAttribute(lua_tostring(l, -2), lua_toboolean(l, -1)? "true" : "false");
			}
			else
			{
				e->setAttribute(lua_tostring(l, -2), lua_tostring(l, -1));
			}
		}

		return 0;
	}

	int lua_endMapEntity(lua_State* l)
	{

		Map::CMapParser::getSingletonPtr()->getEntityList()->push_back(Map::CMapParser::getSingletonPtr()->getEntityInProgress());

		Map::CMapParser::getSingletonPtr()->setEntityInProgress(nullptr);

		return 0;
	}


	/**
	Cargar los prefabs
	*/
	int lua_beginPrefabEntity(lua_State* l)
	{
		Map::CMapParser::getSingletonPtr()->setPrefabInProgress(new Map::CEntity(lua_tostring(l, -1)));

		return 0;
	}

	int lua_addPrefabAttrib(lua_State* l)
	{
		Map::CEntity* e = Map::CMapParser::getSingletonPtr()->getPrefabInProgress();
		std::string key = lua_tostring(l, -2);

		if (key == "type")
		{
			e->setType(lua_tostring(l, -1));
		}
		else if (key == "blueprint"){
			e->setBlueprint(lua_tostring(l, -1));
		}
		else
		{
			if (lua_isboolean(l, -1))
			{
				e->setAttribute(lua_tostring(l, -2), lua_toboolean(l, -1) ? "true" : "false");
			}
			else
			{
				e->setAttribute(lua_tostring(l, -2), lua_tostring(l, -1));
			}
		}

		return 0;
	}

	int lua_endPrefabEntity(lua_State* l)
	{
		Map::CEntity* s = Map::CMapParser::getSingletonPtr()->getPrefabInProgress();

		Map::CMapParser::getSingletonPtr()->getPrefabList()->push_back(Map::CMapParser::getSingletonPtr()->getPrefabInProgress());

		Map::CMapParser::getSingletonPtr()->setPrefabInProgress(nullptr);

		return 0;
	}

}

namespace Map {

	CMapParser* CMapParser::_instance = nullptr;

	//--------------------------------------------------------

	CMapParser::CMapParser(): _traceScanning(false),
							  _traceParsing(false),
							  _entityInProgress(nullptr),
							  _prefabInProgress(nullptr)
	{
		_instance = this;

		// Configuramos la parte de LUA
		ScriptManager::CScriptManager *sm = ScriptManager::CScriptManager::GetPtrSingleton();

		sm->loadScript("media/lua/MapParser.lua");
		sm->registerFunction(lua_beginMapEntity, "BeginMapEntity");
		sm->registerFunction(lua_endMapEntity, "EndMapEntity");
		sm->registerFunction(lua_addEntityAttrib, "AddEntityAttrib");
		sm->registerFunction(lua_beginPrefabEntity, "BeginPrefabEntity");
		sm->registerFunction(lua_endPrefabEntity, "EndPrefabEntity");
		sm->registerFunction(lua_addPrefabAttrib, "AddPrefabAttrib");

	} // CMapParser

	//--------------------------------------------------------

	CMapParser::~CMapParser()
	{
		releaseEntityList();
		releasePrefabList();
		_instance = 0;

	} // ~CMapParser
	
	//--------------------------------------------------------

	bool CMapParser::Init()
	{
		assert(!_instance && "Segunda inicialización de Map::CMapParser no permitida!");

		new CMapParser();
		return true;

	} // Init

	//--------------------------------------------------------

	void CMapParser::Release()
	{
		assert(_instance && "Map::CMapParser no está inicializado!");
		if(_instance)
		{
			delete _instance;
		}

	} // Release

	//--------------------------------------------------------

	bool CMapParser::parseStream(std::istream& in, const std::string& name)
	{
		_streamname = name;

		CScanner scanner(&in);
		scanner.set_debug(_traceScanning);
		_lexer = &scanner;

		releaseEntityList();
		CParser parser(*this);
		parser.set_debug_level(_traceParsing);
		return (parser.parse() == 0);
	} // parseStream

	//--------------------------------------------------------

	bool CMapParser::parseFile(const std::string &filename, const std::string &type)
	{
		ScriptManager::CScriptManager *sm = ScriptManager::CScriptManager::GetPtrSingleton();
		std::string orden;
		if (type == "Map"){
			orden = "loadMap(\"" + filename + "\")";
		}
		else if (type == "Prefab"){
			orden = "loadPrefab(\"" + filename + "\")";
		}
		sm->executeScript(orden.c_str());

		return true;

	} // parseFile

	//--------------------------------------------------------

	bool CMapParser::parseString(const std::string &input, const std::string& name)
	{
		std::istringstream iss(input);
		return parseStream(iss, name);
	} // parseString

	//--------------------------------------------------------

	void CMapParser::error(const class location& l,
			   const std::string& m)
	{
		std::cerr << l << ": " << m << std::endl;
	} // error

	//--------------------------------------------------------

	void CMapParser::error(const std::string& m)
	{
		std::cerr << m << std::endl;
	} // error

	//--------------------------------------------------------
		
	void CMapParser::releaseEntityList()
	{
		while(!_entityList.empty())
		{
			_entityInProgress = _entityList.back();
			_entityList.pop_back();
			delete _entityInProgress;
		}
	} // releaseEntityList

	//--------------------------------------------------------

	void CMapParser::releasePrefabList()
	{
		while (!_prefabList.empty())
		{
			_prefabInProgress = _prefabList.back();
			_prefabList.pop_back();
			delete _prefabInProgress;
		}
	} // releasePrefabList

} // namespace Map

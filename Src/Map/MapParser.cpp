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

#include "luabind\luabind.hpp"

namespace Probando
{
	void sayHello(const std::string& message)
	{
		//std::cout << "HELLOOOOOOOOOOOOOOO!!!" << std::endl;
		std::cout << message << std::endl;
	}

	/**
	Cargar el mapa
	*/
	void lua_beginMapEntity(const std::string& entityName)
	{	
		ScriptManager::CScriptManager *sm = ScriptManager::CScriptManager::GetPtrSingleton();

		Map::CMapParser::getSingletonPtr()->setEntityInProgress(new Map::CEntity(entityName));

	}

	void lua_addEntityAttrib(const std::string& name, const std::string& value)
	{
		ScriptManager::CScriptManager *sm = ScriptManager::CScriptManager::GetPtrSingleton();

		Map::CEntity* e = Map::CMapParser::getSingletonPtr()->getEntityInProgress();
		std::string key = name;

		if (key == "type")
		{
			e->setType(value);
		}
		else if (key == "blueprint"){
			e->setBlueprint(value);
		}
		else
		{
			e->setAttribute(name, value);
		}

	}

	void lua_endMapEntity(const std::string& entityName)
	{

		Map::CMapParser::getSingletonPtr()->getEntityList()->push_back(Map::CMapParser::getSingletonPtr()->getEntityInProgress());

		Map::CMapParser::getSingletonPtr()->setEntityInProgress(nullptr);

	}


	/**
	Cargar los prefabs
	*/
	void lua_beginPrefabEntity(const std::string& prefabName)
	{
		ScriptManager::CScriptManager *sm = ScriptManager::CScriptManager::GetPtrSingleton();

		Map::CMapParser::getSingletonPtr()->setPrefabInProgress(new Map::CEntity(prefabName));

	}

	void lua_addPrefabAttrib(const std::string& name, const std::string& value)
	{
		ScriptManager::CScriptManager *sm = ScriptManager::CScriptManager::GetPtrSingleton();

		Map::CEntity* e = Map::CMapParser::getSingletonPtr()->getPrefabInProgress();
		std::string key = name;

		if (key == "type")
		{
			e->setType(value);
		}
		else if (key == "blueprint"){
			e->setBlueprint(value);
		}
		else
		{
			e->setAttribute(name, value);
		}

	}

	void lua_endPrefabEntity(const std::string& prefabName)
	{
		Map::CEntity* s = Map::CMapParser::getSingletonPtr()->getPrefabInProgress();

		Map::CMapParser::getSingletonPtr()->getPrefabList()->push_back(Map::CMapParser::getSingletonPtr()->getPrefabInProgress());

		Map::CMapParser::getSingletonPtr()->setPrefabInProgress(nullptr);

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

		sm->loadScript("media/lua/script.lua");
		sm->loadScript("media/lua/MapParser.lua");
		

		luabind::module(sm->_lua)
			[
				luabind::def("BeginMapEntity", &Probando::lua_beginMapEntity),
				luabind::def("EndMapEntity", &Probando::lua_endMapEntity),
				luabind::def("AddEntityAttrib", &Probando::lua_addEntityAttrib),
				luabind::def("BeginPrefabEntity", &Probando::lua_beginPrefabEntity),
				luabind::def("EndPrefabEntity", &Probando::lua_endPrefabEntity),
				luabind::def("AddPrefabAttrib", &Probando::lua_addPrefabAttrib),
				luabind::def("SayHello", &Probando::sayHello)
			];
		/*sm->registerFunction(lua_beginMapEntity, "BeginMapEntity");
		sm->registerFunction(lua_endMapEntity, "EndMapEntity");
		sm->registerFunction(lua_addEntityAttrib, "AddEntityAttrib");
		sm->registerFunction(lua_beginPrefabEntity, "BeginPrefabEntity");
		sm->registerFunction(lua_endPrefabEntity, "EndPrefabEntity");
		sm->registerFunction(lua_addPrefabAttrib, "AddPrefabAttrib");*/

		

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
		const char* aux = orden.c_str();
		//sm->executeScript("decirHola(\"MENSAJE\")");
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

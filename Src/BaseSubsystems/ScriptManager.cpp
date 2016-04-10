//---------------------------------------------------------------------------
// ScriptManager.cpp
//---------------------------------------------------------------------------

/**
 * @file ScriptManager.cpp
 *
 * Contiene la definición de la clase que oculta la
 * gestión de los scripts en Lua.
 *
 * @see Scriptmanager::CScriptManager
 *
 * @author Pedro Pablo y Marco Antonio Gómez Martín
 * @date Enero, 2011
 */

#include "ScriptManager.h"

#include <cassert>
#include <iostream> // Mensajes de error

#include "BaseSubsystems/StateMachine.h"
#include "BaseSubsystems/FSMAgent.h"
#include "BaseSubsystems/FSMCrawler.h"

namespace ScriptManager {

// Única instancia de la clase.
CScriptManager *CScriptManager::_instance = 0;


bool CScriptManager::Init() {

	assert(_instance == NULL);
	_instance = new CScriptManager();
	if (!_instance->open()) {
		// ¡¡Vaya!!
		Release();
		return false;
	}

	return true;

} // Init

//---------------------------------------------------------

void CScriptManager::Release() {

	assert(_instance);

	delete _instance;
	_instance = NULL;

} // Release

//---------------------------------------------------------

CScriptManager &CScriptManager::GetSingleton() {

	assert(_instance);

	return *_instance;

} // GetSingleton

//---------------------------------------------------------

CScriptManager *CScriptManager::GetPtrSingleton() {

	assert(_instance);

	return _instance;

} // GetPtrSingleton

//---------------------------------------------------------

bool CScriptManager::loadScript(const char *script) {

	assert(_lua);

	if (luaL_loadfile(_lua, script) != 0) {
		std::cout << "ScriptManager WARNING: error de sintaxis en el fichero " << script << std::endl;
		return false;
	}

	if (lua_pcall(_lua, 0, 0, 0) != 0) {
		std::cout << "Error en la ejecución de " << script << ": " <<
			lua_tostring(_lua, -1) << std::endl;
		lua_pop(_lua, 1);
		return false;
	}

	return true;

} // loadScript

//---------------------------------------------------------

bool CScriptManager::executeScript(const char *script) {

	assert(_lua);

	if (luaL_loadstring(_lua, script) != 0)
		// Devuelve 0 si todo va bien, y 0 en otro caso
		// con un código de error, que ignoramos.
		return false;

	lua_call(_lua, 0, 0);

	return true;

} // executeScript

//---------------------------------------------------------

int CScriptManager::getGlobal(const char *name, int defaultValue) {

	assert(_lua);

	luabind::object obj = luabind::globals(_lua)[name];

	if (!obj.is_valid() || luabind::type(obj) != LUA_TNUMBER)
		return defaultValue;
	else
		return luabind::object_cast<int>(obj);

} // getGlobal(int)

//---------------------------------------------------------

bool CScriptManager::getGlobal(const char *name, bool defaultValue) {
	
	assert(_lua);

	luabind::object obj = luabind::globals(_lua)[name];

	if (!obj.is_valid() || luabind::type(obj) != LUA_TBOOLEAN)
		return defaultValue;
	else
		return luabind::object_cast<bool>(obj);

} // getGlobal(bool)

//---------------------------------------------------------

std::string CScriptManager::getGlobal(const char *name,
                                const char *defaultValue) {

	assert(_lua);

	luabind::object obj = luabind::globals(_lua)[name];

	if (!obj.is_valid() || luabind::type(obj) != LUA_TSTRING)
		return defaultValue;
	else
		return luabind::object_cast<const char*>(obj);

} // getGlobal(char*)

//---------------------------------------------------------

int CScriptManager::getField(const char *table,
                             const char *field,
                             int defaultValue) {


	assert(_lua);

#ifdef _DEBUG
	int topLua = lua_gettop(_lua);
#endif

	int result;

	// Tenemos que conseguir una referencia a la
	// tabla en la cima de la pila de Lua. La tabla
	// es una variable global...
	lua_getglobal(_lua, table);

	if (!lua_istable(_lua, -1)) {
		// Vaya, pues la tabla no existe (o no es
		// una tabla).
		result = defaultValue;
		// Limpiamos la pila
		lua_pop(_lua, 1);
	}
	else {
		// Tenemos la tabla. Ahora apilamos el
		// nombre del campo (índice).
		lua_pushstring(_lua, field);

		// Para acceder a un campo se usa lua_gettable(lua_state, index).
		// Mira en la posición index de la tabla Lua, y ahí espera
		// encontrar la tabla de donde leer. El nombre del campo
		// al que acceder lo saca de la cima, lo desapila, y
		// apila el valor.
		// Ahora en la pila tenemos en la cima (índice -1)
		// el campo (acabamos de apilarlo).
		// Debajo (índice -2) tenemos la referencia a la tabla
		// a la que queremos acceder.
		lua_gettable(_lua, -2);
		// Fijate que en la pila el único cambio está en la cima:
		// el índice se sustituye por el valor. Pero la referencia
		// a la tabla NO SE TOCA (podría de hecho estar muy
		// profunda en la pila de Lua... pues estamos dando
		// directamente el índice en la pila a su posición).

		// En la cima tendremos el valor.
		if (!lua_isnumber(_lua, -1))
			result = defaultValue;
		else
			result = (int) lua_tonumber(_lua, -1);

		// Limpiamos la pila. Hay que quitar el valor conseguido,
		// y la referencia a la tabla.
		lua_pop(_lua, 2);
	} // if-else la tabla existía

	// sanity-check: no dejamos nada en la cima de la pila...
	// (recuerda que assert sólo compila el interior en modo debug)
	assert(lua_gettop(_lua) == topLua);

	return result;

} // getField(int)

//---------------------------------------------------------

bool CScriptManager::getField(const char *table,
                             const char *field,
                             bool defaultValue) {


	assert(_lua);

#ifdef _DEBUG
	int topLua = lua_gettop(_lua);
#endif

	bool result;

	// Tenemos que conseguir una referencia a la
	// tabla en la cima de la pila de Lua. La tabla
	// es una variable global...
	lua_getglobal(_lua, table);

	if (!lua_istable(_lua, -1)) {
		// Vaya, pues la tabla no existe (o no es
		// una tabla).
		result = defaultValue;
		// Limpiamos la pila
		lua_pop(_lua, 1);
	}
	else {
		// Tenemos la tabla. Ahora apilamos el
		// nombre del campo (índice).
		lua_pushstring(_lua, field);

		// Para acceder a un campo se usa lua_gettable(lua_state, index).
		// Mira en la posición index de la tabla Lua, y ahí espera
		// encontrar la tabla de donde leer. El nombre del campo
		// al que acceder lo saca de la cima, lo desapila, y
		// apila el valor.
		// Ahora en la pila tenemos en la cima (índice -1)
		// el campo (acabamos de apilarlo).
		// Debajo (índice -2) tenemos la referencia a la tabla
		// a la que queremos acceder.
		lua_gettable(_lua, -2);
		// Fijate que en la pila el único cambio está en la cima:
		// el índice se sustituye por el valor. Pero la referencia
		// a la tabla NO SE TOCA (podría de hecho estar muy
		// profunda en la pila de Lua... pues estamos dando
		// directamente el índice en la pila a su posición).

		// En la cima tendremos el valor.
		if (!lua_isboolean(_lua, -1))
			result = defaultValue;
		else
			result = lua_toboolean(_lua, -1)==0?false:true;

		// Limpiamos la pila. Hay que quitar el valor conseguido,
		// y la referencia a la tabla.
		lua_pop(_lua, 2);
	} // if-else la tabla existía

	// sanity-check: no dejamos nada en la cima de la pila...
	// (recuerda que assert sólo compila el interior en modo debug)
	assert(lua_gettop(_lua) == topLua);

	return result;

} // getField(bool)

//---------------------------------------------------------


std::string CScriptManager::getField(const char *table,
                               const char *field,
                               const char *defaultValue) {


	size_t len;
	assert(_lua);

#ifdef _DEBUG
	int topLua = lua_gettop(_lua);
#endif

	const char *result; // Antes de hacer la copia.
	std::string ret;

	// Tenemos que conseguir una referencia a la
	// tabla en la cima de la pila de Lua. La tabla
	// es una variable global...
	lua_getglobal(_lua, table);

	if (!lua_istable(_lua, -1)) {
		// Vaya, pues la tabla no existe (o no es
		// una tabla).
		result = defaultValue;
		// Hacemos la copia. La hacemos antes de quitar
		// el elemento de la pila, porque Lua podría decidir
		// recoger la basura y liberar la cadena result.
		ret = std::string(result);

		// Limpiamos la pila
		lua_pop(_lua, 1);
	}
	else {
		// Tenemos la tabla. Ahora apilamos el
		// nombre del campo (índice).
		lua_pushstring(_lua, field);

		// Para acceder a un campo se usa lua_gettable(lua_state, index).
		// Mira en la posición index de la tabla Lua, y ahí espera
		// encontrar la tabla de donde leer. El nombre del campo
		// al que acceder lo saca de la cima, lo desapila, y
		// apila el valor.
		// Ahora en la pila tenemos en la cima (índice -1)
		// el campo (acabamos de apilarlo).
		// Debajo (índice -2) tenemos la referencia a la tabla
		// a la que queremos acceder.
		lua_gettable(_lua, -2);
		// Fijate que en la pila el único cambio está en la cima:
		// el índice se sustituye por el valor. Pero la referencia
		// a la tabla NO SE TOCA (podría de hecho estar muy
		// profunda en la pila de Lua... pues estamos dando
		// directamente el índice en la pila a su posición).

		// En la cima tendremos el valor.
		if (!lua_isstring(_lua, -1))
			result = defaultValue;
		else {
			result = lua_tolstring(_lua, -1, &len);

			// lua_tolstring siempre nos pone el \0
			// al final, pero podría haber alguno más
			// por el medio.
			// Si es así, entonces strlen(result)
			// (que busca el \0) parará "antes de
			// tiempo" y habrá diferencias en las
			// longitudes apreciables.
			assert(len == strlen(result));
		}

		// Hacemos la copia. La hacemos antes de quitar
		// el elemento de la pila, porque Lua podría decidir
		// recoger la basura y liberar la cadena result.
		ret = std::string(result);

		// Limpiamos la pila. Hay que quitar el valor conseguido,
		// y la referencia a la tabla.
		lua_pop(_lua, 2);
	} // if-else la tabla existía

	// sanity-check: no dejamos nada en la cima de la pila...
	// (recuerda que assert sólo compila el interior en modo debug)
	assert(lua_gettop(_lua) == topLua);

	return ret;

} // getField(char*)

//---------------------------------------------------------

bool CScriptManager::executeProcedure(const char *subroutineName) {

	assert(_lua);

	luabind::object obj = luabind::globals(_lua)[subroutineName];

	if (!obj.is_valid() || luabind::type(obj) != LUA_TFUNCTION)
		return false;

	obj();

	return true;

} // executeProcedure


//---------------------------------------------------------

bool CScriptManager::executeProcedure(const char *subroutineName, int param1) {

	assert(_lua);

	try
	{
		luabind::globals(_lua)[subroutineName](param1);
	}
	catch (luabind::error& ex)
	{
		std::cout << ex.what() << std::endl;
		return false;
	}

	return true;

} // executeProcedure(int)

//---------------------------------------------------------

bool CScriptManager::executeFunction(const char *subroutineName,
                                     int param1, int &result) {

	assert(_lua);

	try
	{
		luabind::object res = luabind::globals(_lua)[subroutineName](param1);

		if (!res.is_valid() || luabind::type(res) != LUA_TNUMBER)
			return false;

		result = luabind::object_cast<int>(res);
	}
	catch (luabind::error& ex)
	{
		std::cout << ex.what() << std::endl;
		return false;
	}

	return true;

} // executeFunction

//---------------------------------------------------------

void CScriptManager::registerFunction(lua_CFunction f, const char *luaName) {

	assert(_lua);

	lua_register(_lua, luaName, f);

} // registerFunction

//---------------------------------------------------------
//                   Métodos protegidos
//---------------------------------------------------------

CScriptManager::CScriptManager() : _lua(NULL) {

} // Constructor

//---------------------------------------------------------

CScriptManager::~CScriptManager() {

	close();

} // Destructor

//---------------------------------------------------------

bool CScriptManager::open() {

	_lua = lua_open();

	if (!_lua)
		return false;

	// Abrimos la librería base para hacer disponible
	// print() en Lua.
	luaopen_base(_lua);

	luabind::open(_lua);

	// Cargamos el script del estado de prueba
	if (!loadScript("media/lua/states.lua"))
		std::cout << "No se ha cargado states.lua correctamente" << std::endl;

	// Registramos las funciones de la clase FSMEntity y de la máquina de estados
	luabind::module(_lua)
		[
			/*luabind::class_<AI::FSMAgent>("FSMAgent")
			.def("SayHello", &AI::FSMAgent::sayHello)
			.def("GetFSM", &AI::FSMAgent::getFSM),*/

			luabind::class_<AI::FSMCrawler>("Crawler")
			.def("SeeingPlayer", &AI::FSMCrawler::seeingPlayer)
			.def("ChangeState", &AI::FSMCrawler::changeState)
			.def("GetFSM", &AI::FSMCrawler::getFSM),

			/*luabind::class_<AI::StateMachine<AI::FSMAgent> >("StateMachine")
			.def("ChangeState", &AI::StateMachine<AI::FSMAgent>::changeState)
			.def("GetCurrentState", &AI::StateMachine<AI::FSMAgent>::getCurrentState)
			.def("SetCurrentState", &AI::StateMachine<AI::FSMAgent>::setCurrentState),*/

			luabind::class_<AI::StateMachine<AI::FSMCrawler> >("CrawlerStateMachine")
			.def("ChangeState", &AI::StateMachine<AI::FSMCrawler>::changeState)
			.def("GetCurrentState", &AI::StateMachine<AI::FSMCrawler>::getCurrentState)
			.def("SetCurrentState", &AI::StateMachine<AI::FSMCrawler>::setCurrentState)
		];

	return true;

} // open

//---------------------------------------------------------

void CScriptManager::close() {

	if (_lua)
		lua_close(_lua);

} // close

} // namespace ScriptManager


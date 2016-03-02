//---------------------------------------------------------------------------
// ScriptManager.h
//---------------------------------------------------------------------------

/**
 * @file ScriptManager.h
 *
 * Contiene la declaración de la clase que oculta la
 * gestión de los scripts en Lua.
 *
 * @see Scriptmanager::CScriptManager
 *
 * @author Pedro Pablo y Marco Antonio Gómez Martín
 * @date Enero, 2011
 */

#ifndef __ScriptManager_ScriptManager_H
#define __ScriptManager_ScriptManager_H

// Predeclaración de clases para ahorrar tiempo de compilación
// al ahorrarnos la inclusión de ficheros .h en otros .h

// Estructura con el contexto (estado) del intérprete de Lua.
struct lua_State;

typedef int (*lua_CFunction) (lua_State *L);

#include <string>

namespace ScriptManager {

/**
 * Clase principal del gestor de script (en Lua) de Galeon.
 * Es el responsable de inicializar y cerrar el contexto de
 * Lua, y proporciona funcionalidad para cargar <em>scripts</em>
 * de Lua, ejecutar código, acceder a variables y tablas,
 * etcétera.
 *
 * Funciona como un <em>singleton</em> de inicialización
 * explicita; es necesario invocar a Init() al inicio (antes
 * de usarlo), y llamar a Release() al terminar.
 */
class CScriptManager {
public:

	/**
	 * Método estático para inicializar el <em>singleton</em>.
	 * Debe ser invocado antes de hacer uso de la clase
	 * (llamando a GetSingleton() o GetPtrSingleton().
	 *
	 * @return Cierto si todo fue bien, y falso en otro caso.
	 * Si hay algún problema, el objeto <em>no podrá usarse</em>.
	 */
	static bool Init();

	/**
	 * Destruye la única instancia del objeto. Debe llamarse
	 * al terminar si Init() acabó con éxito. Tras su
	 * invocación, no podrá utilizarse GetSingleton() o
	 * GetPtrSingleton() salvo que se llame de nuevo a Init().
	 */
	static void Release();

	/**
	 * Devuelve la única instancia posible de esta clase.
	 * Debe haberse llamado previamente a Init() con éxito
	 * (y no haberse llamado a Release()).
	 *
	 * @return Única instancia de la clase.
	 */
	static CScriptManager &GetSingleton();

	/**
	 * Devuelve la única instancia posible de esta clase.
	 * Debe haberse llamado previamente a Init() con éxito
	 * (y no haberse llamado a Release()).
	 *
	 * @return Única instancia de la clase.
	 */
	static CScriptManager *GetPtrSingleton();

	/**
	 * Carga un fichero con un <em>script</em> de Lua,
	 * y lo ejecuta.
	 *
	 * @param file Nombre del fichero a cargar (y ejecutar).
	 * @return Cierto si todo fue bien, y falso en otro
	 * caso.
	 *
	 * @note Esta función es bastante mejorable. Si
	 * quisiéramos hacer un gestor de scripts serio, la
	 * clase debería controlar qué scripts han sido ya
	 * cargados y no volver a cargar por segunda vez
	 * aquellos que se solicitaron previamente.
	 *
	 * Además, para permitir la recarga de ficheros ya
	 * cargados ("actualizaciones en caliente"), algo
	 * útil en depuración en producción para hacer
	 * cambios rápidos sin tener que recompilar o
	 * volver a ejecutar, añadiríamos un método nuevo
	 * como reloadScript() para recargar uno, o
	 * reloadScripts() para recargarlos todos.
	 *
	 * Con la inclusión de executeScript() habría que
	 * indicar que los scripts ejecutados en modo
	 * inmediato <em>no</em> se volverían a ejecutar...
	 *
	 * @note Otro punto de mejora es la gestión de
	 * errores. Internamente se utiliza
	 * <tt>lua_call()</tt>, que no permite un
	 * control sencillo de los errores. Si el código
	 * Lua tiene algún error, la aplicación en C
	 * <em>acaba inmediatamente</em>. Una mejora clara
	 * sería hacer uso de <tt>lua_pcall()</tt> y
	 * una gestión más fina de los errores. La clase
	 * llevaría la pista del último error que se ha
	 * producido, pudiendo devolver una cadena
	 * explicativa por ejemplo. Esto queda fuera
	 * del objetivo de la clase.
	 */
	bool loadScript(const char *script);

	/**
	 * Ejecuta el script inmediato recibido en la cadena
	 * del parámetro.
	 *
	 * @param script Código Lua que queremos ejecutar.
	 * @return Cierto si se pudo ejecutar.
	 *
	 * @note Igual que en loadScript() un punto de
	 * mejora es la gestión de errores. Ahora mismo se
	 * devuelve falso sólo si hay un error de sintáxis.
	 * Si hay algún error en ejecución... ¡¡se cierra el
	 * programa!!
	 */
	bool executeScript(const char *script);

	/**
	 * Obtiene el valor de una variable global en Lua
	 * de tipo numérico a partir de su nombre.
	 *
	 * @param name Nombre de la variable global que
	 * se quiere obtener.
	 * @param defaultValue Valor que se devolverá 
	 * si no existe esa variable global en Lua.
	 *
	 * @return Valor de la variable global de Lua, 
	 * o <tt>defaultValue</tt> si no existía.
	 *
	 * @note En Lua el tipo numérico es en principio
	 * <tt>double</tt>. Aquí sin embargo devolvemos
	 * un entero.
	 */
	int getGlobal(const char *name, int defaultValue);

	/**
	 * Obtiene el valor de una variable global en Lua
	 * de tipo boolean a partir de su nombre.
	 *
	 * @param name Nombre de la variable global que
	 * se quiere obtener.
	 * @param defaultValue Valor que se devolverá 
	 * si no existe esa variable global en Lua.
	 *
	 * @return Valor de la variable global de Lua, 
	 * o <tt>defaultValue</tt> si no existía.
	 */
	bool getGlobal(const char *name, bool defaultValue);

	/**
	 * Obtiene el valor de una variable global en Lua
	 * de tipo cadena a partir de su nombre.
	 *
	 * @param name Nombre de la variable global que
	 * se quiere obtener.
	 * @param defaultValue Valor que se devolverá 
	 * si no existe esa variable global en Lua.
	 *
	 * @return Valor de la variable global de Lua, 
	 * o <tt>defaultValue</tt> si no existía.
	 *
	 * @note Esta función tiene un peligro potencial;
	 * Lua soporta cadenas con <tt>'\\0'</tt> en su
	 * interior. Aquí <em>asumiremos que no lo tienen</em>
	 * porque usamos el <tt>'\\0'</tt> como marca de
	 * fin de cadena por simplicidad.
	 * En modo debug se comprueba (con <tt>assert</tt>) que
	 * la cadena devuelta por Lua no tiene <tt>'\\0'</tt>
	 * dentro, pero esta comprobación no es tampoco muy
	 * fiable, porque un script se puede cambiar a
	 * posteriori cuando ya sólo se usa la versión release...
	 */
	std::string getGlobal(const char *name, const char *defaultValue);

	/**
	 * Obtiene el valor de un campo de tipo numérico de
	 * una tabla global.
	 *
	 * @param table Nombre de la tabla (global) a la que
	 * acceder.
	 * @param field Nombre del campo (índice) cuyo valor se
	 * desea obtener.
	 * @param defaultValue Valor que se devolverá 
	 * si no existe la tabla o ese campo (índice) no
	 * es de tipo numérico (o no hay una conversión posible).
	 *
	 * @return Valor del campo solicitado, 
	 * o <tt>defaultValue</tt> si no existía.
	 *
	 * @note En Lua el tipo numérico es en principio
	 * <tt>double</tt>. Aquí sin embargo devolvemos
	 * un entero.
	 */
	int getField(const char *table, const char *field, int defaultValue);

	/**
	 * Obtiene el valor de un campo de tipo booleano de
	 * una tabla global.
	 *
	 * @param table Nombre de la tabla (global) a la que
	 * acceder.
	 * @param field Nombre del campo (índice) cuyo valor se
	 * desea obtener.
	 * @param defaultValue Valor que se devolverá 
	 * si no existe la tabla o ese campo (índice) no
	 * es de tipo booleano (o no hay una conversión posible).
	 *
	 * @return Valor del campo solicitado, 
	 * o <tt>defaultValue</tt> si no existía.
	 */
	bool getField(const char *table, const char *field, bool defaultValue);

	/**
	 * Obtiene el valor de un campo de tipo cadena de
	 * una tabla global.
	 *
	 * @param table Nombre de la tabla (global) a la que
	 * acceder.
	 * @param field Nombre del campo (índice) cuyo valor se
	 * desea obtener.
	 * @param defaultValue Valor que se devolverá 
	 * si no existe la tabla o ese campo (índice) no
	 * es de tipo booleano (o no hay una conversión posible).
	 *
	 * @return Valor del campo solicitado, 
	 * o <tt>defaultValue</tt> si no existía.
	 *
	 * @note Esta función tiene un peligro potencial;
	 * Lua soporta cadenas con <tt>'\\0'</tt> en su
	 * interior. Aquí <em>asumiremos que no lo tienen</em>
	 * porque usamos el <tt>'\\0'</tt> como marca de
	 * fin de cadena por simplicidad.
	 * En modo debug se comprueba (con <tt>assert</tt>) que
	 * la cadena devuelta por Lua no tiene <tt>'\\0'</tt>
	 * dentro, pero esta comprobación no es tampoco muy
	 * fiable, porque un script se puede cambiar a
	 * posteriori cuando ya sólo se usa la versión release...
	 */
	std::string getField(const char *table, const char *field, const char *defaultValue);


	bool executeProcedure(const char *subroutineName);

	bool executeProcedure(const char *subroutineName, int param1);

	bool executeFunction(const char *subroutineName, int param1, int &result);


	/**
	 * Registra una función en el contexto de Lua.
	 *
	 * @param f Puntero a la función de C. Deberá recibir como
	 * parámetro un contexto de Lua (para poder acceder a la pila
	 * de Lua), y devolver el número de valores devueltos (en la
	 * pila de Lua)
	 * @param luaName Nombre Lua con el que se conocerá a la
	 * función (que será global).
	 */
	void registerFunction(lua_CFunction f, const char *luaName);

	lua_State *getNativeInterpreter() { return _lua; }

protected:

	/**
	 * Constructor. La inicialización se realiza
	 * en dos pasos; es necesario invocar a open() tras
	 * crear el objeto. En open() se realizan las acciones
	 * que pueden fallar, de manera que devolverá falso
	 * si hay problemas (algo que el constructor no
	 * podría hacer).
	 *
	 * No obstante, ni el constructor ni open() serán
	 * usados por los clientes de la clase. Ambos
	 * son protegidos dado que la clase funciona como
	 * un <em>singleton</em>. Deberá usarse Init()
	 * en su lugar.
	 */
	CScriptManager();

	/**
	 * Destructor. Libera los recursos.
	 *
	 * Es protegido porque los clientes no podrán destruir
	 * el objeto. En su lugar deben usar Release().
	 */
	~CScriptManager();

	/**
	 * Segunda fase de la inicialización del objeto.
	 * Es llamado automáticamente desde el método
	 * estático Init() para que el usuario no tenga
	 * que preocuparse.
	 *
	 * @return Cierto si todo fue bien, y falso si hubo
	 * algún problema. El objeto <em>no</em> debería usarse
	 * en ese caso, y debería ser destruído.
	 */
	bool open();

	/**
	 * Método inverso a open(). Es llamado automáticamente
	 * desde el destructor.
	 */
	void close();

	/**
	 * Única instancia (singleton) de la clase.
	 * Se inicializa en Init() y se destruye en Release().
	 */
	static CScriptManager *_instance;

	/**
	 * Contexto (intérprete) de Lua usado.
	 */
	lua_State *_lua;

}; // class CScriptManager

} // namespace ScriptManager

#endif // __ScriptManager_ScriptManager_H
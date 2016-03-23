#include "FSMEntity.h"

#include "BaseSubsystems\ScriptManager.h"

extern "C"
{
#include <lua.h>
}

#include <luabind\luabind.hpp>

namespace Logic
{
	IMP_FACTORY(CFSMEntity);

	bool CFSMEntity::spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		registerFSMEntity();

		return true;

	} // spawn

	void CFSMEntity::tick(unsigned int msecs)
	{
		_FSM->update();

	} // tick

	void CFSMEntity::sayHello()
	{
		std::cout << "Hello!!" << std::endl;

	} // sayHello

	void CFSMEntity::registerFSMEntity()
	{
		std::cout << "Registrando funciones del componente..." << std::endl;

		/*lua_State* lua = ScriptManager::CScriptManager::GetPtrSingleton()->getNativeInterpreter();

		luabind::module(lua)
			[
				luabind::class_<CFSMEntity>("CFSMEntity")
				.def("SayHello", &CFSMEntity::sayHello)
				.def("GetFSM", &CFSMEntity::getFSM)
			];*/

	} // registerFSMEntity

} // namespace Logic
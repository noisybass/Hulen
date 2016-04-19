#include "Chase.h"

#include "Logic/Entity/Components/MoveController.h"

namespace Logic
{

	IMP_FACTORY(CChase);

	bool CChase::spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

	} // spawn

	bool CChase::activate()
	{
		std::cout << "ACTIVANDO CHASE..." << std::endl;
		_active = true;

		_target = _entity->getGameObject()->getMap()->getGameObjectByName("Player_GO")->getBody();

		return true;

	} // activate

	void CChase::deactivate()
	{
		std::cout << "DESACTIVANDO CHASE..." << std::endl;
		_active = false;

		_target = nullptr;

	} // deactivate

	void CChase::tick(unsigned int msecs)
	{
		if (_active)
		{
			CMoveController* moveController = (CMoveController*)_entity->getComponent("CMoveController");

			moveController->nextPosition(_target->getPosition());
		}
	}

} // namespace Logic
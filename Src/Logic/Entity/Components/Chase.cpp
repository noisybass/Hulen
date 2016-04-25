#include "Chase.h"

#include "Logic/Entity/Components/MoveController.h"

namespace Logic
{

	IMP_FACTORY(CChase);

	CChase::CChase() : IComponent(), _target(nullptr)
	{

	} // CChase

	bool CChase::spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		_active = false;

	} // spawn

	bool CChase::activate()
	{
		IComponent::activate();

		std::cout << "ACTIVANDO CHASE..." << std::endl;

		_target = _entity->getGameObject()->getMap()->getGameObjectByName("Player_GO")->getBody();

		return true;

	} // activate

	void CChase::deactivate()
	{
		IComponent::deactivate();

		std::cout << "DESACTIVANDO CHASE..." << std::endl;

		_target = nullptr;

	} // deactivate

	void CChase::tick(float msecs)
	{
		if (_active)
		{
			CMoveController* moveController = (CMoveController*)_entity->getComponent("CMoveController");

			moveController->nextPosition(_target->getPosition());
		}
	}

} // namespace Logic
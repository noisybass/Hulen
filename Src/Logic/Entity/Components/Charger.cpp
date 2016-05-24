#include "Charger.h"

namespace Logic
{

	IMP_FACTORY(CCharger);

	CCharger::CCharger() : CState(), _speed(0.0f), _gravity(0.0f)
	{

	} // CCharger

	bool CCharger::spawn(const std::string& name, CEntity *entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		if (entityInfo->hasAttribute("speed"))
			_speed = entityInfo->getFloatAttribute("speed");

		if (entityInfo->hasAttribute("gravity"))
			_gravity = entityInfo->getFloatAttribute("gravity");

		return true;

	} // spawn

	void CCharger::enterState()
	{
		std::cout << "ACTIVANDO CHARGER..." << std::endl;

		CState::enterState();

	} // enterState

	void CCharger::exitState()
	{
		std::cout << "DESACTIVANDO CHASE..." << std::endl;

		CState::exitState();

	} // exitState

	void CCharger::tick(float msecs)
	{
		IComponent::tick(msecs);
		if (_executing)
		{
			Vector3 movement = Vector3(_entity->getDirection(), 0, 0) * _speed * msecs;
			// Acción de la gravedad
			movement += msecs * Vector3(0.0f, -_gravity, 0.0f);

			TMessage message;
			message._type = Message::AVATAR_WALK;
			message.setArg<Vector3>(std::string("movement"), movement);

			_entity->emitMessage(message);
		}
		
	} // tick

} // namespace Logic
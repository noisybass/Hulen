#include "KasaiController.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/GameObject.h"
#include "Map/MapEntity.h"

namespace Logic
{
	IMP_FACTORY(CKasaiController);

	//---------------------------------------------------------

	CKasaiController::CKasaiController()
		: _isVisible(true)
	{

	} // CKasaiController

	//---------------------------------------------------------

	bool CKasaiController::spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(entity, map, entityInfo))
			return false;

		if (entityInfo->hasAttribute("is_visible"))
			_isVisible = entityInfo->getBoolAttribute("is_visible");

		return true;

	} // spawn

	//---------------------------------------------------------

	bool CKasaiController::activate()
	{
		return true;

	} // activate

	//---------------------------------------------------------

	void CKasaiController::deactivate()
	{
		
	} // deactivate

	//---------------------------------------------------------

	bool CKasaiController::accept(const TMessage &message)
	{
		return message._type == Message::KASAI_MOVE ||
			message._type == Message::KASAI_SET_VISIBLE ||
			message._type == Message::TOUCHED ||
			message._type == Message::UNTOUCHED;
	} // accept

	//---------------------------------------------------------


	void CKasaiController::process(const TMessage &message)
	{
		TMessage m;
		switch (message._type)
		{
		case Message::KASAI_MOVE:
			m._type = Message::LIGHT_SET_POSITION;
			m._vector3 = message._vector3;
			_entity->emitMessage(m);

			m._type = Message::KINEMATIC_MOVE;
			m._vector3 = message._vector3 - _entity->getPosition();
			
			// Si nadie captura el mensaje significa que no hay componente físico,
			// así que movemos la entidad nosotros
			if (!_entity->emitMessage(m)) 
			{
				_entity->setPosition(message._vector3);
			}
			break;
		case Message::KASAI_SET_VISIBLE:
			_isVisible = !_isVisible;
			m._type = Message::LIGHT_SET_VISIBLE;
			m._bool = _isVisible;
			
			_entity->emitMessage(m);
			break;
		case Message::TOUCHED:
			if (message._entity->getGameObject()->isPlayer() && message._entity->getType() == Entity::TEntityType::BODY)
			{
				m._type = Message::PLAYER_ENTER_LIGHT;
				message._entity->emitMessage(m);
			}
			break;
		case Message::UNTOUCHED:
			if (message._entity->getGameObject()->isPlayer() && message._entity->getType() == Entity::TEntityType::BODY)
			{
				m._type = Message::PLAYER_OUT_LIGHT;
				message._entity->emitMessage(m);
			}
			break;
		}
	} // process

	//---------------------------------------------------------

} // namespace Logic
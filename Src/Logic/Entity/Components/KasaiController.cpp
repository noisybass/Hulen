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
		Vector3 newPosition;
		switch (message._type)
		{
		case Message::KASAI_MOVE:
			m._type = Message::LIGHT_SET_POSITION;
			newPosition = message.getArg<Vector3>("newPosition");
			m.setArg<Vector3>(std::string("newPosition"), newPosition);
			_entity->emitMessage(m);

			m._type = Message::KINEMATIC_MOVE;
			m.setArg<Vector3>(std::string("movement"), newPosition - _entity->getPosition());
			
			// Si nadie captura el mensaje significa que no hay componente físico,
			// así que movemos la entidad nosotros
			if (!_entity->emitMessage(m)) 
			{
				_entity->setPosition(newPosition);
			}
			break;
		case Message::KASAI_SET_VISIBLE:
			_isVisible = !_isVisible;
			m._type = Message::LIGHT_SET_VISIBLE;
			m.setArg<bool>(std::string("visibility"), _isVisible);
			
			_entity->emitMessage(m);
			break;
		case Message::TOUCHED:
			if (message.getArg<CEntity*>("entity")->getGameObject()->isPlayer() 
				&& message.getArg<CEntity*>("entity")->getType() == Entity::TEntityType::BODY)
			{
				m._type = Message::PLAYER_ENTER_LIGHT;
				message.getArg<CEntity*>("entity")->emitMessage(m);
			}
			break;
		case Message::UNTOUCHED:
			if (message.getArg<CEntity*>("entity")->getGameObject()->isPlayer() 
				&& message.getArg<CEntity*>("entity")->getType() == Entity::TEntityType::BODY)
			{
				m._type = Message::PLAYER_OUT_LIGHT;
				message.getArg<CEntity*>("entity")->emitMessage(m);
			}
			break;
		}
	} // process

	//---------------------------------------------------------

} // namespace Logic
#include "KasaiController.h"

#include "Logic/Entity/Entity.h"
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
			message._type == Message::KASAI_SET_VISIBLE;
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
			break;
		case Message::KASAI_SET_VISIBLE:
			_isVisible = !_isVisible;
			m._type = Message::LIGHT_SET_VISIBLE;
			m._bool = _isVisible;
			
			_entity->emitMessage(m);
			break;
		}
	} // process

	//---------------------------------------------------------

} // namespace Logic
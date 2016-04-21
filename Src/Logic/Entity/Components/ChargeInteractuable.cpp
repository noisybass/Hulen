#include "ChargeInteractuable.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/GameObject.h"
#include "Map/MapEntity.h"
#include "Logic/Entity/Components/PhysicEntity.h"

namespace Logic
{
	IMP_FACTORY(CChargeInteractuable);

	CChargeInteractuable::CChargeInteractuable()
		: IComponent(), _canInteract(false)
	{

	} // Cinteractuable

	CChargeInteractuable::~CChargeInteractuable()
	{

	} // ~CInteractuable

	bool CChargeInteractuable::spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		_graphics = (CGraphics*)(_entity->getComponent("CGraphics"));
		return true;

	} // spawn

	bool CChargeInteractuable::accept(const TMessage &message)
	{
		//std::cout << "Message type: " << message._type << std::endl;
		return message._type == Message::TOUCHED ||
			message._type == Message::UNTOUCHED ||
			message._type == Message::INTERACTUABLE;

	} // accept

	void CChargeInteractuable::process(const TMessage &message)
	{
		CEntity* other;
		switch (message._type)
		{
		case Message::TOUCHED:
		case Message::UNTOUCHED:
			/*other = message.getArg<CEntity*>("entity");
			if (!(other->getBlueprint().compare("World")))
				_entity->removeComponent("CPhysicEntity");*/
			break;
		case Message::INTERACTUABLE:
			
			if (message.getArg<bool>("canInteract")){
				_canInteract = true;
				_graphics->setMaterial("Charge_on");
			}
			else{
				_canInteract = false;
				_graphics->setMaterial("Charge_off");
			}
			break;
		default:
			break;
		}

	} // process

} // namespace Logic
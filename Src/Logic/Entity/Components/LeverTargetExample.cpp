#include "LeverTargetExample.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/GameObject.h"
#include "Map/MapEntity.h"
#include "Logic/Entity/Components/PhysicEntity.h"
#include "GUI/Server.h"

namespace Logic
{
	IMP_FACTORY(CLeverTargetExample);

	CLeverTargetExample::CLeverTargetExample()
		: IComponent(), _leverSwitch(false)
	{

	} // Cinteractuable

	CLeverTargetExample::~CLeverTargetExample()
	{
		
	} // ~CInteractuable

	bool CLeverTargetExample::spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		_graphics = (CGraphics*)(_entity->getComponent("CGraphics"));

		_graphics->setMaterial("Green");

		return true;

	} // spawn

	void CLeverTargetExample::tick(float msecs){
		IComponent::tick(msecs);

		if (_leverSwitch) _graphics->setMaterial("Purple");
		else _graphics->setMaterial("Green");
		
	} // tick

	bool CLeverTargetExample::accept(const TMessage &message)
	{
		return message._type == Message::LEVER_INTERACTUABLE;

	} // accept

	void CLeverTargetExample::process(const TMessage &message)
	{
		switch (message._type)
		{
		case Message::LEVER_INTERACTUABLE:
			
			if (message.getArg<bool>("leverSwitch")){
				_leverSwitch = true;
			}
			else{
				_leverSwitch = false;
			}
			break;
		default:
			break;
		}

	} // process

} // namespace Logic
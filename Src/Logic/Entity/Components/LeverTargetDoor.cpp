#include "LeverTargetDoor.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/GameObject.h"
#include "Map/MapEntity.h"
#include "Logic/Entity/Components/PhysicEntity.h"
#include "GUI/Server.h"

namespace Logic
{
	IMP_FACTORY(CLeverTargetDoor);

	CLeverTargetDoor::CLeverTargetDoor()
		: IComponent()
	{

	} // Cinteractuable

	CLeverTargetDoor::~CLeverTargetDoor()
	{
		
	} // ~CInteractuable

	bool CLeverTargetDoor::spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		_graphics = (CGraphics*)(_entity->getComponent("CGraphics"));

		_graphics->setMaterial("Green");

		return true;

	} // spawn

	bool CLeverTargetDoor::accept(const TMessage &message)
	{
		return message._type == Message::LEVER_INTERACTUABLE;

	} // accept

	void CLeverTargetDoor::process(const TMessage &message)
	{
		switch (message._type)
		{
		case Message::LEVER_INTERACTUABLE:
			
			if (message.getArg<bool>("leverSwitch")){
				switchOn();
			}
			else{
				switchOff();
			}
			break;
		default:
			break;
		}

	} // process

	void CLeverTargetDoor::switchOn(){
		_graphics->setMaterial("Purple");
		TMessage message;
		message._type = Message::SWITCH;
		message.setArg("switch", 1);
		_entity->emitMessage(message);
	} // switchOn

	void CLeverTargetDoor::switchOff(){
		_graphics->setMaterial("Green");
		TMessage message;
		message._type = Message::SWITCH;
		message.setArg("switch", 0);
		_entity->emitMessage(message);
	} // switchOff

} // namespace Logic
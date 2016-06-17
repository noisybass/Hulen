#include "LeverTargetDoor.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/GameObject.h"
#include "Map/MapEntity.h"
#include "Logic/Entity/Components/PhysicEntity.h"
#include "GUI/Server.h"
#include "Sounds/api/SoundsResources.h"

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

		assert(entityInfo->hasAttribute("sound_name") &&
			entityInfo->hasAttribute("sound_volume") &&
			entityInfo->hasAttribute("sound_pitch") && "Tienes que poner todos los atributos del sonido.");
			
		if (entityInfo->hasAttribute("sound_name") &&
			entityInfo->hasAttribute("sound_volume") &&
			entityInfo->hasAttribute("sound_pitch"))
		{
			_soundName = entityInfo->getStringAttribute("sound_name");
			_soundVolume = entityInfo->getFloatAttribute("sound_volume");
			_soundPitch = entityInfo->getFloatAttribute("sound_pitch");
		}

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

		Sounds::CSoundsResources::getSingletonPtr()->playAndDestroySound(_soundName, _soundVolume, _soundPitch, _entity->getPosition(), Vector3(0, 0, 0));
	} // switchOn

	void CLeverTargetDoor::switchOff(){
		_graphics->setMaterial("Green");
		TMessage message;
		message._type = Message::SWITCH;
		message.setArg("switch", 0);
		_entity->emitMessage(message);

		Sounds::CSoundsResources::getSingletonPtr()->playAndDestroySound(_soundName, _soundVolume, _soundPitch, _entity->getPosition(), Vector3(0, 0, 0));
	} // switchOff

} // namespace Logic
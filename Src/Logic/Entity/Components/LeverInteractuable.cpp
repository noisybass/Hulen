#include "LeverInteractuable.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/GameObject.h"
#include "Map/MapEntity.h"
#include "Logic/Entity/Components/PhysicEntity.h"
#include "GUI/Server.h"
#include "Sounds\api\SoundsResources.h"

namespace Logic
{
	IMP_FACTORY(CLeverInteractuable);

	CLeverInteractuable::CLeverInteractuable()
		: IComponent(), _canInteract(false), _leverSwitch(false), _pressLeverButton(false)
	{

	} // Cinteractuable

	CLeverInteractuable::~CLeverInteractuable()
	{
		_target = nullptr;

		Sounds::CSoundsResources* sounds = Sounds::CSoundsResources::getSingletonPtr();
		sounds->deleteSound(_channelSwitchOnSound);
		sounds->deleteSound(_channelSwitchOffSound);
	} // ~CInteractuable

	bool CLeverInteractuable::spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		_graphics = (CGraphics*)(_entity->getComponent("CGraphics"));

		_graphics->setMaterial("Charge_off");

		/**
		Sounds
		*/
		if (entityInfo->hasAttribute("switchOnVolume") && entityInfo->hasAttribute("switchOnPitch"))
		{
			_channelSwitchOnSound = _entity->getName() + "SwitchOn";
			Sounds::CSoundsResources* sounds = Sounds::CSoundsResources::getSingletonPtr();
			sounds->createSound(_channelSwitchOnSound, std::string("SwitchOn"));
			sounds->setSoundVolume(_channelSwitchOnSound, entityInfo->getFloatAttribute("switchOnVolume"));
			sounds->setSoundPitch(_channelSwitchOnSound, entityInfo->getFloatAttribute("switchOnPitch"));
			sounds->setPositionAndVelocity(_channelSwitchOnSound, _entity->getPosition(), Vector3(0,0,0));
		}

		if (entityInfo->hasAttribute("switchOffVolume") && entityInfo->hasAttribute("switchOffPitch"))
		{
			_channelSwitchOffSound = _entity->getName() + "SwitchOff";
			Sounds::CSoundsResources* sounds = Sounds::CSoundsResources::getSingletonPtr();
			sounds->createSound(_channelSwitchOffSound, std::string("SwitchOff"));
			sounds->setSoundVolume(_channelSwitchOffSound, entityInfo->getFloatAttribute("switchOffVolume"));
			sounds->setSoundPitch(_channelSwitchOffSound, entityInfo->getFloatAttribute("switchOffPitch"));
			sounds->setPositionAndVelocity(_channelSwitchOffSound, _entity->getPosition(), Vector3(0, 0, 0));
		}

		return true;

	} // spawn

	bool CLeverInteractuable::init(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (entityInfo->hasAttribute("lever_GO_target")){
			_target = _entity->getGameObject()->getMap()->getGameObjectByName(entityInfo->getStringAttribute("lever_GO_target"))->getBody();
		}

		return true;
	} // init

	bool CLeverInteractuable::activate(){
	
		GUI::CServer::getSingletonPtr()->getObjectsController()->addControllerObject(_entity);
		return true;
	} // activate

	void CLeverInteractuable::deactivate(bool isDeletingMap){
		
		GUI::CServer::getSingletonPtr()->getObjectsController()->removeControllerObject(_entity->getName());
	} // deactivate

	void CLeverInteractuable::tick(float msecs){
		IComponent::tick(msecs);

		// If is inside of the interactuable radius (_canInteract) and
		// the player has pressed the button
		//std::cout << "_canInteract = " << _canInteract << std::endl;
		//std::cout << "_pressLeverButton = " << _pressLeverButton << std::endl;

		if (_canInteract && _pressLeverButton){

			TMessage message;
			_leverSwitch = !_leverSwitch;
			message.setArg("leverSwitch", _leverSwitch);
			message._type = Message::LEVER_INTERACTUABLE;
			_target->emitMessage(message);
			Sounds::CSoundsResources* sounds = Sounds::CSoundsResources::getSingletonPtr();
			if (_leverSwitch) 
			{
				sounds->playSound(_channelSwitchOnSound);
				sounds->pauseSound(_channelSwitchOffSound);
				_graphics->setMaterial("Charge_on");
			}
			else 
			{
				sounds->playSound(_channelSwitchOffSound);
				//sounds->pauseSound(_channelSwitchOnSound);
				_graphics->setMaterial("Charge_off");
			}

			
		}

		_pressLeverButton = false;
	} // tick

	bool CLeverInteractuable::accept(const TMessage &message)
	{
		//std::cout << "Message type: " << message._type << std::endl;
		return message._type == Message::INTERACTUABLE ||
			message._type == Message::PLAYER_LEVER_INTERACT;

	} // accept

	void CLeverInteractuable::process(const TMessage &message)
	{
		switch (message._type)
		{
		case Message::INTERACTUABLE:
			
			if (message.getArg<bool>("canInteract")){
				_canInteract = true;
			}
			else{
				_canInteract = false;
			}
			break;
		case Message::PLAYER_LEVER_INTERACT:
			_pressLeverButton = true;
			break;
		default:
			break;
		}

	} // process

} // namespace Logic
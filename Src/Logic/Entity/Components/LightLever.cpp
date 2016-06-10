#include "LightLever.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/GameObject.h"
#include "Map/MapEntity.h"
#include "Logic/Entity/Components/PhysicEntity.h"
#include "GUI/Server.h"

namespace Logic
{
	IMP_FACTORY(CLightLever);

	CLightLever::CLightLever()
		: IComponent(), _leverSwitch(false), _chargeAbove(false)
	{

	} // Cinteractuable

	CLightLever::~CLightLever()
	{
		_target = nullptr;
	} // ~CInteractuable

	bool CLightLever::spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		if (entityInfo->hasAttribute("light_lever_GO_target")){
			_target = _entity->getGameObject()->getMap()->getGameObjectByName(entityInfo->getStringAttribute("light_lever_GO_target"))->getBody();
			_shadowTarget = _entity->getGameObject()->getMap()->getGameObjectByName(entityInfo->getStringAttribute("light_lever_GO_target"))->getShadow();
		}


		_graphics = (CGraphics*)(_entity->getComponent("CGraphics"));

		_graphics->setMaterial("Charge_off");

		return true;

	} // spawn

	bool CLightLever::activate(){
	
		//GUI::CServer::getSingletonPtr()->getObjectsController()->addControllerObject(_entity);
		return true;
	} // activate

	void CLightLever::deactivate(){
		
		//GUI::CServer::getSingletonPtr()->getObjectsController()->removeControllerObject(_entity->getName());
	} // deactivate

	void CLightLever::tick(float msecs){
		IComponent::tick(msecs);

		// If is inside of the interactuable radius (_canInteract) and
		// the player has pressed the button
		//std::cout << "_canInteract = " << _canInteract << std::endl;
		//std::cout << "_pressLeverButton = " << _pressLeverButton << std::endl;

		// If is a charge above and the lever isn't active
		if (_chargeAbove && !_leverSwitch){

			TMessage message;
			_leverSwitch = !_leverSwitch;
			message.setArg("leverSwitch", _leverSwitch);
			message._type = Message::LEVER_INTERACTUABLE;
			_target->emitMessage(message);
			if (_shadowTarget)
				_shadowTarget->emitMessage(message);
			_graphics->setMaterial("Charge_on");
			//_leverSwitch = true;
		}
		// If isn't a charge above and the lever is active
		else if (!_chargeAbove && _leverSwitch)
		{
			TMessage message;
			_leverSwitch = !_leverSwitch;
			message.setArg("leverSwitch", _leverSwitch);
			message._type = Message::LEVER_INTERACTUABLE;
			_target->emitMessage(message);
			if (_shadowTarget)
				_shadowTarget->emitMessage(message);
			_graphics->setMaterial("Charge_off");
			//_leverSwitch = false;
		}

	} // tick

	bool CLightLever::accept(const TMessage &message)
	{
		//std::cout << "Message type: " << message._type << std::endl;
		return message._type == Message::ON_CONTACT ||
				message._type == Message::PICK_CHARGE;

	} // accept

	void CLightLever::process(const TMessage &message)
	{
		CEntity* entity;
		switch (message._type)
		{
		case Message::ON_CONTACT:
			_chargeAbove = true;
			break;
		case Message::PICK_CHARGE:
			_chargeAbove = false;
			break;
		default:
			break;
		}

	} // process

} // namespace Logic
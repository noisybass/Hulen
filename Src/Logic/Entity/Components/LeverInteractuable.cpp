#include "LeverInteractuable.h"

#include "Logic/Server.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Entity/GameObject.h"
#include "Map/MapEntity.h"
#include "Logic/Entity/Components/PhysicEntity.h"
#include "GUI/Server.h"

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
	} // ~CInteractuable

	bool CLeverInteractuable::spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		if (entityInfo->hasAttribute("lever_GO_target")){
			_target = _entity->getGameObject()->getMap()->getGameObjectByName(entityInfo->getStringAttribute("lever_GO_target"))->getBody();
		}

		_graphics = (CGraphics*)(_entity->getComponent("CGraphics"));

		_graphics->setMaterial("Charge_off");

		return true;

	} // spawn

	bool CLeverInteractuable::activate(){
	
		GUI::CServer::getSingletonPtr()->getObjectsController()->addControllerObject(_entity);
		return true;
	} // activate

	void CLeverInteractuable::deactivate(){
		
		GUI::CServer::getSingletonPtr()->getObjectsController()->removeControllerObject(_entity->getName());
	} // deactivate

	void CLeverInteractuable::tick(float msecs){
		IComponent::tick(msecs);

		// If is inside of the interactuable radius (_canInteract) and
		// the player has pressed the button
		//std::cout << "_canInteract = " << _canInteract << std::endl;
		//std::cout << "_pressLeverButton = " << _pressLeverButton << std::endl;

		if (_canInteract && _pressLeverButton){

			/*
			Cuando se pulsa un interruptor hace el zoomIn. Al acabar el zoomIn hace un zoomOut.
			Por ahora se deja así para demostrar que funciona. En el caso de que se desee separar el
			zoomIn del zoomOut, se debe cambiar un poco la función zoomIn.
			*/
			CServer::getSingletonPtr()->getCamera()->zoomIn();

			TMessage message;
			_leverSwitch = !_leverSwitch;
			message.setArg("leverSwitch", _leverSwitch);
			message._type = Message::LEVER_INTERACTUABLE;
			_target->emitMessage(message);
			if (_leverSwitch) _graphics->setMaterial("Charge_on");
			else _graphics->setMaterial("Charge_off");
			
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
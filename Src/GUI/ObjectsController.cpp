#include "ObjectsController.h"

#include "Logic/Entity/Message.h"

#include <cassert>

namespace GUI {

	CObjectsController::CObjectsController()
	{
		_entities = std::unordered_map<std::string, Logic::CEntity*>();
	} // CPlayerController

	//--------------------------------------------------------

	CObjectsController::~CObjectsController()
	{
		deactivate();
		_entities.clear();

	} // ~CPlayerController

	//--------------------------------------------------------

	void CObjectsController::activate()
	{		
		CInputManager::getSingletonPtr()->addKeyListener(this);
		CInputManager::getSingletonPtr()->addMouseListener(this);

	} // activate

	//--------------------------------------------------------

	void CObjectsController::deactivate()
	{
		CInputManager::getSingletonPtr()->removeKeyListener(this);
		CInputManager::getSingletonPtr()->removeMouseListener(this);

	} // deactivate

	void CObjectsController::addControllerObject(Logic::CEntity* entity)
	{
		assert(_entities.find(entity->getName()) == _entities.end() && "There is an element with the same name into the controller objects");
		_entities.insert({ entity->getName(), entity });

	}

	void CObjectsController::removeControllerObject(const std::string &entityName)
	{
		assert(_entities.find(entityName) != _entities.end() && "Not exists the element that you want erase from controller objects");
		_entities.erase(entityName);

	}

	//--------------------------------------------------------

	bool CObjectsController::keyPressed(TKey key)
	{
		for (std::pair<std::string, Logic::CEntity*> entity : _entities)
		{
			switch (key.keyId){
			case GUI::Key::E:
				Logic::TMessage message;
				message._type = Logic::Message::PLAYER_LEVER_INTERACT;
				entity.second->emitMessage(message);
				break;
			}
		}
		

		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CObjectsController::keyReleased(TKey key)
	{
		
		return false;

	} // keyReleased

	//--------------------------------------------------------
	
	bool CObjectsController::mouseMoved(const CMouseState &mouseState)
	{

		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CObjectsController::mousePressed(const CMouseState &mouseState)
	{

		return false;

	} // mousePressed

	//--------------------------------------------------------

	bool CObjectsController::mouseReleased(const CMouseState &mouseState)
	{
		return false;

	} // mouseReleased

} // namespace GUI

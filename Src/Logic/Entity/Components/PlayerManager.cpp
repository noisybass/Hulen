#include "PlayerManager.h"

#include "Application/GameState.h"
#include "Logic/Entity/GameObject.h"
#include "Logic/Entity/PlayerEvent.h"
#include <boost/signals2/signal.hpp>
namespace Logic
{
	IMP_FACTORY(CPlayerManager);

	CPlayerManager::CPlayerManager() 
		: IComponent(), _onLight(false) 
	{

	} // CPlayerManager

	bool CPlayerManager::accept(const TMessage &message)
	{
		return message._type == Message::PLAYER_ENTER_LIGHT ||
			message._type == Message::PLAYER_OUT_LIGHT ||
			message._type == Message::PLAYER_CHANGE_STATE ||
			message._type == Message::PLAYER_DEATH;

	} // accept

	void CPlayerManager::process(const TMessage &message)
	{
		switch (message._type)
		{
		case Message::PLAYER_ENTER_LIGHT:
			_onLight = true;
			std::cout << "Jugador dentro de la luz" << std::endl;
			break;
		case Message::PLAYER_OUT_LIGHT:
			_onLight = false;
			std::cout << "Jugador fuera de la luz" << std::endl;
			break;
		case Message::PLAYER_CHANGE_STATE:
			if (_onLight)
				changeState();
			break;
		case Message::PLAYER_DEATH:
			std::cout << "Jugador muerto" << std::endl;
			boost::signals2::signal < void() > signal;
			
			signal.connect(&Application::CGameState::playerListener);
	
			
			signal();

			//Logic::CPlayerEvent::getInstance()->fireEvent(/*"Die"*/);

			break;
		}

	} // process

	void CPlayerManager::changeState()
	{
		TMessage message;
		message._type = Message::SEND_STATE;
		switch (_gameObject->_state)
		{
		case GameObject::BODY:
			std::cout << "Cambiando de cuerpo a sombra" << std::endl;
			_gameObject->_state = GameObject::SHADOW;
			message.setArg<CEntity*>(std::string("receiver"), _gameObject->getShadow());

			_gameObject->getShadow()->activate();
			_gameObject->getBody()->emitMessage(message);
			//_gameObject->getBody()->deactivate();

			break;
		case GameObject::SHADOW:
			std::cout << "Cambiando de sombra a cuerpo" << std::endl;
			_gameObject->_state = GameObject::BODY;
			message.setArg<CEntity*>(std::string("receiver"), _gameObject->getBody());

			_gameObject->getBody()->activate();
			_gameObject->getShadow()->emitMessage(message);
			//_gameObject->getShadow()->deactivate();
			break;
		}
	} // changeState

	void CPlayerManager::tick(unsigned int msecs)
	{
		// Llamar al método de la clase padre (IMPORTANTE).
		IComponent::tick(msecs);

		//switch (_gameObject->_state)
		//{
		//case GameObject::BODY:
		//	//_gameObject->getBody()->activate();
		//	_gameObject->getShadow()->deactivate();
		//	break;
		//case GameObject::SHADOW:
		//	//_gameObject->getShadow()->activate();
		//	_gameObject->getBody()->deactivate();
		//	break;
		//}
	} // tick

} // namespace Logic
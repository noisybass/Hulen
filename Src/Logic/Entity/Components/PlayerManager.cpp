#include "PlayerManager.h"

#include "Application/GameState.h"
#include "Logic/Entity/GameObject.h"
#include "Logic/Events/Event.h"
namespace Logic
{
	IMP_FACTORY(CPlayerManager);

	CPlayerManager::CPlayerManager()
		: IComponent(), _onLight(false), _deathTimeElapsed(0)
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

			// Reseteamos el tiempo
			_deathTimeElapsed = 0;
			std::cout << "Resetar tiempo de morir" << std::endl;
			break;
		case Message::PLAYER_OUT_LIGHT:
			_onLight = false;
			if (_gameObject->_state == GameObject::SHADOW)
				changeState();
			std::cout << "Jugador fuera de la luz" << std::endl;
			break;
		case Message::PLAYER_CHANGE_STATE:
			if (_onLight)
				changeState();
			break;
		case Message::PLAYER_DEATH:
			std::cout << "Jugador muerto" << std::endl;
			std::string string = "Die";

			Logic::CEventSystem<Logic::Events::DieClass, Logic::Events::DieFunction>::
				    getInstance<Logic::Events::DieClass, Logic::Events::DieFunction>()
				    ->fireEvent(string);

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

		// Si no estamos en la luz, empezamos a morirnos
		if (!_onLight && _gameObject->_playerCanDie){
			_deathTimeElapsed += msecs;
			std::cout << "Tiempo que llevo fuera de la luz " << _deathTimeElapsed << std::endl;
			if (_deathTimeElapsed >= _gameObject->_playerDeathTime){
				Logic::TMessage m;
				m._type = Logic::Message::PLAYER_DEATH;
				_gameObject->emitMessage(m);
			}
		}

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
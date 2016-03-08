#include "PlayerManager.h"

#include "Application/GameState.h"
#include "Logic/Entity/GameObject.h"
#include "Logic/Events/Event.h"
#include "Map/MapEntity.h"

#include "Logic/Entity/Components/LightingArea.h"

namespace Logic
{
	IMP_FACTORY(CPlayerManager);

	CPlayerManager::CPlayerManager()
		: IComponent(), _onLight(false), _deathTimeElapsed(0), _kasaiName(""), _kasai(nullptr),
		_chargeName(""), _charge(nullptr)
	{

	} // CPlayerManager

	CPlayerManager::~CPlayerManager()
	{
		if (_kasai)
		{
			_kasai = nullptr;
			_charge = nullptr;
		}
	}

	bool CPlayerManager::spawn(const std::string& name, CGameObject* gameObject, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, gameObject, map, entityInfo))
			return false;

		assert(entityInfo->hasAttribute("kasai") && "Hay que especificar el atributo kasai");
		_kasaiName = entityInfo->getStringAttribute("kasai");

		if (entityInfo->hasAttribute("charge"))
			_chargeName = entityInfo->getStringAttribute("charge");

	} // spawn

	bool CPlayerManager::activate()
	{
		_kasai = _gameObject->getMap()->getGameObjectByName(_kasaiName);

		//_charge = _gameObject->getMap()->getGameObjectByName(_chargeName);
		_charge = Logic::CMap::instanciatePrefab(_chargeName, "Charge0");

		return true;

	} // activate

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
		//case Message::PLAYER_ENTER_LIGHT:
		//	_onLight = true;
		//	std::cout << "Jugador dentro de la luz" << std::endl;

		//	// Reseteamos el tiempo
		//	_deathTimeElapsed = 0;
		//	std::cout << "Resetar tiempo de morir" << std::endl;
		//	break;
		//case Message::PLAYER_OUT_LIGHT:
		//	_onLight = false;
		//	if (_gameObject->_state == GameObject::SHADOW)
		//		changeState();
		//	std::cout << "Jugador fuera de la luz" << std::endl;
		//	break;
		case Message::PLAYER_CHANGE_STATE:
			if (_onLight)
			{
				if (_gameObject->_state == GameObject::SHADOW)
					changeState(GameObject::BODY);
				else
					changeState(GameObject::SHADOW);
			}
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

	void CPlayerManager::changeState(GameObject::TState state)
	{
		if (_gameObject->_state != state)
		{
			TMessage message;
			message._type = Message::SEND_STATE;

			// Cambio de sombra a cuerpo
			if (state == GameObject::BODY)
			{
				std::cout << "Cambiando de sombra a cuerpo" << std::endl;
				_gameObject->_state = GameObject::BODY;
				message.setArg<CEntity*>(std::string("receiver"), _gameObject->getBody());

				_gameObject->getBody()->activate();
				_gameObject->getShadow()->emitMessage(message);
			}
			// Cambio de cuerpo a sombra
			else
			{
				std::cout << "Cambiando de cuerpo a sombra" << std::endl;
				_gameObject->_state = GameObject::SHADOW;
				message.setArg<CEntity*>(std::string("receiver"), _gameObject->getShadow());

				_gameObject->getShadow()->activate();
				_gameObject->getBody()->emitMessage(message);
			}
		}

		//TMessage message;
		//message._type = Message::SEND_STATE;
		//switch (_gameObject->_state)
		//{
		//case GameObject::BODY:
		//	std::cout << "Cambiando de cuerpo a sombra" << std::endl;
		//	_gameObject->_state = GameObject::SHADOW;
		//	message.setArg<CEntity*>(std::string("receiver"), _gameObject->getShadow());

		//	_gameObject->getShadow()->activate();
		//	_gameObject->getBody()->emitMessage(message);
		//	//_gameObject->getBody()->deactivate();

		//	break;
		//case GameObject::SHADOW:
		//	std::cout << "Cambiando de sombra a cuerpo" << std::endl;
		//	_gameObject->_state = GameObject::BODY;
		//	message.setArg<CEntity*>(std::string("receiver"), _gameObject->getBody());

		//	_gameObject->getBody()->activate();
		//	_gameObject->getShadow()->emitMessage(message);
		//	//_gameObject->getShadow()->deactivate();
		//	break;
		//}
	} // changeState

	void CPlayerManager::tick(unsigned int msecs)
	{
		// Llamar al método de la clase padre (IMPORTANTE).
		IComponent::tick(msecs);

		_onLight = playerOnLight();


		if (_onLight)
		{
			// Reseteamos el contador para la muerte
			_deathTimeElapsed = 0;
			//std::cout << "Resetar tiempo de morir" << std::endl;
		}
		else
		{
			// Si ya no estoy en la luz paso al estado body
			if (_gameObject->_state == GameObject::SHADOW)
				changeState(GameObject::BODY);

			// Y empezamos a morirnos
			if (!_onLight && _gameObject->_playerCanDie){
				_deathTimeElapsed += msecs;
				//std::cout << "Tiempo que llevo fuera de la luz " << _deathTimeElapsed << std::endl;
				if (_deathTimeElapsed >= _gameObject->_playerDeathTime){
					Logic::TMessage m;
					m._type = Logic::Message::PLAYER_DEATH;
					_gameObject->emitMessage(m);
				}
			}
		}

		
	} // tick

	bool CPlayerManager::playerOnLight()
	{
		CLightingArea* kasaiArea = (CLightingArea*)(_kasai->getBody()->getComponent("CLightingArea"));

		CLightingArea* chargeArea = (CLightingArea*)(_charge->getBody()->getComponent("CLightingArea"));

		return kasaiArea->_playerInside || chargeArea->_playerInside;

	} // playerOnLight

} // namespace Logic
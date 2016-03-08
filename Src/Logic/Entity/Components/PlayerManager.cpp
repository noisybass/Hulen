#include "PlayerManager.h"

#include "Application/GameState.h"
#include "Logic/Entity/GameObject.h"
#include "Logic/Events/Event.h"
#include "Map/MapEntity.h"

#include "Logic/Entity/Components/LightingArea.h"
#include "Logic/Entity/Components/Interactuable.h"

namespace Logic
{
	IMP_FACTORY(CPlayerManager);

	CPlayerManager::CPlayerManager()
		: IComponent(), _onLight(false), _deathTimeElapsed(0), _kasaiName(""), _kasai(nullptr),
		_chargePrefab(""), _chargesOwned(3)
	{

	} // CPlayerManager

	CPlayerManager::~CPlayerManager()
	{
		if (_kasai)
		{
			_kasai = nullptr;
		}
	}

	bool CPlayerManager::spawn(const std::string& name, CGameObject* gameObject, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, gameObject, map, entityInfo))
			return false;

		assert(entityInfo->hasAttribute("kasai") && "Hay que especificar el atributo kasai");
		_kasaiName = entityInfo->getStringAttribute("kasai");

		if (entityInfo->hasAttribute("charge"))
			_chargePrefab = entityInfo->getStringAttribute("charge");

	} // spawn

	bool CPlayerManager::activate()
	{
		_kasai = _gameObject->getMap()->getGameObjectByName(_kasaiName);

		//_charge = _gameObject->getMap()->getGameObjectByName(_chargeName);
		//_charge = Logic::CMap::instantiatePrefab(_chargeName, "Charge0");

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
		CGameObject* chargeInRange;

		switch (message._type)
		{
		case Message::PICK_CHARGE:
			// Comprobamos si hay alguna carga que podamos coger
			chargeInRange = canPickAnyCharge();
			if (chargeInRange)
			{
				// Buscarla en el vector de referencias
				std::vector<CGameObject*>::const_iterator it = std::find_if(_chargesOnMap.begin(), _chargesOnMap.end(), [&](const CGameObject* charge) {
					charge == chargeInRange;
				});

				// Una vez que la tenemos la borramos del vector
				if (it != _chargesOnMap.end())
					_chargesOnMap.erase(it);

				// Ahora la borramos del mapa
				_gameObject->getMap()->removeGameObject((*it));

				// Destruir
				delete (*it);

				// Incrementar el número de cargas que poseemos
				_chargesOwned++;
			}
			break;
		case Message::PUT_CHARGE:
			if (_chargesOwned > 0)
			{
				// Instanciamos la carga en el mapa
				CGameObject* newCharge = Logic::CMap::instantiatePrefab(_chargePrefab, "Charge" + _chargesOwned);

				// La metemos en el vector de referencias
				_chargesOnMap.push_back(newCharge);

				// Decrementamos el número de cargas que poseemos
				_chargesOwned--;
			}
			break;
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

	bool CPlayerManager::playerOnLight() const
	{
		bool b = false;

		CLightingArea* kasaiArea = (CLightingArea*)(_kasai->getBody()->getComponent("CLightingArea"));

		b = kasaiArea->_playerInside;

		CLightingArea* chargeArea;

		for (CGameObject* charge : _chargesOnMap)
		{
			chargeArea = (CLightingArea*)(charge->getBody()->getComponent("CLightingArea"));
			b = b && chargeArea->_playerInside;
		}

		return b;

	} // playerOnLight

	CGameObject* CPlayerManager::canPickAnyCharge() const
	{
		CInteractuable* chargeArea;

		for (CGameObject* charge : _chargesOnMap)
		{
			chargeArea = (CInteractuable*)(charge->getBody()->getComponent("CInteractuable"));
			if (chargeArea->_canInteract)
				return charge;
		}

		return nullptr;

	} // canPickAnyCharge

} // namespace Logic
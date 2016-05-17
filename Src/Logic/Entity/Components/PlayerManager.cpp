#include "PlayerManager.h"

#include "Application/GameState.h"
#include "Logic/Entity/GameObject.h"
#include "Logic/Events/Event.h"
#include "Logic/Maps/EntityFactory.h"
#include "Map/MapEntity.h"

#include "Logic/Entity/Components/LightingArea.h"
#include "Logic/Entity/Components/ChargeInteractuable.h"


namespace Logic
{
	IMP_FACTORY(CPlayerManager);

	CPlayerManager::CPlayerManager()
		: IComponent(), _onLight(false), _deathTimeElapsed(0.0),
		_playerDeathTime(3.0), _kasaiName(""), _kasai(nullptr),
		_chargePrefab(""), _chargesOwned(3), _playerCanDie(false), 
		_pickObjectAnimation("")
	{
		_soundsResources = Sounds::CSoundsResources::getSingletonPtr();
		_soundsResources->createSound("ShadowSongChannel", "ShadowSong");
	} // CPlayerManager

	CPlayerManager::~CPlayerManager()
	{
		if (_kasai)
		{
			_kasai = nullptr;
		}
		if (_soundsResources)
		{
			_soundsResources->deleteSound("ShadowSongChannel");
			_soundsResources = nullptr;
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

		if (entityInfo->hasAttribute("playerDeathTime"))
			_playerDeathTime = entityInfo->getFloatAttribute("playerDeathTime") * 1000;

		if (entityInfo->hasAttribute("playerCanDie"))
			_playerCanDie = entityInfo->getBoolAttribute("playerCanDie");

		if (entityInfo->hasAttribute("pickObjectAnimation"))
			_pickObjectAnimation = entityInfo->getStringAttribute("pickObjectAnimation"); 

		return true;

	} // spawn

	bool CPlayerManager::activate()
	{
		_kasai = _gameObject->getMap()->getGameObjectByName(_kasaiName);

		return true;

	} // activate

	bool CPlayerManager::accept(const TMessage &message)
	{
		return message._type == Message::PLAYER_ENTER_LIGHT ||
			message._type == Message::PLAYER_OUT_LIGHT ||
			message._type == Message::PLAYER_CHANGE_STATE ||
			message._type == Message::PLAYER_EVENT ||
			message._type == Message::PUT_CHARGE ||
			message._type == Message::PICK_CHARGE ||
			message._type == Message::PLAYER_LEVER_INTERACT ||
			message._type == Message::CHARGE_ERASED ||
			message._type == Message::DEATH_PLANE ||
			message._type == Message::PICK_FROM_DEATH_CHARGE;

	} // accept

	void CPlayerManager::process(const TMessage &message)
	{
		CGameObject* chargeInRange = nullptr;
		CEntity* deathCharge = nullptr;
		TMessage m;
		std::string playerEvent;
		

		switch (message._type)
		{
		case Message::PICK_FROM_DEATH_CHARGE:
			deathCharge = message.getArg<CEntity*>("entityCharge");
			// Continue below
		case Message::PICK_CHARGE:
			// Comprobamos si hay alguna carga que podamos coger
			if (!deathCharge)
				chargeInRange = canPickAnyCharge();
			else
				chargeInRange = deathCharge->getGameObject();

			if (chargeInRange)
			{
				// Buscarla en el vector de referencias
				std::vector<CGameObject*>::const_iterator it = std::find(_chargesOnMap.begin(), _chargesOnMap.end(), chargeInRange);

				// Una vez que la tenemos la borramos del vector
				if (it != _chargesOnMap.end())
					_chargesOnMap.erase(it);

				// Avisamos a las cargas graficas que se ha cogido una carga
				TMessage m;
				m._type = Message::PICK_CHARGE;
				m.setArg<Vector3>("position", chargeInRange->getPosition());
				_kasai->emitMessage(m);

				// Animamos al player
				TMessage mAnim;
				mAnim._type = Message::SET_ANIMATION;
				mAnim.setArg<std::string>(std::string("animation"), std::string(_pickObjectAnimation));
				mAnim.setArg<bool>(std::string("loop"), false);
				_gameObject->emitMessage(mAnim, this);

				// Destruir y borrar del mapa
				Logic::CEntityFactory::getSingletonPtr()->deleteGameObject(chargeInRange);

				// Incrementar el número de cargas que poseemos
				_chargesOwned++;
			}
			break;
		case Message::PUT_CHARGE:
			if (_chargesOwned > 0)
			{
				// Instanciamos la carga en el mapa
				Vector3 pos = message.getArg<Vector3>("instancePosition");
				std::stringstream ss;
				ss << pos.x << " " << pos.y << " " << 0;
				std::string chargePosition = ss.str();
				ss.str(std::string());
				ss << "Charge" << _chargesOwned;
				std::string chargeName = ss.str();
				CGameObject* newCharge = Logic::CMap::instantiatePrefab(_chargePrefab, chargeName, chargePosition);

				// La metemos en el vector de referencias
				_chargesOnMap.push_back(newCharge);

				// La activamos
				newCharge->activate();

				// Decrementamos el número de cargas que poseemos
				_chargesOwned--;

				// Quitamos la carga de luz de las cargas graficas
				TMessage m;
				m._type = Message::PUT_CHARGE;
				_kasai->emitMessage(m);
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
		case Message::PLAYER_EVENT:

			Logic::CEventSystem<Logic::Events::GameStateClass, Logic::Events::PlayerEventFunction>::
				getInstance<Logic::Events::GameStateClass, Logic::Events::PlayerEventFunction>()
				->fireEvent(message.getArg<std::string>("playerEvent"));

			break;
		case Message::DEATH_PLANE:
			playerEvent = "die";
			Logic::CEventSystem<Logic::Events::GameStateClass, Logic::Events::PlayerEventFunction>::
				getInstance<Logic::Events::GameStateClass, Logic::Events::PlayerEventFunction>()
				->fireEvent(playerEvent);

			break;
		case Message::CHARGE_ERASED:

			std::string chargeName = message.getArg<std::string>("chargeName");
			CGameObject* charge = _gameObject->_map->getGameObjectByName(chargeName);

			// Buscarla en el vector de referencias
			std::vector<CGameObject*>::const_iterator it = std::find(_chargesOnMap.begin(), _chargesOnMap.end(), charge);

			// Una vez que la tenemos la borramos del vector
			if (it != _chargesOnMap.end())
				_chargesOnMap.erase(it);

			Logic::CEntityFactory::getSingletonPtr()->deleteGameObject(charge);

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
				_gameObject->_state = GameObject::BODY;
				message.setArg<CEntity*>(std::string("receiver"), _gameObject->getBody());

				_gameObject->getBody()->activate();
				_gameObject->getShadow()->emitMessage(message);

				_soundsResources->pauseSound("ShadowSongChannel");
				_soundsResources->playAndDestroySound("DeepIntoShadow", 0.5);
			}
			// Cambio de cuerpo a sombra
			else
			{
				_gameObject->_state = GameObject::SHADOW;
				message.setArg<CEntity*>(std::string("receiver"), _gameObject->getShadow());

				_gameObject->getShadow()->activate();
				_gameObject->getBody()->emitMessage(message);

				_soundsResources->playSound("ShadowSongChannel");
				_soundsResources->playAndDestroySound("DeepIntoShadow", 0.5);
			}
		}
	} // changeState

	void CPlayerManager::tick(float msecs)
	{
		// Llamar al método de la clase padre (IMPORTANTE).
		IComponent::tick(msecs);

		_onLight = playerOnLight();

		if (_onLight)
		{
			// Reseteamos el contador para la muerte
			_deathTimeElapsed = 0.0;
			//std::cout << "Resetar tiempo de morir" << std::endl;
		}
		else
		{
			// Si ya no estoy en la luz paso al estado body
			if (_gameObject->_state == GameObject::SHADOW)
				changeState(GameObject::BODY);

			// Y empezamos a morirnos
			if (!_onLight && _playerCanDie){
				_deathTimeElapsed += msecs;
				//std::cout << "Tiempo que llevo fuera de la luz " << _deathTimeElapsed << std::endl;
				if (_deathTimeElapsed >= _playerDeathTime){
					Logic::TMessage m;
					m._type = Logic::Message::PLAYER_EVENT;
					m.setArg<std::string>(std::string("playerEvent"), std::string("die"));
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
			b = b || chargeArea->_playerInside;
		}

		return b;

	} // playerOnLight

	CGameObject* CPlayerManager::canPickAnyCharge() const
	{
		CChargeInteractuable* chargeArea;

		for (CGameObject* charge : _chargesOnMap)
		{
			chargeArea = (CChargeInteractuable*)(charge->getBody()->getComponent("CChargeInteractuable"));
			if (chargeArea->_canInteract)
				return charge;
		}

		return nullptr;

	} // canPickAnyCharge

} // namespace Logic
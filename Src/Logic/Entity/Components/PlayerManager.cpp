#include "PlayerManager.h"

#include "Application/GameState.h"
#include "Logic/Entity/GameObject.h"
#include "Logic/Events/Event.h"
#include "Logic/Maps/EntityFactory.h"
#include "Map/MapEntity.h"

#include "Logic/Entity/Components/LightingArea.h"
#include "Logic/Entity/Components/ChargeInteractuable.h"
#include "Logic/Entity/Components/PhysicController.h"
#include "Logic/Entity/Components/AvatarController.h"
#include "Logic/Entity/Components/AnimatedGraphics.h"


namespace Logic
{
	IMP_FACTORY(CPlayerManager);

	CPlayerManager::CPlayerManager()
		: IComponent(), _onLight(false), _deathTimeElapsed(0.0),
		_playerDeathTime(3.0), _kasaiName(""), _kasai(nullptr),
		_chargePrefab(""), _chargesOwned(3), _playerCanDie(false), 
		_pickObjectAnimation(""), _chargesCount(0)
	{
		_soundsResources = Sounds::CSoundsResources::getSingletonPtr();
		_soundsResources->createSound(std::string("ShadowSongChannel"), std::string("ShadowSong"));
	} // CPlayerManager

	CPlayerManager::~CPlayerManager()
	{
		if (_kasai)
		{
			_kasai = nullptr;
		}
		if (_soundsResources)
		{
			_soundsResources->deleteSound(std::string("ShadowSongChannel"));
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
			_playerDeathTime = entityInfo->getFloatAttribute("playerDeathTime");

		if (entityInfo->hasAttribute("playerCanDie"))
			_playerCanDie = entityInfo->getBoolAttribute("playerCanDie");

		if (entityInfo->hasAttribute("pickObjectAnimation"))
			_pickObjectAnimation = entityInfo->getStringAttribute("pickObjectAnimation");

		if (entityInfo->hasAttribute("chargesOwned"))
			_chargesOwned = entityInfo->getIntAttribute("chargesOwned");

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
			message._type == Message::PICK_FROM_DEATH_CHARGE;

	} // accept

	void CPlayerManager::process(const TMessage &message)
	{
		CGameObject* chargeInRange = nullptr;
		CEntity* deathCharge = nullptr;
		TMessage m;
		std::string playerEvent;
		bool falling;
		

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

			/**
			If charge is in range and the player is 
			on ground, we can pick the charge.
			*/
			falling = ((CPhysicController*)_gameObject->getComponentInChildren(GameObject::BODY ,"CPhysicController"))->playerFalling();
			if (chargeInRange && !falling)
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
				// Si la carga grafica ha llegado al centro del raton
				if (message.existArg("chargeOnMouseposition"))
				{
					// Instanciamos la carga en el mapa
					Vector3 pos = message.getArg<Vector3>("instancePosition");
					std::stringstream ss;
					ss << pos.x << " " << pos.y << " " << 0;
					std::string chargePosition = ss.str();
					ss.str(std::string());
					_chargesCount = (_chargesCount + 1) % 9;
					ss << "Charge" << _chargesCount;
					std::string chargeName = ss.str();
					CGameObject* newCharge = Logic::CMap::instantiatePrefab(_chargePrefab, chargeName, chargePosition);

					// La metemos en el vector de referencias
					_chargesOnMap.push_back(newCharge);

					// La activamos
					newCharge->activate();

					// Decrementamos el número de cargas que poseemos
					_chargesOwned--;
				}
				// Si la carga que queremos lanzar no esta en el centro del 
				// raton, enviamos un mensaje para que lo haga
				else
				{
					TMessage m;
					m._type = Message::PUT_CHARGE;
					_kasai->emitMessage(m);
				}
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
			//TMessage message;
			//message._type = Message::SEND_STATE;

			// Cambio de sombra a cuerpo
			if (state == GameObject::BODY)
			{
				// Establecemos el estado nuevo del game object
				_gameObject->_state = GameObject::BODY;

				// Le decimos a la sombra que mande su estado al cuerpo
				sendState(_gameObject->_shadow, _gameObject->_body);

				// Sonido de inmersion
				_soundsResources->pauseSound(std::string("ShadowSongChannel"));
				_soundsResources->playAndDestroySound(std::string("DeepIntoShadow"), 0.5, 0, Vector3(0,0,0), Vector3(0,0,0));
			}
			// Cambio de cuerpo a sombra
			else
			{
				// Establecemos el estado nuevo del game object
				_gameObject->_state = GameObject::SHADOW;

				// Le decimos al cuerpo que mande su estado a la sombra
				sendState(_gameObject->_body, _gameObject->_shadow);

				// Sonido de inmersion
				_soundsResources->pauseSound(std::string("ShadowSongChannel"));
				_soundsResources->playAndDestroySound(std::string("DeepIntoShadow"), 0.5, 0, Vector3(0, 0, 0), Vector3(0, 0, 0));
			}
		}
	} // changeState

	void CPlayerManager::sendState(Logic::CEntity* emitter, Logic::CEntity* receiver)
	{
		// Mandamos la posición de la entidad
		Vector3 emitterPos = emitter->getPosition();
		Vector3 receiverPos = receiver->getPosition();
		receiver->setPosition(Vector3(emitterPos.x, emitterPos.y, receiverPos.z)); // La z se mantiene

		// CAvatarController
		CAvatarController* emitterAvatarController = (CAvatarController*)emitter->getComponent("CAvatarController");
		CAvatarController* receiverAvatarController = (CAvatarController*)receiver->getComponent("CAvatarController");
		emitterAvatarController->sendState(receiverAvatarController);
		
		// CPhysicController
		CPhysicController* emitterPhysicController = (CPhysicController*)emitter->getComponent("CPhysicController");
		CPhysicController* receiverPhysicController = (CPhysicController*)receiver->getComponent("CPhysicController");
		emitterPhysicController->sendState(receiverPhysicController);

		// CAnimatedGraphics
		CAnimatedGraphics* emitterAnimatedGraphics = (CAnimatedGraphics*)emitter->getComponent("CAnimatedGraphics");
		CAnimatedGraphics* receiverAnimatedGraphics = (CAnimatedGraphics*)receiver->getComponent("CAnimatedGraphics");
		emitterAnimatedGraphics->sendState(receiverAnimatedGraphics);

		// Desactivamos el emitter
		emitter->deactivate();

		// Activamos el receiver
		receiver->activate();
	}

	void CPlayerManager::tick(float msecs)
	{
		// Llamar al método de la clase padre (IMPORTANTE).
		IComponent::tick(msecs);

		_onLight = playerOnLight();

		Logic::TMessage m;

		if (_onLight)
		{
			m._type = Logic::Message::CHANGE_MATERIAL;
			m.setArg<std::string>("materialName", "PlayerLight");
			_gameObject->getBody()->emitMessage(m);
			// Reseteamos el contador para la muerte
			_deathTimeElapsed = 0.0;
			//std::cout << "Resetar tiempo de morir" << std::endl;
		}
		else
		{
			m._type = Logic::Message::CHANGE_MATERIAL;
			m.setArg<std::string>("materialName", "Player");
			_gameObject->getBody()->emitMessage(m);

			// Si ya no estoy en la luz paso al estado body
			if (_gameObject->_state == GameObject::SHADOW)
				changeState(GameObject::BODY);

			// Y empezamos a morirnos
			if (!_onLight && _playerCanDie){
				_deathTimeElapsed += msecs;
				//std::cout << "Tiempo que llevo fuera de la luz " << _deathTimeElapsed << std::endl;
				if (_deathTimeElapsed >= _playerDeathTime){
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
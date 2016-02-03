#include "GameObject.h"

#include "Component.h"

#include "Logic/Server.h"

#include "Map/MapEntity.h"

#include "GUI/Server.h"
#include "GUI/PlayerController.h"
#include "GUI/LightController.h"

namespace Logic
{
	CGameObject::CGameObject(TEntityID gameObjectID)
		: _gameObjectID(gameObjectID), _body(nullptr), _shadow(nullptr), 
		_map(nullptr), _blueprint(""), _name(""), _isPlayer(false), _isLight(false)
	{

	} // CGameObject

	CGameObject::~CGameObject()
	{
		destroyAllComponents();

	} // ~CGameObject

	bool CGameObject::spawn(CMap *map, const Map::CEntity *entityInfo)
	{
		// Leemos las propiedades comunes
		_blueprint = entityInfo->getBlueprint();
		_map = map;

		if (entityInfo->hasAttribute("name"))
			_name = entityInfo->getStringAttribute("name");

		if (entityInfo->hasAttribute("isPlayer"))
			_isPlayer = entityInfo->getBoolAttribute("isPlayer");

		if (entityInfo->hasAttribute("isLight"))
			_isLight = entityInfo->getBoolAttribute("isLight");

		// Inicializamos los componentes
		TComponentList::const_iterator it;

		bool correct = true;

		for (it = _components.begin(); it != _components.end() && correct; ++it)
			correct = (*it)->spawn(this, map, entityInfo) && correct;

		return correct;

	} // spawn

	void CGameObject::setBody(CEntity* body){
		_body = body;

	} // setBody

	void CGameObject::setShadow(CEntity* shadow)
	{
		_shadow = shadow;

	} // setShadow

	CEntity* CGameObject::getBody() const
	{
		return _body;

	} // getBody

	CEntity* CGameObject::getShadow() const
	{
		return _shadow;

	} // getShadow

	bool CGameObject::activate()
	{
		// Si somos jugador, se lo decimos al servidor
		// y nos registramos para que nos informen
		// de los movimientos que debemos realizar
		if (isPlayer())
		{
			CServer::getSingletonPtr()->setPlayer(_body);
			GUI::CServer::getSingletonPtr()->getPlayerController()->setControlledAvatar(this);
		}

		if (isLight()){
			GUI::CServer::getSingletonPtr()->getLightController()->setControlledLight(this);
		}

		// Solo si se activan todos los componentes y las entidades de cuerpo
		// y sombra nos consideraremos activados
		_activated = true;

		// Activamos los componentes
		TComponentList::const_iterator it;

		for (it = _components.begin(); it != _components.end(); ++it)
			_activated = (*it)->activate() && _activated;

		_activated = true;
		if (_body)
			_activated = _body->activate() && _activated;

		if (_shadow)
			_activated = _shadow->activate() && _activated;

		return _activated;

	} // activate

	void CGameObject::deactivate()
	{
		// Si éramos el jugador, le decimos al servidor que ya no hay.
		// y evitamos que se nos siga informando de los movimientos que 
		// debemos realizar
		if (isPlayer())
		{
			GUI::CServer::getSingletonPtr()->getPlayerController()->setControlledAvatar(nullptr);
			CServer::getSingletonPtr()->setPlayer(nullptr);
		}

		if (isLight()){
			GUI::CServer::getSingletonPtr()->getLightController()->setControlledLight(nullptr);
		}

		_activated = false;

		TComponentList::const_iterator it;

		// Desactivamos los componentes
		for (it = _components.begin(); it != _components.end(); ++it)
			(*it)->deactivate();

		if (_body)
			_body->deactivate();

		if (_shadow)
			_shadow->deactivate();

	} // deactivate

	bool CGameObject::isActivated()
	{
		return _activated;

	} // isActivated

	void CGameObject::tick(unsigned int msecs)
	{
		TComponentList::const_iterator it;

		for (it = _components.begin(); it != _components.end(); ++it)
			(*it)->tick(msecs);

		if (_body && _body->isActivated())
			_body->tick(msecs);

		if (_shadow && _shadow->isActivated())
			_shadow->tick(msecs);

	} // tick

	void CGameObject::addComponent(IComponent* component)
	{
		_components.push_back(component);
		component->setGameObject(this);

	} // addComponent

	bool CGameObject::removeComponent(IComponent* component)
	{
		TComponentList::const_iterator it = _components.begin();

		bool removed = false;
		// Buscamos el componente hasta el final, por si aparecía
		// más de una vez... (no tendría mucho sentido, pero por si
		// acaso).
		while (it != _components.end())
		{
			if (*it == component)
			{
				it = _components.erase(it);
				removed = true;
			}
			else
				++it;
		}
		if (removed)
			component->setEntity(0);
		return removed;

	} // removeComponent

	void CGameObject::destroyAllComponents()
	{
		IComponent* c;
		while (!_components.empty())
		{
			c = _components.back();
			_components.pop_back();
			delete c;
		}

	} // destroyAllComponents

	bool CGameObject::emitMessage(const TMessage &message, IComponent* emitter)
	{
		TComponentList::const_iterator it;
		// Para saber si alguien quiso el mensaje.
		bool anyReceiver = false;
		for (it = _components.begin(); it != _components.end(); ++it)
		{
			// Al emisor no se le envia el mensaje.
			if (emitter != (*it))
				anyReceiver = (*it)->set(message) || anyReceiver;
		}

		if (_body && _body->isActivated())
			anyReceiver = _body->emitMessage(message) || anyReceiver;

		if (_shadow && _shadow->isActivated())
			anyReceiver = _shadow->emitMessage(message) || anyReceiver;

		return anyReceiver;
	} // emitMessage

	Logic::TEntityID CGameObject::getGameObjectID() const 
	{ 
		return _gameObjectID; 

	} // getGameObjectID

	CMap* CGameObject::getMap() 
	{ 
		return _map; 

	} // getMap

	const std::string& CGameObject::getName() const 
	{ 
		return _name; 

	} // getName

	const std::string& CGameObject::getBlueprint() const 
	{ 
		return _blueprint; 

	} // getBlueprint

} // namespace Logic
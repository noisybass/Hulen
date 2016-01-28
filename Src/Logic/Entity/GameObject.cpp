#include "GameObject.h"

#include "Component.h"

#include "Map/MapEntity.h"

namespace Logic
{
	CGameObject::CGameObject(TEntityID gameObjectID)
		: _gameObjectID(gameObjectID), _body(nullptr), _shadow(nullptr), 
		_map(nullptr), _blueprint(""), _name("")
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

		if (entityInfo->hasAttribute("name"))
			_name = entityInfo->getStringAttribute("name");

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
		_activated = true;
		_body->activate();

	} // activate

	void CGameObject::deactivate()
	{
		_activated = false;
		_body->deactivate();

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
		component->setEntity(this);

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
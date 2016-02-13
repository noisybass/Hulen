/**
@file Entity.cpp

Contiene la implementación de la clase Entity, que representa una entidad
de juego. Es una colección de componentes.

@see Logic::CEntity
@see Logic::IComponent

@author David Llansó
@date Julio, 2010
*/

#include "Entity.h"

// Componentes
#include "Component.h"


#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

namespace Logic 
{
	CEntity::CEntity() 
		: _gameObject(nullptr), _blueprint(""), _name(""), _transform(Matrix4::IDENTITY),
		_activated(false), _changeState(false)
	{

	} // CEntity
	
	//---------------------------------------------------------

	CEntity::~CEntity()
	{
		destroyAllComponents();
		_gameObject = nullptr;

	} // ~CEntity
	
	//---------------------------------------------------------

	bool CEntity::spawn(CGameObject* gameObject, CMap *map, const Map::CEntity *entityInfo)
	{
		// Leemos las propiedades comunes
		_blueprint = entityInfo->getBlueprint();
		_gameObject = gameObject;	

		if(entityInfo->hasAttribute("name"))
			_name = entityInfo->getStringAttribute("name");

		if(entityInfo->hasAttribute("position"))
		{
			Vector3 position = entityInfo->getVector3Attribute("position");
			_transform.setTrans(position);
		}

		// Por comodidad en el mapa escribimos los ángulos en grados.
		if(entityInfo->hasAttribute("orientation"))
		{
			float yaw = Math::fromDegreesToRadians(entityInfo->getFloatAttribute("orientation"));
			Math::yaw(yaw,_transform);
		}

		// Inicializamos los componentes
		TComponentList::const_iterator it;

		bool correct = true;

		for( it = _components.begin(); it != _components.end() && correct; ++it )
			correct = (*it)->spawn(this, map, entityInfo) && correct;

		return correct;

	} // spawn

	//---------------------------------------------------------

	bool CEntity::activate() 
	{	
		// Activamos los componentes
		TComponentList::const_iterator it;

		// Solo si se activan todos los componentes correctamente nos
		// consideraremos activados.
		_activated = true;

		for( it = _components.begin(); it != _components.end(); ++it )
			_activated = (*it)->activate() && _activated;


		return _activated;

	} // activate

	//---------------------------------------------------------

	void CEntity::deactivate() 
	{
		TComponentList::const_iterator it;

		// Desactivamos los componentes
		for( it = _components.begin(); it != _components.end(); ++it )
			(*it)->deactivate();

		_activated = false;

	} // deactivate

	//---------------------------------------------------------

	void CEntity::tick(unsigned int msecs) 
	{
		TComponentList::const_iterator it;

		for( it = _components.begin(); it != _components.end(); ++it )
			(*it)->tick(msecs);

		if (_changeState)
		{
			_changeState = false;
			deactivate();
		}

	} // tick

	//---------------------------------------------------------

	void CEntity::addComponent(IComponent* component)
	{
		_components.push_back(component);
		component->setEntity(this);

	} // addComponent

	//---------------------------------------------------------

	bool CEntity::removeComponent(IComponent* component)
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

	//---------------------------------------------------------

	void CEntity::destroyAllComponents()
	{
		IComponent* c;
		while(!_components.empty())
		{
			c = _components.back();
			_components.pop_back();
			delete c;
		}
		
	} // destroyAllComponents

	//---------------------------------------------------------

	bool CEntity::emitMessage(const TMessage &message, IComponent* emitter)
	{
		// Interceptamos los mensajes que además de al resto de los
		// componentes, interesan a la propia entidad.
		TMessage m;
		switch(message._type)
		{
		case Message::SET_TRANSFORM:
			_transform = message.getArg<Matrix4>("transform");
			break;
		case Message::SEND_STATE:
			m._type = Message::RECEIVE_ENTITY_STATE;
			m.setArg<Matrix4>("transform", _transform);

			message.getArg<CEntity*>("receiver")->emitMessage(m);
			_changeState = true;
			break;
		case Message::RECEIVE_ENTITY_STATE:
			setTransform(message.getArg<Matrix4>("transform"));
			break;
		}

		TComponentList::const_iterator it;
		// Para saber si alguien quiso el mensaje.
		bool anyReceiver = false;
		for( it = _components.begin(); it != _components.end(); ++it )
		{
			// Al emisor no se le envia el mensaje.
			if( emitter != (*it) )
				anyReceiver = (*it)->set(message) || anyReceiver;
		}
		return anyReceiver;

	} // emitMessage

	//---------------------------------------------------------

	void CEntity::setTransform(const Matrix4& transform) 
	{
		_transform = transform;

		// Avisamos a los componentes del cambio.
		TMessage message;
		message._type = Message::SET_TRANSFORM;
		message.setArg<Matrix4>(std::string("transform"), _transform);

		emitMessage(message);

	} // setTransform

	//---------------------------------------------------------

	void CEntity::setPosition(const Vector3 &position, IComponent* invoker)  
	{
		_transform.setTrans(position);

		// Avisamos a los componentes del cambio.
		TMessage message;
		message._type = Message::SET_TRANSFORM;
		message.setArg<Matrix4>(std::string("transform"), _transform);

		emitMessage(message,invoker);

	} // setPosition

	//---------------------------------------------------------

	void CEntity::setOrientation(const Matrix3& orientation) 
	{
		_transform = orientation;

		// Avisamos a los componentes del cambio.
		TMessage message;
		message._type = Message::SET_TRANSFORM;
		message.setArg<Matrix4>(std::string("transform"), _transform);

		emitMessage(message);

	} // setOrientation

	//---------------------------------------------------------

	Matrix3 CEntity::getOrientation() const
	{
		Matrix3 orientation;
		_transform.extract3x3Matrix(orientation);
		return orientation;

	} // getOrientation

	//---------------------------------------------------------

	void CEntity::setYaw(float yaw)
	{
		Math::setYaw(yaw, _transform);

		// Avisamos a los componentes del cambio.
		TMessage message;
		message._type = Message::SET_TRANSFORM;
		message.setArg<Matrix4>(std::string("transform"), _transform);

		emitMessage(message);

	} // setYaw

	CGameObject* CEntity::getGameObject() const
	{
		return _gameObject;

	} // getGameObject

} // namespace Logic

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
#include "GameObject.h"

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
		TComponentMap::const_iterator it;

		bool correct = true;

		for( it = _components.begin(); it != _components.end() && correct; ++it )
			correct = it->second->spawn(it->first, this, map, entityInfo) && correct;

		return correct;

	} // spawn

	//---------------------------------------------------------

	bool CEntity::activate() 
	{	
		// Activamos los componentes
		TComponentMap::const_iterator it;

		// Solo si se activan todos los componentes correctamente nos
		// consideraremos activados.
		_activated = true;

		for( it = _components.begin(); it != _components.end(); ++it )
			_activated = it->second->activate() && _activated;


		return _activated;

	} // activate

	//---------------------------------------------------------

	void CEntity::deactivate() 
	{
		TComponentMap::const_iterator it;

		// Desactivamos los componentes
		for( it = _components.begin(); it != _components.end(); ++it )
			it->second->deactivate();

		_activated = false;

	} // deactivate

	//---------------------------------------------------------

	void CEntity::tick(unsigned int msecs) 
	{
		TComponentMap::const_iterator it;

		for( it = _components.begin(); it != _components.end(); ++it )
			it->second->tick(msecs);

		if (_changeState)
		{
			_changeState = false;
			deactivate();
		}

	} // tick

	//---------------------------------------------------------

	void CEntity::addComponent(const std::string& name, IComponent* component)
	{
		_components.emplace(name, component);
		component->setEntity(this);

	} // addComponent

	//---------------------------------------------------------

	bool CEntity::removeComponent(const std::string& name)
	{
		TComponentMap::const_iterator it = _components.find(name);
		IComponent* c;

		if (it != _components.end())
		{
			c = it->second;
			_components.erase(name);
			delete c;

			return true;
		}

		return false;

	} // removeComponent

	//---------------------------------------------------------

	void CEntity::destroyAllComponents()
	{
		IComponent* c;
		for (auto it = _components.begin(); it != _components.end(); ++it)
		{
			c = it->second;
			delete c;
		}
			
		_components.clear();
		
	} // destroyAllComponents

	//---------------------------------------------------------

	bool CEntity::emitMessage(const TMessage &message, IComponent* emitter)
	{
		// Interceptamos los mensajes que además de al resto de los
		// componentes, interesan a la propia entidad.
		TMessage m;
		Vector3 receiverPosition, senderPosition;
		switch(message._type)
		{
		case Message::SET_TRANSFORM:
			_transform = message.getArg<Matrix4>("transform");
			break;
		case Message::SEND_STATE:
			m._type = Message::RECEIVE_ENTITY_STATE;
			receiverPosition = message.getArg<CEntity*>("receiver")->getPosition();
			senderPosition = getPosition();
			m.setArg<Vector3>("entityPosition", Vector3(senderPosition.x, senderPosition.y, receiverPosition.z));

			message.getArg<CEntity*>("receiver")->emitMessage(m);
			_changeState = true;
			break;
		case Message::RECEIVE_ENTITY_STATE:
			setPosition(message.getArg<Vector3>("entityPosition"));
			break;
		}

		TComponentMap::const_iterator it;
		// Para saber si alguien quiso el mensaje.
		bool anyReceiver = false;
		for( it = _components.begin(); it != _components.end(); ++it )
		{
			// Al emisor no se le envia el mensaje.
			if( emitter != it->second )
				anyReceiver = it->second->set(message) || anyReceiver;
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

	//---------------------------------------------------------

	CGameObject* CEntity::getGameObject() const
	{
		return _gameObject;

	} // getGameObject

	//---------------------------------------------------------

	IComponent* CEntity::getComponent(const std::string& name)
	{
		TComponentMap::const_iterator it = _components.find(name);

		if (it != _components.end())
			return it->second;

		return nullptr;
	}

} // namespace Logic

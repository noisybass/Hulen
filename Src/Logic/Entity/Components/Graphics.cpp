/**
@file Graphics.cpp

Contiene la implementación del componente que controla la representación
gráfica de la entidad.
 
@see Logic::CGraphics
@see Logic::IComponent

@author David Llansó
@date Agosto, 2010
*/

#include "Graphics.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/GameObject.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Scene.h"
#include "Graphics/Entity.h"
#include "Graphics/StaticEntity.h"

namespace Logic 
{
	IMP_FACTORY(CGraphics);
	
	//---------------------------------------------------------

	CGraphics::~CGraphics() 
	{
		if(_graphicsEntity)
		{
			_scene->removeEntity(_graphicsEntity);
			delete _graphicsEntity;
			_graphicsEntity = nullptr;
		}

	} // ~CGraphics
	
	//---------------------------------------------------------

	bool CGraphics::spawn(const std::string& name, CEntity *entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if(!IComponent::spawn(name, entity,map,entityInfo))
			return false;
		
		_scene = _entity->getGameObject()->getMap()->getScene();
		_gameObject = _entity->getGameObject();

		if(entityInfo->hasAttribute("model"))
			_model = entityInfo->getStringAttribute("model");

		_graphicsEntity = createGraphicsEntity(entityInfo);
		if(!_graphicsEntity)
			return false;

		if (entityInfo->hasAttribute("material")){
			_material = entityInfo->getStringAttribute("material");
			_graphicsEntity->setMaterial(_material);
		}
		// Si existe un _gameobject le ponemos el material por defecto
		else if (_gameObject){
			_material = _gameObject->getDefaultMaterial(entityInfo->getStringAttribute("type"));
			_graphicsEntity->setMaterial(_material);
		}
		

		if (entityInfo->hasAttribute("guizmoSize"))
			_guizmoSize = entityInfo->getIntAttribute("guizmoSize");

		if (entityInfo->hasAttribute("guizmo")){
			_guizmo= entityInfo->getBoolAttribute("guizmo");
			_graphicsEntity->drawGuizmo(_guizmoSize);
		}

		return true;

	} // spawn
	
	//---------------------------------------------------------

	Graphics::CEntity* CGraphics::createGraphicsEntity(const Map::CEntity *entityInfo)
	{
		bool isStatic = false;
		if(entityInfo->hasAttribute("static"))
			isStatic = entityInfo->getBoolAttribute("static");

		if (entityInfo->hasAttribute("scale"))
			_scale = entityInfo->getVector3Attribute("scale");

		if(isStatic)
		{
			_graphicsEntity = new Graphics::CStaticEntity(_entity->getName(),_model);
			if(!_scene->addStaticEntity((Graphics::CStaticEntity*)_graphicsEntity))
				return 0;
		}
		else
		{
			_graphicsEntity = new Graphics::CEntity(_entity->getName(),_model);
			if(!_scene->addEntity(_graphicsEntity))
				return 0;
		}

		//Importante: La escala debe ser ajustada después de que se haya creada la entidad gráfica y se haya añadido a la escena gráfica.
		//Sino, al escalar dara un fallo de que no existe el nodo correspondiente en Ogre (la entidad gráfica no está creada).

		if (entityInfo->hasAttribute("scale")){
			_scale = entityInfo->getVector3Attribute("scale");
			_graphicsEntity->setScale(_scale);
		}

		_graphicsEntity->setTransform(_entity->getTransform());
		
		return _graphicsEntity;

	} // createGraphicsEntity

	//---------------------------------------------------------

	bool CGraphics::accept(const TMessage &message)
	{
		return message._type == Message::SET_TRANSFORM ||
			   message._type == Message::AMBIENT_LIGHT_SET_FOR_DEBUG ||
			   message._type == Message::AMBIENT_LIGHT_SET_REAL_MATERIAL;

	} // accept
	
	//---------------------------------------------------------

	void CGraphics::process(const TMessage &message)
	{
		switch(message._type)
		{
		case Message::SET_TRANSFORM:
			_graphicsEntity->setTransform(message.getArg<Matrix4>("transform"));
			break;
		case Message::AMBIENT_LIGHT_SET_FOR_DEBUG:
			if (_model == "Cube.mesh"){
				_graphicsEntity->setMaterial(message.getArg<std::string>("ambient_light_set_for_debug"));
			}
			break;
		case Message::AMBIENT_LIGHT_SET_REAL_MATERIAL:
			if (_model == "Cube.mesh"){
				_graphicsEntity->setMaterial(_material);
			}
			break;
		}

	} // process

} // namespace Logic


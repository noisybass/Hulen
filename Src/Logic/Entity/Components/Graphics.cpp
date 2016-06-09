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
#include "Graphics/Server.h"

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

		bool fromFile = true;
		if (entityInfo->hasAttribute("graphic_file"))
			fromFile = entityInfo->getBoolAttribute("graphic_file");

		if (fromFile)
		{
			assert(entityInfo->hasAttribute("model") && "No se ha especificado modelo para la entidad gráfica");
			_model = entityInfo->getStringAttribute("model");
			_graphicsEntity = createGraphicsEntityFromFile(entityInfo);
		}
		else
		{
			// En caso de no tener modelo el nombre que se le va a dar a la malla es el mismo que el de la entidad
			_model = _entity->getName();
			_graphicsEntity = createGraphicsEntity(entityInfo);
		}


		if(!_graphicsEntity)
			return false;

		//_entity->setNode(_graphicsEntity->getNode());

		if (entityInfo->hasAttribute("material"))
			setMaterial(entityInfo->getStringAttribute("material"));
			
		// Si existe un _gameobject le ponemos el material por defecto
		else if (_gameObject){
			_material = _gameObject->getDefaultMaterial(entityInfo->getStringAttribute("type"));
			_graphicsEntity->setMaterial(_material);
		}
		

		/*if (entityInfo->hasAttribute("guizmoSize"))
			_guizmoSize = entityInfo->getIntAttribute("guizmoSize");

		if (entityInfo->hasAttribute("guizmo")){
			_guizmo= entityInfo->getBoolAttribute("guizmo");
			_graphicsEntity->drawGuizmo(_guizmoSize);
		}
*/
		return true;

	} // spawn
	
	//---------------------------------------------------------

	Graphics::CEntity* CGraphics::createGraphicsEntityFromFile(const Map::CEntity *entityInfo)
	{
		bool isStatic = false;
		if(entityInfo->hasAttribute("static"))
			isStatic = entityInfo->getBoolAttribute("static");

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

		_graphicsEntity->setPosition(_entity->getPosition());
		
		return _graphicsEntity;

	} // createGraphicsEntity

	Graphics::CEntity* CGraphics::createGraphicsEntity(const Map::CEntity *entityInfo)
	{
		assert(entityInfo->hasAttribute("graphic_type") && "No se ha especificado tipo para la malla");

		std::string type = entityInfo->getStringAttribute("graphic_type");

		if (type == "plane")
		{
			assert(entityInfo->hasAttribute("graphic_up_vector") && "No se ha especificado vector perpendicular al plano");
			Vector3 upVector = entityInfo->getVector3Attribute("graphic_up_vector");

			assert(entityInfo->hasAttribute("graphic_parallel_vector") && "No se ha especificado vector paralelo al plano");
			Vector3 parallelVector = entityInfo->getVector3Attribute("graphic_parallel_vector");

			assert(entityInfo->hasAttribute("graphic_width") && "No se ha especificado el ancho del plano");
			float width = entityInfo->getFloatAttribute("graphic_width");

			assert(entityInfo->hasAttribute("graphic_height") && "No se ha especificado el alto del plano");
			float height = entityInfo->getFloatAttribute("graphic_height");

			int xSegments = 1;
			if (entityInfo->hasAttribute("graphic_x_segments"))
				xSegments = entityInfo->getIntAttribute("graphic_x_segments");

			int ySegments = 1;
			if (entityInfo->hasAttribute("graphic_y_segments"))
				ySegments = entityInfo->getIntAttribute("graphic_y_segments");

			bool normals = true;
			if (entityInfo->hasAttribute("graphic_normals"))
				normals = entityInfo->getBoolAttribute("graphic_normals");

			float uTile = width / 5.0f;

			float vTile = height / 5.0f;

			Graphics::CServer::getSingletonPtr()->createPlane(upVector, parallelVector, _model, width, height, xSegments, ySegments, normals, uTile, vTile);
			_graphicsEntity = new Graphics::CStaticEntity(_entity->getName(), _model);

			if (!_scene->addStaticEntity((Graphics::CStaticEntity*)_graphicsEntity))
				return 0;
		}

		_graphicsEntity->setPosition(_entity->getPosition());
		return _graphicsEntity;
	}

	//---------------------------------------------------------

	bool CGraphics::accept(const TMessage &message)
	{
		return message._type == Message::SET_POSITION ||
			   message._type == Message::AMBIENT_LIGHT_SET_FOR_DEBUG ||
			   message._type == Message::AMBIENT_LIGHT_SET_REAL_MATERIAL ||
			   message._type == Message::ROLL_ENTITY_NODE ||
			   message._type == Message::CHANGE_MATERIAL;

	} // accept
	
	//---------------------------------------------------------

	void CGraphics::process(const TMessage &message)
	{
		switch(message._type)
		{
		case Message::SET_POSITION:
			_graphicsEntity->setPosition(message.getArg<Vector3>("newPosition"));
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
		case Message::ROLL_ENTITY_NODE:
			_graphicsEntity->rollEntityNode(message.getArg<int>("degrees"));
			break;
		case Message::CHANGE_MATERIAL:
			setMaterial(message.getArg<std::string>("materialName"));
			break;
		}

	} // process

	void CGraphics::setMaterial(std::string material)
	{
		_material = material;
		_graphicsEntity->setMaterial(material);

	} // setMaterial

} // namespace Logic


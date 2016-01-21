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
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Scene.h"
#include "Graphics/Entity.h"
#include "Graphics/StaticEntity.h"

//#include "../../../dependencies/include/OGRE/OgreMeshManager.h"
#include "../../../dependencies/include/OGRE/OgreManualObject.h"
#include "../../../dependencies/include/OGRE/OgreMaterialManager.h"
#include "../../../dependencies/include/OGRE/OgreTechnique.h"

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
			_graphicsEntity = 0;
		}

	} // ~CGraphics
	
	//---------------------------------------------------------

	bool CGraphics::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		_scene = _entity->getMap()->getScene();

		if(entityInfo->hasAttribute("model"))
			_model = entityInfo->getStringAttribute("model");

		_graphicsEntity = createGraphicsEntity(entityInfo);
		if(!_graphicsEntity)
			return false;

		if (entityInfo->hasAttribute("guizmoSize"))
			_guizmo.size = entityInfo->getIntAttribute("guizmoSize");

		if (entityInfo->hasAttribute("guizmo")){
			_guizmo.exist = entityInfo->getBoolAttribute("guizmo");
			drawGuizmo(_guizmo.size);
		}

		return true;

	} // spawn
	
	//---------------------------------------------------------

	Graphics::CEntity* CGraphics::createGraphicsEntity(const Map::CEntity *entityInfo)
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

		_graphicsEntity->setTransform(_entity->getTransform());
		
		return _graphicsEntity;

	} // createGraphicsEntity
	
	//---------------------------------------------------------

	void CGraphics::drawGuizmo(int size)
	{

		std::string guizmoName;
		Vector3 entityPosition = _entity->getPosition();

		/**
		Creating X Axe (RED)
		*/
		Ogre::ManualObject *xAxe = _scene->createManualObject();

		Ogre::MaterialPtr xAxePtr = Ogre::MaterialManager::getSingleton().create("X-Axe-Mat", "General");
		xAxePtr->setReceiveShadows(false);
		xAxePtr->getTechnique(0)->setLightingEnabled(true);
		xAxePtr->getTechnique(0)->getPass(0)->setDiffuse(0.8, 0.05, 0.05, 1);
		xAxePtr->getTechnique(0)->getPass(0)->setAmbient(0.3, 0.1, 0.1);
		xAxePtr->getTechnique(0)->getPass(0)->setSelfIllumination(1, 0, 0);

		xAxe->begin("X-Axe-Mat", Ogre::RenderOperation::OT_LINE_STRIP);

		xAxe->position(entityPosition.x, entityPosition.y, entityPosition.z); // Center
		xAxe->position(entityPosition.x + size, entityPosition.y, entityPosition.z); // X Axis
		
		xAxe->end();
		guizmoName = _entity->getName() + "X-Axe";
		xAxe->convertToMesh(guizmoName);

		_guizmo.XAxis = new Graphics::CStaticEntity(guizmoName, guizmoName);
		_scene->addEntity(_guizmo.XAxis);

		/**
		Creating Y Axe (GREEN)
		*/
		Ogre::ManualObject *yAxe = _scene->createManualObject();

		Ogre::MaterialPtr YAxePtr = Ogre::MaterialManager::getSingleton().create("Y-Axe-Mat", "General");
		YAxePtr->setReceiveShadows(false);
		YAxePtr->getTechnique(0)->setLightingEnabled(true);
		YAxePtr->getTechnique(0)->getPass(0)->setDiffuse(0.2, 0.2, 0.2, 1);
		YAxePtr->getTechnique(0)->getPass(0)->setAmbient(0.1, 0.3, 0.1);
		YAxePtr->getTechnique(0)->getPass(0)->setSelfIllumination(0, 1, 0);

		yAxe->begin("Y-Axe-Mat", Ogre::RenderOperation::OT_LINE_STRIP);
		 

		yAxe->position(entityPosition.x, entityPosition.y, entityPosition.z); // Center
		yAxe->position(entityPosition.x, entityPosition.y + size, entityPosition.z); // Y Axis

		yAxe->end();
		guizmoName = _entity->getName() + "Y-Axe";
		yAxe->convertToMesh(guizmoName);

		_guizmo.YAxis = new Graphics::CStaticEntity(guizmoName, guizmoName);
		_scene->addEntity(_guizmo.YAxis);

		/**
		Creating Z Axe (BLUE)
		*/
		Ogre::ManualObject *zAxe = _scene->createManualObject();

		Ogre::MaterialPtr zAxePtr = Ogre::MaterialManager::getSingleton().create("Z-Axe-Mat", "General");
		zAxePtr->setReceiveShadows(false);
		zAxePtr->getTechnique(0)->setLightingEnabled(true);
		zAxePtr->getTechnique(0)->getPass(0)->setDiffuse(0.1, 0.2, 0.7, 1);
		zAxePtr->getTechnique(0)->getPass(0)->setAmbient(0.3, 0.3, 0.3);
		zAxePtr->getTechnique(0)->getPass(0)->setSelfIllumination(0, 0, 1);

		zAxe->begin("Z-Axe-Mat", Ogre::RenderOperation::OT_LINE_STRIP);

		zAxe->position(entityPosition.x, entityPosition.y, entityPosition.z); // Center
		zAxe->position(entityPosition.x, entityPosition.y, entityPosition.z + size); // ZAxis

		zAxe->end();
		guizmoName = _entity->getName() + "Z-Axe";
		zAxe->convertToMesh(guizmoName);

		_guizmo.ZAxis = new Graphics::CStaticEntity(guizmoName, guizmoName);
		_scene->addEntity(_guizmo.ZAxis);

		/*
		
		manualObject->colour(1, 0, 0);
		manualObject->position(entityPosition.x, entityPosition.y, entityPosition.z); // Center
		manualObject->position(entityPosition.x, entityPosition.y + size, entityPosition.z); // Y Axis
		manualObject->colour(0, 1, 0);
		manualObject->position(entityPosition.x, entityPosition.y, entityPosition.z); // Center
		manualObject->position(entityPosition.x, entityPosition.y, entityPosition.z + size); // ZAxis
		manualObject->colour(0, 0, 1);
		
		Ogre::MeshPtr guizmoMesh = Ogre::MeshManager::getSingleton().createManual("Guizmo", "General");

		Ogre::SubMesh* sub = guizmoMesh->createSubMesh();

		float sqrt13 = 0.577350269f; // sqrt(1/3) 

		// Define the vertices
		const size_t nVertices = 4;
		const size_t vbufCount = 3 * 2 * nVertices;
		Vector3 entityPosition = _entity->getPosition();
		
		float vertices[vbufCount] = {
			entityPosition.x, entityPosition.y, entityPosition.z,		// Center Position (0,0,0)
			sqrt13, sqrt13, sqrt13,										// Center Position (0,0,0)
			entityPosition.x + size, entityPosition.y, entityPosition.z,// X axis (X,0,0)
			sqrt13, sqrt13, sqrt13,										// X axis (X,0,0)
			entityPosition.x, entityPosition.y + size, entityPosition.z,// Y axis (0,Y,0)
			sqrt13, sqrt13, sqrt13,										// Y axis (0,Y,0)
			entityPosition.x, entityPosition.y, entityPosition.z + size,// Z axis (0,0,Z)
			sqrt13, sqrt13, sqrt13,										// Z axis (0,0,Z)
		};

		Ogre::RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();
		Ogre::RGBA colours[nVertices];
		Ogre::RGBA *pColour = colours;

		// Use render system to convert colour value since colour packing varies
		rs->convertColourValue(Ogre::ColourValue(0.0, 0.0, 0.0), pColour++); //Center Position Colour
		rs->convertColourValue(Ogre::ColourValue(1.0, 0.0, 0.0), pColour++); //X Axis Colour RED
		rs->convertColourValue(Ogre::ColourValue(0.0, 1.0, 0.0), pColour++); //Y Axis Colour GREEN
		rs->convertColourValue(Ogre::ColourValue(0.0, 0.0, 1.0), pColour++); //Z Axis Colour BLUE

		// No define the triangles, We only want the vertex.

		// Create vertex data structure for the vertices shared between submeshes
		guizmoMesh->sharedVertexData = new Ogre::VertexData();
		guizmoMesh->sharedVertexData->vertexCount = nVertices;*/




	} // drawGuizmo

	//---------------------------------------------------------

	bool CGraphics::accept(const TMessage &message)
	{
		return message._type == Message::SET_TRANSFORM;

	} // accept
	
	//---------------------------------------------------------

	void CGraphics::process(const TMessage &message)
	{
		switch(message._type)
		{
		case Message::SET_TRANSFORM:
			_graphicsEntity->setTransform(message._transform);
		}

	} // process

} // namespace Logic


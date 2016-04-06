#include "Entity.h"

#include "BaseSubsystems/Server.h"

#include <assert.h>

#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreManualObject.h>
#include <OgreMaterialManager.h>
#include <OgreTechnique.h>

namespace Graphics 
{
	CEntity::CEntity(const std::string &name, const std::string &mesh)
		: _entity(nullptr), _entityNode(nullptr), _scene(nullptr), _loaded(false), _guizmo()
	{
		_name = name;
		_mesh = mesh;

	} // CEntity

	//--------------------------------------------------------

	CEntity::~CEntity() 
	{
		assert(!_scene && "¡¡Para destruir una entidad esta no puede pertenecer a una escena!!");
		
	} // ~CEntity
	
	//--------------------------------------------------------
		
	bool CEntity::attachToScene(CScene *scene)
	{
		assert(scene && "¡¡La entidad debe asociarse a una escena!!");
		// Si la entidad está cargada por otro gestor de escena.
		if(_loaded && (_scene != scene))
			return false;

		// Si no está cargada forzamos su carga.
		if (!_loaded)
		{
			_scene = scene;
			return load();
		}

		// Si ya estaba cargada en la escena se devuelve cierto.
		return true;

	} // attachToScene
	
	//--------------------------------------------------------
		
	bool CEntity::deattachFromScene()
	{
		// Si la entidad no está cargada no se puede quitar de
		// una escena. Ya que no pertenecerá a ninguna.
		if(!_loaded)
			return false;
		// Si la entidad está cargada forzamos su descarga.
		else
		{
			assert(_scene && "¡¡La entidad debe estar asociada a una escena!!");
			unload();
			_scene = 0;
		}

		return true;

	} // deattachFromScene
	
	//--------------------------------------------------------
		
	bool CEntity::load()
	{
		try
		{
			_entity = _scene->getSceneMgr()->createEntity(_name, _mesh);
		}
		catch(std::exception e)
		{
			return false;
		}
		_entityNode = _scene->getSceneMgr()->getRootSceneNode()->
								createChildSceneNode(_name + "_node");
		_entityNode->attachObject(_entity);
		_loaded = true;

		return true;

	} // load
	
	//--------------------------------------------------------
		
	void CEntity::unload()
	{
		if(_entityNode)
		{
			// desacoplamos la entidad de su nodo
			_entityNode->detachAllObjects();
			_scene->getSceneMgr()->destroySceneNode(_entityNode);
			_entityNode = 0;
		}
		if(_entity)
		{
			_scene->getSceneMgr()->destroyEntity(_entity);
			_entity = 0;
		}
		if (_guizmo.XAxis){
			Ogre::deletePtr(_guizmo.XAxis);
			_guizmo.XAxis = nullptr;
		}
		if (_guizmo.YAxis){
			Ogre::deletePtr(_guizmo.YAxis);
			_guizmo.YAxis = nullptr;
		}
		if (_guizmo.ZAxis){
			Ogre::deletePtr(_guizmo.ZAxis);
			_guizmo.ZAxis = nullptr;
		}

	} // load

	//--------------------------------------------------------
		
	void CEntity::tick(float secs)
	{
	} // tick
	
	//--------------------------------------------------------
		
	void CEntity::setTransform(const Matrix4 &transform)
	{
		assert(_entityNode && "La entidad no ha sido cargada");
		if(_entityNode)
		{
			_entityNode->setPosition(transform.getTrans());
			//_entityNode->setOrientation(transform.extractQuaternion());
		}

	} // setTransform
	
	//--------------------------------------------------------
		
	void CEntity::setOrientation(const Matrix3 &orientation)
	{
		assert(_entityNode && "La entidad no ha sido cargada");
		if(_entityNode)
			_entityNode->setOrientation(orientation);

	} // setOrientation
	
	//--------------------------------------------------------
		
	void CEntity::setVisible(bool visible)
	{
		assert(_entityNode && "La entidad no ha sido cargada");
		if(_entityNode)
			_entityNode->setVisible(visible);

	} // setVisible
	
	//--------------------------------------------------------
		
	const bool CEntity::getVisible()
	{
		if(_entityNode)
			return _entity->isVisible();

		throw new std::exception("La entidad no ha sido cargada");

	} // getPosition
	
	//--------------------------------------------------------
		
	void CEntity::setPosition(const Vector3 &position)
	{
		assert(_entityNode && "La entidad no ha sido cargada");
		if(_entityNode)
			_entityNode->setPosition(position);

	} // setPosition
	
	//--------------------------------------------------------
		
	void CEntity::setScale(const Vector3 &scale)
	{
		assert(_entityNode && "La entidad no ha sido cargada");
		if(_entityNode)
			_entityNode->setScale(scale);

	} // setScale
	
	//--------------------------------------------------------
		
	void CEntity::setScale(const float scale)
	{
		assert(_entityNode && "La entidad no ha sido cargada");
		if(_entityNode)
		{
			Vector3 scaleVector(scale,scale,scale);
			_entityNode->setScale(scaleVector);
		}

	} // setScale

	//--------------------------------------------------------

	void CEntity::drawGuizmo(int size){
	
		std::string guizmoName;

		/**
		Creating X Axe (RED)
		*/
		guizmoName = _entity->getName() + "X-Axe";
		Ogre::ManualObject *xAxe = _scene->getSceneMgr()->createManualObject();

		// We set the material and draw the line
		xAxe->begin("Red", Ogre::RenderOperation::OT_LINE_LIST);
		xAxe->position(0, 0, 0); // Center
		xAxe->position(size, 0, 0); // X Axis
		xAxe->end();
		xAxe->convertToMesh(guizmoName);

		// Create a child Node for the Guizmo, thus we don't have to move the guizmo.
		_guizmo.XAxis = new CEntity(guizmoName, guizmoName);
		_guizmo.XAxis->_entity = _scene->getSceneMgr()->createEntity(guizmoName, guizmoName);
		_guizmo.XAxis->_entityNode = _entityNode->createChildSceneNode(guizmoName);
		_guizmo.XAxis->_entityNode->attachObject(_guizmo.XAxis->_entity);
		_guizmo.XAxis->_loaded = true;
		_scene->addEntity(_guizmo.XAxis);
		_scene->_dynamicEntities.push_back(_guizmo.XAxis);

		/**
		Creating Y Axe (GREEN)
		*/
		guizmoName = _entity->getName() + "Y-Axe";
		Ogre::ManualObject *yAxe = _scene->getSceneMgr()->createManualObject();

		// We set the material and draw the line
		yAxe->begin("Green", Ogre::RenderOperation::OT_LINE_LIST);
		yAxe->position(0, 0, 0); // Center
		yAxe->position(0, size, 0); // Y Axis
		yAxe->end();
		yAxe->convertToMesh(guizmoName);

		// Create a child Node for the Guizmo, thus we don't have to move the guizmo.
		_guizmo.YAxis = new CEntity(guizmoName, guizmoName);
		_guizmo.YAxis->_entity = _scene->getSceneMgr()->createEntity(guizmoName, guizmoName);
		_guizmo.YAxis->_entityNode = _entityNode->createChildSceneNode(guizmoName);
		_guizmo.YAxis->_entityNode->attachObject(_guizmo.YAxis->_entity);
		_guizmo.YAxis->_loaded = true;
		_scene->addEntity(_guizmo.YAxis);
		_scene->_dynamicEntities.push_back(_guizmo.YAxis);
		

		/**
		Creating Z Axe (BLUE)
		*/
		guizmoName = _entity->getName() + "Z-Axe";
		Ogre::ManualObject *zAxe = _scene->getSceneMgr()->createManualObject();

		// We set the material and draw the line
		zAxe->begin("Blue", Ogre::RenderOperation::OT_LINE_LIST);
		zAxe->position(0, 0, 0); // Center
		zAxe->position(0, 0, size); // ZAxis
		zAxe->end();
		zAxe->convertToMesh(guizmoName);

		// Create a child Node for the Guizmo, thus we don't have to move the guizmo.
		_guizmo.ZAxis = new CEntity(guizmoName, guizmoName);
		_guizmo.ZAxis->_entity = _scene->getSceneMgr()->createEntity(guizmoName, guizmoName);
		_guizmo.ZAxis->_entityNode = _entityNode->createChildSceneNode(guizmoName);
		_guizmo.ZAxis->_entityNode->attachObject(_guizmo.ZAxis->_entity);
		_guizmo.ZAxis->_loaded = true;
		_scene->addEntity(_guizmo.ZAxis);
		_scene->_dynamicEntities.push_back(_guizmo.ZAxis);
		
	
	} // drawGuizmo

	//--------------------------------------------------------

	void CEntity::setMaterial(std::string material){
		_entity->setMaterialName(material);
	}

	void CEntity::rollEntityNode(int degrees)
	{
		_entityNode->rotate(Vector3::UNIT_Y, Ogre::Degree(degrees));
	}


} // namespace Graphics

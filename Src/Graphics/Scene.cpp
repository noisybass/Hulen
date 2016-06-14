#include "Scene.h"

#include "Graphics/Camera.h"
#include "Graphics/StaticEntity.h"
#include "Graphics/Light.h"
#include "Graphics/PointLight.h"
#include "Graphics/RibbonTrail.h"
#include "Graphics/Billboard.h"
#include "BaseSubsystems/Server.h"
#include "Logic/Entity/Entity.h"

#include <assert.h>

#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreStaticGeometry.h>
#include <OgreColourValue.h>
#include <OgreManualObject.h>
#include <OgreRibbonTrail.h>
#include <OgreBillboard.h>
#include <OgreBillboardSet.h>
#include <OgreColourValue.h>
#include <OgreSceneNode.h>

namespace Graphics 
{
	CScene::CScene(const std::string& name) : _viewport(nullptr), 
			_staticGeometry(nullptr), _directionalLight(nullptr),
			_isAmbientalLight(false)
	{
		_root = BaseSubsystems::CServer::getSingletonPtr()->getOgreRoot();
		_sceneMgr = _root->createSceneManager(Ogre::ST_INTERIOR, name);
		_camera = new CCamera(name,this);
		_name = name;
		

	} // CScene

	//--------------------------------------------------------

	CScene::~CScene() 
	{
		deactivate();
		_sceneMgr->destroyStaticGeometry(_staticGeometry);
		delete _camera;
		_root->destroySceneManager(_sceneMgr);

	} // ~CScene

	//--------------------------------------------------------

	bool CScene::addEntity(CEntity* entity)
	{
		if(!entity->attachToScene(this))
			return false;
		_dynamicEntities.push_back(entity);
		return true;

	} // addEntity

	//--------------------------------------------------------

	bool CScene::addStaticEntity(CStaticEntity* entity)
	{
		if(!entity->attachToScene(this))
			return false;
		_staticEntities.push_back(entity);
		return true;

	} // addStaticEntity

	//--------------------------------------------------------

	void CScene::addLight(CLight* light)
	{
		light->attachToScene(this);
		_lights.push_back(light);

	} // addStaticEntity

	//--------------------------------------------------------

	void CScene::addRibbonTrail(CRibbonTrail* ribbonTrail)
	{
		ribbonTrail->attachToScene(this);
		_ribbonTrails.push_back(ribbonTrail);

	} // addRibbonTrail

	//--------------------------------------------------------

	void CScene::addBillboard(CBillBoard* billboard)
	{
		billboard->attachToScene(this);
		_billboards.push_back(billboard);

	} // addRibbonTrail

	//--------------------------------------------------------

	void CScene::removeEntity(CEntity* entity)
	{
		entity->deattachFromScene();
		_dynamicEntities.remove(entity);

	} // addEntity

	//--------------------------------------------------------

	void CScene::removeStaticEntity(CStaticEntity* entity)
	{
		entity->deattachFromScene();
		_staticEntities.remove(entity);

	} // addStaticEntity

	//--------------------------------------------------------

	void CScene::removeLight(CLight* light)
	{
		light->detachFromScene();
		_lights.remove(light);

	} // addStaticEntity

	void CScene::removeRibbonTrail(CRibbonTrail* ribbonTrail)
	{
		ribbonTrail->deattachFromScene();
		_ribbonTrails.remove(ribbonTrail);
	} // removeRibbonTrail

	void CScene::removeBillboard(CBillBoard* billboard)
	{
		billboard->deattachFromScene();
		_billboards.remove(billboard);
	} // removeRibbonTrail

	//--------------------------------------------------------

	bool CScene::changeAmbientalLightState(){
	
		// Si hay luz ambiental, la quitamos
		if (_isAmbientalLight){
			_directionalLight->setVisible(false);
			_isAmbientalLight = false;
		}
		// Viceversa
		else{
			_directionalLight->setVisible(true);
			_isAmbientalLight = true;
		}

		return _isAmbientalLight;
	}

	//--------------------------------------------------------

	void CScene::activate()
	{
		buildStaticGeometry();
		// HACK en pruebas
		_viewport = BaseSubsystems::CServer::getSingletonPtr()->getRenderWindow()
						->addViewport(_camera->getCamera());
		_viewport->setBackgroundColour(Ogre::ColourValue::Black);

		// Luz direccional para debug
		_directionalLight = _sceneMgr->createLight("directional light");
		_directionalLight->setDiffuseColour(.75f, .75f, .75f);
		_directionalLight->setSpecularColour(.75f, .75f, .75f);
		_directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
		_directionalLight->setDirection(0, -150, 0);
		_directionalLight->setPosition(0, 0, 0);
		_directionalLight->setVisible(false);

	} // activate

	//--------------------------------------------------------

	void CScene::deactivate()
	{
		if(_directionalLight)
		{
			_sceneMgr->destroyLight(_directionalLight);
			_directionalLight = 0;
		}
		if(_viewport)
		{
			BaseSubsystems::CServer::getSingletonPtr()->getRenderWindow()->
					removeViewport(_viewport->getZOrder());
			_viewport = 0;
		}


	} // deactivate
	
	//--------------------------------------------------------

	
	void CScene::tick(float secs)
	{	
		TEntityList::const_iterator it = _dynamicEntities.begin();
		TEntityList::const_iterator end = _dynamicEntities.end();
		for(; it != end; it++)
			(*it)->tick(secs);

	} // tick

	//--------------------------------------------------------

	void CScene::buildStaticGeometry()
	{
		if(!_staticGeometry && !_staticEntities.empty())
		{
			_staticGeometry = 
					_sceneMgr->createStaticGeometry("static");

			TStaticEntityList::const_iterator it = _staticEntities.begin();
			TStaticEntityList::const_iterator end = _staticEntities.end();
			for(; it != end; it++)
				(*it)->addToStaticGeometry();

			_staticGeometry->build();
		}

	} // buildStaticGeometry

} // namespace Graphics

#include "Camera.h"

#include "BaseSubsystems/Server.h"

#include <assert.h>

#include <OgreCamera.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreRay.h>

namespace Graphics 
{
	CCamera::CCamera(const std::string &name, CScene *scene)
		: _scene(0)
	{
		_name = name;
		_scene = scene;

		// Creamos la estructura de nodos de la cámara. Los nodos cuelgan
		// de la raiz, son globales.
		_cameraNode = _scene->getSceneMgr()->getRootSceneNode()->
			createChildSceneNode(name + "_camera_node");
		_targetNode = scene->getSceneMgr()->getRootSceneNode()->
			createChildSceneNode(name + "_target_node");

		// Hacemos que el nodo de la cámara siempre esté mirando al nodo
		// objetivo.
		_cameraNode->setAutoTracking(true, _targetNode);
		// Fijamos el viraje de la cámara para se mantenga paralelo al
		// suelo.
		_cameraNode->setFixedYawAxis(true);

		_camera = scene->getSceneMgr()->createCamera(name + "_camera");
		//HACK: Valores cableados de las distancias para reenderizar. 
		// Deberían poder configurarse.
		_camera->setNearClipDistance(5);
		_camera->setFarClipDistance(500);

		//TO DO: La cámara que necesitamos NO es ortográfica, es con perspectiva. 
		// Si se implementa el poder tener una camara ortográfica, quedaría mejor parametrizado y cargandolo desde el map.txt.
		//_camera->setProjectionType(Ogre::ProjectionType::PT_ORTHOGRAPHIC);
		//_camera->setOrthoWindow(13, 13);

		//TO DO: Ajustar el FOV y el AspectRatio de la cámara.
		//_camera->setFOVy(Ogre::Radian(60.0f));

		// Finalmente adjuntamos la cámara a su nodo.
		_cameraNode->attachObject(_camera);

	} // CCamera

	//--------------------------------------------------------

	CCamera::~CCamera() 
	{
		// desacoplamos la cámara de su nodo
		_cameraNode->detachAllObjects();
		_scene->getSceneMgr()->destroyCamera(_camera);
		_scene->getSceneMgr()->destroySceneNode(_cameraNode);
		_scene->getSceneMgr()->destroySceneNode(_targetNode);

	} // ~CCamera

	//--------------------------------------------------------
	
	const Vector3 &CCamera::getCameraPosition() 
	{
		return _cameraNode->getPosition();
	}

	//--------------------------------------------------------

	const Vector3 &CCamera::getTargetCameraPosition() 
	{
		return _targetNode->getPosition();
	}

	const float &CCamera::getAspectRatio(){
		return _camera->getAspectRatio();
	}

	const float &CCamera::getFOV(){
		return _camera->getFOVy().valueDegrees();
	}

	//--------------------------------------------------------

	const Quaternion &CCamera::getCameraOrientation() 
	{
		return _camera->getOrientation();
	}

	//--------------------------------------------------------

	void CCamera::setCameraPosition(const Vector3 &newPosition)
	{
		_cameraNode->setPosition(newPosition);
	}

	//--------------------------------------------------------

	void CCamera::setTargetCameraPosition(const Vector3 &newPosition)
	{
		_targetNode->setPosition(newPosition);
	}

	void CCamera::setAspectRatio(float ratio)
	{
		_camera->setAspectRatio(ratio);
	}

	void CCamera::setFOV(float degree){
		_camera->setFOVy((Ogre::Radian)Ogre::Math::AngleUnitsToRadians(degree));
	}

	Vector3 CCamera::screenToWorld(float screenX, float screenY) const
	{
		float x = screenX / _camera->getViewport()->getActualWidth();
		float y = screenY / _camera->getViewport()->getActualHeight();

		Ogre::Ray ray = _camera->getCameraToViewportRay(x, y);
		Vector3 pos = ray.getPoint(30.0);

		return pos;
	}

} // namespace Graphics

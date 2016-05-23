#include "Server.h"

#include "Graphics/Scene.h"
#include "Graphics/DebugDrawing.h"
#include "BaseSubsystems/Server.h"
#include "BaseSubsystems/Math.h"

#include <assert.h>

#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>
#include <OgreMeshManager.h>

namespace Graphics 
{
	CServer *CServer::_instance = nullptr;

	CServer::CServer() : _root(nullptr), _renderWindow(nullptr), _activeScene(nullptr), _dummyScene(nullptr), _debugDrawing(nullptr)
	{
		assert(!_instance && "Segunda inicialización de Graphics::CServer no permitida!");

		_instance = this;

	} // CServer

	//--------------------------------------------------------

	CServer::~CServer() 
	{
		assert(_instance);

		_instance = nullptr;

	} // ~CServer

	//--------------------------------------------------------

	bool CServer::Init() 
	{
		assert(!_instance && "Segunda inicialización de Graphics::CServer no permitida!");

		new CServer();

		if (!_instance->open())
		{
			Release();
			return false;
		}

		return true;

	} // Init

	//--------------------------------------------------------

	void CServer::Release()
	{
		if(_instance)
		{
			_instance->close();
			delete _instance;
		}

	} // Release

	//--------------------------------------------------------

	bool CServer::open()
	{
		if(!BaseSubsystems::CServer::getSingletonPtr())
			return false;

		_root = BaseSubsystems::CServer::getSingletonPtr()->getOgreRoot();

		_renderWindow = BaseSubsystems::CServer::getSingletonPtr()->getRenderWindow();

		// Creamos la escena dummy para cuando no hay ninguna activa.
		_dummyScene = createScene("dummy_scene");
		
		// Por defecto la escena activa es la dummy
		setScene(_dummyScene);

		return true;

	} // open

	//--------------------------------------------------------

	void CServer::close() 
	{

		if(_activeScene)
		{
			_activeScene->deactivate();
			_activeScene = nullptr;
		}
		while(!_scenes.empty())
		{
			removeScene(_scenes.begin());
		}
		

	} // close

	//--------------------------------------------------------
		
	typedef std::pair<std::string,CScene*> TStringScenePar;

	CScene* CServer::createScene(const std::string& name)
	{
		//Nos aseguramos de que no exista ya una escena con este nombre.
		assert(_scenes.find(name)==_scenes.end() && 
			"Ya se ha creado una escena con este nombre.");

		CScene *scene = new CScene(name);
		TStringScenePar ssp(name,scene);
		_scenes.insert(ssp);
		return scene;

	} // createScene

	//--------------------------------------------------------

	void CServer::removeScene(CScene* scene)
	{
		if (_debugDrawing){
			delete _debugDrawing;
			_debugDrawing = nullptr;
		}
			

		// Si borramos la escena activa tenemos que quitarla.
		if(_activeScene == scene)
			_activeScene = nullptr;
		_scenes.erase(scene->getName());
		delete scene;

	} // removeScene

	//--------------------------------------------------------

	void CServer::removeScene(const std::string& name)
	{
		CScene* scene = (*_scenes.find(name)).second;
		removeScene(scene);

	} // removeScene

	//--------------------------------------------------------

	void CServer::removeScene(TScenes::const_iterator iterator)
	{

		CScene* scene = (*iterator).second;
		// Si borramos la escena activa tenemos que quitarla.
		if(_activeScene == scene)
			_activeScene = nullptr;
		_scenes.erase(iterator);
		delete scene;

	} // removeScene

	//--------------------------------------------------------

	void CServer::setScene(CScene* scene)
	{
		// En caso de que hubiese una escena activa la desactivamos.
		if(_activeScene)
			_activeScene->deactivate();

		if(scene)
		{
			// Sanity check. Nos aseguramos de que la escena pertenezca 
			// al servidor. Aunque nadie más puede crear escenas...
			assert((*_scenes.find(scene->getName())).second == scene && 
				"Esta escena no pertenece al servidor");

			_activeScene = scene;
		}
		// Si se añade NULL ponemos la escena dummy.
		else
			_activeScene = _dummyScene;

		_activeScene->activate();

	} // createScene

	//--------------------------------------------------------

	void CServer::setScene(const std::string& name)
	{
		// En caso de que hubiese una escena activa la desactivamos.
		if(_activeScene)
			_activeScene->deactivate();

		// Nos aseguramos de que exista una escena con este nombre.
		assert(_scenes.find(name) != _scenes.end() && 
			"Ya se ha creado una escena con este nombre.");
		_activeScene = (*_scenes.find(name)).second;

		_activeScene->activate();

	} // createScene

	//--------------------------------------------------------

	void CServer::tick(float secs) 
	{
		if(_activeScene != _dummyScene)
			_activeScene->tick(secs);
		if(_root)
		{
			// Actualizamos todas las ventanas de reenderizado.
			Ogre::WindowEventUtilities::messagePump();
			// Reenderizamos un frame
			_root->renderOneFrame(secs);
		}
		if (_debugDrawing){
			_debugDrawing->tick(secs);
		}
	} // tick

	CDebugDrawing* CServer::getDebugDrawing()
	{
		if (!_debugDrawing){
			_debugDrawing = new Graphics::CDebugDrawing();
		}

		return _debugDrawing;
	}

	void CServer::createPlane(const Ogre::Vector3& upVector, const Ogre::Vector3& parallelVector, const std::string& planeName, float width, float height, int xSegments, int ySegments, bool normals, float uTile, float vTile)
	{
		Ogre::Plane plane(upVector, 0);

		Ogre::MeshManager::getSingleton().createPlane(
			planeName, 
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
			plane,
			width,
			height,
			xSegments,
			ySegments,
			true,
			1,
			uTile,
			vTile,
			parallelVector);
	}

} // namespace Graphics

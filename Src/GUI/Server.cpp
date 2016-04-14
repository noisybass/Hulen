#include "Server.h"

#include "BaseSubsystems/Server.h"

#include <cassert>

#include <CEGUI/System.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/Window.h>
#include <CEGUI/SchemeManager.h>
#include <CEGUI/FontManager.h>

namespace GUI {

	CServer* CServer::_instance = 0;

	//--------------------------------------------------------

	CServer::CServer() : _playerController(nullptr), _lightController(nullptr), _sceneController(nullptr), _objectsController(nullptr)
	{
		_instance = this;

	} // CServer

	//--------------------------------------------------------

	CServer::~CServer()
	{
		_instance = 0;

	} // ~CServer
	
	//--------------------------------------------------------

	bool CServer::Init()
	{
		assert(!_instance && "Segunda inicialización de GUI::CServer no permitida!");

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
		assert(_instance && "GUI::CServer no está inicializado!");

		if(_instance)
		{
			_instance->close();
			delete _instance;
		}

	} // Release

	//--------------------------------------------------------

	bool CServer::open()
	{
		_playerController = new CPlayerController();
		_lightController = new CLightController();
		_sceneController = new CSceneController();
		_objectsController = new CObjectsController();

		_GUISystem = BaseSubsystems::CServer::getSingletonPtr()->getGUISystem();

		// Cargamos las distintas plantillas o esquemas de fichero
		// que usaremos en nuestro GUI.
		// (automáticamente cargan los archivos looknfeel e imageset)
		CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
		CEGUI::SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
		CEGUI::SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");
		CEGUI::SchemeManager::getSingleton().createFromFile("Hulen.scheme");

#ifndef NON_EXCLUSIVE_MODE_IN_WINDOW_MODE 
		// Establecemos cual será el puntero del ratón.
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().setDefaultImage("OgreTrayImages/MouseArrow");
#endif	
		
		// Cargamos los archivos con las fuentes que usaremos.
		CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-12.font");
		CEGUI::Font& defaultFont = CEGUI::FontManager::getSingleton().createFromFile("Jura-18.font");
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().setDefaultFont(&defaultFont);
		
		CInputManager::getSingletonPtr()->addMouseListener(this);
		CInputManager::getSingletonPtr()->addKeyListener(this);

		return true;

	} // open

	//--------------------------------------------------------

	void CServer::close() 
	{
		CInputManager::getSingletonPtr()->removeKeyListener(this);
		CInputManager::getSingletonPtr()->removeMouseListener(this);

		delete _lightController;
		delete _playerController;
		delete _sceneController;
		delete _objectsController;

	} // close

	//--------------------------------------------------------

	bool CServer::keyPressed(TKey key)
	{
		_GUISystem->getDefaultGUIContext().injectKeyDown((CEGUI::Key::Scan) key.keyId);    
		_GUISystem->getDefaultGUIContext().injectChar(key.text);    

		
		// Queremos que si hay más oyentes también reciban el evento
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CServer::keyReleased(TKey key)
	{
		_GUISystem->getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)key.keyId);

		
		// Queremos que si hay más oyentes también reciban el evento
		return false;

	} // keyReleased

	//--------------------------------------------------------
	
	bool CServer::mouseMoved(const CMouseState &mouseState)
	{
#if defined NON_EXCLUSIVE_MODE_IN_WINDOW_MODE
		_GUISystem->getDefaultGUIContext().injectMousePosition((float)mouseState.posAbsX,(float)mouseState.posAbsY);
#else 
		_GUISystem->getDefaultGUIContext().injectMouseMove((float)mouseState.movX,(float)mouseState.movY);
#endif	
		// Queremos que si hay más oyentes también reciban el evento
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CServer::mousePressed(const CMouseState &mouseState)
	{
		switch (mouseState.button)
		{
		case Button::LEFT:
			_GUISystem->getDefaultGUIContext().injectMouseButtonDown(CEGUI::LeftButton);
		case Button::RIGHT:
			_GUISystem->getDefaultGUIContext().injectMouseButtonDown(CEGUI::RightButton);
		case Button::MIDDLE:
			_GUISystem->getDefaultGUIContext().injectMouseButtonDown(CEGUI::MiddleButton);
		}

		// Queremos que si hay más oyentes también reciban el evento
		return false;

	} // mousePressed

	//--------------------------------------------------------

	bool CServer::mouseReleased(const CMouseState &mouseState)
	{
		switch (mouseState.button)
		{
		case Button::LEFT:
			_GUISystem->getDefaultGUIContext().injectMouseButtonUp(CEGUI::LeftButton);
		case Button::RIGHT:
			_GUISystem->getDefaultGUIContext().injectMouseButtonUp(CEGUI::RightButton);
		case Button::MIDDLE:
			_GUISystem->getDefaultGUIContext().injectMouseButtonUp(CEGUI::MiddleButton);
		}

		// Queremos que si hay más oyentes también reciban el evento
		return false;

	} // mouseReleased

} // namespace GUI

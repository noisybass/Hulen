#include "LightController.h"
#include "InputManager.h"

#include "Logic/Entity/GameObject.h"
#include "Logic/Entity/Message.h"

#include "Graphics\Server.h"
#include "Graphics\Scene.h"
#include "Graphics\Camera.h"

#include <OgreRenderWindow.h>
#include <OgreRay.h>
#include <OgrePlane.h>

#include <cassert>

#define TURN_FACTOR 0.001f

namespace GUI {

	CLightController::CLightController() : _controlledLight(nullptr)
	{

	} // CPlayerController

	//--------------------------------------------------------

	CLightController::~CLightController()
	{
		deactivate();

	} // ~CPlayerController

	//--------------------------------------------------------

	void CLightController::activate()
	{		
		CInputManager::getSingletonPtr()->addKeyListener(this);
		CInputManager::getSingletonPtr()->addMouseListener(this);

	} // activate

	//--------------------------------------------------------

	void CLightController::deactivate()
	{
		CInputManager::getSingletonPtr()->removeKeyListener(this);
		CInputManager::getSingletonPtr()->removeMouseListener(this);

	} // deactivate

	//--------------------------------------------------------

	bool CLightController::keyPressed(TKey key)
	{

		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CLightController::keyReleased(TKey key)
	{
		
		return false;

	} // keyReleased

	//--------------------------------------------------------
	
	bool CLightController::mouseMoved(const CMouseState &mouseState)
	{
		if(_controlledLight)
		{
			Logic::TMessage m;
			m._type = Logic::Message::KASAI_MOVE;

			Graphics::CCamera* camera = Graphics::CServer::getSingletonPtr()->getActiveScene()->getCamera();
			
			Vector3 pos = camera->screenToWorld(mouseState.posAbsX, mouseState.posAbsY);
			m.setArg<Vector3>(std::string("newPosition"), Vector3(pos.x, pos.y, 0));
			//std::cout << "(" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
			
			_controlledLight->emitMessage(m);
			return true;
		}
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CLightController::mousePressed(const CMouseState &mouseState)
	{
		if (_controlledLight)
		{
			Logic::TMessage m;
			switch (mouseState.button)
			{
				case GUI::Button::LEFT:
					m._type = Logic::Message::KASAI_SET_VISIBLE;
					break;
			}

			_controlledLight->emitMessage(m);
			// Si queremos que tambien el PlayerController escuche este evento tendríamos que devolver false
			return true;
		}
		return false;

	} // mousePressed

	//--------------------------------------------------------

	bool CLightController::mouseReleased(const CMouseState &mouseState)
	{
		return false;

	} // mouseReleased

} // namespace GUI

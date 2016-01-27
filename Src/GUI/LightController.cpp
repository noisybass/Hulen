#include "LightController.h"
#include "InputManager.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/Message.h"

#include <cassert>

#define TURN_FACTOR 0.001f

namespace GUI {

	CLightController::CLightController() : _controlledLight(0)
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
			m._type = Logic::Message::MOUSE_POSITION;
			m._vector3 = Vector3(-mouseState.movX , 
								  mouseState.movY , 
								  0);
			_controlledLight->emitMessage(m);
			return true;
		}
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CLightController::mousePressed(const CMouseState &mouseState)
	{
		return false;

	} // mousePressed

	//--------------------------------------------------------

	bool CLightController::mouseReleased(const CMouseState &mouseState)
	{
		return false;

	} // mouseReleased

} // namespace GUI

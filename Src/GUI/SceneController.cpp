#include "SceneController.h"
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

namespace GUI {

	CSceneController::CSceneController() : _controlledScene(nullptr)
	{
		
	} // CPlayerController

	//--------------------------------------------------------

	CSceneController::~CSceneController()
	{
		deactivate();

	} // ~CPlayerController

	//--------------------------------------------------------

	void CSceneController::activate()
	{		
		CInputManager::getSingletonPtr()->addKeyListener(this);
		CInputManager::getSingletonPtr()->addMouseListener(this);

	} // activate

	//--------------------------------------------------------

	void CSceneController::deactivate()
	{
		CInputManager::getSingletonPtr()->removeKeyListener(this);
		CInputManager::getSingletonPtr()->removeMouseListener(this);

	} // deactivate

	//--------------------------------------------------------

	bool CSceneController::keyPressed(TKey key)
	{
		switch (key.keyId){
		case GUI::Key::L:
			

			// Utilizar lo comentado si queremos cambiar los materiales de 
			// las entidades a la hora de debugear.

			/*Logic::TMessage m;
			// Si hay luz ambiental, ponemos a las entidades materiales de debug.
			if (_controlledScene->getScene()->changeAmbientalLightState()){
				m._type = Logic::Message::AMBIENT_LIGHT_SET_FOR_DEBUG;
				// Le pasamos el nombre del material que queremos poner.
				m.setArg<std::string>(std::string("ambient_light_set_for_debug"), std::string("Red"));
			}
			// Si no hay luz ambiental, dejamos todos las entidades con 
			// sus materiales originales
			else{
				m._type = Logic::Message::AMBIENT_LIGHT_SET_REAL_MATERIAL;
			}

			_controlledScene->sendMessageToGameObjects(m);*/

			_controlledScene->getScene()->changeAmbientalLightState();

			break;
		}

		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CSceneController::keyReleased(TKey key)
	{
		
		return false;

	} // keyReleased

	//--------------------------------------------------------
	
	bool CSceneController::mouseMoved(const CMouseState &mouseState)
	{

		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CSceneController::mousePressed(const CMouseState &mouseState)
	{

		return false;

	} // mousePressed

	//--------------------------------------------------------

	bool CSceneController::mouseReleased(const CMouseState &mouseState)
	{
		return false;

	} // mouseReleased

} // namespace GUI

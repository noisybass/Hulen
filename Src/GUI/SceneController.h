#ifndef GUI_SCENE_CONTROLLER_H
#define GUI_SCENE_CONTROLLER_H

#include "InputManager.h"
#include "Logic\Maps\Map.h"

namespace GUI
{
	
	class CSceneController : public CKeyboardListener, public CMouseListener
	{
	public:

		/**
		Constructor.
		*/
		CSceneController();

		/**
		Destructor.
		*/
		~CSceneController();

		/**
		Establece el componente de la luz al que enviaremos acciones 
		de movimiento en función de las teclas pulsadas y el movimiento 
		del ratón.

		@param controlledLight Componente al que enviaremos acciones de 
		movimiento en función de las teclas pulsadas y el movimiento del 
		ratón.
		*/
		void setControlledScene(Logic::CMap* controlledScene)
										{_controlledScene = controlledScene;} 

		/**
		Activa la la clase, se registra en el CInputManager y así empieza a 
		escuchar eventos.
		*/
		void activate();

		/**
		Desctiva la la clase, se deregistra en el CInputManager y deja de 
		escuchar eventos.
		*/
		void deactivate();

		/***************************************************************
		Métodos de CKeyboardListener
		***************************************************************/
		
		/**
		Método que será invocado siempre que se pulse una tecla.

		@param key Código de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamará a otros listeners.
		*/
		bool keyPressed(TKey key);
		
		/**
		Método que será invocado siempre que se termine la pulsación
		de una tecla.

		@param key Código de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamará a otros listeners.
		*/
		bool keyReleased(TKey key);

		/***************************************************************
		Métodos de CKeyboardListener
		***************************************************************/
		
		/**
		Método que será invocado siempre que se mueva el ratón.

		@param mouseState Estado del ratón cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamará a otros listeners.
		*/
		bool mouseMoved(const CMouseState &mouseState);
		
		/**
		Método que será invocado siempre que se pulse un botón.

		@param mouseState Estado del ratón cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamará a otros listeners.
		*/
		bool mousePressed(const CMouseState &mouseState);

		/**
		Método que será invocado siempre que se termine la pulsación
		de un botón.

		@param mouseState Estado del ratón cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamará a otros listeners.
		*/
		bool mouseReleased(const CMouseState &mouseState);

	protected:

		/**
		Luz a la que enviaremos acciones de movimiento en
		función de las teclas pulsadas y el movimiento del ratón.
		*/
		Logic::CMap* _controlledScene;

	}; // class CSceneController

} // namespace GUI

#endif // __GUI_SceneController_H

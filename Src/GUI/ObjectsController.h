#ifndef GUI_OBJECTS_CONTROLLER_H
#define GUI_OBJECTS_CONTROLLER_H

#include "InputManager.h"
#include "Logic\Entity\Entity.h"
#include <unordered_map>

namespace GUI
{
	
	class CObjectsController : public CKeyboardListener, public CMouseListener
	{
	public:

		/**
		Constructor.
		*/
		CObjectsController();

		/**
		Destructor.
		*/
		~CObjectsController();

		void addControllerObject(Logic::CEntity* entity);

		void removeControllerObject(const std::string &entityName);

		void activate();

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

		std::unordered_map<std::string, Logic::CEntity*> _entities;
		

	}; // class CSceneController

} // namespace GUI

#endif // GUI_OBJECTS_CONTROLLER_H

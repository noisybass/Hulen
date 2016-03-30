#ifndef LOGIC_COMPONENT_FACTORY_H
#define LOGIC_COMPONENT_FACTORY_H

#include "BaseSubsystems/Factory.h"

// Predeclaración de clases para ahorrar tiempo de compilación
namespace Logic 
{
	class IComponent;
}

// Declaración de la clase
namespace Logic
{
	/**
	Factoría de componentes. Extiende la plantilla BaseSubsystems::CFactory
	para IComponent haciendo de ella un singleton por lo que solo habrá una 
	instancia de esta clase.
	<p>
	Es usada para almacenar componentes 
	en Logic::CEntityFactory donde todo el registro de componentes se realiza 
	utilizando macros del preprocesador declarados en Logic::CComponent.

	@ingroup logicGroup
	@ingroup mapGroup

	@author David Llansó
	@date Julio, 2010
	*/
	class CComponentFactory : public BaseSubsystems::CFactory<IComponent*>
	{
	public:

		/**
		Devuelve la única instancia de la clase CComponentFactory.
		
		@return Única instancia de la clase CComponentFactory.
		*/
		static CComponentFactory* getSingletonPtr();

		/**
		Destructor.
		*/
		~CComponentFactory();

	protected:
		/**
		Constructor.
		*/
		CComponentFactory ();

	private:
		/**
		Única instancia de la clase.
		*/
		static CComponentFactory* _instance;

	}; // class CComponentFactory

} // namespace Logic

#endif // __Logic_ComponentFactory_H

#include "ComponentFactory.h"

#include "Logic/Entity/Component.h"

#include <cassert>

namespace Logic {

	CComponentFactory* CComponentFactory::_instance = 0;

	//--------------------------------------------------------

	CComponentFactory::CComponentFactory() : CFactory()
	{
		_instance = this;

	} // CComponentFactory

	//--------------------------------------------------------

	CComponentFactory::~CComponentFactory()
	{
		_instance = 0;

	} // ~CComponentFactory
	
	//--------------------------------------------------------

	CComponentFactory* CComponentFactory::getSingletonPtr()
	{
		if(!_instance)
			new CComponentFactory();

		return _instance;

	} // Init

} // namespace Logic

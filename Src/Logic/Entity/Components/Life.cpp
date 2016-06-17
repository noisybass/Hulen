#include "Life.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"
#include "Application/BaseApplication.h"

namespace Logic 
{
	IMP_FACTORY(CLife);
	
	//---------------------------------------------------------

	CLife::~CLife()
	{
		_scene->removeBillboard(_billboard);
		_scene = nullptr;
		delete _billboard;
		_billboard = nullptr;
	}


	bool CLife::spawn(const std::string& name, CGameObject* gameObject, CMap *map, const Map::CEntity *entityInfo)
	{
		if(!IComponent::spawn(name, gameObject,map,entityInfo))
			return false;

		_scene = _gameObject->getMap()->getScene();

		_billboard = new Graphics::CBillBoard(_gameObject->getName());
		_scene->addBillboard(_billboard);

		assert(entityInfo->hasAttribute("billboard_position") &&
			entityInfo->hasAttribute("billboard_color") &&
			entityInfo->hasAttribute("billboard_width") &&
			entityInfo->hasAttribute("billboard_height") &&
			entityInfo->hasAttribute("billboard_material") && "Tienes que poner todos los atributos, revisa el map.lua");

		if (entityInfo->hasAttribute("billboard_position") &&
			entityInfo->hasAttribute("billboard_color") &&
			entityInfo->hasAttribute("billboard_width") &&
			entityInfo->hasAttribute("billboard_height") &&
			entityInfo->hasAttribute("billboard_material"))
		{
			_position = entityInfo->getVector3Attribute("billboard_position");
			_color = entityInfo->getVector3Attribute("billboard_color");
			_width = entityInfo->getFloatAttribute("billboard_width");
			_height = entityInfo->getFloatAttribute("billboard_height");
			_materialName = entityInfo->getStringAttribute("billboard_material");

			_billboard->init(_position, Ogre::ColourValue(_color.x, _color.y, _color.z), _width, _height, _materialName);
		}

		if (entityInfo->hasAttribute("playerDeathTime"))
			_deathTime = entityInfo->getFloatAttribute("playerDeathTime");
		

		return true;

	} // spawn

	void CLife::setDeathTime(float time)
	{
		_billboard->setDimensions( _width - ((time * _width) / _deathTime) , _height);
	} // setDeathTime

	void CLife::setVisible(bool visible)
	{
		_billboard->setVisible(visible);
	} // setVisible
	
	//---------------------------------------------------------

	bool CLife::accept(const TMessage &message)
	{
		return false;
	} // accept
	
	//---------------------------------------------------------

	void CLife::process(const TMessage &message)
	{

	} // process


} // namespace Logic


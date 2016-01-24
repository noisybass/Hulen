#include "PointLight.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

namespace Logic
{
	IMP_FACTORY(CPointLight);

	CPointLight::CPointLight() 
		: IComponent(), _light(nullptr) {} // CPointLight

	CPointLight::~CPointLight()
	{
		if (_light)
		{
			_scene->removeLight(_light);
			delete _light;
			_light = nullptr;
		}
	} // ~CPointLight

	bool CPointLight::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(entity, map, entityInfo))
			return false;

		_scene = _entity->getMap()->getScene();

		_light = new Graphics::CPointLight(_entity->getName());
		_scene->addLight(_light);

		Vector3 colour;

		if (entityInfo->hasAttribute("diffuse_colour"))
			colour = entityInfo->getVector3Attribute("diffuse_colour");
		_light->setDiffuseColour(Ogre::ColourValue(colour.x, colour.y, colour.z));

		if (entityInfo->hasAttribute("specular_colour"))
			colour = entityInfo->getVector3Attribute("specular_colour");
		_light->setSpecularColour(Ogre::ColourValue(colour.x, colour.y, colour.z));

		if (entityInfo->hasAttribute("light_position"))
			_light->setPosition(entityInfo->getVector3Attribute("light_position"));

		return true;
	} // spawn

	bool CPointLight::accept(const TMessage &message)
	{
		return false;

	} // accept

	void CPointLight::process(const TMessage &message)
	{

	} // process

} // namespace Logic
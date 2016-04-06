#include "PointLight.h"

#include "Logic/Entity/Entity.h"
#include "Logic\Entity\GameObject.h"
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

	bool CPointLight::spawn(const std::string& name, CEntity *entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		_scene = _entity->getGameObject()->getMap()->getScene();

		_light = new Graphics::CPointLight(_entity->getName());
		_scene->addLight(_light);

		Vector3 colour;

		if (entityInfo->hasAttribute("diffuse_colour")){
			colour = entityInfo->getVector3Attribute("diffuse_colour");
			_light->setDiffuseColour(Ogre::ColourValue(colour.x, colour.y, colour.z));
		}
			
		if (entityInfo->hasAttribute("specular_colour")){
			colour = entityInfo->getVector3Attribute("specular_colour");
			_light->setSpecularColour(Ogre::ColourValue(colour.x, colour.y, colour.z));
		}
		
		if (entityInfo->hasAttribute("light_position")){
			_light->setPosition(entityInfo->getVector3Attribute("light_position"));
		}
		else
			_light->setPosition(_entity->getPosition());

		/**
		Attenuation settings
		see this website for more info: http://www.ogre3d.org/tikiwiki/-Point+Light+Attenuation
		*/
		if (entityInfo->hasAttribute("light_attenuation_range") &&
			entityInfo->hasAttribute("light_attenuation_constant") &&
			entityInfo->hasAttribute("light_attenuation_linear") &&
			entityInfo->hasAttribute("light_attenuation_quadratic")){
			_light->setAttenuation( entityInfo->getFloatAttribute("light_attenuation_range"),
									entityInfo->getFloatAttribute("light_attenuation_constant"), 
									entityInfo->getFloatAttribute("light_attenuation_linear"), 
									entityInfo->getFloatAttribute("light_attenuation_quadratic"));
		
		}

		/**
		Flare settings
		*/

		if (entityInfo->hasAttribute("flare_material") &&
			entityInfo->hasAttribute("flare_colour") &&
			entityInfo->hasAttribute("flare_size")){
			colour = entityInfo->getVector3Attribute("flare_colour");
			_light->setFlare(Ogre::ColourValue(colour.x, colour.y, colour.z), 
							entityInfo->getStringAttribute("flare_material"),
							entityInfo->getIntAttribute("flare_size"));
		}

		return true;
	} // spawn

	bool CPointLight::accept(const TMessage &message)
	{
		return message._type == Message::LIGHT_SET_POSITION ||
			message._type == Message::LIGHT_SET_COLOR ||
			message._type == Message::SET_POSITION;

	} // accept

	void CPointLight::process(const TMessage &message)
	{
		switch (message._type)
		{
			case Message::LIGHT_SET_POSITION:
				setPosition(message.getArg<Vector3>("newPosition"));
				break;
			case Message::LIGHT_SET_COLOR:
				setColor(message.getArg<Vector3>("newColor"));
				break;
			case Message::SET_POSITION:
				setPosition(message.getArg<Vector3>("newPosition"));
				break;
		}
		
	} // process

	void CPointLight::setPosition(const Vector3& newPosition)
	{
		_light->setPosition(newPosition);

	} // setPosition

	void CPointLight::setColor(const Vector3& newColor)
	{
		_light->setDiffuseColour(Ogre::ColourValue(newColor.x, newColor.y, newColor.z));
	} // setColor

} // namespace Logic
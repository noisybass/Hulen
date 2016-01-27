#include "PointLight.h"
#include <OgreSceneNode.h>

namespace Graphics
{
	CPointLight::CPointLight(const std::string &name)
		: CLight(name)
	{ 
		_type = Ogre::Light::LightTypes::LT_POINT;

	} // CPointLight

	void CPointLight::setPosition(const Ogre::Vector3& position)
	{
		//_light->setPosition(position);
		_node->setPosition(position);

	} // setPosition

	/**
	Por ahora se utiliza para actualizar la posicion de la luz cuando
	movemos el raton.
	*/
	void CPointLight::updatePosition(const Ogre::Vector3& position){
		Ogre::Vector3 nodePos = _node->getPosition();
		_node->setPosition( nodePos.x + position.x,
							nodePos.y - position.y,
							nodePos.z);
	}

} // namespace Graphics
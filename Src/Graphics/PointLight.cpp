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

	const Ogre::Vector3& CPointLight::getPosition() const
	{
		return _node->getPosition();

	} // getPosition

} // namespace Graphics
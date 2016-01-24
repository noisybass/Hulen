#include "PointLight.h"

namespace Graphics
{
	CPointLight::CPointLight(const std::string &name)
		: CLight(name)
	{ 
		_type = Ogre::Light::LightTypes::LT_POINT;

	} // CPointLight

	void CPointLight::setPosition(const Ogre::Vector3& position)
	{
		_light->setPosition(position);

	} // setPosition

} // namespace Graphics
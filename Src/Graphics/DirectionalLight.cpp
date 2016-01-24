#include "DirectionalLight.h"

namespace Graphics
{
	CDirectionalLight::CDirectionalLight(const std::string &name)
		: CLight(name)
	{
		_type = Ogre::Light::LightTypes::LT_DIRECTIONAL;

	} // CDirectionalLight

	void CDirectionalLight::setDirection(const Ogre::Vector3& direction)
	{
		_light->setDirection(direction);

	} // setDirection

} // namespace Graphics
#include "Spotlight.h"

namespace Graphics
{
	CSpotlight::CSpotlight(const std::string &name)
		: CLight(name)
	{
		_type = Ogre::Light::LightTypes::LT_SPOTLIGHT;

	} // CSpotlight

	void CSpotlight::setPosition(const Ogre::Vector3& position)
	{
		_light->setPosition(position);

	} // setPosition

	void CSpotlight::setDirection(const Ogre::Vector3& direction)
	{
		_light->setDirection(direction);

	} // setDirection

	void CSpotlight::setSpotlightRange(const Ogre::Radian& innerAngle, const Ogre::Radian& outerAngle, Ogre::Real falloff)
	{
		_light->setSpotlightRange(innerAngle, outerAngle, falloff);

	} // setSpotlightRange

} // namespace Graphics
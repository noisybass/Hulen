#ifndef GRAPHICS_SPOTLIGHT_H
#define GRAPHICS_SPOTLIGHT_H

#include "Light.h"

namespace Graphics
{
	class CSpotlight : public CLight
	{
	public:
		CSpotlight(const std::string &name);

		void setPosition(const Ogre::Vector3& position);

		void setDirection(const Ogre::Vector3& direction);

		void setSpotlightRange(const Ogre::Radian& innerAngle, const Ogre::Radian& outerAngle, Ogre::Real falloff = 1.0);

	}; // class CSpotlight

} // namespace Graphics

#endif // GRAPHICS_SPOTLIGHT_H
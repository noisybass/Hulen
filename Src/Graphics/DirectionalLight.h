#ifndef GRAPHICS_DIRECTIONAL_LIGHT_H
#define GRAPHICS_DIRECTIONAL_LIGHT_H

#include "Light.h"

namespace Graphics
{
	class CDirectionalLight : CLight
	{
	public:
		CDirectionalLight(const std::string &name);

		void setDirection(const Ogre::Vector3& direction);

	}; // class CDirectionalLight

} // namespace Graphics

#endif // GRAPHICS_DIRECTIONAL_LIGHT_H
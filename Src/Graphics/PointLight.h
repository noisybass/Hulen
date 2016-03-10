#ifndef GRAPHICS_POINT_LIGHT_H
#define GRAPHICS_POINT_LIGHT_H

#include "Light.h"

namespace Graphics
{
	class CPointLight : public CLight
	{
	public:
		CPointLight(const std::string &name);

		void setPosition(const Ogre::Vector3& position);

		const Ogre::Vector3& getPosition() const;

	}; // class CPointLight

} // namespace Graphics

#endif // GRAPHICS_POINT_LIGHT_H
#include "Light.h"

#include <cassert>

#include <OgreSceneManager.h>

namespace Graphics
{
	CLight::CLight(const std::string &name)
		: _light(nullptr), _scene(nullptr), _name(name) {} // CLight

	//--------------------------------------------------------

	CLight::~CLight()
	{
		assert(!_scene && "¡¡Para destruir una entidad esta no puede pertenecer a una escena!!");

	} // ~CLight

	//--------------------------------------------------------

	void CLight::attachToScene(CScene* scene)
	{
		assert(scene && "¡¡La entidad debe asociarse a una escena!!");
		_scene = scene;
		
		_light = _scene->getSceneMgr()->createLight(_name);
		_light->setType(_type);

	} // attachToScene

	//--------------------------------------------------------

	void CLight::detachFromScene()
	{
		if (_scene)
			_scene = nullptr;

	} // deattachFromScene

	//--------------------------------------------------------

	void CLight::setDiffuseColour(const Ogre::ColourValue &colour)
	{
		_light->setDiffuseColour(colour);

	} // setDiffuseColour

	//--------------------------------------------------------

	void CLight::setSpecularColour(const Ogre::ColourValue &colour)
	{
		_light->setSpecularColour(colour);

	} // setSpecularColour

} // namespace Graphics
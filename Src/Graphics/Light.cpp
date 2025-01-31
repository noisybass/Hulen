#include "Light.h"

#include <cassert>

#include <OgreSceneManager.h>
#include <OgreBillboardSet.h>
#include <OgreBillboard.h>

namespace Graphics
{
	CLight::CLight(const std::string &name)
		: _light(nullptr), _scene(nullptr), _name(name), _billboardFlare(nullptr) ,
		_billboardSetFlare(nullptr), _node(nullptr) {} // CLight

	//--------------------------------------------------------

	CLight::~CLight()
	{
		assert(!_scene && "��Para destruir una entidad esta no puede pertenecer a una escena!!");

	} // ~CLight

	//--------------------------------------------------------

	void CLight::attachToScene(CScene* scene)
	{
		assert(scene && "��La entidad debe asociarse a una escena!!");
		_scene = scene;
		
		_light = _scene->getSceneMgr()->createLight(_name);
		_light->setType(_type);

		_node = _scene->getSceneMgr()->getRootSceneNode()->createChildSceneNode();
		_node->attachObject(_light);

	} // attachToScene

	//--------------------------------------------------------

	void CLight::detachFromScene()
	{
		if (_scene)
		{
			_scene->getSceneMgr()->destroyLight(_light);
			_scene = nullptr;
		}
			

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

	//--------------------------------------------------------

	void CLight::setFlare(const Ogre::ColourValue colour, const std::string materialName, const unsigned int flareSize){

		_billboardSetFlare = _scene->getSceneMgr()->createBillboardSet(1);
		_billboardFlare = _billboardSetFlare->createBillboard(Ogre::Vector3::ZERO, colour);
		_billboardFlare->setDimensions(flareSize, flareSize);
		_billboardSetFlare->setMaterialName(materialName);
		// Creo que esto no hace mucha falta, pero lo dejo porsi
		_billboardSetFlare->setRenderQueueGroup(55);
		_node->attachObject(_billboardSetFlare);

	} // setFlare

	//--------------------------------------------------------

	void CLight::setAttenuation(const float range,
								const float constant,
								const float linear,
								const float quadratic){
		_light->setAttenuation(range, constant, linear, quadratic);

	} // setAttenuation

	//--------------------------------------------------------

	void CLight::setVisible(bool visible)
	{
		_light->setVisible(visible);
		_billboardSetFlare->setVisible(visible);

	} // setVisible

} // namespace Graphics
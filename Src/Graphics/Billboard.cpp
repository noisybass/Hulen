#include "Billboard.h"

#include <assert.h>

#include <OgreEntity.h>
#include <OgreAnimationState.h>
#include <OgreSceneManager.h>
#include "Graphics\Scene.h"

namespace Graphics 
{

	CBillBoard::CBillBoard(const std::string &name) :
		CEntity(name)
	{
		
	} // CRibbonTrail

	void CBillBoard::init(Vector3& position, Ogre::ColourValue& color, float width, float height, std::string& materialName)
	{

		_billboardSet = _scene->getSceneMgr()->createBillboardSet(1);
		_billboardSet->setBillboardOrigin(Ogre::BillboardOrigin::BBO_TOP_LEFT);
		_billboard = _billboardSet->createBillboard(position, color);
		_billboard->setDimensions(width, height);
		_billboardSet->setMaterialName(materialName);
		
		_node->attachObject(_billboardSet);

	} // init

	bool CBillBoard::load()
	{
		_node = _scene->getSceneMgr()->getRootSceneNode()->createChildSceneNode();
		_loaded = true;
		return true;
	} // load

	void CBillBoard::setDimensions(float width, float height)
	{
		_billboard->setDimensions(width, height);
	} // setDimensions

	void CBillBoard::unload()
	{
		_node->detachAllObjects();
		_scene->getSceneMgr()->destroySceneNode(_node);
		_node = nullptr;
	} // unload

	CBillBoard::~CBillBoard()
	{
		
	}

} // namespace Graphics
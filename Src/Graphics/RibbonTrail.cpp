#include "RibbonTrail.h"

#include <assert.h>

#include <OgreEntity.h>
#include <OgreAnimationState.h>
#include <OgreSceneManager.h>

namespace Graphics 
{
	
	/**
	CKasaiControllerFunction
	*/
	Ogre::Real CKasaiControllerFunction::calculate(Ogre::Real source)
	{
		return _faded;
	};

	/**
	CRibbonTrail
	*/

	CRibbonTrail::CRibbonTrail(const std::string &name) :
		CEntity(name), Ogre::RibbonTrail(name + std::string("_ribbonTrailNode"))
	{

	} // CRibbonTrail

	void CRibbonTrail::init(Ogre::SceneNode* anotherNode, std::string& materialName, float lenght, float maxChain,
		Vector3& initialRGB, float initialAlpha, Vector3& changeRGB, float changeAlpha, float initialWidth, float fadedValue)
	{
		Ogre::SceneManager* sceneMgr = _scene->getSceneMgr();

		this->setMaterialName(materialName);
		this->setTrailLength(lenght);
		this->setMaxChainElements(maxChain);
		this->setInitialColour(0, initialRGB.x, initialRGB.y, initialRGB.z, initialAlpha);
		this->setColourChange(0, changeRGB.x, changeRGB.y, changeRGB.z, changeAlpha);
		this->setInitialWidth(0, initialWidth);
		this->addNode(anotherNode);

		// Change the function to control the fading
		kasaiFunction = OGRE_NEW CKasaiControllerFunction(fadedValue);
		Ogre::SharedPtr<Ogre::ControllerFunction<Ogre::Real>> func = Ogre::SharedPtr<CKasaiControllerFunction>();
		func.bind(kasaiFunction);
		this->mFadeController->setFunction(func);

		_scene->getSceneMgr()->getRootSceneNode()->attachObject(this);

	} // init

	bool CRibbonTrail::load()
	{
		_loaded = true;
		return true;
	} // load

	CRibbonTrail::~CRibbonTrail()
	{
		// Don't delete Kasai controller because 
		// Ogre::Ribbontrail do it for us.
	}

} // namespace Graphics
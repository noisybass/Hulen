#ifndef GRAPHICS_RIBBON_TRAIL_H
#define GRAPHICS_RIBBON_TRAIL_H

#include "Graphics/Entity.h"
#include "Graphics/Scene.h"
#include <OgreRibbonTrail.h>
	
namespace Graphics 
{

	/**
	Class to change the ribbon trail behaviour
	*/
	class CKasaiControllerFunction : public Ogre::ControllerFunction<Ogre::Real>
	{
	public:
		CKasaiControllerFunction(float faded) : ControllerFunction<Ogre::Real>(false), _faded(faded){}

		Ogre::Real calculate(Ogre::Real source);

	protected:
		float _faded;
	};


	/**
	
	*/
	class CRibbonTrail : public CEntity, public Ogre::RibbonTrail
	{
	public:

		/**
		Constructor de la clase.

		@param name Nombre de la entidad.
		@param mesh Nombre del modelo que debe cargarse.
		*/
		CRibbonTrail(const std::string &name);

		/**
		Destructor de la aplicación.
		*/
		virtual ~CRibbonTrail();

		void init(Ogre::SceneNode* anotherNode, std::string& materialName, float lenght, float maxChain,
			Vector3& initialRGB, float initialAlpha, Vector3& changeRGB, float changeAlpha, float initialWidth, float fadedValue);

		bool load() override;

	protected:
		CKasaiControllerFunction* kasaiFunction;// RibbonTrail function

	}; // class CAnimatedEntity

} // namespace Graphics

#endif // GRAPHICS_RIBBON_TRAIL_H

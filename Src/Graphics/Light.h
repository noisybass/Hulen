#ifndef GRAPHICS_LIGHT_H
#define GRAPHICS_LIGHT_H

#include "Scene.h"

#include <string>

#include <OgreLight.h>

namespace Graphics
{
	class CLight
	{
	public:
		/**
		Constructor de la clase.

		@param name Nombre de la luz.
		*/
		CLight(const std::string& name);

		/**
		Destructor de la luz.
		*/
		virtual ~CLight();

		/**
		
		*/
		void setDiffuseColour(const Ogre::ColourValue &colour);

		/**

		*/
		void setSpecularColour(const Ogre::ColourValue &colour);

		/**
		A point light's attenuation defines how bright it is with respect to its distance from objects.
		*/
		void setAttenuation(const float range,
							const float constant,
							const float linear,
							const float quadratic);
		/**
		The Light will have a flare around it if you call this method.
		*/
		void setFlare(const Ogre::ColourValue colour, const std::string materialName, const unsigned int flareSize);

		

	protected:

		friend class CScene;

		/**
		Añade la luz al SceneManager pasado por parámetro.

		@param sceneMgr Gestor de la escena de Ogre a la que se quiere añadir
		la entidad.
		@return true si la entidad se pudo cargar y añadir a la escena.
		*/
		void attachToScene(CScene* scene);

		/**
		Descarga la luz de la escena en la que se encuentra cargada.
		*/
		void detachFromScene();

		/**
		Luz de Ogre.
		*/
		Ogre::Light* _light;

		/**
		Nombre de la luz.
		*/
		std::string _name;

		/**
		Tipo de la luz.
		*/
		Ogre::Light::LightTypes _type;

		/**
		
		*/
		CScene* _scene;


		/**
		Flare stuff
		*/
		Ogre::Billboard* _billboardFlare;

		Ogre::BillboardSet* _billboardSetFlare;

		Ogre::SceneNode* _node;

	}; // class CLight

} // namespace Graphics

#endif // GRAPHICS_LIGHT_H

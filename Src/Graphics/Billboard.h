#ifndef GRAPHICS_BILLBOARD_H
#define GRAPHICS_BILLBOARD_H

#include "Graphics/Entity.h"
#include <OgreBillboard.h>
#include <OgreBillboardSet.h>
	
namespace Graphics 
{
	class CBillBoard : public CEntity
	{
	public:

		/**
		Constructor de la clase.

		@param name Nombre de la entidad.
		@param mesh Nombre del modelo que debe cargarse.
		*/
		CBillBoard(const std::string &name);

		/**
		Destructor de la aplicación.
		*/
		virtual ~CBillBoard();

		void init(Vector3& position, Ogre::ColourValue& color, float width, float height, std::string& materialName);
		void setDimensions(float width, float height);
		void setVisible(bool visible) override;

		bool load() override;
		void unload() override;

	protected:
		Ogre::Billboard* _billboard;
		Ogre::BillboardSet* _billboardSet;
		Ogre::SceneNode* _node;

	}; // class CAnimatedEntity

} // namespace Graphics

#endif // GRAPHICS_BILLBOARD_H

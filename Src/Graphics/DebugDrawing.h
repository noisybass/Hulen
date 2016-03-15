#ifndef GRAPHICS_DEBUGDRAWING_H
#define GRAPHICS_DEBUGDRAWING_H

#include <OgreSingleton.h>
#include <OgreVector3.h>
#include <OgreRenderOperation.h>


namespace Graphics 
{
	
	class CDebugDrawing 
	{
	public:

		/**
		Constructor por defecto
		*/
		CDebugDrawing();

		virtual ~CDebugDrawing();

		void drawLine(const Ogre::Vector3 &start, const Ogre::Vector3 &end, const Ogre::ColourValue &colour, float alpha = 1.0f);

		/**
		Se encarga de recorrer las estructuras de datos y pintar.
		*/
		void tick(float secs);

	private:
		int addLineVertex(const Ogre::Vector3 &vertex, const Ogre::ColourValue &colour);
		void addLineIndices(int index1, int index2);

		/**
		Singleton
		*/
		static CDebugDrawing* _instance;

		struct DebugEntity{

			DebugEntity::DebugEntity() : _vertexPairList()
			{
				
			}

			/**
			Operación que queremos realizar, a elegir entre:
			OT_POINT_LIST 		A list of points 			1 vertex per point
			OT_LINE_LIST 		A list of lines 			2 vertices per line
			OT_LINE_STRIP 		A strip of connected lines 	1 start vertex and 1 vertex per line
			OT_TRIANGLE_LIST 	A list of triangles 		3 vertices per triangle
			OT_TRIANGLE_STRIP 	A strip of triangles 		3 vertices for the first triangle and 1 per triangle after that
			OT_TRIANGLE_FAN		A fan of triangles 			3 vertices for the first triangle and 1 per triangle after that 
			*/
			Ogre::RenderOperation::OperationType _operationType;

			/**
			Representa un punto en el espacio junto a su color.
			*/
			typedef std::pair<Ogre::Vector3, Ogre::ColourValue> tVertexPair;

			/**
			Lista con los vertices que contiene la entidad.
			*/
			std::vector<tVertexPair> _vertexPairList;
		};
		
		std::vector<DebugEntity*> _debugEntities;

		/*
		typedef std::pair<Ogre::Vector3, Ogre::ColourValue> tVertexPair;
		int linesIndex;
		std::list<int> lineIndices;
		std::list<tVertexPair> lineVertices;*/

	}; // class CDebugDrawing

} // namespace Graphics

#endif // GRAPHICS_DEBUGDRAWING_H

#ifndef GRAPHICS_DEBUGDRAWING_H
#define GRAPHICS_DEBUGDRAWING_H

#include <OgreSingleton.h>
#include <OgreVector3.h>
#include <OgreRenderOperation.h>
#include <OgreManualObject.h>
#include <unordered_map>


namespace Graphics 
{
	
	class CDebugDrawing 
	{
	public:

		/**
		Constructor por defecto
		*/
		CDebugDrawing();

		/**
		Destructor por defecto
		*/
		virtual ~CDebugDrawing();

		/**
		Dibujamos una linea
		*/
		void drawLine(const std::string &name, const Ogre::Vector3 &start, const Ogre::Vector3 &end, const Ogre::ColourValue &colour, float alpha = 1.0f);

		/**
		Se encarga de recorrer las estructuras de datos y pintar.
		*/
		void tick(float secs);

		/**
		Limpia las estructuras de datos y demás.
		*/
		void clean();

	private:

		/**
		Construimos las entidades para poder pintarlas despues con ogre en el tick
		*/
		void buildManualObjects();

		/**
		Pintamos las entidades que hemos construido previamente.
		*/
		void paintManualObjects();

		struct DebugEntity{

			DebugEntity::DebugEntity() = default;

			virtual DebugEntity::~DebugEntity() = default;

			DebugEntity::DebugEntity(const std::string name) : _vertexPairList(), _name (name), _manualObject(name), _sceneNode(nullptr), _updateManualObject(false){}

			/**
			Nombre de la entidad de depuración.
			*/
			std::string _name;

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

			/**
			La contruccion de la entidad con el que lo pintaremos.
			*/
			Ogre::ManualObject _manualObject;

			/**
			Nodo de la escena en el que se encuentra la entidad
			*/
			Ogre::SceneNode* _sceneNode;

			/**
			Flag para comprobar si un manualObject ha sido creado o no.
			*/
			bool _updateManualObject;
		};

		/**
		Singleton
		*/
		static CDebugDrawing* _instance;

		/**
		Scene Manager
		*/
		Ogre::SceneManager* _sceneManager;
		
		/**
		Lista con las entidades que vamos a construir para 
		despues pintarlas.
		*/
		//std::vector<DebugEntity*> _debugEntities;
		std::unordered_map<std::string, DebugEntity*> _debugEntities;

	}; // class CDebugDrawing

} // namespace Graphics

#endif // GRAPHICS_DEBUGDRAWING_H

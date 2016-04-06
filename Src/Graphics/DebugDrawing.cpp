#include "DebugDrawing.h"
#include "Graphics\Scene.h"
#include "Graphics\Server.h"

#include <assert.hpp>

#include <OgreColourValue.h>
#include <OgreSceneManager.h>

namespace Graphics
{
	CDebugDrawing* CDebugDrawing::_instance = nullptr;

	CDebugDrawing::CDebugDrawing() : _debugEntities()
	{
		assert(!_instance && "No puede hacer dos instancias de la clase DebugDrawing");
		if (!_instance){
			_instance = this;
			_sceneManager = Graphics::CServer::getSingletonPtr()->getActiveScene()->getSceneMgr();
		}
	}

	CDebugDrawing::~CDebugDrawing()
	{
		clean();
	}

	void CDebugDrawing::tick(float secs)
	{
		buildManualObjects();
		paintManualObjects();
		
	}

	void CDebugDrawing::buildManualObjects()
	{
		// Para todas las entidades de debug
		for (std::pair<std::string, DebugEntity*> debugEntityWithName : _debugEntities){
			DebugEntity* debugEntity = debugEntityWithName.second;

			// Si no ha sido creado el manual Object, lo creamos
			if (!debugEntity->_updateManualObject){
				debugEntity->_manualObject.begin("BaseWhiteNoLighting", debugEntity->_operationType);

				for (unsigned int j = 0; j < debugEntity->_vertexPairList.size(); ++j){
					DebugEntity::tVertexPair vertexPair = debugEntity->_vertexPairList[j];
					debugEntity->_manualObject.position(vertexPair.first);
					debugEntity->_manualObject.colour(vertexPair.second);
				}
				debugEntity->_manualObject.end();
				debugEntity->_updateManualObject = true;
			}
			// Solo modificamos los vertices del manual object sin volverlo a crear
			else{

				debugEntity->_manualObject.beginUpdate(0);

				for (unsigned int j = 0; j < debugEntity->_vertexPairList.size(); ++j){
					DebugEntity::tVertexPair vertexPair = debugEntity->_vertexPairList[j];
					debugEntity->_manualObject.position(vertexPair.first);
					debugEntity->_manualObject.colour(vertexPair.second);
				}

				debugEntity->_manualObject.end();
			}

			
		}
	}

	void CDebugDrawing::paintManualObjects()
	{
		for (std::pair<std::string, DebugEntity*> debugEntityWithName : _debugEntities){
			DebugEntity* debugEntity = debugEntityWithName.second;
			if (!debugEntity->_sceneNode){
				debugEntity->_sceneNode = _sceneManager->getRootSceneNode()->createChildSceneNode();
				debugEntity->_sceneNode->attachObject(&debugEntity->_manualObject);
			}
		}
	}


	void CDebugDrawing::drawLine(const std::string &name, const Ogre::Vector3 &start, const Ogre::Vector3 &end, const Ogre::ColourValue &colour, float alpha)
	{

		// Si no esta en el mapa, lo añadimos
		if (_debugEntities.find(name) == _debugEntities.end()){
			DebugEntity* debugEntity = new DebugEntity(name);
			debugEntity->_operationType = Ogre::RenderOperation::OperationType::OT_LINE_LIST;

			debugEntity->_vertexPairList.push_back(DebugEntity::tVertexPair(start, Ogre::ColourValue(colour.r, colour.g, colour.b, alpha)));
			debugEntity->_vertexPairList.push_back(DebugEntity::tVertexPair(end, Ogre::ColourValue(colour.r, colour.g, colour.b, alpha)));

			_debugEntities.insert({ name, debugEntity });
		}
		// Si esta en la lista, actualizamos los valores de los vertices.
		else{
			DebugEntity* debugEntity = _debugEntities.at(name);

			// Limpiamos lo que pudiese haber antes y metemos los puntos de la nueva linea
			debugEntity->_vertexPairList.clear();
			debugEntity->_vertexPairList.push_back(DebugEntity::tVertexPair(start, Ogre::ColourValue(colour.r, colour.g, colour.b, alpha)));
			debugEntity->_vertexPairList.push_back(DebugEntity::tVertexPair(end, Ogre::ColourValue(colour.r, colour.g, colour.b, alpha)));
		}
	}

	void CDebugDrawing::clean()
	{
		if (!_debugEntities.empty())
		{
			for (std::pair<std::string, DebugEntity*> debugEntityWithName : _debugEntities)
			{
				DebugEntity* debugEntity = debugEntityWithName.second;
				// Eliminamos el nodo
				debugEntity->_sceneNode->removeAndDestroyAllChildren();
				_sceneManager->destroySceneNode(debugEntity->_sceneNode);

				// Eliminamos la entidad de depuracion
				delete debugEntityWithName.second;
			}
			_debugEntities.clear();
		}
		
		_instance = nullptr;
		_sceneManager = nullptr;
	}

}
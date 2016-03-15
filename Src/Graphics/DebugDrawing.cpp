#include "DebugDrawing.h"
#include <OgreColourValue.h>
#include <assert.hpp>

namespace Graphics
{
	CDebugDrawing* CDebugDrawing::_instance = nullptr;

	CDebugDrawing::CDebugDrawing() : _debugEntities()
	{
		assert(_instance && "No puede hacer dos instancias de la clase DebugDrawing");
		if (!_instance){
			_instance = this;
		}
	}

	CDebugDrawing::~CDebugDrawing()
	{
		_instance = nullptr;
	}

	void CDebugDrawing::tick(float secs)
	{
		
	}

	void CDebugDrawing::drawLine(const Ogre::Vector3 &start, const Ogre::Vector3 &end, const Ogre::ColourValue &colour, float alpha)
	{
		/*int i = addLineVertex(start, Ogre::ColourValue(colour.r, colour.g, colour.b, alpha));
		addLineVertex(end, Ogre::ColourValue(colour.r, colour.g, colour.b, alpha));

		addLineIndices(i, i + 1);*/
		DebugEntity* debugEntity = new DebugEntity();
		debugEntity->_operationType = Ogre::RenderOperation::OperationType::OT_LINE_LIST;

		debugEntity->_vertexPairList.push_back(DebugEntity::tVertexPair(start, Ogre::ColourValue(colour.r, colour.g, colour.b, alpha)));
		debugEntity->_vertexPairList.push_back(DebugEntity::tVertexPair(end,   Ogre::ColourValue(colour.r, colour.g, colour.b, alpha)));

	}

	int CDebugDrawing::addLineVertex(const Ogre::Vector3 &vertex, const Ogre::ColourValue &colour){
		/*lineVertices.push_back(tVertexPair(vertex, colour));
		return linesIndex++;*/
		return 1;
	}

	void CDebugDrawing::addLineIndices(int index1, int index2){
		/*lineIndices.push_back(index1);
		lineIndices.push_back(index2);*/
	}
}
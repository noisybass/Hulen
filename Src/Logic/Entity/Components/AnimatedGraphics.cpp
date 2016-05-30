/**
@file AnimatedGraphics.cpp

Contiene la implementación del componente que controla la representación
gráfica de una entidad estática.
 
@see Logic::CAnimatedGraphics
@see Logic::IComponent

@author David Llansó
@date Agosto, 2010
*/

#include "AnimatedGraphics.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Scene.h"
#include "Logic/Entity/GameObject.h"

namespace Logic 
{
	IMP_FACTORY(CAnimatedGraphics);
	
	//---------------------------------------------------------

	Graphics::CEntity* CAnimatedGraphics::createGraphicsEntityFromFile(const Map::CEntity *entityInfo)
	{
		_animatedGraphicsEntity = new Graphics::CAnimatedEntity(_entity->getName(),_model);
		
		if(!_scene->addEntity(_animatedGraphicsEntity))
			return 0;

		if (entityInfo->hasAttribute("defaultAnimationVelocity"))
		{
			_defaultAnimationVelocity = entityInfo->getFloatAttribute("defaultAnimationVelocity");
		}

		if (entityInfo->hasAttribute("defaultBlendingVelocity"))
		{
			_defaultBlendingVelocity = entityInfo->getFloatAttribute("defaultBlendingVelocity");
		}

		std::unordered_map<std::string, float> animationValues;
		setAnimationsValues(entityInfo, animationValues);

		std::unordered_map<std::string, float> blendingValues;
		setBlendingValues(entityInfo, blendingValues);
#ifdef _DEBUG
		_animatedGraphicsEntity->dumpAnimsStates();
#endif
		_animatedGraphicsEntity->initAnimationStates(_defaultAnimationVelocity, animationValues,
													 _defaultBlendingVelocity, blendingValues);
		//_animatedGraphicsEntity->setTransform(_entity->getTransform());
		_animatedGraphicsEntity->setPosition(_entity->getPosition());

		if (entityInfo->hasAttribute("scale"))
		{
			_scale = entityInfo->getVector3Attribute("scale");
			_animatedGraphicsEntity->setScale(_scale);
		}
		
		if(entityInfo->hasAttribute("defaultAnimation"))
		{
			_defaultAnimation = entityInfo->getStringAttribute("defaultAnimation");
			_animatedGraphicsEntity->setAnimation(_defaultAnimation,true);
			_animatedGraphicsEntity->setObserver(this);
		}

		return _animatedGraphicsEntity;

	} // createGraphicsEntity

	//---------------------------------------------------------

	

	//---------------------------------------------------------
	
	bool CAnimatedGraphics::activate()
	{
		_graphicsEntity->setVisible(true);
		return true;

	} // activate

	//---------------------------------------------------------

	void CAnimatedGraphics::deactivate()
	{
		_graphicsEntity->setVisible(false);

	} // deactivate

	//---------------------------------------------------------

	bool CAnimatedGraphics::accept(const TMessage &message)
	{
		return CGraphics::accept(message) ||
			   message._type == Message::SET_ANIMATION ||
			   message._type == Message::STOP_ANIMATION;

	} // accept
	
	//---------------------------------------------------------

	void CAnimatedGraphics::process(const TMessage &message)
	{
		CGraphics::process(message);

		TMessage m;
		switch (message._type)
		{
		case Message::SET_ANIMATION:
			// Paramos todas las animaciones antes de poner una nueva.
			// Un control más sofisticado debería permitir interpolación
			// de animaciones. Galeon no lo plantea.
			//_animatedGraphicsEntity->stopAllAnimations();

			if (message.existArg("nextAnimation"))
				_animatedGraphicsEntity->setAnimation(message.getArg<std::string>("animation"),
					message.getArg<bool>("loop"), message.getArg<bool>("nextAnimation"));
			else
				_animatedGraphicsEntity->setAnimation(message.getArg<std::string>("animation"),
					message.getArg<bool>("loop"));
			break;
		case Message::STOP_ANIMATION:
			_animatedGraphicsEntity->stopAnimation(message.getArg<std::string>("animation"));
			break;
		}

	} // process

	void CAnimatedGraphics::sendState(CAnimatedGraphics* receiver)
	{
		std::cout << "AnimatedGraphics mandando estado..." << std::endl;
		receiver->_animatedGraphicsEntity->setPosition(Vector3(_entity->getPosition().x,
															   _entity->getPosition().y,
															   receiver->_entity->getPosition().z)); // La z no cambia
		receiver->_animatedGraphicsEntity->setAnimation(_animatedGraphicsEntity->getCurrentAnimationName(),
														_animatedGraphicsEntity->getCurrentAnimationLoop());
	}
	
	//---------------------------------------------------------
	
	void CAnimatedGraphics::animationFinished(const std::string &animation, bool nextAnimation)
	{
		// Si acaba una animación y tenemos una por defecto la ponemos
		//_animatedGraphicsEntity->stopAllAnimations();

		Logic::TMessage m;
		m._type = Logic::Message::ANIMATION_WITHOUT_LOOP_FINISHED;
		m.setArg<std::string>("name", animation);
		_entity->emitMessage(m);

		if (nextAnimation)
			_animatedGraphicsEntity->setAnimation(_defaultAnimation, true);
		
	} // animationFinisheda

	void CAnimatedGraphics::animationWithoutLoopStarted(const std::string &animation)
	{
		Logic::TMessage m;
		m._type = Logic::Message::ANIMATION_WITHOUT_LOOP_STARTED;
		m.setArg<std::string>("name", animation);
		_entity->emitMessage(m);
	} // animationWithoutLoopStarted

	void CAnimatedGraphics::setAnimationsValues(const Map::CEntity *entityInfo, std::unordered_map<std::string, float>& animationValues)
	{

		if (entityInfo->hasAttribute("idle1Animation"))
			animationValues.insert(entityInfo->getPairStringFloat("idle1Animation"));

		if (entityInfo->hasAttribute("idle2Animation"))
			animationValues.insert(entityInfo->getPairStringFloat("idle2Animation"));

		if (entityInfo->hasAttribute("walkAnimation"))
			animationValues.insert(entityInfo->getPairStringFloat("walkAnimation"));

		if (entityInfo->hasAttribute("runAnimation"))
			animationValues.insert(entityInfo->getPairStringFloat("runAnimation"));

		if (entityInfo->hasAttribute("deathAnimation"))
			animationValues.insert(entityInfo->getPairStringFloat("deathAnimation"));

		if (entityInfo->hasAttribute("jump1Animation"))
			animationValues.insert(entityInfo->getPairStringFloat("jump1Animation"));

		if (entityInfo->hasAttribute("fall1Animation"))
			animationValues.insert(entityInfo->getPairStringFloat("fall1Animation"));

		if (entityInfo->hasAttribute("land1Animation"))
			animationValues.insert(entityInfo->getPairStringFloat("land1Animation"));

		if (entityInfo->hasAttribute("jump2Animation"))
			animationValues.insert(entityInfo->getPairStringFloat("jump2Animation"));

		if (entityInfo->hasAttribute("fall2Animation"))
			animationValues.insert(entityInfo->getPairStringFloat("fall2Animation"));

		if (entityInfo->hasAttribute("land2Animation"))
			animationValues.insert(entityInfo->getPairStringFloat("land2Animation"));

		if (entityInfo->hasAttribute("pickObjectAnimation"))
			animationValues.insert(entityInfo->getPairStringFloat("pickObjectAnimation"));

		if (entityInfo->hasAttribute("changeDirectionAnimation"))
			animationValues.insert(entityInfo->getPairStringFloat("changeDirectionAnimation"));

		if (entityInfo->hasAttribute("startRunAnimation"))
			animationValues.insert(entityInfo->getPairStringFloat("startRunAnimation"));

		if (entityInfo->hasAttribute("preparationAnimation"))
			animationValues.insert(entityInfo->getPairStringFloat("preparationAnimation"));

		if (entityInfo->hasAttribute("killScreamAnimation"))
			animationValues.insert(entityInfo->getPairStringFloat("killScreamAnimation"));

	} // setAnimationsValues

	void CAnimatedGraphics::setBlendingValues(const Map::CEntity *entityInfo, std::unordered_map<std::string, float>& blendingValues)
	{

		if (entityInfo->hasAttribute("idle1Blending"))
			blendingValues.insert(entityInfo->getPairStringFloat("idle1Blending"));

		if (entityInfo->hasAttribute("idle2Blending"))
			blendingValues.insert(entityInfo->getPairStringFloat("idle2Blending"));

		if (entityInfo->hasAttribute("walkBlending"))
			blendingValues.insert(entityInfo->getPairStringFloat("walkBlending"));

		if (entityInfo->hasAttribute("runBlending"))
			blendingValues.insert(entityInfo->getPairStringFloat("runBlending"));

		if (entityInfo->hasAttribute("deathBlending"))
			blendingValues.insert(entityInfo->getPairStringFloat("deathBlending"));

		if (entityInfo->hasAttribute("jump1Blending"))
			blendingValues.insert(entityInfo->getPairStringFloat("jump1Blending"));

		if (entityInfo->hasAttribute("fall1Blending"))
			blendingValues.insert(entityInfo->getPairStringFloat("fall1Blending"));

		if (entityInfo->hasAttribute("land1Blending"))
			blendingValues.insert(entityInfo->getPairStringFloat("land1Blending"));

		if (entityInfo->hasAttribute("jump2Blending"))
			blendingValues.insert(entityInfo->getPairStringFloat("jump2Blending"));

		if (entityInfo->hasAttribute("fall2Blending"))
			blendingValues.insert(entityInfo->getPairStringFloat("fall2Blending"));

		if (entityInfo->hasAttribute("land2Blending"))
			blendingValues.insert(entityInfo->getPairStringFloat("land2Blending"));

		if (entityInfo->hasAttribute("pickObjectBlending"))
			blendingValues.insert(entityInfo->getPairStringFloat("pickObjectBlending"));

		if (entityInfo->hasAttribute("changeDirectionBlending"))
			blendingValues.insert(entityInfo->getPairStringFloat("changeDirectionBlending"));

		if (entityInfo->hasAttribute("startRunBlending"))
			blendingValues.insert(entityInfo->getPairStringFloat("startRunBlending"));

		if (entityInfo->hasAttribute("preparationBlending"))
			blendingValues.insert(entityInfo->getPairStringFloat("preparationBlending"));

		if (entityInfo->hasAttribute("killScreamBlending"))
			blendingValues.insert(entityInfo->getPairStringFloat("killScreamBlending"));

	} // setAnimationsValues

} // namespace Logic


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

	Graphics::CEntity* CAnimatedGraphics::createGraphicsEntity(const Map::CEntity *entityInfo)
	{
		_animatedGraphicsEntity = new Graphics::CAnimatedEntity(_entity->getName(),_model);
		
		if(!_scene->addEntity(_animatedGraphicsEntity))
			return 0;

		if (entityInfo->hasAttribute("defaultAnimationVelocity"))
		{
			_defaultAnimationVelocity = entityInfo->getFloatAttribute("defaultAnimationVelocity");
		}

		std::unordered_map<std::string, float> animationValues;

		setAnimationsValues(entityInfo, animationValues);

		_animatedGraphicsEntity->dumpAnimsStates();
		_animatedGraphicsEntity->initAnimationStates(_defaultAnimationVelocity, animationValues);
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
			   message._type == Message::STOP_ANIMATION ||
			   message._type == Message::SEND_STATE ||
			   message._type == Message::RECEIVE_ANIMATION_STATE;

	} // accept
	
	//---------------------------------------------------------

	void CAnimatedGraphics::process(const TMessage &message)
	{
		CGraphics::process(message);

		TMessage m;
		switch(message._type)
		{
		case Message::SET_ANIMATION:
			// Paramos todas las animaciones antes de poner una nueva.
			// Un control más sofisticado debería permitir interpolación
			// de animaciones. Galeon no lo plantea.
			//_animatedGraphicsEntity->stopAllAnimations();
			_animatedGraphicsEntity->setAnimation(message.getArg<std::string>("animation"),
				message.getArg<bool>("loop"));
			break;
		case Message::STOP_ANIMATION:
			_animatedGraphicsEntity->stopAnimation(message.getArg<std::string>("animation"));
			break;
		case Message::SEND_STATE:
			std::cout << "Mandando estado..." << std::endl;
			m._type = Message::RECEIVE_ANIMATION_STATE;
			m.setArg<std::string>(std::string("animation"), _animatedGraphicsEntity->getCurrentAnimationName());
			m.setArg<bool>(std::string("loop"), _animatedGraphicsEntity->getCurrentAnimationLoop());

			message.getArg<CEntity*>("receiver")->emitMessage(m);
			break;
		case Message::RECEIVE_ANIMATION_STATE:
			std::cout << "Recibiendo estado..." << std::endl;
			//_animatedGraphicsEntity->stopAllAnimations();
			_animatedGraphicsEntity->setAnimation(message.getArg<std::string>("animation"),
				message.getArg<bool>("loop"));
			break;
		}

	} // process
	
	//---------------------------------------------------------
	
	void CAnimatedGraphics::animationFinished(const std::string &animation)
	{
		// Si acaba una animación y tenemos una por defecto la ponemos
		//_animatedGraphicsEntity->stopAllAnimations();

		Logic::TMessage m;
		m._type = Logic::Message::ANIMATION_WITHOUT_LOOP_FINISHED;
		m.setArg<std::string>("name", animation);
		_entity->emitMessage(m);
		
		_animatedGraphicsEntity->setAnimation(_defaultAnimation, true);
		
	} // animationFinished

	void CAnimatedGraphics::animationWithoutLoopStarted(const std::string &animation)
	{
		Logic::TMessage m;
		m._type = Logic::Message::ANIMATION_WITHOUT_LOOP_STARTED;
		m.setArg<std::string>("name", animation);
		_entity->emitMessage(m);
	} // animationWithoutLoopStarted

} // namespace Logic


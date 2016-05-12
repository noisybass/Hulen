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

		if (entityInfo->hasAttribute("fadeInOut_Velocity"))
		{
			_fadeInOutvelocity = entityInfo->getIntAttribute("fadeInOut_Velocity");
		}

		//_animatedGraphicsEntity->dumpAnimsStates();
		_animatedGraphicsEntity->initAnimationStates(_fadeInOutvelocity);
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
		_animatedGraphicsEntity->stopAllAnimations();
		_animatedGraphicsEntity->setAnimation(_defaultAnimation,true);
	}

} // namespace Logic


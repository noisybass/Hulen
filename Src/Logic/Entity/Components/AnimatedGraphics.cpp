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

#include "Logic/Entity/Components/FSMEntity.h"

namespace Logic 
{
	IMP_FACTORY(CAnimatedGraphics);

	CAnimatedGraphics::~CAnimatedGraphics()
	{
		_animationNames->clear();
		delete _animationNames;
		_animationNames = nullptr;
	} // ~CAnimatedGraphics
	
	//---------------------------------------------------------

	Graphics::CEntity* CAnimatedGraphics::createGraphicsEntityFromFile(const Map::CEntity *entityInfo)
	{
		_animatedGraphicsEntity = new Graphics::CAnimatedEntity(_entity->getName(),_model);
		_animationNames = new std::unordered_map<std::string, std::string>();
		
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

	void CAnimatedGraphics::deactivate(bool isDeletingMap)
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
		//std::cout << "AnimatedGraphics mandando estado..." << std::endl;
		receiver->_animatedGraphicsEntity->setPosition(Vector3(_entity->getPosition().x,
															   _entity->getPosition().y,
															   receiver->_entity->getPosition().z)); // La z no cambia

		receiver->_animatedGraphicsEntity->setAnimation(_animatedGraphicsEntity->getCurrentAnimationName(),
			_animatedGraphicsEntity->getCurrentAnimationLoop());

		receiver->_animatedGraphicsEntity->copyCurrentAnimationsValues(_animatedGraphicsEntity->getCurrentAnimation());

		
	}
	
	//---------------------------------------------------------
	
	void CAnimatedGraphics::animationFinished(const std::string &animation, bool nextAnimation)
	{
		// Si acaba una animación y tenemos una por defecto la ponemos
		//_animatedGraphicsEntity->stopAllAnimations();

		// Send value to LUA FSM if isn't the player.
		if (_entity->getName() != "Player_Body" && _entity->getName() != "Player_Shadow")
		{
			Logic::CFSMEntity* fsm = (Logic::CFSMEntity*)(_entity->getComponent("CFSMEntity"));
			fsm->setValue<bool>(_animationNames->at(animation) + "Started", false);
			fsm->setValue<bool>(_animationNames->at(animation) + "Finish", true);
		}
		
		Logic::TMessage m;
		m._type = Logic::Message::ANIMATION_WITHOUT_LOOP_FINISHED;
		m.setArg<std::string>("name", animation);
		_entity->emitMessage(m);

		if (nextAnimation)
			_animatedGraphicsEntity->setAnimation(_defaultAnimation, true);
		
	} // animationFinisheda

	void CAnimatedGraphics::animationWithoutLoopStarted(const std::string &animation)
	{

		// Send value to LUA FSM if isn't the player.
		if (_entity->getName() != "Player_Body" && _entity->getName() != "Player_Shadow")
		{
			Logic::CFSMEntity* fsm = (Logic::CFSMEntity*)(_entity->getComponent("CFSMEntity"));
			fsm->setValue<bool>(_animationNames->at(animation) + "Finish", false);
			fsm->setValue<bool>(_animationNames->at(animation) + "Started", true);
		}

		Logic::TMessage m;
		m._type = Logic::Message::ANIMATION_WITHOUT_LOOP_STARTED;
		m.setArg<std::string>("name", animation);
		_entity->emitMessage(m);
	} // animationWithoutLoopStarted

	void CAnimatedGraphics::setAnimationsValues(const Map::CEntity *entityInfo, std::unordered_map<std::string, float>& animationValues)
	{

		if (entityInfo->hasAttribute("idle1Animation"))
		{
			animationValues.insert(entityInfo->getPairStringFloat("idle1Animation"));
			_animationNames->insert({ entityInfo->getPairStringFloat("idle1Animation").first, std::string("idle1Animation") });
		}	
			
		if (entityInfo->hasAttribute("idle2Animation"))
		{
			animationValues.insert(entityInfo->getPairStringFloat("idle2Animation"));
			_animationNames->insert({ entityInfo->getPairStringFloat("idle2Animation").first, std::string("idle2Animation") });
		}	
			
		if (entityInfo->hasAttribute("walkAnimation"))
		{
			animationValues.insert(entityInfo->getPairStringFloat("walkAnimation"));
			_animationNames->insert({ entityInfo->getPairStringFloat("walkAnimation").first, std::string("walkAnimation") });
		}	
			
		if (entityInfo->hasAttribute("runAnimation"))
		{
			animationValues.insert(entityInfo->getPairStringFloat("runAnimation"));
			_animationNames->insert({ entityInfo->getPairStringFloat("runAnimation").first, std::string("runAnimation") });
		}	
			
		if (entityInfo->hasAttribute("deathAnimation"))
		{
			animationValues.insert(entityInfo->getPairStringFloat("deathAnimation"));
			_animationNames->insert({ entityInfo->getPairStringFloat("deathAnimation").first, std::string("deathAnimation") });
		}
			
		if (entityInfo->hasAttribute("jump1Animation"))
		{
			animationValues.insert(entityInfo->getPairStringFloat("jump1Animation"));
			_animationNames->insert({ entityInfo->getPairStringFloat("jump1Animation").first, std::string("jump1Animation") });
		}	
			
		if (entityInfo->hasAttribute("fall1Animation"))
		{
			animationValues.insert(entityInfo->getPairStringFloat("fall1Animation"));
			_animationNames->insert({ entityInfo->getPairStringFloat("fall1Animation").first, std::string("fall1Animation") });
		}	

		if (entityInfo->hasAttribute("land1Animation"))
		{
			animationValues.insert(entityInfo->getPairStringFloat("land1Animation"));
			_animationNames->insert({ entityInfo->getPairStringFloat("land1Animation").first, std::string("land1Animation") });
		}
				
		if (entityInfo->hasAttribute("jump2Animation"))
		{
			animationValues.insert(entityInfo->getPairStringFloat("jump2Animation"));
			_animationNames->insert({ entityInfo->getPairStringFloat("jump2Animation").first, std::string("jump2Animation") });
		}	

		if (entityInfo->hasAttribute("fall2Animation"))
		{
			animationValues.insert(entityInfo->getPairStringFloat("fall2Animation"));
			_animationNames->insert({ entityInfo->getPairStringFloat("fall2Animation").first, std::string("fall2Animation") });
		}

		if (entityInfo->hasAttribute("land2Animation"))
		{
			animationValues.insert(entityInfo->getPairStringFloat("land2Animation"));
			_animationNames->insert({ entityInfo->getPairStringFloat("land2Animation").first, std::string("land2Animation") });
		}
			
		if (entityInfo->hasAttribute("pickObjectAnimation"))
		{
			animationValues.insert(entityInfo->getPairStringFloat("pickObjectAnimation"));
			_animationNames->insert({ entityInfo->getPairStringFloat("pickObjectAnimation").first, std::string("pickObjectAnimation") });
		}
				
		if (entityInfo->hasAttribute("changeDirectionAnimation"))
		{
			animationValues.insert(entityInfo->getPairStringFloat("changeDirectionAnimation"));
			_animationNames->insert({ entityInfo->getPairStringFloat("changeDirectionAnimation").first, std::string("changeDirectionAnimation") });
		}
			
		if (entityInfo->hasAttribute("startRunAnimation"))
		{
			animationValues.insert(entityInfo->getPairStringFloat("startRunAnimation"));
			_animationNames->insert({ entityInfo->getPairStringFloat("startRunAnimation").first, std::string("startRunAnimation") });
		}
			
		if (entityInfo->hasAttribute("preparationAnimation"))
		{
			animationValues.insert(entityInfo->getPairStringFloat("preparationAnimation"));
			_animationNames->insert({ entityInfo->getPairStringFloat("preparationAnimation").first, std::string("preparationAnimation") });
		}
			
		if (entityInfo->hasAttribute("killScreamAnimation"))
		{
			animationValues.insert(entityInfo->getPairStringFloat("killScreamAnimation"));
			_animationNames->insert({ entityInfo->getPairStringFloat("killScreamAnimation").first, std::string("killScreamAnimation") });
		}

		if (entityInfo->hasAttribute("eatLightAnimation"))
		{
			animationValues.insert(entityInfo->getPairStringFloat("eatLightAnimation"));
			_animationNames->insert({ entityInfo->getPairStringFloat("eatLightAnimation").first, std::string("eatLightAnimation") });
		}

		if (entityInfo->hasAttribute("attackAnimation"))
		{
			animationValues.insert(entityInfo->getPairStringFloat("attackAnimation"));
			_animationNames->insert({ entityInfo->getPairStringFloat("attackAnimation").first, std::string("attackAnimation") });
		}
			
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

		if (entityInfo->hasAttribute("eatLightBlending"))
			blendingValues.insert(entityInfo->getPairStringFloat("eatLightBlending"));

		if (entityInfo->hasAttribute("attackBlending"))
			blendingValues.insert(entityInfo->getPairStringFloat("attackBlending"));

	} // setAnimationsValues

} // namespace Logic


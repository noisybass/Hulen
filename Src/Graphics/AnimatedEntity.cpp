#include "AnimatedEntity.h"

#include <assert.h>

#include <OgreEntity.h>
#include <OgreAnimationState.h>

namespace Graphics 
{
	
	CAnimatedEntity::CAnimatedEntity(const std::string &name, const std::string &mesh) : 
		CEntity(name, mesh), _currentAnimation(nullptr), _fadeInOutVelocity(0)
	{
		
	} // Constructor

	CAnimatedEntity::~CAnimatedEntity()
	{
		for (auto it : _animations)
		{
			delete it.second;
		}
		_animations.clear();
	} // Destructor

	bool CAnimatedEntity::setAnimation(const std::string &anim, bool loop)
	{

		if (_currentAnimation != nullptr)
		{
			// if anim is the same animation, don't do nothing.
			if (_currentAnimation->animationState->getAnimationName() == anim)
				return true;

			// If there are an animation yet, we set to true the fading out.
			// We disable the animation when its weight arrived to zero on tick method.
			//_animations.at(_currentAnimation.animationState->getAnimationName());
			//_currentAnimation->animationState->setTimePosition(0); // To reset animation
			_currentAnimation->fadingIn = false;
			_currentAnimation->fadingOut = true;
			
		}

		assert(_animations.find(anim) != _animations.end() && "The animation that you want play don't exist. SetAnimation");
		Animation* newAnimation = _animations.at(anim);
		newAnimation->animationState->setEnabled(true); // Enable the new animation
		//if (!_currentAnimation.fadingOut)
		//	_currentAnimation.animationState->setWeight(0); // Reset weight
		newAnimation->animationState->setLoop(loop);
		newAnimation->animationState->setWeight(0.0f);
		newAnimation->animationState->setTimePosition(0.0f);
		newAnimation->fadingIn = true;
		newAnimation->fadingOut = false;
		_currentAnimation = newAnimation;

		if (!loop)
		{
			_observer->animationWithoutLoopStarted(getCurrentAnimationName());
		}

		return true;

	} // setAnimation

	//--------------------------------------------------------
		
	bool CAnimatedEntity::stopAnimation(const std::string &anim)
	{
		if(!_entity->getAllAnimationStates()->hasAnimationState(anim))
			return false;
		Ogre::AnimationState *animation = _entity->getAnimationState(anim);
		animation->setEnabled(false);
		// Si la animación a parar es la animación activa ya no lo estará.
		if(animation == _currentAnimation->animationState)
			_currentAnimation->animationState = nullptr;
		return true;

	} // stopAnimation

	//--------------------------------------------------------
		
	void CAnimatedEntity::stopAllAnimations()
	{
		if(_entity->getAllAnimationStates()->hasEnabledAnimationState())
		{
			Ogre::ConstEnabledAnimationStateIterator it = 
				_entity->getAllAnimationStates()->getEnabledAnimationStateIterator();
			Ogre::AnimationState *animation;

			//hay que recorrer con el iterador las animaciones una a una y pausarlas
			while(it.hasMoreElements())
			{
				animation = it.getNext();
				animation->setEnabled(false);
			}

			// Si había animación activa ya no lo está.
			_currentAnimation->animationState = nullptr;
		}

	} // stopAllAnimations

	//--------------------------------------------------------
		
	void CAnimatedEntity::tick(float secs)
	{
		if (_currentAnimation->animationState)
		{
			// Add time to the main animation
			_currentAnimation->animationState->addTime(secs);

			// Do fadeIn/fadeOut
			for (std::pair<std::string, Animation*> anim : _animations)
			{
				Animation* animation = anim.second;
				if (animation->fadingIn)
				{
					//std::cout << animation->animationState->getAnimationName() << " IN: ";
					Ogre::Real newWeight = animation->animationState->getWeight() + secs * _fadeInOutVelocity;
					//std::cout << newWeight << std::endl;
					if (newWeight >= 1.0f)
					{
						newWeight = 1.0f;
						animation->fadingIn = false;
						_animations.insert({ anim.first, animation });
					}
					animation->animationState->setWeight(newWeight);
				}
				else if (animation->fadingOut)
				{
					//std::cout << animation->animationState->getAnimationName() << " OUT: ";
					Ogre::Real newWeight = animation->animationState->getWeight() - secs * _fadeInOutVelocity;
					//std::cout << newWeight << std::endl;
					if (newWeight <= 0.0f)
					{
						newWeight = 0.0f;
						animation->fadingOut = false;
						animation->animationState->setEnabled(false); // Disable animation
						_animations.insert({ anim.first, animation });
					}
					animation->animationState->setWeight(newWeight);
				}
			}

			// Comprobamos si la animación ha terminado para avisar
			if (_observer && _currentAnimation->animationState->hasEnded())
				_observer->animationFinished(_currentAnimation->animationState->getAnimationName());
		}

	} // tick

	std::string CAnimatedEntity::getCurrentAnimationName() const
	{
		return _currentAnimation->animationState->getAnimationName();

	} // getCurrentAnimationName


	bool CAnimatedEntity::getCurrentAnimationLoop() const
	{
		return _currentAnimation->animationState->getLoop();

	} // getCurrentAnimationLopp

	void CAnimatedEntity::dumpAnimsStates() {

		Ogre::AnimationStateSet *allAnimations = _entity->getAllAnimationStates();

		Ogre::AnimationStateIterator it = allAnimations->getAnimationStateIterator();

		std::cout << "------------ " << _entity->getName() << " -----------" << std::endl;
		printf("         Nombre\tEnabled\tWeight\tLong.\tLoop\tPos.\tBlendMask\n");
		while (it.hasMoreElements()) {
			Ogre::AnimationState *as = it.getNext();
			printf("%15s\t%s\t%1.4f\t%1.4f\t%s\t%1.4f\t%s\n",
				as->getAnimationName().c_str(),
				as->getEnabled() ? "true" : "false",
				as->getWeight(), as->getLength(),
				as->getLoop() ? "true" : "false",
				as->getTimePosition(),
				as->hasBlendMask() ? "true" : "false");
		}
		std::cout << "------------ END -----------" << std::endl;

	} // dumpAnimsStates

	void CAnimatedEntity::initAnimationStates(int fadeInOutVelocity)
	{
		Ogre::AnimationStateSet *allAnimations = _entity->getAllAnimationStates();
		Ogre::AnimationStateIterator it = allAnimations->getAnimationStateIterator();

		while (it.hasMoreElements()) {
			Ogre::AnimationState *as = it.getNext();
			_animations.insert({as->getAnimationName(), new Animation(as, false, false)});
		}

		_fadeInOutVelocity = fadeInOutVelocity;

	} // initAnimationStates

} // namespace Graphics
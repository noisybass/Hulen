#ifndef GRAPHICS_ANIMATED_ENTITY_H
#define GRAPHICS_ANIMATED_ENTITY_H

#include "Graphics/Entity.h"
#include "Graphics/Scene.h"

// Predeclaración de clases para ahorrar tiempo de compilación
namespace Ogre 
{
	class AnimationState;
}
	
namespace Graphics 
{
	/**
	Esta clase debe ser implementada por las clases que quieren
	registrarse en una entidad animada para enterarse de cuando
	terminan las animaciones de ésta.
	
	@ingroup graphicsGroup

	@author David Llansó
	@date Julio, 2010
	*/
	class CAnimatedEntityListener 
	{
	public:

		/**
		Método que será invocado siempre que se termine una animación.
		Las animaciones en cíclicas no invocarán nunca este método.

		@param animation Nombre de la animación terminada.
		*/
		virtual void animationFinished(const std::string &animation) {}

	}; // CAnimatedEntityListener

	/**
	Clase que representa una entidad gráfica con animaciones. Especializa la clase
	Graphics::CEntity por lo que contiene una referencia a una entidad de 
	Ogre y al Nodo que la contiene. Añade la posibilidad de activar una animación 
	y reproducirla.
	<p>
	Esta clase es bastante sencilla y solo controlamos una animación activa.
	Podría ser más sofisticada permitiendo interpolación de animaciones o avisando
	mediante observers cuando una animación termina de reproducirse.
	<p>
	Oculta los detalles escabrosos del motor gráfico.
	
	@ingroup graphicsGroup

	@author David Llansó
	@date Julio, 2010
	*/
	class CAnimatedEntity : public CEntity
	{
	public:

		/**
		Constructor de la clase.

		@param name Nombre de la entidad.
		@param mesh Nombre del modelo que debe cargarse.
		*/
		CAnimatedEntity(const std::string &name, const std::string &mesh);

		/**
		Destructor de la aplicación.
		*/
		virtual ~CAnimatedEntity();

		/**
		Activa una animación a partir de su nombre.

		@param anim Nombre de la animación a activar.
		@param loop true si la animación debe reproducirse cíclicamente.
		@return true si la animación solicitada fue correctamente activada.
		*/
		bool setAnimation(const std::string &anim, bool loop);
		
		/**
		Desactiva una animación a partir de su nombre.

		@param anim Nombre de la animación a activar.
		@return true si la animación solicitada fue correctamente desactivada.
		*/
		bool stopAnimation(const std::string &anim);
		
		/**
		Desactiva todas las animaciones de una entidad.
		*/
		void stopAllAnimations();

		/**
		Función que registra al oyente de la entidad gráfica. Por 
		simplicidad solo habrá un oyente por entidad.
		*/
		void setObserver(CAnimatedEntityListener *observer)
											{_observer = observer;}

		/**
		Función que quita al oyente de la entidad gráfica. Por 
		simplicidad solo habrá un oyente por entidad.
		*/
		void removeObserver(CAnimatedEntityListener *observer)
							{if(_observer = observer) _observer = 0;}

		std::string getCurrentAnimationName() const;

		bool getCurrentAnimationLoop() const;

		void dumpAnimsStates();

		void initAnimationStates(int fadeInOutVelocity);

	protected:

		/**
		Objeto oyente que es informado de cambios en la entidad como 
		la terminación de las animaciones. Por simplicidad solo habrá
		un oyente por entidad.
		*/
		CAnimatedEntityListener *_observer;

		// Cada entidad debe pertenecer a una escena. Solo permitimos
		// a la escena actualizar el estado.
		friend class CScene;
		
		/**
		Actualiza el estado de la entidad cada ciclo.
		
		@param secs Número de milisegundos transcurridos desde la última 
		llamada.
		*/
		virtual void tick(float secs);

		struct Animation{
			Animation() : animationState(nullptr), fadingIn(false), fadingOut(false){};

			Animation(Ogre::AnimationState* as, bool fadingIn, bool fadingOut) :
				animationState(as), fadingIn(fadingIn), fadingOut(fadingOut){};

			~Animation() = default;

			Ogre::AnimationState* animationState;
			bool fadingIn;
			bool fadingOut;
		};

		std::unordered_map < std::string, Animation* > _animations;


		/**
		Animación que tiene la entidad activada.
		*/
		Animation* _currentAnimation;

		int _fadeInOutVelocity;

	}; // class CAnimatedEntity

} // namespace Graphics

#endif // __Graphics_AnimatedEntity_H

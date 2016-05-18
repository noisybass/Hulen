/**
@file Camera.h

Contiene la declaración del componente que controla la cámara gráfica
de una escena.

@see Logic::CCamera
@see Logic::IComponent

@author David Llansó
@date Septiembre, 2010
*/
#ifndef __Logic_Camera_H
#define __Logic_Camera_H

#include "Logic/Entity/Component.h"

// Predeclaración de clases para ahorrar tiempo de compilación
namespace Graphics 
{
	class CCamera;
	class CScene;
}

//declaración de la clase
namespace Logic 
{
/**
	Componente que se encarga de mover la cámara gráfica de una escena, para que 
	ésta se pueda reenderizar, siguiendo al jugador.
	<p>
	La cámara se situará a una distancia detrás del jugador y a una altura del 
	suelo y enfocará a un punto imaginario por delante del jugador que estará 
	también a cierta altura del suelo. Todas estas características son configurables 
	desde la declaración del mapa definiendo los nombres de atributo "distance",
	"height", "targetDistance" y "targetHeight".
	<p>
	El componente irá recalculando en cada ciclo las posiciones de la cámara y del
	punto de mira en función de la posición y orientación del jugador.
	
    @ingroup logicGroup

	@author David Llansó García
	@date Septiembre, 2010
*/
	class CCamera : public IComponent
	{
		DEC_FACTORY(CCamera);
	public:

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		CCamera() : IComponent(), _graphicsCamera(0), _zoomSpeed(1), 
			_isZoomedIn(false), _isZoomingIn(false), _isZoomingOut(false),
			_offsetX(0), _offsetY(0), _offsetZ(0){}
		
		/**
		Inicialización del componente, utilizando la información extraída de
		la entidad leída del mapa (Maps::CEntity). Se accede a los atributos 
		necesarios como la cámara gráfica y se leen atributos del mapa.

		@param entity Entidad a la que pertenece el componente.
		@param map Mapa Lógico en el que se registrará el objeto.
		@param entityInfo Información de construcción del objeto leído del
			fichero de disco.
		@return Cierto si la inicialización ha sido satisfactoria.
		*/
		virtual bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		Método que activa el componente; invocado cuando se activa
		el mapa donde está la entidad a la que pertenece el componente.
		<p>
		Se coge el jugador del mapa, la entidad que se quiere "seguir".

		@return true si todo ha ido correctamente.
		*/
		virtual bool activate();
		
		/**
		Método que desactiva el componente; invocado cuando se
		desactiva el mapa donde está la entidad a la que pertenece el
		componente. Se invocará siempre, independientemente de si estamos
		activados o no.
		<p>
		Se pone el objetivo a seguir a NULL.
		*/
		virtual void deactivate();

		/**
		Método llamado en cada frame que actualiza el estado del componente.
		<p>
		Se encarga de mover la cámara siguiendo al jugador.

		@param msecs Milisegundos transcurridos desde el último tick.
		*/
		virtual void tick(float msecs);

		/**
		Metodo que sirve para hacer el zoomIn sobre el personaje.
		Solo lo hace cuando no se ha hecho un zoomIn anteriormente.
		Hace el zoomIn sobre el player.
		*/
		void zoomIn();

		/**
		Metodo que sirve para hacer el zoomIn sobre el personaje.
		Solo lo hace cuando no se ha hecho un zoomIn anteriormente.
		Hace el zoomIn sobre el player.
		*/
		void zoomOut();

	protected:
		
		/**
		Cámara gráfica.
		*/
		Graphics::CCamera *_graphicsCamera;

		/**
		Indica si la camara debe seguir al target o no. 
		Esto implica que la posición del target no debe actualizarse en cada tick.
		*/
		bool _fixed;

		// Parámetros del zoom de la cámara

		/**
		Posicion inicial de la cámara.
		*/
		Vector3 startPosition;

		/**
		Velocidad a la que hace el Zoom In y Zoom Out.
		*/
		float _zoomSpeed;

		/**
		Indica si la cámara está haciendo un Zoom In.
		*/
		bool _isZoomingIn;

		/**
		Indica si se ha hecho un Zoom In.
		*/
		bool _isZoomedIn;

		/**
		Indica si está haciendo un Zoom Out.
		*/
		bool _isZoomingOut;

		/**
		Coordenada X que se le suma a la posición del player sobre la ue hacer zoom.
		*/
		float _offsetX;

		/**
		Coordenada Y que se le suma a la posición del player sobre la ue hacer zoom.
		*/
		float _offsetY;

		/**
		Coordenada > que se le suma a la posición del player sobre la ue hacer zoom.
		*/
		float _offsetZ;

	}; // class CCamera

	REG_FACTORY(CCamera);

} // namespace Logic

#endif // __Logic_Camera_H

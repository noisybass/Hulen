#ifndef VISION_H
#define VISION_H

#include "Logic/Entity/Component.h"
#include "Logic/Entity/Components/FSMEntity.h"

//declaración de la clase
namespace Logic 
{
/**
	Este componente procesa mensajes de tipo TOUCHED o UNTOUCHED (indican que la 
	entidad ha sido tocada o dejada de ser tocada) para enviar un mensaje SWITCH a 
	una entidad objetivo.
	<p>
	La entidad objetivo se especifica en el mapa con el atributo "target". Este 
	atributo <em>debe</em> ser especificado.
	
    @ingroup logicGroup

	@author David Llansó García
	@date Octubre, 2010
*/
	class CVision : public IComponent
	{
		DEC_FACTORY(CVision);
	public:

		/**
		Constructor por defecto.
		*/
		CVision() : IComponent(), _fsm(nullptr), _ray(), _defaultVision(5), _xRaySeparation(0.7), _yRaySeparation(0.5),
			_seeingEntity(false), _lastSeenEntity(nullptr) {}
		
		/**
		Inicialización del componente usando la descripción de la entidad que hay en 
		el fichero de mapa.
		*/
		bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;

		bool activate() override;

		void deactivate() override;

		bool accept(const TMessage &message) override;

		void process(const TMessage &message) override;

		void tick(unsigned int msecs) override;

		/**
		Devuelve la primera entidad vista. Utiliza
		la vision por defecto o que se ha proporcionado al crear
		el objeto.
		*/
		Logic::CEntity* visionRay();

		/**
		Devuelve la primera entidad vista. Se calcula dada la distancia 
		a la que se quiere calcular el rayo.
		*/
		Logic::CEntity* visionRay(const float maxDistance);

		bool _seeingEntity;
		Logic::CEntity* _lastSeenEntity;

	protected:

		Logic::CFSMEntity* _fsm;

		Ray _ray;

		float _defaultVision;

		float _xRaySeparation;
		float _yRaySeparation;

	}; // class CVision

	REG_FACTORY(CVision);

} // namespace Logic

#endif // VISION_H

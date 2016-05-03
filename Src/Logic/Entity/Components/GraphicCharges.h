#ifndef LOGIC_GRAPHIC_CHARGES_H
#define LOGIC_GRAPHIC_CHARGES_H

#include "Logic/Entity/Component.h"

//declaración de la clase
namespace Logic 
{
	class CGraphicCharges : public IComponent
	{
		DEC_FACTORY(CGraphicCharges);
	public:

		/**
		Constructor por defecto.
		*/
		CGraphicCharges() : IComponent(), _graphicChargeName("GraphicCharge_Prefab"), _numCharges(0) {}
		
		/**
		Inicialización del componente usando la descripción de la entidad que hay en 
		el fichero de mapa.
		*/
		bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;

		bool activate() override;

		void deactivate() override;

		bool accept(const TMessage &message) override;

		void process(const TMessage &message) override;

		void tick(float msecs) override;

	protected:

		std::vector<CGameObject*> _graphicCharges;

		std::string _graphicChargeName;

		unsigned int _numCharges;

	}; // class CGraphicCharges

	REG_FACTORY(CGraphicCharges);

} // namespace Logic

#endif // LOGIC_GRAPHIC_CHARGES_H

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
		CGraphicCharges() : IComponent(), _graphicChargeName("GraphicCharge_Prefab"), _numCharges(0),
			_graphicChargeVelocity(5.5), _graphicChargeRadius(3), _graphicChargeRotationBar(0.2f),
			_graphicChargesDeltaSeparation(0.15f), _graphicChargesDeltaSeparationToFirstCharge(0.85f){}
		
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

		/**
		Guardamos las cargas que vamos a poner en la escena aquí
		para que hagan la animacion de ir a la posicion del ratón.
		*/
		std::vector<CGameObject*> _thrownOutCharges;

		std::string _graphicChargeName;

		/**
		Funcion con la que conseguimos que las cargas giren a una misma distancia.
		OJO: Por ahora solo esta implementado para 3 cargas e inferior.
		*/
		bool equilateralTriangle(int chargeNum, float sideOfTriangle);

		/**
		Numero de cargas
		*/
		unsigned int _numCharges;

		/**
		Velocidad de la carga
		*/
		float _graphicChargeVelocity;

		/**
		Velocidad de la carga desde su sitio hasta
		el centro del raton (PUT_CHARGE)
		*/
		float _thrownChargeVelocity;

		/**
		Radio al que van a girar las cargas de Kasai
		*/
		float _graphicChargeRadius;

		/**
		Distancia entre una carga y otra.
		OJO: En teoria las cargas siempre deberian de estar a la misma distancia
		pero por temas de computo de la velocidad a la que van de las cargas, hay que
		tener un rango que sumaremos y restaremos a esta distancia para que al calcular
		la velocidad este dentro de este valor.
		Los rangos que utilizaremos son los siguientes: "_graphicChargesDeltaSeparation" y
		"_graphicChargesDeltaSeparationToFirstCharge"
		*/
		float _graphicChargeDistanceBetweenThem;

		/**
		Rango que utilizamos para que las cargas giren al "mismo"
		radio, lo hacemos tambien por el tema del calculo de la velocidad
		comentado en el anterior comentario.
		*/
		float _graphicChargeRotationBar;

		/**
		Rango que utilizamos para las cargas de la 0 a la 3
		*/
		float _graphicChargesDeltaSeparation;

		/**
		Ultimo rango que utilizamos para comprobar que la ultima carga y la primera 
		carga estan a la misma distancia.
		*/
		float _graphicChargesDeltaSeparationToFirstCharge;

	}; // class CGraphicCharges

	REG_FACTORY(CGraphicCharges);

} // namespace Logic

#endif // LOGIC_GRAPHIC_CHARGES_H

#ifndef LOGIC_PLAYER_MANAGER_H
#define LOGIC_PLAYER_MANAGER_H

#include "Logic/Entity/Component.h"
#include "Logic/Entity/GameObject.h"
#include "Sounds/api/SoundsResources.h"

#include <vector>

namespace Logic
{
	/**
	Este componente es el encargado de hacer que el game object que representa
	al player cambie de estado físico a sombra, o viceversa. 
	Para que el player pueda cambiar de estado tiene que estar iluminado.
	*/
	class CPlayerManager : public IComponent
	{
		DEC_FACTORY(CPlayerManager);
	public:

		CPlayerManager();

		~CPlayerManager();

		bool spawn(const std::string& name, CGameObject* gameObject, CMap *map, const Map::CEntity *entityInfo) override;

		bool activate() override;

		bool accept(const TMessage &message) override;

		void process(const TMessage &message) override;

		void tick(float msecs) override;

		unsigned int howManyCharges() const { return _chargesOwned; };

		void addMapCharges(CGameObject* gameObject);
	protected:

		/**
		Atributo que indica si el jugador esta iluminado
		*/
		bool _onLight;

		void changeState(GameObject::TState state);

		void sendState(Logic::CEntity* emitter, Logic::CEntity* receiver);

		bool playerOnLight() const;

		CGameObject* canPickAnyCharge() const;

		CGameObject* nearOfLever() const;

		

	private:

		/**
		Opcion de depuracion, si lo ponemos a true el jugador puede morir,
		si no por defecto no morira.
		*/
		bool _playerCanDie;

		/**
		Atributo que indica el tiempo maximo que el jugador
		puede mantenerse en la oscuridad.
		*/
		float _playerDeathTime;

		/**
		El tiempo que le queda para que el jugador muera.
		*/
		float _deathTimeElapsed;

		/**
		Nombre del puntero de luz.
		*/
		std::string _kasaiName;

		/**
		Referencia al puntero de luz.
		*/
		CGameObject* _kasai;

		/**
		Nombre de la carga.
		*/
		std::string _chargePrefab;

		/**
		Contador de cargas, solo podremos tener 3, pero vamos a dejar un margen 
		de 9 numeros para las cargas para evitar posibles sobreescribiento de nombres.
		*/
		unsigned int _chargesCount;

		/**
		Vector que guarda las referencias a las cargas que están puestas en el mapa.
		*/
		std::vector<CGameObject*> _chargesOnMap;

		/**
		Número de cargas que puede poner el jugador.
		*/
		unsigned int _chargesOwned;

		/**
		To play sounds
		*/
		Sounds::CSoundsResources* _soundsResources;

		// Animations
		std::string _pickObjectAnimation;


	}; // class CPlayerManager

	REG_FACTORY(CPlayerManager);

} // namespace Logic

#endif // LOGIC_PLAYER_MANAGER_H
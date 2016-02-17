#ifndef LOGIC_PLAYER_MANAGER_H
#define LOGIC_PLAYER_MANAGER_H

#include "Logic/Entity/Component.h"

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

		bool accept(const TMessage &message) override;

		void process(const TMessage &message) override;

		void tick(unsigned int msecs) override;
	protected:

		/**
		Atributo que indica si el jugador esta iluminado
		*/
		bool _onLight;

		void changeState();

	private:

		/**
		El tiempo que le queda para que el jugador muera.
		*/
		float _deathTimeElapsed;

	}; // class CPlayerManager

	REG_FACTORY(CPlayerManager);

} // namespace Logic

#endif // LOGIC_PLAYER_MANAGER_H
#ifndef SOUNDS_BANK_H
#define SOUNDS_BANK_H

#include <unordered_map>
#include "fmod\studio\fmod_studio.hpp"

namespace Sounds{

	class CBank{

	public:

		/**
		Constructor de la clase.
		*/
		CBank();

		/**
		Destructor de la clase.
		*/
		~CBank();

		bool loadBank(std::string bankName, std::string fileName);

		bool unloadBank(std::string bankName);

		FMOD::Studio::Bank* getBank(std::string bankName);
	
	private:

		// Instancia de fmod studio
		FMOD::Studio::System* _fmod_studio_system;

		typedef std::unordered_map<std::string, FMOD::Studio::Bank*> tBanks;
		tBanks *_banks;

	}; // class CBank

} // namespace Sounds
#endif SOUNDS_BANK_H

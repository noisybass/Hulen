#include "Sounds\studio\Bank.h"
#include "Sounds\Server.h"
#include <assert.h>


namespace Sounds{


	CBank::CBank()
	{
		// Obtenemos el sistema de bajo nivel
		_fmod_studio_system = Sounds::CServer::getSingletonPtr()->_fmod_studio_system;

		// Inicializamos la estuctura de datos
		_banks = new tBanks();
	}

	CBank::~CBank()
	{
		_fmod_studio_system = nullptr;

		delete _banks;
	}

	bool CBank::loadBank(std::string bankName, std::string fileName)
	{
		std::string file = CServer::getSoundsPath() + fileName;
		FMOD::Studio::Bank* bank = nullptr;

		/**
		OJO: When loading banks with FMOD_STUDIO_LOAD_BANK_NORMAL,
		the function will not return until the bank has completed loading
		*/
		FMOD_RESULT result = _fmod_studio_system->loadBankFile(file.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);
		assert(result == FMOD_OK && "Error al cargar el banco. Sounds::CBank::loadBank");

		_banks->insert({bankName, bank});

		return result == FMOD_OK;
	}

	bool CBank::unloadBank(std::string bankName)
	{
		assert(_banks->find(bankName) != _banks->end() && "Tiene que existir el banco para poder descargarlo. Sounds::CBank::unloadBank");
		FMOD::Studio::Bank* bank = _banks->at(bankName);

		FMOD_RESULT result = bank->unload();
		assert(result == FMOD_OK && "Error al descargar el banco. Sounds::CBank::unloadBank");

		if (result == FMOD_OK)
			_banks->erase(bankName);

		return result == FMOD_OK;
	}

	FMOD::Studio::Bank* CBank::getBank(std::string bankName)
	{
		FMOD::Studio::Bank* bank = _banks->at(bankName);
		assert(bank && "No existe el sonido para crear el canal. Sounds::CBank::getBank");

		return bank;
	}
};

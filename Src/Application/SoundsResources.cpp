
#include "SoundsResources.h"
#include "Sounds\Server.h"
#include <assert.h>

namespace Application {

	// Definition
	CSoundsResources* CSoundsResources::_instance = nullptr;

	CSoundsResources::CSoundsResources(){
		assert(!_instance && "Segunda inicialización de Graphics::CServer no permitida!");
		_instance = this;
	} // CSoundsResources

	CSoundsResources::~CSoundsResources(){
		assert(_instance);
		_instance = nullptr;
	} // ~CSoundsResources

	bool CSoundsResources::init(){
		assert(!_instance && "Segunda inicialización de Graphics::CServer no permitida!");
		new CSoundsResources();
		return true;
	} // init

	void CSoundsResources::release(){
		if (_instance){
			delete _instance;
		}
	} // release

	void CSoundsResources::loadAll(){
		loadMainMenu();
	} // loadAll

	void CSoundsResources::unloadAll(){
		unloadMainMenu();
	} // unloadAll

	void CSoundsResources::loadMainMenu(){
		Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		soundServer->getBanksPtr()->loadBank("Banco1", "Master Bank.bank");
		soundServer->getBanksPtr()->loadBank("Banco2", "Master Bank.strings.bank");
		soundServer->getBanksPtr()->loadBank("Banco3", "Ambiente.bank");
		soundServer->getEventDescriptionsPtr()->loadEventDescription("MainMenuEvent", "event:/Ambientes");
	} // loadMainMenu

	void CSoundsResources::unloadMainMenu(){
		Sounds::CServer* soundServer = Sounds::CServer::getSingletonPtr();
		soundServer->getEventDescriptionsPtr()->unloadEventDescription("MainMenuEvent");
		soundServer->getBanksPtr()->unloadBank("Banco3");
		soundServer->getBanksPtr()->unloadBank("Banco2");
		soundServer->getBanksPtr()->unloadBank("Banco1");
	} // unloadMainMenu

} // namespace Application

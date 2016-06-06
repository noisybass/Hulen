
#include "SoundsResources.h"
#include <assert.h>

namespace Sounds {

	// Definition
	CSoundsResources* CSoundsResources::_instance = nullptr;
	Sounds::CServer* CSoundsResources::_soundServer = nullptr;

	CSoundsResources::CSoundsResources(){
		assert(!_instance && "Segunda inicialización de Graphics::CServer no permitida!");
		_soundServer = Sounds::CServer::getSingletonPtr();
		_instance = this;
	} // CSoundsResources

	CSoundsResources::~CSoundsResources(){
		assert(_instance);
		_instance = nullptr;
		_soundServer = nullptr;
	} // ~CSoundsResources


	//
	// Instances
	//-----------

	void CSoundsResources::createInstance(std::string instanceName, std::string descriptionName, bool paused){
		_soundServer->getEventInstancesPtr()->loadInstance(instanceName, descriptionName);
		_soundServer->getEventInstancesPtr()->setPaused(instanceName, paused);
		_soundServer->getEventInstancesPtr()->start(instanceName);
	} // createInstance

	void CSoundsResources::deleteInstance(std::string instanceName){
		_soundServer->getEventInstancesPtr()->stop(instanceName);
	} // deleteInstance

	void CSoundsResources::playInstance(std::string instanceName){
		_soundServer->getEventInstancesPtr()->setPaused(instanceName, false);
	} // playInstance

	void CSoundsResources::pauseInstance(std::string instanceName){
		_soundServer->getEventInstancesPtr()->setPaused(instanceName, true);
	} // playInstance

	void CSoundsResources::setInstanceParameterValue(std::string instanceName, std::string parameterName, float parameterValue){
		_soundServer->getEventInstancesPtr()->setParameterValue(instanceName, parameterName, parameterValue);
	} // setInstanceParameterValue

	void CSoundsResources::setInstanceVolume(std::string instanceName, float volume){
		_soundServer->getEventInstancesPtr()->setVolume(instanceName, volume);
	} // setInstanceVolume


	//
	// Sounds
	//-----------

	void CSoundsResources::createSound(std::string channelName, std::string soundName, bool paused){
		_soundServer->getChannelsPtr()->loadChannel(channelName, soundName, paused);
	} // createSound

	void CSoundsResources::deleteSound(std::string channelName){
		_soundServer->getChannelsPtr()->stop(channelName);
	} // deleteSound

	void CSoundsResources::playSound(std::string channelName){
		_soundServer->getChannelsPtr()->setPaused(channelName, false);
	} // playSound

	void CSoundsResources::pauseSound(std::string channelName){
		_soundServer->getChannelsPtr()->setPaused(channelName, true);
	} // playSound

	bool CSoundsResources::getPausedSound(std::string channelName){
		return _soundServer->getChannelsPtr()->getPaused(channelName);
	} // getPausedSound

	void CSoundsResources::setSoundPitch(std::string channelName, float pitch){
		_soundServer->getChannelsPtr()->setPitch(channelName, pitch);
	} // setSoundPitch

	void CSoundsResources::setSoundVolume(std::string channelName, float volume){
		_soundServer->getChannelsPtr()->setVolume(channelName, volume);
	} // setSoundVolume

	void CSoundsResources::playAndDestroySound(std::string soundName, float volume){
		_soundServer->getChannelsPtr()->loadChannelAndDestroy(soundName, volume);
	} // playAndDestroy

	void CSoundsResources::setPositionAndVelocity(std::string channelName, Vector3 position, Vector3 velocity){
		/**
		-2 to 2 X Sounds position
		-2 to 2 Y Sounds position
		*/
		FMOD_VECTOR fmod_position = { position.x/15, position.y/15, position.z/15 };
		FMOD_VECTOR fmod_velocity = { velocity.x/8.5, velocity.y/8.5, velocity.z/8.5 };

		_soundServer->getChannelsPtr()->set3DAttributes(channelName, fmod_position, fmod_velocity);
	} // setPositionAndVelocity


	//
	// Resources
	//-----------

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
		loadPrisoner();
		loadCentaur();
	} // loadAll

	void CSoundsResources::unloadAll(){
		unloadMainMenu();
		unloadPrisoner();
		unloadCentaur();
	} // unloadAll


	//
	// Main Menu Resources
	//-----------

	void CSoundsResources::loadMainMenu(){
		_soundServer->getBanksPtr()->loadBank("Banco1", "Master Bank.bank");
		_soundServer->getBanksPtr()->loadBank("Banco2", "Master Bank.strings.bank");
		_soundServer->getBanksPtr()->loadBank("Banco3", "Ambiente.bank");
		_soundServer->getEventDescriptionsPtr()->loadEventDescription("MainMenuEvent", "event:/Ambientes");
	} // loadMainMenu

	void CSoundsResources::unloadMainMenu(){
		_soundServer->getEventDescriptionsPtr()->unloadEventDescription("MainMenuEvent");
		_soundServer->getBanksPtr()->unloadBank("Banco3");
		_soundServer->getBanksPtr()->unloadBank("Banco2");
		_soundServer->getBanksPtr()->unloadBank("Banco1");
	} // unloadMainMenu


	//
	// Prisoner Resources
	//-----------

	void CSoundsResources::loadPrisoner(){

		// Shadow Song
		_soundServer->getSoundsPtr()->loadSound("ShadowSong", "ShadowSong.mp3", Sounds::Loop_Normal + Sounds::Sound_3D);

		// Shadow deep
		_soundServer->getSoundsPtr()->loadSound("DeepIntoShadow", "DeepIntoShadow.mp3", Sounds::Loop_Off + Sounds::Sound_3D);

		// Prisoner walk and shadow walk
		_soundServer->getSoundsPtr()->loadSound("PrisonerWalk", "PrisonerWalk.mp3", Sounds::Loop_Normal + Sounds::Sound_3D);
		_soundServer->getSoundsPtr()->loadSound("PrisonerShadowWalk", "PrisonerShadowWalk.mp3", Sounds::Loop_Normal + Sounds::Sound_3D);
		
	} // loadPrisoner

	void CSoundsResources::unloadPrisoner(){

		// Shadow Song
		_soundServer->getSoundsPtr()->unloadSound("ShadowSong");

		// Shadow Deep
		_soundServer->getSoundsPtr()->unloadSound("DeepIntoShadow");

		// Prisoner walk and shadow walk
		_soundServer->getSoundsPtr()->unloadSound("PrisonerWalk");
		_soundServer->getSoundsPtr()->unloadSound("PrisonerShadowWalk");

	} // unloadPrisoner


	//
	// Centaur Resources
	//-----------

	void CSoundsResources::loadCentaur(){

		// Centaur Screeches
		_soundServer->getSoundsPtr()->loadSound("CentaurScreeches", "CentaurScreeches.wav", Sounds::Loop_Off + Sounds::Sound_3D);
	
	} // loadCentaur

	void CSoundsResources::unloadCentaur(){

		// Centaur Screeches
		_soundServer->getSoundsPtr()->unloadSound("CentaurScreeches");

	} // unloadCentaur

} // namespace Application

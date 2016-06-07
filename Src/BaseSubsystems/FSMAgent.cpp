#include "FSMAgent.h"

#include "BaseSubsystems/ScriptManager.h"

#include "Logic/Entity/Components/State.h"

#include "Logic/Entity/Message.h"

namespace AI
{

	FSMAgent::FSMAgent(Logic::CEntity* entity, const std::string& initialState) : _seeingPlayer(false), _entity(entity), _sounds(Sounds::CSoundsResources::getSingletonPtr())
	{
		_agentValues = new TValues();

		_FSM = new AI::FSM<FSMAgent>(this);

		lua_State* lua = ScriptManager::CScriptManager::GetPtrSingleton()->getNativeInterpreter();

		luabind::object states = luabind::globals(lua);

		if (luabind::type(states) == LUA_TTABLE)
		{
			_FSM->setCurrentState(states[initialState]);
		}

	} // Crawler

	FSMAgent::~FSMAgent()
	{
		delete _agentValues;
		delete _FSM;
		_sounds = nullptr;

	} // ~Crawler

	void FSMAgent::update(float msecs)
	{
		_FSM->update(msecs);

	} // update

	void FSMAgent::changeState(const luabind::object& newState)
	{
		_FSM->changeState(newState);

	} // changeState

	void FSMAgent::activate(const std::string& component)
	{
		Logic::CState* stateComponent = (Logic::CState*)_entity->getComponent(component);

		stateComponent->enterState();

	} // activate

	void FSMAgent::deactivate(const std::string& component)
	{
		Logic::CState* stateComponent = (Logic::CState*)_entity->getComponent(component);

		stateComponent->exitState();

	} // deactivate

	void FSMAgent::setAnimation(const std::string& animationName, bool loop, bool nextAnimation)
	{
		Logic::TMessage message;
		message._type = Logic::Message::SET_ANIMATION;
		message.setArg<std::string>("animation", getValue<std::string>(animationName));
		message.setArg<bool>("loop", loop);
		message.setArg<bool>("nextAnimation", nextAnimation);
		_entity->emitMessage(message);

	} // setAnimation

	/**
	Instances
	*/
	void FSMAgent::createInstance(std::string instanceName, std::string descriptionName, bool paused)
	{
		_sounds->createInstance(instanceName, descriptionName, paused);
	} // createInstance

	void FSMAgent::deleteInstance(std::string instanceName)
	{
		_sounds->deleteInstance(instanceName);
	} // deleteInstance

	void FSMAgent::playInstance(std::string instanceName)
	{
		_sounds->playInstance(instanceName);
	} // playInstance
	
	void FSMAgent::pauseInstance(std::string instanceName)
	{
		_sounds->pauseInstance(instanceName);
	} // pauseInstance

	void FSMAgent::setInstanceParameterValue(std::string instanceName, std::string parameterName, float parameterValue)
	{
		_sounds->setInstanceParameterValue(instanceName, parameterName, parameterValue);
	} // setInstanceParameterValue

	void FSMAgent::setInstanceVolume(std::string instanceName, float volume)
	{
		_sounds->setInstanceVolume(instanceName, volume);
	} // setInstanceVolume

	/**
	Sounds
	*/

	void FSMAgent::createSound(std::string channelName, std::string soundName, bool paused)
	{
		_sounds->createSound(channelName, soundName, paused);
	} // createSound

	void FSMAgent::deleteSound(std::string channelName)
	{
		_sounds->deleteSound(channelName);
	} // deleteSound

	void FSMAgent::playSound(std::string channelName)
	{
		_sounds->playSound(channelName);
	} // playSound

	void FSMAgent::pauseSound(std::string channelName)
	{
		_sounds->pauseSound(channelName);
	} // pauseSound

	bool FSMAgent::getPausedSound(std::string channelName)
	{
		return _sounds->getPausedSound(channelName);
	} // getPausedSound

	void FSMAgent::setSoundPitch(std::string channelName, float pitch)
	{
		_sounds->setSoundPitch(channelName, pitch);
	} // setSoundPitch

	void FSMAgent::setSoundVolume(std::string channelName, float volume)
	{
		_sounds->setSoundVolume(channelName, volume);
	} // setSoundVolume

	void FSMAgent::playAndDestroySound(std::string soundName, float volume, float pitch, Vector3& position, Vector3& velocity)
	{
		_sounds->playAndDestroySound(soundName, volume, pitch, position, velocity);
	} // playAndDestroySound

	void FSMAgent::setPositionAndVelocity(std::string channelName, Vector3 &position, Vector3 &velocity)
	{
		_sounds->setPositionAndVelocity(channelName, position, velocity);
	} // setPositionAndVelocity

} // namespace AI
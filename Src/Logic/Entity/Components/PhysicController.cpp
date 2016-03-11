/**
@file PhysicController.cpp

Contiene la implementación del componente que se utiliza para representar jugadores y enemigos en
el mundo físico usando character controllers.

@see Logic::CPhysicController
@see Logic::CPhysicEntity
@see Logic::IPhysics

@author Antonio Sánchez Ruiz-Granados
@date Noviembre, 2012
*/

#include "PhysicController.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/Components/AvatarController.h"
#include "Map/MapEntity.h"
#include "Physics/Server.h"
#include "Physics/Conversions.h"

#include <PxPhysicsAPI.h>

using namespace Logic;
using namespace Physics;
using namespace physx; 

IMP_FACTORY(CPhysicController);

//---------------------------------------------------------

CPhysicController::CPhysicController() : IPhysics(), _controller(NULL), 
								       _movement(0,0,0), _falling(false)
{
	_server = CServer::getSingletonPtr();
}

//---------------------------------------------------------

CPhysicController::~CPhysicController() 
{
	if (_controller) {
		_controller->release();
		_controller = NULL;
	}

	_server = NULL;
} 

//---------------------------------------------------------

bool CPhysicController::spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
{
	// Invocar al método de la clase padre
	if(!IComponent::spawn(name, entity,map,entityInfo))
		return false;

	// Crear el character controller asociado al componente
	_controller = createController(entityInfo);

	return true;
}

//---------------------------------------------------------

bool CPhysicController::accept(const TMessage &message)
{
	return message._type == Message::AVATAR_WALK ||
		message._type == Message::SEND_STATE ||
		message._type == Message::RECEIVE_PHYSIC_STATE;
} 

//---------------------------------------------------------

void CPhysicController::process(const TMessage &message)
{
	TMessage m;
	Vector3 receiverPosition, senderPosition;
	switch(message._type)
	{
	case Message::AVATAR_WALK:
		// Anotamos el vector de desplazamiento para usarlo posteriormente en 
		// el método tick. De esa forma, si recibimos varios mensajes AVATAR_WALK
		// en el mismo ciclo sólo tendremos en cuenta el último.
		_movement = message.getArg<Vector3>("movement");
		break;
	case Message::SEND_STATE:
		std::cout << "Mandando estado..." << std::endl;
		m._type = Message::RECEIVE_PHYSIC_STATE;
		m.setArg<Vector3>("movement", _movement);
		m.setArg<bool>("falling", _falling);
		receiverPosition = message.getArg<CEntity*>("receiver")->getPosition();
		senderPosition = Physics::PxExtendedVec3ToVector3(_controller->getPosition());
		m.setArg<Vector3>("controllerPosition", Vector3(senderPosition.x, senderPosition.y, receiverPosition.z));

		message.getArg<CEntity*>("receiver")->emitMessage(m);
		break;
	case Message::RECEIVE_PHYSIC_STATE:
		std::cout << "Recibiendo estado..." << std::endl;
		_movement = message.getArg<Vector3>("movement");
		_falling = message.getArg<bool>("falling");
		_controller->setPosition(Physics::Vector3ToPxExtendedVec3(message.getArg<Vector3>("controllerPosition")));
		break;
	}

} 

//---------------------------------------------------------

void CPhysicController::tick(unsigned int msecs) 
{
	// Llamar al método de la clase padre (IMPORTANTE).
	IComponent::tick(msecs);

	// Actualizar la posición y orientación de la entidad lógica usando la 
	// información proporcionada por el motor de física	
	_entity->setPosition(_server->getControllerPosition(_controller), this);

	// Si estamos cayendo modificar el vector de desplazamiento para simular el 
	// efecto de la gravedad. Lo hacemos de manera sencilla y pero poco realista.
	//_movement += msecs * Vector3(0.0f, -1.0f, 0.0f);

	// Intentamos mover el controller a la posición recibida en el último mensaje 
	// de tipo AVATAR_WALK. 
	unsigned flags = _server->moveController(_controller, _movement, msecs);

	// Actualizamos el flag que indica si estamos cayendo
	_falling =  !(flags & PxControllerFlag::eCOLLISION_DOWN);

	if (flags & PxControllerFlag::eCOLLISION_UP)
	{
		CAvatarController* controller = (CAvatarController*)(_entity->getComponent("CAvatarController"));
		controller->_jump = false;
		controller->_currentHeight = 0.0f;
	}

	// Ponemos el movimiento a cero
	_movement = Vector3::ZERO;
}

//---------------------------------------------------------

PxCapsuleController* CPhysicController::createController(const Map::CEntity *entityInfo)
{
	// Obtenemos la posición de la entidad. Inicialmente colocaremos el controller
	// un poco por encima del suelo, porque si lo ponemos justo en el suelo a veces
	// lo atraviesa en el primer ciclo de simulación.
	Vector3 position = _entity->getPosition() + Vector3(0, 0.5f, 0);
	
	// Leer el volumen de colisión del controller. Por ahora sólo admitimos cápsulas.
	std::string shape = "capsule";
	if (entityInfo->hasAttribute("physic_shape")) {
		shape = entityInfo->getStringAttribute("physic_shape");
		assert(shape == "capsule");
	}

	// Leer el radio de la cápsula
	assert(entityInfo->hasAttribute("physic_radius"));
	float radius = entityInfo->getFloatAttribute("physic_radius");

	// Leer la altura de la cápsula
	assert(entityInfo->hasAttribute("physic_height"));
	float height = entityInfo->getFloatAttribute("physic_height");

	// Crear el controller de tipo cápsula
	return _server->createCapsuleController(position, radius, height, this);
} 

//---------------------------------------------------------

void CPhysicController::onTrigger(IPhysics *otherComponent, bool enter)
{

}

//---------------------------------------------------------

void CPhysicController::onShapeHit (const PxControllerShapeHit &hit)
{
	// Si chocamos contra una entidad estática no hacemos nada
	PxRigidDynamic* actor = hit.shape->getActor()->isRigidDynamic();

	if(!actor)
		return;

	// Si chocamos contra una entidad cinemática mandamos
	// un mensaje a la entidad contra la que nos hemos
	// chocado
	if (_server->isKinematic(actor)){
		IPhysics *otherComponent = (IPhysics *)actor->userData;

		TMessage msg;
		msg._type = Message::SHAPE_HIT;
		otherComponent->getEntity()->emitMessage(msg);
		return;
	}
	
	// Aplicar una fuerza a la entidad en la dirección del movimiento
	actor->addForce(hit.dir * hit.length * 1000.0f);
}

//---------------------------------------------------------

void CPhysicController::onControllerHit (const PxControllersHit &hit)
{

}
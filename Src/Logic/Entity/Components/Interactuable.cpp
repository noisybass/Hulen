#include "Interactuable.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/GameObject.h"
#include "Map/MapEntity.h"
#include "Logic/Entity/Components/Graphics.h"
#include "Logic/Entity/Components/PhysicEntity.h"

namespace Logic
{
	IMP_FACTORY(CInteractuable);

	CInteractuable::CInteractuable()
		: IComponent(), _canInteract(false), _radius(0.0f), _playerName(""), _player(nullptr)
	{

	} // Cinteractuable

	CInteractuable::~CInteractuable()
	{
		if (_player)
			_player = nullptr;

	} // ~CInteractuable

	bool CInteractuable::spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		assert(entityInfo->hasAttribute("player") && "Hay que especificar el atributo player");
		_playerName = entityInfo->getStringAttribute("player");

		if (entityInfo->hasAttribute("interactuable_area_radius")){
			_radius = entityInfo->getFloatAttribute("interactuable_area_radius");
		}

	} // spawn

	bool CInteractuable::activate()
	{
		_player = _entity->getGameObject()->getMap()->getGameObjectByName(_playerName);

		return true;

	} // activate

	void CInteractuable::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		CGraphics* graphics = (CGraphics*)(_entity->getComponent("CGraphics"));

		float dist = _entity->getPosition().squaredDistance(_player->getPosition());
		//std::cout << dist << std::endl;
		if (dist < _radius*_radius)
		{
			_canInteract = true;
			graphics->setMaterial("Blue");
		}
		else
		{
			_canInteract = false;
			graphics->setMaterial("Purple");
		}

	} // tick

	bool CInteractuable::accept(const TMessage &message)
	{
		//std::cout << "Message type: " << message._type << std::endl;
		return message._type == Message::TOUCHED ||
			message._type == Message::UNTOUCHED;

	} // accept

	void CInteractuable::process(const TMessage &message)
	{
		CEntity* other;
		switch (message._type)
		{
		case Message::TOUCHED:
		case Message::UNTOUCHED:
			other = message.getArg<CEntity*>("entity");
			if (!(other->getBlueprint().compare("World")))
				_entity->removeComponent("CPhysicEntity");
			break;
		default:
			break;
		}

	} // process

} // namespace Logic
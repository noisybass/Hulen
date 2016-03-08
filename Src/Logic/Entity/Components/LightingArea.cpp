#include "LightingArea.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/GameObject.h"
#include "Map/MapEntity.h"
#include "Logic/Entity/Components/PointLight.h"

namespace Logic
{
	IMP_FACTORY(CLightingArea);

	CLightingArea::CLightingArea() 
		: IComponent(), _playerInside(false), _radius(0.0f), _playerName(""), _player(nullptr)
	{

	} // CLightingArea

	CLightingArea::~CLightingArea()
	{
		if (_player)
			_player = nullptr;

	} // ~CLightingArea

	bool CLightingArea::spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;

		assert(entityInfo->hasAttribute("player") && "Hay que especificar el atributo player");
		_playerName = entityInfo->getStringAttribute("player");

		if (entityInfo->hasAttribute("lighting_area_radius")){
			_radius = entityInfo->getFloatAttribute("lighting_area_radius");
		}

	} // spawn

	bool CLightingArea::activate()
	{
		_player = _entity->getGameObject()->getMap()->getGameObjectByName(_playerName);

		return true;

	} // activate

	void CLightingArea::tick(unsigned int msecs)
	{
		CPointLight* light = (CPointLight*)(_entity->getComponent("CPointLight"));

		float dist = _entity->getPosition().squaredDistance(_player->getPosition());
		if (dist < _radius*_radius)
		{
			_playerInside = true;
			light->setColor(Vector3(0, 1, 0));
		}
		else
		{
			_playerInside = false;
			light->setColor(Vector3(1, 0, 0));
		}
	} // tick

} // namespace Logic
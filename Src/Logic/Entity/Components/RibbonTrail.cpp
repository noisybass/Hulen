
#include "RibbonTrail.h"

#include "Graphics/Server.h"
#include "Graphics/RibbonTrail.h"

namespace Logic
{
	IMP_FACTORY(CRibbonTrail);

	CRibbonTrail::CRibbonTrail() : IComponent(), _ribbonMaterial(""), _ribbonLenght(0.0f),
		_ribbonMaxChain(0.0f), _initialRGB{ Vector3::ZERO }, _initialAlpha(0.0f), _changeRGB{Vector3::ZERO},
		_changeAlpha(0.0f), _initialWidht(0.0f), _fadedTime(0.0f)
	{}

	CRibbonTrail::~CRibbonTrail()
	{
		_scene->removeRibbonTrail(_ribbonTrail);
	}

	bool CRibbonTrail::spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo)
	{
		if (!IComponent::spawn(name, entity, map, entityInfo))
			return false;
		 
		if (entityInfo->hasAttribute("ribbonTrail_material"))
			_ribbonMaterial = entityInfo->getStringAttribute("ribbonTrail_material");

		if (entityInfo->hasAttribute("ribbonTrail_lenght"))
			_ribbonLenght = entityInfo->getFloatAttribute("ribbonTrail_lenght");
		
		if (entityInfo->hasAttribute("ribbonTrail_maxChainElements"))
			_ribbonMaxChain = entityInfo->getFloatAttribute("ribbonTrail_maxChainElements");

		if (entityInfo->hasAttribute("ribbonTrail_initialRGBColor"))
			_initialRGB = entityInfo->getVector3Attribute("ribbonTrail_initialRGBColor");

		if (entityInfo->hasAttribute("ribbonTrail_initialAlphaColor"))
			_initialAlpha = entityInfo->getFloatAttribute("ribbonTrail_initialAlphaColor");

		if (entityInfo->hasAttribute("ribbonTrail_ChangeRGBColor"))
			_changeRGB = entityInfo->getVector3Attribute("ribbonTrail_ChangeRGBColor");

		if (entityInfo->hasAttribute("ribbonTrail_ChangelAlphaColor"))
			_changeAlpha = entityInfo->getFloatAttribute("ribbonTrail_ChangelAlphaColor");

		if (entityInfo->hasAttribute("ribbonTrail_initialWidth"))
			_initialWidht = entityInfo->getFloatAttribute("ribbonTrail_initialWidth");

		if (entityInfo->hasAttribute("ribbonTrail_fadedTime"))
			_fadedTime = entityInfo->getFloatAttribute("ribbonTrail_fadedTime");
			

		_scene = _entity->getGameObject()->getMap()->getScene();

		_ribbonTrail = new Graphics::CRibbonTrail(_entity->getName());
		_scene->addRibbonTrail(_ribbonTrail);
		_ribbonTrail->init(_entity->getNode(), _ribbonMaterial, _ribbonLenght, _ribbonMaxChain,
							_initialRGB, _initialAlpha, _changeRGB, _changeAlpha, _initialWidht, _fadedTime);

		return true;
	} // spawn

	bool CRibbonTrail::accept(const TMessage &message)
	{

		return false;
	} // accept

	void CRibbonTrail::process(const TMessage &message)
	{
		
	} // process
}
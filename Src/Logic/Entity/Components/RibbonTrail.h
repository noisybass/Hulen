#ifndef LOGIC_RIBBONTRAIL_H
#define LOGIC_RIBBONTRAIL_H

#include "Logic/Entity/Component.h"


namespace Logic 
{

	class CRibbonTrail : public IComponent
	{
		DEC_FACTORY(CRibbonTrail);
	public:

		
		CRibbonTrail();


		virtual ~CRibbonTrail();


		virtual bool spawn(const std::string& name, CEntity* entity, CMap *map, const Map::CEntity *entityInfo);


		virtual bool accept(const TMessage &message);


		virtual void process(const TMessage &message);


	protected:

		/**
		Ribbon Attributtes
		*/
		std::string _ribbonMaterial;
		float _ribbonLenght;
		float _ribbonMaxChain;
		Vector3 _initialRGB;
		float _initialAlpha;
		Vector3 _changeRGB;
		float _changeAlpha;
		float _initialWidht;
		float _fadedTime;

		Graphics::CRibbonTrail* _ribbonTrail;
		Graphics::CScene* _scene;
		
	}; // class CRibbonTrail

	REG_FACTORY(CRibbonTrail);

} // namespace Logic

#endif // LOGIC_RIBBONTRAIL_H

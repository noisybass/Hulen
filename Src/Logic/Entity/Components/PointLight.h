#ifndef LOGIC_POINT_LIGHT
#define LOGIC_POINT_LIGHT

#include "Logic\Entity\Component.h"
#include "Graphics\PointLight.h"
#include "Graphics\Scene.h"

namespace Logic
{

	class CPointLight : public IComponent
	{
		DEC_FACTORY(CPointLight);
	public:

		CPointLight();

		~CPointLight();

		bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo) override;

		bool accept(const TMessage &message) override;

		void process(const TMessage &message) override;

	protected:

		Graphics::CPointLight* _light;

		Graphics::CScene* _scene;

	}; // class CPointLight

	REG_FACTORY(CPointLight);

} // namespace Logic

#endif // LOGIC_POINT_LIGHT
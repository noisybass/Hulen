#ifndef LOGIC_POINT_LIGHT
#define LOGIC_POINT_LIGHT

#include "Logic\Entity\Component.h"
#include "Graphics\PointLight.h"
#include "Graphics\Scene.h"

namespace Logic
{
	/**
	Posible Bug a solucionar si nos molesta. Siempre que creamos una luz, al heredar de la
	clase Entity se crea un SceneNode nuevo, mas o menos esta situación:
			--------
			| ROOT |
			--------
			   |
			   Y
	---------------------------
	| Nodo que crea la Entity |
	---------------------------

	El problema esta en que para mover la luz y todas sus caracteristicas (PE: la llama que tiene la luz
	alrededor suya) he necesitado crear un SceneNode, pero no hay manera de acceder al nodo que crea
	la entity segun Galeon esta montado ahora. por lo que la situacion actual es esta.
			--------
			| ROOT |---------------------------------
			--------									|
				|									|
				Y									Y
	---------------------------             --------------------------
	| Nodo que crea la Entity |				| Nodo creado por la luz |
	---------------------------				--------------------------

	Tenemos dos nodos que se crean a partir de root, pero solo utilizamos uno, el de la Luz,
	el otro nodo es malgastar memoria a lo tonto... Pero lo dejo aquí documentado para que algún
	día se solucione.

	*/
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
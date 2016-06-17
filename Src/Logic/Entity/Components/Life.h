/**
@file Life.h

Contiene la declaración del componente que controla la vida de una entidad.

@see Logic::CLife
@see Logic::IComponent

@author David Llansó
@date Octubre, 2010
*/
#ifndef __Logic_Life_H
#define __Logic_Life_H

#include "Logic/Entity/Component.h"
#include "Graphics/Billboard.h"

//declaración de la clase
namespace Logic 
{
	class CLife : public IComponent
	{
		DEC_FACTORY(CLife);
	public:

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		CLife() : IComponent() {}

		~CLife();
		
		/**
		Inicialización del componente usando la descripción de la entidad que hay en 
		el fichero de mapa.
		*/
		bool spawn(const std::string& name, CGameObject* gameObject, CMap *map, const Map::CEntity *entityInfo) override;

		/**
		Este componente sólo acepta mensajes de tipo DAMAGED.
		*/
		virtual bool accept(const TMessage &message);

		/**
		Al recibir un mensaje de tipo DAMAGED la vida de la entidad disminuye.
		*/
		virtual void process(const TMessage &message);

		void setDeathTime(float time);

		void setVisible(bool visible);

	protected:
		Graphics::CScene* _scene;
		Graphics::CBillBoard* _billboard;

		Vector3 _position;
		Vector3 _color;
		float _width;
		float _height;
		std::string _materialName;
		float _deathTime;
		
	}; // class CLife

	REG_FACTORY(CLife);

} // namespace Logic

#endif // __Logic_Life_H

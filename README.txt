POR LA PARTE DE LA LOGICA:
--------------------------

-> Las entidades ya no tienen un id unico, ni el mapa. Estos campos los tiene ahora el game object

POR LA PARTE DE LA CARGA:
-------------------------

-> Ha hecho falta cambiar la EntityFactory, ya que como su nombre indica, sólo cargaba entidades XD.
Y necesitamos ser capaces de cargar entidades y game objects.
Al cargar una entidad le ponias todos sus componentes y la asignabas al mapa (función createEntity de EntityFactory). 
¿Problema? Ahora el mapa sólo tiene game objects, y los game objects las entidades. Por lo que las entidades ya no se 
añaden al mapa, sino a su game object, y el game object es el que se añade al mapa.

SOLUCION:
	- En map.txt debe aparecer siempre el game object antes que las entidades
	- Hay un nuevo campo en los objetos del map.txt que se llama "blueprint", equivale al antiguo "type"
	- Ahora "type" nos indica si ese objeto es un GameObject, o una Entity
	- Si es una entidad necesitaremos otro campo "game_object" con el nombre del GameObject que va a contenerla (similar a lo de los triggers)
	- Si es un GameObject (type = "GameObject") en EntityFactory::createEntity hacemos lo que haciamos antes con las entidades, lo creamos, 
	le añadimos los componentes y lo añadimos al mapa.
	- Si es una entidad (type = "Entity") creamos la entidad y le añadimos los componentes, pero no la añadimos al mapa, sino que buscamos en el
	mapa su GameObject (de ahi que necesitemos el campo "game_object") y la añadimos a él.

EJEMPLO DE COMO SERÍAN LOS FICHEROS

-> blueprints.txt

PlayerManager CPlayerManager
PlayerBody CAvatarController CAnimatedGraphics CPhysicController
PlayerShadow CAvatarController CAnimatedGraphics CPhysicController

* En realidad si PlayerBody y PlayerShadow son exactamente iguales podriamos tener un unico blueprint Player, pero por claridad pongo ambos

-> map.txt

Map = {
	PlayerManager = {
		type = "GameObject",
		blueprint = "PlayerManager",
		// Más campos necesarios...
	},
	PlayerBody = {
		type = "Entity",
		game_object = "PlayerManager",
		blueprint = "PlayerBody",
		// Más campos necesarios...
	},
	PlayerShadow = {
		type = "Entity",
		game_object = "PlayerManager",
		blueprint = "PlayerShadow",
		// Más campos necesarios...
	},
}
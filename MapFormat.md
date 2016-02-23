Vamos a poner como ejemplo una entidad cualquiera, básica, y que tenga cuerpo y sombra.

Lo primero que debe aparecer es la definición de su game object.

```lua
Entity_GO = {
	type = "GameObject",
	blueprint = "Empty",
	state = "Body",
},
```
* `type`: puede ser o bien _GameObject_, _Body_ o _Shadow_, en este caso _GameObject_.
* `blueprint`: el correspondiente en el _blueprints.txt_, en este caso _Empty_ para indicar que no tiene ningún componente.
* `state`: nos idica en que estado comienza la entidad, aunque luego puede cambiar durante la ejecución. Sus valores pueden ser _Body_, _Shadow_ o _Both_.

Lo siguiente que aparecerán serás las definiciones de su cuerpo y su sombra. El orden de éstas es indiferente.

```lua
Entity_Body = {
	type = "Body",
	blueprint = "Entity",
	game_object = "Entity_GO",
	position = {-27.8, -14.7, 1.5},
},

Entity_Shadow = {
	type = "Shadow",
	blueprint = "Entity",
	game_object = "Entity_GO",
	position = {-27.8, -14.7, -3.5},
},
```
* `type`: que en este caso es o _Body_ o _Shadow_, lo que corresponda.
* `blueprint`: al igual que para el game object, será el correspondiente en el _blueprints.txt_.
* `game_object`: nombre del game object al que va a pertener, **que tiene que estar declarado previamente, sino explotará**
* `position`: toda entidad, ya sea _Body_ o _Shadow_, necesita una posición obligatoriamente.


En el caso de sólo tener cuerpo o sombra simplemente omitiríamos la declaración de la entidad correspondiente en el código de arriba. Es decir, para una entidad con sólo cuerpo sólo tendríamos el Entity_Body, y para una con sólo sombra el Entity_Shadow, y se declararían exactamente igual que en el ejemplo.
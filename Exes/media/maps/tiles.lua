Map_GO = {

	Camera_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

	World0_GO = {
		type = "GameObject",
		prefab = "World_Prefab",
	},

	World1_GO = {
		type = "GameObject",
		prefab = "World_Prefab",
	},

	World2_GO = {
		type = "GameObject",
		prefab = "World_Prefab",
	},

	World3_GO = {
		type = "GameObject",
		prefab = "World_Prefab",
	},

	World4_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body"
	},

	Tile1_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body"
	},
	Tile2_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body"
	},
	Tile3_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body"
	},
	Tile4_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body"
	},
	Tile5_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body"
	},
	Tile6_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body"
	},
}

Map = {

	Camera = {
		type = "Body",
		blueprint = "Camera",
		game_object = "Camera_GO",
		position = {0, 0, 30},
		fixed = true,
		ratio = 169,
		fov = 60,
	},

	World0 = {
		type = "Body",
		game_object = "World0_GO",
		prefab = "World_Prefab",
		position = {30, 0, 0},
		scale = {1, 35, 10},
		physic_dimensions = { 1, 35, 10 },
	},
		

	World1 = {
		type = "Body",
		blueprint = "DeathPlane",
		game_object = "World1_GO",
		position = {0, -25, 0},
		model = "Cube.mesh",
		physic_entity = "rigid",
		physic_type = "static",
		physic_trigger = true,
		physic_shape = "box",
		scale = {60, 1, 10},
		physic_dimensions = { 65, 1, 10 },
	},

	World2 = {
		type = "Body",
		game_object = "World2_GO",
		prefab = "World_Prefab",
		position = {0, 17, 0},
		scale = {60, 1, 10},
		physic_dimensions = { 65, 1, 10 },
	},

	World3 = {
		type = "Body",
		game_object = "World3_GO",
		prefab = "World_Prefab",
		position = {-30, 0, 0},
		scale = {1, 35, 10},
		physic_dimensions = { 1, 35, 10 },
	},

	World4 = {
		type = "Body",
		blueprint = "Background",
		game_object = "World4_GO",
		position = {0, 0, -3.5},
		model = "Plane.mesh",
		material = "Rocky",
	},

	Tile1 = {
		type = "Body",
		blueprint = "World",
		game_object = "Tile1_GO",
		position = {-10, -10, 0},
		scale = {0.5, 0.5, 0.5},
		model = "floor1.mesh",
		material = "TexturaFloor",
		physic_entity = "rigid",
		physic_type = "static",
		physic_shape = "box",
		physic_dimensions = {0.4, 0.4, 0.4},
	},

	Tile2 = {
		type = "Body",
		blueprint = "World",
		game_object = "Tile2_GO",
		position = {0, -10, 0},
		scale = {0.5, 0.5, 0.5},
		model = "floor2.mesh",
		material = "TexturaFloor",
		physic_entity = "rigid",
		physic_type = "static",
		physic_shape = "box",
		physic_dimensions = {0.4, 0.4, 0.4},
	},

	Tile3 = {
		type = "Body",
		blueprint = "World",
		game_object = "Tile3_GO",
		position = {10, -10, 0},
		scale = {0.5, 0.5, 0.5},
		model = "floor3.mesh",
		material = "TexturaFloor",
		physic_entity = "rigid",
		physic_type = "static",
		physic_shape = "box",
		physic_dimensions = {0.4, 0.4, 0.4},
	},

	Tile4 = {
		type = "Body",
		blueprint = "World",
		game_object = "Tile4_GO",
		position = {-10, 10, 0},
		scale = {0.5, 0.5, 0.5},
		model = "floor4.mesh",
		material = "TexturaFloor",
		physic_entity = "rigid",
		physic_type = "static",
		physic_shape = "box",
		physic_dimensions = {0.4, 0.4, 0.4},
	},

	Tile5 = {
		type = "Body",
		blueprint = "World",
		game_object = "Tile5_GO",
		position = {0, 10, 0},
		scale = {0.5, 0.5, 0.5},
		model = "floor5.mesh",
		material = "TexturaFloor",
		physic_entity = "rigid",
		physic_type = "static",
		physic_shape = "box",
		physic_dimensions = {0.4, 0.4, 0.4},
	},

	Tile6 = {
		type = "Body",
		blueprint = "World",
		game_object = "Tile6_GO",
		position = {10, 10, 0},
		scale = {0.5, 0.5, 0.5},
		model = "floor6.mesh",
		material = "TexturaFloor",
		physic_entity = "rigid",
		physic_type = "static",
		physic_shape = "box",
		physic_dimensions = {0.4, 0.4, 0.4},
	},

}
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

	Kasai_GO = {
		type = "GameObject",
		blueprint = "Empty",
		isLight = true,
		state = "Body",
	},

	Player_GO = {
		type = "GameObject",
		blueprint = "Player_GO",
		isPlayer = true,
		state = "Body",
		playerDeathTime = 3,
		playerCanDie = false,
		kasai = "Kasai_GO",
		charge = "Charge_Prefab",
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
		material = "perPixel",
	},

	Tile1 = {
		type = "Body",
		blueprint = "World",
		game_object = "Tile1_GO",
		position = {-10, -10, 0},
		model = "floor1.mesh",
		material = "perPixel",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	},

	Tile1_Shadow = {
		type = "Shadow",
		blueprint = "World",
		game_object = "Tile1_GO",
		position = {-10, -10, -3.4},
		model = "floor1.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	},

	Tile2 = {
		type = "Body",
		blueprint = "World",
		game_object = "Tile2_GO",
		position = {0, -10, 0},
		model = "floor2.mesh",
		material = "perPixel",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor2.RepX",
	},

	Tile3 = {
		type = "Body",
		blueprint = "World",
		game_object = "Tile3_GO",
		position = {10, -10, 0},
		model = "floor3.mesh",
		material = "perPixel",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor3.RepX",
	},

	Tile4 = {
		type = "Body",
		blueprint = "World",
		game_object = "Tile4_GO",
		position = {-10, 10, 0},
		model = "floor4.mesh",
		material = "perPixel",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor4.RepX",
	},

	Tile5 = {
		type = "Body",
		blueprint = "World",
		game_object = "Tile5_GO",
		position = {0, 10, 0},
		model = "floor5.mesh",
		material = "perPixel",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor5.RepX",
	},

	Tile6 = {
		type = "Body",
		blueprint = "World",
		game_object = "Tile6_GO",
		position = {10, 10, 0},
		model = "floor6.mesh",
		material = "perPixel",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor6.RepX",
	},

	Kasai = {
		type = "Body",
		blueprint = "Kasai",
		game_object = "Kasai_GO",
		position = {0,0,0},
		light_position = {0,0,0},
		specular_colour = {1,1,1},
		diffuse_colour = {1,1,1},
		--flare_material = "Flare",
		--flare_colour = {1,1,1},
		--flare_size = 10,
		light_attenuation_range = 6.5,
		light_attenuation_constant = 1.0,
		light_attenuation_linear = 0.2,
		light_attenuation_quadratic = 0.05,
		player = "Player_GO",
		lighting_area_radius = 6.5,
		graphicChargeVelocity = 8,
		graphicChargeRadius = 3,
	},

	Player_Body = {
		type = "Body",
		blueprint = "Player",
		game_object = "Player_GO",
		position = {0, 0, 0},
		scale = {0.3, 0.3, 0.3},
		--model = "marine.mesh",
		model = "Test_Main_character.mesh",
		material = "Yellow",
		--defaultAnimation = "Idle",
		defaultAnimation = "Idle_cycle_1",
		walkRightAnimation = "Walking_cycle",
		idleAnimation = "Idle_cycle_1",
		--fadeInOut_Velocity = 5,
		physic_shape = "capsule",
		physic_radius = 1,
		physic_height = 1,
		guizmo = false,
		guizmoSize = 10,
		speed = 10,
		jump_speed = 30,
		jump_height = 8.0,
		gravity = 15,
		defaultVision = 5,
	},

	Player_Shadow = {
		type = "Shadow",
		blueprint = "Player",
		game_object = "Player_GO",
		position = {0, 0, -3.5},
		scale = {0.2, 0.2, 0.2},
		--model = "marine.mesh",
		model = "Test_Main_character.mesh",
		material = "Black",
		--defaultAnimation = "Idle",
		defaultAnimation = "Idle_cycle_1",
		walkRightAnimation = "Walking_cycle",
		idleAnimation = "Idle_cycle_1",
		--fadeInOut_Velocity = 5,
		physic_shape = "capsule",
		physic_radius = 1,
		physic_height = 1,
		guizmo = false,
		guizmoSize = 10,
		speed = 10,
		jump_speed = 30,
		jump_height = 8.0,
		gravity = 15,
	},
}
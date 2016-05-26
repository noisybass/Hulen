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
		pickObjectAnimation = "pick_object",
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
		--prefab = "World_Prefab",
		--position = {30, 0, 0},
		--scale = {1, 35, 10},
		--physic_dimensions = { 1, 35, 10 },

		blueprint = "Background",
		position = {30, 0, 0},
		-- Graphic Entity
		--model = "Plane.mesh",
		graphic_file = false,
		graphic_type = "plane",
		graphic_up_vector = {-1, 0, 0},
		graphic_parallel_vector = {0, 1, 0},
		graphic_width = 10,
		graphic_height = 50,
		material = "Wall",
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
		--prefab = "World_Prefab",
		--position = {0, 17, 0},
		--scale = {60, 1, 10},
		--physic_dimensions = { 65, 1, 10 },

		blueprint = "Background",
		position = {0, 17, 0},
		-- Graphic Entity
		--model = "Plane.mesh",
		graphic_file = false,
		graphic_type = "plane",
		graphic_up_vector = {0, -1, 0},
		graphic_parallel_vector = {1, 0, 0},
		graphic_width = 10,
		graphic_height = 60,
		material = "Wall",
	},

	World3 = {
		type = "Body",
		game_object = "World3_GO",
		--prefab = "World_Prefab",
		--position = {-30, 0, 0},
		--scale = {1, 35, 10},
		--physic_dimensions = { 1, 35, 10 },

		blueprint = "Background",
		position = {-30, 0, 0},
		-- Graphic Entity
		--model = "Plane.mesh",
		graphic_file = false,
		graphic_type = "plane",
		graphic_up_vector = {1, 0, 0},
		graphic_parallel_vector = {0, 1, 0},
		graphic_width = 10,
		graphic_height = 50,
		material = "Wall",
	},

	World4 = {
		type = "Body",
		blueprint = "Background",
		game_object = "World4_GO",
		position = {0, 0, -1.5},
		-- Graphic Entity
		--model = "Plane.mesh",
		graphic_file = false,
		graphic_type = "plane",
		graphic_up_vector = {0, 0, 1},
		graphic_parallel_vector = {0, 1, 0},
		graphic_width = 65,
		graphic_height = 50,
		material = "Wall",
	},

	Tile1 = {
		type = "Body",
		blueprint = "World",
		game_object = "Tile1_GO",
		position = {-3.5, -10.1, 0},
		model = "floor1.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	},

	Tile2 = {
		type = "Body",
		blueprint = "World",
		game_object = "Tile2_GO",
		position = {0, -9.9, 0},
		model = "floor2.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor2.RepX",
	},

	Tile3 = {
		type = "Body",
		blueprint = "World",
		game_object = "Tile3_GO",
		position = {3.5, -10, 0},
		model = "floor3.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor3.RepX",
	},

	Tile4 = {
		type = "Body",
		blueprint = "World",
		game_object = "Tile4_GO",
		position = {7, -9.9, 0},
		model = "floor4.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor4.RepX",
	},

	Tile5 = {
		type = "Body",
		blueprint = "World",
		game_object = "Tile5_GO",
		position = {-7, -9.9, 0},
		model = "floor5.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor5.RepX",
	},

	Tile6 = {
		type = "Body",
		blueprint = "World",
		game_object = "Tile6_GO",
		position = {7.5, -5.8, 0},
		model = "wall1.mesh",
		material = "Floor",
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
		graphicChargeVelocity = 5.5,
		graphicChargeRadius = 3,
		graphicChargeRotationBar = 0.2,
		graphicChargesDeltaSeparation = 0.15,
		graphicChargesDeltaSeparationToFirstCharge = 0.85,
	},

	Player_Body = {
		type = "Body",
		blueprint = "Player",
		game_object = "Player_GO",
		position = {0, 0, 0},
		scale = {4, 4, 4},
		--model = "marine.mesh",
		model = "Main_character.mesh",
		material = "Player",
		physic_shape = "capsule",
		physic_radius = 1,
		physic_height = 1,
		guizmo = false,
		guizmoSize = 10,
		speed = 10,
		jump_speed = 20,
		jump_height = 8,
		gravity = 8,
		defaultVision = 5,

		--Animations
		defaultAnimation = "idle_cycle_1",
		defaultAnimationVelocity = 5,
		idle1Animation = { "idle_cycle_1", 1, "null"},
		idle2Animation = { "idle_cycle_2", 1, "null"},
		walkAnimation  = { "Walking_cycle", 1, "null"},
		runAnimation   = { "Running_cycle", 1, "null"},
		deathAnimation = { "death", 1, "null"},
		delayinitJump  = 0.3,
		jump1Animation = { "Jump_movement", 2, "null"},
		fall1Animation = { "fall", 2, "null"},
		land1Animation = { "landing", 4.5 , "null"},
		--jump2Animation = { "", 2, "null"},
		--fall2Animation = { "", 2, "null"},
		--land2Animation = { "", 2, "null"},
		pickObjectAnimation = { "pick_object",1, "null"},

		--Blending
		defaultBlendingVelocity = 5,
		idle1Blending = { "idle_cycle_1", 2, "null"},
		idle2Blending = { "idle_cycle_2", 2, "null"},
		walkBlending  = { "Walking_cycle", 5, "null"},
		runBlending   = { "Running_cycle", 2, "null"},
		deathBlending = { "death", 2, "null"},
		jump1Blending = { "Jump_movement", 2, "null"},
		fall1Blending = { "fall", 2, "null"},
		land1Blending = { "landing", 2, "null"},
		--jump2Blending = { "", 2, "null"},
		--fall2Blending = { "", 2, "null"},
		--land2Blending = { "", 2, "null"},
		pickObjectBlending = { "pick_object", 2, "null"},
	},

	Player_Shadow = {
		type = "Shadow",
		blueprint = "Player",
		game_object = "Player_GO",
		position = {0, 0, -3.5},
		scale = {4, 4, 4},
		--model = "marine.mesh",
		model = "Main_character.mesh",
		material = "Black",
		physic_shape = "capsule",
		physic_radius = 1,
		physic_height = 1,
		guizmo = false,
		guizmoSize = 10,
		speed = 10,
		jump_speed = 30,
		jump_height = 8.0,
		gravity = 15,

		---Animations
		defaultAnimation = "idle_cycle_1",
		defaultAnimationVelocity = 5,
		idle1Animation = { "idle_cycle_1", 1, "null"},
		idle2Animation = { "idle_cycle_2", 1, "null"},
		walkAnimation  = { "Walking_cycle", 1, "null"},
		runAnimation   = { "Running_cycle", 1, "null"},
		deathAnimation = { "death", 1, "null"},
		jump1Animation = { "Jump_movement", 1, "null"},
		fall1Animation = { "fall", 1, "null"},
		land1Animation = { "landing", 1, "null"},
		--jump2Animation = { "", 2, "null"},
		--fall2Animation = { "", 2, "null"},
		--land2Animation = { "", 2, "null"},
		pickObjectAnimation = { "pick_object",1, "null"},

		--Blending
		defaultBlendingVelocity = 5,
		idle1Blending = { "idle_cycle_1", 2, "null"},
		idle2Blending = { "idle_cycle_2", 2, "null"},
		walkBlending  = { "Walking_cycle", 5, "null"},
		runBlending   = { "Running_cycle", 2, "null"},
		deathBlending = { "death", 2, "null"},
		jump1Blending = { "Jump_movement", 2, "null"},
		fall1Blending = { "fall", 2, "null"},
		land1Blending = { "landing", 2, "null"},
		--jump2Blending = { "", 2, "null"},
		--fall2Blending = { "", 2, "null"},
		--land2Blending = { "", 2, "null"},
		pickObjectBlending = { "pick_object", 2, "null"},
	},
}
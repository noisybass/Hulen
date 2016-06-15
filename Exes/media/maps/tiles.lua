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

	Spike1_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

	Spike2_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
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
		playerCanDie = true,
		chargesOwned = 0,
		kasai = "Kasai_GO",
		charge = "Charge_Prefab",
		pickObjectAnimation = "pick_object",

		-- Life Bar
		billboard_position = {-25,16,0},
		billboard_color    = {1,1,1},
		billboard_width    = 10,
		billboard_height   = 1,
		billboard_material = "LifeBar",
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
		blueprint = "Background",
		game_object = "World3_GO",
		position = {0, 0, -4},
		graphic_file = false,
		graphic_type = "plane",
		graphic_up_vector = {0, 0, 1},
		graphic_parallel_vector = {0, 1, 0},
		graphic_width = 72,
		graphic_height = 40.8,
		graphic_uTile = 1,
		graphic_vTile = 1,
		material = "Sublevel1",
	},

	World4 = {
		type = "Body",
		blueprint = "Background",
		game_object = "World4_GO",
		position = {0, 0, -2.6},
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
		position = {7.18, -10.09, -0.04},
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
		position = {3.59, -9.85, -0.04},
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
		position = {0, -10, 0},
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
		position = {-3.59, -9.86, -0.02},
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
		position = {-7.18, -9.85, 0},
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
		position = {-10.77, -10.1, -0.01},
		model = "wall1.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor6.RepX",
	},

	Spike1 = {
		type = "Body",
		blueprint = "Spike",
		game_object = "Spike1_GO",
		position = {-2.77, -5.1, -0.01},
		model = "spike1.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/spike1.RepX",
	},

	Spike2 = {
		type = "Body",
		blueprint = "Spike",
		game_object = "Spike2_GO",
		position = {-5.77, -5.1, -0.01},
		model = "spike2.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/spike2.RepX",
	},

	Kasai = {
		type = "Body",
		blueprint = "Kasai",
		game_object = "Kasai_GO",
		position = {0, 0, 0},
		diffuse_colour = {0.75, 0.6, 0.25},
		model = "Sphere.mesh",
		scale = {0.75, 0.75, 0.75},
		material = "Charge_on",
		light_attenuation_range = 9,
		light_attenuation_constant = 0,
		light_attenuation_linear = 0,
		light_attenuation_quadratic = 0,
		player = "Player_GO",
		lighting_area_radius = 9,

		-- Graphic Charge
		graphicChargeVelocity = 5.5,
		thrownChargeVelocity = 10,
		graphicChargeRadius = 3,
		graphicChargeRotationBar = 0.2,
		graphicChargesDeltaSeparation = 0.15,
		graphicChargesDeltaSeparationToFirstCharge = 0.85,

		-- Ribbon Trail
		ribbonTrail_material          = "LightRibbonTrail",
		ribbonTrail_lenght            = 500,
		ribbonTrail_maxChainElements  = 500,
		ribbonTrail_initialRGBColor   = {1.0,1.0,1.0},
		ribbonTrail_initialAlphaColor = 1,
		ribbonTrail_ChangeRGBColor    = {0.5,0.5,0.5},
		ribbonTrail_ChangelAlphaColor = 0.5,
		ribbonTrail_initialWidth      = 1,
		ribbonTrail_fadedTime         = 0.4,
	},

	Player_Body = {
		type = "Body",
		blueprint = "Player",
		game_object = "Player_GO",
		position = {0, 0, 0.1},
		scale = {4, 4, 4},
		--model = "marine.mesh",
		model = "Main_character.mesh",
		material = "Player",
		physic_shape = "capsule",
		physic_radius = 1,
		physic_height = 1,
		guizmo = false,
		guizmoSize = 10,
		defaultVision = 5,

		-- Sounds
		walkSound = "PrisonerWalk",
		walkVolume = 0.8,
		walkPitch = 1.65,

		jumpSound = "PrisonerJump",
		jumpVolume = 0.3, 
		jumpPitch = 1,

		landSound = "PrisonerLand",
		landVolume = 0.3,
		landPitch = 1,

		-- Avatar controller
		speed = 10,
		jump_speed = 20,
		jump_height = 8,
		gravity = 8,
		

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
		position = {-27.8, -13.5, -3.5},
		scale = {4, 4, 4},
		--model = "marine.mesh",
		model = "Main_character.mesh",
		material = "Black",
		physic_shape = "capsule",
		physic_radius = 1,
		physic_height = 1,
		guizmo = false,
		guizmoSize = 10,

		-- Avatar controller
		speed = 10,
		jump_speed = 20,
		jump_height = 8,
		gravity = 8,

		-- Sounds
		walkSound = "PrisonerShadowWalk",
		walkVolume = 0.8,
		walkPitch = 1.65,

		jumpSound = "PrisonerShadowJump",
		jumpVolume = 0.3, 
		jumpPitch = 1,

		landSound = "PrisonerShadowLand",
		landVolume = 0.3,
		landPitch = 1,

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
}
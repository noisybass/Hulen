Map_GO = {

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


	Kasai_GO = {
		type = "GameObject",
		blueprint = "Empty",
		isLight = true,
		state = "Body",
	},

	Camera_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

	
}

Map = {
	
	Player_Body = {
		type = "Body",
		blueprint = "Player",
		game_object = "Player_GO",
		position = {-27.8, 0, 0.1},
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
		position = {-27.8, 0, -3.5},
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

	Kasai = {
		type = "Body",
		blueprint = "Kasai",
		game_object = "Kasai_GO",
		position = {0,0,0},
		light_position = {0,0,0},
		specular_colour = {1,1,1},
		diffuse_colour = {1,1,1},
		model = "Sphere.mesh",
		scale = {0.75, 0.75, 0.75},
		material = "Charge_on",
		--flare_material = "Flare",
		--flare_colour = {1,1,1},
		--flare_size = 10,
		light_attenuation_range = 6.5,
		light_attenuation_constant = 1.0,
		light_attenuation_linear = 0.2,
		light_attenuation_quadratic = 0.05,
		player = "Player_GO",
		lighting_area_radius = 6.5,

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

	Camera = {
		type = "Body",
		blueprint = "Camera",
		game_object = "Camera_GO",
		position = {0, 0, 30},
		fixed = true,
		ratio = 169,
		fov = 60,
	},
	
}
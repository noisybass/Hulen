 Map_GO = {

	Player_GO = { 
	type = "GameObject", 
	blueprint  = "Player_GO", 
	isPlayer = true, 
	state = "Body", 
	playerCanDie  = false ,
	playerDeathTime  = 3,
	kasai = "Kasai_GO",
	charge = "Charge_Prefab",
	}, 

	Kasai_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	isLight = true, 
	state = "Body", 
	}, 

	Camera_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	Spike0_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Shadow", 
	},

	Spike1_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Shadow", 
	},  

	Spike2_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Shadow", 
	}, 

	World0_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Both", 
	}, 

	World1_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Both", 
	}, 

	World2_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World3_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World4_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World5_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World6_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World7_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Both", 
	}, 

	World8_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Both", 
	}, 

	World9_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Both", 
	}, 

	World10_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Both", 
	}, 

	World11_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Both", 
	}, 

	World12_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Both", 
	}, 

	World13_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World14_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World15_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World16_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World17_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World18_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World19_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World20_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World21_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World22_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World23_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Shadow", 
	}, 

	World24_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Shadow", 
	}, 

	World25_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World26_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World27_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World28_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World29_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	}, 

	World30_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	},

	World31_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Body", 
	},

	World32_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Shadow", 
	},

	World33_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Shadow", 
	},

	World34_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Shadow", 
	},

	World35_GO = { 
	type = "GameObject", 
	blueprint  = "Empty", 
	state = "Shadow", 
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
		physic_radius = 0.8,
		physic_height = 1.7,
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
		position = {-27.8, 0, -2.4},
		scale = {4, 4, 4},
		--model = "marine.mesh",
		model = "Main_character.mesh",
		material = "Black",
		physic_shape = "capsule",
		physic_radius = 0.8,
		physic_height = 1.7,
		guizmo = false,
		guizmoSize = 10,
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

	Kasai_Body = { 
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
		light_attenuation_range = 7.5,
		light_attenuation_constant = 1.0,
		light_attenuation_linear = 0.2,
		light_attenuation_quadratic = 0.05,
		player = "Player_GO",
		lighting_area_radius = 7.5,
		graphicChargeVelocity = 5.5,
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

	Camera_Body = { 
	type = "Body", 
	blueprint  = "Camera", 
	game_object  = "Camera_GO", 
	position = {0, 0, 30}, 
	fixed = true, 
	ratio = 169, 
	fov = 60, 
	}, 

	Spike0 = { 
	type = "Shadow", 
	blueprint  = "Spike", 
	game_object  = "Spike0_GO", 
	position = {0, -13.71, -2.6}, 
	model = "Spike.mesh", 
	material = "Black", 
	static = true, 
	scale = { 1, 1, 1 }, 
	physic_entity = "fromFile", 
	physic_file = "media/models/Spike.RepX", 
	physic_group = 1, 
	}, 

	Spike1 = { 
	type = "Shadow", 
	blueprint  = "Spike", 
	game_object  = "Spike1_GO", 
	position = {-1.2, -13.71, -2.6}, 
	model = "Spike.mesh", 
	material = "Black", 
	static = true, 
	scale = { 1, 1, 1 }, 
	physic_entity = "fromFile", 
	physic_file = "media/models/Spike.RepX", 
	physic_group = 1, 
	},

	Spike2 = { 
	type = "Shadow", 
	blueprint  = "Spike", 
	game_object  = "Spike2_GO", 
	position = {1.2, -13.71, -2.6}, 
	model = "Spike.mesh", 
	material = "Black", 
	static = true, 
	scale = { 1, 1, 1 }, 
	physic_entity = "fromFile", 
	physic_file = "media/models/Spike.RepX", 
	physic_group = 1, 
	},  

	World0 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World0_GO", 
		position = {-28.39, -5.2, 0}, 
		model = "floor1.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	},

	World0_Shadow = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World0_GO", 
		position = {-28.39, -5.2, -2.6}, 
		model = "floor1.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	}, 

	World1 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World1_GO", 
		position = {-24.89, -4.95, 0}, 
		model = "floor2.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	}, 

	World1_Shadow = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World1_GO", 
		position = {-24.89, -4.95, -2.6}, 
		model = "floor2.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	},

	World32_Shadow = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World32_GO", 
		position = {-21.4, -4.95, -2.6}, 
		model = "floor2.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	},

	World33_Shadow = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World33_GO", 
		position = {-18.4, -4.95, -2.6}, 
		model = "floor2.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	},

	World34_Shadow = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World34_GO", 
		position = {-12.4, -10.95, -2.6}, 
		model = "floor2.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	},

	World35_Shadow = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World35_GO", 
		position = {-9.4, -10.95, -2.6}, 
		model = "floor2.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	},

	World2 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World2_GO", 
		position = {-16.08, -5.1, 0}, 
		model = "floor3.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	},

	World3 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World3_GO", 
		position = {-12.58, -4.95, 0}, 
		model = "floor4.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	},  

	World4 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World4_GO", 
		position = {-14.39, -5.1, 0}, 
		model = "floor5.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	}, 

	World5 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World5_GO", 
		position = {-10.89, -5.3, 0}, 
		model = "floor6.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	}, 

	World6 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World6_GO", 
		position = {-7.39, -5.3, 0}, 
		model = "floor1.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	}, 

	World7 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World7_GO", 
		position = {3.11, -5.05, 0}, 
		model = "floor2.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	},

	World7_Shadow = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World7_GO", 
		position = {3.11, -4.95, -2.6}, 
		model = "floor2.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	},  

	World8 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World8_GO", 
		position = {-0.39, -5.2, 0}, 
		model = "floor3.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX", 
	},

	World8_Shadow = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World8_GO", 
		position = {-0.39, -5.1, -2.6}, 
		model = "floor3.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX", 
	},  

	World9 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World9_GO", 
		position = {-3.89, -5.05, 0}, 
		model = "floor4.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	}, 

	World9_Shadow = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World9_GO", 
		position = {-3.89, -4.95, -2.6}, 
		model = "floor4.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	}, 

	World10 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World10_GO", 
		position = {6.61, -5.05, 0}, 
		model = "floor5.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX", 
	}, 

	World10_Shadow = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World10_GO", 
		position = {6.61, -4.95, -2.6}, 
		model = "floor5.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX", 
	}, 

	World11 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World11_GO", 
		position = {10.11, -5.3, 0}, 
		model = "floor6.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX", 
	}, 

	World11_Shadow = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World11_GO", 
		position = {10.11, -5.15, -2.6}, 
		model = "floor6.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX", 
	},

	World12 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World12_GO", 
		position = {13.61, -5.3, 0}, 
		model = "floor1.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	}, 

	World12_Shadow = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World12_GO", 
		position = {13.61, -5.2, -2.6}, 
		model = "floor1.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	}, 

	World13 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World13_GO", 
		position = {-21.12, -12.92, 0}, 
		model = "floor2.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	}, 

	World14 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World14_GO", 
		position = {-24.62, -13.05, 0}, 
		model = "floor3.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	}, 

	World15 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World15_GO", 
		position = {-17.62, -12.92, 0}, 
		model = "floor4.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	}, 

	World16 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World16_GO", 
		position = {-1.32, -15.15, 0}, 
		model = "floor5.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX", 
	}, 

	World16_Shadow = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World16_GO", 
		position = {-1.32, -15.15, -2.6}, 
		model = "floor5.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX", 
	},

	World17 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World17_GO", 
		position = {-8.32, -15.4, 0}, 
		model = "floor6.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	}, 

	World17_Shadow = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World17_GO", 
		position = {-8.32, -15.4, -2.6}, 
		model = "floor6.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	}, 

	World18 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World18_GO", 
		position = {-4.82, -15.4, 0}, 
		model = "floor1.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	},

	World18_Shadow = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World18_GO", 
		position = {-4.82, -15.4, -2.6}, 
		model = "floor1.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	}, 

	World19 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World19_GO", 
		position = {5.68, -15.15, 0}, 
		model = "floor2.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX", 
	}, 

	World19_Shadow = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World19_GO", 
		position = {5.68, -15.15, -2.6}, 
		model = "floor2.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX", 
	},

	World20 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World20_GO", 
		position = {2.18, -15.3, 0}, 
		model = "floor3.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	},

	World20_Shadow = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World20_GO", 
		position = {2.18, -15.3, -2.6}, 
		model = "floor3.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	},  

	World21 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World21_GO", 
		position = {9.18, -15.17, 0}, 
		model = "floor4.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX", 
	}, 

	World21_Shadow = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World21_GO", 
		position = {9.18, -15.17, -2.6}, 
		model = "floor4.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX", 
	},

	World22 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World22_GO", 
		position = {12.68, -15.17, 0}, 
		model = "floor5.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	}, 

	World22_Shadow = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World22_GO", 
		position = {12.68, -15.17, -2.6}, 
		model = "floor5.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	}, 

	World23 = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World23_GO", 
		position = {20.04, -13.82, -2.6}, 
		model = "floor6.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX", 
	}, 

	World24 = { 
		type = "Shadow", 
		blueprint  = "World", 
		game_object  = "World24_GO", 
		position = {23.54, -13.55, -0.5}, 
		model = "floor2.mesh",
		material = "Black",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	}, 

	World25 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World25_GO", 
		position = {28.63, -9.87, 0}, 
		model = "floor3.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor1.RepX",
	}, 

	World26 = { 
		type = "Body", 
		blueprint = "Background",
		game_object  = "World26_GO", 
		position = {-30, 0, 0}, 
		graphic_file = false,
		graphic_type = "plane",
		graphic_up_vector = {1, 0, 0},
		graphic_parallel_vector = {0, 1, 0},
		graphic_width = 10,
		graphic_height = 50,
		material = "Wall", 
	}, 

	World27 = { 
		type = "Body", 
		blueprint  = "World", 
		game_object  = "World27_GO", 
		position = {13.86, -1, 0}, 
		model = "wall1.mesh",
		material = "Floor",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/floor6.RepX",
	}, 

	World28 = { 
		type = "Body", 
		blueprint = "Background",
		game_object  = "World28_GO", 
		position = {30, 0, 0}, 
		graphic_file = false,
		graphic_type = "plane",
		graphic_up_vector = {-1, 0, 0},
		graphic_parallel_vector = {0, 1, 0},
		graphic_width = 10,
		graphic_height = 50,
		material = "Wall",
	}, 

	World29 = { 
		type = "Body", 
		blueprint = "Background",
		game_object  = "World29_GO", 
		position = {0, 17, 0}, 
		graphic_file = false,
		graphic_type = "plane",
		graphic_up_vector = {0, -1, 0},
		graphic_parallel_vector = {1, 0, 0},
		graphic_width = 10,
		graphic_height = 60,
		material = "Wall",
	}, 

	World30 = {
		type = "Body",
		blueprint = "Background",
		game_object = "World30_GO",
		position = {0, 0, -2.6},
		-- Graphic Entity
		graphic_file = false,
		graphic_type = "plane",
		graphic_up_vector = {0, 0, 1},
		graphic_parallel_vector = {0, 1, 0},
		graphic_width = 65,
		graphic_height = 50,
		material = "Wall",
	},

	World31 = {
		type = "Body",
		blueprint = "DeathPlane",
		game_object = "World31_GO",
		position = {0, -25, 0},
		model = "Cube.mesh",
		physic_entity = "rigid",
		physic_type = "static",
		physic_trigger = true,
		physic_shape = "box",
		scale = {60, 1, 10},
		physic_dimensions = { 65, 1, 10 },
	},
}

-- Generated with Version 0.6 of the Hulen Editor © 2016


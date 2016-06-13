Prefab_GO = {
	
	World_Prefab_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

	Charge_Prefab_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

	Spike_Prefab_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

	GraphicCharge_Prefab_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	}

}

Prefab = {
	
	World_Prefab_Body = {
		type = "Body",
		blueprint = "World",
		game_object = "World_Prefab_GO",
		model = "Cube.mesh",
		physic_entity = "rigid",
		physic_type = "static",
		physic_shape = "box",
		material = "White",
	},

	World_Prefab_Shadow = {
		type = "Shadow",
		blueprint = "World",
		game_object = "World_Prefab_GO",
		model = "Cube.mesh",
		physic_entity = "rigid",
		physic_type = "static",
		physic_shape = "box",
		material = "Black",
	},

	Spike_Prefab_Body = {
		type = "Body",
		blueprint = "Spike",
		game_object = "Spike_Prefab_GO",
		model = "Spike.mesh",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/Spike.RepX",
		physic_change_coords = true,
	},

	Spike_Prefab_Shadow = {
		type = "Shadow",
		blueprint = "Spike",
		game_object = "Spike_Prefab_GO",
		model = "Spike.mesh",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/Spike.RepX",
		physic_change_coords = true,
		material = "Black",
	},

	Charge_Prefab = {
		type = "Body",
		blueprint = "Charge",
		game_object = "Charge_Prefab_GO",
		model = "Sphere.mesh",
		scale = {0.5, 0.5, 0.5},
		diffuse_colour = {0.75, 0.6, 0.25},
		light_attenuation_range = 7,
		light_attenuation_constant = 0,
		light_attenuation_linear = 0,
		light_attenuation_quadratic = 0,
		player = "Player_GO",
		lighting_area_radius = 7,
		interactuable_area_radius = 3.0,
		physic_entity = "rigid",
		physic_type = "dynamic",
		physic_shape = "sphere",
		physic_trigger = false,
		physic_group = 2,
		physic_mass = 1,
		physic_radius = 0.1,

		-- Sounds
		chargeImpactSound = "ChargeImpact",
		chargeImpactVolume = 0.5,
		chargeImpactPicth = 1,
	},

	GraphicCharge_Prefab = {
		type = "Body",
		blueprint = "GraphicCharge",
		game_object = "GraphicCharge_Prefab_GO",
		model = "Sphere.mesh",
		scale = {0.5, 0.5, 0.5},
		--specular_colour = {1,1,1},
		--diffuse_colour = {1,1,1},
		material = "Charge_on",

		-- Ribbon Trail
		ribbonTrail_material          = "LightRibbonTrail",
		ribbonTrail_lenght            = 500,
		ribbonTrail_maxChainElements  = 500,
		ribbonTrail_initialRGBColor   = {1.0,1.0,1.0},
		ribbonTrail_initialAlphaColor = 1,
		ribbonTrail_ChangeRGBColor    = {0.5,0.5,0.5},
		ribbonTrail_ChangelAlphaColor = 0.5,
		ribbonTrail_initialWidth      = 1,
	}

}
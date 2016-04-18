Prefab_GO = {
	
	World_Prefab_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

	Kasai_Prefab_GO = {
		type = "GameObject",
		blueprint = "Empty",
		isLight = true,
		state = "Body",
	},

	Camera_Prefab_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

	Charge_Prefab_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

}

Prefab = {
	
	World_Prefab = {
		type = "Body",
		blueprint = "World",
		game_object = "World_Prefab_GO",
		model = "Cube.mesh",
		physic_entity = "rigid",
		physic_type = "static",
		physic_shape = "box",
		material = "Rocky",
	},

	Kasai_Prefab = {
		type = "Body",
		blueprint = "Kasai",
		game_object = "Kasai_Prefab_GO",
		player = "Player_GO",
		light_position = {0,0,0},
		specular_colour = {0,1,1},
		diffuse_colour = {1,1,1},
		flare_material = "Flare",
		flare_colour = {1,1,1},
		flare_size = 10,
		light_attenuation_range = 6.5,
		light_attenuation_constant = 1.0,
		light_attenuation_linear = 0.2,
		light_attenuation_quadratic = 0.05,
		is_visible = true,
		physic_entity = "rigid",
		physic_type = "kinematic",
		physic_trigger = true,
		physic_shape = "sphere",
		physic_radius = 6.5,
		physic_mass = 1,
		physic_group = 1,
	},

	Camera_Prefab = {
		type = "Body",
		blueprint = "Camera",
		game_object = "Camera_Prefab_GO",
		position = {0, 0, 30},
		fixed = true,
		ratio = 169,
		fov = 60,
	},

	Charge_Prefab = {
		type = "Body",
		blueprint = "Charge",
		game_object = "Charge_Prefab_GO",
		model = "Cube.mesh",
		scale = {0.5, 0.5, 0.5},
		specular_colour = {1,1,1},
		diffuse_colour = {1,1,1},
		light_attenuation_range = 5.0,
		light_attenuation_constant = 1.0,
		light_attenuation_linear = 0.2,
		light_attenuation_quadratic = 0.05,
		player = "Player_GO",
		lighting_area_radius = 5.0,
		interactuable_area_radius = 3.0,
		physic_entity = "rigid",
		physic_type = "dynamic",
		physic_shape = "sphere",
		physic_trigger = true,
		physic_group = 1,
		physic_mass = 1,
		physic_radius = 0.5,
	},

}
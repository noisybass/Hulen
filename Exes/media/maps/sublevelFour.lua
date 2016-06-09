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
	
	
World0_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Shadow", 
}, 

World1_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Shadow", 
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
state = "Shadow", 
}, 

World5_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Shadow", 
}, 

World6_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Shadow", 
}, 

World7_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World8_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World9_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Shadow", 
}, 

World10_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World11_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World12_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
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
state = "Shadow", 
}, 

World16_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Shadow", 
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
state = "Shadow", 
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
state = "Body", 
}, 

World24_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
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
state = "Shadow", 
}, 

World31_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World32_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World33_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Shadow", 
}, 

World34_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World35_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World36_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World37_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World38_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World39_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World40_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World41_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World42_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World43_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World44_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World45_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World46_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World47_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World48_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

World49_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

Background_GO = {
	type = "GameObject",
	blueprint = "Empty",
	state = "Body"
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
	
	
World0_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World0_GO", 
position = {5.24, -3.38, -3}, 
model = "wall2.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/wall2.RepX", 
}, 

World1_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World1_GO", 
position = {-11.66, -8.52, -2.987}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World2_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World2_GO", 
position = {25.71, -2.48, 0.013}, 
model = "floor4.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World2_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World2_GO", 
position = {25.71, -2.48, -2.987}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World3_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World3_GO", 
position = {7.7, -11.07, 0}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World3_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World3_GO", 
position = {7.7, -11.07, -3}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World4_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World4_GO", 
position = {-15.25, -8.66, -3}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World5_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World5_GO", 
position = {5.02, -9.58, -3}, 
model = "wall2.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/wall2.RepX", 
}, 

World6_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World6_GO", 
position = {2.56, 4.99, -2.767}, 
model = "floor2.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor2.RepX", 
}, 

World7_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World7_GO", 
position = {-13.48, 3.23, 0}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World8_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World8_GO", 
position = {-9.89, 3.37, 0.013}, 
model = "floor4.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World9_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World9_GO", 
position = {5.46, 2.82, -3}, 
model = "wall2.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/wall2.RepX", 
}, 

World10_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World10_GO", 
position = {-32.92, -10.5, 0}, 
model = "floor1.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor1.RepX", 
}, 

World11_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World11_GO", 
position = {-25.74, -10.5, 0}, 
model = "floor1.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor1.RepX", 
}, 

World12_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World12_GO", 
position = {-29.33, -10.26, -0.003}, 
model = "floor2.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor2.RepX", 
}, 

World13_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World13_GO", 
position = {-1.22, -7.42, 0.04}, 
model = "floor2.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor2.RepX", 
}, 

World13_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World13_GO", 
position = {-1.22, -7.42, -2.96}, 
model = "floor2.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor2.RepX", 
}, 

World14_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World14_GO", 
position = {2.37, -7.66, 0.04}, 
model = "floor1.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor1.RepX", 
}, 

World14_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World14_GO", 
position = {2.37, -7.66, -2.96}, 
model = "floor1.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor1.RepX", 
}, 

World15_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World15_GO", 
position = {-1.53, -1.48, -2.987}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World16_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World16_GO", 
position = {-5.12, -1.62, -3}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World17_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World17_GO", 
position = {-23.7, -2.29, 0}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World18_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World18_GO", 
position = {-20.11, -2.15, 0.013}, 
model = "floor4.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World19_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World19_GO", 
position = {4.79, -15.82, -3}, 
model = "wall2.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/wall2.RepX", 
}, 

World20_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World20_GO", 
position = {13.4, -13.01, 0}, 
model = "floor1.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor1.RepX", 
}, 

World20_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World20_GO", 
position = {13.4, -13.01, -3}, 
model = "floor1.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor1.RepX", 
}, 

World21_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World21_GO", 
position = {16.989, -12.77, -0.003}, 
model = "floor2.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor2.RepX", 
}, 

World21_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World21_GO", 
position = {16.989, -12.77, -3.003}, 
model = "floor2.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor2.RepX", 
}, 

World22_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World22_GO", 
position = {45.7, -12.81, 0.003}, 
model = "floor2.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor2.RepX", 
}, 

World22_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World22_GO", 
position = {45.7, -12.81, -2.997}, 
model = "floor2.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor2.RepX", 
}, 

World23_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World23_GO", 
position = {20.578, -13.01, 0}, 
model = "floor1.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor1.RepX", 
}, 

World23_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World23_GO", 
position = {20.578, -13.01, -3}, 
model = "floor1.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor1.RepX", 
}, 

World24_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World24_GO", 
position = {24.167, -12.77, -0.003}, 
model = "floor2.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor2.RepX", 
}, 

World24_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World24_GO", 
position = {24.167, -12.77, -3.003}, 
model = "floor2.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor2.RepX", 
}, 

World25_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World25_GO", 
position = {49.3, -13.01, 0.003}, 
model = "floor1.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor1.RepX", 
}, 

World25_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World25_GO", 
position = {49.3, -13.01, -2.997}, 
model = "floor1.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor1.RepX", 
}, 

World26_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World26_GO", 
position = {27.756, -13.01, 0}, 
model = "floor1.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor1.RepX", 
}, 

World26_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World26_GO", 
position = {27.756, -13.01, -3}, 
model = "floor1.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor1.RepX", 
}, 

World27_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World27_GO", 
position = {42.1, -13.01, 0.003}, 
model = "floor1.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor1.RepX", 
}, 

World27_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World27_GO", 
position = {42.1, -13.01, -2.997}, 
model = "floor1.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor1.RepX", 
}, 

World28_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World28_GO", 
position = {34.934, -13.01, 0}, 
model = "floor1.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor1.RepX", 
}, 

World28_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World28_GO", 
position = {34.934, -13.01, -3}, 
model = "floor1.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor1.RepX", 
}, 

World29_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World29_GO", 
position = {31.345, -12.77, -0.003}, 
model = "floor2.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor2.RepX", 
}, 

World29_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World29_GO", 
position = {31.345, -12.77, -3.003}, 
model = "floor2.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor2.RepX", 
}, 

World30_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World30_GO", 
position = {8.29, -4.54, -3}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World31_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World31_GO", 
position = {22.66, -4.4, 0.01}, 
model = "floor4.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World31_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World31_GO", 
position = {22.66, -4.4, -2.99}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World32_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World32_GO", 
position = {19.06, -4.54, 0}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World32_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World32_GO", 
position = {19.06, -4.54, -3}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World33_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World33_GO", 
position = {11.88, -4.54, -3}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World34_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World34_GO", 
position = {15.47, -4.4, 0.01}, 
model = "floor4.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World34_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World34_GO", 
position = {15.47, -4.4, -2.99}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World35_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World35_GO", 
position = {33.432, -4.4, 0.007}, 
model = "floor4.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World35_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World35_GO", 
position = {33.432, -4.4, -2.993}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World36_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World36_GO", 
position = {29.842, -4.54, -0.003}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World36_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World36_GO", 
position = {29.842, -4.54, -3.003}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World37_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World37_GO", 
position = {37.022, -4.54, -0.003}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World37_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World37_GO", 
position = {37.022, -4.54, -3.003}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World38_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World38_GO", 
position = {26.252, -4.54, -0.003}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World38_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World38_GO", 
position = {26.252, -4.54, -3.003}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World39_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World39_GO", 
position = {25.71, -10.9, 0.013}, 
model = "floor4.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World40_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World40_GO", 
position = {12.89, -8.7, -0.236}, 
model = "wall2.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/wall2.RepX", 
}, 

World40_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World40_GO", 
position = {12.89, -8.7, -3.236}, 
model = "wall2.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/wall2.RepX", 
}, 

World41_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World41_GO", 
position = {35.58, 10.96, -0.003}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World41_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World41_GO", 
position = {35.58, 10.96, -3.003}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World42_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World42_GO", 
position = {39.17, 10.96, -0.003}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World42_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World42_GO", 
position = {39.17, 10.96, -3.003}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World43_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World43_GO", 
position = {24.8, 11.1, 0.01}, 
model = "floor4.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World43_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World43_GO", 
position = {24.8, 11.1, -2.99}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World44_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World44_GO", 
position = {21.21, 10.96, 0}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World44_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World44_GO", 
position = {21.21, 10.96, -3}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World45_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World45_GO", 
position = {28.39, 10.96, 0}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World45_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World45_GO", 
position = {28.39, 10.96, -3}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World46_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World46_GO", 
position = {31.99, 11.1, 0.01}, 
model = "floor4.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World46_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World46_GO", 
position = {31.99, 11.1, -2.99}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World47_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World47_GO", 
position = {17.62, 10.96, 0}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World47_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World47_GO", 
position = {17.62, 10.96, -3}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World48_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World48_GO", 
position = {28.64, 15.17, -0.236}, 
model = "wall2.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/wall2.RepX", 
}, 

World48_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World48_GO", 
position = {28.64, 15.17, -3.236}, 
model = "wall2.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/wall2.RepX", 
}, 

World49_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World49_GO", 
position = {23.25, 15.17, -0.236}, 
model = "wall2.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/wall2.RepX", 
}, 

World49_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World49_GO", 
position = {23.25, 15.17, -3.236}, 
model = "wall2.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/wall2.RepX", 
}, 

Background = {
		type = "Body",
		blueprint = "Background",
		game_object = "Background_GO",
		position = {0, 0, -3.5},
		graphic_file = false,
		graphic_type = "plane",
		graphic_up_vector = {0, 0, 1},
		graphic_parallel_vector = {0, 1, 0},
		graphic_width = 72,
		graphic_height = 40.8,
		graphic_uTile = 1,
		graphic_vTile = 1,
		material = "Sublevel4",
	},

}
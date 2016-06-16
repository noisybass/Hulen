Map_GO = {

Player_GO = {
	type = "GameObject",
	blueprint = "Player_GO",
	isPlayer = true,
	state = "Body",
	playerDeathTime = 3,
	playerCanDie = true,
	chargesOwned = 1,
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
state = "Body", 
}, 

World1_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
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
state = "Body", 
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
state = "Shadow", 
}, 

World21_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Shadow", 
}, 

World22_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Shadow", 
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
state = "Shadow", 
}, 

World26_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Shadow", 
}, 

World27_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Shadow", 
}, 

World28_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Shadow", 
}, 

World29_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Shadow", 
}, 

World30_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Shadow", 
}, 

World31_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Shadow", 
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

PlataformaOlvidada1_GO = {
	type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
},

PlataformaOlvidada2_GO = {
	type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
},

-- PALANCA LUZ
World34_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

-- LIGHTBULB
World35_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

-- CARGA LUZ
World36_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

Wall0_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

Background_GO = {
	type = "GameObject",
	blueprint = "Empty",
	state = "Body"
},

DeathPlane_GO = {
	type = "GameObject",
	blueprint = "Empty",
	state = "Body"
},

InvisibleLeftWall_GO = {
	type = "GameObject",
	blueprint = "Empty",
	state = "Body",
},

FinishLevel_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
},

LightSave_GO = {
	type = "GameObject",
	blueprint = "Empty",
	state = "Body",
},

ChargeSave_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

--[[nose_GO = {
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
},]]--

}

Map = {
	
		Player_Body = {
		type = "Body",
		blueprint = "Player",
		game_object = "Player_GO",
		position = {-27.8, -13.5, 0.1},
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

	Camera = {
		type = "Body",
		blueprint = "Camera",
		game_object = "Camera_GO",
		position = {0, 0, 30},
		fixed = true,
		ratio = 169,
		fov = 60,
	},
	
	
World0_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World0_GO", 
position = {18.85, -6.87, -0.03}, 
model = "floor4.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World0_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World0_GO", 
position = {18.85, -6.87, -3.03}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World1_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World1_GO", 
position = {-23.186, -14.33, -0.043}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World1_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World1_GO", 
position = {-23.186, -14.33, -3.043}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World2_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World2_GO", 
position = {30.9, -14.33, -0.043}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World3_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World3_GO", 
position = {22.44, -7.01, -0.043}, 
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
position = {22.44, -7.01, -3.043}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World4_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World4_GO", 
position = {12.94, -14.187, -0.03}, 
model = "floor4.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World5_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World5_GO", 
position = {29.62, -7.01, -0.043}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World5_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World5_GO", 
position = {29.62, -7.01, -3.043}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World6_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World6_GO", 
position = {-5.222, -14.187, -0.03}, 
model = "floor4.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World6_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World6_GO", 
position = {-5.222, -14.187, -3.03}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World7_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World7_GO", 
position = {23.72, -14.33, -0.043}, 
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
position = {16.53, -14.33, -0.043}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World9_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World9_GO", 
position = {-26.778, -14.187, -0.03}, 
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
position = {-26.778, -14.187, -3.03}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World10_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World10_GO", 
position = {26.03, -6.87, -0.03}, 
model = "floor4.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World10_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World10_GO", 
position = {26.03, -6.87, -3.03}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World11_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World11_GO", 
position = {27.31, -14.187, -0.03}, 
model = "floor4.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World12_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World12_GO", 
position = {33.22, -6.87, -0.03}, 
model = "floor4.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World12_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World12_GO", 
position = {33.22, -6.87, -3.03}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World13_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World13_GO", 
position = {9.35, -14.33, -0.043}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World14_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World14_GO", 
position = {-30.37, -14.33, -0.043}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World14_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World14_GO", 
position = {-30.37, -14.33, -3.043}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World15_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World15_GO", 
position = {20.12, -14.187, -0.03}, 
model = "floor4.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World16_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World16_GO", 
position = {-8.822, -14.33, -0.043}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World16_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World16_GO", 
position = {-8.822, -14.33, -3.043}, 
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
position = {-16.002, -14.33, -0.043}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World17_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World17_GO", 
position = {-16.002, -14.33, -3.043}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World18_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World18_GO", 
position = {-19.594, -14.187, -0.03}, 
model = "floor4.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World18_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World18_GO", 
position = {-19.594, -14.187, -3.03}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World19_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World19_GO", 
position = {-12.412, -14.187, -0.03}, 
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
position = {-12.412, -14.187, -3.03}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World20_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World20_GO", 
position = {-21.99, 0.67, -3.043}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World21_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World21_GO", 
position = {-4.03, 0.82, -3.03}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World22_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World22_GO", 
position = {-25.58, 0.82, -3.03}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World23_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World23_GO", 
position = {-29.18, 0.67, -3.043}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World24_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World24_GO", 
position = {-7.63, 0.67, -3.043}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World25_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World25_GO", 
position = {-14.81, 0.67, -3.043}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World26_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World26_GO", 
position = {-18.4, 0.82, -3.03}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World27_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World27_GO", 
position = {-11.22, 0.82, -3.03}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World28_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World28_GO", 
position = {10.34, 0.82, -3.03}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World29_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World29_GO", 
position = {-0.44, 0.67, -3.043}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World30_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World30_GO", 
position = {3.16, 0.82, -3.03}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World31_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World31_GO", 
position = {6.75, 0.67, -3.043}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

World32_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World32_GO", 
position = {-14.52, -5.14, -3.03}, 
model = "floor4.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

World33_Shadow = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World33_GO", 
position = {-10.93, -5.29, -3.043}, 
model = "floor3.mesh", 
material = "Black", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

PlataformaOlvidada1_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "PlataformaOlvidada1_GO", 
position = {-16.52, -4.14, 0.03}, 
model = "floor4.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor4.RepX", 
}, 

PlataformaOlvidada2_Body = { 
type = "Body", 
blueprint  = "World", 
game_object  = "PlataformaOlvidada2_GO", 
position = {-12.93, -4.29, 0.043}, 
model = "floor3.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/floor3.RepX", 
}, 

-- PALANCA LUZ
World34_Body = { 
type = "Body", 
blueprint  = "LightLever", 
game_object  = "World34_GO", 
light_lever_GO_target = "Wall0_GO",
position = {-20.544, -12.536, -0.043},
model = "LightSwitch.mesh",
static = true,
physic_entity = "fromFile",
physic_file = "media/models/LightSwitch.RepX",
scale = { 1, 1, 1 }, 
physic_change_coords = true,
--physic_group = 4,

}, 

-- LIGHTBULB
World35_Body = { 
type = "Body",
blueprint = "Lightbulb",
game_object  = "World35_GO", 
rollRotate = 90,
position = {13.3, -12.536, -0.043}, 
direction = "left",
scale = {0.2, 0.2, 0.2},
model = "LightBulb.mesh",
material = "Red",
physic_shape = "capsule",
physic_radius = 1,
physic_height = 0.1,
gravity = 15,
guizmo = false,
guizmoSize = 10,
--speed = 2.5,
patrolPosition1 = {10, 0, 0},
patrolPosition2 = {17, 0, 0},
--position = {10, 0, 0}, 
--position = {17, 0, 0}, 
positionToGo = {10,0,0},
fsm_initial_state = "Lightbulb_Patrol",

--Animations
defaultAnimation = "walking_cycle",
defaultAnimationVelocity = 1,
idle1Animation =           {"idle_search", 1, "null"},
walkAnimation =            {"walking_cycle", 1, "null"},
runAnimation =             {"running_cycle", 1, "null"},
changeDirectionAnimation = {"change_direction", 1, "null"},
eatLightAnimation        = {"eat_light",1, "null"},
attackAnimation          = {"attack", 1, "null"},

--Blending
defaultBlendingVelocity = 5,
idle1Blending =           {"idle_search", 2, "null"},
walkBlending =            {"walking_cycle", 2, "null"},
runBlending =             {"running_cycle", 2, "null"},
changeDirectionBlending = {"change_direction", 2, "null"},
eatLightBlending        = {"eat_light",2, "null"},
attackBlending          = {"attack", 2, "null"},
}, 

-- CARGA LUZ
World36_Body = { 
type = "Body",
blueprint = "Charge",
prefab = "Charge_Prefab",
game_object = "World36_GO",
onMap = true, 
position = {24.54, -5.216, -0.043}, 
}, 

Wall0_Body = { 
type = "Body", 
blueprint  = "LeverTarget", 
game_object  = "Wall0_GO", 
position = {-4.229, -17.11, -0.321}, 
model = "wall2.mesh", 
material = "Floor", 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/wall2.RepX",
position2 = {-4.229, -10.11, -0.321}, 
speed = 10,
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
		graphic_width = 65,
		graphic_height = 50,
		material = "perPixel",
	},

	DeathPlane = {
		type = "Body",
		blueprint = "DeathPlane",
		game_object = "DeathPlane_GO",
		position = {0, -25, 0},
		model = "Cube.mesh",
		physic_entity = "rigid",
		physic_type = "static",
		physic_trigger = true,
		physic_shape = "box",
		scale = {60, 1, 10},
		physic_dimensions = { 120, 1, 10 },
	},

	

	InvisibleLeftWall_Body = {
		type = "Body",
		blueprint = "InvisibleWorld",
		game_object = "InvisibleLeftWall_GO",
		position = {-30, -10, 0},
		--model = "Cube.mesh",
		physic_entity = "rigid",
		physic_type = "static",
		physic_shape = "box",
		physic_dimensions = { 1,5,1 },
	},

	InvisibleLeftWall_Shadow = {
		type = "Shadow",
		blueprint = "InvisibleWorld",
		game_object = "InvisibleLeftWall_GO",
		position = {-30, -10, -3},
		--model = "Cube.mesh",
		physic_entity = "rigid",
		physic_type = "static",
		physic_shape = "box",
		physic_dimensions = { 1,5,1 },
	},

	FinishLevel_Body = {
		type = "Body",
		blueprint = "FinishLevel",
		game_object = "FinishLevel_GO",
		position = {30, -12, 0},
		model = "Cube.mesh",
		physic_entity = "rigid",
		physic_type = "static",
		physic_trigger = true,
		physic_shape = "box",
		physic_dimensions = { 1,5,1 },
	},

	LightSave = {
	type = "Body", 
	blueprint  = "LightLever", 
	game_object  = "LightSave_GO", 
	position = {-28, -13.3, -1.5}, 
	model = "EndLevelLightSwitch.mesh",
	static = true,
	physic_entity = "fromFile",
	physic_file = "media/models/EndLevelLightSwitch.RepX",
	physic_change_coords = true,
	--physic_group = 4,
	saverLight = true,

	},

	ChargeSave = { 
	type = "Body",
	blueprint = "Charge",
	prefab = "Charge_Prefab",
	game_object = "ChargeSave_GO",
	onMap = true,
	position = {-28, -10, -1.5}, 
	},

	--[[nose = {
		type = "Body",
		blueprint = "World",
		game_object = "nose_GO",
		position = {-14.52, -5.14, -3.03},
		model = "Cube.mesh",
		physic_entity = "rigid",
		physic_type = "static",
		physic_trigger = true,
		physic_shape = "box",
		physic_dimensions = { 1,5,1 },
	},]]

}
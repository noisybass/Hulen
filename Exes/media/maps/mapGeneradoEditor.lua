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
state = "Body", 
}, 

Spike1_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Shadow", 
}, 

Spike2_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Body", 
}, 

Spike3_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Shadow", 
}, 

Spike4_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Shadow", 
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
state = "Shadow", 
}, 

World6_GO = { 
type = "GameObject", 
blueprint  = "Empty", 
state = "Shadow", 
}, 


}

 Map = { 


Player_Body = { 
type = "Body", 
blueprint  = "Player", 
game_object  = "Player_GO", 
position = {-21.51, 8.69, 0}, 
model = "Test_Main_character.mesh", 
material = "Yellow", 
defaultAnimation  = "Idle_cycle_1", 
scale = { 0.2, 0.2, 0.2 }, 
physic_shape = "capsule", 
physic_radius = 1.5, 
physic_height = 0.75, 
speed = 0.01, 
jump_speed = 0.03, 
jump_height = 8, 
gravity = 0.015, 
}, 

Player_Shadow = { 
type = "Shadow", 
blueprint  = "Player", 
game_object  = "Player_GO", 
position = {-21.51, 8.69, 0}, 
model = "Test_Main_character.mesh", 
material = "Yellow", 
defaultAnimation  = "Idle_cycle_1", 
scale = { 0.2, 0.2, 0.2 }, 
physic_shape = "capsule", 
physic_radius = 1.5, 
physic_height = 0.75, 
speed = 0.01, 
jump_speed = 0.03, 
jump_height = 8, 
gravity = 0.015, 
}, 

Kasai_Body = { 
type = "Body", 
blueprint  = "Kasai", 
game_object  = "Kasai_GO", 
position = {0, 0, 0}, 
light_position = {0,0,0}, 
specular_colour = {1,1,1}, 
diffuse_colour = {1,1,1}, 
flare_material = "Flare", 
flare_colour = {1,1,1}, 
flare_size = 10, 
light_attenuation_range  = 6.5, 
light_attenuation_constant = 1.0, 
light_attenuation_linear = 0.2, 
light_attenuation_quadratic = 0.05, 
player = "Player_GO", 
lighting_area_radius = 6.5, 
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
type = "Body", 
blueprint  = "Spike", 
game_object  = "Spike0_GO", 
position = {-17.05, -2.58, 0}, 
model = "Spike.mesh", 
material = "Yellow", 
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
position = {-5.14, -14.21, 0}, 
model = "Spike.mesh", 
material = "Black", 
static = true, 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/Spike.RepX", 
physic_group = 1, 
}, 

Spike2 = { 
type = "Body", 
blueprint  = "Spike", 
game_object  = "Spike2_GO", 
position = {-11.94, -8.41, 0}, 
model = "Spike.mesh", 
material = "Yellow", 
static = true, 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/Spike.RepX", 
physic_group = 1, 
}, 

Spike3 = { 
type = "Shadow", 
blueprint  = "Spike", 
game_object  = "Spike3_GO", 
position = {0.21, -14.08, 0}, 
model = "Spike.mesh", 
material = "Black", 
static = true, 
scale = { 1, 1, 1 }, 
physic_entity = "fromFile", 
physic_file = "media/models/Spike.RepX", 
physic_group = 1, 
}, 

Spike4 = { 
type = "Shadow", 
blueprint  = "Spike", 
game_object  = "Spike4_GO", 
position = {11.01, -3.89, 0}, 
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
position = {-22.026, -3.52, 0}, 
model = "Cube.mesh", 
material = "Rocky", 
scale = { 14.64663, 1, 1 }, 
physic_shape = "box", 
physic_dimensions  = { 14.64663, 1, 1 }, 
physic_entity = "rigid", 
physic_type = "static", 
}, 

World1 = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World1_GO", 
position = {-15.16, -9.48, 0}, 
model = "Cube.mesh", 
material = "Rocky", 
scale = { 9.093, 1, 1 }, 
physic_shape = "box", 
physic_dimensions  = { 9.093, 1, 1 }, 
physic_entity = "rigid", 
physic_type = "static", 
}, 

World2 = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World2_GO", 
position = {-5.37, -15.03, 0}, 
model = "Cube.mesh", 
material = "Rocky", 
scale = { 15.96909, 1, 1 }, 
physic_shape = "box", 
physic_dimensions  = { 15.96909, 1, 1 }, 
physic_entity = "rigid", 
physic_type = "static", 
}, 

World3 = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World3_GO", 
position = {9.09, -11.24, 0}, 
model = "Cube.mesh", 
material = "Rocky", 
scale = { 9.093, 1, 1 }, 
physic_shape = "box", 
physic_dimensions  = { 9.093, 1, 1 }, 
physic_entity = "rigid", 
physic_type = "static", 
}, 

World4 = { 
type = "Body", 
blueprint  = "World", 
game_object  = "World4_GO", 
position = {16.67, -4.82, 0}, 
model = "Cube.mesh", 
material = "Rocky", 
scale = { 14.64663, 1, 1 }, 
physic_shape = "box", 
physic_dimensions  = { 14.64663, 1, 1 }, 
physic_entity = "rigid", 
physic_type = "static", 
}, 

World5 = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World5_GO", 
position = {-9.12, -3.51, 0}, 
model = "Cube.mesh", 
material = "Black", 
scale = { 11.36509, 1, 1 }, 
physic_shape = "box", 
physic_dimensions  = { 11.36509, 1, 1 }, 
physic_entity = "rigid", 
physic_type = "static", 
}, 

World6 = { 
type = "Shadow", 
blueprint  = "World", 
game_object  = "World6_GO", 
position = {-5.22, -9.48, 0}, 
model = "Cube.mesh", 
material = "Black", 
scale = { 11.36509, 1, 1 }, 
physic_shape = "box", 
physic_dimensions  = { 11.36509, 1, 1 }, 
physic_entity = "rigid", 
physic_type = "static", 
}, 



}

-- Generated with Version 0.6 of the Hulen Editor © 2016

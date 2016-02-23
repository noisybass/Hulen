## AnimatedGraphics
-------------------
### _Attributes_

| Attribute        | Type           |
| ---------------- | -------------- |
| scale            | Vector3        |
| defaultAnimation | std::string    |


## AvatarController
-------------------
### _Attributes_

| Attribute        | Type           |
| ---------------- | -------------- |
| speed            | float          |


## Camera
-------------------
### _Attributes_

| Attribute        | Type           |
| ---------------- | -------------- |
| distance         | float          |
| height           | float          |
| targetDistance   | float          |
| fixed            | bool           |
| ratio            | std::string    |
| fov              | float          |


## Graphics
-------------------
### _Attributes_

| Attribute        | Type           |
| ---------------- | -------------- |
| model            | std::string    |
| material         | std::string    |
| guizmoSize       | int            |
| guizmo           | bool           |
| static           | bool           |
| scale            | Vector3        |


## KasaiController
-------------------
### _Attributes_

| Attribute        | Type           |
| ---------------- | -------------- |
| player           | std::string    |
| is_visible       | bool           |


## PointLight
-------------------
### _Attributes_

| Attribute                   | Type           |
| --------------------------- | -------------- |
| diffuse_colour              | Vector3        |
| specular_colour             | Vector3        |
| light_position              | Vector3        |
| light_attenuation_range     | float          |
| light_attenuation_constant  | float          |
| light_attenuation_linear    | float          |
| light_attenuation_quadratic | float          |
| flare_material              | std::string    |
| flare_colour                | Vector3        |
| flare_size                  | int            |


## PhysicEntity
-------------------
### _Attributes_

| Attribute                   | Type           | Values                 |
| --------------------------- | -------------- | ---------------------- |
| physic_entity               | std::string    | plane, rigid, fromFile |
| physic_group                | int            |                        |

Si `physic_entity = plane`:
| Attribute                   | Type           |
| --------------------------- | -------------- |
| physic_normal               | Vector3        |

Si `physic_entity = fromFile`:
| Attribute                   | Type           |
| --------------------------- | -------------- |
| physic_file                 | std::string    |

Si `physic_entity = rigid`:
| Attribute                   | Type           | Values                     |
| --------------------------- | -------------- | -------------------------- |
| physic_type                 | std::string    | static, dynamic, kinematic |
| physic_shape                | std::sring     | box, sphere                |
| physic_trigger              | bool           |                            |

Si `physic_type != static`, es decir, `dynamic` o `kinematic`:
| Attribute                   | Type           |
| --------------------------- | -------------- |
| physic_mass                 | float          |

Si `physic_shape = box`:
| Attribute                   | Type           |
| --------------------------- | -------------- |
| physic_dimensions           | Vector3        |

Si `physic_shape = sphere`:
| Attribute                   | Type           |
| --------------------------- | -------------- |
| physic_radius               | float          |


## PhysicController
-------------------
### _Attributes_

| Attribute                   | Type           |
| --------------------------- | -------------- |
| physic_shape                | string         |
| physic_radius               | float          |
| physic_height               | float          |

	El atributo `physic_shape` es opcional, y su valor por defecto es `"capsule"`.
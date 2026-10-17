extends Label

#quick and dirty parallax

#@export var building_first_Node2D: Node2D
#@export var building_last_Node2D: Node2D
#@export 
var camera_Node2D: Node2D

var building_x_dist: float
var parallax_max_x: float

func _ready() -> void:
	#building_first_Node2D = $"../Windmills"
	var building_last_Node2D = $"../bacteria_factory"
	camera_Node2D = $"../Camera2D"
	building_x_dist = building_last_Node2D.position.x #- building_first_Node2D.position.x
	parallax_max_x = building_x_dist - 65

func _process(_delta: float) -> void:
	var cam_x: float = camera_Node2D.position.x
	var ratio: float = cam_x / building_x_dist
	position.x = ratio * parallax_max_x
	

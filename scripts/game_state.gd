class_name GameState
extends Node

@export var toxicity: float = 100
@export var energy: int = 0
@export var energy_income: int = 10
@export var selected_building: int = 0
@export var all_buildings: Array[Building]
#@export var camera: OurCamera


var current_day: float

#func _ready() -> void:
	#pass # Replace with function body.


func _process(delta: float) -> void:
	current_day += delta
	if(Input.is_action_just_pressed("left")):
		selected_building -= 1
		if(selected_building < 0):
			selected_building = all_buildings.size() - 1
		print("left")#OurCamera.start_moving()
	if(Input.is_action_just_pressed("right")):
		#ddselected_building = (selected_building + 1) % all_buildings.size()
		print("right")#OurCamera.start_moving()
	#if(Input.is_action_just_pressed("up")):
#z		all_buildings[selected_building].select_up()
	#if(Input.is_action_just_pressed("down")):
		#all_buildings[selected_building].select_down()
	if(Input.is_action_just_pressed("exit")):
		get_tree().quit()

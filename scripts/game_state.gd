class_name GameState
extends Node

@export var toxicity: float = 100
@export var energy: int = 0
@export var energy_income: int = 10
@export var selected_building: int = 0
@export var all_buildings: Array[Building]
@export var camera: OurCamera
@export var ui_bar: UIBar

var current_day: float

#func _ready() -> void:
	#pass # Replace with function body.

func set_energy_income(new_income: int):
	energy_income = new_income
	ui_bar.update_energy_income_label(new_income)

func add_to_energy_storage(added_energy: int):
	energy += added_energy
	ui_bar.update_energy_stored_label(energy)

func take_to_energy_storage(taken_energy: int):
	energy -= taken_energy
	ui_bar.update_energy_stored_label(energy)


func _process(delta: float) -> void:
	current_day += delta
	if(Input.is_action_just_pressed("left")):
		selected_building -= 1
		if(selected_building < 0):
			selected_building = all_buildings.size() - 1
		camera.start_moving()
	if(Input.is_action_just_pressed("right")):
		selected_building = (selected_building + 1) % all_buildings.size()
		camera.start_moving()
	if(Input.is_action_just_pressed("up")):
		all_buildings[selected_building].select_up()
	if(Input.is_action_just_pressed("down")):
		all_buildings[selected_building].select_down()
	if(Input.is_action_just_pressed("exit")):
		get_tree().quit()

class_name GameState
extends Node

@export var toxicity: float = 100
@export var toxicity_reduction: float = 0.1
@export var energy: int = 0
@export var energy_income: int = 10
@export var selected_building: int = 0
@export var all_buildings: Array[Building]
@export var camera: OurCamera
@export var ui_bar: UIBar
@export var day_duration: float = 1

var time_passed: float
var current_day: int = 1

func _ready() -> void:
	set_ui()

func set_ui():
	ui_bar.update_acidity_level_label(toxicity)
	ui_bar.update_acidity_change_label(toxicity_reduction)
	ui_bar.update_energy_income_label(energy_income)
	ui_bar.update_energy_stored_label(energy)
	ui_bar.update_displayed_date(current_day)
	display_message("Welcome to Venus! Deadly rain of sulfuric acid was found to be bad for colonists health. Get rid of it! The acid of course, rain can stay.")

func _update_toxicity():
	remove_acidity(toxicity_reduction)

func _update_energy():
	add_to_energy_storage(energy_income)

func set_energy_income(new_income: int):
	energy_income = new_income
	ui_bar.update_energy_income_label(new_income)

func add_to_energy_storage(added_energy: int):
	energy += added_energy
	ui_bar.update_energy_stored_label(energy)

func take_to_energy_storage(taken_energy: int):
	energy -= taken_energy
	ui_bar.update_energy_stored_label(energy)

func remove_acidity(removed_acidity: float):
	toxicity -= removed_acidity
	if toxicity < 0:
		_end_game()
	ui_bar.update_acidity_level_label(toxicity)

func set_acidity_change(new_acidity_change: float):
	toxicity_reduction = new_acidity_change
	ui_bar.update_acidity_change_label(toxicity_reduction)

func _end_game():
	get_tree().change_scene_to_file("res://scenes/main_menu.tscn")
	# TODO: end game scene

func _on_day_timeout():
	time_passed = 0
	current_day += 1
	ui_bar.update_displayed_date(current_day)
	
	_update_energy()
	_update_toxicity()

func display_message(message: String):
	ui_bar.set_message(message)

func _process(delta: float) -> void:
	time_passed += delta
	if time_passed > day_duration:
		_on_day_timeout()
	
	if(Input.is_action_just_pressed("ok")):
		all_buildings[selected_building].applySelectedUpgrade()
	if(Input.is_action_just_pressed("left")):
		selected_building -= 1
		if(selected_building < 0):
			selected_building = all_buildings.size() - 1
		ui_bar.update_selected_building_label(all_buildings[selected_building].title)
		camera.start_moving()
	if(Input.is_action_just_pressed("right")):
		selected_building = (selected_building + 1) % all_buildings.size()
		ui_bar.update_selected_building_label(all_buildings[selected_building].title)
		camera.start_moving()
	if(Input.is_action_just_pressed("up")):
		all_buildings[selected_building].select_up()
	if(Input.is_action_just_pressed("down")):
		all_buildings[selected_building].select_down()
	if(Input.is_action_just_pressed("exit")):
		get_tree().quit()

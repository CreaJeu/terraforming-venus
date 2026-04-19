extends Node2D

func _input(event):
	if event.is_action_pressed("ui_accept"):
		load_main_scene()
	if event.is_action_pressed("exit"):
		quit_game()

func load_main_scene():
	#get_tree().change_scene_to_file("res://scenes/main.tscn")
	var other_path = "res://scenes/main.tscn"
	var other_packed: PackedScene = load(other_path)
	var other_scene:Node = other_packed.instantiate()
	get_node("..").add_child(other_scene)
	queue_free()

func quit_game():
	get_tree().quit()

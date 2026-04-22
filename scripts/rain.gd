class_name Rain
extends Node2D

func get_random_position_in_screen() -> Vector2:
	var rng = RandomNumberGenerator.new()
	var screenSize = get_viewport().get_visible_rect().size
	
	# A bit outside camera to fill everything with diagonal movement
	var rndX = rng.randi_range(-20, screenSize.x)
	var rndY = rng.randi_range(-10, screenSize.y-40)
	return Vector2(rndX, rndY)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta: float) -> void:
	var rain_particle_scene: PackedScene = load("res://scenes/rain_particle.tscn")
	var rain_particle: RainParticle = rain_particle_scene.instantiate()
	rain_particle.position = get_random_position_in_screen()
	add_child(rain_particle)

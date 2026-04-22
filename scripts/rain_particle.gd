class_name RainParticle
extends Label

func _ready() -> void:
	var rng = RandomNumberGenerator.new()
	var particle_type = rng.randi_range(0, 1)
	if particle_type == 0:
		text = '\\'
	if particle_type == 1:
		text = "`"

func _process(delta: float) -> void:
	position.y += 20 * delta
	position.x += 20 * delta
	if position.y > get_viewport().get_visible_rect().size.y - 10:
		self.queue_free()

extends Node

@onready var label: Label = $".."
@export var timeout_at: float = 0.5
var accumulated_time: float = 0

func _process(delta: float) -> void:
	accumulated_time += delta
	
	if accumulated_time >= timeout_at:
		accumulated_time = 0
		_on_timeout()

func _on_timeout():
	label.visible = !label.visible

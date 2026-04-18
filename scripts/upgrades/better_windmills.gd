class_name BetterWindmills
extends Node2D

@export var energy_multiplier: float = 2.0
@export var price: int = 400
@export var selected: bool = false

func _ready() -> void:
	if selected:
		select()
	else:
		deselect()

func select() -> void:
	selected = true
	$pointer_Label.show()
	$buy_Label.show()
	$pointer_Label/BlinkLabel.process_mode = Node.PROCESS_MODE_INHERIT
	
func deselect() -> void:
	selected = false
	$pointer_Label.hide()
	$buy_Label.hide()
	$pointer_Label/BlinkLabel.process_mode = Node.PROCESS_MODE_DISABLED

extends Node2D

@export var energy_multiplier: float = 2.0
@export var selected: bool = false
@export var gamestate: GameState

func _ready() -> void:
	if selected:
		select()
	else:
		deselect()

func _exit_tree() -> void:
	if(gamestate == null):
		return
	gamestate.set_energy_income(gamestate.energy_income * 2)
	gamestate.display_message("The windmills now have a motor making them spin extra fast to produce more energy")

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

extends Node2D

@export var acidity_reduction_modifier: int = 2
@export var price: int = 500
@export var selected: bool = false
@export var gamestate: GameState

func _ready() -> void:
	if selected:
		select()
	else:
		deselect()

func apply() -> bool:
	if gamestate.energy < price:
		gamestate.display_message("Not enough energy: " + str(price) + " is needed for this upgrade")
		return false
		
	gamestate.add_to_energy_storage(-price)
	gamestate.set_acidity_change(gamestate.toxicity_reduction * acidity_reduction_modifier)
	gamestate.display_message("This energy actually went into a lot of research to improve bacteria's genetics. What did you think we would do with it?")
	
	return true

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

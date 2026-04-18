extends Node2D

@export var additional_energy: int = 10
@export var price: int = 100
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
	gamestate.set_energy_income(gamestate.energy_income + additional_energy)
	gamestate.display_message("More windmills = More energy. Luckily there is no lack of wind on Venus.")

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

extends Node

@export var price: int = 100

var gs: GameState

func _ready() -> void:
	gs = $"../../../gameState_Node"

func apply_upgrade() -> bool:
	if gs.energy < price:
		gs.display_message("Not enough energy: " + str(price) + " is needed for this upgrade")
		return false
	gs.add_to_energy_storage(-price)
	$"..".queue_free()
	#gs.set_energy_income(gamestate.energy_income * 2)
	#gs.display_message("The windmills now have a motor making them spin extra fast to produce more energy")
	return true

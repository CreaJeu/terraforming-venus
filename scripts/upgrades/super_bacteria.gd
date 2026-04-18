extends Node2D

@export var acidity_reduction: int = 10
@export var price: int = 200
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
	gamestate.remove_acidity(acidity_reduction)
	gamestate.display_message("Our scientists cultivated a gigantic bacteria to help cleanse the rain. It broke the containment and ate a ton of sulfuric acid before dying.")
	
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

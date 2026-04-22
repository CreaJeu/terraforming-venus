extends Node2D

@export var acidity_reduction: int = 20
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
	gamestate.remove_acidity(acidity_reduction)
	gamestate.display_message("Our scientists cultivated a gigantic bacteria to help cleanse the rain. It broke the containment and ate a ton of sulfuric acid before dying.")

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

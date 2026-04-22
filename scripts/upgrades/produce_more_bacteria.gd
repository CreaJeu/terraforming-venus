extends Node2D

@export var bacteria_reduction_improvement: float = 0.4
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
	gamestate.set_acidity_change(gamestate.toxicity_reduction + bacteria_reduction_improvement)
	gamestate.display_message("Shoking bacteria with a lot of electricity surprisingly makes more of them. That was definetly why we tried that.")

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

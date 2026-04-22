extends Node2D

@export var acidity_reduction_modifier: int = 2
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
	gamestate.set_acidity_change(gamestate.toxicity_reduction * acidity_reduction_modifier)
	gamestate.display_message("This energy actually went into a lot of research to improve bacteria's genetics. What did you think we would do with it?")

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

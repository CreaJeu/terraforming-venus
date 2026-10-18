extends Sprite2D

#@export var rot_speed : float = -.7
var gamestate: GameState

func _ready() -> void:
	gamestate = $"/root/main_Node/gameState_Node"
	print_tree_pretty()
	print_debug(gamestate)

func _process(delta: float) -> void:
	if is_visible_in_tree():
		rotate(gamestate.windmill_rot_speed * delta)

class_name OurCamera
extends Camera2D

@export var MOVE_TIME: float = .5
var time_till_arrived: float = .5
var gs: GameState


func _ready() -> void:
	gs = $"../gameState_Node"
	make_current()

func _process(delta: float) -> void:
	if(time_till_arrived > 0):
		var b: Building = gs.all_buildings[gs.selected_building]
		if(delta < time_till_arrived):
			var whole_move = b.position - position
			var ratio: float = delta / time_till_arrived
			time_till_arrived -= delta
			translate(whole_move * ratio)
		else:
			time_till_arrived = 0
			position = b.position

func start_moving() -> void:
	time_till_arrived = MOVE_TIME

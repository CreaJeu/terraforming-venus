class_name Upgrade
extends Node2D

@export var name_str: String = ". Placeholder upgrade thing stuff ."
@export var effect_acidity: float = -10
@export var effect_energy: int = +10
@export var price: int = 99
@export var selected: bool = false

func _ready() -> void:
	$name_Label.text = name_str
	if(effect_acidity != 0):
		$effect_Label.text = "effect : acidity %f %%/Day" % effect_acidity
	if(effect_energy != 0):
		$effect_Label.text = "effect : energy +%d W/Day" % effect_energy
	$price_Label.text = "price : %d W" % price
	
	if selected:
		select()
	else:
		deselect()

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

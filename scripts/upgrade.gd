class_name Upgrade
extends Node2D

@export var name_str: String = ". Placeholder upgrade thing stuff ."
@export var effect_acidity: float = -10
@export var effect_energy: int = +10
@export var price: int = 99

func _ready() -> void:
	$name_Label.text = name_str
	if(effect_acidity != 0):
		$effect_Label.text = "effect : acidity %f %/Day" % effect_acidity
	if(effect_energy != 0):
		$effect_Label.text = "effect : energy +%d W/Day" % effect_energy
	$price_Label.text = "price : %d W" % price
	#blbl()

#func _process(delta: float) -> void:
	#pass

#func blbl() -> void:
	#print("BLBL effect : acidity %d m/day" % effect_acidity)

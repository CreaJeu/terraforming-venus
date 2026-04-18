class_name Building
extends Node2D

@export
var title: String = "~  Placeholder Building cool  ~"

@export var selected_upgrade: Upgrade

func _ready() -> void:
	$title_Label.text = title
	#$upgradeList_Node2D/bidon_upgrade_Node2D.blbl()

#func _process(delta: float) -> void:
	#pass

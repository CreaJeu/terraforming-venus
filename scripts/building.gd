class_name Building
extends Node2D

@export
var title: String = "~  Placeholder Building cool  ~"

@export var selected_upgrade: Upgrade

func _ready() -> void:
	var char_number = title.length() + 2
	var text = "#" + "#".repeat(char_number) + "#" + "\n" 
	text += "#" + " ".repeat(char_number) + "#" + "\n"
	text += "# " + title + " #\n"
	text += "#" + " ".repeat(char_number) + "#" + "\n"
	text += "#" + "#".repeat(char_number) + "#" + "\n"
	
	$title_Label.text = text
	#$upgradeList_Node2D/bidon_upgrade_Node2D.blbl()

#func _process(delta: float) -> void:
	#pass

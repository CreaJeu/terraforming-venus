class_name Building
extends Node2D

@export
var title: String = "~  Placeholder Building cool  ~"

@export var selected_upgrade: Node2D

func _ready() -> void:	
	$title_Label.text = make_ui_title_from_text(title)
	#$upgradeList_Node2D/bidon_upgrade_Node2D.blbl()

func make_ui_title_from_text(text: String) -> String:
	var char_number = text.length() + 2
	var new_text = "#" + "#".repeat(char_number) + "#" + "\n" 
	new_text += "#" + " ".repeat(char_number) + "#" + "\n"
	new_text += "# " + text + " #\n"
	new_text += "#" + " ".repeat(char_number) + "#" + "\n"
	new_text += "#" + "#".repeat(char_number) + "#" + "\n"
	return new_text


#func _process(delta: float) -> void:
	#pass

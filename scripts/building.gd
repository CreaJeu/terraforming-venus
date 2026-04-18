class_name Building
extends Node2D

@export
var title: String = "~  Placeholder Building cool  ~"

@export var upgrades: Array[Node2D]
@export var selected_upgrade_index: int = 0

func _ready() -> void:	
	$title_Label.text = make_ui_title_from_text(title)
	upgrades[selected_upgrade_index].select()

func make_ui_title_from_text(text: String) -> String:
	var char_number = text.length() + 2
	var new_text = "#" + "#".repeat(char_number) + "#" + "\n" 
	new_text += "#" + " ".repeat(char_number) + "#" + "\n"
	new_text += "# " + text + " #\n"
	new_text += "#" + " ".repeat(char_number) + "#" + "\n"
	new_text += "#" + "#".repeat(char_number) + "#" + "\n"
	return new_text

func applySelectedUpgrade():
	if upgrades.size()==0:
		return
	# Get selected upgrade and apply it
	var upgrade = upgrades[selected_upgrade_index]
	# TODO: return if not enough money
	if !upgrade.apply():
		return
	
	upgrades.remove_at(selected_upgrade_index)
	if upgrades.size() > 0:
		selected_upgrade_index = (selected_upgrade_index + 1) % upgrades.size()
		upgrades[selected_upgrade_index].select()
	else:
		selected_upgrade_index = 0
	
	# Destroy the applied upgrade
	upgrade.queue_free()
	

func select_up():
	upgrades[selected_upgrade_index].deselect()
	selected_upgrade_index = (selected_upgrade_index - 1) % upgrades.size()
	upgrades[selected_upgrade_index].select()

func select_down():
	upgrades[selected_upgrade_index].deselect()
	selected_upgrade_index = (selected_upgrade_index + 1) % upgrades.size()
	upgrades[selected_upgrade_index].select()

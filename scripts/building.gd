class_name Building
extends Node2D

@export
var title: String = "~  Placeholder Building cool  ~"

@export var upgrades_paths: Array[String]
@export var selected_upgrade_index: int = 0

var upgrades: Array[Node2D]

func _ready() -> void:	
	$title_Label.text = make_ui_title_from_text(title)
	for i in upgrades_paths.size():
		var path = upgrades_paths[i]
		var upgr_n2D: Node2D = get_node(path)
		upgrades.push_back(upgr_n2D)
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
	var upgr_applyer = upgrade.get_node("applyer_Node")
	if !upgr_applyer.apply_upgrade():
		return
	
	upgrades.remove_at(selected_upgrade_index)
	if upgrades.size() > 0:
		selected_upgrade_index = selected_upgrade_index % upgrades.size()
		upgrades[selected_upgrade_index].select()
	else:
		selected_upgrade_index = 0

func select_up():
	if(upgrades.size() > 0):
		upgrades[selected_upgrade_index].deselect()
		selected_upgrade_index = (selected_upgrade_index - 1) % upgrades.size()
		upgrades[selected_upgrade_index].select()

func select_down():
	if(upgrades.size() > 0):
		upgrades[selected_upgrade_index].deselect()
		selected_upgrade_index = (selected_upgrade_index + 1) % upgrades.size()
		upgrades[selected_upgrade_index].select()

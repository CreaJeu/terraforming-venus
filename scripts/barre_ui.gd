class_name UIBar
extends Node2D

@onready var BuildingSelect: Label = $TextLine1/BuildingSelect
@onready var EnergyStored: Label = $TextLine1/EnergyStored_Label
@onready var EnergyIncome: Label = $TextLine1/EnergyIncome_Label
@onready var AcidityLevel: Label = $TextLine1/AcidityLevel_Label
@onready var AcidityChange: Label = $TextLine1/AcidityChange_Label
@onready var Date_Label: Label = $TextLine1/Date_Label
@onready var Message_Label: Label = $TextLine2/Text

func update_selected_building_label(new_building: String):
	BuildingSelect.text = "[ ← ] " + new_building + " [ → ]"
	
func update_energy_stored_label(new_energy: int):
	EnergyStored.text = "Energy stored: " + str(new_energy) + " W"

func update_energy_income_label(new_income: int):
	EnergyIncome.text = "(+" + str(new_income) + " W/Day)"

func update_acidity_level_label(new_level: float):
	AcidityLevel.text = "Rain acidity: " + str("%0.1f" % new_level) + " %"
	
func update_acidity_change_label(new_change: float):
	AcidityChange.text = "(-" + str("%0.1f" % new_change) + " %/Day)"

func update_displayed_date(current_day: int):
	var day: int = current_day%365
	var year: int = floor(current_day / 365)
	Date_Label.text = "Year " + str(year) + " Day " + str(day)

func set_message(message: String):
	Message_Label.text = message

#include <cluige.h>
#include "BarreUI.h"
void ready_BarreUI(Script* this_Script);

Script* instantiate_BarreUI(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	BarreUI* new_BarreUI = iCluige.checked_malloc(sizeof(BarreUI));
	new_Script->_sub_class = new_BarreUI;

	//plug virtual mehods
	new_BarreUI->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_BarreUI;
	new_Script->ready = ready_BarreUI;
	return new_Script;
}

void register_BarreUIFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_BarreUI;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/barre_ui", sf);
}

void delete_BarreUI(Script* this_Script)
{
	BarreUI* this_BarreUI =
			(BarreUI*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_BarreUI->_delete_super;
	free(this_BarreUI);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

void ready_BarreUI(Script* this_Script)
{
	BarreUI* this_BarreUI = (BarreUI*)(this_Script->_sub_class);
    Node* this_Node = (Node*)(this_Script->node);

	Node* n = iCluige.iNode.get_node(this_Node, "./TextLine1/BuildingSelect");
	this_BarreUI->BuildingSelect = (SpriteText*)n->script->_sub_class;

    n = iCluige.iNode.get_node(this_Node, "./TextLine1/EnergyStored_Label");
	this_BarreUI->EnergyStored = (SpriteText*)n->script->_sub_class;

    n = iCluige.iNode.get_node(this_Node, "./TextLine1/EnergyIncome_Label");
	this_BarreUI->EnergyIncome = (SpriteText*)n->script->_sub_class;

    n = iCluige.iNode.get_node(this_Node, "./TextLine1/AcidityLevel_Label");
	this_BarreUI->AcidityLevel = (SpriteText*)n->script->_sub_class;

    n = iCluige.iNode.get_node(this_Node, "./TextLine1/AcidityChange_Label");
	this_BarreUI->AcidityChange = (SpriteText*)n->script->_sub_class;

    n = iCluige.iNode.get_node(this_Node, "./TextLine1/Date_Label");
	this_BarreUI->Date_Label = (SpriteText*)n->script->_sub_class;

    n = iCluige.iNode.get_node(this_Node, "./TextLine2/Text");
	this_BarreUI->Message_Label = (SpriteText*)n->script->_sub_class;
}

void update_selected_building_label(BarreUI* barreUI, char* new_building){
    char str[50];
    sprintf(str, "[ <- ] %s [ -> ]", new_building);
    iCluige.iSpriteText.set_text(barreUI->BuildingSelect, str);
}

void update_energy_stored_label(BarreUI* barreUI, int new_energy){
    char str[40];
    sprintf(str, "Energy stored: %d W", new_energy);
    iCluige.iSpriteText.set_text(barreUI->EnergyStored, str);
}

void update_energy_income_label(BarreUI* barreUI, int new_income){
    char str[40];
    sprintf(str, "(+ %d W/Day)", new_income);
    iCluige.iSpriteText.set_text(barreUI->EnergyIncome, str);
}

void update_acidity_level_label(BarreUI* barreUI, float new_level){
    char str[50];
    sprintf(str, "Rain acidity %.2f %%", new_level);
    iCluige.iSpriteText.set_text(barreUI->AcidityLevel, str);
}

void update_acidity_change_label(BarreUI* barreUI, float new_change){
    char str[50];
    sprintf(str, "(-%.2f %%/Day)", new_change);
    iCluige.iSpriteText.set_text(barreUI->AcidityChange, str);
}

void update_displayed_date(BarreUI* barreUI, int current_day){
    int day = current_day%365;
    int year = (int) (current_day / 365);
    //Date_Label.text = "Year " + str(year) + " Day " + str(day)
    char str[40];
    sprintf(str, "Year %d Day %d", year, day);
    iCluige.iSpriteText.set_text(barreUI->Date_Label, str);
}

void set_message(BarreUI* barreUI, char* message){
    iCluige.iSpriteText.set_text(barreUI->Message_Label, message);
}

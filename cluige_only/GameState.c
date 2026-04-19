#include <cluige.h>
#include "GameState.h"
#include "OurCamera.h"
#include "BarreUI.h"
#include "Building.h"

void process_GameState(Script* this_Script, float delta);
void ready_GameState(Script* this_Script);

Script* instantiate_GameState(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	GameState* new_GameState = iCluige.checked_malloc(sizeof(GameState));
	new_Script->_sub_class = new_GameState;

	//instantiate fields
	bool found = utils_float_from_parsed(&(new_GameState->toxicity), parsed_params, "toxicity");
	if(!found)
	{
		new_GameState->toxicity = 100;//default value from .gd
	}
	found = utils_float_from_parsed(&(new_GameState->toxicity_reduction), parsed_params, "toxicity_reduction");
	if(!found)
	{
		new_GameState->toxicity_reduction = .1;//default value from .gd
	}
	found = utils_int_from_parsed(&(new_GameState->energy), parsed_params, "energy");
	if(!found)
	{
		new_GameState->energy = 0;//default value from .gd
	}
	found = utils_int_from_parsed(&(new_GameState->energy_income), parsed_params, "energy_income");
	if(!found)
	{
		new_GameState->energy_income = 10;//default value from .gd
	}
	found = utils_int_from_parsed(&(new_GameState->selected_building), parsed_params, "selected_building");
	if(!found)
	{
		new_GameState->selected_building = 0;//default value from .gd
	}
	iCluige.iDeque.deque_alloc(&(new_GameState->all_buildings), VT_POINTER, 3);
	new_GameState->camera = NULL;
	new_GameState->ui_bar = NULL;
	found = utils_float_from_parsed(&(new_GameState->day_duration), parsed_params, "day_duration");
	if(!found)
	{
		new_GameState->day_duration = 1;//default value from .gd
	}
	new_GameState->time_passed = 0;
	new_GameState->current_day = 1;

	//plug virtual mehods
	new_GameState->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_GameState;
	new_Script->process = process_GameState;
	new_Script->ready = ready_GameState;
	return new_Script;
}

void register_GameStateFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_GameState;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/game_state", sf);
}

void delete_GameState(Script* this_Script)
{
	GameState* this_GameState =
			(GameState*)(this_Script->_sub_class);
	iCluige.iDeque.pre_delete_Deque(&(this_GameState->all_buildings));
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_GameState->_delete_super;
	free(this_GameState);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

void set_energy_income(GameState* this_GameState, int new_income)
{
    this_GameState->energy_income = new_income;
    update_energy_income_label(this_GameState->ui_bar, new_income);
}

void add_to_energy_storage(GameState* this_GameState, int added_energy)
{
    this_GameState->energy += added_energy;
    update_energy_stored_label(this_GameState->ui_bar, this_GameState->energy);
}

void take_from_energy_storage(GameState* this_GameState, int taken_energy)
{
    this_GameState->energy -= taken_energy;
    update_energy_stored_label(this_GameState->ui_bar, this_GameState->energy);
}

void remove_acidity(GameState* this_GameState, float removed_acidity)
{
    this_GameState->toxicity -= removed_acidity;
    update_acidity_level_label(this_GameState->ui_bar, this_GameState->toxicity);
}

void set_acidity_change(GameState* this_GameState, float new_acidity_change)
{
    this_GameState->toxicity_reduction = new_acidity_change;
    update_acidity_change_label(this_GameState->ui_bar, new_acidity_change);
}

void _update_toxicity(GameState* this_GameState){
    remove_acidity(this_GameState, this_GameState->toxicity_reduction);
}

void _update_energy(GameState* this_GameState){
    add_to_energy_storage(this_GameState, this_GameState->energy_income);
}

void _on_day_timeout(GameState* this_GameState){
    this_GameState->time_passed = 0;
    this_GameState->current_day++;
    update_displayed_date(this_GameState->ui_bar, this_GameState->current_day);

    _update_toxicity(this_GameState);
    _update_energy(this_GameState);
}

void set_ui(GameState* this_GameState){
	update_acidity_level_label(this_GameState->ui_bar, this_GameState->toxicity);
	update_acidity_change_label(this_GameState->ui_bar, this_GameState->toxicity_reduction);
	update_energy_income_label(this_GameState->ui_bar, this_GameState->energy_income);
	update_energy_stored_label(this_GameState->ui_bar, this_GameState->energy);
	update_displayed_date(this_GameState->ui_bar, this_GameState->current_day);
	set_message(this_GameState->ui_bar, "Welcome to Venus! Deadly rain of sulfuric acid was found to be bad for colonists health. Get rid of it! The acid of course, the rain can stay.");
}

void process_GameState(Script* this_Script, float delta)
{
    // Handling time passing
	GameState* this_GameState = (GameState*)(this_Script->_sub_class);
	this_GameState->time_passed+=delta;
	if (this_GameState->time_passed > this_GameState->day_duration){
        _on_day_timeout(this_GameState);
	}

	int selec = this_GameState->selected_building;
	Deque* bb = &(this_GameState->all_buildings);
	Building* b = (Building*)iCluige.iDeque.at(bb, selec).ptr;
	int nbb = iCluige.iDeque.size(bb);
	int ok_action = iCluige.iInput.action_id_from_name("ok", true);
	int left_action = iCluige.iInput.action_id_from_name("left", true);
	int right_action = iCluige.iInput.action_id_from_name("right", true);
	int up_action = iCluige.iInput.action_id_from_name("up", true);
	int down_action = iCluige.iInput.action_id_from_name("down", true);
	int exit_action = iCluige.iInput.action_id_from_name("exit", true);
	if(iCluige.iInput.is_action_just_pressed(ok_action))
	{
		applySelectedUpgrade(b);
	}
	if(iCluige.iInput.is_action_just_pressed(left_action))
	{
		this_GameState->selected_building = (selec - 1) % nbb;
		update_selected_building_label(
			this_GameState->ui_bar, b->title);
		start_moving(this_GameState->camera);
	}
	if(iCluige.iInput.is_action_just_pressed(right_action))
	{
		this_GameState->selected_building = (selec + 1) % nbb;
		update_selected_building_label(
			this_GameState->ui_bar, b->title);
		start_moving(this_GameState->camera);
	}
	if(iCluige.iInput.is_action_just_pressed(up_action))
	{
		select_up(b);
	}
	if(iCluige.iInput.is_action_just_pressed(down_action))
	{
		select_down(b);
	}
	if(iCluige.iInput.is_action_just_pressed(exit_action))
	{
		iCluige.quit_asked = true;
	}
//	Node2D* this_Node2D = (Node2D*)(this_Script->node->_sub_class);
}

void ready_GameState(Script* this_Script)
{
	GameState* this_GameState = (GameState*)(this_Script->_sub_class);
	Node* this_Node = this_Script->node;
	Node* n = iCluige.iNode.get_node(this_Node, "../Windmills");
	Building* b = (Building*)(n->script->_sub_class);
	iCluige.iDeque.push_back(&(this_GameState->all_buildings), b);
	n = iCluige.iNode.get_node(this_Node, "../bacteria_factory");
	b = (Building*)(n->script->_sub_class);
	iCluige.iDeque.push_back(&(this_GameState->all_buildings), b);
	n = iCluige.iNode.get_node(this_Node, "../Camera2D");
	this_GameState->camera = (OurCamera*)(n->script->_sub_class);
	n = iCluige.iNode.get_node(this_Node, "../Camera2D/ui_bar");
	this_GameState->ui_bar = (BarreUI*)(n->script->_sub_class);

	set_ui(this_GameState);
}


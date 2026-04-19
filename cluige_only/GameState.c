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
}

void process_GameState(Script* this_Script, float delta)
{//TODO
//	GameState* this_GameState = (GameState*)(this_Script->_sub_class);
//	if(iCluige.iInput.is_action_just_pressed(UP))
//	{
//		...
//	}
//	Node2D* this_Node2D = (Node2D*)(this_Script->node->_sub_class);
//	iCluige.iNode2D.move_local(this_Node2D, (Vector2){dx * delta, dy * delta});
}

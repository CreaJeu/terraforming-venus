#include <cluige.h>
#include "ProduceMoreBacteria.h"
#include "BarreUI.h"

void ready_ProduceMoreBacteria(Script* this_Script);
static void exit_tree(Script*);

Script* instantiate_ProduceMoreBacteria(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	ProduceMoreBacteria* new_ProduceMoreBacteria = iCluige.checked_malloc(sizeof(ProduceMoreBacteria));
	new_Script->_sub_class = new_ProduceMoreBacteria;

	//instantiate fields
	bool found;
	found = utils_float_from_parsed(&(new_ProduceMoreBacteria->bacteria_reduction_improvement), parsed_params, "bacteria_reduction_improvement");
	if(!found)
	{
		new_ProduceMoreBacteria->bacteria_reduction_improvement = .1;//default value from .gd
	}

//	found = utils_bool_from_parsed(&(new_ProduceMoreBacteria->selected), parsed_params, "selected");
//	if(!found)
//	{
		new_ProduceMoreBacteria->selected = false;//default value from .gd
//	}


	//plug virtual mehods
	new_ProduceMoreBacteria->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_ProduceMoreBacteria;
	new_Script->ready = ready_ProduceMoreBacteria;
	new_Script->exit_tree = exit_tree;
	return new_Script;
}

void register_ProduceMoreBacteriaFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_ProduceMoreBacteria;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/upgrades/produce_more_bacteria", sf);
}

void delete_ProduceMoreBacteria(Script* this_Script)
{
	ProduceMoreBacteria* this_ProduceMoreBacteria =
			(ProduceMoreBacteria*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_ProduceMoreBacteria->_delete_super;
	free(this_ProduceMoreBacteria);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

void ready_ProduceMoreBacteria(Script* this_Script)
{
	ProduceMoreBacteria* this_ProduceMoreBacteria = (ProduceMoreBacteria*)(this_Script->_sub_class);
	Node* root = iCluige.public_root_2D;
	Node* gamestate_Node = iCluige.iNode.get_node(root, "main_Node/gameState_Node");
	this_ProduceMoreBacteria->gamestate = (GameState*)gamestate_Node->script->_sub_class;
}

//bool apply_ProduceMoreBacteria(ProduceMoreBacteria* this_ProduceMoreBacteria, GameState* gamestate)
static void exit_tree(Script* this_Script)
{
	ProduceMoreBacteria* this_ProduceMoreBacteria = (ProduceMoreBacteria*)(this_Script->_sub_class);
	GameState* gs = this_ProduceMoreBacteria->gamestate;
    set_acidity_change(gs, gs->toxicity_reduction + this_ProduceMoreBacteria->bacteria_reduction_improvement);
    set_message(gs->ui_bar, "Shoking bacteria with a lot of electricity surprisingly makes more of them. That was definetly why we tried that.");
}

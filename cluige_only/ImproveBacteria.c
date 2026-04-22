#include <cluige.h>
#include "ImproveBacteria.h"
#include "BarreUI.h"

void ready_ImproveBacteria(Script* this_Script);
static void exit_tree(Script*);

Script* instantiate_ImproveBacteria(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	ImproveBacteria* new_ImproveBacteria = iCluige.checked_malloc(sizeof(ImproveBacteria));
	new_Script->_sub_class = new_ImproveBacteria;

	//instantiate fields
	bool found;
	found = utils_int_from_parsed(&(new_ImproveBacteria->acidity_reduction_modifier), parsed_params, "acidity_reduction_modifier");
	if(!found)
	{
		new_ImproveBacteria->acidity_reduction_modifier = 2;//default value from .gd
	}

//	found = utils_bool_from_parsed(&(new_ImproveBacteria->selected), parsed_params, "selected");
//	if(!found)
//	{
		new_ImproveBacteria->selected = false;//default value from .gd
//	}


	//plug virtual mehods
	new_ImproveBacteria->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_ImproveBacteria;
	new_Script->ready = ready_ImproveBacteria;
	new_Script->exit_tree = exit_tree;
	return new_Script;
}

void register_ImproveBacteriaFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_ImproveBacteria;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/upgrades/improve_bacteria", sf);
}

void delete_ImproveBacteria(Script* this_Script)
{
	ImproveBacteria* this_ImproveBacteria =
			(ImproveBacteria*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_ImproveBacteria->_delete_super;
	free(this_ImproveBacteria);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

void ready_ImproveBacteria(Script* this_Script)
{
	ImproveBacteria* this_ImproveBacteria = (ImproveBacteria*)(this_Script->_sub_class);
	Node* root = iCluige.public_root_2D;
	Node* gamestate_Node = iCluige.iNode.get_node(root, "main_Node/gameState_Node");
	this_ImproveBacteria->gamestate = (GameState*)gamestate_Node->script->_sub_class;
}

//bool apply_ImproveBacteria(ImproveBacteria* this_ImproveBacteria, GameState* gamestate)
static void exit_tree(Script* this_Script)
{
	ImproveBacteria* this_ImproveBacteria = (ImproveBacteria*)(this_Script->_sub_class);
	GameState* gs = this_ImproveBacteria->gamestate;
    set_acidity_change(gs, gs->toxicity_reduction * this_ImproveBacteria->acidity_reduction_modifier);
    set_message(gs->ui_bar, "This energy actually went into a lot of research to improve bacteria's genetics. What did you think we would do with it?");
}

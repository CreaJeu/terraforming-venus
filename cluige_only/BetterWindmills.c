#include <cluige.h>
#include "BetterWindmills.h"
#include "BarreUI.h"

void ready_BetterWindmills(Script* this_Script);
static void exit_tree(Script*);

Script* instantiate_BetterWindmills(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	BetterWindmills* new_BetterWindmills = iCluige.checked_malloc(sizeof(BetterWindmills));
	new_Script->_sub_class = new_BetterWindmills;

	//instantiate fields
	bool found;
	found = utils_float_from_parsed(&(new_BetterWindmills->energy_multiplier), parsed_params, "energy_multiplier");
	if(!found)
	{
		new_BetterWindmills->energy_multiplier = 2;//default value from .gd
	}

//	found = utils_bool_from_parsed(&(new_BetterWindmills->selected), parsed_params, "selected");
//	if(!found)
//	{
		new_BetterWindmills->selected = false;//default value from .gd
//	}


	//plug virtual mehods
	new_BetterWindmills->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_BetterWindmills;
	new_Script->ready = ready_BetterWindmills;
	new_Script->exit_tree = exit_tree;
	return new_Script;
}

void register_BetterWindmillsFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_BetterWindmills;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/upgrades/better_windmills", sf);
}

void delete_BetterWindmills(Script* this_Script)
{
	BetterWindmills* this_BetterWindmills =
			(BetterWindmills*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_BetterWindmills->_delete_super;
	free(this_BetterWindmills);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

void ready_BetterWindmills(Script* this_Script)
{
	BetterWindmills* this_BetterWindmills = (BetterWindmills*)(this_Script->_sub_class);
	Node* root = iCluige.public_root_2D;
	Node* gamestate_Node = iCluige.iNode.get_node(root, "main_Node/gameState_Node");
	this_BetterWindmills->gamestate = (GameState*)gamestate_Node->script->_sub_class;
}

//bool apply_BetterWindmills(BetterWindmills* this_BetterWindmills, GameState* gamestate)
static void exit_tree(Script* this_Script)
{
	BetterWindmills* this_BetterWindmills = (BetterWindmills*)(this_Script->_sub_class);
	GameState* gs = this_BetterWindmills->gamestate;
    set_energy_income(gs, (int)(gs->energy_income * this_BetterWindmills->energy_multiplier));
    set_message(gs->ui_bar, "The windmills now have a motor making them spin extra fast to produce more energy");
}

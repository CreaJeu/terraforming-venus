#include <cluige.h>
#include "MoreWindmills.h"

void ready_MoreWindmills(Script* this_Script);

Script* instantiate_MoreWindmills(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	MoreWindmills* new_MoreWindmills = iCluige.checked_malloc(sizeof(MoreWindmills));
	new_Script->_sub_class = new_MoreWindmills;

	//instantiate fields
	bool found;
	found = utils_int_from_parsed(&(new_MoreWindmills->additional_energy), parsed_params, "additional_energy");
	if(!found)
	{
		new_MoreWindmills->additional_energy = 10;//default value from .gd
	}

	found = utils_int_from_parsed(&(new_MoreWindmills->price), parsed_params, "price");
	if(!found)
	{
		new_MoreWindmills->price = 100;//default value from .gd
	}

	found = utils_bool_from_parsed(&(new_MoreWindmills->selected), parsed_params, "selected");
	if(!found)
	{
		new_MoreWindmills->selected = false;//default value from .gd
	}


	//plug virtual mehods
	new_MoreWindmills->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_MoreWindmills;
//	new_Script->process = process_MoreWindmills;
	return new_Script;
}

void register_MoreWindmillsFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_MoreWindmills;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/upgrades/more_windmills", sf);
}

void delete_MoreWindmills(Script* this_Script)
{
	MoreWindmills* this_MoreWindmills =
			(MoreWindmills*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_MoreWindmills->_delete_super;
	free(this_MoreWindmills);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

void ready_MoreWindmills(Script* this_Script)
{
	MoreWindmills* this_MoreWindmills = (MoreWindmills*)(this_Script->_sub_class);
	Node* root = iCluige.public_root_2D;
	Node* gamestate_Node = iCluige.iNode.get_node(root, "gameState_Node");
	this_MoreWindmills->gamestate = (GameState*)gamestate_Node->script;
}

bool apply_MoreWindmills(MoreWindmills* this_MoreWindmills, GameState* gamestate)
{
    if (gamestate->energy < this_MoreWindmills->price){
        set_message(gamestate->ui_bar, "Not enough energy for this upgrade.");
        return false;
    }
    take_from_energy_storage(gamestate, this_MoreWindmills->price);
    set_energy_income(gamestate, gamestate->energy_income+this_MoreWindmills->additional_energy);
    set_message("More windmills = More energy. Luckily there is no lack of wind on Venus.");

    return true;
}

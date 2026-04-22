#include <cluige.h>
#include "SuperBacteria.h"
#include "BarreUI.h"

void ready_SuperBacteria(Script* this_Script);
static void exit_tree(Script*);

Script* instantiate_SuperBacteria(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	SuperBacteria* new_SuperBacteria = iCluige.checked_malloc(sizeof(SuperBacteria));
	new_Script->_sub_class = new_SuperBacteria;

	//instantiate fields
	bool found;
	found = utils_int_from_parsed(&(new_SuperBacteria->acidity_reduction), parsed_params, "acidity_reduction");
	if(!found)
	{
		new_SuperBacteria->acidity_reduction = 10;//default value from .gd
	}

//	found = utils_bool_from_parsed(&(new_SuperBacteria->selected), parsed_params, "selected");
//	if(!found)
//	{
		new_SuperBacteria->selected = false;//default value from .gd
//	}


	//plug virtual mehods
	new_SuperBacteria->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_SuperBacteria;
	new_Script->ready = ready_SuperBacteria;
	new_Script->exit_tree = exit_tree;
	return new_Script;
}

void register_SuperBacteriaFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_SuperBacteria;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/upgrades/super_bacteria", sf);
}

void delete_SuperBacteria(Script* this_Script)
{
	SuperBacteria* this_SuperBacteria =
			(SuperBacteria*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_SuperBacteria->_delete_super;
	free(this_SuperBacteria);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

void ready_SuperBacteria(Script* this_Script)
{
	SuperBacteria* this_SuperBacteria = (SuperBacteria*)(this_Script->_sub_class);
	Node* root = iCluige.public_root_2D;
	Node* gamestate_Node = iCluige.iNode.get_node(root, "main_Node/gameState_Node");
	this_SuperBacteria->gamestate = (GameState*)gamestate_Node->script->_sub_class;
}

//bool apply_SuperBacteria(SuperBacteria* this_SuperBacteria, GameState* gamestate)
static void exit_tree(Script* this_Script)
{
	SuperBacteria* this_SuperBacteria = (SuperBacteria*)(this_Script->_sub_class);
	GameState* gs = this_SuperBacteria->gamestate;
    remove_acidity(gs, this_SuperBacteria->acidity_reduction);
    set_message(gs->ui_bar, "Our scientists cultivated a gigantic bacteria to help cleanse the rain. It broke the containment and ate a ton of sulfuric acid before dying.");
}

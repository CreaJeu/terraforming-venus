#include <cluige.h>
#include "BetterWindmills.h"


Script* instantiate_BetterWindmills(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	BetterWindmills* new_BetterWindmills = iCluige.checked_malloc(sizeof(BetterWindmills));
	new_Script->_sub_class = new_BetterWindmills;

	//instantiate fields
//	bool found = utils_float_from_parsed(&(new_BetterWindmills->speed), parsed_params, "speed");
//	if(!found)
//	{
//		new_BetterWindmills->speed = 3;//default value from .gd
//	}

	//plug virtual mehods
	new_BetterWindmills->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_BetterWindmills;
//	new_Script->process = process_BetterWindmills;
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

//void process_BetterWindmills(Script* this_Script, float delta)
//{
//	BetterWindmills* this_BetterWindmills = (BetterWindmills*)(this_Script->_sub_class);
//	if(iCluige.iInput.is_action_just_pressed(UP))
//	{
//		...
//	}
//	Node2D* this_Node2D = (Node2D*)(this_Script->node->_sub_class);
//	iCluige.iNode2D.move_local(this_Node2D, (Vector2){dx * delta, dy * delta});
//}

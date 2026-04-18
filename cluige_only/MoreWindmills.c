#include <cluige.h>
#include "MoreWindmills.h"


Script* instantiate_MoreWindmills(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	MoreWindmills* new_MoreWindmills = iCluige.checked_malloc(sizeof(MoreWindmills));
	new_Script->_sub_class = new_MoreWindmills;

	//instantiate fields
//	bool found = utils_float_from_parsed(&(new_MoreWindmills->speed), parsed_params, "speed");
//	if(!found)
//	{
//		new_MoreWindmills->speed = 3;//default value from .gd
//	}

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

//void process_MoreWindmills(Script* this_Script, float delta)
//{
//	MoreWindmills* this_MoreWindmills = (MoreWindmills*)(this_Script->_sub_class);
//	if(iCluige.iInput.is_action_just_pressed(UP))
//	{
//		...
//	}
//	Node2D* this_Node2D = (Node2D*)(this_Script->node->_sub_class);
//	iCluige.iNode2D.move_local(this_Node2D, (Vector2){dx * delta, dy * delta});
//}

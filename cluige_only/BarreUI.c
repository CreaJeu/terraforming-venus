#include <cluige.h>
#include "BarreUI.h"


Script* instantiate_BarreUI(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	BarreUI* new_BarreUI = iCluige.checked_malloc(sizeof(BarreUI));
	new_Script->_sub_class = new_BarreUI;

	//instantiate fields
//	bool found = utils_float_from_parsed(&(new_BarreUI->speed), parsed_params, "speed");
//	if(!found)
//	{
//		new_BarreUI->speed = 3;//default value from .gd
//	}

	//plug virtual mehods
	new_BarreUI->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_BarreUI;
//	new_Script->process = process_BarreUI;
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

//void process_BarreUI(Script* this_Script, float delta)
//{
//	BarreUI* this_BarreUI = (BarreUI*)(this_Script->_sub_class);
//	if(iCluige.iInput.is_action_just_pressed(UP))
//	{
//		...
//	}
//	Node2D* this_Node2D = (Node2D*)(this_Script->node->_sub_class);
//	iCluige.iNode2D.move_local(this_Node2D, (Vector2){dx * delta, dy * delta});
//}

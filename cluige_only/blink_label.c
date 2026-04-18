#include <cluige.h>
#include "blink_label.h"


Script* instantiate_BlinkLabel(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	BlinkLabel* new_BlinkLabel = iCluige.checked_malloc(sizeof(BlinkLabel));
	new_Script->_sub_class = new_BlinkLabel;

	//instantiate fields
//	bool found = utils_float_from_parsed(&(new_BlinkLabel->speed), parsed_params, "speed");
//	if(!found)
//	{
//		new_BlinkLabel->speed = 3;//default value from .gd
//	}

	//plug virtual mehods
	new_BlinkLabel->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_BlinkLabel;
//	new_Script->process = process_BlinkLabel;
	return new_Script;
}

void register_BlinkLabelFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_BlinkLabel;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/blink_label", sf);
}

void delete_BlinkLabel(Script* this_Script)
{
	BlinkLabel* this_BlinkLabel =
			(BlinkLabel*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_BlinkLabel->_delete_super;
	free(this_BlinkLabel);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

//void process_BlinkLabel(Script* this_Script, float delta)
//{
//	BlinkLabel* this_BlinkLabel = (BlinkLabel*)(this_Script->_sub_class);
//	if(iCluige.iInput.is_action_just_pressed(UP))
//	{
//		...
//	}
//	Node2D* this_Node2D = (Node2D*)(this_Script->node->_sub_class);
//	iCluige.iNode2D.move_local(this_Node2D, (Vector2){dx * delta, dy * delta});
//}

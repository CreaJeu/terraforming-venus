#include <cluige.h>
#include "Rain.h"


Script* instantiate_Rain(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	Rain* new_Rain = iCluige.checked_malloc(sizeof(Rain));
	new_Script->_sub_class = new_Rain;

	//instantiate fields
//	bool found = utils_float_from_parsed(&(new_Rain->speed), parsed_params, "speed");
//	if(!found)
//	{
//		new_Rain->speed = 3;//default value from .gd
//	}

	//plug virtual mehods
	new_Rain->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_Rain;
//	new_Script->process = process_Rain;
	return new_Script;
}

void register_RainFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_Rain;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/rain", sf);
}

void delete_Rain(Script* this_Script)
{
	Rain* this_Rain =
			(Rain*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_Rain->_delete_super;
	free(this_Rain);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

//void process_Rain(Script* this_Script, float delta)
//{
//	Rain* this_Rain = (Rain*)(this_Script->_sub_class);
//	if(iCluige.iInput.is_action_just_pressed(UP))
//	{
//		...
//	}
//	Node2D* this_Node2D = (Node2D*)(this_Script->node->_sub_class);
//	iCluige.iNode2D.move_local(this_Node2D, (Vector2){dx * delta, dy * delta});
//}

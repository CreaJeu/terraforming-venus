#include <cluige.h>
#include "Building.h"


Script* instantiate_Building(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	Building* new_Building = iCluige.checked_malloc(sizeof(Building));
	new_Script->_sub_class = new_Building;

	//instantiate fields
//	bool found = utils_float_from_parsed(&(new_Building->speed), parsed_params, "speed");
//	if(!found)
//	{
//		new_Building->speed = 3;//default value from .gd
//	}

	//plug virtual mehods
	new_Building->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_Building;
//	new_Script->process = process_Building;
	return new_Script;
}

void register_BuildingFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_Building;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/building", sf);
}

void delete_Building(Script* this_Script)
{
	Building* this_Building =
			(Building*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_Building->_delete_super;
	free(this_Building);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

//void process_Building(Script* this_Script, float delta)
//{
//	Building* this_Building = (Building*)(this_Script->_sub_class);
//	if(iCluige.iInput.is_action_just_pressed(UP))
//	{
//		...
//	}
//	Node2D* this_Node2D = (Node2D*)(this_Script->node->_sub_class);
//	iCluige.iNode2D.move_local(this_Node2D, (Vector2){dx * delta, dy * delta});
//}

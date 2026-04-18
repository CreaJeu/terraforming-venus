#include <cluige.h>
#include "SuperBacteria.h"


Script* instantiate_SuperBacteria(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	SuperBacteria* new_SuperBacteria = iCluige.checked_malloc(sizeof(SuperBacteria));
	new_Script->_sub_class = new_SuperBacteria;

	//instantiate fields
//	bool found = utils_float_from_parsed(&(new_SuperBacteria->speed), parsed_params, "speed");
//	if(!found)
//	{
//		new_SuperBacteria->speed = 3;//default value from .gd
//	}

	//plug virtual mehods
	new_SuperBacteria->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_SuperBacteria;
//	new_Script->process = process_SuperBacteria;
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

//void process_SuperBacteria(Script* this_Script, float delta)
//{
//	SuperBacteria* this_SuperBacteria = (SuperBacteria*)(this_Script->_sub_class);
//	if(iCluige.iInput.is_action_just_pressed(UP))
//	{
//		...
//	}
//	Node2D* this_Node2D = (Node2D*)(this_Script->node->_sub_class);
//	iCluige.iNode2D.move_local(this_Node2D, (Vector2){dx * delta, dy * delta});
//}

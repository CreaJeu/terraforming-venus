#include <cluige.h>
#include "ProduceMoreBacteria.h"


Script* instantiate_ProduceMoreBacteria(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	ProduceMoreBacteria* new_ProduceMoreBacteria = iCluige.checked_malloc(sizeof(ProduceMoreBacteria));
	new_Script->_sub_class = new_ProduceMoreBacteria;

	//instantiate fields
//	bool found = utils_float_from_parsed(&(new_ProduceMoreBacteria->speed), parsed_params, "speed");
//	if(!found)
//	{
//		new_ProduceMoreBacteria->speed = 3;//default value from .gd
//	}

	//plug virtual mehods
	new_ProduceMoreBacteria->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_ProduceMoreBacteria;
//	new_Script->process = process_ProduceMoreBacteria;
	return new_Script;
}

void register_ProduceMoreBacteriaFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_ProduceMoreBacteria;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/upgrades/produce_more_bacteria", sf);
}

void delete_ProduceMoreBacteria(Script* this_Script)
{
	ProduceMoreBacteria* this_ProduceMoreBacteria =
			(ProduceMoreBacteria*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_ProduceMoreBacteria->_delete_super;
	free(this_ProduceMoreBacteria);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

//void process_ProduceMoreBacteria(Script* this_Script, float delta)
//{
//	ProduceMoreBacteria* this_ProduceMoreBacteria = (ProduceMoreBacteria*)(this_Script->_sub_class);
//	if(iCluige.iInput.is_action_just_pressed(UP))
//	{
//		...
//	}
//	Node2D* this_Node2D = (Node2D*)(this_Script->node->_sub_class);
//	iCluige.iNode2D.move_local(this_Node2D, (Vector2){dx * delta, dy * delta});
//}

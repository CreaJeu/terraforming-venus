#include <cluige.h>
#include "ImproveBacteria.h"


Script* instantiate_ImproveBacteria(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	ImproveBacteria* new_ImproveBacteria = iCluige.checked_malloc(sizeof(ImproveBacteria));
	new_Script->_sub_class = new_ImproveBacteria;

	//instantiate fields
//	bool found = utils_float_from_parsed(&(new_ImproveBacteria->speed), parsed_params, "speed");
//	if(!found)
//	{
//		new_ImproveBacteria->speed = 3;//default value from .gd
//	}

	//plug virtual mehods
	new_ImproveBacteria->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_ImproveBacteria;
//	new_Script->process = process_ImproveBacteria;
	return new_Script;
}

void register_ImproveBacteriaFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_ImproveBacteria;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/upgrades/improve_bacteria", sf);
}

void delete_ImproveBacteria(Script* this_Script)
{
	ImproveBacteria* this_ImproveBacteria =
			(ImproveBacteria*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_ImproveBacteria->_delete_super;
	free(this_ImproveBacteria);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

//void process_ImproveBacteria(Script* this_Script, float delta)
//{
//	ImproveBacteria* this_ImproveBacteria = (ImproveBacteria*)(this_Script->_sub_class);
//	if(iCluige.iInput.is_action_just_pressed(UP))
//	{
//		...
//	}
//	Node2D* this_Node2D = (Node2D*)(this_Script->node->_sub_class);
//	iCluige.iNode2D.move_local(this_Node2D, (Vector2){dx * delta, dy * delta});
//}

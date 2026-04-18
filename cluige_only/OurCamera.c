#include <cluige.h>
#include "OurCamera.h"


Script* instantiate_OurCamera(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	OurCamera* new_OurCamera = iCluige.checked_malloc(sizeof(OurCamera));
	new_Script->_sub_class = new_OurCamera;

	//instantiate fields
//	bool found = utils_float_from_parsed(&(new_OurCamera->speed), parsed_params, "speed");
//	if(!found)
//	{
//		new_OurCamera->speed = 3;//default value from .gd
//	}

	//plug virtual mehods
	new_OurCamera->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_OurCamera;
//	new_Script->process = process_OurCamera;
	return new_Script;
}

void register_OurCameraFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_OurCamera;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/OurCamera", sf);
}

void delete_OurCamera(Script* this_Script)
{
	OurCamera* this_OurCamera =
			(OurCamera*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_OurCamera->_delete_super;
	free(this_OurCamera);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

//void process_OurCamera(Script* this_Script, float delta)
//{
//	OurCamera* this_OurCamera = (OurCamera*)(this_Script->_sub_class);
//	if(iCluige.iInput.is_action_just_pressed(UP))
//	{
//		...
//	}
//	Node2D* this_Node2D = (Node2D*)(this_Script->node->_sub_class);
//	iCluige.iNode2D.move_local(this_Node2D, (Vector2){dx * delta, dy * delta});
//}

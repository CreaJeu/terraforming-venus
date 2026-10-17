#include <cluige.h>
#include "Landscape.h"

void ready_Landscape(Script* this_script);

Node2D* camera_Node2D;
float building_x_dist;
float parallax_max_x;

Script* instantiate_Landscape(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	Landscape* new_Landscape = iCluige.checked_malloc(sizeof(Landscape));
	new_Script->_sub_class = new_Landscape;

	//instantiate fields

	//plug virtual mehods
	new_Landscape->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_Landscape;
	new_Script->process = process_Landscape;
	new_Script->ready = ready_Landscape;
	return new_Script;
}

void register_LandscapeFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_Landscape;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/landscape", sf);
}

void delete_Landscape(Script* this_Script)
{
	Landscape* this_Landscape =
			(Landscape*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_Landscape->_delete_super;
	free(this_Landscape);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

void ready_Landscape(Script* this_Script)
{
	//Landscape* this_Landscape = (Landscape*)(this_Script->_sub_class);
	Node* this_Node = this_Script->node;

	Node* building_last_Node = iCluige.iNode.get_node(this_Node, "../bacteria_factory", true);
	Node2D* building_last_Node2D = iCluige.iNode2D.cast_from_Node(building_last_Node);

	Node* camera_Node = iCluige.iNode.get_node(this_Node, "../Camera2D", true);
	camera_Node2D = iCluige.iNode2D.cast_from_Node(camera_Node);

	building_x_dist = building_last_Node2D->position.x;
	parallax_max_x = building_x_dist - 65;
}

void process_Landscape(Script* this_Script, float delta)
{
	//Landscape* this_Landscape = (Landscape*)(this_Script->_sub_class);
	Node* this_Node = this_Script->node;
	Node2D* this_Node2D = iCluige.iNode2D.cast_from_Node(this_Node);

	float cam_x = camera_Node2D->position.x;
	float ratio = cam_x / building_x_dist;
	float new_x = ratio * parallax_max_x;
	float y = this_Node2D->position.y;
	iCluige.iNode2D.set_local_position(this_Node2D, (Vector2){new_x, y});
}

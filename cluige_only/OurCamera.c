#include <cluige.h>
#include "OurCamera.h"
#include "GameState.h"
#include "Building.h"

void process_OurCamera(Script* this_Script, float delta);
void ready_OurCamera(Script* this_Script);

Script* instantiate_OurCamera(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	OurCamera* new_OurCamera = iCluige.checked_malloc(sizeof(OurCamera));
	new_Script->_sub_class = new_OurCamera;

	//instantiate fields
	bool found = utils_float_from_parsed(&(new_OurCamera->MOVE_TIME), parsed_params, "speed");
	if(!found)
	{
		new_OurCamera->MOVE_TIME = .5;//default value from .gd
	}
	new_OurCamera->time_till_arrived = .5;
	new_OurCamera->gs = NULL;

	//plug virtual mehods
	new_OurCamera->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_OurCamera;
	new_Script->process = process_OurCamera;
	new_Script->ready = ready_OurCamera;
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
	OurCamera* this_OurCamera = (OurCamera*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_OurCamera->_delete_super;
	free(this_OurCamera);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

void ready_OurCamera(Script* this_Script)
{
//	gs = $"../gameState_Node"
	Node* this_Node = this_Script->node;
	OurCamera* this_OurCamera = (OurCamera*)(this_Script->_sub_class);

	Node* n = iCluige.iNode.get_node(this_Node, "../gameState_Node");
	this_OurCamera->gs = (GameState*)n->script->_sub_class;

//	make_current()
	Node2D* this_Node2D = (Node2D*)(this_Node->_sub_class);
	Camera2D* this_Camera2D = (Camera2D*)(this_Node2D->_sub_class);
	iCluige.iCamera2D.make_current(this_Camera2D);
}

void process_OurCamera(Script* this_Script, float delta)
{
	OurCamera* this_OurCamera = (OurCamera*)(this_Script->_sub_class);

//	Node2D* this_Node2D = (Node2D*)(this_Script->node->_sub_class);
//	iCluige.iNode2D.move_local(this_Node2D, (Vector2){dx * delta, dy * delta});

//	if(time_till_arrived > 0):
	if(this_OurCamera->time_till_arrived > 0)
	{
//		var b: Building = gs.all_buildings[gs.selected_building]
		Deque* all_b = &(this_OurCamera->gs->all_buildings);
		Building* b = (Building*)
				iCluige.iDeque.at(all_b, this_OurCamera->gs->selected_building).ptr;
		//Node2D* bn2d = b-> TODO
//		if(delta < time_till_arrived):
		if(delta < this_OurCamera->time_till_arrived)
		{
//			var whole_move = b.position - position
			//Vector2 whole_move;
			//iCluige.iVector2.substract()
//			var ratio: float = delta / time_till_arrived
//			time_till_arrived -= delta
//			translate(whole_move * ratio)
		}
//		else:
//			time_till_arrived = 0
//			position = b.position
	}
}

void start_moving(OurCamera* this_OurCamera)
{
//	time_till_arrived = MOVE_TIME
	this_OurCamera->time_till_arrived = this_OurCamera->MOVE_TIME;
}


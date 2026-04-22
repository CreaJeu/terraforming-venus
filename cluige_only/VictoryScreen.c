#include <cluige.h>
#include "VictoryScreen.h"
#include "blink_label.h"

void ready_VictoryScreen(Script* this_script);
void process_VictoryScreen(Script* this_Script, float delta);

Node2D* this_Node2D;
Script* this_script;
Script* restart_blink_script;

Script* instantiate_VictoryScreen(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	VictoryScreen* new_VictoryScreen = iCluige.checked_malloc(sizeof(VictoryScreen));
	new_Script->_sub_class = new_VictoryScreen;

	//plug virtual mehods
	new_VictoryScreen->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_VictoryScreen;
	new_Script->ready = ready_VictoryScreen;
	//stay NULL => inactive at first, next see show_VictoryScreen()
//	new_Script->process = process_VictoryScreen;
	return new_Script;
}

void register_VictoryScreenFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_VictoryScreen;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/VictoryScreen", sf);
}

void delete_VictoryScreen(Script* this_Script)
{
	VictoryScreen* this_VictoryScreen =
			(VictoryScreen*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_VictoryScreen->_delete_super;
	free(this_VictoryScreen);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

//because visibility inheritance not yet implemented in cluige
void set_visible_VictoryScreen(bool visible)
{
	Node* n = iCluige.iNode.get_node(this_script->node, "victory_Label");
	Node2D* n2D = (Node2D*)n->_sub_class;
	n2D->visible = visible;
	n = iCluige.iNode.get_node(this_script->node, "restart_Label");
	n2D = (Node2D*)n->_sub_class;
	n2D->visible = visible;
	n = iCluige.iNode.get_node(this_script->node, "Quit_Label");
	n2D = (Node2D*)n->_sub_class;
	n2D->visible = visible;
}

void show_VictoryScreen()
{
	iCluige.iNode2D.show(this_Node2D);
	this_script->process = process_VictoryScreen;
	restart_blink_script->process = process_BlinkLabel;
	set_visible_VictoryScreen(true);
}

void ready_VictoryScreen(Script* this_Script)
{
	this_Node2D = (Node2D*)this_Script->node->_sub_class;
	this_script = this_Script;
	Node* blk = iCluige.iNode.get_node(this_Script->node, "restart_Label/BlinkLabel");
	restart_blink_script = blk->script;
	restart_blink_script->process = NULL;
	set_visible_VictoryScreen(false);
}

void process_VictoryScreen(Script* this_Script, float delta)
{
	Camera2D* cam = iCluige.iCamera2D.current_camera;
	Node2D* cam_n2D = cam->_this_Node2D;
	iCluige.iNode2D.set_local_position(this_Node2D, cam_n2D->position);
}

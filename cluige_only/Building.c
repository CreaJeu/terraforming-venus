#include <cluige.h>
#include "Building.h"
#include "blink_label.h"


Script* instantiate_Building(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	Building* new_Building = iCluige.checked_malloc(sizeof(Building));
	new_Script->_sub_class = new_Building;

	//instantiate fields
	new_Building->title = iCluige.checked_malloc(60 * sizeof(char));
	bool found = utils_str_from_parsed(&(new_Building->title), parsed_params, "title");
	iCluige.iDeque.deque_alloc(&(new_Building->upgrades), VT_POINTER, 5);
	found = utils_int_from_parsed(&(new_Building->selected_upgrade_index), parsed_params, "selected_upgrade_index");
	if(!found)
	{
		new_Building->selected_upgrade_index = 0;//default value from .gd
	}

	//plug virtual mehods
	new_Building->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_Building;
//	new_Script->process = process_Building;
	return new_Script;
}

void make_ui_title_from_text(char* out, char* title)
{
	int char_number = strlen(title) + 2;
	char repeat_sh[char_number+1];
	for(int i=0; i<char_number; i++)
	{
		repeat_sh[i] = '#';
	}
	repeat_sh[char_number] = '\0';
	char repeat_sp[char_number+1];
	for(int i=0; i<char_number; i++)
	{
		repeat_sp[i] = ' ';
	}
	repeat_sp[char_number] = '\0';
	sprintf(out,
"\
#%s#\n\
#%s#\n\
# %s #\n\
#%s#\n\
#%s#",
			repeat_sh,
			repeat_sp,
			title,
			repeat_sp,
			repeat_sh);
}

void select_upgrade(Node* this_Node, int i)
{
	Node* up_n = iCluige.iNode.get_child(this_Node, i);
	Node* label_n = iCluige.iNode.get_node(up_n, "pointer_Label");
	Node2D* label_n2D = (Node2D*)label_n->_sub_class;
	label_n2D->visible = true;

	label_n = iCluige.iNode.get_node(up_n, "buy_Label");
	label_n2D = (Node2D*)label_n->_sub_class;
	label_n2D->visible = true;

	Node* blink = iCluige.iNode.get_node(up_n, "pointer_Label/BlinkLabel");
	blink->script->process = NULL;
}

void deselect_upgrade(Node* this_Node, int i)
{
	Node* up_n = iCluige.iNode.get_child(this_Node, i);
	Node* label_n = iCluige.iNode.get_node(up_n, "pointer_Label");
	Node2D* label_n2D = (Node2D*)label_n->_sub_class;
	label_n2D->visible = false;

	label_n = iCluige.iNode.get_node(up_n, "buy_Label");
	label_n2D = (Node2D*)label_n->_sub_class;
	label_n2D->visible = false;

	Node* blink = iCluige.iNode.get_node(up_n, "pointer_Label/BlinkLabel");
	blink->script->process = process_BlinkLabel;
}

void ready_Building(Script* this_Script)
{
	Building* this_Building = (Building*)(this_Script->_sub_class);
	Node* this_Node = this_Script->node;
	this_Building->_this_Node2D = (Node2D*)this_Node->_sub_class;
	Node* tn = iCluige.iNode.get_node(this_Node, "title_Label");
	Node2D* tn2d = (Node2D*)tn->_sub_class;
	SpriteText* ts = (SpriteText*)tn2d->_sub_class;
	char str[500];
	make_ui_title_from_text(str, this_Building->title);
	iCluige.iSpriteText.set_text(ts, str);
	select_upgrade(this_Node, this_Building->selected_upgrade_index);
	deselect_upgrade(this_Node, 1);//gamejam quick&dirty
	deselect_upgrade(this_Node, 2);
	deselect_upgrade(this_Node, 3);
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
	free(this_Building->title);
	iCluige.iDeque.pre_delete_Deque(&(this_Building->upgrades));
	free(this_Building);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

void applySelectedUpgrade(Building* this_Building)
{
/////TODO
//	Deque* ups = &(this_Building->upgrades);
//	int selec = this_Building->selected_upgrade_index;
//	int nbb = iCluige.iDeque.size(ups);
//	if(nbb == 0)
//	{
//		return;
//	}
//	Building* b = (Building*)iCluige.iDeque.at(ups, selec).ptr;
}

void select_up(Building* this_Building)
{
	Node* this_Node = this_Building->_this_Node2D->_this_Node;
	int selec = this_Building->selected_upgrade_index;
	deselect_upgrade(this_Node, selec);

	Deque* ups = &(this_Building->upgrades);
	int nbb = iCluige.iDeque.size(ups);
	selec = (selec - 1) % nbb;
	this_Building->selected_upgrade_index = selec;

	select_upgrade(this_Node,  selec);
}

void deselect_up(Building* this_Building)
{
	Node* this_Node = this_Building->_this_Node2D->_this_Node;
	int selec = this_Building->selected_upgrade_index;
	deselect_upgrade(this_Node, selec);

	Deque* ups = &(this_Building->upgrades);
	int nbb = iCluige.iDeque.size(ups);
	selec = (selec - 1) % nbb;
	this_Building->selected_upgrade_index = selec;

	select_upgrade(this_Node, selec);
}

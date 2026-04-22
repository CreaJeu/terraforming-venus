#include <cluige.h>
#include "Building.h"
#include "blink_label.h"
#include "UpgradeApplyer.h"
#include <string.h>

void ready_Building(Script* this_Script);

Script* instantiate_Building(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	Building* new_Building = iCluige.checked_malloc(sizeof(Building));
	new_Script->_sub_class = new_Building;

	//instantiate fields
	new_Building->title = iCluige.checked_malloc(60 * sizeof(char));
	bool found = utils_str_from_parsed(&(new_Building->title), parsed_params, "title");
	iCluige.iDeque.deque_alloc(&(new_Building->upgrades_paths), VT_POINTER, 5);
	iCluige.iDeque.deque_alloc(&(new_Building->upgrades), VT_POINTER, 5);
	found = utils_int_from_parsed(&(new_Building->selected_upgrade_index), parsed_params, "selected_upgrade_index");
	if(!found)
	{
		new_Building->selected_upgrade_index = 0;//default value from .gd
	}
	//Array[String](["more_windmills_upgrade", "more_windmills_upgrade2", "more_windmills_upgrade3", "better_windmills_upgrade"])
	char* parsed_list = "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      ";
	found = utils_nonquoted_str_from_parsed(&parsed_list, parsed_params, "upgrades_paths");
	CLUIGE_ASSERT(found, "upgrades_paths not found");
	char* from = strchr(parsed_list, '"');
	while(from != NULL)
	{
		char* to = strchr(++from, '"');
		int non_term_size = to - from;
		char* one_path = iCluige.checked_malloc(sizeof(char) * (non_term_size + 1));
		strncpy(one_path, from, non_term_size);
		one_path[non_term_size] = '\0';
		iCluige.iDeque.push_back(&(new_Building->upgrades_paths), one_path);
		from = strchr(to+1, '"');
	}

	//plug virtual mehods
	new_Building->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_Building;
	new_Script->ready = ready_Building;
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

void select_upgrade(Building* this_Building, int i)
{
//	Node* up_n = iCluige.iNode.get_child(this_Node, i+2);
	this_Building->selected_upgrade_index = i;
	Node* up_n = (Node*)iCluige.iDeque.at(&(this_Building->upgrades), i).ptr;
	Node* label_n = iCluige.iNode.get_node(up_n, "pointer_Label");
	Node2D* label_n2D = (Node2D*)label_n->_sub_class;
	label_n2D->visible = true;

	label_n = iCluige.iNode.get_node(up_n, "buy_Label");
	label_n2D = (Node2D*)label_n->_sub_class;
	label_n2D->visible = true;

	Node* blink = iCluige.iNode.get_node(up_n, "pointer_Label/BlinkLabel");
	blink->script->process = process_BlinkLabel;
}

void deselect_upgrade(Building* this_Building, int i)
{
//	Node* up_n = iCluige.iNode.get_child(this_Node, i+2);
	Node* up_n = (Node*)iCluige.iDeque.at(&(this_Building->upgrades), i).ptr;
	Node* label_n = iCluige.iNode.get_node(up_n, "pointer_Label");
	Node2D* label_n2D = (Node2D*)label_n->_sub_class;
	label_n2D->visible = false;

	label_n = iCluige.iNode.get_node(up_n, "buy_Label");
	label_n2D = (Node2D*)label_n->_sub_class;
	label_n2D->visible = false;

	Node* blink = iCluige.iNode.get_node(up_n, "pointer_Label/BlinkLabel");
	blink->script->process = NULL;
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
	int nbb = iCluige.iDeque.size(&(this_Building->upgrades_paths));
	for(int i=0; i<nbb; i++)
	{
		char* upgr_path_i = (char*)iCluige.iDeque.at(
				&(this_Building->upgrades_paths), i).ptr;
		tn = iCluige.iNode.get_node(this_Node, upgr_path_i);
		iCluige.iDeque.push_back(&(this_Building->upgrades), tn);
		free(upgr_path_i);
	}
	//no more need of upgrades_paths
	iCluige.iDeque.pre_delete_Deque(&(this_Building->upgrades_paths));
	select_upgrade(this_Building, 0);//gamejam quick&dirty
	deselect_upgrade(this_Building, 1);
	deselect_upgrade(this_Building, 2);
	deselect_upgrade(this_Building, 3);
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
	Deque* ups = &(this_Building->upgrades);
	int nbb = iCluige.iDeque.size(ups);
	if(nbb == 0)
	{
		return;
	}
	int selec = this_Building->selected_upgrade_index;
	Node* upgr_node = (Node*)iCluige.iDeque.at(ups, selec).ptr;
	Node* applyer_node = iCluige.iNode.get_node(upgr_node, "applyer_Node");
	UpgradeApplyer* applyer = (UpgradeApplyer*)applyer_node->script->_sub_class;
	if(!apply_upgrade(applyer))
	{
		return;
	}
	iCluige.iDeque.remove(ups, selec);
	if(nbb > 1)
	{
		if(selec >= nbb - 1)
		{
			selec--;
		}
		select_upgrade(this_Building, selec);
	}
}

void select_up(Building* this_Building)
{
	Deque* ups = &(this_Building->upgrades);
	int nbb = iCluige.iDeque.size(ups);
	if(nbb == 0)
	{
		return;
	}
	int selec = this_Building->selected_upgrade_index;
	deselect_upgrade(this_Building, selec);

	selec = selec - 1;
	if(selec < 0)
	{
		selec = nbb - 1;
	}
	select_upgrade(this_Building,  selec);
}

void select_down(Building* this_Building)
{
	Deque* ups = &(this_Building->upgrades);
	int nbb = iCluige.iDeque.size(ups);
	if(nbb == 0)
	{
		return;
	}
	int selec = this_Building->selected_upgrade_index;
	deselect_upgrade(this_Building, selec);

	selec = (selec + 1) % nbb;
	select_upgrade(this_Building, selec);
}

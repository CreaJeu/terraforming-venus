#include <cluige.h>
#include "MainMenu.h"
void process_MainMenu(Script* this_Script, float delta);
Node* instantiate_scene(char* path);


Script* instantiate_MainMenu(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	MainMenu* new_MainMenu = iCluige.checked_malloc(sizeof(MainMenu));
//	new_MainMenu->_this_Node = new_Script->node;
	new_Script->_sub_class = new_MainMenu;

	//plug virtual mehods
	new_MainMenu->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_MainMenu;
	new_Script->process = process_MainMenu;
	return new_Script;
}

void register_MainMenuFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_MainMenu;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/main_menu", sf);
}

void delete_MainMenu(Script* this_Script)
{
	MainMenu* this_MainMenu =
			(MainMenu*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_MainMenu->_delete_super;
	free(this_MainMenu);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

void load_main_scene(Node* this_node){
    char* main_scene_path = "scenes/main.tscn";
    Node* main_scene_node = instantiate_scene(main_scene_path);
    Node* root = iCluige.iNode.get_node(this_node, "..");
    iCluige.iNode.add_child(root, main_scene_node);
    iCluige.iNode.queue_free(this_node);
}

Node* instantiate_scene(char* path)
{
    SortedDictionary* path_to_ps = &(iCluige.iPackedScene.dico_path_to_packed);
    Checked_Variant cv =iCluige.iSortedDictionary.get(
        path_to_ps, path
    );
    if (!cv.valid){
        printf("Failed");
    }

    PackedScene* ps = (PackedScene*)(cv.v.ptr);
    return iCluige.iPackedScene.instantiate(ps);
}

void process_MainMenu(Script* this_Script, float delta)
{
//	MainMenu* this_MainMenu = (MainMenu*)(this_Script->_sub_class);
    Node* this_Node = this_Script->node;
	int ok_action = iCluige.iInput.action_id_from_name("ok", true);
	int exit_action = iCluige.iInput.action_id_from_name("exit", true);
	if(iCluige.iInput.is_action_just_pressed(ok_action))
	{
		load_main_scene(this_Node);
	}
	if(iCluige.iInput.is_action_just_pressed(exit_action))
	{
		iCluige.quit_asked = true;
	}
//	Node2D* this_Node2D = (Node2D*)(this_Script->node->_sub_class);
//	iCluige.iNode2D.move_local(this_Node2D, (Vector2){dx * delta, dy * delta});
}

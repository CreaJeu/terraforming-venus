#include <cluige.h>
#include "WindmillWing.h"

void ready_WindmillWing(Script* this_script);

Script* instantiate_WindmillWing(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	WindmillWing* new_WindmillWing = iCluige.checked_malloc(sizeof(WindmillWing));
	new_Script->_sub_class = new_WindmillWing;

	//plug virtual mehods
	new_WindmillWing->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_WindmillWing;
	new_Script->process = process_WindmillWing;
	new_Script->ready = ready_WindmillWing;
	return new_Script;
}

void register_WindmillWingFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_WindmillWing;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/windmill_wing", sf);
}

void delete_WindmillWing(Script* this_Script)
{
	WindmillWing* this_WindmillWing =
			(WindmillWing*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_WindmillWing->_delete_super;
	free(this_WindmillWing);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

void ready_WindmillWing(Script* this_Script)
{
	WindmillWing* this_WindmillWing = (WindmillWing*)(this_Script->_sub_class);
	Node* root = iCluige.public_root;
	Node* gamestate_Node = iCluige.iNode.get_node(root, "main_Node/gameState_Node", true);
	this_WindmillWing->gamestate = (GameState*)gamestate_Node->script->_sub_class;
}

void process_WindmillWing(Script* this_Script, float delta)
{
	WindmillWing* this_WindmillWing = (WindmillWing*)(this_Script->_sub_class);
	Node2D* this_Node2D = iCluige.iNode2D.cast_from_Node(this_Script->node);
	SpriteSVG* this_SpriteSVG = iCluige.iSpriteSVG.cast_from_Node(this_Script->node);
	if(this_Node2D->_new_baked.visible)
	{
		float speed = this_WindmillWing->gamestate->windmill_rot_speed;
		iCluige.iSpriteSVG.rotate(this_SpriteSVG, speed * delta);
	}
}

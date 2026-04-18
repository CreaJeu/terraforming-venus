#include <cluige.h>
#include "GameState.h"


Script* instantiate_GameState(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	GameState* new_GameState = iCluige.checked_malloc(sizeof(GameState));
	new_Script->_sub_class = new_GameState;

	//instantiate fields
//	bool found = utils_float_from_parsed(&(new_GameState->speed), parsed_params, "speed");
//	if(!found)
//	{
//		new_GameState->speed = 3;//default value from .gd
//	}

	//plug virtual mehods
	new_GameState->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_GameState;
//	new_Script->process = process_GameState;
	return new_Script;
}

void register_GameStateFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_GameState;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/game_state", sf);
}

void delete_GameState(Script* this_Script)
{
	GameState* this_GameState =
			(GameState*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_GameState->_delete_super;
	free(this_GameState);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

//void process_GameState(Script* this_Script, float delta)
//{
//	GameState* this_GameState = (GameState*)(this_Script->_sub_class);
//	if(iCluige.iInput.is_action_just_pressed(UP))
//	{
//		...
//	}
//	Node2D* this_Node2D = (Node2D*)(this_Script->node->_sub_class);
//	iCluige.iNode2D.move_local(this_Node2D, (Vector2){dx * delta, dy * delta});
//}

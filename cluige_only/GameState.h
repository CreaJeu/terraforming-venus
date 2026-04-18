#ifndef GameState_H_INCLUDED
#define GameState_H_INCLUDED

//typedef Script;
//typedef Node2D;

typedef struct _GameState GameState;
struct _GameState
{
//	Script* _this_Script;
//	Node2D* _this_Node2D;

	//@export from .gd
//	float speed;//cluige characters per second

	//virtual methods - private copy of mother class pointers
	void (*_delete_super)(Script*);

	//virtual methods in .c
	//void (*process)(Script* this_Script, float delta);
};

//Script* instantiate_GameState(const SortedDictionary* parsed_params);
void register_GameStateFactory();
void delete_GameState(Script* this_Script);
//void process_GameState(Script* this_Script, float delta);

#endif // _H_INCLUDED

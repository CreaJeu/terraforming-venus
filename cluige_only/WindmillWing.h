#ifndef WindmillWing_H_INCLUDED
#define WindmillWing_H_INCLUDED

//typedef Script;
//typedef Node2D;
#include "GameState.h"

typedef struct _WindmillWing WindmillWing;
struct _WindmillWing
{
//	Script* _this_Script;
//	Node2D* _this_Node2D;

	//@export from .gd
	float timeout_at;
	float accumulated_time;
	Node2D* label;

	GameState* gamestate;

	//virtual methods - private copy of mother class pointers
	void (*_delete_super)(Script*);

	//virtual methods in .c
	//void (*process)(Script* this_Script, float delta);
};

//Script* instantiate_WindmillWing(const SortedDictionary* parsed_params);
void register_WindmillWingFactory();
void delete_WindmillWing(Script* this_Script);
//void process_WindmillWing(Script* this_Script, float delta);

void process_WindmillWing(Script* this_Script, float delta);

#endif // _H_INCLUDED

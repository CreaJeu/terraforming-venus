#ifndef MoreWindmills_H_INCLUDED
#define MoreWindmills_H_INCLUDED

//typedef Script;
//typedef Node2D;
#include "GameState.h"

typedef struct _MoreWindmills MoreWindmills;
struct _MoreWindmills
{
//	Script* _this_Script;
//	Node2D* _this_Node2D;

	//@export from .gd
	int additional_energy;
	int price;
	bool selected;
	GameState* gamestate;

	//virtual methods - private copy of mother class pointers
	void (*_delete_super)(Script*);

	//virtual methods in .c
	//void (*process)(Script* this_Script, float delta);
};

//Script* instantiate_MoreWindmills(const SortedDictionary* parsed_params);
void register_MoreWindmillsFactory();
void delete_MoreWindmills(Script* this_Script);
//void process_MoreWindmills(Script* this_Script, float delta);

bool apply_MoreWindmills(MoreWindmills* this_MoreWindmills, GameState* gamestate);

#endif // _H_INCLUDED

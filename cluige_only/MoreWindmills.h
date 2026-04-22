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
	bool selected;
	GameState* gamestate;

	//virtual methods - private copy of mother class pointers
	void (*_delete_super)(Script*);
};

void register_MoreWindmillsFactory();
void delete_MoreWindmills(Script* this_Script);

//see exit_tree()
//bool apply_MoreWindmills(MoreWindmills* this_MoreWindmills, GameState* gamestate);

#endif // _H_INCLUDED

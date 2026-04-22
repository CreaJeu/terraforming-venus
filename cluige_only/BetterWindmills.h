#ifndef BetterWindmills_H_INCLUDED
#define BetterWindmills_H_INCLUDED

//typedef Script;
//typedef Node2D;
#include "GameState.h"

typedef struct _BetterWindmills BetterWindmills;
struct _BetterWindmills
{
//	Script* _this_Script;
//	Node2D* _this_Node2D;

	//@export from .gd
	float energy_multiplier;
	bool selected;
	GameState* gamestate;

	//virtual methods - private copy of mother class pointers
	void (*_delete_super)(Script*);
};

void register_BetterWindmillsFactory();
void delete_BetterWindmills(Script* this_Script);

//see exit_tree()
//bool apply_BetterWindmills(BetterWindmills* this_BetterWindmills, GameState* gamestate);

#endif // _H_INCLUDED

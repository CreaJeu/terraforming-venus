#ifndef ImproveBacteria_H_INCLUDED
#define ImproveBacteria_H_INCLUDED

//typedef Script;
//typedef Node2D;
#include "GameState.h"

typedef struct _ImproveBacteria ImproveBacteria;
struct _ImproveBacteria
{
//	Script* _this_Script;
//	Node2D* _this_Node2D;

	//@export from .gd
	int acidity_reduction_modifier;
	bool selected;
	GameState* gamestate;

	//virtual methods - private copy of mother class pointers
	void (*_delete_super)(Script*);
};

void register_ImproveBacteriaFactory();
void delete_ImproveBacteria(Script* this_Script);

//see exit_tree()
//bool apply_ImproveBacteria(ImproveBacteria* this_ImproveBacteria, GameState* gamestate);

#endif // _H_INCLUDED

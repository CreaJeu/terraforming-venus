#ifndef SuperBacteria_H_INCLUDED
#define SuperBacteria_H_INCLUDED

//typedef Script;
//typedef Node2D;
#include "GameState.h"

typedef struct _SuperBacteria SuperBacteria;
struct _SuperBacteria
{
//	Script* _this_Script;
//	Node2D* _this_Node2D;

	//@export from .gd
	int acidity_reduction;
	bool selected;
	GameState* gamestate;

	//virtual methods - private copy of mother class pointers
	void (*_delete_super)(Script*);
};

void register_SuperBacteriaFactory();
void delete_SuperBacteria(Script* this_Script);

//see exit_tree()
//bool apply_SuperBacteria(SuperBacteria* this_SuperBacteria, GameState* gamestate);

#endif // _H_INCLUDED

#ifndef ProduceMoreBacteria_H_INCLUDED
#define ProduceMoreBacteria_H_INCLUDED

//typedef Script;
//typedef Node2D;
#include "GameState.h"

typedef struct _ProduceMoreBacteria ProduceMoreBacteria;
struct _ProduceMoreBacteria
{
//	Script* _this_Script;
//	Node2D* _this_Node2D;

	//@export from .gd
	float bacteria_reduction_improvement;
	bool selected;
	GameState* gamestate;

	//virtual methods - private copy of mother class pointers
	void (*_delete_super)(Script*);
};

void register_ProduceMoreBacteriaFactory();
void delete_ProduceMoreBacteria(Script* this_Script);

//see exit_tree()
//bool apply_ProduceMoreBacteria(ProduceMoreBacteria* this_ProduceMoreBacteria, GameState* gamestate);

#endif // _H_INCLUDED

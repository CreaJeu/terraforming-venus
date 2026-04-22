#ifndef UpgradeApplyer_H_INCLUDED
#define UpgradeApplyer_H_INCLUDED

//typedef Script;
//typedef Node2D;
#include "GameState.h"

typedef struct _UpgradeApplyer UpgradeApplyer;
struct _UpgradeApplyer
{
//	Script* _this_Script;
//	Node2D* _this_Node2D;

	//@export from .gd
	int price;

	GameState* gs;

	Script* this_Script;

	//virtual methods - private copy of mother class pointers
	void (*_delete_super)(Script*);

	//virtual methods in .c
	//void (*process)(Script* this_Script, float delta);
};

//Script* instantiate_UpgradeApplyer(const SortedDictionary* parsed_params);
void register_UpgradeApplyerFactory();
void delete_UpgradeApplyer(Script* this_Script);
//void process_UpgradeApplyer(Script* this_Script, float delta);

bool apply_upgrade(UpgradeApplyer* this_UpgradeApplyer);

#endif // _H_INCLUDED

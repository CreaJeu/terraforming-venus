#ifndef Building_H_INCLUDED
#define Building_H_INCLUDED

//typedef Script;
//typedef Node2D;

typedef struct _Building Building;
struct _Building
{
//	Script* _this_Script;
	Node2D* _this_Node2D;

	//@export from .gd
	char* title;
	Deque upgrades;
	int selected_upgrade_index;

	//virtual methods - private copy of mother class pointers
	void (*_delete_super)(Script*);

	//virtual methods in .c
	//void (*process)(Script* this_Script, float delta);
	void (*ready)(Script* this_Script, float delta);
};

//Script* instantiate_Building(const SortedDictionary* parsed_params);
void register_BuildingFactory();
void delete_Building(Script* this_Script);
//void process_Building(Script* this_Script, float delta);

void applySelectedUpgrade(Building* this_Building);
void select_up(Building* this_Building);
void select_down(Building* this_Building);

#endif // _H_INCLUDED

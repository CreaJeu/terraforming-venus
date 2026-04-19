#ifndef GameState_H_INCLUDED
#define GameState_H_INCLUDED

//#include "OurCamera.h"
//#include "BarreUI.h"
typedef struct _OurCamera OurCamera;
typedef struct _BarreUI BarreUI;
//typedef Script;
//typedef Node2D;

typedef struct _GameState GameState;
struct _GameState
{
//	Script* _this_Script;
//	Node2D* _this_Node2D;

	float toxicity;
	float toxicity_reduction;
	int energy;
	int energy_income;
	int selected_building;
	Deque all_buildings;
	OurCamera* camera;
	BarreUI* ui_bar;
	float day_duration;

	float time_passed;
	int current_day;

	//virtual methods - private copy of mother class pointers
	void (*_delete_super)(Script*);

	//virtual methods in .c
	//void (*process)(Script* this_Script, float delta);
};

//Script* instantiate_GameState(const SortedDictionary* parsed_params);
void register_GameStateFactory();
void delete_GameState(Script* this_Script);
//void process_GameState(Script* this_Script, float delta);

void set_energy_income(GameState* this_GameState, int new_income);
void add_to_energy_storage(GameState* this_GameState, int added_energy);
void take_from_energy_storage(GameState* this_GameState, int taken_energy);
void remove_acidity(GameState* this_GameState, float removed_acidity);
void set_acidity_change(GameState* this_GameState, float new_acidity_change);

#endif // _H_INCLUDED

#ifndef BarreUI_H_INCLUDED
#define BarreUI_H_INCLUDED

//typedef Script;
//typedef Node2D;

typedef struct _BarreUI BarreUI;
struct _BarreUI
{
//	Script* _this_Script;
//	Node2D* _this_Node2D;

	//@export from .gd
//	float speed;//cluige characters per second

	//virtual methods - private copy of mother class pointers
	void (*_delete_super)(Script*);

	SpriteText* BuildingSelect;
	SpriteText* EnergyStored;
	SpriteText* EnergyIncome;
	SpriteText* AcidityLevel;
	SpriteText* AcidityChange;
	SpriteText* Date_Label;
	SpriteText* Message_Label;

	//virtual methods in .c
	//void (*process)(Script* this_Script, float delta);
};

//Script* instantiate_BarreUI(const SortedDictionary* parsed_params);
void register_BarreUIFactory();
void delete_BarreUI(Script* this_Script);

void update_selected_building_label(BarreUI* barreUI, char* new_building);
void update_energy_stored_label(BarreUI* barreUI, int new_energy);
void update_energy_income_label(BarreUI* barreUI, int new_income);
void update_acidity_level_label(BarreUI* barreUI, float new_level);
void update_acidity_change_label(BarreUI* barreUI, float new_change);
void update_displayed_date(BarreUI* barreUI, int current_day);
void set_message(BarreUI* barreUI, char* message);
//void process_BarreUI(Script* this_Script, float delta);

#endif // _H_INCLUDED

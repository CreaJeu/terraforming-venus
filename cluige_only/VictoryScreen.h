#ifndef VictoryScreen_H_INCLUDED
#define VictoryScreen_H_INCLUDED

//typedef Script;
//typedef Node2D;

typedef struct _VictoryScreen VictoryScreen;
struct _VictoryScreen
{
	//virtual methods - private copy of mother class pointers
	void (*_delete_super)(Script*);
};

//Script* instantiate_VictoryScreen(const SortedDictionary* parsed_params);
void register_VictoryScreenFactory();
void delete_VictoryScreen(Script* this_Script);
//void process_VictoryScreen(Script* this_Script, float delta);

void show_VictoryScreen();

#endif // _H_INCLUDED

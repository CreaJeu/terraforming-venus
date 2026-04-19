#ifndef MainMenu_H_INCLUDED
#define MainMenu_H_INCLUDED

//typedef Script;
//typedef Node2D;

typedef struct _MainMenu MainMenu;
struct _MainMenu
{
//	Script* _this_Script;
//	Node* _this_Node;

	//@export from .gd
//	float speed;//cluige characters per second

	//virtual methods - private copy of mother class pointers
	void (*_delete_super)(Script*);

	//virtual methods in .c
	//void (*process)(Script* this_Script, float delta);
};

//Script* instantiate_MainMenu(const SortedDictionary* parsed_params);
void register_MainMenuFactory();
void delete_MainMenu(Script* this_Script);
//void process_MainMenu(Script* this_Script, float delta);

#endif // _H_INCLUDED

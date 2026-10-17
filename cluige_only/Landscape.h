#ifndef LANDSCAPE_H_INCLUDED
#define LANDSCAPE_H_INCLUDED

//quick and dirty parallax

//typedef Script;
//typedef Node2D;

typedef struct _Landscape Landscape;
struct _Landscape
{
//	Script* _this_Script;
//	Node2D* _this_Node2D;

	//@export from .gd

	//virtual methods - private copy of mother class pointers
	void (*_delete_super)(Script*);

	//virtual methods in .c
	//void (*process)(Script* this_Script, float delta);
};

//Script* instantiate_Landscape(const SortedDictionary* parsed_params);
void register_LandscapeFactory();
void delete_Landscape(Script* this_Script);
//void process_Landscape(Script* this_Script, float delta);

void process_Landscape(Script* this_Script, float delta);

#endif // _H_INCLUDED

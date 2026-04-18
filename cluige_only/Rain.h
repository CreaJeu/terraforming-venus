#ifndef Rain_H_INCLUDED
#define Rain_H_INCLUDED

//typedef Script;
//typedef Node2D;

typedef struct _Rain Rain;
struct _Rain
{
//	Script* _this_Script;
//	Node2D* _this_Node2D;

	//@export from .gd
//	float speed;//cluige characters per second

	//virtual methods - private copy of mother class pointers
	void (*_delete_super)(Script*);

	//virtual methods in .c
	//void (*process)(Script* this_Script, float delta);
};

//Script* instantiate_Rain(const SortedDictionary* parsed_params);
void register_RainFactory();
void delete_Rain(Script* this_Script);
//void process_Rain(Script* this_Script, float delta);

#endif // _H_INCLUDED

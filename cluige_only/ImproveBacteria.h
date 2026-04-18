#ifndef ImproveBacteria_H_INCLUDED
#define ImproveBacteria_H_INCLUDED

//typedef Script;
//typedef Node2D;

typedef struct _ImproveBacteria ImproveBacteria;
struct _ImproveBacteria
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

//Script* instantiate_ImproveBacteria(const SortedDictionary* parsed_params);
void register_ImproveBacteriaFactory();
void delete_ImproveBacteria(Script* this_Script);
//void process_ImproveBacteria(Script* this_Script, float delta);

#endif // _H_INCLUDED

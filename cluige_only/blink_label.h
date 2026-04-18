#ifndef BLINK_LABEL_H_INCLUDED
#define BLINK_LABEL_H_INCLUDED

//typedef Script;
//typedef Node2D;

typedef struct _BlinkLabel BlinkLabel;
struct _BlinkLabel
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

//Script* instantiate_BlinkLabel(const SortedDictionary* parsed_params);
void register_BlinkLabelFactory();
void delete_BlinkLabel(Script* this_Script);
//void process_BlinkLabel(Script* this_Script, float delta);

#endif // _H_INCLUDED

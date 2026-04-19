#include <cluige.h>
#include "blink_label.h"
void ready_BlinkLabel(Script* this_script);

Script* instantiate_BlinkLabel(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	BlinkLabel* new_BlinkLabel = iCluige.checked_malloc(sizeof(BlinkLabel));
	new_Script->_sub_class = new_BlinkLabel;

	//instantiate fields
	bool found = utils_float_from_parsed(&(new_BlinkLabel->timeout_at), parsed_params, "timeout_at");
	if(!found)
	{
		new_BlinkLabel->timeout_at = 0.5;//default value from .gd
	}
	new_BlinkLabel->accumulated_time = 0;

	//plug virtual mehods
	new_BlinkLabel->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_BlinkLabel;
	new_Script->process = process_BlinkLabel;
	new_Script->ready = ready_BlinkLabel;
	return new_Script;
}

void register_BlinkLabelFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_BlinkLabel;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/blink_label", sf);
}

void delete_BlinkLabel(Script* this_Script)
{
	BlinkLabel* this_BlinkLabel =
			(BlinkLabel*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_BlinkLabel->_delete_super;
	free(this_BlinkLabel);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

void _on_timeout(BlinkLabel* this_BlinkLabel){
    this_BlinkLabel->label->visible = !this_BlinkLabel->label->visible;
}

void process_BlinkLabel(Script* this_Script, float delta)
{
	BlinkLabel* this_BlinkLabel = (BlinkLabel*)(this_Script->_sub_class);
	this_BlinkLabel->accumulated_time += delta;

	if (this_BlinkLabel->accumulated_time > this_BlinkLabel->timeout_at){
        this_BlinkLabel->accumulated_time = 0;
        _on_timeout(this_BlinkLabel);
	}

}

void ready_BlinkLabel(Script* this_Script){
    BlinkLabel* this_BlinkLabel = (BlinkLabel*)(this_Script->_sub_class);
    Node* this_Node = this_Script->node;

    this_BlinkLabel->label = (Node2D*)iCluige.iNode.get_node(this_Node, "..")->_sub_class;

}

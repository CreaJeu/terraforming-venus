#include <cluige.h>
#include "RainParticle.h"
void process_RainParticle(Script* this_Script, float delta);
void ready_RainParticle(Script* this_Script);

Script* instantiate_RainParticle(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	RainParticle* new_RainParticle = iCluige.checked_malloc(sizeof(RainParticle));
	new_Script->_sub_class = new_RainParticle;

	//plug virtual mehods
	new_RainParticle->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_RainParticle;
	new_Script->process = process_RainParticle;
	new_Script->ready = ready_RainParticle;
	return new_Script;
}

void register_RainParticleFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_RainParticle;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/rain_particle", sf);
}

void delete_RainParticle(Script* this_Script)
{
	RainParticle* this_RainParticle =
			(RainParticle*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_RainParticle->_delete_super;
	free(this_RainParticle);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

void process_RainParticle(Script* this_Script, float delta)
{
	//RainParticle* this_RainParticle = (RainParticle*)(this_Script->_sub_class);
	Node2D* this_Node2D = (Node2D*)(this_Script->node->_sub_class);

	iCluige.iNode2D.move_local(this_Node2D, (Vector2){1, 1});//20 * delta, 20 * delta});

	Vector2 screen_size = iCluige.get_screen_size();
	if (
        this_Node2D->position.y > screen_size.y - 10
        ||
        this_Node2D->position.x > screen_size.x - 70
	)
	{
        iCluige.iNode.queue_free(this_Script->node);
	}
}

void ready_RainParticle(Script* this_Script)
{
    Node2D* this_Node2D = (Node2D*)(this_Script->node->_sub_class);
    SpriteText* this_Label = (SpriteText*)(this_Node2D->_sub_class);

    int particle_type = rand() % 2;

    if (particle_type == 0){
        iCluige.iSpriteText.set_text(this_Label, "\\");
    }
    if (particle_type == 1){
        iCluige.iSpriteText.set_text(this_Label, "`");
    }
}

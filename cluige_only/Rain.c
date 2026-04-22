#include <cluige.h>
#include "Rain.h"
void process_Rain(Script* this_Script, float delta);

static int particle_count = 0;

Script* instantiate_Rain(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	Rain* new_Rain = iCluige.checked_malloc(sizeof(Rain));
	new_Script->_sub_class = new_Rain;

	//plug virtual mehods
	new_Rain->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_Rain;
	new_Script->process = process_Rain;
	return new_Script;
}

void register_RainFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_Rain;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/rain", sf);
}

void delete_Rain(Script* this_Script)
{
	Rain* this_Rain =
			(Rain*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_Rain->_delete_super;
	free(this_Rain);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

Vector2 get_random_position_in_screen(){
    Vector2 screen_size = iCluige.get_screen_size();
    int rndX = rand() % (int)(screen_size.x) - 70;
    int rndY = -2;//rand() % (int)(screen_size.y - 40) - 10;

    return (Vector2){rndX, rndY};
}

Node* instantiate_rain_particle()
{
    SortedDictionary* path_to_ps = &(iCluige.iPackedScene.dico_path_to_packed);
    Checked_Variant cv = iCluige.iSortedDictionary.get(
        path_to_ps, "scenes/rain_particle.tscn"
    );
    if (!cv.valid){
        printf("Failed");
    }

    PackedScene* ps = (PackedScene*)(cv.v.ptr);
    return iCluige.iPackedScene.instantiate(ps);
}


void process_Rain(Script* this_Script, float delta)
{
    Node* rain_particle = instantiate_rain_particle();
    particle_count++;
    sprintf(rain_particle->name, "%d", particle_count);
    Node2D* rain_particle_Node2D = rain_particle->_sub_class;
    Vector2 random_position = get_random_position_in_screen();
    iCluige.iNode2D.set_local_position(rain_particle_Node2D, random_position);
    iCluige.iNode.add_child(this_Script->node, rain_particle);
}

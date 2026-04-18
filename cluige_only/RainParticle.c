#include <cluige.h>
#include "RainParticle.h"


Script* instantiate_RainParticle(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	RainParticle* new_RainParticle = iCluige.checked_malloc(sizeof(RainParticle));
	new_Script->_sub_class = new_RainParticle;

	//instantiate fields
//	bool found = utils_float_from_parsed(&(new_RainParticle->speed), parsed_params, "speed");
//	if(!found)
//	{
//		new_RainParticle->speed = 3;//default value from .gd
//	}

	//plug virtual mehods
	new_RainParticle->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_RainParticle;
//	new_Script->process = process_RainParticle;
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

//void process_RainParticle(Script* this_Script, float delta)
//{
//	RainParticle* this_RainParticle = (RainParticle*)(this_Script->_sub_class);
//	if(iCluige.iInput.is_action_just_pressed(UP))
//	{
//		...
//	}
//	Node2D* this_Node2D = (Node2D*)(this_Script->node->_sub_class);
//	iCluige.iNode2D.move_local(this_Node2D, (Vector2){dx * delta, dy * delta});
//}

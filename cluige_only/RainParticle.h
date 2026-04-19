#ifndef RainParticle_H_INCLUDED
#define RainParticle_H_INCLUDED

//typedef Script;
//typedef Node2D;

typedef struct _RainParticle RainParticle;
struct _RainParticle
{
//	Script* _this_Script;
//	Node2D* _this_Node2D;

	//virtual methods - private copy of mother class pointers
	void (*_delete_super)(Script*);

	//virtual methods in .c
	//void (*process)(Script* this_Script, float delta);
};

//Script* instantiate_RainParticle(const SortedDictionary* parsed_params);
void register_RainParticleFactory();
void delete_RainParticle(Script* this_Script);
//void process_RainParticle(Script* this_Script, float delta);

#endif // _H_INCLUDED

#include <cluige.h>
#include "GameState.h"
#include "UpgradeApplyer.h"
#include "BarreUI.h"

void ready_UpgradeApplyer(Script* this_script);

Script* instantiate_UpgradeApplyer(const SortedDictionary* parsed_params)
{
	//mallocs
	Script* new_Script = iCluige.iScript.new_Script();
	UpgradeApplyer* new_UpgradeApplyer = iCluige.checked_malloc(sizeof(UpgradeApplyer));
	new_Script->_sub_class = new_UpgradeApplyer;
	new_UpgradeApplyer->this_Script = new_Script;

	//instantiate fields
	bool found;
	found = utils_int_from_parsed(&(new_UpgradeApplyer->price), parsed_params, "price");
	if(!found)
	{
		new_UpgradeApplyer->price = 100;//default value from .gd
	}
	new_UpgradeApplyer->gs = NULL;

	//plug virtual mehods
	new_UpgradeApplyer->_delete_super = new_Script->delete_Script;
	new_Script->delete_Script = delete_UpgradeApplyer;
	new_Script->ready = ready_UpgradeApplyer;
	return new_Script;
}

void register_UpgradeApplyerFactory()
{
	ScriptFactory* sf;
	sf = iCluige.checked_malloc(sizeof(*sf));
	sf->instantiate = instantiate_UpgradeApplyer;
	iCluige.iScript.register_ScriptFactory_no_ext("scripts/upgrades/upgrade_applyer", sf);
}

void delete_UpgradeApplyer(Script* this_Script)
{
	UpgradeApplyer* this_UpgradeApplyer =
			(UpgradeApplyer*)(this_Script->_sub_class);
	//tmp memorize function pointer before calling free(this)
	void (*delete_super)(Script*) = this_UpgradeApplyer->_delete_super;
	free(this_UpgradeApplyer);
	this_Script->_sub_class = NULL;
	delete_super(this_Script);
}

void ready_UpgradeApplyer(Script* this_Script){
	UpgradeApplyer* this_UpgradeApplyer = (UpgradeApplyer*)(this_Script->_sub_class);
	Node* this_Node = this_Script->node;

	Node* gsn = iCluige.iNode.get_node(this_Node, "../../../gameState_Node");
	this_UpgradeApplyer->gs = (GameState*)gsn->script->_sub_class;
}

bool apply_upgrade(UpgradeApplyer* this_UpgradeApplyer)
{
	Node* this_Node = this_UpgradeApplyer->this_Script->node;
	if(this_UpgradeApplyer->gs->energy < this_UpgradeApplyer->price)
	{
		char msg[120];
		sprintf(msg, "Not enough energy: %d is needed for this upgrade", this_UpgradeApplyer->price);
		set_message(this_UpgradeApplyer->gs->ui_bar, msg);
		return false;
	}
	add_to_energy_storage(this_UpgradeApplyer->gs, -this_UpgradeApplyer->price);
	Node* upgr = iCluige.iNode.get_node(this_Node, "..");
	iCluige.iNode.queue_free(upgr);
	return true;
}

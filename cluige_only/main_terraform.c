//#include <stdio.h>
#include <cluige.h>
//#include <float.h>
//#include <string.h>
//#include <time.h>
//#include <stdlib.h>

#include "BarreUI.h"
#include "BetterWindmills.h"
#include "blink_label.h"
#include "Building.h"
#include "GameState.h"
#include "ImproveBacteria.h"
#include "MainMenu.h"
#include "MoreWindmills.h"
#include "OurCamera.h"
#include "ProduceMoreBacteria.h"
#include "Rain.h"
#include "RainParticle.h"
#include "SuperBacteria.h"
#include "UpgradeApplyer.h"


static void register_all_scripts()
{
	register_BarreUIFactory();
	register_BetterWindmillsFactory();
	register_BlinkLabelFactory();
	register_BuildingFactory();
	register_GameStateFactory();
	register_ImproveBacteriaFactory();
	register_MainMenuFactory();
	register_MoreWindmillsFactory();
	register_OurCameraFactory();
	register_ProduceMoreBacteriaFactory();
	register_RainFactory();
	register_RainParticleFactory();
	register_SuperBacteriaFactory();
	register_UpgradeApplyerFactory();
	//...
}

static void parse_scene(const char* path)
{
	TscnParser tparser;
	iCluige.iTscnParser.tscn_parser_alloc(&tparser, path, 2000);
	bool ok = tparser.parse_scene(&tparser);
	CLUIGE_BREAKPOINT(&ok, !ok);
	iCluige.iTscnParser.pre_delete_TscnParser(&tparser);
}

int main()
{
	//init
	cluige_init(register_all_scripts);//makes all roots, set all functions pointers, etc.

	//import godot data
	parse_scene("scenes/barre_ui.tscn");
	parse_scene("scenes/blink_label.tscn");
	parse_scene("scenes/building.tscn");
	parse_scene("scenes/main_menu.tscn");
	parse_scene("scenes/main.tscn");
	parse_scene("scenes/rain_particle.tscn");
	parse_scene("scenes/rain.tscn");
//	parse_scene("scenes/upgrade.tscn");
	parse_scene("scenes/upgrades/upgrade_better_windmills.tscn");
	parse_scene("scenes/upgrades/upgrade_more_windmills.tscn");
	parse_scene("scenes/upgrades/upgrade_better_bacteria.tscn");
	parse_scene("scenes/upgrades/upgrade_more_bacteria.tscn");
	parse_scene("scenes/upgrades/upgrade_super_bacteria.tscn");

	ProjectDotGodotParser pdgp;
	iCluige.iProjectDotGodotParser.project_dot_godot_parser_alloc(&pdgp, "project.godot");
	bool ok = pdgp.run(&pdgp);
	CLUIGE_BREAKPOINT(&ok, !ok);
	iCluige.iProjectDotGodotParser.pre_delete_ProjectDotGodotParser(&pdgp);

	//run
	cluige_run();

	int finish = cluige_finish();
	return finish;
}


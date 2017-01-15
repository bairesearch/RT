/*******************************************************************************
 *
 * File Name: LDparser.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Generic Ldraw Construct Functions
 * Project Version: 3a7d 11-June-2012
 *
 *******************************************************************************/


#ifndef HEADER_LD_PARSER
#define HEADER_LD_PARSER

#include "LDreferenceClass.h"



#ifdef LINUX
	#define DEFAULT_PARTS_DIRECTORY_FULL_PATH "/usr/share/local/LDRAW/PARTS/"
	#define DEFAULT_PRIMITIVES_DIRECTORY_FULL_PATH "/usr/share/local/LDRAW/P/"
#else
	#define DEFAULT_PARTS_DIRECTORY_FULL_PATH "C:/Program Files/LDraw/PARTS/"
	#define DEFAULT_PRIMITIVES_DIRECTORY_FULL_PATH "C:/Program Files/LDraw/P/"
#endif

#define LD_PARSER_ALLOW_WHITE_SPACE (true)

/*
#define DO_NOT_USE_D12
#ifdef DO_NOT_USE_D12
	#define METAL_HELMETS_DO_NOT_PROVIDE_EXTRA_MOD
#endif
#define ROBIN_HATS_PROVIDE_HELMET_MOD	//added 19-3-06


#define MAXIMUM_DISTANCE_CATAPULT_LONGDISTANCE 35		//distance given in cm
#define MAXIMUM_DISTANCE_LONGBOW_LONGDISTANCE 20		//distance given in cm
#define MAXIMUM_DISTANCE_CROSSBOW_LONGDISTANCE 15		//distance given in cm
#define MAXIMUM_DISTANCE_HANDAXE_LONGDISTANCE 5			//distance given in cm
#define MAXIMUM_DISTANCE_SPEAR_LONGDISTANCE 10			//distance given in cm


//Define extra building material Ldraw parts (for defence calculations for units behind battlments and bushes)
#define PLANT_TREE_PINE_LARGE "3471"
#define PLANT_TREE_PINE_SMALL "2435"
#define PLANT_TREE_FRUIT "3470"
#define PLANT_BUSH "6064"
//------
#define PLANT_TREE_PINE_LARGE_LEN 4
#define PLANT_TREE_PINE_SMALL_LEN 4
#define PLANT_TREE_FRUIT_LEN 4
#define PLANT_BUSH_LEN 4



//Define common building material Ldraw parts
#define BUILDING_WALL_WINDOW "4444"
#define BUILDING_WALL_CORNER "2345"
#define BUILDING_BATTLEMENT_TOWER "6066"
#define BUILDING_BRICK_1X1 "3005"
#define BUILDING_BRICK_1X2 "3004"
#define BUILDING_BRICK_1X3 "3622"
#define BUILDING_BRICK_1X4 "3010"
#define BUILDING_BRICK_1X6 "3009"
#define BUILDING_ROCK_SMALL "6083"
#define BUILDING_ROCK_LARGE "6082"
//------
#define BUILDING_WALL_WINDOW_LEN 4
#define BUILDING_WALL_CORNER_LEN 4
#define BUILDING_BATTLEMENT_TOWER_LEN 4
#define BUILDING_BRICK_1X1_LEN 4
#define BUILDING_BRICK_1X2_LEN 4
#define BUILDING_BRICK_1X3_LEN 4
#define BUILDING_BRICK_1X4_LEN 4
#define BUILDING_BRICK_1X6_LEN 4
#define BUILDING_ROCK_SMALL_LEN 4
#define BUILDING_ROCK_LARGE_LEN 4


//Define common combat Ldraw parts
#define HEAD_CHIN_GUARD "3896"
#define HEAD_NECK_PROTECTOR "3844"
#define HEAD_CROWN "71015"
#define HEAD_PLATE "KniHel"
#define HEAD_ROBIN "RobCap"

#define HEAD_CHIN_GUARD_LEN 4
#define HEAD_NECK_PROTECTOR_LEN 4
#define HEAD_CROWN_LEN 5
#define HEAD_PLATE_LEN 6
#define HEAD_ROBIN_LEN 6

#define HEAD_CHIN_GUARD_MOD 1
#define HEAD_NECK_PROTECTOR_MOD 1

#ifndef METAL_HELMETS_DO_NOT_PROVIDE_EXTRA_MOD
#define HEAD_CROWN_MOD 2
#define HEAD_PLATE_MOD 2
#else
#define HEAD_CROWN_MOD 1
#define HEAD_PLATE_MOD 1
#endif

#ifdef ROBIN_HATS_PROVIDE_HELMET_MOD
#define HEAD_ROBIN_MOD 1
#else
#define HEAD_ROBIN_MOD 0
#endif

#define SHIELD_TRIANGULAR "3846"
#define SHIELD_OVAL "770"

#define SHIELD_TRIANGULAR_LEN 4
#define SHIELD_OVAL_LEN 3

#define SHIELD_TRIANGULAR_MOD 1
#define SHIELD_OVAL_MOD 1


#define TORSO_CHAINMAIL "973P41"
#define TORSO_METAL "973P40"
#define NECK_PLATE "2587"
#define TORSO_ROYAL_CHAINMAIL "973P4E"
#define TORSO_ROYAL_CREST "973P4D"
#define TORSO_WOLF_CREST "973P44"
#define TORSO_EAGLE_CREST "973P43"
#define TORSO_LION_CREST_A "xxxx"	//part does not exist yet
#define TORSO_LION_CREST_B "973P42"	//pikes
#define TORSO_DRAGON_CREST "973P4B"
#define TORSO_ROBIN_A "973P46"
#define TORSO_ROBIN_B "973P50"
#define TORSO_ROBIN_C "973P49"
#define TORSO_ROBIN_D "973P48"
#define TORSO_PLAIN_LADY "973P4Q"

#define TORSO_CHAINMAIL_LEN 6
#define TORSO_METAL_LEN 6
#define NECK_PLATE_LEN 4
#define TORSO_ROYAL_CHAINMAIL_LEN 6
#define TORSO_ROYAL_CREST_LEN 6
#define TORSO_WOLF_CREST_LEN 6
#define TORSO_EAGLE_CREST_LEN 6
#define TORSO_LION_CREST_A_LEN 4	//part does not exist yet
#define TORSO_LION_CREST_B_LEN 6	//pikes
#define TORSO_DRAGON_CREST_LEN 6
#define TORSO_ROBIN_A_LEN 6
#define TORSO_ROBIN_B_LEN 6
#define TORSO_ROBIN_C_LEN 6
#define TORSO_ROBIN_D_LEN 6
#define TORSO_PLAIN_LADY_LEN 6

#define TORSO_CHAINMAIL_MOD 2
#define TORSO_METAL_MOD 3
#define NECK_PLATE_MOD 3
#define TORSO_ROYAL_CHAINMAIL_MOD 2
#define TORSO_ROYAL_CREST_MOD 2
#define TORSO_WOLF_CREST_MOD 2
#define TORSO_EAGLE_CREST_MOD 2
#define TORSO_LION_CREST_A_MOD 2	//part does not exist yet
#define TORSO_LION_CREST_B_MOD 2	//pikes
#define TORSO_DRAGON_CREST_MOD 2
#define TORSO_ROBIN_A_MOD 1
#define TORSO_ROBIN_B_MOD 1
#define TORSO_ROBIN_C_MOD 1
#define TORSO_ROBIN_D_MOD 1
#define TORSO_PLAIN_LADY_MOD 1

#define HAND_LANCE "3849"
#define HAND_SWORD "3847"
#define HAND_LARGESWORD "59"
#define HAND_BOW "4499"
#define HAND_CROSS_BOW "2570"
#define HAND_HANDAXE "774"
#define HAND_AXE "3848"
#define HAND_LARGEAXE "6123"
#define HAND_SPEAR "4497"

#define HAND_LANCE_LEN 4
#define HAND_SWORD_LEN 4
#define HAND_LARGESWORD_LEN 2
#define HAND_BOW_LEN 4
#define HAND_CROSS_BOW_LEN 4
#define HAND_HANDAXE_LEN 3
#define HAND_AXE_LEN 4
#define HAND_LARGEAXE_LEN 4
#define HAND_SPEAR_LEN 4

//Close Combat Weapon Attack Value Modifications
#define HAND_LANCE_MOD 1		//in 2008 [3aXy] a lance is considered a level 6 (value 1) weapon with a +4 mounted bonus. in 2007 [2a11a] a lance is considered a level 4 (value 3) weapon with a +2 mounted bonus. in 2005/2006 this was 5
#define HAND_SWORD_MOD 3
#define HAND_LARGESWORD_MOD 4
#define HAND_LONGBOW_MOD 0
#define HAND_CROSSBOW_MOD 0
#define HAND_HANDAXE_MOD 0
#define HAND_AXE_MOD 3
#define HAND_LARGEAXE_MOD 4
#define HAND_SPEAR_MOD 2

#define HAND_SPEAR_AGAINST_MOUNTED_BONUS 2
#define HAND_SPEAR_MOUNTED_BONUS 2
#define HAND_LANCE_MOUNTED_BONUS 4
#define HAND_OTHER_MOUNTED_BONUS 1 //sword, axe

#define HAND_DAGGER_MOD 1	//All units have daggers as definied in the rules

//Long Distance Weapon Attack Value Modifications
#define HAND_LONGBOW_MOD_LONGDISTANCE 2
#define HAND_CROSSBOW_MOD_LONGDISTANCE 3
#define HAND_HANDAXE_MOD_LONGDISTANCE 4
#define HAND_SPEAR_MOD_LONGDISTANCE 3


#define NECK_QUIVER "4498"
#define NECK_QUIVER_LEN 4



//Define common ModelDetails Type Ldraw parts

#define TORSO_GHOST "xxxx"
#define TORSO_SKELETON "6260"
#define TORSO_GHOST_LEN 4
#define TORSO_SKELETON_LEN 4

#define HORSE "4493"
#define HORSE_LEN 4
#define PERSON_HEAD "3626B"
#define PERSON_HEAD_LEN 5
#define SADDLE "4491"
#define SADDLE_LEN 4

#define VEHICLE_SMALL_WHEEL "2470"
#define VEHICLE_SMALL_WHEEL_LEN 4
#define VEHICLE_LARGE_WHEEL "4489"
#define VEHICLE_LARGE_WHEEL_LEN 4
#define BOAT_SMALL_HULL "4855"
#define BOAT_SMALL_HULL_LEN 4
#define BOAT_LARGE_HULL "2626"
#define BOAT_LARGE_HULL_LEN 4


#define VEHICLE_WHEEL_HOLDER "4488"
#define VEHICLE_WHEEL_HOLDER_LEN 4
#define VEHICLE_WHEEL_HOLDER_DUAL "4600"
#define VEHICLE_WHEEL_HOLDER_DUAL_LEN 4
#define VEHICLE_HORSE_HITCH "2397"
#define VEHICLE_HORSE_HITCH_LEN 4
#define VEHICLE_HORSE_HITCH_WITH_HINGE "4587"
#define VEHICLE_HORSE_HITCH_WITH_HINGE_LEN 4
#define VEHICLE_HORSE_HITCH_HINGE_ROTATABLE "251c01"
#define VEHICLE_HORSE_HITCH_HINGE_ROTATABLE_LEN 6
#define CATAPULT_BUCKET "4626"
#define CATAPULT_BUCKET_LEN 4
#define CATAPULT_AXEL "4504"
#define CATAPULT_AXEL_LEN 4

//unit type attack/defence modifiers
#define CATAPULT_MOD_LONGDISTANCE 10		//d20
*/


/*
#define CART_LARGE_DEFENCE_MOD 20			//2xd20
#define BOAT_LARGE_DEFENCE_MOD 20			//2xd20
#define WARMACHINE_LARGE_DEFENCE_MOD 20		//2xd20
#define CART_SMALL_DEFENCE_MOD 10			//d20
#define BOAT_SMALL_DEFENCE_MOD 10			//d20
#define WARMACHINE_SMALL_DEFENCE_MOD 5		//d10
*/


#define NECK_QUIVER_NAME "NECK_QUIVER"
#define HAND_BOW_NAME "HAND_BOW"

//#define HAND_DAGGER_MOD 1	//All units have daggers as definied in the rules	- this can be moved to LRRCrules.xml
#define HAND_DAGGER_MOD_NAME "HAND_DAGGER_MOD"
extern int HAND_DAGGER_MOD;

#ifdef USE_LRRC
void fillInParserExternVariables();
#endif

//generic parser
bool parseFile(char * parseFileName, Reference * initialReference, Reference * parentReference, bool recurseIntoPartsDir);
	#ifdef USE_LRRC
	void updateUnitDetailsWithCombatDetails(char* subPartFileName, ModelDetails * u);
	void updateUnitDetailsWithBuildingDetails(char* subPartFileName, ModelDetails * u);
	void updateUnitDetailsWithTypeDetails(char* subPartFileName, ModelDetails * u);
	void updateUnitDetailsWithTerrainDefenceDetails(char* subPartFileName, ModelDetails * u);
	#endif

double calcModXPosBasedUponRotate(vec * childRelativePosition, mat * parentReferenceDeformationMatrix);
double calcModYPosBasedUponRotate(vec * childRelativePosition, mat * parentReferenceDeformationMatrix);
double calcModZPosBasedUponRotate(vec * childRelativePosition, mat * parentReferenceDeformationMatrix);

bool removeWhiteSpaceFromString(char * s);


#endif

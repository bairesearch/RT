/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: LDsprite.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2021 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3p1a 15-March-2021
 * Description: Contains common sprite commands
 * /
 *******************************************************************************/


#ifndef HEADER_LD_SPRITE
#define HEADER_LD_SPRITE

#include "LDreferenceClass.hpp"
#include "SHAREDglobalDefs.hpp"
#include "LDreferenceManipulation.hpp"
#include "SHAREDvector.hpp"
#include "SHAREDvars.hpp"	//required for writeByteArrayToFile
#include "XMLrulesClass.hpp"
#include "math.h"

#define CPLUSPLUSERRORCORRECTION2 (500)


#define CHAR_PLUS ('+')
#define CHAR_MINUS ('-')
#define CHAR_EQUALS ('=')
#define CHAR_FULLSTOP ('.')

#define DEFAULT_LDRAW_SUBMODEL_COLOUR (16)


#define ANN_OR_LRRC_SPRITE_HEADER_NAME "\n0 Start ann.exe Sprites\n"
#define ANN_OR_LRRC_SPRITE_TRAILER_NAME "0 End ann.exe Sprites\n"
#define ANN_OR_LRRC_SPRITE_HEADER_NUM_LINES (2)
#define ANN_OR_LRRC_SPRITE_TRAILER_NUM_LINES (1)
#define ANN_OR_LRRC_SPRITE_HEADER_LENGTH 25
#define ANN_OR_LRRC_SPRITE_TRAILER_LENGTH 22





#define SPRITE_CHARACTER_DICE_OFFSET (192)
#define SPRITE_CHARACTER_NUM_OFFSET (48)
#define MAX_ATTACK_DEFENCE_LEVEL (6)
#define MAX_DICE_ATTACK_DEFENCE_VALUE_SUPPORTED (5)			/*CHECK THIS: this will change once more spritetextdx.dat files are created - ie spritetextd12.dat [change to 6] and spritetextd20.dat [change to 10] are created*/
#define MIN_DICE_ATTACK_DEFENCE_VALUE_SUPPORTED (2)			/*CHECK THIS: this will change once more spritetextd2.dat file is created [change to 1]*/



#define ANSI_DECIMAL_DIFF_BETWEEN_CASE_TEXT (32)
#define ANSI_NUMBER_CHARACTERS (256)

#define SPRITE_INDEX_MAGNITUDE (5)

#define SPRITE_TEXT_DICE_SCALE_FACTOR_NAME "SPRITE_TEXT_DICE_SCALE_FACTOR" //assume dice have already been appropriately scaled
#define SPRITE_LINE_SPACING_RATIO_BASE_NAME "SPRITE_LINE_SPACING_RATIO_BASE"
#define SPRITE_DICE_WIDTH_IN_LDRAW_UNITS_NAME "SPRITE_DICE_WIDTH_IN_LDRAW_UNITS"
#define SPRITE_TEXT_DICE_Y_OFFSET_NAME "SPRITE_TEXT_DICE_Y_OFFSET"

#define SPRITE_TEXT_SCALE_FACTOR_NAME "SPRITE_TEXT_SCALE_FACTOR"	//this can easily be changed
#define SPRITE_WIDTH_OF_CHARS_IN_LDRAW_UNITS_NAME "SPRITE_WIDTH_OF_CHARS_IN_LDRAW_UNITS"
#define SPRITE_HEIGHT_OF_CHARS_IN_LDRAW_UNITS_NAME "SPRITE_HEIGHT_OF_CHARS_IN_LDRAW_UNITS"
#define SPRITE_CHAR_SPACING_RATIO_NAME "SPRITE_CHAR_SPACING_RATIO"
#define SPRITE_TEXT_PADDING_IN_LDRAW_UNITS_NAME "SPRITE_TEXT_PADDING_IN_LDRAW_UNITS"

#define SPRITES_FLOATING_WIDTH_IN_LDRAW_UNITS_NAME "SPRITES_FLOATING_WIDTH_IN_LDRAW_UNITS"
#define SPRITES_FLOATING_HEIGHT_IN_LDRAW_UNITS_NAME "SPRITES_FLOATING_HEIGHT_IN_LDRAW_UNITS"


#define SPRITES_DISPLAY_DICE
//#define SPRITE_ALWAYS_ADD_TEXT


#define SPRITE_NAME_START_NAME "SPRITE_NAME_START"
#define SPRITE_EXTENSION_NAME  "SPRITE_EXTENSION"
#define SPRITE_CHARACTER_START_NAME "SPRITE_CHARACTER_START"
#define SPRITE_CHARACTER_EXTENSION_NAME "SPRITE_CHARACTER_EXTENSION"		//sprite submodel extension
/*
#define SPRITE_NAME_START "sprite"
#define SPRITE_EXTENSION  ".ldr"
#define SPRITE_CHARACTER_START "spritetext"
#define SPRITE_CHARACTER_EXTENSION ".dat"		//sprite submodel extension
*/


#define SPRITE_DEFAULT_COLOUR_NAME "SPRITE_DEFAULT_COLOUR"
//#define SPRITE_DEFAULT_COLOUR (DAT_FILE_DEFAULT_COLOUR)

extern int SPRITE_DEFAULT_COLOUR;

class LDspriteClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: SHAREDvectorClass SHAREDvector;
	private: LDreferenceManipulationClass LDreferenceManipulation;
	public: void fillInLDspriteExternVariables();

	public: string LDcreateSpriteReferenceName(const int spriteIndex, string sceneFileName);
	public: LDreference* LDaddTextualSpriteInfoStringToReferenceList(LDreference* unitReference, string spriteTextString, int spriteColourArray[], LDreference* spriteSubmodelInitialReference, const int spriteNumberOfLines, int* numSpritesAdded, const bool addIndividualSprites);
	public: LDreference* LDaddBasicTextualSpriteStringToReferenceList(string spriteTextString, LDreference* currentReference, vec* position, int* numSpritesAdded, const bool addIndividualSprites, int colour, double scale);


	private: bool LDaddSpriteToSpriteReferenceList(const vec* spriteSceneCoords, const vec* eyeCoords, LDreference* spriteListInitialReference, const string spriteReferenceFileName, const int spriteDefaultColour, double spriteScaleFactor);

	/*low level sprite routines*/
	private: void LDgenerateSpriteRotationMatrix(const vec* spriteSceneCoords, const vec* eyeCoords, mat* spriteRotationMatrix);
	private: void LDspriteSubmodelFillTextualReference(LDreference* spriteSubmodelCurrentReference, vec* spriteParagraphCurrentPosition, const char characterToWrite, int spriteColour, double scale);
};

#endif

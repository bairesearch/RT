/*******************************************************************************
 *
 * File Name: LDsprite.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2010 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3a5g 01-Nov-2011
 * Description: Contains common sprite commands
 *
 *******************************************************************************/

#include "SHAREDglobalDefs.h"


#include "LDsprite.h"
//#include "LDparser.h"
#include "math.h"
#include "LDreferenceManipulation.h"
#include "SHAREDvector.h"

#include "XMLrulesClass.h"


int SPRITE_DEFAULT_COLOUR;

static double SPRITE_CHAR_PIXEL_TO_LDRAW_UNIT_RATIO;
static double SPRITE_TEXT_SCALE_FACTOR;
static double SPRITE_TEXT_DICE_SCALE_FACTOR;
static double SPRITE_CHAR_HEIGHT_IN_PIXELS;
static double SPRITE_LINE_SPACING_RATIO_WITHOUT_DICE_PRESENT;

	static double SPRITE_HEIGHT_OF_CHARS_IN_LDRAW_UNITS;			//derivable
	static double SPRITE_LINE_SPACING_RATIO;						//derivable
	static double SPRITE_LINE_SPACING_SIZE_IN_LDRAW_UNITS;			//derivable

static double SPRITE_CHAR_WIDTH_IN_PIXELS;
static double SPRITE_SMALL_CHAR_WIDTH_IN_PIXELS;
static double SPRITE_DICE_WIDTH_IN_LDRAW_UNITS;
static double SPRITE_CHAR_SPACING_RATIO;

	static double SPRITE_WIDTH_OF_CHARS_IN_LDRAW_UNITS;			//derivable
	static double SPRITE_WIDTH_OF_SMALL_CHARS_IN_LDRAW_UNITS;		//derivable
	static double SPRITE_CHAR_SPACING_SIZE_IN_LDRAW_UNITS;			//derivable
	static double SPRITE_SMALL_CHAR_SPACING_SIZE_IN_LDRAW_UNITS;	//derivable
	static double SPRITE_DICE_SPACING_SIZE_IN_LDRAW_UNITS;			//derivable

static double SPRITES_FLOATING_WIDTH_IN_LDRAW_UNITS;
static double SPRITES_FLOATING_HEIGHT_IN_LDRAW_UNITS;

static double SPRITE_TEXT_DICE_Y_OFFSET;

static string SPRITE_NAME_START;
static string SPRITE_EXTENSION;
static string SPRITE_CHARACTER_START;
static string SPRITE_CHARACTER_EXTENSION;

double spriteTextKernelArray[ANSI_NUMBER_CHARACTERS][2];

void fillInLDSpriteExternVariables()
{
	//extract common sprite variables from either xml file (LRRC or ANN)
	#ifdef USE_LRRC
		RulesClass * currentReferenceRulesClass = LRRCrulesSprite;
	#elif defined USE_CS
		RulesClass * currentReferenceRulesClass = CSrulesSprite;
	#else
		RulesClass * currentReferenceRulesClass = ANNrulesSprite;
	#endif

	while(currentReferenceRulesClass->next != NULL)
	{
		if(currentReferenceRulesClass->name == SPRITE_DEFAULT_COLOUR_NAME)
		{
			SPRITE_DEFAULT_COLOUR = currentReferenceRulesClass->fractionalValue;
		}


		else if(currentReferenceRulesClass->name == SPRITE_CHAR_PIXEL_TO_LDRAW_UNIT_RATIO_NAME)
		{
			SPRITE_CHAR_PIXEL_TO_LDRAW_UNIT_RATIO = currentReferenceRulesClass->fractionalValue;
		}
		else if(currentReferenceRulesClass->name == SPRITE_TEXT_SCALE_FACTOR_NAME)
		{
			SPRITE_TEXT_SCALE_FACTOR = currentReferenceRulesClass->fractionalValue;
		}
		else if(currentReferenceRulesClass->name == SPRITE_TEXT_DICE_SCALE_FACTOR_NAME)
		{
			SPRITE_TEXT_DICE_SCALE_FACTOR = currentReferenceRulesClass->fractionalValue;
		}
		else if(currentReferenceRulesClass->name == SPRITE_CHAR_HEIGHT_IN_PIXELS_NAME)
		{
			SPRITE_CHAR_HEIGHT_IN_PIXELS = currentReferenceRulesClass->fractionalValue;
		}
		else if(currentReferenceRulesClass->name == SPRITE_LINE_SPACING_RATIO_WITHOUT_DICE_PRESENT_NAME)
		{
			SPRITE_LINE_SPACING_RATIO_WITHOUT_DICE_PRESENT = currentReferenceRulesClass->fractionalValue;
		}


		else if(currentReferenceRulesClass->name == SPRITE_CHAR_WIDTH_IN_PIXELS_NAME)
		{
			SPRITE_CHAR_WIDTH_IN_PIXELS = currentReferenceRulesClass->fractionalValue;
		}
		else if(currentReferenceRulesClass->name == SPRITE_SMALL_CHAR_WIDTH_IN_PIXELS_NAME)
		{
			SPRITE_SMALL_CHAR_WIDTH_IN_PIXELS  = currentReferenceRulesClass->fractionalValue;
		}
		else if(currentReferenceRulesClass->name == SPRITE_DICE_WIDTH_IN_LDRAW_UNITS_NAME)
		{
			SPRITE_DICE_WIDTH_IN_LDRAW_UNITS = currentReferenceRulesClass->fractionalValue;
		}
		else if(currentReferenceRulesClass->name == SPRITE_CHAR_SPACING_RATIO_NAME)
		{
			SPRITE_CHAR_SPACING_RATIO = currentReferenceRulesClass->fractionalValue;
		}


		else if(currentReferenceRulesClass->name == SPRITES_FLOATING_WIDTH_IN_LDRAW_UNITS_NAME)
		{
			SPRITES_FLOATING_WIDTH_IN_LDRAW_UNITS = currentReferenceRulesClass->fractionalValue;
		}
		else if(currentReferenceRulesClass->name == SPRITES_FLOATING_HEIGHT_IN_LDRAW_UNITS_NAME)
		{
			SPRITES_FLOATING_HEIGHT_IN_LDRAW_UNITS = currentReferenceRulesClass->fractionalValue;
		}

		else if(currentReferenceRulesClass->name == SPRITE_TEXT_DICE_Y_OFFSET_NAME)
		{
			SPRITE_TEXT_DICE_Y_OFFSET = currentReferenceRulesClass->fractionalValue;
		}


		else if(currentReferenceRulesClass->name == SPRITE_NAME_START_NAME)
		{
			SPRITE_NAME_START = currentReferenceRulesClass->stringValue;
		}
		else if(currentReferenceRulesClass->name == SPRITE_EXTENSION_NAME)
		{
			SPRITE_EXTENSION = currentReferenceRulesClass->stringValue;
		}
		else if(currentReferenceRulesClass->name == SPRITE_CHARACTER_START_NAME)
		{
			SPRITE_CHARACTER_START = currentReferenceRulesClass->stringValue;
		}
		else if(currentReferenceRulesClass->name == SPRITE_CHARACTER_EXTENSION_NAME)
		{
			SPRITE_CHARACTER_EXTENSION = currentReferenceRulesClass->stringValue;
		}

		else
		{

		}

		currentReferenceRulesClass = currentReferenceRulesClass->next;
	}

	SPRITE_HEIGHT_OF_CHARS_IN_LDRAW_UNITS = (SPRITE_CHAR_HEIGHT_IN_PIXELS * SPRITE_CHAR_PIXEL_TO_LDRAW_UNIT_RATIO);
	SPRITE_LINE_SPACING_RATIO = (SPRITE_LINE_SPACING_RATIO_WITHOUT_DICE_PRESENT * SPRITE_TEXT_SCALE_FACTOR);	//OLD: SPRITE_LINE_SPACING_RATIO_WITHOUT_DICE_PRESENT/(SPRITE_TEXT_SCALE_FACTOR/4), //NB '/(SPRITE_TEXT_SCALE_FACTOR/4)' is due to dice size. without dice present SPRITE_LINE_SPACING_RATIO = (1.5);
	SPRITE_LINE_SPACING_SIZE_IN_LDRAW_UNITS = ((SPRITE_HEIGHT_OF_CHARS_IN_LDRAW_UNITS*SPRITE_LINE_SPACING_RATIO)*SPRITE_TEXT_SCALE_FACTOR);

	SPRITE_WIDTH_OF_CHARS_IN_LDRAW_UNITS = (SPRITE_CHAR_WIDTH_IN_PIXELS * SPRITE_CHAR_PIXEL_TO_LDRAW_UNIT_RATIO);
	SPRITE_WIDTH_OF_SMALL_CHARS_IN_LDRAW_UNITS = (SPRITE_SMALL_CHAR_WIDTH_IN_PIXELS * SPRITE_CHAR_PIXEL_TO_LDRAW_UNIT_RATIO);
	SPRITE_CHAR_SPACING_SIZE_IN_LDRAW_UNITS = ((SPRITE_WIDTH_OF_CHARS_IN_LDRAW_UNITS * SPRITE_CHAR_SPACING_RATIO)*SPRITE_TEXT_SCALE_FACTOR);
	SPRITE_SMALL_CHAR_SPACING_SIZE_IN_LDRAW_UNITS = ((SPRITE_WIDTH_OF_SMALL_CHARS_IN_LDRAW_UNITS * SPRITE_CHAR_SPACING_RATIO)*SPRITE_TEXT_SCALE_FACTOR);
	SPRITE_DICE_SPACING_SIZE_IN_LDRAW_UNITS = ((SPRITE_DICE_WIDTH_IN_LDRAW_UNITS * SPRITE_CHAR_SPACING_RATIO)*SPRITE_TEXT_DICE_SCALE_FACTOR);


	//in ldraw units
	spriteTextKernelArray[48][0] = 0.5;
	spriteTextKernelArray[49][0] = 1.1;
	spriteTextKernelArray[50][0] = 0.4;
	spriteTextKernelArray[51][0] = 0.5;
	spriteTextKernelArray[52][0] = 0.2;
	spriteTextKernelArray[53][0] = 0.5;
	spriteTextKernelArray[54][0] = 0.4;
	spriteTextKernelArray[55][0] = 0.6;
	spriteTextKernelArray[56][0] = 0.5;
	spriteTextKernelArray[57][0] = 0.5;
	spriteTextKernelArray[45][0] = 0.4;
	spriteTextKernelArray[43][0] = 0.6;
	spriteTextKernelArray[61][0] = 0.6;
	spriteTextKernelArray[65][0] = 0.1;
	spriteTextKernelArray[66][0] = 0.9;
	spriteTextKernelArray[67][0] = 0.6;
	spriteTextKernelArray[68][0] = 0.9;
	spriteTextKernelArray[69][0] = 0.9;
	spriteTextKernelArray[70][0] = 0.9;
	spriteTextKernelArray[71][0] = 0.6;
	spriteTextKernelArray[72][0] = 0.9;
	spriteTextKernelArray[73][0] = 2.8;	//TEMP = 1.8
	spriteTextKernelArray[74][0] = 0.4;
	spriteTextKernelArray[75][0] = 0.9;
	spriteTextKernelArray[76][0] = 0.9;
	spriteTextKernelArray[77][0] = 0.3;
	spriteTextKernelArray[78][0] = 0.9;
	spriteTextKernelArray[79][0] = 0.6;
	spriteTextKernelArray[80][0] = 0.9;
	spriteTextKernelArray[81][0] = 0.6;
	spriteTextKernelArray[82][0] = 0.9;
	spriteTextKernelArray[83][0] = 0.6;
	spriteTextKernelArray[84][0] = 0.2;
	spriteTextKernelArray[85][0] = 0.9;
	spriteTextKernelArray[86][0] = 0.2;
	spriteTextKernelArray[87][0] = 0;
	spriteTextKernelArray[88][0] = 0.1;
	spriteTextKernelArray[89][0] = 0.2;
	spriteTextKernelArray[90][0] = 0.2;
	spriteTextKernelArray[46][0] = 1.5;

	spriteTextKernelArray[48][1] = 5;
	spriteTextKernelArray[49][1] = 3.6;
	spriteTextKernelArray[50][1] = 4.9;
	spriteTextKernelArray[51][1] = 5;
	spriteTextKernelArray[52][1] = 5;
	spriteTextKernelArray[53][1] = 5;
	spriteTextKernelArray[54][1] = 5;
	spriteTextKernelArray[55][1] = 5;
	spriteTextKernelArray[56][1] = 4.9;
	spriteTextKernelArray[57][1] = 5;
	spriteTextKernelArray[45][1] = 3;
	spriteTextKernelArray[43][1] = 5.2;
	spriteTextKernelArray[61][1] = 5.1;
	spriteTextKernelArray[65][1] = 6.4;
	spriteTextKernelArray[66][1] = 6;
	spriteTextKernelArray[67][1] = 6.5;
	spriteTextKernelArray[68][1] = 6.5;
	spriteTextKernelArray[69][1] = 6;
	spriteTextKernelArray[70][1] = 5.5;
	spriteTextKernelArray[71][1] = 7;
	spriteTextKernelArray[72][1] = 6.2;
	spriteTextKernelArray[73][1] = 3.7;	//TEMP= 4.7
	spriteTextKernelArray[74][1] = 4.1;
	spriteTextKernelArray[75][1] = 6.6;
	spriteTextKernelArray[76][1] = 5.1;
	spriteTextKernelArray[77][1] = 6.8;
	spriteTextKernelArray[78][1] = 6.2;
	spriteTextKernelArray[79][1] = 7;
	spriteTextKernelArray[80][1] = 6;
	spriteTextKernelArray[81][1] = 7;
	spriteTextKernelArray[82][1] = 6.6;
	spriteTextKernelArray[83][1] = 6;
	spriteTextKernelArray[84][1] = 5.8;
	spriteTextKernelArray[85][1] = 6.2;
	spriteTextKernelArray[86][1] = 6.5;
	spriteTextKernelArray[87][1] = 6.9;
	spriteTextKernelArray[88][1] = 6.4;
	spriteTextKernelArray[89][1] = 6.3;
	spriteTextKernelArray[90][1] = 5.8;
	spriteTextKernelArray[46][1] = 3;
}




/*Secondary sprite routines*/

//

void LDcreateSpriteReferenceName(char * spriteReferenceFileName, int spriteIndex, char * sceneFileName)
{
	//cout << "66" << endl;
	//creates sprite reference name spriteReferenceName = [SPRITE_NAME_START][spriteIndex][sceneFileName]
	char * tempString = new char[SPRITE_INDEX_MAGNITUDE*CPLUSPLUSERRORCORRECTION2];

	spriteReferenceFileName[0] = '\0';

	strcpy(tempString, sceneFileName);

	int i;
	for(i = 0; i < strlen(tempString); i++)
	{
		if(tempString[i] == '.')
		{
			tempString[i] = '\0';
		}
	}
	strcat(spriteReferenceFileName, tempString);

	strcat(spriteReferenceFileName, SPRITE_NAME_START.c_str());
	//itoa(spriteIndex, tempString, 10);
	sprintf(tempString, "%d", spriteIndex);

	strcat(spriteReferenceFileName, tempString);

	strcat(spriteReferenceFileName, SPRITE_EXTENSION.c_str());

	//cout << "67" << endl;
	delete tempString;
	//cout << "68" << endl;
	//create the "spritex.ldr" file that will be referenced by the scene file
}

Reference * LDaddBasicTextualSpriteStringToReferenceList(string * spriteTextString, Reference * currentReference, vec * position, int * numSpritesAdded, bool addIndividualSprites, int colour, double scale)
{
	Reference * spriteSubmodelCurrentReference = currentReference;

	bool result = true;

	char * spriteText = new char[(*spriteTextString).size()+1];
	const char * constSpriteText = (*spriteTextString).c_str();
	strcpy(spriteText, constSpriteText);
	int spriteTextLength = (int)strlen(spriteText);

	int spriteTextIndex;

	vec spriteSubmodelCurrentReferencePosition;
	spriteSubmodelCurrentReferencePosition.x = 0.0 - ((double)SPRITES_FLOATING_WIDTH_IN_LDRAW_UNITS*scale / 2.0);
	spriteSubmodelCurrentReferencePosition.y = 0.0 + (double)SPRITES_FLOATING_HEIGHT_IN_LDRAW_UNITS*scale;
	spriteSubmodelCurrentReferencePosition.z = 0.0;


	//common local variables for loop
	double spriteCurrentCharacterSpacing;
	int spriteLineNumber = 0;

	for(spriteTextIndex = 0; spriteTextIndex < spriteTextLength; spriteTextIndex++)
	{
		/*convert lowercase text to uppercase text:*/
		if((spriteText[spriteTextIndex] >= 'a') && (spriteText[spriteTextIndex] <= 'z'))
		{
			spriteText[spriteTextIndex] = spriteText[spriteTextIndex] - ANSI_DECIMAL_DIFF_BETWEEN_CASE_TEXT;
		}

		if(spriteText[spriteTextIndex] == '\n')
		{
			spriteLineNumber++;
			spriteSubmodelCurrentReferencePosition.y  = spriteSubmodelCurrentReferencePosition.y + (double)SPRITE_LINE_SPACING_SIZE_IN_LDRAW_UNITS*scale;
			spriteSubmodelCurrentReferencePosition.x = 0.0 - ((double)SPRITES_FLOATING_WIDTH_IN_LDRAW_UNITS*scale / 2.0);
		}
		else if(((spriteText[spriteTextIndex] >= '0') && (spriteText[spriteTextIndex] <= '9')) || (spriteText[spriteTextIndex] == CHAR_PLUS) || (spriteText[spriteTextIndex] == CHAR_MINUS) || (spriteText[spriteTextIndex] == CHAR_EQUALS) || (spriteText[spriteTextIndex] == CHAR_FULLSTOP))
		{

			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x - spriteTextKernelArray[spriteText[spriteTextIndex]][0]*scale;

			if(!addIndividualSprites)
			{
				vec tempAbsPos;
				addVectors(&tempAbsPos, &spriteSubmodelCurrentReferencePosition, position);
				LDspriteSubmodelFillTextualReference(spriteSubmodelCurrentReference, &tempAbsPos, spriteText[spriteTextIndex], colour, scale);
			}
			else
			{
				LDspriteSubmodelFillTextualReference(spriteSubmodelCurrentReference, &spriteSubmodelCurrentReferencePosition, spriteText[spriteTextIndex], colour, scale);
			}

			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + spriteTextKernelArray[spriteText[spriteTextIndex]][1]*scale;

			Reference * newReference = new Reference();
			spriteSubmodelCurrentReference -> next = newReference;
			spriteSubmodelCurrentReference = spriteSubmodelCurrentReference -> next;
			*numSpritesAdded = *numSpritesAdded + 1;
		}
		else if((spriteText[spriteTextIndex] >= 'A') && (spriteText[spriteTextIndex] <= 'Z'))
		{
			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x - spriteTextKernelArray[spriteText[spriteTextIndex]][0]*scale;

			if(!addIndividualSprites)
			{
				vec tempAbsPos;
				addVectors(&tempAbsPos, &spriteSubmodelCurrentReferencePosition, position);
				LDspriteSubmodelFillTextualReference(spriteSubmodelCurrentReference, &tempAbsPos, spriteText[spriteTextIndex], colour, scale);
			}
			else
			{
				LDspriteSubmodelFillTextualReference(spriteSubmodelCurrentReference, &spriteSubmodelCurrentReferencePosition, spriteText[spriteTextIndex], colour, scale);
			}
			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + spriteTextKernelArray[spriteText[spriteTextIndex]][1]*scale;

			Reference * newReference = new Reference();
			spriteSubmodelCurrentReference -> next = newReference;
			spriteSubmodelCurrentReference = spriteSubmodelCurrentReference -> next;
			*numSpritesAdded = *numSpritesAdded + 1;

			//cout << "spriteTextKernelArray[spriteText[spriteTextIndex]][1] = " << spriteTextKernelArray[spriteText[spriteTextIndex]][1] << endl;
			//cout << "spriteText[spriteTextIndex]] = " << spriteText[spriteTextIndex] << endl;


		}
		else if(spriteText[spriteTextIndex] == ' ')
		{
			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + ((double)SPRITE_CHAR_SPACING_SIZE_IN_LDRAW_UNITS/2.0)*scale;
		}
		else
		{
			/*
			char temp = (char)SPRITE_CHARACTER_DICE_OFFSET;
			char temp2 = (char)(SPRITE_CHARACTER_DICE_OFFSET+MAX_ATTACK_DEFENCE_LEVEL);
			printf("\nunknown character - system must exit (character = %c %d)", spriteText[spriteTextIndex], spriteText[spriteTextIndex]);
			printf("\nNB SPRITE_CHARACTER_DICE_OFFSET = %c %d", temp, temp);
			printf("\nNB (SPRITE_CHARACTER_DICE_OFFSET+MAX_ATTACK_DEFENCE_LEVEL) = %c %d", temp2, temp2);
			exit(0);
			*/
		}
	}

	delete spriteText;


	return spriteSubmodelCurrentReference;
}



//CHECK THIS spriteSubmodelCurrentReference parameter may have to be changed to the LRRCaddTextualSpriteInfoStringToReferenceList() function return value
//bool LRRCaddTextualSpriteInfoStringToReferenceList(string * spriteTextString, int spriteColourArray[], Reference * spriteSubmodelFirstReference, int spriteNumberOfLines, Reference * spriteSubmodelFinalReference);
Reference * LDaddTextualSpriteInfoStringToReferenceList(Reference * unitReference, string * spriteTextString, int spriteColourArray[], Reference * spriteSubmodelInitialReference, int spriteNumberOfLines, int * numSpritesAdded, bool addIndividualSprites)
{
	bool result = true;



	char * spriteText = new char[(*spriteTextString).size()+1];
	const char * constSpriteText = (*spriteTextString).c_str();
	strcpy(spriteText, constSpriteText);
	int spriteTextLength = (int)strlen(spriteText);

	int spriteTextIndex;

	Reference * spriteSubmodelCurrentReference = spriteSubmodelInitialReference;

	vec spriteSubmodelCurrentReferencePosition;
	spriteSubmodelCurrentReferencePosition.x = 0.0 - (SPRITES_FLOATING_WIDTH_IN_LDRAW_UNITS / 2);
	spriteSubmodelCurrentReferencePosition.y = 0.0 + SPRITES_FLOATING_HEIGHT_IN_LDRAW_UNITS;
	spriteSubmodelCurrentReferencePosition.z = 0.0;


	//common local variables for loop
	double spriteCurrentCharacterSpacing;
	int spriteLineNumber = 0;

	for(spriteTextIndex = 0; spriteTextIndex < spriteTextLength; spriteTextIndex++)
	{
		/*convert lowercase text to uppercase text:*/
		if((spriteText[spriteTextIndex] >= 'a') && (spriteText[spriteTextIndex] <= 'z'))
		{
			spriteText[spriteTextIndex] = spriteText[spriteTextIndex] - ANSI_DECIMAL_DIFF_BETWEEN_CASE_TEXT;
		}

		if(spriteText[spriteTextIndex] == '\n')
		{
			spriteLineNumber++;
			if(spriteLineNumber >= spriteNumberOfLines)
			{
				cout << "error; (spriteLineNumber >= spriteNumberOfLines)" << endl;


				result = false;
			}
			spriteSubmodelCurrentReferencePosition.y  = spriteSubmodelCurrentReferencePosition.y + SPRITE_LINE_SPACING_SIZE_IN_LDRAW_UNITS;
			spriteSubmodelCurrentReferencePosition.x = 0.0 - (SPRITES_FLOATING_WIDTH_IN_LDRAW_UNITS / 2);
		}
		else if(((spriteText[spriteTextIndex] >= '0') && (spriteText[spriteTextIndex] <= '9')) || (spriteText[spriteTextIndex] == CHAR_PLUS) || (spriteText[spriteTextIndex] == CHAR_MINUS) || (spriteText[spriteTextIndex] == CHAR_EQUALS) || (spriteText[spriteTextIndex] == CHAR_FULLSTOP))
		{
			//spriteCurrentCharacterSpacing = SPRITE_SMALL_CHAR_SPACING_SIZE_IN_LDRAW_UNITS; 	//OLD; SPRITE_CHAR_SPACING_SIZE_IN_LDRAW_UNITS * (SPRITE_SMALL_CHAR_WIDTH_IN_PIXELS/SPRITE_CHAR_WIDTH_IN_PIXELS);
			//spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + spriteCurrentCharacterSpacing/2;
			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x - spriteTextKernelArray[spriteText[spriteTextIndex]][0]*SPRITE_TEXT_SCALE_FACTOR;

			if(!addIndividualSprites)
			{
				vec tempAbsPos;
				addVectors(&tempAbsPos, &spriteSubmodelCurrentReferencePosition, &(unitReference->absolutePosition));
				LDspriteSubmodelFillTextualReference(spriteSubmodelCurrentReference, &tempAbsPos, spriteText[spriteTextIndex], spriteColourArray[spriteLineNumber], SPRITE_TEXT_SCALE_FACTOR);
			}
			else
			{
				LDspriteSubmodelFillTextualReference(spriteSubmodelCurrentReference, &spriteSubmodelCurrentReferencePosition, spriteText[spriteTextIndex], spriteColourArray[spriteLineNumber], SPRITE_TEXT_SCALE_FACTOR);
			}

			//spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + spriteCurrentCharacterSpacing;
			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + + spriteTextKernelArray[spriteText[spriteTextIndex]][1]*SPRITE_TEXT_SCALE_FACTOR;

			Reference * newReference = new Reference();
			spriteSubmodelCurrentReference -> next = newReference;
			spriteSubmodelCurrentReference = spriteSubmodelCurrentReference -> next;
			*numSpritesAdded = *numSpritesAdded + 1;
		}
		else if((spriteText[spriteTextIndex] >= 'A') && (spriteText[spriteTextIndex] <= 'Z'))
		{
			//spriteCurrentCharacterSpacing = SPRITE_CHAR_SPACING_SIZE_IN_LDRAW_UNITS;
			//spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + spriteCurrentCharacterSpacing/2;
			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x - spriteTextKernelArray[spriteText[spriteTextIndex]][0]*SPRITE_TEXT_SCALE_FACTOR;

			if(!addIndividualSprites)
			{
				vec tempAbsPos;
				addVectors(&tempAbsPos, &spriteSubmodelCurrentReferencePosition, &(unitReference->absolutePosition));
				LDspriteSubmodelFillTextualReference(spriteSubmodelCurrentReference, &tempAbsPos, spriteText[spriteTextIndex], spriteColourArray[spriteLineNumber], SPRITE_TEXT_SCALE_FACTOR);
			}
			else
			{
				LDspriteSubmodelFillTextualReference(spriteSubmodelCurrentReference, &spriteSubmodelCurrentReferencePosition, spriteText[spriteTextIndex], spriteColourArray[spriteLineNumber], SPRITE_TEXT_SCALE_FACTOR);
			}
			//spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + spriteCurrentCharacterSpacing/2;
			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + spriteTextKernelArray[spriteText[spriteTextIndex]][1]*SPRITE_TEXT_SCALE_FACTOR;

			Reference * newReference = new Reference();
			spriteSubmodelCurrentReference -> next = newReference;
			spriteSubmodelCurrentReference = spriteSubmodelCurrentReference -> next;
			*numSpritesAdded = *numSpritesAdded + 1;

		}
		else if(((unsigned char)spriteText[spriteTextIndex] > (unsigned char)SPRITE_CHARACTER_DICE_OFFSET) && ((unsigned char)spriteText[spriteTextIndex] <= (unsigned char)(SPRITE_CHARACTER_DICE_OFFSET+MAX_ATTACK_DEFENCE_LEVEL)))
		{
			spriteCurrentCharacterSpacing = SPRITE_DICE_SPACING_SIZE_IN_LDRAW_UNITS;
			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + spriteCurrentCharacterSpacing/2;

			if(!addIndividualSprites)
			{
				vec tempAbsPos;
				addVectors(&tempAbsPos, &spriteSubmodelCurrentReferencePosition, &(unitReference->absolutePosition));
				LDspriteSubmodelFillTextualReference(spriteSubmodelCurrentReference, &tempAbsPos, spriteText[spriteTextIndex], spriteColourArray[spriteLineNumber], SPRITE_TEXT_SCALE_FACTOR);
			}
			else
			{
				LDspriteSubmodelFillTextualReference(spriteSubmodelCurrentReference, &spriteSubmodelCurrentReferencePosition, spriteText[spriteTextIndex], spriteColourArray[spriteLineNumber], SPRITE_TEXT_SCALE_FACTOR);
			}
			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + spriteCurrentCharacterSpacing;

			Reference * newReference = new Reference();
			spriteSubmodelCurrentReference -> next = newReference;
			spriteSubmodelCurrentReference = spriteSubmodelCurrentReference -> next;
			*numSpritesAdded = *numSpritesAdded + 1;
		}
		else if(spriteText[spriteTextIndex] == ' ')
		{
			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + (SPRITE_CHAR_SPACING_SIZE_IN_LDRAW_UNITS/2);
		}
		else
		{
			char temp = (char)SPRITE_CHARACTER_DICE_OFFSET;
			char temp2 = (char)(SPRITE_CHARACTER_DICE_OFFSET+MAX_ATTACK_DEFENCE_LEVEL);
			printf("\nunknown character - system must exit (character = %c %d)", spriteText[spriteTextIndex], spriteText[spriteTextIndex]);
			printf("\nNB SPRITE_CHARACTER_DICE_OFFSET = %c %d", temp, temp);
			printf("\nNB (SPRITE_CHARACTER_DICE_OFFSET+MAX_ATTACK_DEFENCE_LEVEL) = %c %d", temp2, temp2);
			exit(0);
		}
	}

	delete spriteText;

	//spriteSubmodelFinalReference = spriteSubmodelCurrentReference;

	return spriteSubmodelCurrentReference;
}





//OLD: new items [eg char, Reference] are currently not being properly created in LRRCsprite.cpp
bool LDaddSpriteToSpriteReferenceList(vec * spriteSceneCoords, vec * eyeCoords, Reference * spriteListInitialReference, char * spriteReferenceFileName, int spriteDefaultColour, double spriteScaleFactor)
{
	//add sprite to spriteByteArray (replace sprite of sprite index, spriteIndex, if it already exists)

	bool result = true;


	//spriteReferenceSubmodelNameLength = (int)strlen(spriteReferenceFileName);

	Reference * spriteReference = new Reference();

	spriteReference->colour = spriteDefaultColour;		//CHECK THIS - this should be changed to player
	spriteReference->type = REFERENCE_TYPE_SUBMODEL;
	mat spriteRotationMatrix;

	createIdentityMatrix(&spriteRotationMatrix);
	scaleMatrix(&spriteRotationMatrix, spriteScaleFactor);		//	scaleMatrix(&currentDeformationMatrix, ((neuronContainer->neuron->bias)*(SPRITE_SUBMODEL_RANGE_SCALE_FACTOR*LDRAW_UNITS_PER_CM)));

/*original before RBB 26-jan-07
	ANNgenerateSpriteRotationMatrix(spriteSceneCoords, eyeCoords, &spriteRotationMatrix);
*/
	copyMatrix2IntoMatrix1(&(spriteReference->deformationMatrix), &(spriteRotationMatrix));
		//spriteReference->deformationMatrix = spriteRotationMatrix;

	spriteReference->relativePosition.x = spriteSceneCoords->x;
	spriteReference->relativePosition.y = spriteSceneCoords->y;
	spriteReference->relativePosition.z = spriteSceneCoords->z;
	spriteReference->name = spriteReferenceFileName;
	//cout << "DEBUG: mmstart";


	int lineNumberInFileOfSprite;

	/*
	cout << "about to findTextInByteArray;" << endl;
	cout << "DEBUG: spriteListByteArray = " << spriteListByteArray << endl;
	cout << "DEBUG: *spriteListByteArraySize = " << *spriteListByteArraySize << endl;
	cout << "DEBUG: spriteReferenceString = " << spriteReferenceString << endl;
	cout << "DEBUG: spriteReferenceStringSize = " << spriteReferenceStringSize << endl;
	cout << "DEBUG: &lineNumberInFileOfSprite = " << &lineNumberInFileOfSprite << endl;
	*/

	if(search1DRefListNameAndColourFindRef(spriteListInitialReference, spriteReference))
	{
		//cout << "DEBUG LRRCsprite.cpp 3b " << endl;

		if(!search1DRefListNameAndColourReplaceRef(spriteListInitialReference, spriteReference, spriteReference))
		{
			cout << "error: cannot replace Reference in Sprite Reference List" << endl;
			cout << "\t spriteReference->colour  = \n" << spriteReference->colour  << endl;
			cout << "\t spriteReference->name = " << spriteReference->name << endl;
			result = false;
		}
	}
	else
	{
		//cout << "DEBUG LRRCsprite.cpp 3c " << endl;
		if(!search1DRefListAddReference(spriteListInitialReference, spriteReference))
		{
			cout << "error: cannot add Reference to Sprite Reference List" << endl;
			cout << "\t spriteReference->colour  = \n" << spriteReference->colour  << endl;
			cout << "\t spriteReference->name = " << spriteReference->name << endl;
			result = false;
		}
	}

	delete spriteReference;
	//cout << "DEBUG LRRCsprite.cpp 4 " << endl;

	return result;
}


bool LDaddSpriteListByteArrayToSceneFileInefficient(char * sceneFileName, char * sceneFileNameWithSprites, char * spriteListByteArray, int spriteListByteArraySize, int spriteListByteArrayLines)
{
	bool result = true;

	char * spriteHeaderSearchString = ANN_OR_LRRC_SPRITE_HEADER_NAME;
	char * spriteTrailerSearchString = ANN_OR_LRRC_SPRITE_TRAILER_NAME;
	int spriteHeaderSearchStringLength = ANN_OR_LRRC_SPRITE_HEADER_LENGTH;
	int spriteTrailerSearchStringLength = ANN_OR_LRRC_SPRITE_TRAILER_LENGTH;

	int sceneFileNumberOfLines;
	int sceneFileByteArraySize = 0;
	char * sceneFileByteArray = new char[DAT_FILE_MAX_NUM_OF_REFERENCES*DAT_FILE_REF_MAX_SIZE];

	if(!readFileIntoByteArray(sceneFileName, sceneFileByteArray, &sceneFileNumberOfLines, &sceneFileByteArraySize))
	{
		cout << "error: cannot read file, " << sceneFileName << endl;
		result = false;
	}
	else
	{
		int sceneFileNumberOfLinesWithSprites = sceneFileNumberOfLines;

		//TEMP DEBUG
		/*
		int temp1 = DAT_FILE_MAX_NUM_OF_REFERENCES;
		int temp2 = DAT_FILE_REF_MAX_SIZE;
		cout << "DAT_FILE_MAX_NUM_OF_REFERENCES = " << temp1 << endl;
		cout << "DAT_FILE_REF_MAX_SIZE = " << temp2 << endl;
		*/

		#ifdef TEMPDEBUG
		cout << "DEBUG; sceneFileByteArray = \n" << endl;
		for(int i = 0; i < sceneFileByteArraySize; i++)
		{
			cout << sceneFileByteArray[i];
		}
		cout << "DEBUG; sceneFileNumberOfLinesWithSprites = " << sceneFileNumberOfLinesWithSprites << endl;
		cout << "DEBUG; sceneFileByteArraySize = " << sceneFileByteArraySize << endl;
		#endif

		/*Start Sprite Header Section Confirmation*/

		int lineNumberOfSpriteHeader;
		int lineNumberOfSpriteTrailer;
		int lineNumberInFileOfSprite;

		bool spriteHeaderFound = false;
		bool spriteTrailerFound = false;

		/*determines whether a Sprite Header line exists in the scene file by looking for a spriteHeaderSearchString*/
		if(findTextInByteArray(sceneFileByteArray, sceneFileByteArraySize, spriteHeaderSearchString, spriteHeaderSearchStringLength, &lineNumberOfSpriteHeader))
		{
			spriteHeaderFound = true;
		}

		/*determines whether a Sprite Trailer line exists in the scene file by looking for a spriteHeaderSearchString*/
		if(findTextInByteArray(sceneFileByteArray, sceneFileByteArraySize, spriteTrailerSearchString, spriteTrailerSearchStringLength, &lineNumberOfSpriteTrailer))
		{
			spriteTrailerFound = true;
		}
		/*End Sprite Header Section Confirmation*/

		if(spriteHeaderFound && spriteTrailerFound)
		{
			/*sprite header info found, continue*/
			lineNumberInFileOfSprite = (lineNumberOfSpriteHeader+1);
			if(!replaceLinesInByteArray(sceneFileByteArray, spriteListByteArray, &sceneFileByteArraySize, spriteListByteArraySize, lineNumberInFileOfSprite, (lineNumberOfSpriteTrailer - lineNumberOfSpriteHeader - 1)))
			{
				cout << "ERROR0" << endl;
				cout << "error: cannot replace line in byte array" << endl;
				cout << "\t sceneFileNumberOfLinesWithSprites = " << sceneFileNumberOfLinesWithSprites << endl;
				cout << "\t sceneFileByteArray = " << sceneFileByteArray << endl;
				cout << "\t spriteListByteArray = " << spriteListByteArray << endl;
				cout << "\t sceneFileByteArraySize = " << sceneFileByteArraySize << endl;
				cout << "\t spriteListByteArraySize = " << spriteListByteArraySize << endl;
				cout << "\t lineNumberInFileOfSprite = " << lineNumberInFileOfSprite << endl;
				cout << "\t numLinesToReplace = " << (lineNumberOfSpriteTrailer - lineNumberOfSpriteHeader - 1) << endl;
				result = false;
			}

			//write the byteArray - replacing the original scene file
			writeByteArrayToFile(sceneFileNameWithSprites, sceneFileByteArray, sceneFileByteArraySize);
		}
		else if(!spriteHeaderFound && !spriteTrailerFound)
		{
			/*add a sprite header to scene file*/
			#ifdef TEMPDEBUG
			cout << "\n\n ADDING SPRITE HEADER TO SCENE FILE \n\n" << endl;
			#endif

			lineNumberOfSpriteHeader = (sceneFileNumberOfLinesWithSprites-1);

			#ifdef TEMPDEBUG2
			cout << "DEBUG; sceneFileByteArraySize theoretical = " << (sceneFileByteArraySize + ANN_OR_LRRC_SPRITE_HEADER_LENGTH) << endl;
			#endif

			if(!addLinesToByteArray(sceneFileByteArray, spriteHeaderSearchString, &sceneFileByteArraySize, spriteHeaderSearchStringLength, lineNumberOfSpriteHeader))
			{
				cout << "ERROR1" << endl;
				cout << "error: cannot add line to byte array" << endl;
				cout << "\t sceneFileNumberOfLinesWithSprites = " << sceneFileNumberOfLinesWithSprites << endl;
				//cout << "\t sceneFileByteArray = " << sceneFileByteArray << endl;
				cout << "\t spriteHeaderSearchString = " << spriteHeaderSearchString << endl;
				cout << "\t sceneFileByteArraySize = " << sceneFileByteArraySize << endl;
				cout << "\t spriteHeaderSearchStringLength = " << spriteHeaderSearchStringLength << endl;
				cout << "\t lineNumberOfSpriteHeader = " << lineNumberOfSpriteHeader << endl;
				result = false;
			}

			sceneFileNumberOfLinesWithSprites=sceneFileNumberOfLinesWithSprites+ANN_OR_LRRC_SPRITE_HEADER_NUM_LINES;

			#ifdef TEMPDEBUG2
			cout << "DEBUG; sceneFileByteArray = \n" << endl;
			for(int i = 0; i < sceneFileByteArraySize; i++)
			{
				cout << sceneFileByteArray[i];
			}
			cout << "DEBUG; sceneFileNumberOfLinesWithSprites = " << sceneFileNumberOfLinesWithSprites << endl;
			cout << "DEBUG; sceneFileByteArraySize = " << sceneFileByteArraySize << endl;
			#endif

			/*add a sprites to scene file*/
			#ifdef TEMPDEBUG
			cout << "\n\n ADDING SPRITES TO SCENE FILE  \n\n" << endl;
			#endif

			#ifdef TEMPDEBUG2
			cout << "DEBUG; sceneFileByteArraySize theoretical = " << (sceneFileByteArraySize + spriteListByteArraySize) << endl;
			#endif

			lineNumberInFileOfSprite = (sceneFileNumberOfLinesWithSprites-1);
			if(!addLinesToByteArray(sceneFileByteArray, spriteListByteArray, &sceneFileByteArraySize, spriteListByteArraySize, lineNumberInFileOfSprite))
			{
				cout << "ERROR2" << endl;
				cout << "error: cannot add line to byte array" << endl;
				cout << "\t sceneFileNumberOfLinesWithSprites = " << sceneFileNumberOfLinesWithSprites << endl;
				//cout << "\t sceneFileByteArray = " << sceneFileByteArray << endl;
				cout << "\t spriteListByteArray = " << spriteListByteArray << endl;
				cout << "\t sceneFileByteArraySize = " << sceneFileByteArraySize << endl;
				cout << "\t spriteListByteArraySize = " << spriteListByteArraySize << endl;
				cout << "\t lineNumberInFileOfSprite = " << lineNumberInFileOfSprite << endl;
				result = false;
			}

			sceneFileNumberOfLinesWithSprites = sceneFileNumberOfLinesWithSprites + spriteListByteArrayLines;


			#ifdef TEMPDEBUG2
			cout << "DEBUG; sceneFileByteArray = \n" << endl;
			for(int i = 0; i < sceneFileByteArraySize; i++)
			{
				cout << sceneFileByteArray[i];
			}
			cout << "DEBUG; sceneFileNumberOfLinesWithSprites = " << sceneFileNumberOfLinesWithSprites << endl;
			cout << "DEBUG; sceneFileByteArraySize = " << sceneFileByteArraySize << endl;
			#endif


			/*add a sprite trailer to scene file*/
			#ifdef TEMPDEBUG
			cout << "\n\n ADDING SPRITE TRAILER TO SCENE FILE  \n\n" << endl;
			#endif

			lineNumberOfSpriteTrailer = (sceneFileNumberOfLinesWithSprites-1);
			if(!addLinesToByteArray(sceneFileByteArray, spriteTrailerSearchString, &sceneFileByteArraySize, spriteTrailerSearchStringLength, lineNumberOfSpriteTrailer))
			{
				cout << "ERROR3" << endl;
				cout << "error: cannot add line to byte array" << endl;
				cout << "\t sceneFileNumberOfLinesWithSprites = " << sceneFileNumberOfLinesWithSprites << endl;
				//cout << "\t sceneFileByteArray = " << sceneFileByteArray << endl;
				cout << "\t spriteTrailerSearchString = " << spriteTrailerSearchString << endl;
				cout << "\t sceneFileByteArraySize = " << sceneFileByteArraySize << endl;
				cout << "\t spriteTrailerSearchStringLength = " << spriteTrailerSearchStringLength << endl;
				cout << "\t lineNumberOfSpriteTrailer = " << lineNumberOfSpriteTrailer << endl;
				cout << "\t sceneFileNameWithSprites = " << sceneFileNameWithSprites << endl;
				cout << "\t spriteListByteArrayLines = " << spriteListByteArrayLines << endl;
				cout << "\t sceneFileNumberOfLines = " << sceneFileNumberOfLines << endl;

				result = false;
			}
			sceneFileNumberOfLinesWithSprites=sceneFileNumberOfLinesWithSprites+ANN_OR_LRRC_SPRITE_TRAILER_NUM_LINES;


			#ifdef TEMPDEBUG
			cout << "DEBUG; sceneFileByteArray = \n" << endl;
			for(int i = 0; i < sceneFileByteArraySize; i++)
			{
				cout << sceneFileByteArray[i];
			}
			cout << "DEBUG; sceneFileNumberOfLinesWithSprites = " << sceneFileNumberOfLinesWithSprites << endl;
			cout << "DEBUG; sceneFileByteArraySize = " << sceneFileByteArraySize << endl;
			#endif


			//write the byteArray - replacing the original scene file
			writeByteArrayToFile(sceneFileNameWithSprites, sceneFileByteArray, sceneFileByteArraySize);
		}
		else
		{
			result = false;
			cout << "error: file contains inconsistent sprite header/trailer, spriteHeaderFound = " << spriteHeaderFound << ", spriteTrailerFound = " << spriteTrailerFound << endl;
		}
	}

	delete sceneFileByteArray;

	return result;
}

/*this is not complete yet - just use an Identity matrix - ie do not rotate the sprite according to the user POV*/
void LDgenerateSpriteRotationMatrix(vec * spriteSceneCoords, vec * eyeCoords, mat * spriteRotationMatrix)
{
	//TEMP - this is not complete
	createIdentityMatrix(spriteRotationMatrix);		//CHECK THIS
}


void LDspriteSubmodelFillTextualReference(Reference * spriteSubmodelCurrentReference, vec * spriteParagraphCurrentPosition, char characterToWrite, int spriteColour, double scale)
{
	string referenceNameStart = SPRITE_CHARACTER_START;
	string referenceNameEnd = SPRITE_CHARACTER_EXTENSION;
	spriteSubmodelCurrentReference->colour = spriteColour;
	spriteSubmodelCurrentReference->type = REFERENCE_TYPE_SUBMODEL;

	spriteSubmodelCurrentReference->relativePosition.x = spriteParagraphCurrentPosition->x;
	spriteSubmodelCurrentReference->relativePosition.y = spriteParagraphCurrentPosition->y;
	spriteSubmodelCurrentReference->relativePosition.z = spriteParagraphCurrentPosition->z;

	mat currentDeformationMatrix;

	char * tempString = new char[SPRITE_INDEX_MAGNITUDE];

	if(((unsigned char)characterToWrite > (unsigned char)SPRITE_CHARACTER_DICE_OFFSET) && ((unsigned char)characterToWrite <= (unsigned char)(SPRITE_CHARACTER_DICE_OFFSET+MAX_ATTACK_DEFENCE_LEVEL)))
	{
		/*no change to currentDeformationMatrix*/
		createIdentityMatrix(&currentDeformationMatrix);

		scaleMatrix(&currentDeformationMatrix, SPRITE_TEXT_DICE_SCALE_FACTOR);
		spriteSubmodelCurrentReference->relativePosition.y = spriteSubmodelCurrentReference->relativePosition.y + SPRITE_TEXT_DICE_Y_OFFSET;
		spriteSubmodelCurrentReference->colour = spriteSubmodelCurrentReference->colour + DAT_FILE_COLOUR_TRANPARENT_MOD;
		tempString[0] = 'd';
		int diceValue = ((unsigned char)characterToWrite - (unsigned char)SPRITE_CHARACTER_DICE_OFFSET)*2;
		if(diceValue > 9)
		{
			tempString[1] = 1 + SPRITE_CHARACTER_NUM_OFFSET;
			tempString[2] = (diceValue - 10) + SPRITE_CHARACTER_NUM_OFFSET;
			tempString[3] = '\0';
		}
		else
		{
			tempString[1] = (diceValue + SPRITE_CHARACTER_NUM_OFFSET);
			tempString[2] = '\0';
		}

	}
	else
	{
		createIdentityMatrix(&currentDeformationMatrix);
		scaleMatrix(&currentDeformationMatrix, scale);
		tempString[0] = characterToWrite;
		tempString[1] = '\0';
	}

	copyMatrix2IntoMatrix1(&(spriteSubmodelCurrentReference->deformationMatrix), &(currentDeformationMatrix));

	spriteSubmodelCurrentReference->name = referenceNameStart + tempString + referenceNameEnd;
	//cout << "DEBUG: SPRITE_CHARACTER_EXTENSION = " << SPRITE_CHARACTER_EXTENSION << endl;
	//cout << "DEBUG: spriteSubmodelCurrentReference->name = " << spriteSubmodelCurrentReference->name << endl;

	delete tempString;
}

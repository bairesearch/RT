/*******************************************************************************
 * 
 * This file is part of BAIPROJECT.
 * 
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation.
 * 
 * BAIPROJECT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 * 
 * You should have received a copy of the GNU Affero General Public License
 * version 3 along with BAIPROJECT.  If not, see <http://www.gnu.org/licenses/>
 * for a copy of the AGPLv3 License.
 * 
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: LDsprite.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3c5b 15-December-2012
 * Description: Contains common sprite commands
 *
 *******************************************************************************/

#include "SHAREDglobalDefs.h"


#include "LDsprite.h"
#include "math.h"
#include "LDreferenceManipulation.h"
#include "SHAREDvector.h"

#include "XMLrulesClass.h"


int SPRITE_DEFAULT_COLOUR;

static double SPRITE_TEXT_DICE_SCALE_FACTOR;
static double SPRITE_LINE_SPACING_RATIO_WITHOUT_DICE_PRESENT;
static double SPRITE_DICE_WIDTH_IN_LDRAW_UNITS;
static double SPRITE_TEXT_DICE_Y_OFFSET;
	static double SPRITE_LINE_SPACING_RATIO;	//derivable
	static double SPRITE_DICE_SPACING_SIZE_IN_LDRAW_UNITS;			//derivable

static double SPRITE_TEXT_SCALE_FACTOR;
static double SPRITE_WIDTH_OF_CHARS_IN_LDRAW_UNITS;
static double SPRITE_HEIGHT_OF_CHARS_IN_LDRAW_UNITS;
static double SPRITE_CHAR_SPACING_RATIO;
static double SPRITE_TEXT_PADDING_IN_LDRAW_UNITS;
	static double SPRITE_LINE_SPACING_SIZE_IN_LDRAW_UNITS;			//derivable
	static double SPRITE_CHAR_SPACING_SIZE_IN_LDRAW_UNITS;			//derivable

static double SPRITES_FLOATING_WIDTH_IN_LDRAW_UNITS;
static double SPRITES_FLOATING_HEIGHT_IN_LDRAW_UNITS;

static string SPRITE_NAME_START;
static string SPRITE_EXTENSION;
static string SPRITE_CHARACTER_START;
static string SPRITE_CHARACTER_EXTENSION;

double spriteTextKernelArray[ANSI_NUMBER_CHARACTERS];


void fillInLDspriteExternVariables()
{
	#ifdef USE_CS
		RulesClass * currentReferenceRulesClass = CSrulesSprite;
	#elif defined USE_GIA
		RulesClass * currentReferenceRulesClass = GIArulesSprite;
	#else
		RulesClass * currentReferenceRulesClass = ANNrulesSprite;
	#endif

	while(currentReferenceRulesClass->next != NULL)
	{
		if(currentReferenceRulesClass->name == SPRITE_DEFAULT_COLOUR_NAME)
		{
			SPRITE_DEFAULT_COLOUR = currentReferenceRulesClass->fractionalValue;
		}



		else if(currentReferenceRulesClass->name == SPRITE_TEXT_DICE_SCALE_FACTOR_NAME)
		{
			SPRITE_TEXT_DICE_SCALE_FACTOR = currentReferenceRulesClass->fractionalValue;
		}
		else if(currentReferenceRulesClass->name == SPRITE_LINE_SPACING_RATIO_WITHOUT_DICE_PRESENT_NAME)
		{
			SPRITE_LINE_SPACING_RATIO_WITHOUT_DICE_PRESENT = currentReferenceRulesClass->fractionalValue;
		}
		else if(currentReferenceRulesClass->name == SPRITE_DICE_WIDTH_IN_LDRAW_UNITS_NAME)
		{
			SPRITE_DICE_WIDTH_IN_LDRAW_UNITS = currentReferenceRulesClass->fractionalValue;
		}
		else if(currentReferenceRulesClass->name == SPRITE_TEXT_DICE_Y_OFFSET_NAME)
		{
			SPRITE_TEXT_DICE_Y_OFFSET = currentReferenceRulesClass->fractionalValue;
		}


		else if(currentReferenceRulesClass->name == SPRITE_TEXT_SCALE_FACTOR_NAME)
		{
			SPRITE_TEXT_SCALE_FACTOR = currentReferenceRulesClass->fractionalValue;
		}
		else if(currentReferenceRulesClass->name == SPRITE_WIDTH_OF_CHARS_IN_LDRAW_UNITS_NAME)
		{
			SPRITE_WIDTH_OF_CHARS_IN_LDRAW_UNITS = currentReferenceRulesClass->fractionalValue;
		}
		else if(currentReferenceRulesClass->name == SPRITE_HEIGHT_OF_CHARS_IN_LDRAW_UNITS_NAME)
		{
			SPRITE_HEIGHT_OF_CHARS_IN_LDRAW_UNITS = currentReferenceRulesClass->fractionalValue;
		}
		else if(currentReferenceRulesClass->name == SPRITE_CHAR_SPACING_RATIO_NAME)
		{
			SPRITE_CHAR_SPACING_RATIO = currentReferenceRulesClass->fractionalValue;
		}
		else if(currentReferenceRulesClass->name == SPRITE_TEXT_PADDING_IN_LDRAW_UNITS_NAME)
		{
			SPRITE_TEXT_PADDING_IN_LDRAW_UNITS = currentReferenceRulesClass->fractionalValue;
		}



		else if(currentReferenceRulesClass->name == SPRITES_FLOATING_WIDTH_IN_LDRAW_UNITS_NAME)
		{
			SPRITES_FLOATING_WIDTH_IN_LDRAW_UNITS = currentReferenceRulesClass->fractionalValue;
		}
		else if(currentReferenceRulesClass->name == SPRITES_FLOATING_HEIGHT_IN_LDRAW_UNITS_NAME)
		{
			SPRITES_FLOATING_HEIGHT_IN_LDRAW_UNITS = currentReferenceRulesClass->fractionalValue;
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

	SPRITE_LINE_SPACING_RATIO = (SPRITE_LINE_SPACING_RATIO_WITHOUT_DICE_PRESENT);
	SPRITE_LINE_SPACING_SIZE_IN_LDRAW_UNITS = ((SPRITE_HEIGHT_OF_CHARS_IN_LDRAW_UNITS*SPRITE_LINE_SPACING_RATIO)*SPRITE_TEXT_SCALE_FACTOR);

	SPRITE_CHAR_SPACING_SIZE_IN_LDRAW_UNITS = ((SPRITE_WIDTH_OF_CHARS_IN_LDRAW_UNITS * SPRITE_CHAR_SPACING_RATIO)*SPRITE_TEXT_SCALE_FACTOR);
	SPRITE_DICE_SPACING_SIZE_IN_LDRAW_UNITS = ((SPRITE_DICE_WIDTH_IN_LDRAW_UNITS * SPRITE_CHAR_SPACING_RATIO)*SPRITE_TEXT_DICE_SCALE_FACTOR);


	spriteTextKernelArray[48] = 7.0;
	spriteTextKernelArray[49] = 3.0;
	spriteTextKernelArray[50] = 5.0;
	spriteTextKernelArray[51] = 6.0;
	spriteTextKernelArray[52] = 6.0;
	spriteTextKernelArray[53] = 5.0;
	spriteTextKernelArray[54] = 5.5;
	spriteTextKernelArray[55] = 5.5;
	spriteTextKernelArray[56] = 5.0;
	spriteTextKernelArray[57] = 6.0;
	spriteTextKernelArray[45] = 3.5;
	spriteTextKernelArray[43] = 5.0;
	spriteTextKernelArray[61] = 5.0;
	spriteTextKernelArray[65] = 6.0;
	spriteTextKernelArray[66] = 6.0;
	spriteTextKernelArray[67] = 6.0;
	spriteTextKernelArray[68] = 6.0;
	spriteTextKernelArray[69] = 5.0;
	spriteTextKernelArray[70] = 5.0;
	spriteTextKernelArray[71] = 6.0;
	spriteTextKernelArray[72] = 5.0;
	spriteTextKernelArray[73] = 1.0;
	spriteTextKernelArray[74] = 5.0;
	spriteTextKernelArray[75] = 6.0;
	spriteTextKernelArray[76] = 5.0;
	spriteTextKernelArray[77] = 6.0;
	spriteTextKernelArray[78] = 6.0;
	spriteTextKernelArray[79] = 7.0;
	spriteTextKernelArray[80] = 5.0;
	spriteTextKernelArray[81] = 7.0;
	spriteTextKernelArray[82] = 6.0;
	spriteTextKernelArray[83] = 4.5;
	spriteTextKernelArray[84] = 5.0;
	spriteTextKernelArray[85] = 5.0;
	spriteTextKernelArray[86] = 5.5;
	spriteTextKernelArray[87] = 8.0;
	spriteTextKernelArray[88] = 6.0;
	spriteTextKernelArray[89] = 7.0;
	spriteTextKernelArray[90] = 5.0;
	spriteTextKernelArray[46] = 2.0;


}




/*Secondary sprite routines*/

void LDcreateSpriteReferenceName(char * spriteReferenceFileName, int spriteIndex, char * sceneFileName)
{
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
	sprintf(tempString, "%d", spriteIndex);

	strcat(spriteReferenceFileName, tempString);

	strcat(spriteReferenceFileName, SPRITE_EXTENSION.c_str());

	delete tempString;
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
	spriteSubmodelCurrentReferencePosition.x = 0.0 - ((double)SPRITES_FLOATING_WIDTH_IN_LDRAW_UNITS*scale / 2.0);		//NB can remove *scale
	spriteSubmodelCurrentReferencePosition.y = 0.0 + (double)SPRITES_FLOATING_HEIGHT_IN_LDRAW_UNITS*scale;			//NB can remove *scale
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
			spriteSubmodelCurrentReferencePosition.y  = spriteSubmodelCurrentReferencePosition.y + (double)SPRITE_LINE_SPACING_SIZE_IN_LDRAW_UNITS*scale;		//NB can remove *scale
			spriteSubmodelCurrentReferencePosition.x = 0.0 - ((double)SPRITES_FLOATING_WIDTH_IN_LDRAW_UNITS*scale / 2.0);						//NB can remove *scale
		}
		else if(((spriteText[spriteTextIndex] >= '0') && (spriteText[spriteTextIndex] <= '9')) || (spriteText[spriteTextIndex] == CHAR_PLUS) || (spriteText[spriteTextIndex] == CHAR_MINUS) || (spriteText[spriteTextIndex] == CHAR_EQUALS) || (spriteText[spriteTextIndex] == CHAR_FULLSTOP))
		{

			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + (spriteTextKernelArray[spriteText[spriteTextIndex]]+SPRITE_TEXT_PADDING_IN_LDRAW_UNITS)*scale*SPRITE_TEXT_SCALE_FACTOR;

			if(!addIndividualSprites)
			{
				vec tempAbsPos;
				addVectors(&tempAbsPos, &spriteSubmodelCurrentReferencePosition, position);
				LDspriteSubmodelFillTextualReference(spriteSubmodelCurrentReference, &tempAbsPos, spriteText[spriteTextIndex], colour, scale*SPRITE_TEXT_SCALE_FACTOR);
			}
			else
			{
				LDspriteSubmodelFillTextualReference(spriteSubmodelCurrentReference, &spriteSubmodelCurrentReferencePosition, spriteText[spriteTextIndex], colour, scale*SPRITE_TEXT_SCALE_FACTOR);
			}

			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + (spriteTextKernelArray[spriteText[spriteTextIndex]]+SPRITE_TEXT_PADDING_IN_LDRAW_UNITS)*scale*SPRITE_TEXT_SCALE_FACTOR;

			Reference * newReference = new Reference();
			spriteSubmodelCurrentReference -> next = newReference;
			spriteSubmodelCurrentReference = spriteSubmodelCurrentReference -> next;
			*numSpritesAdded = *numSpritesAdded + 1;
		}
		else if((spriteText[spriteTextIndex] >= 'A') && (spriteText[spriteTextIndex] <= 'Z'))
		{
			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + (spriteTextKernelArray[spriteText[spriteTextIndex]]+SPRITE_TEXT_PADDING_IN_LDRAW_UNITS)*scale*SPRITE_TEXT_SCALE_FACTOR;

			if(!addIndividualSprites)
			{
				vec tempAbsPos;
				addVectors(&tempAbsPos, &spriteSubmodelCurrentReferencePosition, position);
				LDspriteSubmodelFillTextualReference(spriteSubmodelCurrentReference, &tempAbsPos, spriteText[spriteTextIndex], colour, scale*SPRITE_TEXT_SCALE_FACTOR);
			}
			else
			{
				LDspriteSubmodelFillTextualReference(spriteSubmodelCurrentReference, &spriteSubmodelCurrentReferencePosition, spriteText[spriteTextIndex], colour, scale*SPRITE_TEXT_SCALE_FACTOR);
			}
			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + (spriteTextKernelArray[spriteText[spriteTextIndex]]+SPRITE_TEXT_PADDING_IN_LDRAW_UNITS)*scale*SPRITE_TEXT_SCALE_FACTOR;

			Reference * newReference = new Reference();
			spriteSubmodelCurrentReference -> next = newReference;
			spriteSubmodelCurrentReference = spriteSubmodelCurrentReference -> next;
			*numSpritesAdded = *numSpritesAdded + 1;
		}
		else if(spriteText[spriteTextIndex] == ' ')
		{
			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + ((double)SPRITE_CHAR_SPACING_SIZE_IN_LDRAW_UNITS/2.0)*scale*SPRITE_TEXT_SCALE_FACTOR;
		}
		else
		{
		
		}
	}

	delete spriteText;

	return spriteSubmodelCurrentReference;
}



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
			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + (spriteTextKernelArray[spriteText[spriteTextIndex]]+SPRITE_TEXT_PADDING_IN_LDRAW_UNITS)*SPRITE_TEXT_SCALE_FACTOR;

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
			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + (spriteTextKernelArray[spriteText[spriteTextIndex]]+SPRITE_TEXT_PADDING_IN_LDRAW_UNITS)*SPRITE_TEXT_SCALE_FACTOR;

			Reference * newReference = new Reference();
			spriteSubmodelCurrentReference -> next = newReference;
			spriteSubmodelCurrentReference = spriteSubmodelCurrentReference -> next;
			*numSpritesAdded = *numSpritesAdded + 1;
		}
		else if((spriteText[spriteTextIndex] >= 'A') && (spriteText[spriteTextIndex] <= 'Z'))
		{
			//spriteCurrentCharacterSpacing = SPRITE_CHAR_SPACING_SIZE_IN_LDRAW_UNITS;
			//spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + spriteCurrentCharacterSpacing/2;
			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + (spriteTextKernelArray[spriteText[spriteTextIndex]]+SPRITE_TEXT_PADDING_IN_LDRAW_UNITS)*SPRITE_TEXT_SCALE_FACTOR;

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
			spriteSubmodelCurrentReferencePosition.x = spriteSubmodelCurrentReferencePosition.x + (spriteTextKernelArray[spriteText[spriteTextIndex]]+SPRITE_TEXT_PADDING_IN_LDRAW_UNITS)*SPRITE_TEXT_SCALE_FACTOR;

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





bool LDaddSpriteToSpriteReferenceList(vec * spriteSceneCoords, vec * eyeCoords, Reference * spriteListInitialReference, char * spriteReferenceFileName, int spriteDefaultColour, double spriteScaleFactor)
{
	//add sprite to spriteByteArray (replace sprite of sprite index, spriteIndex, if it already exists)

	bool result = true;

	Reference * spriteReference = new Reference();

	spriteReference->colour = spriteDefaultColour;
	spriteReference->type = REFERENCE_TYPE_SUBMODEL;
	mat spriteRotationMatrix;

	createIdentityMatrix(&spriteRotationMatrix);
	scaleMatrix(&spriteRotationMatrix, spriteScaleFactor);

	copyMatrixTwoIntoMatrixOne(&(spriteReference->deformationMatrix), &(spriteRotationMatrix));

	spriteReference->relativePosition.x = spriteSceneCoords->x;
	spriteReference->relativePosition.y = spriteSceneCoords->y;
	spriteReference->relativePosition.z = spriteSceneCoords->z;
	spriteReference->name = spriteReferenceFileName;

	int lineNumberInFileOfSprite;

	if(search1DrefListNameAndColourFindRef(spriteListInitialReference, spriteReference))
	{
		if(!search1DrefListNameAndColourReplaceRef(spriteListInitialReference, spriteReference, spriteReference))
		{
			cout << "error: cannot replace Reference in Sprite Reference List" << endl;
			cout << "\t spriteReference->colour  = \n" << spriteReference->colour  << endl;
			cout << "\t spriteReference->name = " << spriteReference->name << endl;
			result = false;
		}
	}
	else
	{
		if(!search1DrefListAddReference(spriteListInitialReference, spriteReference))
		{
			cout << "error: cannot add Reference to Sprite Reference List" << endl;
			cout << "\t spriteReference->colour  = \n" << spriteReference->colour  << endl;
			cout << "\t spriteReference->name = " << spriteReference->name << endl;
			result = false;
		}
	}

	delete spriteReference;

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

			lineNumberOfSpriteHeader = (sceneFileNumberOfLinesWithSprites-1);

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

			/*add a sprites to scene file*/

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

			/*add a sprite trailer to scene file*/

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

	copyMatrixTwoIntoMatrixOne(&(spriteSubmodelCurrentReference->deformationMatrix), &(currentDeformationMatrix));

	spriteSubmodelCurrentReference->name = referenceNameStart + tempString + referenceNameEnd;

	delete tempString;
}

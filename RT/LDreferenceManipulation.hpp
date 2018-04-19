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
 * File Name: LDreferenceManipulation.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3m13e 22-February-2018
 * /
 *******************************************************************************/


#ifndef HEADER_LD_REFERENCE_MANIPULATION
#define HEADER_LD_REFERENCE_MANIPULATION

#include "LDreferenceClass.hpp"
#include "SHAREDvector.hpp"
#include "SHAREDvars.hpp"	//required for writeByteArrayToFile

#define DAT_FILE_GENERIC_MAX_SIZE (100000000)		//100MB - the maximum size of any ldraw .DAT/.LDR file

/*currently shared routines*/

#define SPRITE_HEADER_NAME "0 Start Sprites"
#define SPRITE_TRAILER_NAME "0 End Sprites"

#define CHAR_SPACE ' '
#define CHAR_NEWLINE '\n'

/*
#ifdef USE_RT
	#define FILE_FLOAT_PRECISION "%0.2f"
#else
	#define FILE_FLOAT_PRECISION "%0.4f"
#endif
*/
#ifdef USE_CS
	#define FILE_FLOAT_PRECISION "%0.4f"
#else
	#define FILE_FLOAT_PRECISION "%0.4f"
#endif

class LDreferenceManipulationClass
{
	private: SHAREDvectorClass SHAREDvector;
	private: SHAREDvarsClass SHAREDvars;
	public: LDreference* search1DrefListFindLastReference(LDreference* initialReferenceInList);
	public: bool search1DrefListFindRef(const LDreference* referenceToFind, const LDreference* initialReferenceInList);		//not currently used
	public: bool search1DrefListNameAndColourFindRef(LDreference* referenceToFind, const LDreference* initialReferenceInList);
	public: bool search1DrefListReplaceRef(const LDreference* referenceToFind, LDreference* referenceToReplaceWith, LDreference* initialReferenceInList);	//not currently used
	public: bool search1DrefListNameAndColourReplaceRef(LDreference* referenceToFind, LDreference* referenceToReplaceWith, LDreference* initialReferenceInList);
	public: bool search1DrefListAddReference(LDreference* initialReferenceInList, LDreference* referenceToAdd);
	public: bool compareReferenceNameAndColour(const LDreference* reference, const string referenceName, const int referenceColour);
	public: void copyReferences(LDreference* referenceNew, LDreference* referenceToCopy, const int type);
	public: bool compareReferences(const LDreference* reference1, const LDreference* reference2, const int type);


	public: string convertPositionCoordinatesToString(const vec* spriteSceneCoords);
	public: string convertPositionCoordinatesToStringWithCommaDelimiterPreceeding(const vec* spriteSceneCoords);

	public: bool writeReferencesToFile(const string fileName, LDreference* firstReference);
	public: bool addReferenceToFileObject(ofstream* writeFileObject, LDreference* currentReference);
		private: bool convertReferenceToString(LDreference* currentReference, string* referenceString);

	public: bool readFileIntoString(const string fileName, string* fileContentsString, int* fileNumberOfLines, int* fileByteArraySize);

	/*sprite routines*/
	public: string convertRotationMatrixToString(const mat* rotationMatrix);

	public: bool addSpriteReferenceListToSceneFile(const string sceneFileName, const string sceneFileNameWithSprites, LDreference* firstSpriteInReferenceList, const int spriteListByteArrayLines);

	public: bool write2DreferenceListCollapsedTo1DtoFile(const string fileName, LDreference* firstReference);
		private: bool write2DreferencesLayerToFileObject(ofstream* writeFileObject, LDreference* firstReferenceInLayer);

	public: bool joinReferenceLists(LDreference* initialReferenceInMainList, LDreference* initialReferenceInAdditionalList);
};

#endif

/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation. The use of
 * intermediary programs or interfaces including file i/o is considered
 * remote network interaction. This does not imply such arrangements
 * do not constitute derivative works.
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
 * File Name: LDreferenceManipulation.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3j1a 14-January-2017
 *
 *******************************************************************************/


#ifndef HEADER_LD_REFERENCE_MANIPULATION
#define HEADER_LD_REFERENCE_MANIPULATION

#include "LDreferenceClass.h"

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

LDreference* search1DrefListFindLastReference(LDreference* initialReferenceInList);
bool search1DrefListFindRef(const LDreference* referenceToFind, const LDreference* initialReferenceInList);		//not currently used
bool search1DrefListNameAndColourFindRef(LDreference* referenceToFind, const LDreference* initialReferenceInList);
bool search1DrefListReplaceRef(const LDreference* referenceToFind, LDreference* referenceToReplaceWith, LDreference* initialReferenceInList);	//not currently used
bool search1DrefListNameAndColourReplaceRef(LDreference* referenceToFind, LDreference* referenceToReplaceWith, LDreference* initialReferenceInList);
bool search1DrefListAddReference(LDreference* initialReferenceInList, LDreference* referenceToAdd);
bool compareReferenceNameAndColour(const LDreference* reference, const string referenceName, const int referenceColour);
void copyReferences(LDreference* referenceNew, LDreference* referenceToCopy, const int type);
bool compareReferences(const LDreference* reference1, const LDreference* reference2, const int type);


string convertPositionCoordinatesToString(const vec* spriteSceneCoords);
string convertPositionCoordinatesToStringWithCommaDelimiterPreceeding(const vec* spriteSceneCoords);

bool writeReferencesToFile(const string fileName, LDreference* firstReference);
bool addReferenceToFileObject(ofstream* writeFileObject, LDreference* currentReference);
	bool convertReferenceToString(LDreference* currentReference, string* referenceString);
bool openFileAndCopyDataIntoCurrentFileObject(const string fileToOpenName, ofstream* writeFileObject);

bool readFileIntoString(const string fileName, string* fileContentsString, int* fileNumberOfLines, int* fileByteArraySize);
void copyFiles(const string newFileName, const string fileToCopyName);

/*sprite routines*/
string convertRotationMatrixToString(const mat* rotationMatrix);

bool addSpriteReferenceListToSceneFile(const string sceneFileName, const string sceneFileNameWithSprites, LDreference* firstSpriteInReferenceList, const int spriteListByteArrayLines);

bool write2DreferenceListCollapsedTo1DtoFile(const string fileName, LDreference* firstReference);
	bool write2DreferencesLayerToFileObject(ofstream* writeFileObject, LDreference* firstReferenceInLayer);

bool joinReferenceLists(LDreference* initialReferenceInMainList, LDreference* initialReferenceInAdditionalList);

#endif

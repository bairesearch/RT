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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3e3b 01-September-2014
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

Reference * search1DrefListFindLastReference(Reference * initialReferenceInList);
bool search1DrefListFindRef(Reference * referenceToFind, Reference * initialReferenceInList);		//not currently used
bool search1DrefListNameAndColourFindRef(Reference * referenceToFind, Reference * initialReferenceInList);
bool search1DrefListReplaceRef(Reference * referenceToFind, Reference * referenceToReplaceWith, Reference * initialReferenceInList);	//not currently used
bool search1DrefListNameAndColourReplaceRef(Reference * referenceToFind, Reference * referenceToReplaceWith, Reference * initialReferenceInList);
bool search1DrefListAddReference(Reference * initialReferenceInList, Reference * referenceToAdd);
bool compareReferenceNameAndColour(Reference * reference, string referenceName, int referenceColour);
void copyReferences(Reference * referenceNew, Reference * referenceToCopy, int type);
bool compareReferences(Reference * reference1, Reference * reference2, int type);


string convertPositionCoordinatesToString(vec * spriteSceneCoords);
string convertPositionCoordinatesToStringWithCommaDelimiterPreceeding(vec * spriteSceneCoords);

bool writeReferencesToFile(string fileName, Reference * firstReference);
bool addReferenceToFileObject(ofstream * writeFileObject, Reference * currentReference);
	bool convertReferenceToString(Reference * currentReference, string * referenceString);
bool openFileAndCopyDataIntoCurrentFileObject(string fileToOpenName, ofstream * writeFileObject);

bool readFileIntoString(string fileName, string * fileContentsString, int * fileNumberOfLines, int * fileByteArraySize);
void copyFiles(string newFileName, string fileToCopyName);

/*sprite routines*/
string convertRotationMatrixToString(mat * rotationMatrix);

bool addSpriteReferenceListToSceneFile(string sceneFileName, string sceneFileNameWithSprites, Reference * firstSpriteInReferenceList, int spriteListByteArrayLines);

bool write2DreferenceListCollapsedTo1DtoFile(string fileName, Reference * firstReference);
	bool write2DreferencesLayerToFileObject(ofstream * writeFileObject, Reference * firstReferenceInLayer);

bool joinReferenceLists(Reference * initialReferenceInMainList, Reference * initialReferenceInAdditionalList);

#endif

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
 * File Name: LDreferenceManipulation.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3c5b 15-December-2012
 *
 *******************************************************************************/

#include "LDreferenceManipulation.h"
#include "SHAREDvector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;









/*currently shared routines*/








Reference * search1DrefListFindLastReference(Reference * initialReferenceInList)
{
	Reference * lastReference;
	Reference * currentReference = initialReferenceInList;

	while(currentReference->next != NULL)
	{
		currentReference = currentReference->next;
	}
	lastReference = currentReference;

	return lastReference;

}



bool search1DrefListFindRef(Reference * referenceToFind, Reference * initialReferenceInList)
{
	bool foundReference = false;

	Reference * currentReference = initialReferenceInList;

	while(currentReference->next != NULL)
	{
		if(compareReferences(currentReference, referenceToFind, referenceToFind->type))
		{
			foundReference = true;
		}

		currentReference = currentReference->next;
	}

	return foundReference;
}

bool search1DrefListNameAndColourFindRef(Reference * referenceToFind, Reference * initialReferenceInList)
{
	bool foundReference = false;

	Reference * currentReference = initialReferenceInList;

	while(currentReference->next != NULL)
	{
		if(compareReferenceNameAndColour(currentReference, (referenceToFind->name).c_str(), referenceToFind->colour))
		{
			foundReference = true;
		}

		currentReference = currentReference->next;
	}

	return foundReference;
}

bool search1DrefListReplaceRef(Reference * referenceToFind, Reference * referenceToReplaceWith, Reference * initialReferenceInList)
{
	bool foundReference = false;

	Reference * currentReference = initialReferenceInList;

	while(currentReference->next != NULL)
	{
		if(compareReferences(currentReference, referenceToFind, referenceToFind->type))
		{
			foundReference = true;
			copyReferences(currentReference, referenceToReplaceWith, referenceToReplaceWith->type);
		}

		currentReference = currentReference->next;
	}

	return foundReference;
}

bool search1DrefListNameAndColourReplaceRef(Reference * referenceToFind, Reference * referenceToReplaceWith, Reference * initialReferenceInList)
{
	bool foundReference = false;

	Reference * currentReference = initialReferenceInList;

	while(currentReference->next != NULL)
	{
		if(compareReferenceNameAndColour(currentReference, (referenceToFind->name).c_str(), referenceToFind->colour))
		{
			foundReference = true;
			copyReferences(currentReference, referenceToReplaceWith, referenceToReplaceWith->type);
		}

		currentReference = currentReference->next;
	}

	return foundReference;
}

bool search1DrefListAddReference(Reference * initialReferenceInList, Reference * referenceToAdd)
{
	bool foundReference = true;

	Reference * currentReference = initialReferenceInList;

	if(currentReference->next == NULL)
	{
		Reference * newReference = new Reference();
		copyReferences(currentReference, referenceToAdd, referenceToAdd->type);
		currentReference->next = newReference;
	}
	else
	{
		while(currentReference->next != NULL)
		{
			currentReference = currentReference->next;

			if(currentReference->next == NULL)
			{
				Reference * newReference = new Reference();
				copyReferences(currentReference, referenceToAdd, referenceToAdd->type);
				currentReference->next = newReference;
				currentReference = currentReference->next;
			}
		}
	}

	return foundReference;
}



bool compareReferenceNameAndColour(Reference * reference, string referenceName, int referenceColour)
{
	bool result = true;

	if(reference->name != referenceName)
	{
		result = false;
	}
	if(reference->colour != referenceColour)
	{
		result = false;
	}

	return result;
}

/*
bool compareSubmodelReferencesNameAndColour(Reference * reference1, Reference * reference2)
{
	bool result = true;

	if(reference1->type != reference2->type)
	{
		result = false;
	}
	if(reference1->colour != reference2->colour)
	{
		result = false;
	}

	return result;
}
*/


bool compareReferences(Reference * reference1, Reference * reference2, int type)
{
	bool result = true;

	if(reference1->type != reference2->type)
	{
		result = false;
	}
	if(reference1->colour != reference2->colour)
	{
		result = false;
	}

	if(type == REFERENCE_TYPE_SUBMODEL)
	{
		if(!compareVectors(&(reference1->relativePosition),  &(reference2->relativePosition)))
		{
			result = false;
		}
		if(!compareMatricies(&(reference1->deformationMatrix),  &(reference2->deformationMatrix)))
		{
			result = false;
		}
		if(reference1->name != reference2->name)
		{
			result = false;
		}
	}
	else
	{
		if((type == REFERENCE_TYPE_LINE) || (type == REFERENCE_TYPE_TRI) || (type == REFERENCE_TYPE_QUAD) || (type == REFERENCE_TYPE_OPTIONALLINE))
		{
			if(!compareVectors(&(reference1->vertex1relativePosition),  &(reference2->vertex1relativePosition)))
			{
				result = false;
			}
			if(!compareVectors(&(reference1->vertex2relativePosition),  &(reference2->vertex2relativePosition)))
			{
				result = false;
			}
		}
		if((type == REFERENCE_TYPE_TRI) || (type == REFERENCE_TYPE_QUAD) || (type == REFERENCE_TYPE_OPTIONALLINE))
		{
			if(!compareVectors(&(reference1->vertex3relativePosition),  &(reference2->vertex3relativePosition)))
			{
				result = false;
			}
		}
		if((type == REFERENCE_TYPE_QUAD) || (type == REFERENCE_TYPE_OPTIONALLINE))
		{
			if(!compareVectors(&(reference1->vertex4relativePosition),  &(reference2->vertex4relativePosition)))
			{
				result = false;
			}
		}
	}

	return result;
}

void copyReferences(Reference * referenceNew, Reference * referenceToCopy, int type)
{
	referenceNew->type = referenceToCopy->type;
	referenceNew->colour = referenceToCopy->colour;


	if(type == REFERENCE_TYPE_SUBMODEL)
	{
		copyVectors(&(referenceNew->relativePosition),  &(referenceToCopy->relativePosition));
		copyVectors(&(referenceNew->absolutePosition),  &(referenceToCopy->absolutePosition));
		copyMatricies(&(referenceNew->deformationMatrix),  &(referenceToCopy->deformationMatrix));
		referenceNew->name = referenceToCopy->name;
	}
	else
	{
		if((type == REFERENCE_TYPE_LINE) || (type == REFERENCE_TYPE_TRI) || (type == REFERENCE_TYPE_QUAD) || (type == REFERENCE_TYPE_OPTIONALLINE))
		{
			copyVectors(&(referenceNew->vertex1relativePosition),  &(referenceToCopy->vertex1relativePosition));
			copyVectors(&(referenceNew->vertex2relativePosition),  &(referenceToCopy->vertex2relativePosition));
		}
		if((type == REFERENCE_TYPE_TRI) || (type == REFERENCE_TYPE_QUAD) || (type == REFERENCE_TYPE_OPTIONALLINE))
		{
			copyVectors(&(referenceNew->vertex3relativePosition),  &(referenceToCopy->vertex3relativePosition));
		}
		if((type == REFERENCE_TYPE_QUAD) || (type == REFERENCE_TYPE_OPTIONALLINE))
		{
			copyVectors(&(referenceNew->vertex4relativePosition),  &(referenceToCopy->vertex4relativePosition));
		}
	}
}

void addNewLineCharacterToString(char * string)
{
	//write space to string
	char tempString[2];
	tempString[0] = '\n';
	tempString[1] = '\0';
	strcat(string, tempString);
}


void addSpaceCharacterToString(char * string)
{
	//write space to string
	char tempString[2];
	tempString[0] = ' ';
	tempString[1] = '\0';
	strcat(string, tempString);
}

void addArbitraryCharacterToString(char * string, char delimiter)
{
	//write space to string
	char tempString[2];
	tempString[0] = delimiter;
	tempString[1] = '\0';
	strcat(string, tempString);
}





void convertPositionCoordinatesToString(vec * spriteSceneCoords, char * string)
{
	char dataValueString[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "\0";
	string[0] = '\0';
	//_gcvt(spriteSceneCoords->x, DAT_FILE_DATA_VALUE_RECOMMENDED_LENGTH, dataValueString);
	sprintf(dataValueString, FILE_FLOAT_PRECISION, spriteSceneCoords->x);
	strcat(string, dataValueString);
	addSpaceCharacterToString(string);
	//_gcvt(spriteSceneCoords->y, DAT_FILE_DATA_VALUE_RECOMMENDED_LENGTH, dataValueString);
	sprintf(dataValueString, FILE_FLOAT_PRECISION, spriteSceneCoords->y);
	strcat(string, dataValueString);
	addSpaceCharacterToString(string);
	//_gcvt(spriteSceneCoords->z, DAT_FILE_DATA_VALUE_RECOMMENDED_LENGTH, dataValueString);
	sprintf(dataValueString, FILE_FLOAT_PRECISION, spriteSceneCoords->z);
	strcat(string, dataValueString);
	addSpaceCharacterToString(string);
}

void convertPositionCoordinatesToStringWithCommaDelimiterPreceeding(vec * spriteSceneCoords, char * string)
{
	char dataValueString[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "\0";
	string[0] = '\0';
	addArbitraryCharacterToString(string, ',');
	addArbitraryCharacterToString(string, ' ');
	//_gcvt(spriteSceneCoords->x, DAT_FILE_DATA_VALUE_RECOMMENDED_LENGTH, dataValueString);
	sprintf(dataValueString, FILE_FLOAT_PRECISION, spriteSceneCoords->x);
	strcat(string, dataValueString);
	addArbitraryCharacterToString(string, ',');
	addArbitraryCharacterToString(string, ' ');
	//_gcvt(spriteSceneCoords->y, DAT_FILE_DATA_VALUE_RECOMMENDED_LENGTH, dataValueString);
	sprintf(dataValueString, FILE_FLOAT_PRECISION, spriteSceneCoords->y);
	strcat(string, dataValueString);
	addArbitraryCharacterToString(string, ',');
	addArbitraryCharacterToString(string, ' ');
	//_gcvt(spriteSceneCoords->z, DAT_FILE_DATA_VALUE_RECOMMENDED_LENGTH, dataValueString);
	sprintf(dataValueString, FILE_FLOAT_PRECISION, spriteSceneCoords->z);
	strcat(string, dataValueString);

}







//OLD
bool writeReferencesToFileInefficient(char * fileName, Reference * firstReference)
{
	bool result = true;

	Reference * currentReference = firstReference;
	int temp;
	temp =DAT_FILE_REF_MAX_SIZE;
	temp =DAT_FILE_REF_MAX_SIZE*DAT_FILE_MAX_NUM_OF_REFERENCES;
	char * fileByteArray = new char[DAT_FILE_REF_MAX_SIZE*DAT_FILE_MAX_NUM_OF_REFERENCES];

	int fileByteArraySize = 0;

	//convertReferencesToByteArray
	convertReferencesToByteArray(currentReference, fileByteArray, &fileByteArraySize);

	//create file
	writeByteArrayToFile(fileName, fileByteArray, fileByteArraySize);

	delete fileByteArray;

	return result;
}

bool convertReferencesToByteArray(Reference * firstReference, char * fileByteArray, int * fileByteArraySize)
{
	bool result = true;

	Reference * currentReference = firstReference;

	//fill byte array
	int fileByteArrayByteIndex = 0;
	//int fileByteArrayReferenceIndex = 0;

	while((currentReference -> next) != NULL)
	{
		char * submodelReferenceString = new char[DAT_FILE_REF_MAX_SIZE];
		submodelReferenceString[0] = '\0';

		if(!convertReferenceToString(currentReference, submodelReferenceString))
		{
			result = false;
		}

		//write submodelReferenceString to fileByteArray
		int stringIndex = 0;

		while(submodelReferenceString[stringIndex] != '\0')
		{
			fileByteArray[fileByteArrayByteIndex+stringIndex] = submodelReferenceString[stringIndex];
			stringIndex++;
		}

		fileByteArrayByteIndex = fileByteArrayByteIndex + (int)strlen(submodelReferenceString);

		delete submodelReferenceString;

		currentReference = currentReference -> next;
	}

	*fileByteArraySize = fileByteArrayByteIndex;

	return result;
}









bool write2DreferenceListCollapsedTo1DtoFile(char * fileName, Reference * firstReference)
{
	ofstream writeFileObject(fileName);

	write2DreferencesLayerToFileObject(&writeFileObject, firstReference);

	writeFileObject.close();

	return true;
}


bool write2DreferencesLayerToFileObject(ofstream * writeFileObject, Reference * firstReferenceInLayer)
{
	bool result = true;

	Reference * currentReference = firstReferenceInLayer;
	while(currentReference->next != NULL)
	{
		if(currentReference->isSubModelReference)
		{

			result = write2DreferencesLayerToFileObject(writeFileObject, currentReference->firstReferenceWithinSubModel);
		}
		else
		{
			Reference collapsedReference;
			copyReferences(&collapsedReference, currentReference, currentReference->type);

			collapsedReference.relativePosition.x = currentReference->absolutePosition.x; //- currentReference->relativePosition.x;	//collapse 2D reference list to top level 1D reference list
			collapsedReference.relativePosition.y = currentReference->absolutePosition.y; // - currentReference->relativePosition.y;	//collapse 2D reference list to top level 1D reference list
			collapsedReference.relativePosition.z = currentReference->absolutePosition.z; // - currentReference->relativePosition.z;	//collapse 2D reference list to top level 1D reference list

			copyMatricies(&(collapsedReference.deformationMatrix), &(currentReference->absoluteDeformationMatrix));	//collapse 2D reference list to top level 1D reference list

			copyVectors(&(collapsedReference.vertex1relativePosition), &(currentReference->vertex1absolutePosition));
			copyVectors(&(collapsedReference.vertex2relativePosition), &(currentReference->vertex2absolutePosition));
			copyVectors(&(collapsedReference.vertex3relativePosition), &(currentReference->vertex3absolutePosition));
			copyVectors(&(collapsedReference.vertex4relativePosition), &(currentReference->vertex4absolutePosition));

		#ifdef USE_LD_ABSOLUTE_COLOUR
			collapsedReference.colour = currentReference->absoluteColour;
		#endif

			if(currentReference->referenceEnabledMethod2DOD)
			{
				addReferenceToFileObject(writeFileObject, &collapsedReference);
			}

		}

		currentReference = currentReference->next;
	}

	return result;
}


bool writeReferencesToFile(char * fileName, Reference * firstReference)
{
	ofstream writeFileObject(fileName);

	Reference * currentReference = firstReference;
	while(currentReference->next != NULL)
	{
		addReferenceToFileObject(&writeFileObject, currentReference);
		currentReference = currentReference->next;
	}
	// Exactly 8 bytes written

	writeFileObject.close();

	return true;
}


//preconditions; submodelReferenceString must be long enough to store all reference information that is to be written to it
bool convertReferenceToString(Reference * currentReference, char * referenceString)
{
	bool result = true;

	char dataValueString[DAT_FILE_DATA_VALUE_MAX_LENGTH];
	char positionCoordinatesString[DAT_FILE_REF_POS_COORD_MAX_LENGTH];
	char rotationMatrixString[DAT_FILE_REF_MATRIX_MAX_LENGTH];

	referenceString[0] = '\0';

	//write reference type
	sprintf(dataValueString, "%d", currentReference->type);
	strcat(referenceString, dataValueString);
	addSpaceCharacterToString(referenceString);

	//write reference colour
	sprintf(dataValueString, "%d", currentReference->colour);
	strcat(referenceString, dataValueString);
	addSpaceCharacterToString(referenceString);

	if(currentReference->type == REFERENCE_TYPE_SUBMODEL)
	{
		//write position coords
		vec submodelPositionCoordinatesVec;
		submodelPositionCoordinatesVec.x = currentReference->relativePosition.x;
		submodelPositionCoordinatesVec.y = currentReference->relativePosition.y;
		submodelPositionCoordinatesVec.z = currentReference->relativePosition.z;
		convertPositionCoordinatesToString(&submodelPositionCoordinatesVec, positionCoordinatesString);
		strcat(referenceString, positionCoordinatesString);

		//write rotation matrix values
		mat submodelRotationMatrix;
		copyMatrixTwoIntoMatrixOne(&submodelRotationMatrix, &(currentReference->deformationMatrix));

		convertRotationMatrixToString(&submodelRotationMatrix, rotationMatrixString);
		strcat(referenceString, rotationMatrixString);

		//write submodel name
		strcat(referenceString, (currentReference->name).c_str());		//convert string to char*
	}
	else if((currentReference->type == REFERENCE_TYPE_OPTIONALLINE) || (currentReference->type == REFERENCE_TYPE_TRI) || (currentReference->type == REFERENCE_TYPE_QUAD) || (currentReference->type == REFERENCE_TYPE_LINE))
	{
		//write primitive vertex coords

		convertPositionCoordinatesToString(&(currentReference->vertex1relativePosition), positionCoordinatesString);
		strcat(referenceString, positionCoordinatesString);

		convertPositionCoordinatesToString(&(currentReference->vertex2relativePosition), positionCoordinatesString);
		strcat(referenceString, positionCoordinatesString);

		if((currentReference->type == REFERENCE_TYPE_OPTIONALLINE) || (currentReference->type == REFERENCE_TYPE_TRI) || (currentReference->type == REFERENCE_TYPE_QUAD))
		{
			convertPositionCoordinatesToString(&(currentReference->vertex3relativePosition), positionCoordinatesString);
			strcat(referenceString, positionCoordinatesString);

			if((currentReference->type == REFERENCE_TYPE_OPTIONALLINE) || (currentReference->type == REFERENCE_TYPE_QUAD))
			{
				convertPositionCoordinatesToString(&(currentReference->vertex4relativePosition), positionCoordinatesString);
				strcat(referenceString, positionCoordinatesString);
			}
		}
	}
	else if(currentReference->type == REFERENCE_TYPE_COMMENT)
	{
		//write comment name
		strcat(referenceString, (currentReference->name).c_str ( ));
	}
	else
	{
		cout << "This reference type cannot be converted to string: name=" << currentReference->name << ", type=" << currentReference->type << endl;
	}

	//write new line
	addNewLineCharacterToString(referenceString);

	return result;
}

bool addReferenceToFileObjectInefficient(ofstream * writeFileObject, Reference * reference)
{

	char * referenceString = new char[DAT_FILE_REF_MAX_SIZE];
	convertReferenceToString(reference, referenceString);
	for(int i=0; i<strlen(referenceString); i++)
	{
		writeFileObject->put(referenceString[i]);
	}
	delete referenceString;

	return true;
}


//preconditions; submodelReferenceString must be long enough to store all reference information that is to be written to it
bool addReferenceToFileObject(ofstream * writeFileObject, Reference * currentReference)
{
	bool result = true;

	char dataValueString[DAT_FILE_DATA_VALUE_MAX_LENGTH];
	char positionCoordinatesString[DAT_FILE_REF_POS_COORD_MAX_LENGTH];
	char rotationMatrixString[DAT_FILE_REF_MATRIX_MAX_LENGTH];

	if(currentReference->type != REFERENCE_TYPE_COMMENT)
	{
		//write reference type
		sprintf(dataValueString, "%d", currentReference->type);

		for(int i = 0; i<strlen(dataValueString); i++)
		{
			writeFileObject->put(dataValueString[i]);
		}
		writeFileObject->put(CHAR_SPACE);

		//write reference colour
		sprintf(dataValueString, "%u", currentReference->colour);
		for(int i = 0; i<strlen(dataValueString); i++)
		{
			writeFileObject->put(dataValueString[i]);
		}
		writeFileObject->put(CHAR_SPACE);
	}


	if(currentReference->type == REFERENCE_TYPE_SUBMODEL)
	{
		//write position coords
		vec submodelPositionCoordinatesVec;
		submodelPositionCoordinatesVec.x = currentReference->relativePosition.x;
		submodelPositionCoordinatesVec.y = currentReference->relativePosition.y;
		submodelPositionCoordinatesVec.z = currentReference->relativePosition.z;
		convertPositionCoordinatesToString(&submodelPositionCoordinatesVec, positionCoordinatesString);
		for(int i = 0; i<strlen(positionCoordinatesString); i++)
		{
			writeFileObject->put(positionCoordinatesString[i]);
		}

		//write rotation matrix values
		mat submodelRotationMatrix;
		copyMatrixTwoIntoMatrixOne(&submodelRotationMatrix, &(currentReference->deformationMatrix));

		convertRotationMatrixToString(&submodelRotationMatrix, rotationMatrixString);

		for(int i = 0; i<strlen(rotationMatrixString); i++)
		{
			writeFileObject->put(rotationMatrixString[i]);
		}

		//write submodel name
		for(int i = 0; i<currentReference->name.length(); i++)
		{
			writeFileObject->put((currentReference->name)[i]);
		}
	}
	else if((currentReference->type == REFERENCE_TYPE_OPTIONALLINE) || (currentReference->type == REFERENCE_TYPE_TRI) || (currentReference->type == REFERENCE_TYPE_QUAD) || (currentReference->type == REFERENCE_TYPE_LINE))
	{
		//write primitive vertex coords

		convertPositionCoordinatesToString(&(currentReference->vertex1relativePosition), positionCoordinatesString);
		for(int i = 0; i<strlen(positionCoordinatesString); i++)
		{
			writeFileObject->put(positionCoordinatesString[i]);
		}

		convertPositionCoordinatesToString(&(currentReference->vertex2relativePosition), positionCoordinatesString);
		for(int i = 0; i<strlen(positionCoordinatesString); i++)
		{
			writeFileObject->put(positionCoordinatesString[i]);
		}

		if((currentReference->type == REFERENCE_TYPE_OPTIONALLINE) || (currentReference->type == REFERENCE_TYPE_TRI) || (currentReference->type == REFERENCE_TYPE_QUAD))
		{
			convertPositionCoordinatesToString(&(currentReference->vertex3relativePosition), positionCoordinatesString);
			for(int i = 0; i<strlen(positionCoordinatesString); i++)
			{
				writeFileObject->put(positionCoordinatesString[i]);
			}

			if((currentReference->type == REFERENCE_TYPE_OPTIONALLINE) || (currentReference->type == REFERENCE_TYPE_QUAD))
			{
				convertPositionCoordinatesToString(&(currentReference->vertex4relativePosition), positionCoordinatesString);
				for(int i = 0; i<strlen(positionCoordinatesString); i++)
				{
					writeFileObject->put(positionCoordinatesString[i]);
				}
			}
		}
	}
	else if(currentReference->type == REFERENCE_TYPE_COMMENT)
	{
		//write comment name
		for(int i = 0; i<currentReference->name.length(); i++)
		{
			writeFileObject->put((currentReference->name)[i]);
		}
	}
	else
	{
		cout << "This reference type cannot be converted to string: name=" << currentReference->name << ", type=" << currentReference->type << endl;
	}

	//write new line
	writeFileObject->put(CHAR_NEWLINE);

	return result;
}



bool openFileAndCopyDataIntoCurrentFileObject(char * fileToOpenName, ofstream * writeFileObject)
{
	bool result = true;
	char c;	//current character being read in
	int currentLine = 1;
	int index = 0;

	ifstream parseFileObject(fileToOpenName);

	//2. fill in the data array
	if(!parseFileObject.rdbuf( )->is_open( ))
	{
		//file does not exist in current directory.
		cout << "file, " << fileToOpenName << " cannot be opened" << endl;
		result = false;
	}
	else
	{
		while ((parseFileObject).get(c))
		{
			writeFileObject->put(c);
			if(c == '\n')
			{
				currentLine++;
			}
			index++;
		}
		parseFileObject.close();
	}

	return result;
}












void writeByteArrayToFile(char * fileName, char * fileByteArray, int fileByteArraySize)
{
	ofstream parseFileObject(fileName);

	// Exactly 8 bytes written
	parseFileObject.write(fileByteArray, (sizeof(char)*fileByteArraySize));

	parseFileObject.close();

}

bool readFileIntoByteArray(char * fileName, char * fileByteArray, int * fileNumberOfLines, int * fileByteArraySize)
{
	bool result = true;
	char c;	//current character being read in
	int currentLine = 1;
	int index = 0;

	ifstream parseFileObject(fileName);

	//2. fill in the data array
	if(!parseFileObject.rdbuf( )->is_open( ))
	{
		//file does not exist in current directory.
		cout << "file, " << fileName << " cannot be opened" << endl;
		result = false;
	}
	else
	{
		while ((parseFileObject).get(c))
		{
			fileByteArray[index] = c;
			if(c == '\n')
			{
				currentLine++;
			}
			index++;
		}
		parseFileObject.close();
		*fileNumberOfLines = currentLine;
		*fileByteArraySize = index;
	}
	
	return result;
}


bool readFileIntoString(string fileName, string * fileContentsString, int * fileNumberOfLines, int * fileByteArraySize)
{
	char * fileNamecharstar = const_cast<char*>(fileName.c_str());

	bool result = true;
	char c;	//current character being read in
	int currentLine = 1;
	int index = 0;

	ifstream parseFileObject(fileNamecharstar);

	//2. fill in the data array
	if(!parseFileObject.rdbuf( )->is_open( ))
	{
		//file does not exist in current directory.
		//cout << "file, " << fileName << " cannot be opened" << endl;
		result = false;
	}
	else
	{
		while ((parseFileObject).get(c))
		{
			*fileContentsString = *fileContentsString + c;
			if(c == '\n')
			{
				currentLine++;
			}
			index++;
		}
		parseFileObject.close();
		*fileNumberOfLines = currentLine;
		*fileByteArraySize = index;
	}

	return result;
}



void copyFiles(char * newFileName, char * fileToCopyName)
{
	ofstream writeFileObject(newFileName);

	openFileAndCopyDataIntoCurrentFileObject(fileToCopyName, &writeFileObject);

	writeFileObject.close();
}

void copyFilesInefficient(char * newFileName, char * fileToCopyName)
{
	int fileNumberOfLines = 0;
	int fileByteArraySize = 0;
	char * fileByteArray = new char[DAT_FILE_REF_MAX_SIZE*DAT_FILE_MAX_NUM_OF_REFERENCES];

	readFileIntoByteArray(fileToCopyName, fileByteArray, &fileNumberOfLines, &fileByteArraySize);

	writeByteArrayToFile(newFileName, fileByteArray, fileByteArraySize);

	delete fileByteArray;
}




bool addSpriteReferenceListToSceneFile(char * sceneFileName, char * sceneFileNameWithSprites, Reference * firstSpriteInReferenceList, int spriteListByteArrayLines)
{
	bool result = true;

	char * spriteHeaderSearchString = SPRITE_HEADER_NAME;
	char * spriteTrailerSearchString = SPRITE_TRAILER_NAME;

	ofstream writeFileObject(sceneFileNameWithSprites);

	//add original data
	openFileAndCopyDataIntoCurrentFileObject(sceneFileName, &writeFileObject);

	//add sprite header
	Reference spriteHeaderReference;
	spriteHeaderReference.type = REFERENCE_TYPE_COMMENT;
	spriteHeaderReference.name = SPRITE_HEADER_NAME;
	addReferenceToFileObject(&writeFileObject, &spriteHeaderReference);

	//add sprite data
	Reference * currentReference = firstSpriteInReferenceList;
	while(currentReference->next != NULL)
	{
		addReferenceToFileObject(&writeFileObject, currentReference);
		currentReference = currentReference->next;
	}

	//add sprite trailer
	Reference spriteTrailerReference;
	spriteTrailerReference.type = REFERENCE_TYPE_COMMENT;
	spriteTrailerReference.name = SPRITE_TRAILER_NAME;
	addReferenceToFileObject(&writeFileObject, &spriteTrailerReference);

	writeFileObject.close();

	return true;
}































/*sprite routines*/


void convertRotationMatrixToString(mat * rotationMatrix, char * string)
{
	char dataValueString[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "\0";
	string[0] = '\0';

	sprintf(dataValueString, "%0.4f", rotationMatrix->a.x);
	strcat(string, dataValueString);
	addSpaceCharacterToString(string);
	sprintf(dataValueString, "%0.4f", rotationMatrix->b.x);
	strcat(string, dataValueString);
	addSpaceCharacterToString(string);
	sprintf(dataValueString, "%0.4f", rotationMatrix->c.x);
	strcat(string, dataValueString);
	addSpaceCharacterToString(string);
	sprintf(dataValueString, "%0.4f", rotationMatrix->a.y);
	strcat(string, dataValueString);
	addSpaceCharacterToString(string);
	sprintf(dataValueString, "%0.4f", rotationMatrix->b.y);
	strcat(string, dataValueString);
	addSpaceCharacterToString(string);
	sprintf(dataValueString, "%0.4f", rotationMatrix->c.y);
	strcat(string, dataValueString);
	addSpaceCharacterToString(string);
	sprintf(dataValueString, "%0.4f", rotationMatrix->a.z);
	strcat(string, dataValueString);
	addSpaceCharacterToString(string);
	sprintf(dataValueString, "%0.4f", rotationMatrix->b.z);
	strcat(string, dataValueString);
	addSpaceCharacterToString(string);
	sprintf(dataValueString, "%0.4f", rotationMatrix->c.z);
	strcat(string, dataValueString);
	addSpaceCharacterToString(string);
}






































/*old sprite routines*/
bool findTextInByteArray(char * byteArray, int byteArraySize, char * searchString, int searchStringLength, int * lineNumberOfReference)
{
	bool result = false;
	int index;
	int lineNumber = 0;
	int searchStringIndex = 0;

	for(index = 0; index < byteArraySize; index++)
	{
		if(byteArray[index] == searchString[searchStringIndex])
		{
			searchStringIndex++;
			if(searchStringIndex == searchStringLength)
			{
				result = true;
				*lineNumberOfReference = lineNumber;
				searchStringIndex = 0;
			}
		}
		else
		{
			searchStringIndex = 0;
		}

		if(byteArray[index] == '\n')
		{
			lineNumber++;
		}
		index++;
	}

	return result;
}

//precondition - there is enough room in the byteArray space to add an extra lines worth of bytes

bool addLinesToByteArray(char * byteArray, char * lineByteArray, int * byteArraySize, int lineByteArraySize, int lineNumberToAdd)
{
	return replaceLinesInByteArray(byteArray, lineByteArray, byteArraySize, lineByteArraySize, lineNumberToAdd, 0);
}


bool replaceLinesInByteArray(char * byteArray, char * lineByteArray, int * byteArraySize, int lineByteArraySize, int lineNumberToReplace, int numberOfLinesToReplace)
{
	bool result = true;
	char * tempByteArray = new char[*byteArraySize];
	int tempByteArrayIndex = 0;
	bool addingToTempArray = false;
	int lineNumber = 0;
	int byteArrayIndexOfLineToReplace = 0;

	int index;
	for(index = 0; index < *byteArraySize; index++)
	{
		if(byteArray[index] == '\n')
		{
			lineNumber++;
		}
		if((lineNumber == lineNumberToReplace) && (addingToTempArray == false))
		{
			byteArrayIndexOfLineToReplace = index;
		}
		if(lineNumber == lineNumberToReplace+numberOfLinesToReplace)
		{
			addingToTempArray = true;
		}
		if(addingToTempArray)
		{
			tempByteArray[tempByteArrayIndex] = byteArray[index];
			tempByteArrayIndex++;
		}
	}

	if(*byteArraySize != 0)
	{
		if(addingToTempArray == false)
		{
			cout << "error: (addingToTempArray == false)" << endl;
			result = false;
		}
		if(tempByteArrayIndex == 0)
		{
			cout << "error: (tempByteArrayIndex == 0)" << endl;
			result = false;
		}
	}

	if(result == true)
	{
		for(index = 0; index < lineByteArraySize; index++)
		{
			byteArray[byteArrayIndexOfLineToReplace+index] = lineByteArray[index];
		}

		for(index = 0; index < (*byteArraySize - byteArrayIndexOfLineToReplace); index++)
		{
			byteArray[byteArrayIndexOfLineToReplace+lineByteArraySize+index] = tempByteArray[index];
		}

		*byteArraySize = *byteArraySize + lineByteArraySize - numberOfLinesToReplace;
	}

	delete tempByteArray;

	return result;
}






bool joinReferenceLists(Reference * initialReferenceInMainList, Reference * initialReferenceInAdditionalList)
{
	Reference * currentReferenceInMainList = initialReferenceInMainList;
	while(currentReferenceInMainList->next != NULL)
	{
		currentReferenceInMainList = currentReferenceInMainList->next;
	}
	currentReferenceInMainList = initialReferenceInAdditionalList;

	return true;
}


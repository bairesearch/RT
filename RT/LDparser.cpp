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
 * File Name: LDparser.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3d5c 05-August-2014
 *
 *******************************************************************************/

#include "LDparser.h"
#include "SHAREDvector.h"
#include "LDreferenceClass.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;


bool removeWhiteSpaceFromString(char * s)
{
	#define MAX_STR_LEN (100)
	char tmpStr[MAX_STR_LEN];
	strcpy(tmpStr, s);
	int newIndex = 0;
	for(int i=0; i<MAX_STR_LEN; i++)
	{
		if(tmpStr[i] == ' ')
		{

		}
		else
		{
			s[newIndex] = tmpStr[i];
			newIndex++;
		}
	}
	s[newIndex] = '\0';

	return true;
}

bool parseFile(char * parseFileName, Reference * initialReference, Reference * parentReference, bool recurseIntoPartsDir)
{
	bool result = true;

	int charCount = 0;
	int lineCount = 0;

	char c;	//current character being read in

		/*new parameters added to parseFile() 18-mar-07*/
	int type = REFERENCE_TYPE_UNDEFINED;
	bool readingVertex1X = false;
	bool readingVertex1Y = false;
	bool readingVertex1Z = false;
	bool readingVertex2X = false;
	bool readingVertex2Y = false;
	bool readingVertex2Z = false;
	bool readingVertex3X = false;
	bool readingVertex3Y = false;
	bool readingVertex3Z = false;
	bool readingVertex4X = false;
	bool readingVertex4Y = false;
	bool readingVertex4Z = false;
	char vertex1X[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char vertex1Y[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char vertex1Z[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char vertex2X[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char vertex2Y[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char vertex2Z[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char vertex3X[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char vertex3Y[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char vertex3Z[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char vertex4X[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char vertex4Y[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char vertex4Z[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	bool finishedReadingReference = false;

	bool readingType = true;
	bool readingColour = false;
	bool readingCoordX = false;
   	bool readingCoordY = false;
	bool readingCoordZ = false;
	bool readingRotation1 = false;
	bool readingRotation2 = false;
	bool readingRotation3 = false;
	bool readingRotation4 = false;
	bool readingRotation5 = false;
	bool readingRotation6 = false;
	bool readingRotation7 = false;
	bool readingRotation8 = false;
	bool readingRotation9 = false;
	bool readingSubPartFileName = false;
	bool waitingForNewLine = false;
	char colour[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char coordX[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char coordY[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char coordZ[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char rotation1[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char rotation2[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char rotation3[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char rotation4[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char rotation5[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char rotation6[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char rotation7[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char rotation8[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char rotation9[DAT_FILE_DATA_VALUE_MAX_LENGTH] = "";
	char subPartFileName[DAT_FILE_REF_SUBMODEL_NAME_LENGTH_MAX] = "";

	Reference * currentReference = initialReference;

	ifstream * parseFileObject = new ifstream(parseFileName);
	bool managedToFindFile = false;

	if(!parseFileObject->rdbuf( )->is_open( ))
	{
		parseFileObject->close();
		delete parseFileObject;

		if(recurseIntoPartsDir)
		{
			char parseFileNameInPartsDir[100];
			parseFileNameInPartsDir[0] = '\0';
			strcat(parseFileNameInPartsDir, DEFAULT_PARTS_DIRECTORY_FULL_PATH);
			removeWhiteSpaceFromString(parseFileName);
			strcat(parseFileNameInPartsDir, parseFileName);
			parseFileObject = new ifstream(parseFileNameInPartsDir);
			if(!parseFileObject->rdbuf( )->is_open( ))
			{
				parseFileObject->close();
				delete parseFileObject;

				char parseFileNameInPartsDir[100];
				parseFileNameInPartsDir[0] = '\0';
				strcat(parseFileNameInPartsDir, DEFAULT_PRIMITIVES_DIRECTORY_FULL_PATH);
				removeWhiteSpaceFromString(parseFileName);
				strcat(parseFileNameInPartsDir, parseFileName);
				parseFileObject = new ifstream(parseFileNameInPartsDir);
				if(!parseFileObject->rdbuf( )->is_open( ))
				{
					parseFileObject->close();
					delete parseFileObject;

					//file does not exist in parts directory.
					managedToFindFile = false;
					result = false;
				}
				else
				{
					//gone into prim file.
					result = true;
					managedToFindFile = true;
				}
			}
			else
			{
				result = true;
				managedToFindFile = true;
			}

		}
		else
		{
			//file does not exist in current directory.
			managedToFindFile = false;
			result = false;
		}
	}
	else
	{
		result = true;
		managedToFindFile = true;
	}




	if(managedToFindFile)
	{
		while (parseFileObject->get(c))
		{
			charCount++;

			if((waitingForNewLine) && (c == '\n'))
			{
				lineCount++;
				waitingForNewLine = false;
				readingType = true;
			}
			else if(waitingForNewLine)
			{
				//do nothing, still waiting for new line
			}
			else if(readingType)
			{
				bool whiteSpaceLineDetectedInsteadOfReference = false;

				if(c == '0')
				{//comment detected
					waitingForNewLine = true;
					type = REFERENCE_TYPE_COMMENT;
				}
				else if(c == '1')
				{//submodel detected
					waitingForNewLine = false;
					type = REFERENCE_TYPE_SUBMODEL;
				}
				else if(c == '2')
				{//submodel detected
					waitingForNewLine = false;
					type = REFERENCE_TYPE_LINE;
				}
				else if(c == '3')
				{//tri primative detected
					waitingForNewLine = false;
					type = REFERENCE_TYPE_TRI;
				}
				else if(c == '4')
				{//quad primative detected
					waitingForNewLine = false;
					type = REFERENCE_TYPE_QUAD;
				}
				else if(c == '5')
				{//quad primative detected
					waitingForNewLine = true;
					type = REFERENCE_TYPE_OPTIONALLINE;
				}
				else
				{
					if((c == '\n') && (LD_PARSER_ALLOW_WHITE_SPACE))
					{
						lineCount++;
						//white space removal required for messy dat files from ldraw parts library
						whiteSpaceLineDetectedInsteadOfReference = true;
					}
					else if((c == '\t') && (LD_PARSER_ALLOW_WHITE_SPACE))
					{
						//white space removal required for messy dat files from ldraw parts library
						whiteSpaceLineDetectedInsteadOfReference = true;
					}
					else if((c == ' ') && (LD_PARSER_ALLOW_WHITE_SPACE))
					{
						//white space removal required for messy dat files from ldraw parts library
						whiteSpaceLineDetectedInsteadOfReference = true;
					}
					else
					{
						type = REFERENCE_TYPE_UNDEFINED;
						cout << "1" << endl;
						cout << "readingType = " << readingType << endl;
						cout << "Invalid ModelDetails. Corrupted file has been detected. Reference Type Illegal. \n" << endl;
						cout << "character charCount = "<< charCount << endl;
						cout << "lineCount = " << lineCount << endl;
						cout << "type = " << type << endl;
						cout << "parentReference->name = " << parentReference->name << endl;
						cout << "parseFileName = " << parseFileName << endl;
						cout << "character = " << c << endl;
						cout << "(int)character = " << (int)c << endl;
						exit(0);
					}
				}

				if(!whiteSpaceLineDetectedInsteadOfReference)
				{

					parseFileObject->get(c); //gets a blank/space
					if((c != ' ') && (type != REFERENCE_TYPE_COMMENT))
					{
						cout << "2" << endl;
						cout << "\n Invalid ModelDetails. Corrupted file has been detected. Value After Reference Type is not space \n" << endl;
						cout << "\n c = "<< c << endl;
						cout << "\n character charCount = "<< charCount << endl;
						cout << "\n lineCount = " << lineCount << endl;
						cout << "\n type = " << type << endl;
						cout << "parseFileName = " << parseFileName << endl;
						exit(0);
					}

					colour[0] = '\0';
					coordX[0] = '\0';
					coordY[0] = '\0';
					coordZ[0] = '\0';
					rotation1[0] = '\0';
					rotation2[0] = '\0';
					rotation3[0] = '\0';
					rotation4[0] = '\0';
					rotation5[0] = '\0';
					rotation6[0] = '\0';
					rotation7[0] = '\0';
					rotation8[0] = '\0';
					rotation9[0] = '\0';

					vertex1X[0] = '\0';
					vertex1Y[0] = '\0';
					vertex1Z[0] = '\0';
					vertex2X[0] = '\0';
					vertex2Y[0] = '\0';
					vertex2Z[0] = '\0';
					vertex3X[0] = '\0';
					vertex3Y[0] = '\0';
					vertex3Z[0] = '\0';
					vertex4X[0] = '\0';
					vertex4Y[0] = '\0';
					vertex4Z[0] = '\0';

					subPartFileName[0] = '\0';

					readingType = false;
					readingColour = true;
				}
			}
			else
			{
				if((type == REFERENCE_TYPE_LINE) || (type == REFERENCE_TYPE_QUAD) || (type == REFERENCE_TYPE_TRI))
				{

					if((readingColour) && (c == ' '))
					{
						readingColour = false;
						readingVertex1X = true;
					}
					else if(readingColour)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(colour, typeString);
					}

					else if((readingVertex1X) && (c == ' '))
					{
						readingVertex1X = false;
						readingVertex1Y = true;
					}
					else if(readingVertex1X)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(vertex1X, typeString);
					}
					else if((readingVertex1Y) && (c == ' '))
					{
						readingVertex1Y = false;
						readingVertex1Z = true;
					}
					else if(readingVertex1Y)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(vertex1Y, typeString);
					}
					else if((readingVertex1Z) && (c == ' '))
					{
						readingVertex1Z = false;
						readingVertex2X = true;
					}
					else if(readingVertex1Z)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(vertex1Z, typeString);
					}

					else if((readingVertex2X) && (c == ' '))
					{
						readingVertex2X = false;
						readingVertex2Y = true;
					}
					else if(readingVertex2X)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(vertex2X, typeString);
					}
					else if((readingVertex2Y) && (c == ' '))
					{
						readingVertex2Y = false;
						readingVertex2Z = true;
					}
					else if(readingVertex2Y)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(vertex2Y, typeString);
					}
					else if((readingVertex2Z) && ((c == ' ') || (c == '\n')))
					{
						readingVertex2Z = false;
						if(type == REFERENCE_TYPE_LINE)
						{
						#ifdef LD_USE_STRICT_PARSER
							if(c == '\n')
							{
							}
							else
							{
								cout << "3" << endl;
								cout << "Invalid ModelDetails. Corrupted file has been detected. Reference Type Line corrupt. \n" << endl;
								cout << "character charCount = "<< charCount << endl;
								cout << "lineCount = " << lineCount << endl;
								cout << "type = " << type << endl;
								cout << "filename = " << parentReference->name << endl;
								exit(0);
							}
						#endif
							lineCount++;
							finishedReadingReference = true;
							readingType = true;
						}
						else if((type == REFERENCE_TYPE_QUAD) || (type == REFERENCE_TYPE_TRI))
						{
							if(c == ' ')
							{
							}
							else
							{
								cout << "4" << endl;
								cout << "Invalid ModelDetails. Corrupted file has been detected. Reference Type Quad/Tri corrupt. \n" << endl;
								cout << "character charCount = "<< charCount << endl;
								cout << "lineCount = " << lineCount << endl;
								cout << "type = " << type << endl;
								cout << "filename = " << parentReference->name << endl;
								exit(0);
							}
							readingVertex3X = true;
						}
					}
					else if(readingVertex2Z)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(vertex2Z, typeString);
					}

					else if((readingVertex3X) && (c == ' '))
					{
						readingVertex3X = false;
						readingVertex3Y = true;
					}
					else if(readingVertex3X)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(vertex3X, typeString);
					}
					else if((readingVertex3Y) && (c == ' '))
					{
						readingVertex3Y = false;
						readingVertex3Z = true;
					}
					else if(readingVertex3Y)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(vertex3Y, typeString);
					}
					else if((readingVertex3Z) && ((c == ' ') || (c == '\n')))
					{
						readingVertex3Z = false;
						if(type == REFERENCE_TYPE_QUAD)
						{
							if(c == ' ')
							{
							}
							else
							{
								cout << "5" << endl;
								cout << "Invalid ModelDetails. Corrupted file has been detected. Reference Type Quad corrupt. \n" << endl;
								cout << "character charCount = "<< charCount << endl;
								cout << "lineCount = " << lineCount << endl;
								cout << "type = " << type << endl;
								cout << "filename = " << parentReference->name << endl;
								exit(0);
							}
							readingVertex4X = true;
						}
						else if(type == REFERENCE_TYPE_TRI)
						{

						#ifdef LD_USE_STRICT_PARSER
							if(c == '\n')
							{
							}
							else
							{
								cout << "6" << endl;
								cout << "Invalid ModelDetails. Corrupted file has been detected. Reference Type Tri corrupt. \n" << endl;
								cout << "character charCount = "<< charCount << endl;
								cout << "lineCount = " << lineCount << endl;
								cout << "type = " << type << endl;
								cout << "filename = " << parentReference->name << endl;
								exit(0);
							}
						#endif
							lineCount++;
							finishedReadingReference = true;
							readingType = true;
						}
					}
					else if(readingVertex3Z)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(vertex3Z, typeString);
					}

					else if((readingVertex4X) && (c == ' '))
					{
						readingVertex4X = false;
						readingVertex4Y = true;
					}
					else if(readingVertex4X)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(vertex4X, typeString);
					}
					else if((readingVertex4Y) && (c == ' '))
					{
						readingVertex4Y = false;
						readingVertex4Z = true;
					}
					else if(readingVertex4Y)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(vertex4Y, typeString);
					}
					else if((readingVertex4Z) && (c == '\n'))
					{
						lineCount++;
						readingVertex4Z = false;
						finishedReadingReference = true;
						readingType = true;
					}
					else if(readingVertex4Z)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(vertex4Z, typeString);
					}

					if(finishedReadingReference == true)
					{
						finishedReadingReference = false;

						//3. Record Reference information into current Reference object
						currentReference->type = type;

						currentReference->colour = (unsigned int)(atof(colour));
					#ifdef USE_LD_ABSOLUTE_COLOUR
						if(currentReference->colour == DAT_FILE_DEFAULT_COLOUR)
						{
							currentReference->absoluteColour = parentReference->absoluteColour;
						}
						else
						{
							currentReference->absoluteColour = currentReference->colour;
						}
					#endif

						currentReference->vertex1relativePosition.x = (atof(vertex1X));
						currentReference->vertex1relativePosition.y = (atof(vertex1Y));
						currentReference->vertex1relativePosition.z = (atof(vertex1Z));
						currentReference->vertex2relativePosition.x = (atof(vertex2X));
						currentReference->vertex2relativePosition.y = (atof(vertex2Y));
						currentReference->vertex2relativePosition.z = (atof(vertex2Z));
						currentReference->vertex3relativePosition.x = (atof(vertex3X));
						currentReference->vertex3relativePosition.y = (atof(vertex3Y));
						currentReference->vertex3relativePosition.z = (atof(vertex3Z));
						currentReference->vertex4relativePosition.x = (atof(vertex4X));
						currentReference->vertex4relativePosition.y = (atof(vertex4Y));
						currentReference->vertex4relativePosition.z = (atof(vertex4Z));

					#ifndef NO_ROTATION_OF_MODELS_ALLOWED

						currentReference->vertex1absolutePosition.x = calcModXPosBasedUponRotate(&(currentReference->vertex1relativePosition), &(parentReference->absoluteDeformationMatrix)) + parentReference->absolutePosition.x;
						currentReference->vertex1absolutePosition.y = calcModYPosBasedUponRotate(&(currentReference->vertex1relativePosition), &(parentReference->absoluteDeformationMatrix)) + parentReference->absolutePosition.y;
						currentReference->vertex1absolutePosition.z = calcModZPosBasedUponRotate(&(currentReference->vertex1relativePosition), &(parentReference->absoluteDeformationMatrix)) + parentReference->absolutePosition.z;
						currentReference->vertex2absolutePosition.x = calcModXPosBasedUponRotate(&(currentReference->vertex2relativePosition), &(parentReference->absoluteDeformationMatrix)) + parentReference->absolutePosition.x;
						currentReference->vertex2absolutePosition.y = calcModYPosBasedUponRotate(&(currentReference->vertex2relativePosition), &(parentReference->absoluteDeformationMatrix)) + parentReference->absolutePosition.y;
						currentReference->vertex2absolutePosition.z = calcModZPosBasedUponRotate(&(currentReference->vertex2relativePosition), &(parentReference->absoluteDeformationMatrix)) + parentReference->absolutePosition.z;
						currentReference->vertex3absolutePosition.x = calcModXPosBasedUponRotate(&(currentReference->vertex3relativePosition), &(parentReference->absoluteDeformationMatrix)) + parentReference->absolutePosition.x;
						currentReference->vertex3absolutePosition.y = calcModYPosBasedUponRotate(&(currentReference->vertex3relativePosition), &(parentReference->absoluteDeformationMatrix)) + parentReference->absolutePosition.y;
						currentReference->vertex3absolutePosition.z = calcModZPosBasedUponRotate(&(currentReference->vertex3relativePosition), &(parentReference->absoluteDeformationMatrix)) + parentReference->absolutePosition.z;
						currentReference->vertex4absolutePosition.x = calcModXPosBasedUponRotate(&(currentReference->vertex4relativePosition), &(parentReference->absoluteDeformationMatrix)) + parentReference->absolutePosition.x;
						currentReference->vertex4absolutePosition.y = calcModYPosBasedUponRotate(&(currentReference->vertex4relativePosition), &(parentReference->absoluteDeformationMatrix)) + parentReference->absolutePosition.y;
						currentReference->vertex4absolutePosition.z = calcModZPosBasedUponRotate(&(currentReference->vertex4relativePosition), &(parentReference->absoluteDeformationMatrix)) + parentReference->absolutePosition.z;
					#else
						currentReference->vertex1absolutePosition.x = currentReference->vertex1relativePosition.x + parentReference->absolutePosition.x;
						currentReference->vertex1absolutePosition.y = currentReference->vertex1relativePosition.y + parentReference->absolutePosition.y;
						currentReference->vertex1absolutePosition.z = currentReference->vertex1relativePosition.z + parentReference->absolutePosition.z;
						currentReference->vertex2absolutePosition.x = currentReference->vertex2relativePosition.x + parentReference->absolutePosition.x;
						currentReference->vertex2absolutePosition.y = currentReference->vertex2relativePosition.y + parentReference->absolutePosition.y;
						currentReference->vertex2absolutePosition.z = currentReference->vertex2relativePosition.z + parentReference->absolutePosition.z;
						currentReference->vertex3absolutePosition.x = currentReference->vertex3relativePosition.x + parentReference->absolutePosition.x;
						currentReference->vertex3absolutePosition.y = currentReference->vertex3relativePosition.y + parentReference->absolutePosition.y;
						currentReference->vertex3absolutePosition.z = currentReference->vertex3relativePosition.z + parentReference->absolutePosition.z;
						currentReference->vertex4absolutePosition.x = currentReference->vertex4relativePosition.x + parentReference->absolutePosition.x;
						currentReference->vertex4absolutePosition.y = currentReference->vertex4relativePosition.y + parentReference->absolutePosition.y;
						currentReference->vertex4absolutePosition.z = currentReference->vertex4relativePosition.z + parentReference->absolutePosition.z;
					#endif

						/*
						cout << "" << endl;
						cout << "currentReference->type = " << currentReference->type << endl;
						cout << "currentReference->colour = " << currentReference->colour << endl;
						cout << "currentReference->name = " << currentReference->name << endl;
						cout << "currentReference->vertex1relativePosition.x = " << currentReference->vertex1relativePosition.x << endl;
						cout << "currentReference->vertex1relativePosition.y = " << currentReference->vertex1relativePosition.y << endl;
						cout << "currentReference->vertex1relativePosition.z = " << currentReference->vertex1relativePosition.z << endl;
						cout << "currentReference->vertex2relativePosition.x = " << currentReference->vertex2relativePosition.x << endl;
						cout << "currentReference->vertex2relativePosition.y = " << currentReference->vertex2relativePosition.y << endl;
						cout << "currentReference->vertex2relativePosition.z = " << currentReference->vertex2relativePosition.z << endl;
						cout << "currentReference->vertex3relativePosition.x = " << currentReference->vertex3relativePosition.x << endl;
						cout << "currentReference->vertex3relativePosition.y = " << currentReference->vertex3relativePosition.y << endl;
						cout << "currentReference->vertex3relativePosition.z = " << currentReference->vertex3relativePosition.z << endl;
						cout << "currentReference->vertex4relativePosition.x = " << currentReference->vertex4relativePosition.x << endl;
						cout << "currentReference->vertex4relativePosition.y = " << currentReference->vertex4relativePosition.y << endl;
						cout << "currentReference->vertex4relativePosition.z = " << currentReference->vertex4relativePosition.z << endl;
						cout << "currentReference->vertex1absolutePosition.x = " << currentReference->vertex1absolutePosition.x << endl;
						cout << "currentReference->vertex1absolutePosition.y = " << currentReference->vertex1absolutePosition.y << endl;
						cout << "currentReference->vertex1absolutePosition.z = " << currentReference->vertex1absolutePosition.z << endl;
						cout << "currentReference->vertex2absolutePosition.x = " << currentReference->vertex2absolutePosition.x << endl;
						cout << "currentReference->vertex2absolutePosition.y = " << currentReference->vertex2absolutePosition.y << endl;
						cout << "currentReference->vertex2absolutePosition.z = " << currentReference->vertex2absolutePosition.z << endl;
						cout << "currentReference->vertex3absolutePosition.x = " << currentReference->vertex3absolutePosition.x << endl;
						cout << "currentReference->vertex3absolutePosition.y = " << currentReference->vertex3absolutePosition.y << endl;
						cout << "currentReference->vertex3absolutePosition.z = " << currentReference->vertex3absolutePosition.z << endl;
						cout << "currentReference->vertex4absolutePosition.x = " << currentReference->vertex4absolutePosition.x << endl;
						cout << "currentReference->vertex4absolutePosition.y = " << currentReference->vertex4absolutePosition.y << endl;
						cout << "currentReference->vertex4absolutePosition.z = " << currentReference->vertex4absolutePosition.z << endl;
						cout << "" << endl;
						*/


						//4. finalise Reference object
						//code to create a new reference object
						Reference * nextReference = new Reference();
						currentReference -> next = nextReference;
						currentReference = currentReference->next;
					}
				}
				else if(type == REFERENCE_TYPE_SUBMODEL)
				{
					if((readingColour) && (c == ' '))
					{
						readingColour = false;
						readingCoordX = true;
					}
					else if(readingColour)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(colour, typeString);
					}
					else if((readingCoordX) && (c == ' '))
					{
						readingCoordX = false;
						readingCoordY = true;
					}
					else if(readingCoordX)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(coordX, typeString);
					}
					else if((readingCoordY) && (c == ' '))
					{
						readingCoordY = false;
						readingCoordZ = true;
					}
					else if(readingCoordY)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(coordY, typeString);
					}
					else if((readingCoordZ) && (c == ' '))
					{
						readingCoordZ = false;
						readingRotation1 = true;
					}
					else if(readingCoordZ)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(coordZ, typeString);
					}
					else if((readingRotation1) && (c == ' '))
					{
						readingRotation1 = false;
						readingRotation2 = true;
					}
					else if(readingRotation1)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(rotation1, typeString);
					}
					else if((readingRotation2) && (c == ' '))
					{
						readingRotation2 = false;
						readingRotation3 = true;
					}
					else if(readingRotation2)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(rotation2, typeString);
					}
					else if((readingRotation3) && (c == ' '))
					{
						readingRotation3 = false;
						readingRotation4 = true;
					}
					else if(readingRotation3)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(rotation3, typeString);
					}
					else if((readingRotation4) && (c == ' '))
					{
						readingRotation4 = false;
						readingRotation5 = true;
					}
					else if(readingRotation4)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(rotation4, typeString);
					}
					else if((readingRotation5) && (c == ' '))
					{
						readingRotation5 = false;
						readingRotation6 = true;
					}
					else if(readingRotation5)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(rotation5, typeString);
					}
					else if((readingRotation6) && (c == ' '))
					{
						readingRotation6 = false;
						readingRotation7 = true;
					}
					else if(readingRotation6)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(rotation6, typeString);
					}
					else if((readingRotation7) && (c == ' '))
					{
						readingRotation7 = false;
						readingRotation8 = true;
					}
					else if(readingRotation7)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(rotation7, typeString);
					}
					else if((readingRotation8) && (c == ' '))
					{
						readingRotation8 = false;
						readingRotation9 = true;
					}
					else if(readingRotation8)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(rotation8, typeString);
					}
					else if((readingRotation9) && (c == ' '))
					{
						readingRotation9 = false;
						readingSubPartFileName = true;
					}
					else if(readingRotation9)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(rotation9, typeString);
					}
					else if((readingSubPartFileName) && (c == '\n'))
					{
						lineCount++;
						readingSubPartFileName = false;
						finishedReadingReference = true;
						readingType = true;
					}
					else if(readingSubPartFileName)
					{
						char typeString[2];
						typeString[0] = c;
						typeString[1] = '\0';
						strcat(subPartFileName, typeString);
					}

					if(finishedReadingReference == true)
					{
						finishedReadingReference = false;


						//3. Record Reference information into current Reference object
						currentReference->type = type;
						currentReference->colour = (unsigned int)(atof(colour));
					#ifdef USE_LD_ABSOLUTE_COLOUR
						if(currentReference->colour == DAT_FILE_DEFAULT_COLOUR)
						{
							currentReference->absoluteColour = parentReference->absoluteColour;
						}
						else
						{
							currentReference->absoluteColour = currentReference->colour;
						}
					#endif

						currentReference->relativePosition.x = (atof(coordX));
						currentReference->relativePosition.y = (atof(coordY));
						currentReference->relativePosition.z = (atof(coordZ));

							//26-jan-07 change; take into account rotation of parent reference in calculation of child reference absolute coordinates;
					#ifndef NO_ROTATION_OF_MODELS_ALLOWED

						currentReference->deformationMatrix.a.x = (atof(rotation1));
						currentReference->deformationMatrix.b.x = (atof(rotation2));
						currentReference->deformationMatrix.c.x = (atof(rotation3));
						currentReference->deformationMatrix.a.y = (atof(rotation4));
						currentReference->deformationMatrix.b.y = (atof(rotation5));
						currentReference->deformationMatrix.c.y = (atof(rotation6));
						currentReference->deformationMatrix.a.z = (atof(rotation7));
						currentReference->deformationMatrix.b.z = (atof(rotation8));
						currentReference->deformationMatrix.c.z = (atof(rotation9));

						multiplyMatricies(&(currentReference->absoluteDeformationMatrix), &(parentReference->absoluteDeformationMatrix), &(currentReference->deformationMatrix));

						currentReference->absolutePosition.x = calcModXPosBasedUponRotate(&(currentReference->relativePosition), &(parentReference->absoluteDeformationMatrix)) + parentReference->absolutePosition.x;
						currentReference->absolutePosition.y = calcModYPosBasedUponRotate(&(currentReference->relativePosition), &(parentReference->absoluteDeformationMatrix)) + parentReference->absolutePosition.y;
						currentReference->absolutePosition.z = calcModZPosBasedUponRotate(&(currentReference->relativePosition), &(parentReference->absoluteDeformationMatrix)) + parentReference->absolutePosition.z;

					#else
						currentReference->absolutePosition.x = currentReference->relativePosition.x + parentReference->absolutePosition.x;
						currentReference->absolutePosition.y = currentReference->relativePosition.y + parentReference->absolutePosition.y;
						currentReference->absolutePosition.z = currentReference->relativePosition.z + parentReference->absolutePosition.z;
					#endif


						currentReference->name = subPartFileName;


					#ifndef USE_OLC
						//1. Perform Recursion into sub files in designated search directory (default = current directory) if possible

							//code to create a new reference object
						Reference * subModelReference = new Reference(true);
						currentReference->firstReferenceWithinSubModel = subModelReference;

						subModelReference->isSubModelReference = false;	//added aug 08

						if(parseFile(subPartFileName, currentReference->firstReferenceWithinSubModel, currentReference, recurseIntoPartsDir))
						{
							//cout << "successfully parsed; currentReference->name = " <<  currentReference->name << endl;
							currentReference->isSubModelReference = true;
						}
						else
						{
							/*clear memory of currentReference->subModelReference and currentReference->subModelDetails as submodel does not exist*/
							delete subModelReference;
							currentReference->firstReferenceWithinSubModel = NULL;	//added aug 08
							currentReference->isSubModelReference = false;	//added aug 08
						}
					#endif

						/*
						cout << "" << endl;
						cout << "currentReference->type = " << currentReference->type << endl;
						cout << "currentReference->colour = " << currentReference->colour << endl;
						cout << "currentReference->relativePosition.x = " << currentReference->relativePosition.x << endl;
						cout << "currentReference->relativePosition.y = " << currentReference->relativePosition.y << endl;
						cout << "currentReference->relativePosition.z = " << currentReference->relativePosition.z << endl;
						cout << "currentReference->deformationMatrix.a.x = " << currentReference->deformationMatrix.a.x << endl;
						cout << "currentReference->deformationMatrix.b.x = " << currentReference->deformationMatrix.b.x << endl;
						cout << "currentReference->deformationMatrix.c.x = " << currentReference->deformationMatrix.c.x << endl;
						cout << "currentReference->deformationMatrix.a.y = " << currentReference->deformationMatrix.a.y << endl;
						cout << "currentReference->deformationMatrix.b.y = " << currentReference->deformationMatrix.b.y << endl;
						cout << "currentReference->deformationMatrix.c.y = " << currentReference->deformationMatrix.c.y << endl;
						cout << "currentReference->deformationMatrix.a.z = " << currentReference->deformationMatrix.a.z << endl;
						cout << "currentReference->deformationMatrix.b.z = " << currentReference->deformationMatrix.b.z << endl;
						cout << "currentReference->deformationMatrix.c.z = " << currentReference->deformationMatrix.c.z << endl;
						cout << "currentReference->name = " << currentReference->name << endl;
						*/

						//4. finalise Reference object

						//code to create a new reference object
						Reference * nextReference = new Reference();
						currentReference -> next = nextReference;
						currentReference = currentReference->next;
					}
				}
			}
		}

		parseFileObject->close();
		delete parseFileObject;
	}


	return result;
}




double calcModXPosBasedUponRotate(vec * childRelativePosition, mat * parentReferenceDeformationMatrix)
{
	double xPosBasedUponRotatedParent;

	xPosBasedUponRotatedParent = ((parentReferenceDeformationMatrix->a.x * childRelativePosition->x) + (parentReferenceDeformationMatrix->b.x * childRelativePosition->y) + (parentReferenceDeformationMatrix->c.x * childRelativePosition->z));

	return xPosBasedUponRotatedParent;
}

double calcModYPosBasedUponRotate(vec * childRelativePosition, mat * parentReferenceDeformationMatrix)
{
	double yPosBasedUponRotatedParent;

	yPosBasedUponRotatedParent = ((parentReferenceDeformationMatrix->a.y * childRelativePosition->x) + (parentReferenceDeformationMatrix->b.y * childRelativePosition->y) + (parentReferenceDeformationMatrix->c.y * childRelativePosition->z));

	return yPosBasedUponRotatedParent;
}


double calcModZPosBasedUponRotate(vec * childRelativePosition, mat * parentReferenceDeformationMatrix)
{
	double zPosBasedUponRotatedParent;

	zPosBasedUponRotatedParent = ((parentReferenceDeformationMatrix->a.z * childRelativePosition->x) + (parentReferenceDeformationMatrix->b.z * childRelativePosition->y) + (parentReferenceDeformationMatrix->c.z * childRelativePosition->z));

	return zPosBasedUponRotatedParent;
}




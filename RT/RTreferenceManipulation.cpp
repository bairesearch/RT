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
 * File Name: RTreferenceManipulation.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3a13a 24-Sept-2012
 *
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;

#include "RTreferenceManipulation.h"
#include "LDreferenceManipulation.h"
#include "SHAREDvector.h"
#include "RToperations.h"


bool write2DReferenceListCollapsedTo1DToFileRayTraceFormat(char * fileName, Reference * firstReference, bool useCustomViewInfo, view_info * vi, bool useCustomLightSource, vec * lightSourcePosition, char * lightSourceColour)
{
	ofstream writeFileObject;
	writeFileObject.open(fileName);
	if(writeFileObject.is_open())
	{
		writeRayTraceFormatHeaderInfo(&writeFileObject, useCustomViewInfo, vi, useCustomLightSource, lightSourcePosition, lightSourceColour);

		write2DReferencesLayerToFileObjectRayTraceFormat(&writeFileObject, firstReference);

		writeFileObject.close();
	}
	else
	{
		cout << "Error: cannot create new file, " << fileName << endl;
		exit(0);
	}
}



bool writeRayTraceFormatHeaderInfo(ofstream * writeFileObject, bool useCustomViewInfo, view_info * vi, bool useCustomLightSource, vec * lightSourcePosition, char * lightSourceColour)
{
	/*
	#ifdef COMPILE_TH_RT
		printf("1");
		exit(0);
	#elif defined COMPILE_TH_ANN_WITH_LRRC
		printf("2");
		printf("width= %d ", (int)TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_WIDTH);
		exit(0);
	#else
		printf("3");
		exit(0);
	#endif
	*/

	char tempDataValueString[100];
	string dataValueString;


	int imgwidth;
	int imgheight;
	if(useCustomViewInfo)
	{
		imgwidth = vi->imgwidth;
		imgheight = vi->imgheight;
	}
	else
	{
		imgwidth = TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_WIDTH;
		imgheight = TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_HEIGHT;
	}
	sprintf(tempDataValueString, "%d", imgwidth);
	string imgwidthString = tempDataValueString;
	sprintf(tempDataValueString, "%d", imgheight);
	string imgheightString = tempDataValueString;
	dataValueString = "";
	dataValueString = dataValueString + TAL_FILE_HEADER_IMAGE_SIZE + " " + imgwidthString + " " + imgheightString;

	for(int i = 0; i<dataValueString.length(); i++)
	{
		writeFileObject->put(dataValueString[i]);
	}
	writeFileObject->put(CHAR_NEWLINE);


	double eyex;
	double eyey;
	double eyez;
	if(useCustomViewInfo)
	{
		eyex = vi->eye.x;
		eyey = vi->eye.y;
		eyez = vi->eye.z;
	}
	else
	{
		eyex = TAL_FILE_HEADER_DEFAULT_EYE_X;
		eyey = TAL_FILE_HEADER_DEFAULT_EYE_Y;
		eyez = TAL_FILE_HEADER_DEFAULT_EYE_Z;
	}
	sprintf(tempDataValueString, "%0.4f", eyex);
	string eyexString = tempDataValueString;
	sprintf(tempDataValueString, "%0.4f", eyey);
	string eyeyString = tempDataValueString;
	sprintf(tempDataValueString, "%0.4f", eyez);
	string eyezString = tempDataValueString;
	dataValueString = "";
	dataValueString = dataValueString + TAL_FILE_HEADER_EYE + " " + eyexString + " " + eyeyString + " " + eyezString;

	for(int i = 0; i<dataValueString.length(); i++)
	{
		writeFileObject->put(dataValueString[i]);
	}
	writeFileObject->put(CHAR_NEWLINE);


	double viewatx;
	double viewaty;
	double viewatz;
	if(useCustomViewInfo)
	{
		viewatx = vi->viewat.x;
		viewaty = vi->viewat.y;
		viewatz = vi->viewat.z;
	}
	else
	{
		viewatx = TAL_FILE_HEADER_DEFAULT_VIEWAT_X;
		viewaty = TAL_FILE_HEADER_DEFAULT_VIEWAT_Y;
		viewatz = TAL_FILE_HEADER_DEFAULT_VIEWAT_Z;
	}
	sprintf(tempDataValueString, "%0.4f", viewatx);
	string viewatxString = tempDataValueString;
	sprintf(tempDataValueString, "%0.4f", viewaty);
	string viewatyString = tempDataValueString;
	sprintf(tempDataValueString, "%0.4f", viewatz);
	string viewatzString = tempDataValueString;
	dataValueString = "";
	dataValueString = dataValueString + TAL_FILE_HEADER_VIEWAT + " " + viewatxString + " " + viewatyString + " " + viewatzString;

	for(int i = 0; i<dataValueString.length(); i++)
	{
		writeFileObject->put(dataValueString[i]);
	}
	writeFileObject->put(CHAR_NEWLINE);


	double viewupx;
	double viewupy;
	double viewupz;
	if(useCustomViewInfo)
	{
		viewupx = vi->viewup.x;
		viewupy = vi->viewup.y;
		viewupz = vi->viewup.z;
	}
	else
	{
		viewupx = TAL_FILE_HEADER_DEFAULT_VIEWUP_X;
		viewupy = TAL_FILE_HEADER_DEFAULT_VIEWUP_Y;
		viewupz = TAL_FILE_HEADER_DEFAULT_VIEWUP_Z;
	}
	sprintf(tempDataValueString, "%0.4f", viewupx);
	string viewupxString = tempDataValueString;
	sprintf(tempDataValueString, "%0.4f", viewupy);
	string viewupyString = tempDataValueString;
	sprintf(tempDataValueString, "%0.4f", viewupz);
	string viewupzString = tempDataValueString;
	dataValueString = "";
	dataValueString = dataValueString + TAL_FILE_HEADER_VIEWUP + " " + viewupxString + " " + viewupyString + " " + viewupzString;
	for(int i = 0; i<dataValueString.length(); i++)
	{
		writeFileObject->put(dataValueString[i]);
	}
	writeFileObject->put(CHAR_NEWLINE);


	double focal_length;
	if(useCustomViewInfo)
	{
		focal_length = vi->focal_length;
	}
	else
	{
		focal_length = TAL_FILE_HEADER_DEFAULT_FOCAL;
	}
	sprintf(tempDataValueString, "%0.4f", focal_length);
	string focal_lengthString = tempDataValueString;
	dataValueString = "";
	dataValueString = dataValueString + TAL_FILE_HEADER_FOCAL + " " + focal_lengthString;
	for(int i = 0; i<dataValueString.length(); i++)
	{
		writeFileObject->put(dataValueString[i]);
	}
	writeFileObject->put(CHAR_NEWLINE);


	double viewwidth;
	double viewheight;
	if(useCustomViewInfo)
	{
		viewwidth = vi->viewwidth;
		viewheight = vi->viewheight;
	}
	else
	{
		viewwidth = TAL_FILE_HEADER_DEFAULT_VIEWSIZE_WIDTH;
		viewheight = TAL_FILE_HEADER_DEFAULT_VIEWSIZE_HEIGHT;
	}
	sprintf(tempDataValueString, "%0.4f", viewwidth);
	string viewwidthString = tempDataValueString;
	sprintf(tempDataValueString, "%0.4f", viewheight);
	string viewheightString = tempDataValueString;
	dataValueString = "";
	dataValueString = dataValueString + TAL_FILE_HEADER_VIEWSIZE + " " + viewwidthString + " " + viewheightString;
	for(int i = 0; i<dataValueString.length(); i++)
	{
		writeFileObject->put(dataValueString[i]);
	}
	writeFileObject->put(CHAR_NEWLINE);


	string lightSourcePositionxstring;
	string lightSourcePositionystring;
	string lightSourcePositionzstring;
	double lightSourcePositionx;
	double lightSourcePositiony;
	double lightSourcePositionz;
	string lightSourceColourString;

	if(useCustomLightSource)
	{
		lightSourcePositionx = lightSourcePosition->x;
		lightSourcePositiony = lightSourcePosition->y;
		lightSourcePositionz = lightSourcePosition->z;
		lightSourceColourString = lightSourceColour;
	}
	else
	{
		lightSourcePositionx = TAL_FILE_HEADER_DEFAULT_POINTSOURCE_X;
		lightSourcePositiony = TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Y;
		lightSourcePositionz = TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Z;
		lightSourceColourString = TAL_FILE_HEADER_DEFAULT_POINTSOURCE_COLOUR;
	}


	sprintf(tempDataValueString, "%0.1f", lightSourcePositionx);
	lightSourcePositionxstring = tempDataValueString;
	sprintf(tempDataValueString, "%0.1f", lightSourcePositiony);
	lightSourcePositionystring = tempDataValueString;
	sprintf(tempDataValueString, "%0.1f", lightSourcePositionz);
	lightSourcePositionzstring = tempDataValueString;

	//light source cannot currently be customised
	dataValueString = "";
	dataValueString = dataValueString + TAL_FILE_HEADER_POINTSOURCE + " " + lightSourcePositionxstring + " " + lightSourcePositionystring + " " + lightSourcePositionzstring + " " + lightSourceColourString;	//TAL_FILE_HEADER_DEFAULT_POINTSOURCE
	for(int i = 0; i<dataValueString.length(); i++)
	{
		writeFileObject->put(dataValueString[i]);
	}
	writeFileObject->put(CHAR_NEWLINE);

	return true;
}

bool write2DReferencesLayerToFileObjectRayTraceFormat(ofstream * writeFileObject, Reference * firstReferenceInLayer)
{
	Reference * currentReference = firstReferenceInLayer;
	while(currentReference->next != NULL)
	{
		if((currentReference->isSubModelReference)
		&& !(((currentReference->type == REFERENCE_TYPE_SUBMODEL) && (currentReference->name == "4-4CUBE.DAT"))
		|| ((currentReference->type == REFERENCE_TYPE_SUBMODEL) && (currentReference->name == "4-4SPHE.DAT"))
		|| ((currentReference->type == REFERENCE_TYPE_SUBMODEL) && (currentReference->name == "CIRCLE.DAT"))))
		{
			write2DReferencesLayerToFileObjectRayTraceFormat(writeFileObject, currentReference->firstReferenceWithinSubModel);
		}
		else
		{
			if((currentReference->type == REFERENCE_TYPE_TRI)
			|| (currentReference->type == REFERENCE_TYPE_QUAD)
			|| (currentReference->type == REFERENCE_TYPE_LINE)
			|| ((currentReference->type == REFERENCE_TYPE_SUBMODEL) && (currentReference->name == "4-4CUBE.DAT"))
			|| ((currentReference->type == REFERENCE_TYPE_SUBMODEL) && (currentReference->name == "4-4SPHE.DAT"))
			|| ((currentReference->type == REFERENCE_TYPE_SUBMODEL) && (currentReference->name == "CIRCLE.DAT")))
			{

				//cout << "Writing ref; currentReference->name = " << currentReference->name << endl;
				//cout << "currentReference->type = " << currentReference->type << endl;
				//cout << "currentReference->colour = " << currentReference->colour << endl;
				//cout << "currentReference->name = " << currentReference->name << endl;
				//cout << "currentReference->absoluteDeformationMatrix.c.z = " << currentReference->absoluteDeformationMatrix.c.z << endl;
				//cout << "currentReference->deformationMatrix.c.z = " << currentReference->deformationMatrix.c.z << endl;
				//cout << "currentReference->relativePosition.z = " << currentReference->relativePosition.z << endl;

				Reference collapsedReference;
				copyReferences(&collapsedReference, currentReference, currentReference->type);

				if(currentReference->type == REFERENCE_TYPE_SUBMODEL)
				{
					copyVectors(&(collapsedReference.relativePosition), &(currentReference->absolutePosition)); 	//collapse 2D reference list to top level 1D reference list
					copyMatricies(&(collapsedReference.deformationMatrix), &(currentReference->absoluteDeformationMatrix));	//collapse 2D reference list to top level 1D reference list
				}

				copyVectors(&(collapsedReference.vertex1relativePosition), &(currentReference->vertex1absolutePosition));
				copyVectors(&(collapsedReference.vertex2relativePosition), &(currentReference->vertex2absolutePosition));
				copyVectors(&(collapsedReference.vertex3relativePosition), &(currentReference->vertex3absolutePosition));
				copyVectors(&(collapsedReference.vertex4relativePosition), &(currentReference->vertex4absolutePosition));

				collapsedReference.colour = currentReference->absoluteColour;

				if(currentReference->referenceEnabledMethod2DOD)
				{
					addReferenceToFileObjectRayTraceFormat(writeFileObject, &collapsedReference);
				}
			}
		}

		currentReference = currentReference->next;

	}
	return true;
}

//preconditions; submodelReferenceString must be long enough to store all reference information that is to be written to it
bool addReferenceToFileObjectRayTraceFormat(ofstream * writeFileObject, Reference * currentReference)
{

	bool result = true;

	char dataEndString[DAT_FILE_DATA_VALUE_MAX_LENGTH];
	char dataValueString[DAT_FILE_DATA_VALUE_MAX_LENGTH];
	char positionCoordinatesString[DAT_FILE_REF_POS_COORD_MAX_LENGTH];
	char rotationVectorString[DAT_FILE_REF_MATRIX_MAX_LENGTH];
	char lengthWidthHeightString[100];



	//write reference type
	if(currentReference->type == REFERENCE_TYPE_TRI)
	{
		strcpy(dataValueString, TAL_FILE_TYPE_PRIM_TRI);
	}
	else if(currentReference->type == REFERENCE_TYPE_QUAD)
	{
		strcpy(dataValueString, TAL_FILE_TYPE_PRIM_QUAD);
	}
	else if(currentReference->type == REFERENCE_TYPE_LINE)
	{
		strcpy(dataValueString, TAL_FILE_TYPE_PRIM_LINE);
	}
	else if((currentReference->type == REFERENCE_TYPE_SUBMODEL) && (currentReference->name == "4-4CUBE.DAT"))
	{
		strcpy(dataValueString, TAL_FILE_TYPE_RECT_PRISM);
	}
	else if((currentReference->type == REFERENCE_TYPE_SUBMODEL) && (currentReference->name == "4-4SPHE.DAT"))
	{
		strcpy(dataValueString, TAL_FILE_TYPE_SPHERE);
	}
	else if((currentReference->type == REFERENCE_TYPE_SUBMODEL) && (currentReference->name == "CIRCLE.DAT"))
	{
		strcpy(dataValueString, TAL_FILE_TYPE_CIRCLE);
	}
	else
	{
		cout << "error; cannot produce raytrace reference of type, " << currentReference->type << endl;
		exit(0);
	}

	for(int i = 0; i<strlen(dataValueString); i++)
	{
		writeFileObject->put(dataValueString[i]);
	}
	writeFileObject->put(CHAR_SPACE);



	//write reference colour
	if(currentReference->colour == DAT_FILE_COLOUR_BLACK)
	{
		strcpy(dataValueString, TAL_FILE_COLOUR_BLACK);
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_BLUE)
	{
		strcpy(dataValueString, TAL_FILE_COLOUR_BLUE);
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_GREEN)
	{
		strcpy(dataValueString, TAL_FILE_COLOUR_GREEN);
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_CYAN)
	{
		strcpy(dataValueString, TAL_FILE_COLOUR_CYAN);
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_RED)
	{
		strcpy(dataValueString, TAL_FILE_COLOUR_RED);
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_MAGENTA)
	{
		strcpy(dataValueString, TAL_FILE_COLOUR_MAGENTA);
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_BROWN)
	{
		strcpy(dataValueString, TAL_FILE_COLOUR_BROWN);
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_LIGHTGREY)
	{
		strcpy(dataValueString, TAL_FILE_COLOUR_LIGHTGREY);
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_DARKGREY)
	{
		strcpy(dataValueString, TAL_FILE_COLOUR_DARKGREY);
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_YELLOW)
	{
		strcpy(dataValueString, TAL_FILE_COLOUR_YELLOW);
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_WHITE)
	{
		strcpy(dataValueString, TAL_FILE_COLOUR_WHITE);
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_ORANGE)
	{
		strcpy(dataValueString, TAL_FILE_COLOUR_ORANGE);
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_PURPLE)
	{
		strcpy(dataValueString, TAL_FILE_COLOUR_PURPLE);
	}
	else if(currentReference->colour == DAT_FILE_DEFAULT_COLOUR)
	{
		strcpy(dataValueString, TAL_FILE_COLOUR_RED);
	}
	else if(currentReference->colour == DAT_FILE_DEFAULT_COLOUR_EDGELINE)
	{
		strcpy(dataValueString, TAL_FILE_COLOUR_RED);
	}
	else if(currentReference->colour >= DAT_FILE_FIRST_RGB_COLOUR)
	{
		strcpy(dataValueString, TAL_FILE_COLOUR_RGB_PADDER);
		unsigned int colourExtracted = currentReference->colour;
		colourExtracted = colourExtracted - (DAT_FILE_FIRST_RGB_COLOUR << 24);
		char colourValueString[100];
		sprintf(colourValueString, "%06x", colourExtracted);

		strcat(dataValueString, colourValueString);
	}
	else
	{
		cout << "error; cannot produce raytrace reference of colour, " << currentReference->colour << endl;
		exit(0);
	}
	for(int i = 0; i<strlen(dataValueString); i++)
	{
		writeFileObject->put(dataValueString[i]);
	}
	writeFileObject->put(CHAR_SPACE);




	if((currentReference->type == REFERENCE_TYPE_TRI) || (currentReference->type == REFERENCE_TYPE_QUAD) || (currentReference->type == REFERENCE_TYPE_LINE))
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

		if((currentReference->type == REFERENCE_TYPE_TRI) || (currentReference->type == REFERENCE_TYPE_QUAD))
		{
			convertPositionCoordinatesToString(&(currentReference->vertex3relativePosition), positionCoordinatesString);
			for(int i = 0; i<strlen(positionCoordinatesString); i++)
			{
				writeFileObject->put(positionCoordinatesString[i]);
			}

			if(currentReference->type == REFERENCE_TYPE_QUAD)
			{
				convertPositionCoordinatesToString(&(currentReference->vertex4relativePosition), positionCoordinatesString);
				for(int i = 0; i<strlen(positionCoordinatesString); i++)
				{
					writeFileObject->put(positionCoordinatesString[i]);
				}
			}
		}
	}
	else if(currentReference->type == REFERENCE_TYPE_SUBMODEL)
	{
		//write position coords
		convertPositionCoordinatesToString(&(currentReference->relativePosition), positionCoordinatesString);
		for(int i = 0; i<strlen(positionCoordinatesString); i++)
		{
			writeFileObject->put(positionCoordinatesString[i]);
		}

	#ifdef RT_CONVERT_LDR_OBJECT_ROTATION_PROPERLY
		//write rotation vector values
		vec submodelRotationVector;
		vec submodelRotationVectorDegrees;
		calculateRotationVectorFromDeformationMatrix(&(currentReference->deformationMatrix), &submodelRotationVector);
		submodelRotationVectorDegrees.x = submodelRotationVector.x / PI * 180.0;
		submodelRotationVectorDegrees.y = submodelRotationVector.y / PI * 180.0;
		submodelRotationVectorDegrees.z = submodelRotationVector.z / PI * 180.0;
		convertPositionCoordinatesToString(&submodelRotationVectorDegrees, rotationVectorString);
	#else
		//write rotation vector values
		vec submodelRotationVector;
		submodelRotationVector.x = 0;
		submodelRotationVector.y = 0;
		submodelRotationVector.z = 0;
		convertPositionCoordinatesToString(&submodelRotationVector, rotationVectorString);
	#endif
		for(int i = 0; i<strlen(rotationVectorString); i++)
		{
			writeFileObject->put(rotationVectorString[i]);
		}

		//write width length height values

	#ifdef RT_CONVERT_LDR_OBJECT_SCALES_PROPERLY
		double width;
		double length;
		double height;

		if(!compareDoubles(submodelRotationVector.x, 0.0) || !compareDoubles(submodelRotationVector.y, 0.0) || !compareDoubles(submodelRotationVector.z, 0.0))
		{
			advanced_mat inverseRotationxMatrix, inverseRotationyMatrix, inverseRotationzMatrix;
			advanced_mat tmpAdvancedMatrix1b, tmpAdvancedMatrix2b, tmpAdvancedMatrix3b;

			advanced_mat deformationMatrixAdvanced;
			makeAdvancedMatrix(&deformationMatrixAdvanced, &(currentReference->deformationMatrix), 1);

			createInverseRotationxMatrix(submodelRotationVector.x, &inverseRotationxMatrix);
			createInverseRotationyMatrix(submodelRotationVector.y, &inverseRotationyMatrix);
			createInverseRotationzMatrix(submodelRotationVector.z, &inverseRotationzMatrix);

			multAdvancedMatrix(&inverseRotationyMatrix, &inverseRotationzMatrix, &tmpAdvancedMatrix1b);
			multAdvancedMatrix(&inverseRotationxMatrix, &tmpAdvancedMatrix1b, &tmpAdvancedMatrix2b);
			multAdvancedMatrix(&tmpAdvancedMatrix2b, &deformationMatrixAdvanced, &tmpAdvancedMatrix3b);

			width = (tmpAdvancedMatrix3b.a.x) * 2.0;
			length = (tmpAdvancedMatrix3b.b.y) * 2.0;
			height = (tmpAdvancedMatrix3b.c.z) * 2.0;
		}
		else
		{
			width = (currentReference->deformationMatrix.a.x) * 2.0;
			length = (currentReference->deformationMatrix.b.y) * 2.0;
			height = (currentReference->deformationMatrix.c.z) * 2.0;
		}

		char widthdataValueString[100];
		sprintf(widthdataValueString, FILE_FLOAT_PRECISION, width);
		char lengthdataValueString[100];
		sprintf(lengthdataValueString, FILE_FLOAT_PRECISION, length);
		char heightdataValueString[100];
		sprintf(heightdataValueString, FILE_FLOAT_PRECISION, height);

		string tempString = "";
		tempString = tempString + TAL_FILE_REF_WIDTH + widthdataValueString + TAL_FILE_REF_LENGTH + lengthdataValueString + TAL_FILE_REF_HEIGHT + heightdataValueString + " ";

	#else
		double widthLengthHeight = (currentReference->deformationMatrix.a.x) * 2.0;

		char dataValueString[100];
		sprintf(dataValueString, FILE_FLOAT_PRECISION, widthLengthHeight);

		string tempString = "";
		tempString = tempString + TAL_FILE_REF_WIDTH + dataValueString + TAL_FILE_REF_LENGTH + dataValueString + TAL_FILE_REF_HEIGHT + dataValueString + " ";
	#endif

		for(int i = 0; i<tempString.length(); i++)
		{
			writeFileObject->put(tempString[i]);
		}
		//width 2 length 2 height 2"

	}
	else
	{
		cout << "This reference type cannot be converted to string: name=" << currentReference->name << ", type=" << currentReference->type << endl;
		exit(0);
	}

	//write ref end
	strcpy(dataEndString, TAL_FILE_REF_END);
	for(int i = 0; i<strlen(dataEndString); i++)
	{
		writeFileObject->put(dataEndString[i]);
	}


	//write new line
	writeFileObject->put(CHAR_NEWLINE);

	return result;
}



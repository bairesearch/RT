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
 * File Name: RTreferenceManipulation.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2021 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3p3a 19-March-2021
 * /
 *******************************************************************************/


#include "RTreferenceManipulation.hpp"


bool RTreferenceManipulationClass::write2DReferenceListCollapsedTo1DToFileRayTraceFormat(string fileName, LDreference* firstReference, const bool useCustomViewInfo, const RTviewInfo* vi, const bool useCustomLightSource, const vec* lightSourcePosition, const string lightSourceColour)
{
	ofstream writeFileObject;
	writeFileObject.open(fileName.c_str());
	if(writeFileObject.is_open())
	{
		writeRayTraceFormatHeaderInfo(&writeFileObject, useCustomViewInfo, vi, useCustomLightSource, lightSourcePosition, lightSourceColour);

		write2DReferencesLayerToFileObjectRayTraceFormat(&writeFileObject, firstReference);

		writeFileObject.close();
	}
	else
	{
		cerr << "Error: cannot create new file, " << fileName << endl;
		exit(EXIT_ERROR);
	}
}



bool RTreferenceManipulationClass::writeRayTraceFormatHeaderInfo(ofstream* writeFileObject, const bool useCustomViewInfo, const RTviewInfo* vi, const bool useCustomLightSource, const vec* lightSourcePosition, const string lightSourceColour)
{
	/*
	#ifdef COMPILE_TH_RT
		cerr << "1" << endl;
		exit(EXIT_ERROR);
	#elif defined COMPILE_TH_ANN_WITH_LRRC
		cerr << "2" << endl;
		cerr << "width= " << (int)TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_WIDTH << endl;
		exit(EXIT_ERROR);
	#else
		cerr << "3" << endl;
		exit(EXIT_ERROR);
	#endif
	*/

	string dataValueString;


	int imageWidth;
	int imageHeight;
	if(useCustomViewInfo)
	{
		imageWidth = vi->imageWidth;
		imageHeight = vi->imageHeight;
	}
	else
	{
		imageWidth = TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_WIDTH;
		imageHeight = TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_HEIGHT;
	}
	string imgwidthString = SHAREDvars.convertIntToString(imageWidth);
	string imgheightString = SHAREDvars.convertIntToString(imageHeight);
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
	string eyexString = SHAREDvars.convertDoubleToString(eyex, "%0.4f");
	string eyeyString = SHAREDvars.convertDoubleToString(eyey, "%0.4f");
	string eyezString = SHAREDvars.convertDoubleToString(eyez, "%0.4f");
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
		viewatx = vi->viewAt.x;
		viewaty = vi->viewAt.y;
		viewatz = vi->viewAt.z;
	}
	else
	{
		viewatx = TAL_FILE_HEADER_DEFAULT_VIEWAT_X;
		viewaty = TAL_FILE_HEADER_DEFAULT_VIEWAT_Y;
		viewatz = TAL_FILE_HEADER_DEFAULT_VIEWAT_Z;
	}
	string viewatxString = SHAREDvars.convertDoubleToString(viewatx, "%0.4f");
	string viewatyString = SHAREDvars.convertDoubleToString(viewaty, "%0.4f");
	string viewatzString = SHAREDvars.convertDoubleToString(viewatz, "%0.4f");
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
		viewupx = vi->viewUp.x;
		viewupy = vi->viewUp.y;
		viewupz = vi->viewUp.z;
	}
	else
	{
		viewupx = TAL_FILE_HEADER_DEFAULT_VIEWUP_X;
		viewupy = TAL_FILE_HEADER_DEFAULT_VIEWUP_Y;
		viewupz = TAL_FILE_HEADER_DEFAULT_VIEWUP_Z;
	}
	string viewupxString = SHAREDvars.convertDoubleToString(viewupx, "%0.4f");
	string viewupyString = SHAREDvars.convertDoubleToString(viewupy, "%0.4f");
	string viewupzString = SHAREDvars.convertDoubleToString(viewupz, "%0.4f");
	dataValueString = "";
	dataValueString = dataValueString + TAL_FILE_HEADER_VIEWUP + " " + viewupxString + " " + viewupyString + " " + viewupzString;
	for(int i = 0; i<dataValueString.length(); i++)
	{
		writeFileObject->put(dataValueString[i]);
	}
	writeFileObject->put(CHAR_NEWLINE);


	double focalLength;
	if(useCustomViewInfo)
	{
		focalLength = vi->focalLength;
	}
	else
	{
		focalLength = TAL_FILE_HEADER_DEFAULT_FOCAL;
	}
	string focal_lengthString = SHAREDvars.convertDoubleToString(focalLength, "%0.4f");
	dataValueString = "";
	dataValueString = dataValueString + TAL_FILE_HEADER_FOCAL + " " + focal_lengthString;
	for(int i = 0; i<dataValueString.length(); i++)
	{
		writeFileObject->put(dataValueString[i]);
	}
	writeFileObject->put(CHAR_NEWLINE);


	double viewWidth;
	double viewHeight;
	if(useCustomViewInfo)
	{
		viewWidth = vi->viewWidth;
		viewHeight = vi->viewHeight;
	}
	else
	{
		viewWidth = TAL_FILE_HEADER_DEFAULT_VIEWSIZE_WIDTH;
		viewHeight = TAL_FILE_HEADER_DEFAULT_VIEWSIZE_HEIGHT;
	}
	string viewwidthString = SHAREDvars.convertDoubleToString(viewWidth, "%0.4f");
	string viewheightString = SHAREDvars.convertDoubleToString(viewHeight, "%0.4f");
	dataValueString = "";
	dataValueString = dataValueString + TAL_FILE_HEADER_VIEWSIZE + " " + viewwidthString + " " + viewheightString;
	for(int i = 0; i<dataValueString.length(); i++)
	{
		writeFileObject->put(dataValueString[i]);
	}
	writeFileObject->put(CHAR_NEWLINE);


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
	string lightSourcePositionxstring = SHAREDvars.convertDoubleToString(lightSourcePositionx, "%0.1f");
	string lightSourcePositionystring = SHAREDvars.convertDoubleToString(lightSourcePositiony, "%0.1f");
	string lightSourcePositionzstring = SHAREDvars.convertDoubleToString(lightSourcePositionz, "%0.1f");

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

bool RTreferenceManipulationClass::write2DReferencesLayerToFileObjectRayTraceFormat(ofstream* writeFileObject, LDreference* firstReferenceInLayer)
{
	LDreference* currentReference = firstReferenceInLayer;
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
				#ifdef RT_DEBUG
				//cout << "Writing ref; currentReference->name = " << currentReference->name << endl;
				//cout << "currentReference->type = " << currentReference->type << endl;
				//cout << "currentReference->colour = " << currentReference->colour << endl;
				//cout << "currentReference->name = " << currentReference->name << endl;
				//cout << "currentReference->absoluteDeformationMatrix.c.z = " << currentReference->absoluteDeformationMatrix.c.z << endl;
				//cout << "currentReference->deformationMatrix.c.z = " << currentReference->deformationMatrix.c.z << endl;
				//cout << "currentReference->relativePosition.z = " << currentReference->relativePosition.z << endl;
				#endif

				LDreference collapsedReference;
				LDreferenceManipulation.copyReferences(&collapsedReference, currentReference, currentReference->type);

				if(currentReference->type == REFERENCE_TYPE_SUBMODEL)
				{
					SHAREDvector.copyVectors(&(collapsedReference.relativePosition), &(currentReference->absolutePosition)); 	//collapse 2D reference list to top level 1D reference list
					SHAREDvector.copyMatricies(&(collapsedReference.deformationMatrix), &(currentReference->absoluteDeformationMatrix));	//collapse 2D reference list to top level 1D reference list
				}

				SHAREDvector.copyVectors(&(collapsedReference.vertex1relativePosition), &(currentReference->vertex1absolutePosition));
				SHAREDvector.copyVectors(&(collapsedReference.vertex2relativePosition), &(currentReference->vertex2absolutePosition));
				SHAREDvector.copyVectors(&(collapsedReference.vertex3relativePosition), &(currentReference->vertex3absolutePosition));
				SHAREDvector.copyVectors(&(collapsedReference.vertex4relativePosition), &(currentReference->vertex4absolutePosition));

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

//preconditions; submodelReferenceString must be int64_t enough to store all reference information that is to be written to it
bool RTreferenceManipulationClass::addReferenceToFileObjectRayTraceFormat(ofstream* writeFileObject, LDreference* currentReference)
{

	bool result = true;



	//write reference type
	string referenceTypeString = "";
	if(currentReference->type == REFERENCE_TYPE_TRI)
	{
		referenceTypeString = TAL_FILE_TYPE_PRIM_TRI;
	}
	else if(currentReference->type == REFERENCE_TYPE_QUAD)
	{
		referenceTypeString = TAL_FILE_TYPE_PRIM_QUAD;
	}
	else if(currentReference->type == REFERENCE_TYPE_LINE)
	{
		referenceTypeString = TAL_FILE_TYPE_PRIM_LINE;
	}
	else if((currentReference->type == REFERENCE_TYPE_SUBMODEL) && (currentReference->name == "4-4CUBE.DAT"))
	{
		referenceTypeString = TAL_FILE_TYPE_RECT_PRISM;
	}
	else if((currentReference->type == REFERENCE_TYPE_SUBMODEL) && (currentReference->name == "4-4SPHE.DAT"))
	{
		referenceTypeString = TAL_FILE_TYPE_SPHERE;
	}
	else if((currentReference->type == REFERENCE_TYPE_SUBMODEL) && (currentReference->name == "CIRCLE.DAT"))
	{
		referenceTypeString = TAL_FILE_TYPE_CIRCLE;
	}
	else
	{
		cerr << "error; cannot produce raytrace reference of type, " << currentReference->type << endl;
		exit(EXIT_ERROR);
	}

	for(int i = 0; i<referenceTypeString.length(); i++)
	{
		writeFileObject->put(referenceTypeString[i]);
	}
	writeFileObject->put(CHAR_SPACE);




	//write reference colour
	string referenceColourString = "";
	if(currentReference->colour == DAT_FILE_COLOUR_BLACK)
	{
		referenceColourString = TAL_FILE_COLOUR_BLACK;
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_BLUE)
	{
		referenceColourString = TAL_FILE_COLOUR_BLUE;
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_GREEN)
	{
		referenceColourString = TAL_FILE_COLOUR_GREEN;
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_CYAN)
	{
		referenceColourString = TAL_FILE_COLOUR_CYAN;
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_RED)
	{
		referenceColourString = TAL_FILE_COLOUR_RED;
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_MAGENTA)
	{
		referenceColourString = TAL_FILE_COLOUR_MAGENTA;
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_BROWN)
	{
		referenceColourString = TAL_FILE_COLOUR_BROWN;
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_LIGHTGREY)
	{
		referenceColourString = TAL_FILE_COLOUR_LIGHTGREY;
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_DARKGREY)
	{
		referenceColourString = TAL_FILE_COLOUR_DARKGREY;
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_YELLOW)
	{
		referenceColourString = TAL_FILE_COLOUR_YELLOW;
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_WHITE)
	{
		referenceColourString = TAL_FILE_COLOUR_WHITE;
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_ORANGE)
	{
		referenceColourString = TAL_FILE_COLOUR_ORANGE;
	}
	else if(currentReference->colour == DAT_FILE_COLOUR_PURPLE)
	{
		referenceColourString = TAL_FILE_COLOUR_PURPLE;
	}
	else if(currentReference->colour == DAT_FILE_DEFAULT_COLOUR)
	{
		referenceColourString = TAL_FILE_COLOUR_RED;
	}
	else if(currentReference->colour == DAT_FILE_DEFAULT_COLOUR_EDGELINE)
	{
		referenceColourString = TAL_FILE_COLOUR_RED;
	}
	else if(currentReference->colour >= DAT_FILE_FIRST_RGB_COLOUR)
	{
		uint32_t colourExtracted = currentReference->colour;
		colourExtracted = colourExtracted - (DAT_FILE_FIRST_RGB_COLOUR << 24);
		char colourValueString[100];
		sprintf(colourValueString, "%06x", colourExtracted);

		referenceColourString = string(TAL_FILE_COLOUR_RGB_PADDER) + colourValueString;
	}
	else
	{
		cerr << "error; cannot produce raytrace reference of colour, " << currentReference->colour << endl;
		exit(EXIT_ERROR);
	}
	for(int i = 0; i<referenceColourString.length(); i++)
	{
		writeFileObject->put(referenceColourString[i]);
	}
	writeFileObject->put(CHAR_SPACE);




	if((currentReference->type == REFERENCE_TYPE_TRI) || (currentReference->type == REFERENCE_TYPE_QUAD) || (currentReference->type == REFERENCE_TYPE_LINE))
	{
		//write primitive vertex coords

		string positionCoordinatesString = LDreferenceManipulation.convertPositionCoordinatesToString(&(currentReference->vertex1relativePosition));
		for(int i = 0; i<positionCoordinatesString.length(); i++)
		{
			writeFileObject->put(positionCoordinatesString[i]);
		}

		positionCoordinatesString = LDreferenceManipulation.convertPositionCoordinatesToString(&(currentReference->vertex2relativePosition));
		for(int i = 0; i<positionCoordinatesString.length(); i++)
		{
			writeFileObject->put(positionCoordinatesString[i]);
		}

		if((currentReference->type == REFERENCE_TYPE_TRI) || (currentReference->type == REFERENCE_TYPE_QUAD))
		{
			positionCoordinatesString = LDreferenceManipulation.convertPositionCoordinatesToString(&(currentReference->vertex3relativePosition));
			for(int i = 0; i<positionCoordinatesString.length(); i++)
			{
				writeFileObject->put(positionCoordinatesString[i]);
			}

			if(currentReference->type == REFERENCE_TYPE_QUAD)
			{
				positionCoordinatesString = LDreferenceManipulation.convertPositionCoordinatesToString(&(currentReference->vertex4relativePosition));
				for(int i = 0; i<positionCoordinatesString.length(); i++)
				{
					writeFileObject->put(positionCoordinatesString[i]);
				}
			}
		}
	}
	else if(currentReference->type == REFERENCE_TYPE_SUBMODEL)
	{
		//write position coords
		string positionCoordinatesString = LDreferenceManipulation.convertPositionCoordinatesToString(&(currentReference->relativePosition));
		for(int i = 0; i<positionCoordinatesString.length(); i++)
		{
			writeFileObject->put(positionCoordinatesString[i]);
		}

	#ifdef RT_CONVERT_LDR_OBJECT_ROTATION_PROPERLY
		//write rotation vector values
		vec submodelRotationVector;
		vec submodelRotationVectorDegrees;
		SHAREDvector.calculateRotationVectorFromDeformationMatrix(&(currentReference->deformationMatrix), &submodelRotationVector);
		submodelRotationVectorDegrees.x = submodelRotationVector.x / PI* 180.0;
		submodelRotationVectorDegrees.y = submodelRotationVector.y / PI* 180.0;
		submodelRotationVectorDegrees.z = submodelRotationVector.z / PI* 180.0;
		string rotationVectorString = LDreferenceManipulation.convertPositionCoordinatesToString(&submodelRotationVectorDegrees);
	#else
		//write rotation vector values
		vec submodelRotationVector;
		submodelRotationVector.x = 0;
		submodelRotationVector.y = 0;
		submodelRotationVector.z = 0;
		string rotationVectorString = LDreferenceManipulation.convertPositionCoordinatesToString(&submodelRotationVector);
	#endif
		for(int i = 0; i<rotationVectorString.length(); i++)
		{
			writeFileObject->put(rotationVectorString[i]);
		}

		//write width length height values

	#ifdef RT_CONVERT_LDR_OBJECT_SCALES_PROPERLY
		double width;
		double length;
		double height;

		if(!SHAREDvars.compareDoubles(submodelRotationVector.x, 0.0) || !SHAREDvars.compareDoubles(submodelRotationVector.y, 0.0) || !SHAREDvars.compareDoubles(submodelRotationVector.z, 0.0))
		{
			advancedMat inverseRotationxMatrix, inverseRotationyMatrix, inverseRotationzMatrix;
			advancedMat tmpAdvancedMatrix1b, tmpAdvancedMatrix2b, tmpAdvancedMatrix3b;

			advancedMat deformationMatrixAdvanced;
			RToperations.makeAdvancedMatrix(&deformationMatrixAdvanced, &(currentReference->deformationMatrix), 1);

			RToperations.createInverseRotationxMatrix(submodelRotationVector.x, &inverseRotationxMatrix);
			RToperations.createInverseRotationyMatrix(submodelRotationVector.y, &inverseRotationyMatrix);
			RToperations.createInverseRotationzMatrix(submodelRotationVector.z, &inverseRotationzMatrix);

			RToperations.multAdvancedMatrix(&inverseRotationyMatrix, &inverseRotationzMatrix, &tmpAdvancedMatrix1b);
			RToperations.multAdvancedMatrix(&inverseRotationxMatrix, &tmpAdvancedMatrix1b, &tmpAdvancedMatrix2b);
			RToperations.multAdvancedMatrix(&tmpAdvancedMatrix2b, &deformationMatrixAdvanced, &tmpAdvancedMatrix3b);

			width = (tmpAdvancedMatrix3b.a.x)* 2.0;
			length = (tmpAdvancedMatrix3b.b.y)* 2.0;
			height = (tmpAdvancedMatrix3b.c.z)* 2.0;
		}
		else
		{
			width = (currentReference->deformationMatrix.a.x)* 2.0;
			length = (currentReference->deformationMatrix.b.y)* 2.0;
			height = (currentReference->deformationMatrix.c.z)* 2.0;
		}

		char widthdataValueString[100];
		sprintf(widthdataValueString, FILE_FLOAT_PRECISION, width);
		char lengthdataValueString[100];
		sprintf(lengthdataValueString, FILE_FLOAT_PRECISION, length);
		char heightdataValueString[100];
		sprintf(heightdataValueString, FILE_FLOAT_PRECISION, height);

		string scaleString = "";
		scaleString = scaleString + TAL_FILE_REF_WIDTH + widthdataValueString + TAL_FILE_REF_LENGTH + lengthdataValueString + TAL_FILE_REF_HEIGHT + heightdataValueString + " ";

	#else
		double widthLengthHeight = (currentReference->deformationMatrix.a.x)* 2.0;

		char dataValueString[100];
		sprintf(dataValueString, FILE_FLOAT_PRECISION, widthLengthHeight);

		string scaleString = "";
		scaleString = scaleString + TAL_FILE_REF_WIDTH + dataValueString + TAL_FILE_REF_LENGTH + dataValueString + TAL_FILE_REF_HEIGHT + dataValueString + " ";
	#endif

		for(int i = 0; i<scaleString.length(); i++)
		{
			writeFileObject->put(scaleString[i]);
		}
		//width 2 length 2 height 2"

	}
	else
	{
		cerr << "This reference type cannot be converted to string: name=" << currentReference->name << ", type=" << currentReference->type << endl;
		exit(EXIT_ERROR);
	}

	//write ref end
	string dataEndString = TAL_FILE_REF_END;
	for(int i = 0; i<dataEndString.length(); i++)
	{
		writeFileObject->put(dataEndString[i]);
	}


	//write new line
	writeFileObject->put(CHAR_NEWLINE);

	return result;
}



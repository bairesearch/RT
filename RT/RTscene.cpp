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
 * File Name: RTscene.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2020 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3n9a 11-September-2020
 * /
 *******************************************************************************/


#include "RTscene.hpp"

#ifndef LINUX
	#include <windows.h>
#endif


static int lightingMode = DEFAULT_LIGHTING_MODE;
static float lightingAmbientRed = AMBIENT_RED;
static float lightingAmbientGreen = AMBIENT_GREEN;
static float lightingAmbientBlue = AMBIENT_BLUE;
static float lightingSpecularPower = SPECULAR_POWER;
static float lightingSpecular = SPECULAR;
static float lightingDiffuse = DIFFUSE;


RTlightingInfo::RTlightingInfo(void)
{
	nextLight = NULL;
}

RTlightingInfo::~RTlightingInfo(void)
{
	delete nextLight;
}

void RTsceneClass::setLightingMode(const int newLightingMode)
{
	lightingMode = newLightingMode;
}

void RTsceneClass::setSceneLightingConditions(const float lightingAmbientRedNew, const float lightingAmbientGreenNew, const float lightingAmbientBlueNew, const float lightingSpecularNew, const float lightingDiffuseNew)
{
	lightingAmbientRed = lightingAmbientRedNew;
	lightingAmbientGreen = lightingAmbientGreenNew;
	lightingAmbientBlue = lightingAmbientBlueNew;
	lightingSpecular = lightingSpecularNew;
	lightingDiffuse = lightingDiffuseNew;
}

	/*used to store the original scene in the list*/

int RTsceneClass::rayTraceScene(const string talFileName, string imageFileName, const int outputImageFiles, const int setRGBAndDepthAndNormalAndPointMaps, unsigned char* rgbMap, double* depthMap, double* normalMap, double* pointMap)
{
	#ifndef USE_ATOR
	RTpixelMaps.fillInRTRulesExternVariables();
	#endif

	//printf("Raytrace Started\n");

	int result = TRUE;

	RTviewInfo* vi = NULL;
	RTsceneInfo* si = NULL;
	RTlightingInfo* li = NULL;

	parseTalFileInitialiseParser(talFileName);
	vi = parseTalFileGetViewInfo(vi);
	li = parseTalFileGetLightInfo(li);
	si = parseTalFileGetSceneInfo(si);

	RTparser.exitParser();

	SHAREDvars.setCurrentDirectory(outputFolder);


	if(!rayTraceSceneWithoutParse(vi, si, li, imageFileName, outputImageFiles, setRGBAndDepthAndNormalAndPointMaps, rgbMap, depthMap, normalMap, pointMap))
	{
		result = FALSE;
	}

	/*
	delete vi;
	delete si;
	delete li;
	*/
	delete si;
	delete li;

	//printf("Raytrace Finished\n");

	return result;

}

int RTsceneClass::rayTraceSceneWithoutParse(RTviewInfo* vi, RTsceneInfo* si, const RTlightingInfo* li, string imageFileName, const int outputImageFiles, const int setRGBAndDepthAndNormalAndPointMaps, unsigned char* rgbMap, double* depthMap, double* normalMap, double* pointMap)
{
	int result = TRUE;

	if(!setRGBAndDepthAndNormalAndPointMaps)
	{
		rgbMap = new unsigned char[(vi->imageWidth)*(vi->imageHeight)*(RGB_NUM)];
	#ifdef TEST_DEPTH_NORMAL_MAP_CREATION
		depthMap = new double[vi->imageWidth*vi->imageHeight];
		normalMap = new double[vi->imageWidth*vi->imageHeight*VEC_MAP_VEC_NUM_DIMENSIONS];
	#endif
	}


	#ifdef TEST_DEPTH_NORMAL_MAP_CREATION
	createImage(true, rgbMap, depthMap, normalMap, pointMap, vi, si, li);
	#else
	createImage(setRGBAndDepthAndNormalAndPointMaps, rgbMap, depthMap, normalMap, pointMap, vi, si, li);
	#endif



	if(outputImageFiles)
	{
		int x,y;
		pixmap* pm;
		pixmap* dm;
		pixmap* nm;

		pm = RTppm.newPixmap(vi->imageWidth, vi->imageHeight);

	#ifdef TEST_DEPTH_NORMAL_MAP_CREATION
		dm = RTppm.newPixmap(vi->imageWidth, vi->imageHeight);
		nm = RTppm.newPixmap(vi->imageWidth, vi->imageHeight);
	#endif

  		for(x = 0; x < vi->imageWidth; x++)
		{
			for(y = 0; y < vi->imageHeight; y++)
			{
				colour col;
				RTpixelMaps.getRGBMapValues(x, y, vi->imageWidth,rgbMap,&col);
				RTppm.placepointPPM(pm, x, y, col.r, col.g, col.b);

			#ifdef TEST_DEPTH_NORMAL_MAP_CREATION

				vec norm;
				RTpixelMaps.getNormalMapValue(x, y, vi->imageWidth,normalMap,&norm);
				RTppm.placepointPPM(nm, x, y, (int)(norm.x*255.0), (int)(norm.y*255.0), (int)(norm.z*255.0));
				//RTppm.placepointPPM(nm, x, y, (int)((norm.x+1.0)*128.0), (int)((norm.y+1.0)*128.0), (int)((norm.z+1.0)*128.0));

				double tAtSurface;
				tAtSurface = RTpixelMaps.getLumOrContrastOrDepthMapValue(x, y, vi->imageWidth, depthMap);

				if(tAtSurface == RT_RAYTRACE_NO_HIT_DEPTH_T)
				{
					tAtSurface = ESTIMATE_MAX_DEPTH_T_REAL;
				}
				double tValSurfaceNormalised = SHAREDvars.minInt((int)(tAtSurface/ESTIMATE_MAX_DEPTH_T_REAL*255.0), 255);
				RTppm.placepointPPM(dm, x, y, tValSurfaceNormalised, tValSurfaceNormalised, tValSurfaceNormalised);

			#endif
			}
		}


		RTpixelMaps.writeImage(imageFileName, pm);



	#ifdef TEST_DEPTH_NORMAL_MAP_CREATION

		string outputFileNameWithExtension = "";
		string outputFileNameWithoutExtension = "";

		if(imageFileName != NULL)
		{
			stripExtension(imageFileName, &outputFileNameWithoutExtension);
		}


		if(imageFileName != NULL)
		{
			//make normal output filename same as rgb output file name
			if(!addExtension(outputFileNameWithoutExtension, NORMALMAP_PPM_EXTENSION, &outputFileNameWithExtension))
			{
				cerr << "error: cannot add extension" << endl;
				exit(EXIT_ERROR);
			}

			//printf("outputFileNameWithExtension = %s", outputFileNameWithExtension);
		}
		else
		{
			cerr << "error: cannot use standard output for multiple file output" << endl;
			exit(EXIT_ERROR);
		}


		RTpixelMaps.writeImage(outputFileNameWithExtension, nm);

		if(imageFileName != NULL)
		{
			//make depth output filename same as rgb output file name
			if(!addExtension(outputFileNameWithoutExtension, DEPTHMAP_PPM_EXTENSION, &outputFileNameWithExtension))
			{
				cerr << "error: cannot add extension" << endl;
				exit(EXIT_ERROR);
			}

			//printf("outputFileNameWithExtension = %s", outputFileNameWithExtension);
		}
		else
		{
			cerr << "error: cannot use standard output for multiple file output" << endl;
			exit(EXIT_ERROR);
		}

		RTpixelMaps.writeImage(outputFileNameWithExtension, dm);

	#endif
	}


	if(!setRGBAndDepthAndNormalAndPointMaps)
	{
		delete rgbMap;

		#ifdef TEST_DEPTH_NORMAL_MAP_CREATION
			delete depthMap;
			delete normalMap;
		#endif
	}

	return result;
}

bool RTsceneClass::stripExtension(string filenameWithExtension, string* filenameWithoutExtension)
{
	bool result = true;
	int i = 0;

	*filenameWithoutExtension = filenameWithExtension;
	int positionOfFullStop = filenameWithExtension.find(CHAR_FULLSTOP);
	if(positionOfFullStop != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		*filenameWithoutExtension = filenameWithExtension.substr(0, positionOfFullStop);
		cout << "filenameWithoutExtension without fullstop = " <<* filenameWithoutExtension << endl;
	}
	else
	{
		result = false;
	}

	return result;

}

bool RTsceneClass::addExtension(string filenameWithoutExtension, string extension, string* filenameWithExtension)
{
	bool result = true;

	*filenameWithExtension = filenameWithoutExtension + extension;

	return result;
}




RTsceneInfo* addSceneToEnd(RTsceneInfo* si_orig, RTsceneInfo* new_node)
{
	RTsceneInfo* tmp;
	if(si_orig == NULL)
	{
		return new_node;
	}

	for(tmp = si_orig; tmp->nextScene != NULL; tmp = tmp->nextScene)
	{
		/*nothing*/
	}
	tmp->nextScene = new_node;
	return si_orig;
}

RTlightingInfo* addLightToEnd(RTlightingInfo* li_orig, RTlightingInfo* new_node)
{

	RTlightingInfo* tmp;


	if(li_orig == NULL)
	{
		return new_node;
	}

	for(tmp = li_orig; tmp->nextLight != NULL; tmp = tmp->nextLight)
	{
		/*nothing*/
	}
	tmp->nextLight = new_node;
	return li_orig;
}


void RTsceneClass::parseTalFileInitialiseParser(const string talFileName)
{

 	FILE* f;

  	if(talFileName != "")
	{
   		 f = fopen(talFileName.c_str(), "r");
 	}
	else
	{
   		 f = stdin;
	}

  	if(!f)
	{
		cerr << "error; no file name specified in code execution, and no standard input given to RT.exe executable" << endl;
		exit(EXIT_ERROR);
	}
	else
	{

		RTparser.initParser(f);
	}
}

RTviewInfo* RTsceneClass::parseTalFileGetViewInfo(RTviewInfo* vi)
{
	if(! RTparser.readViewport())
	{
		cerr << "could not read viewport" << endl;
		exit(EXIT_ERROR);
	}

	vi = RTparser.get_view_info();

	return vi;
}


RTlightingInfo* RTsceneClass::parseTalFileGetLightInfo(RTlightingInfo* li)
{
	while(RTparser.nextLightSource())
	{
		/*the first time round, read info commands do not provide relevant pointers!*/
		RTlightingInfo* nd = new RTlightingInfo(); //(RTlightingInfo*)malloc(sizeof(RTlightingInfo));

		nd->ls = *(RTparser.get_light_info());
		nd->nextLight = NULL;

		li = addLightToEnd(li, nd);



	}
	return li;
}


RTsceneInfo* RTsceneClass::parseTalFileGetSceneInfo(RTsceneInfo* si)
{
	double height;
	double width;
	double length;
	double transx;
	double transy;
	double transz;

	/*defining advanced variables - for rotation, translation, scaling*/
	advancedVec tmpAvancedVector;
	advancedMat tmpAdvancedMatrix;	/*used for matrix manipulation*/
	advancedMat tmpAdvancedMatrix2;/*used for matrix manipulation*/
	advancedMat tmpAdvancedMatrix3;/*used for matrix manipulation*/
	advancedMat rotationxMatrix;
	advancedMat rotationyMatrix;
	advancedMat rotationzMatrix;
	advancedMat inverseRotationxMatrix;
	advancedMat inverseRotationyMatrix;
	advancedMat inverseRotationzMatrix;
	advancedMat inverseTranslationMatrix;
	advancedMat inverseScaleMatrix;
	advancedMat translationMatrix;
	advancedMat scaleMatrix;
	advancedMat reverseMatrix;
	advancedMat standardMatrix;

  	while (RTparser.nextSceneCommand())
	{
		/*the first time round, read info commands do not provide relevant pointers!*/
		RTsceneInfo* nd = new RTsceneInfo(); //(RTsceneInfo*)malloc(sizeof(RTsceneInfo));
		nd->pi = *(RTparser.getPieceInfo());
		nd->di = *(RTparser.getDimensionsInfo());
		nd-> tIn = 0.0;
		nd-> tOut = 0.0;
		nd->nextScene = NULL;


		/*reverse matrix = A^-1 = reverseMatrix. n = N = normal, n' = N' = normal to basic cube*/

		/*NEW, nb sides are not scaled, since they will already have been scaled
		inside raytracer.c*/
		height = ONE;
		width = ONE;
		length = ONE;
		#ifdef RT_CONVERT_LDR_OBJECT_TRANSLATION_PROPERLY_VERSIONB
		transx = nd->pi.pos.x - (nd->di.width/2);
		transy = nd->pi.pos.y - (nd->di.length/2);
		transz = nd->pi.pos.z - (nd->di.height/2);
		#else
		transx = nd->pi.pos.x;
		transy = nd->pi.pos.y;
		transz = nd->pi.pos.z;
		#endif

		/*for standardMatrix calculate*/

		RToperations.createRotationxMatrix(RToperations.toRadians(nd->pi.xrot), &rotationxMatrix);
		RToperations.createRotationyMatrix(RToperations.toRadians(nd->pi.yrot), &rotationyMatrix);
		RToperations.createRotationzMatrix(RToperations.toRadians(nd->pi.zrot), &rotationzMatrix);
		RToperations.createTranslationMatrix(transx, transy, transz, &translationMatrix);
		RToperations.createScaleMatrix(width, length, height, &scaleMatrix);

		RToperations.multAdvancedMatrix(&inverseRotationyMatrix, &inverseRotationxMatrix,&tmpAdvancedMatrix);
		RToperations.multAdvancedMatrix(&inverseRotationzMatrix, &tmpAdvancedMatrix, &tmpAdvancedMatrix2);		//This used to be (before 14 June 2012);  RToperations.multAdvancedMatrix(&inverseRotationxMatrix, &tmpAdvancedMatrix, &tmpAdvancedMatrix2);
		RToperations.multAdvancedMatrix(&tmpAdvancedMatrix2, &scaleMatrix, &tmpAdvancedMatrix3);
		RToperations.multAdvancedMatrix(&translationMatrix, &tmpAdvancedMatrix3, &standardMatrix);

		/*for reverseMatrix calculate*/
		/*now create the reverse matrix (A^-1)...*/

		RToperations.createInverseRotationxMatrix(RToperations.toRadians(nd->pi.xrot), &inverseRotationxMatrix);
		RToperations.createInverseRotationyMatrix(RToperations.toRadians(nd->pi.yrot), &inverseRotationyMatrix);
		RToperations.createInverseRotationzMatrix(RToperations.toRadians(nd->pi.zrot), &inverseRotationzMatrix);
		RToperations.createInverseTranslationMatrix(transx, transy, transz, &inverseTranslationMatrix);
		RToperations.createInverseScaleMatrix(width, length, height,&inverseScaleMatrix);

		RToperations.multAdvancedMatrix(&inverseRotationyMatrix, &inverseRotationzMatrix, &tmpAdvancedMatrix);
		RToperations.multAdvancedMatrix(&inverseRotationxMatrix, &tmpAdvancedMatrix, &tmpAdvancedMatrix2);
		RToperations.multAdvancedMatrix(&tmpAdvancedMatrix2, &inverseTranslationMatrix, &tmpAdvancedMatrix3);
		RToperations.multAdvancedMatrix(&inverseScaleMatrix, &tmpAdvancedMatrix3, &reverseMatrix);

		nd->standardMatrix = standardMatrix;
		nd->reverseMatrix = reverseMatrix;

		si = addSceneToEnd(si, nd);
	}
	return si;
}

void RTsceneClass::createImage(const int setRGBAndDepthAndNormalAndPointMaps, unsigned char* rgbMap, double* depthMap, double* normalMap, double* pointMap, RTviewInfo* vi, RTsceneInfo* si, const RTlightingInfo* li)
{


		/*for Window traversing*/
	colour col;
	double tAtSurface = 0.0;
	vec nAtSurface;
	vec pAtSurface;
	pAtSurface.x = 0.0;	//absolutely required
	pAtSurface.y = 0.0;	//absolutely required
	pAtSurface.z = 0.0;	//absolutely required
	nAtSurface.x = 0.0;
	nAtSurface.y = 0.0;
	nAtSurface.z = 0.0;
	col.r = 0;
	col.g = 0;
	col.b = 0;

	int x, y;


		/*declaration of variables for tildaMatrix calculation*/

	mat tildaMat_structure;
	mat* tildaMat = &tildaMat_structure;
	vec uvn_structure;
	vec* uvn = &uvn_structure;

	vec wTilda_structure;
	vec vTilda_structure;
	vec nTilda_structure;
	vec uTilda_structure;
	vec tmp_structure;		/*used for vector manipulation*/

	/*defining vectors*/
	vec* wTilda = &wTilda_structure;
	vec* vTilda = &vTilda_structure;
	vec* nTilda = &nTilda_structure;
	vec* uTilda = &uTilda_structure;
	vec* tmp = &tmp_structure;	/*used for vector manipulation*/

		/*defining the nTilda, uTilda, vTilda vectors*/

	/*nTilda = (eye - viewAt)*/
	SHAREDvector.negativeVector(&(vi->viewAt), tmp);
	SHAREDvector.addVectorsRT(tmp,(&(vi->eye)), nTilda);
	SHAREDvector.normaliseVector(nTilda);

	/*wTilda = (viewUp - eye)*/
	SHAREDvector.negativeVector(&(vi->eye), tmp);
	SHAREDvector.addVectorsRT(tmp,(&(vi->viewUp)), wTilda);
	SHAREDvector.normaliseVector(wTilda);

	/*uTilda = wTilda x nTilda*/
	SHAREDvector.crossProduct(wTilda, nTilda, uTilda);
	SHAREDvector.normaliseVector(uTilda);

	/*vTilda = nTilda x uTilda*/
	SHAREDvector.crossProduct(nTilda, uTilda, vTilda);
	SHAREDvector.normaliseVector(vTilda);

		/*calculation of tildaMatrix*/

	/*creating the uTilda vTilda nTilda matrix from the u, v, n vectors*/
	SHAREDvector.makeMatrix(uTilda, vTilda, nTilda, tildaMat);



		/*raytrace x/y coordinates of view port*/

  	for(x = 0; x < vi->imageWidth; x++)
	{
		#ifdef DEMONSTRATE_CPP_STRING_TO_CSTRING_CAST_CORRUPTION
		printf("\nimageFileName = %s", imageFileName);
		#endif

		for(y = 0; y < vi->imageHeight; y++)
		{
			//printf("pixel being raytraced; x= %d, y=%d", x , y);
			#ifndef RT_NO_TEXT_FEEDBACK
			if(y == 0)
			{
				printf("\nvertical line of pixels currently being raytraced; x=%d", x);
			}
			#endif



			RTsceneInfo* nd = si;

			/*calculates UVN Scalars*/
			calculateUVNScalars(vi, uvn, x, y);

			/*ray trace each piece for this point*/
			while(nd != NULL)
			{
				RTraytracer.rayTrace(vi, nd, tildaMat, uvn);
				nd = nd -> nextScene;
			}



			if(lightingMode == 0)
			{
				calculateBasicColour(vi, si, li, &col, &tAtSurface, &nAtSurface, &pAtSurface);
				//placepointPPM(pm, x, y, col.r, col.g, col.b);
			}
			else if(lightingMode == 1)
			{
				calculateTransparencyColour(vi, si, li, &col);
				//placepointPPM(pm, x, y, col.r, col.g, col.b);

			}
			else if(lightingMode == 2)
			{
				calculateAmbientDiffuseSpecular(vi, si, li, &col, &tAtSurface, &nAtSurface, &pAtSurface);
				//placepointPPM(pm, x, y, col.r, col.g, col.b);
			}

			RTpixelMaps.setRGBMapValues(x, y,vi->imageWidth, &col, rgbMap);

			if(setRGBAndDepthAndNormalAndPointMaps)
			{
				//printf("\n tAtSurface = %f", tAtSurface);
				//printf("\n nAtSurface.y = %f", nAtSurface.y);
				RTpixelMaps.setLumOrContrastOrDepthMapValue(x, y, vi->imageWidth, tAtSurface, depthMap);
				RTpixelMaps.setNormalMapValue(x, y, vi->imageWidth, &nAtSurface, normalMap);
				RTpixelMaps.setPointMapValue(x, y, vi->imageWidth, &pAtSurface, pointMap);
			}


			//printf("\npAtSurface.x = %d", pAtSurface.x);
			//printf("\npAtSurface.y = %d", pAtSurface.y);
			//printf("\npAtSurface.z = %d", pAtSurface.z);

		}
	}
}



void RTsceneClass::calculateBasicColour(const RTviewInfo* vi, const RTsceneInfo* si, const RTlightingInfo* li, colour* rgb, double* tAtSurface, vec* nAtSurface, vec* pointAtSurface)
{
	const RTsceneInfo* nd;
	double minTIn;
	int count, recordedCountForMinTIn;

	/*will be nd = si, but till error is fixed*/
	nd = si;

	/*now find the least value of si -> tIn*/
	minTIn = 0;
	count = 0;
	recordedCountForMinTIn = 0;
	while(nd != NULL)
	{

		if(minTIn == 0)
		{
			if(nd->tIn > 0)
			{
				minTIn = nd->tIn;
				recordedCountForMinTIn = count;
			}
			else
			{
				/*no new record for count*/
			}
		}
		else
		{
			if((nd->tIn > 0) && (nd->tIn < minTIn))
			{
				minTIn = nd->tIn;
				recordedCountForMinTIn = count;
			}
			else
			{
				/*no new record for count*/
			}
		}
		nd = nd->nextScene;
		count++;

	}
	/*will be nd = si, but till error is fixed*/
	nd = si;

	/*go through linkedlist to relevant to find the node which
	contains the minTIn*/
	count = 0;
		/*loops to  relevant node in linked list*/
	while(count < recordedCountForMinTIn)
	{
		nd = nd->nextScene;
		count++;
	}

	if(minTIn == RT_RAYTRACE_NO_HIT_DEPTH_T)
	{
		/*no hits, colour area black*/
		rgb->r = NO_COLOUR;
		rgb->g = NO_COLOUR;
		rgb->b = NO_COLOUR;
	}
	else
	{
		rgb->r = nd->pi.col.r;
		rgb->g = nd->pi.col.g;
		rgb->b = nd->pi.col.b;
	}

	*tAtSurface = minTIn;
	SHAREDvector.copyVectorRT(nAtSurface, &(nd->n));
	SHAREDvector.copyVectorRT(pointAtSurface, &(nd->p));
}



int compare_tin(RTsceneInfo* p, RTsceneInfo* q, void* pointer)
{
	//printf("\nhere1\n");
	if(p->tIn < q->tIn)
	{
		//printf("\nhere2\n");
		return 1; /*p is to be before q in sorted orded. nb putting bricks with greatest tIn first in the list!*/
	}
	else if(p->tIn > q->tIn)
	{
		//printf("\nhere3\n");
		return 0;
	}
	else
	{
		//printf("\nhere4\n");
		return 0;
	}

	/*could include checking that p->tOut < q->tIn. has not been implimented yet..*/
}




void RTsceneClass::calculateTransparencyColour(const RTviewInfo* vi, const RTsceneInfo* si, const RTlightingInfo* li, colour* rgb)
{
	const RTsceneInfo* nd_orig;
	const RTsceneInfo* nd;

	/*temporarily, TRANSPARENCY is a global variable coverting all bricktypes.
	This can easily be changed to individual brick/piece types but the current .tal
	parsable format does not specify a specific alpha value as a standard byte*/

	/*this method currently only works for ambient lighting that effects the surface colour concentration*/
	/*NB ambient light does not discriminate between nearer objects and farther objects*/

	/*transparency is based on colour subtraction not addition.*/

	int count = 0;
	double maximumAmountOfColourLost, maxColour, surfaceColourConcentration;
	double rOpacityTotal = 0;
	double gOpacityTotal = 0;
	double bOpacityTotal = 0;
	int hit = FALSE; /*there is initally no hit*/
	maxColour = MAX_COLOUR;
	surfaceColourConcentration = SURFACE_COLOUR_CONCENTRATION;

	nd_orig = si;
	nd = si;

	/*create an ordered list containing the tree depth of each brick and its distance to the eye, and thickness*/
	/*orders bricks*/


	/*
	nd = sort_linked_list(nd_orig, 0, compare_tin, NULL, NULL);
	*/
	/*this may not be needed*/

	/*aim now is to make closer bricks eliminate the light from previous bricks based on their transparency colour*/
	/*also will detect if there is overlap between objects.. but this may need normalisation of p0, p1 vectors..*/

	while(nd != NULL)
	{

		if(nd->tIn > 0)
		{
			hit = TRUE;
			/*these values are not currently, but should be effected by AMBIENT lighting*/
			maximumAmountOfColourLost = maxColour - (double)(nd->pi.col.r);
			rOpacityTotal = rOpacityTotal + (double)(nd->pi.col.r)*surfaceColourConcentration - (maximumAmountOfColourLost*RATIO_OF_COLOUR_LOSS_TO_DISTANCE*(nd->tOut - nd->tIn));
			maximumAmountOfColourLost = maxColour - (double)(nd->pi.col.g);
			gOpacityTotal = gOpacityTotal + (double)(nd->pi.col.g)*surfaceColourConcentration - (maximumAmountOfColourLost*RATIO_OF_COLOUR_LOSS_TO_DISTANCE*(nd->tOut - nd->tIn));
			maximumAmountOfColourLost = maxColour - (double)(nd->pi.col.b);
			bOpacityTotal = bOpacityTotal + (double)(nd->pi.col.b)*surfaceColourConcentration - (maximumAmountOfColourLost*RATIO_OF_COLOUR_LOSS_TO_DISTANCE*(nd->tOut - nd->tIn));
		}
		else
		{
			/*no change to r,b,g Totals...*/
		}

		nd = nd->nextScene;

	}
	/*check if r,g,b totals are greater than 255. NOT NEEDED NOW*/
	if(rOpacityTotal > 255)
	{
		rOpacityTotal = 255;
	}
	if(gOpacityTotal > 255)
	{
		gOpacityTotal = 255;
	}
	if(bOpacityTotal > 255)
	{
		bOpacityTotal = 255;
	}

	/*check if r,g,b totals are less than 0, or if there was no hit at all...*/
	if(rOpacityTotal < 0 || !hit)
	{
		rOpacityTotal = 0;
	}
	if(gOpacityTotal < 0 || !hit)
	{
		gOpacityTotal = 0;
	}
	if(bOpacityTotal < 0 || !hit)
	{
		bOpacityTotal = 0;
	}


	rgb->r = rOpacityTotal;
	rgb->g = gOpacityTotal;
	rgb->b = bOpacityTotal;

}


	/* calculateAmbientDiffuseSpecular is a modified version
	of shading.c's get_point_value method*/

void RTsceneClass::calculateAmbientDiffuseSpecular(RTviewInfo* vi, const RTsceneInfo* si, const RTlightingInfo* li, colour* rgb, double* tAtSurface, vec* nAtSurface, vec* pointAtSurface)
{
		/*light info declarations*/

	 /* si->p; the point we're drawing, in 3-space	*/
	/* si->n; the normal to the surface of the plane	*/

	vec l,   /* the direction of the light from each point source	*/
	    lpr, /* the reflection of the light from each point source	*/
	    v;   /* the vector from the eye to the point we're drawing	*/

	/* col; The cumulative diffuse and specular colour	*
	* for this point.*/

	double specular = lightingSpecular;
	double spec_power = SPECULAR_POWER;
	double diffuse = lightingDiffuse;
	double ambientRed = lightingAmbientRed;
	double ambientGreen = lightingAmbientGreen;
	double ambientBlue = lightingAmbientBlue;
	colourAdvanced col;
	const RTlightingInfo* nd2;
	vec tmp, tmp2, tmp3;
	double diff_amt, spec_amt;


		/*for scene info traversing declarations..*/

	const RTsceneInfo* nd;	/*stands for 'node'*/
	double minTIn;
	int count, recordedCountForMinTIn;

	/*will be nd = si, but till error is fixed*/
	nd = si;

	/*now find the least value of si -> tIn*/
	minTIn = 0;
	count = 0;
	recordedCountForMinTIn = 0;

	while(nd != NULL)
	{

		if(minTIn == 0)
		{
			if(nd->tIn > 0)
			{
				minTIn = nd->tIn;
				recordedCountForMinTIn = count;
			}
			else
			{
				/*no new record for count*/
			}
		}
		else
		{
			if((nd->tIn > 0) && (nd->tIn < minTIn))
			{
				minTIn = nd->tIn;
				recordedCountForMinTIn = count;
			}
			else
			{
				/*no new record for count*/
			}
		}
		nd = nd->nextScene;
		count++;

	}
	/*will be nd = si, but till error is fixed*/
	nd = si;

	/*go through linkedlist to relevant to find the node which
	contains the minTIn*/
	count = 0;

		/*loops to  relevant node in linked list*/
	while(count < recordedCountForMinTIn)
	{
		nd = nd->nextScene;
		count++;
	}


	if(minTIn == RT_RAYTRACE_NO_HIT_DEPTH_T)
	{
		/*no hits, colour area black*/
		rgb->r = NO_COLOUR;
		rgb->g = NO_COLOUR;
		rgb->b = NO_COLOUR;
	}
	else
	{
		if(nd->pi.type == PRIM_LINE)
		{

			rgb->r = nd->pi.col.r;
			rgb->g = nd->pi.col.g;
			rgb->b = nd->pi.col.b;
		}
		else
		{

			SHAREDvector.subtractVectorsRT(&(nd->p), &(vi->eye), &v);	/* Get the vector from eye to p	*/
			SHAREDvector.normaliseVector(&v);

			col.r = ambientRed*nd->pi.col.r/MAX_COLOUR;
			col.g = ambientGreen*nd->pi.col.g/MAX_COLOUR;
			col.b = ambientBlue*nd->pi.col.b/MAX_COLOUR;

			/* Iterate over all the light sources, adding to the diffuse
			* and specular_colours.*/

			nd2 = li;
			while(nd2 != NULL)
			{

				/* Find l for this light source; normaliseVector it.*/
				SHAREDvector.subtractVectorsRT(&(nd->p), &(nd2->ls.pos), &l);
				SHAREDvector.normaliseVector(&l);


				/* Find l' using the equation on p5 of the tute 6 notes*/

				SHAREDvector.multiplyVectorByScalarRT(&(nd->n), 2.0*SHAREDvector.dotProduct(&l,&(nd->n)), &tmp);	/* find  (2 l.n) n	*/
				SHAREDvector.subtractVectorsRT(&l, &tmp, &lpr);		/* subtractVectors it from l	*/


				/* Find the diffuse intensity for this light ...*/


				diff_amt = -SHAREDvector.dotProduct(&l, &(nd->n))* diffuse;
				if (diff_amt < 0.0) diff_amt=0;	/* see tute 6 pre-work*/

				/*diffuse lighting effects the surface dependant on the colour of the surface
				/*method 2*/
				col.r = col.r + (nd2->ls.col.r* diff_amt)*nd->pi.col.r/MAX_COLOUR;
				col.g = col.g + (nd2->ls.col.g* diff_amt)*nd->pi.col.g/MAX_COLOUR;
				col.b = col.b + (nd2->ls.col.b* diff_amt)*nd->pi.col.b/MAX_COLOUR;
				/*
				col.r = col.r* (1 + (nd2->ls.col.r* diff_amt));
				col.g = col.g* (1 + (nd2->ls.col.g* diff_amt));
				col.b = col.b* (1 + (nd2->ls.col.b* diff_amt));
				*/

				/* ... and the specular intensity.*/

				if (-(SHAREDvector.dotProduct(&lpr, &v)) < 0.0) spec_amt = 0;
				else spec_amt = pow(-SHAREDvector.dotProduct(&lpr, &v), 1.0*spec_power)* specular;
					/*'pow' is a method from math.h*/

				col.r = col.r + nd2->ls.col.r* spec_amt;
				col.g = col.g + nd2->ls.col.g* spec_amt;
				col.b = col.b + nd2->ls.col.b* spec_amt;

				/* OLD
				/*
				col.r += nd2->ls.col.r* (diff_amt + spec_amt);
				col.g += nd2->ls.col.g* (diff_amt + spec_amt);
				col.b += nd2->ls.col.b* (diff_amt + spec_amt);
				*/



				nd2 = nd2 -> nextLight;
			}


			/* colour now contains the added light intensities for each value;
			* we have to clamp it to the range (0, 1)
			*/

			if (col.r > 1.0) col.r = 1.0;
			if (col.g > 1.0) col.g = 1.0;
			if (col.b > 1.0) col.b = 1.0;

			/*
			rgb->r = (unsigned char)((col.r)*MAX_COLOUR);
			rgb->g = (unsigned char)((col.g)*MAX_COLOUR);
			rgb->b = (unsigned char)((col.b)*MAX_COLOUR);
			*/

			rgb->r = col.r*MAX_COLOUR;
			rgb->g = col.g*MAX_COLOUR;
			rgb->b = col.b*MAX_COLOUR;
		}
	}

	*tAtSurface = minTIn;
	SHAREDvector.copyVectorRT(nAtSurface, &(nd->n));
	SHAREDvector.copyVectorRT(pointAtSurface, &(nd->p));
}



void RTsceneClass::calculateUVNScalars(const RTviewInfo* vi, vec* uvn, const int x, const int y)
{
	double u, v, n;

	/*defining the u, v, n scalars*/
	u = ((double)x - (vi->imageWidth)/2)*(vi->viewWidth)/(vi->imageWidth);
	v = ((vi->imageHeight)/2 - (double)y)*(vi->viewHeight)/(vi->imageHeight);
	n = -vi->focalLength;

	/*creating the uvn vector from the u, v, n scalars*/
	uvn->x = u;
	uvn->y = v;
	uvn->z = n;

	return;
}

void RTsceneClass::calculatePointMapValue(const double xPos, const double yPos, double depthVal, vec* xyzWorld, RTviewInfo* vi)
{
	//this function requires viewAt, viewUp and eye vectors to be defined

	/*
	cout << "xPos = " << xPos << endl;
	cout << "yPos = " << yPos << endl;
	cout << "depthVal = " << depthVal << endl;
	cout << "vi->viewAt.x = " << vi->viewAt.x << endl;
	cout << "vi->viewAt.y = " << vi->viewAt.y << endl;
	cout << "vi->viewAt.z = " << vi->viewAt.z << endl;
	cout << "vi->viewUp.x = " << vi->viewUp.x << endl;
	cout << "vi->viewUp.y = " << vi->viewUp.y << endl;
	cout << "vi->viewUp.z = " << vi->viewUp.z << endl;
	cout << "vi->eye.x = " << vi->eye.x << endl;
	cout << "vi->eye.y = " << vi->eye.y << endl;
	cout << "vi->eye.z = " << vi->eye.z << endl;
	cout << "vi->focalLength = " << vi->focalLength << endl;
	*/

	vec uvn;
	calculateUVNScalars(vi, &uvn, xPos, yPos);

	vec p;
	vec p0;
	vec p1;
	RTraytracer.calculatePointUsingTInWorld(depthVal, &p0, &p1, vi, &p, &uvn);

	xyzWorld->x = p.x;
	xyzWorld->y = p.y;
	xyzWorld->z = p.z;

	/*
	cout << "p.x = " << p.x << endl;
	cout << "p.y = " << p.y << endl;
	cout << "p.z = " << p.z << endl;
	*/

}

void RTsceneClass::createPointMapUsingDepthMap(const int imageWidth, const int imageHeight, double* pointMap, const double* depthMap,  RTviewInfo* vi)
{
	for(int y = 0; y < (imageHeight); y++)
	{
		for(int x = 0; x < (imageWidth); x++)
		{
			vec xyzWorld;
			double depthVal = RTpixelMaps.getLumOrContrastOrDepthMapValue(x, y, imageWidth, depthMap);
			calculatePointMapValue(x, y, depthVal, &xyzWorld, vi);
			RTpixelMaps.setPointMapValue(x, y, imageWidth, &xyzWorld, pointMap);

		}
	}

}



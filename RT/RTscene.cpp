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
 * File Name: RTscene.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3c1a 11-October-2012
 *
 *******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;


#include "RTscene.h"
#include "RTpixelMaps.h"

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


lighting_info::lighting_info(void)
{
	nextLight = NULL;
}

lighting_info::~lighting_info(void)
{
	delete nextLight;
}

void setLightingMode(int newLightingMode)
{
	lightingMode = newLightingMode;
}

void setSceneLightingConditions(float lightingAmbientRedNew, float lightingAmbientGreenNew, float lightingAmbientBlueNew, float lightingSpecularNew, float lightingDiffuseNew)
{
	lightingAmbientRed = lightingAmbientRedNew;
	lightingAmbientGreen = lightingAmbientGreenNew;
	lightingAmbientBlue = lightingAmbientBlueNew;
	lightingSpecular = lightingSpecularNew;
	lightingDiffuse = lightingDiffuseNew;
}

	/*used to store the original scene in the list*/

int rayTraceScene(char * talFileName, char * imageFileName, int outputImageFiles, int setRGBAndDepthAndNormalAndPointMaps, unsigned char * rgbMap, double * depthMap, double * normalMap, double * pointMap)
{
	#ifndef USE_OR
	fillInRTRulesExternVariables();
	#endif

	//printf("Raytrace Started\n");

	int result = TRUE;

	view_info *vi = NULL;
	scene_info *si = NULL;
	lighting_info *li = NULL;

	parseTalFileInitialiseParser(talFileName);
	vi = parseTalFileGetViewInfo(vi);
	li = parseTalFileGetLightInfo(li);
	si = parseTalFileGetSceneInfo(si);

	exit_parser();

	#ifdef LINUX
	chdir(tempFolderCharStar);
	#else
	::SetCurrentDirectory(tempFolderCharStar);
	#endif


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

int rayTraceSceneWithoutParse(view_info *vi, scene_info *si, lighting_info *li, char * imageFileName, int outputImageFiles, int setRGBAndDepthAndNormalAndPointMaps, unsigned char * rgbMap, double * depthMap, double * normalMap, double * pointMap)
{
	int result = TRUE;

	if(!setRGBAndDepthAndNormalAndPointMaps)
	{
		rgbMap = new unsigned char[(vi->imgwidth)*(vi->imgheight)*(RGB_NUM)];
	#ifdef TEST_DEPTH_NORMAL_MAP_CREATION
		depthMap = new double[vi->imgwidth*vi->imgheight];
		normalMap = new double[vi->imgwidth*vi->imgheight*VEC_MAP_VEC_NUM_DIMENSIONS];
	#endif
	}


	#ifdef TEST_DEPTH_NORMAL_MAP_CREATION
	createImage(imageFileName, true, rgbMap, depthMap, normalMap, pointMap, vi, si, li);
	#else
	createImage(imageFileName, setRGBAndDepthAndNormalAndPointMaps, rgbMap, depthMap, normalMap, pointMap, vi, si, li);
	#endif



	if(outputImageFiles)
	{
		int x,y;
		pixmap* pm;
		pixmap* dm;
		pixmap* nm;

		pm = new_pixmap(vi->imgwidth, vi->imgheight);

	#ifdef TEST_DEPTH_NORMAL_MAP_CREATION
		dm = new_pixmap(vi->imgwidth, vi->imgheight);
		nm = new_pixmap(vi->imgwidth, vi->imgheight);
	#endif

  		for(x = 0; x < vi->imgwidth; x++)
		{
			for(y = 0; y < vi->imgheight; y++)
			{
				colour col;
				getRGBMapValues(x, y, vi->imgwidth,rgbMap,&col);
				placepoint_ppm(pm, x, y, col.r, col.g, col.b);

			#ifdef TEST_DEPTH_NORMAL_MAP_CREATION

				vec norm;
				getNormalMapValue(x, y, vi->imgwidth,normalMap,&norm);
				placepoint_ppm(nm, x, y, (int)(norm.x*255.0), (int)(norm.y*255.0), (int)(norm.z*255.0));
				//placepoint_ppm(nm, x, y, (int)((norm.x+1.0)*128.0), (int)((norm.y+1.0)*128.0), (int)((norm.z+1.0)*128.0));

				double tAtSurface;
				tAtSurface = getLumOrContrastOrDepthMapValue(x, y, vi->imgwidth, depthMap);

				if(tAtSurface == RT_RAYTRACE_NO_HIT_DEPTH_T)
				{
					tAtSurface = ESTIMATE_MAX_DEPTH_T_REAL;
				}
				double tValSurfaceNormalised = minInt((int)(tAtSurface/ESTIMATE_MAX_DEPTH_T_REAL*255.0), 255);
				placepoint_ppm(dm, x, y, tValSurfaceNormalised, tValSurfaceNormalised, tValSurfaceNormalised);

			#endif
			}
		}


		writeImage(imageFileName, pm);



	#ifdef TEST_DEPTH_NORMAL_MAP_CREATION

		char * outputFileNameWithExtension = new char[100];
		char * outputFileNameWithoutExtension = new char[100];

		/*
		char outputFileNameWithExtensionArray[100];
		char outputFileNameWithoutExtensionArray[100];
		char * outputFileNameWithExtension = outputFileNameWithExtensionArray;
		char * outputFileNameWithoutExtension = outputFileNameWithoutExtensionArray;
		*/
		if(imageFileName != NULL)
		{
			stripExtension(imageFileName, outputFileNameWithoutExtension);
		}


		if(imageFileName != NULL)
		{
			//make normal output filename same as rgb output file name
			if(!addExtension(outputFileNameWithoutExtension, NORMALMAP_PPM_EXTENSION, outputFileNameWithExtension))
			{
				printf("error: cannot add extension");
				exit(0);
			}

			//printf("outputFileNameWithExtension = %s", outputFileNameWithExtension);
		}
		else
		{
			printf("error: cannot use standard output for multiple file output");
			exit(0);
		}


		writeImage(outputFileNameWithExtension, nm);

		if(imageFileName != NULL)
		{
			//make depth output filename same as rgb output file name
			if(!addExtension(outputFileNameWithoutExtension, DEPTHMAP_PPM_EXTENSION, outputFileNameWithExtension))
			{
				printf("error: cannot add extension");
				exit(0);
			}

			//printf("outputFileNameWithExtension = %s", outputFileNameWithExtension);
		}
		else
		{
			printf("error: cannot use standard output for multiple file output");
			exit(0);
		}

		writeImage(outputFileNameWithExtension, dm);

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

int stripExtension(char * filenameWithExtension, char * filenameWithoutExtension)
{
	int result = TRUE;
	int i = 0;

	while((filenameWithExtension[i] != '.') && (filenameWithExtension[i] != '\0'))
	{
		filenameWithoutExtension[i] = filenameWithExtension[i];

		if(filenameWithExtension[i] == '\0')
		{
			result = FALSE;
		}

		i++;
	}
	filenameWithoutExtension[i] = '\0';

	return result;

}

int addExtension(char * filenameWithoutExtension, char * extension, char * filenameWithExtension)
{

	//printf("\n\nfilenameWithoutExtension = %s", filenameWithoutExtension);

	int result = TRUE;

	int i = 0;
	int j = 0;

	while(filenameWithoutExtension[j] != '\0')
	{
		filenameWithExtension[j] = filenameWithoutExtension[j];
		j++;
	}

	//printf("\nj = %d", j);

	while(extension[i] != '\0')
	{
		//printf("\n extension[i] = %c", extension[i]);

		filenameWithExtension[j] = extension[i];
		i++;
		j++;
	}
	filenameWithExtension[j] = '\0';

	return result;
}




scene_info *addSceneToEnd(scene_info *si_orig, scene_info *new_node)
{
	scene_info *tmp;
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

lighting_info *addLightToEnd(lighting_info *li_orig, lighting_info *new_node)
{

	lighting_info *tmp;


	if(li_orig == NULL)
	{
		return new_node;
	}

	/*
	printf("asd");
	exit(0);
	*/

	for(tmp = li_orig; tmp->nextLight != NULL; tmp = tmp->nextLight)
	{
		/*nothing*/
	}
	tmp->nextLight = new_node;
	return li_orig;
}


void parseTalFileInitialiseParser(char *talFileName)
{

 	FILE *f;

  	if (talFileName != NULL)
   		 f = fopen(talFileName, "r");
 	else
   		 f = stdin;

  	if(!f)
	{
		printf("error; no file name specified in code execution, and no standard input given to OpenRT.exe executable");
		exit(0);
	}
	else
	{

		init_parser(f);
	}
}

view_info * parseTalFileGetViewInfo(view_info *vi)
{
	if(! read_viewport())
	{
		printf("could not read viewport");
		exit(0);
	}

	vi = get_view_info();

	return vi;
}


lighting_info * parseTalFileGetLightInfo(lighting_info *li)
{
	while(next_light_source())
	{
		/*the first time round, read info commands do not provide relevant pointers!*/
		lighting_info* nd = new lighting_info(); //(lighting_info*)malloc(sizeof(lighting_info));

		nd->ls = *(get_light_info());
		nd->nextLight = NULL;

		li = addLightToEnd(li, nd);



	}
	return li;
}


scene_info * parseTalFileGetSceneInfo(scene_info *si)
{
	double height;
	double width;
	double length;
	double transx;
	double transy;
	double transz;

	/*defining advanced variables - for rotation, translation, scaling*/
	advanced_vec tmpAvancedVector;
	advanced_mat tmpAdvancedMatrix;	/*used for matrix manipulation*/
	advanced_mat tmpAdvancedMatrix2;/*used for matrix manipulation*/
	advanced_mat tmpAdvancedMatrix3;/*used for matrix manipulation*/
	advanced_mat rotationxMatrix;
	advanced_mat rotationyMatrix;
	advanced_mat rotationzMatrix;
	advanced_mat inverseRotationxMatrix;
	advanced_mat inverseRotationyMatrix;
	advanced_mat inverseRotationzMatrix;
	advanced_mat inverseTranslationMatrix;
	advanced_mat inverseScaleMatrix;
	advanced_mat translationMatrix;
	advanced_mat scaleMatrix;
	advanced_mat reverseMatrix;
	advanced_mat standardMatrix;

  	while (next_scene_command())
	{
		/*the first time round, read info commands do not provide relevant pointers!*/
		scene_info* nd = new scene_info(); //(scene_info*)malloc(sizeof(scene_info));
		nd->pi = *(get_piece_info());
		nd->di = *(get_dimensions_info());
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

		createRotationxMatrix(toRadians(nd->pi.xrot), &rotationxMatrix);
		createRotationyMatrix(toRadians(nd->pi.yrot), &rotationyMatrix);
		createRotationzMatrix(toRadians(nd->pi.zrot), &rotationzMatrix);
		createTranslationMatrix(transx, transy, transz, &translationMatrix);
		createScaleMatrix(width, length, height, &scaleMatrix);

		multAdvancedMatrix(&inverseRotationyMatrix, &inverseRotationxMatrix,&tmpAdvancedMatrix);
		multAdvancedMatrix(&inverseRotationzMatrix, &tmpAdvancedMatrix, &tmpAdvancedMatrix2);		//This used to be (before 14 June 2012);  multAdvancedMatrix(&inverseRotationxMatrix, &tmpAdvancedMatrix, &tmpAdvancedMatrix2);
		multAdvancedMatrix(&tmpAdvancedMatrix2, &scaleMatrix, &tmpAdvancedMatrix3);
		multAdvancedMatrix(&translationMatrix, &tmpAdvancedMatrix3, &standardMatrix);

		/*for reverseMatrix calculate*/
		/*now create the reverse matrix (A^-1)...*/

		createInverseRotationxMatrix(toRadians(nd->pi.xrot), &inverseRotationxMatrix);
		createInverseRotationyMatrix(toRadians(nd->pi.yrot), &inverseRotationyMatrix);
		createInverseRotationzMatrix(toRadians(nd->pi.zrot), &inverseRotationzMatrix);
		createInverseTranslationMatrix(transx, transy, transz, &inverseTranslationMatrix);
		createInverseScaleMatrix(width, length, height,&inverseScaleMatrix);

		multAdvancedMatrix(&inverseRotationyMatrix, &inverseRotationzMatrix, &tmpAdvancedMatrix);
		multAdvancedMatrix(&inverseRotationxMatrix, &tmpAdvancedMatrix, &tmpAdvancedMatrix2);
		multAdvancedMatrix(&tmpAdvancedMatrix2, &inverseTranslationMatrix, &tmpAdvancedMatrix3);
		multAdvancedMatrix(&inverseScaleMatrix, &tmpAdvancedMatrix3, &reverseMatrix);

		nd->standardMatrix = standardMatrix;
		nd->reverseMatrix = reverseMatrix;

		si = addSceneToEnd(si, nd);
	}
	return si;
}

void createImage(char * imageFileName, int setRGBAndDepthAndNormalAndPointMaps, unsigned char * rgbMap, double * depthMap, double * normalMap, double * pointMap, view_info *vi, scene_info *si, lighting_info *li)
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
	negativeVector(&(vi->viewat), tmp);
	addVectorsRT(tmp,(&(vi->eye)), nTilda);
	normaliseVector(nTilda);

	/*wTilda = (viewUp - eye)*/
	negativeVector(&(vi->eye), tmp);
	addVectorsRT(tmp,(&(vi->viewup)), wTilda);
	normaliseVector(wTilda);

	/*uTilda = wTilda x nTilda*/
	crossProduct(wTilda, nTilda, uTilda);
	normaliseVector(uTilda);

	/*vTilda = nTilda x uTilda*/
	crossProduct(nTilda, uTilda, vTilda);
	normaliseVector(vTilda);

		/*calculation of tildaMatrix*/

	/*creating the uTilda vTilda nTilda matrix from the u, v, n vectors*/
	makeMatrix(uTilda, vTilda, nTilda, tildaMat);



		/*raytrace x/y coordinates of view port*/

  	for(x = 0; x < vi->imgwidth; x++)
	{
		#ifdef DEMONSTRATE_CPP_STRING_TO_CSTRING_CAST_CORRUPTION
		printf("\nimageFileName = %s", imageFileName);
		#endif

		for(y = 0; y < vi->imgheight; y++)
		{
			//printf("pixel being raytraced; x= %d, y=%d", x , y);
			#ifndef RT_NO_TEXT_FEEDBACK
			if(y == 0)
			{
				printf("\nvertical line of pixels currently being raytraced; x=%d", x);
			}
			#endif



			scene_info* nd = si;

			/*calculates UVN Scalars*/
			calculateUVNScalars(vi, uvn, x, y);

			/*ray trace each piece for this point*/
			while(nd != NULL)
			{
				rayTrace(vi, nd, tildaMat, uvn);
				nd = nd -> nextScene;
			}



			if(lightingMode == 0)
			{
				calculateBasicColour(vi, si, li, &col, &tAtSurface, &nAtSurface, &pAtSurface);
				//placepoint_ppm(pm, x, y, col.r, col.g, col.b);
			}
			else if(lightingMode == 1)
			{
				calculateTransparencyColour(vi, si, li, &col);
				//placepoint_ppm(pm, x, y, col.r, col.g, col.b);

			}
			else if(lightingMode == 2)
			{
				calculateAmbientDiffuseSpecular(vi, si, li, &col, &tAtSurface, &nAtSurface, &pAtSurface);
				//placepoint_ppm(pm, x, y, col.r, col.g, col.b);
			}

			setRGBMapValues(x, y,vi->imgwidth, &col, rgbMap);

			if(setRGBAndDepthAndNormalAndPointMaps)
			{
				//printf("\n tAtSurface = %f", tAtSurface);
				//printf("\n nAtSurface.y = %f", nAtSurface.y);
				setLumOrContrastOrDepthMapValue(x, y, vi->imgwidth, tAtSurface, depthMap);
				setNormalMapValue(x, y, vi->imgwidth, &nAtSurface, normalMap);
				setPointMapValue(x, y, vi->imgwidth, &pAtSurface, pointMap);
			}


			//printf("\npAtSurface.x = %d", pAtSurface.x);
			//printf("\npAtSurface.y = %d", pAtSurface.y);
			//printf("\npAtSurface.z = %d", pAtSurface.z);

		}
	}
}



void calculateBasicColour(view_info *vi, scene_info *si, lighting_info *li, colour *rgb, double * tAtSurface, vec * nAtSurface, vec * pointAtSurface)
{
	scene_info* nd;
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
	copyVectorRT(nAtSurface, &(nd->n));
	copyVectorRT(pointAtSurface, &(nd->p));
}



int compare_tin(scene_info *p, scene_info *q, void *pointer)
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




void calculateTransparencyColour(view_info *vi, scene_info *si, lighting_info *li, colour *rgb)
{
	scene_info* nd_orig;
	scene_info* nd;

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

void calculateAmbientDiffuseSpecular(view_info *vi, scene_info *si, lighting_info *li, colour *rgb, double * tAtSurface, vec * nAtSurface, vec * pointAtSurface)
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
	lighting_info* nd2;
	vec tmp, tmp2, tmp3;
	double diff_amt, spec_amt;


		/*for scene info traversing declarations..*/

	scene_info* nd;	/*stands for 'node'*/
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

			subtractVectorsRT(&(nd->p), &(vi->eye), &v);	/* Get the vector from eye to p	*/
			normaliseVector(&v);

			col.r = ambientRed*nd->pi.col.r/MAX_COLOUR;
			col.g = ambientGreen*nd->pi.col.g/MAX_COLOUR;
			col.b = ambientBlue*nd->pi.col.b/MAX_COLOUR;

			/* Iterate over all the light sources, adding to the diffuse
			 * and specular_colours.*/

			nd2 = li;
			while(nd2 != NULL)
			{

				/* Find l for this light source; normaliseVector it. */
				subtractVectorsRT(&(nd->p), &(nd2->ls.pos), &l);
				normaliseVector(&l);


				/* Find l' using the equation on p5 of the tute 6 notes */

				multiplyVectorByScalarRT(&(nd->n), 2.0*dotproduct(&l,&(nd->n)), &tmp);	/* find  (2 l.n) n	*/
				subtractVectorsRT(&l, &tmp, &lpr);		/* subtractVectors it from l	*/


				/* Find the diffuse intensity for this light ... */


				diff_amt = -dotproduct(&l, &(nd->n)) * diffuse;
				if (diff_amt < 0.0) diff_amt=0;	/* see tute 6 pre-work */

				/*diffuse lighting effects the surface dependant on the colour of the surface
				/*method 2*/
				col.r = col.r + (nd2->ls.col.r * diff_amt)*nd->pi.col.r/MAX_COLOUR;
				col.g = col.g + (nd2->ls.col.g * diff_amt)*nd->pi.col.g/MAX_COLOUR;
				col.b = col.b + (nd2->ls.col.b * diff_amt)*nd->pi.col.b/MAX_COLOUR;
				/*
				col.r = col.r * (1 + (nd2->ls.col.r * diff_amt));
				col.g = col.g * (1 + (nd2->ls.col.g * diff_amt));
				col.b = col.b * (1 + (nd2->ls.col.b * diff_amt));
				*/

				/* ... and the specular intensity. */

				if (-(dotproduct(&lpr, &v)) < 0.0) spec_amt = 0;
				else spec_amt = pow(-dotproduct(&lpr, &v), 1.0*spec_power) * specular;
					/*'pow' is a method from math.h*/

				col.r = col.r + nd2->ls.col.r * spec_amt;
				col.g = col.g + nd2->ls.col.g * spec_amt;
				col.b = col.b + nd2->ls.col.b * spec_amt;

				/* OLD
				/*
				col.r += nd2->ls.col.r * (diff_amt + spec_amt);
				col.g += nd2->ls.col.g * (diff_amt + spec_amt);
				col.b += nd2->ls.col.b * (diff_amt + spec_amt);
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
	copyVectorRT(nAtSurface, &(nd->n));
	copyVectorRT(pointAtSurface, &(nd->p));
}



void calculateUVNScalars(view_info *vi, vec* uvn, int x, int y)
{
	double u, v, n;

	/*defining the u, v, n scalars*/
	u = ((double)x - (vi->imgwidth)/2)*(vi->viewwidth)/(vi->imgwidth);
	v = ((vi->imgheight)/2 - (double)y)*(vi->viewheight)/(vi->imgheight);
	n = -vi->focal_length;

	/*creating the uvn vector from the u, v, n scalars*/
	uvn->x = u;
	uvn->y = v;
	uvn->z = n;

	return;
}

void calculatePointMapValue(double xPos, double yPos, double depthVal, vec * xyzWorld, view_info * vi)
{
	//this function requires viewat, viewup and eye vectors to be defined

	/*
	cout << "xPos = " << xPos << endl;
	cout << "yPos = " << yPos << endl;
	cout << "depthVal = " << depthVal << endl;
	cout << "vi->viewat.x = " << vi->viewat.x << endl;
	cout << "vi->viewat.y = " << vi->viewat.y << endl;
	cout << "vi->viewat.z = " << vi->viewat.z << endl;
	cout << "vi->viewup.x = " << vi->viewup.x << endl;
	cout << "vi->viewup.y = " << vi->viewup.y << endl;
	cout << "vi->viewup.z = " << vi->viewup.z << endl;
	cout << "vi->eye.x = " << vi->eye.x << endl;
	cout << "vi->eye.y = " << vi->eye.y << endl;
	cout << "vi->eye.z = " << vi->eye.z << endl;
	cout << "vi->focal_length = " << vi->focal_length << endl;
	*/

	vec uvn;
	calculateUVNScalars(vi, &uvn, xPos, yPos);

	vec p;
	vec p0;
	vec p1;
	calculatePointUsingTInWorld(depthVal, &p0, &p1, vi, &p, &uvn);

	xyzWorld->x = p.x;
	xyzWorld->y = p.y;
	xyzWorld->z = p.z;

	/*
	cout << "p.x = " << p.x << endl;
	cout << "p.y = " << p.y << endl;
	cout << "p.z = " << p.z << endl;
	*/

}

void createPointMapUsingDepthMap(int imageWidth, int imageHeight, double * pointMap, double * depthMap,  view_info * vi)
{
	for(int y = 0; y < (imageHeight); y++)
	{
		for(int x = 0; x < (imageWidth); x++)
		{
			vec xyzWorld;
			double depthVal = getLumOrContrastOrDepthMapValue(x, y, imageWidth, depthMap);
			calculatePointMapValue(x, y, depthVal, &xyzWorld, vi);
			setPointMapValue(x, y, imageWidth, &xyzWorld, pointMap);

		}
	}

}



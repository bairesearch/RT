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
 * File Name: RTscene.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3c4b 01-December-2012
 *
 *******************************************************************************/


#ifndef HEADER_RT_SCENE
#define HEADER_RT_SCENE


#include "RTraytracer.h"
#include "RTparser.h"
#include "RTppm.h"



//#define DEMONSTRATE_CPP_STRING_TO_CSTRING_CAST_CORRUPTION
//#define TEST_DEPTH_NORMAL_MAP_CREATION


#define NO_COLOUR 0
#define TRUE 1
#define FALSE 0
#define FAILED 0
#define SUCCESSFUL 0

#define MAX_COLOUR 255.0
#define MIN_COLOUR 0.0

#define LIGHTING_MODE_BASIC (0)
#define LIGHTING_MODE_ARTIFICIAL_TRANSPARENCY (1)
#define LIGHTING_MODE_AMBIENT_DIFFUSE_SPECULAR (2)
#define DEFAULT_LIGHTING_MODE (LIGHTING_MODE_AMBIENT_DIFFUSE_SPECULAR)


	/*secondary global vars used for artificial transparancy*/

/*used to calculate the amount of colour subtraced during lights progression between tin and tout
distance units as defined by tin, tout values in scene*/
#define RATIO_OF_COLOUR_LOSS_TO_DISTANCE 0.01	//#define RATIO_OF_COLOUR_LOSS_TO_DISTANCE 2
#define SURFACE_COLOUR_CONCENTRATION 1		//#define SURFACE_COLOUR_CONCENTRATION 1

	/*secondary global used for Amb-Diff-Spec*/

#define AMBIENT_RED 0.6		//#define AMBIENT_RED 0.3
#define AMBIENT_GREEN 0.6	//#define AMBIENT_GREEN 0.3
#define AMBIENT_BLUE 0.6	//#define AMBIENT_BLUE 0.3
#define SPECULAR_POWER 2.0	//#define SPECULAR_POWER 2.0
#define SPECULAR 0.01 		//#define SPECULAR 0.02
#define DIFFUSE 0.002 		//#define DIFFUSE 0.003

#define ONE 1.0  /*default height of object*/
/*decimal places are used instead of fractions since C has trouble calculating
the 2/15 -HEIGHT_OF_BASEPLATE- fraction...*/




/*
typedef struct light lightingInfo;
struct light
{
	lightSource ls;
	lightingInfo *nextLight;
};
*/

class lightingInfo
{
public:

	lightingInfo(void);
	~lightingInfo(void);

	lightSource ls;
	lightingInfo *nextLight;
};


int rayTraceScene(char * talFileName, char * imageFileName, int outputImageFiles, int setRGBAndDepthAndNormalAndPointMaps, unsigned char * rgbMap, double * depthMap, double * normalMap, double * pointMap);
	int rayTraceSceneWithoutParse(ViewInfo *vi, sceneInfo *si, lightingInfo *li, char * imageFileName, int outputImageFiles, int setRGBAndDepthAndNormalAndPointMaps, unsigned char * rgbMap, double * depthMap, double * normalMap, double * pointMap);

void setSceneLightingConditions(float lightingAmbientRedNew, float lightingAmbientGreenNew, float lightingAmbientBlueNew, float lightingSpecularNew, float lightingDiffuseNew);
void setLightingMode(int newLightingMode);

void parseTalFileInitialiseParser(char *talFileName);
ViewInfo * parseTalFileGetViewInfo(ViewInfo *vi);
lightingInfo * parseTalFileGetLightInfo(lightingInfo *li);
sceneInfo * parseTalFileGetSceneInfo(sceneInfo *si);

void createImage(char * imageFileName, int setRGBAndDepthAndNormalAndPointMaps, unsigned char * rgbMap, double * depthMap, double * normalMap, double * pointMap, ViewInfo *vi, sceneInfo *si, lightingInfo *li);


typedef struct advancedColour colourAdvanced;
struct advancedColour
{
	double r, g, b;
};

void calculateTransparencyColour(ViewInfo *vi, sceneInfo *si, lightingInfo *li, colour *rgb);

void calculateUVNScalars(ViewInfo *vi, vec* uvn, int x, int y);

void calculateAmbientDiffuseSpecular(ViewInfo *vi, sceneInfo *si, lightingInfo *li, colour *rgb, double * tAtSurface, vec * nAtSurface, vec * pointAtSurface);

void calculateBasicColour(ViewInfo *vi, sceneInfo *si, lightingInfo *li, colour *rgb, double * tAtSurface, vec * nAtSurface, vec * pointAtSurface);


int stripExtension(char * filenameWithExtension, char * filenameWithoutExtension);
int addExtension(char * filenameWithoutExtension, char * extension, char * filenameWithExtension);


void calculatePointMapValue(double xPos, double yPos, double depthVal, vec * xyzWorld, ViewInfo * vi);

void createPointMapUsingDepthMap(int imageWidth, int imageHeight, double * pointMap, double * depthMap,  ViewInfo * vi);


#endif

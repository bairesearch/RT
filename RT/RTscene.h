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
 * File Name: RTscene.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3f4a 11-July-2015
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
typedef struct light RTlightingInfo;
struct light
{
	RTlightSource ls;
	RTlightingInfo* nextLight;
};
*/

class RTlightingInfo
{
public:

	RTlightingInfo(void);
	~RTlightingInfo(void);

	RTlightSource ls;
	RTlightingInfo* nextLight;
};


int rayTraceScene(string talFileName, string imageFileName, int outputImageFiles, int setRGBAndDepthAndNormalAndPointMaps, unsigned char* rgbMap, double* depthMap, double* normalMap, double* pointMap);
	int rayTraceSceneWithoutParse(RTviewInfo* vi, RTsceneInfo* si, RTlightingInfo* li, string imageFileName, int outputImageFiles, int setRGBAndDepthAndNormalAndPointMaps, unsigned char* rgbMap, double* depthMap, double* normalMap, double* pointMap);

void setSceneLightingConditions(float lightingAmbientRedNew, float lightingAmbientGreenNew, float lightingAmbientBlueNew, float lightingSpecularNew, float lightingDiffuseNew);
void setLightingMode(int newLightingMode);

void parseTalFileInitialiseParser(string talFileName);
RTviewInfo* parseTalFileGetViewInfo(RTviewInfo* vi);
RTlightingInfo* parseTalFileGetLightInfo(RTlightingInfo* li);
RTsceneInfo* parseTalFileGetSceneInfo(RTsceneInfo* si);

void createImage(int setRGBAndDepthAndNormalAndPointMaps, unsigned char* rgbMap, double* depthMap, double* normalMap, double* pointMap, RTviewInfo* vi, RTsceneInfo* si, RTlightingInfo* li);


typedef struct advancedColour colourAdvanced;
struct advancedColour
{
	double r, g, b;
};

void calculateTransparencyColour(RTviewInfo* vi, RTsceneInfo* si, RTlightingInfo* li, colour* rgb);

void calculateUVNScalars(RTviewInfo* vi, vec* uvn, int x, int y);

void calculateAmbientDiffuseSpecular(RTviewInfo* vi, RTsceneInfo* si, RTlightingInfo* li, colour* rgb, double* tAtSurface, vec* nAtSurface, vec* pointAtSurface);

void calculateBasicColour(RTviewInfo* vi, RTsceneInfo* si, RTlightingInfo* li, colour* rgb, double* tAtSurface, vec* nAtSurface, vec* pointAtSurface);


bool stripExtension(string filenameWithExtension, string* filenameWithoutExtension);
bool addExtension(string filenameWithoutExtension, string extension, string* filenameWithExtension);


void calculatePointMapValue(double xPos, double yPos, double depthVal, vec* xyzWorld, RTviewInfo* vi);

void createPointMapUsingDepthMap(int imageWidth, int imageHeight, double* pointMap, double* depthMap,  RTviewInfo* vi);


#endif

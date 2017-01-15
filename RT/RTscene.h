/*******************************************************************************
 *
 * File Name: RTscene.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2010 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3a6b 30-Apr-2012
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
typedef struct light lighting_info;
struct light
{
	light_source ls;
	lighting_info *nextLight;
};
*/

class lighting_info
{
public:

	lighting_info(void);
	~lighting_info(void);

	light_source ls;
	lighting_info *nextLight;
};


int rayTraceScene(char * talFileName, char * imageFileName, int outputImageFiles, int setRGBAndDepthAndNormalAndPointMaps, unsigned char * rgbMap, double * depthMap, double * normalMap, double * pointMap);
	int rayTraceSceneWithoutParse(view_info *vi, scene_info *si, lighting_info *li, char * imageFileName, int outputImageFiles, int setRGBAndDepthAndNormalAndPointMaps, unsigned char * rgbMap, double * depthMap, double * normalMap, double * pointMap);

void setSceneLightingConditions(float lightingAmbientRedNew, float lightingAmbientGreenNew, float lightingAmbientBlueNew, float lightingSpecularNew, float lightingDiffuseNew);
void setLightingMode(int newLightingMode);


//void parseTalFile(char *talFileName, view_info *vi, scene_info *si, lighting_info *li);
void parseTalFileInitialiseParser(char *talFileName);
view_info * parseTalFileGetViewInfo(view_info *vi);
lighting_info * parseTalFileGetLightInfo(lighting_info *li);
scene_info * parseTalFileGetSceneInfo(scene_info *si);



void createImage(char * imageFileName, int setRGBAndDepthAndNormalAndPointMaps, unsigned char * rgbMap, double * depthMap, double * normalMap, double * pointMap, view_info *vi, scene_info *si, lighting_info *li);







typedef struct advancedColour colourAdvanced;
struct advancedColour
{
	double r, g, b;
};

void calculateTransparencyColour(view_info *vi, scene_info *si, lighting_info *li, colour *rgb);

//scene_info *addToEnd(scene_info *si_orig, scene_info *new_node);

void calculateUVNScalars(view_info *vi, vec* uvn, int x, int y);

//void colourPixel(int x, int y);

void calculateAmbientDiffuseSpecular(view_info *vi, scene_info *si, lighting_info *li, colour *rgb, double * tAtSurface, vec * nAtSurface, vec * pointAtSurface);

void calculateBasicColour(view_info *vi, scene_info *si, lighting_info *li, colour *rgb, double * tAtSurface, vec * nAtSurface, vec * pointAtSurface);


//void setNormalMapValue(int x, int y, int imageHeight, vec * normalVal, double * normalMap);
//void getNormalMapValue(int x, int y, int imageHeight, double * normalMap, vec * normalVal);

int stripExtension(char * filenameWithExtension, char * filenameWithoutExtension);
int addExtension(char * filenameWithoutExtension, char * extension, char * filenameWithExtension);


void calculatePointMapValue(double xPos, double yPos, double depthVal, vec * xyzWorld, view_info * vi);

void createPointMapUsingDepthMap(int imageWidth, int imageHeight, double * pointMap, double * depthMap,  view_info * vi);


#endif

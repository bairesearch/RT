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
 * File Name: RTpixelMaps.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3h9b 09-December-2015
 *
 *******************************************************************************/

#ifndef HEADER_RT_PIXELMAPS
#define HEADER_RT_PIXELMAPS

#include "RTglobalDefs.h"
#include "SHAREDvars.h"
#include "RTppm.h"
#include "RTviewinfo.h"



#define RED_R (255)
#define RED_G (0)
#define RED_B (0)
#define GREEN_R (0)
#define GREEN_G (255)
#define GREEN_B (0)
#define BLUE_R (0)
#define BLUE_G (0)
#define BLUE_B (255)
#define DARK_RED_R (127)
#define DARK_RED_G (0)
#define DARK_RED_B (0)
#define DARK_GREEN_R (0)
#define DARK_GREEN_G (127)
#define DARK_GREEN_B (0)
#define DARK_BLUE_R (0)
#define DARK_BLUE_G (0)
#define DARK_BLUE_B (127)
#define YELLOW_R (255)
#define YELLOW_G (255)
#define YELLOW_B (0)
#define CYAN_R (0)
#define CYAN_G (255)
#define CYAN_B (255)
#define MAGENTA_R (255)
#define MAGENTA_G (0)
#define MAGENTA_B (255)

#define VEC_MAP_VEC_NUM_DIMENSIONS (3)
#define VEC_MAP_VEC_X (0)
#define VEC_MAP_VEC_Y (1)
#define VEC_MAP_VEC_Z (2)

#define PIXMAP_NUMBER_OF_RGB_COLOURS (3)
#define LUMINOSITY_MAP_MAX_RGB_VALUE (256)
#define LUMINOSITY_MAP_MAX_LUMINOSITY_VALUE (LUMINOSITY_MAP_MAX_RGB_VALUE*PIXMAP_NUMBER_OF_RGB_COLOURS)
#define CONTRAST_MAP_MAX_CONTRAST_VALUE (LUMINOSITY_MAP_MAX_LUMINOSITY_VALUE)

//#define USE_CONTRAST_PIXMAP_INVERSE
//#define USE_BOOLEAN_PIXMAP_INVERSE
//#define USE_BOOLEAN_PIXMAP_DOT_ENHANCEMENT
#define BOOLEAN_PIXMAP_DOT_ENHANCEMENT (1)	//or 0
#define BOOLEAN_PIXMAP_DOT_RED (255)
#define BOOLEAN_PIXMAP_DOT_GREEN (0)
#define BOOLEAN_PIXMAP_DOT_BLUE (0)

/*
#define CONTRAST_MAP_THRESHOLD_VALUE (100)	//33/256 or 100/768
#define LUMINOSITY_MAP_THRESHOLD_VALUE (100)	//33/256 or 100/768
*/


void printRGBMap(int imageWidth, int imageHeight, unsigned char* rgbMap);

double calculateLuminosityLevelFromColour(colour* col);

void setBooleanMapValue(int x, int y, int imageWidth, bool booleanVal, bool* booleanMap);
bool getBooleanMapValue(int x, int y, int imageWidth, bool* booleanMap);

void setIntMapValue(int x, int y, int imageWidth, int intVal, int* intMap);
int getIntMapValue(int x, int y, int imageWidth, int* intMap);

unsigned char getRGBMapValue(int x, int y, int imageWidth, int rgb, unsigned char* rgbMap);
void getRGBMapValues(int x, int y, int imageWidth, unsigned char* rgbMap, colour* col);
void setRGBMapValues(int x, int y, int imageWidth, colour* col, unsigned char* rgbMap);
void setRGBMapValue(int x, int y, int imageWidth, int rgb, unsigned char* rgbMap, int rgbVal);

void setNormalMapValue(int x, int y, int imageWidth, vec* normalVal, double* normalMap);
void getNormalMapValue(int x, int y, int imageWidth, double* normalMap, vec* normalVal);
void setPointMapValue(int x, int y, int imageWidth, vec* pointVal, double* pointMap);
void getPointMapValue(int x, int y, int imageWidth, double* pointMap, vec* pointVal);
	void setVectorMapValue(int x, int y, int imageWidth, vec* vectorVal, double* vectorMap);
	void getVectorMapValue(int x, int y, int imageWidth, double* vectorMap, vec* vectorVal);

void setLumOrContrastOrDepthMapValue(int x, int y, int imageWidth, double contrastVal, double* contrastMap);
double getLumOrContrastOrDepthMapValue(int x, int y, int imageWidth, double* contrastMap);

void generatePixmapFromRGBmap(string imageFileName, int imageWidth, int imageHeight, unsigned char* rgbMap);
void generatePixmapFromLuminosityContrastMap(string imageFileName, int imageWidth, int imageHeight, double* contrastMap);
void generatePixmapFromDepthMapOrDepthContrastMap(string imageFileName, int imageWidth, int imageHeight, double* depthMap);
void generatePixmapFromDepthMapOrDepthContrastMapAdvanced(string imageFileName, int imageWidth, int imageHeight, double* depthMap, double noHitDepth, double estimateMaxDepth);
void generateRGBMapFromDepthMapOrDepthContrastMap(int imageWidth, int imageHeight, double* depthMap, unsigned char* rgbMap);
void generateRGBMapFromDepthMapOrDepthContrastMapAdvanced(int imageWidth, int imageHeight, double* depthMap, unsigned char* rgbMap, double noHitDepth, double estimateMaxDepth);
void generatePixmapFromNormalMap(string imageFileName, int imageWidth, int imageHeight, double* normalMap);
void generateRGBMapFromNormalMap(int imageWidth, int imageHeight, double* normalMap, unsigned char* rgbMap);
void generatePixmapFromLuminosityMap(string imageFileName, int imageWidth, int imageHeight, double* luminosityMap);
void generatePixmapFromBooleanMap(string imageFileName, int imageWidth, int imageHeight, bool* booleanMap);
void generatePixmapFromEnumIntMap(string filename, int imageWidth, int imageHeight, int* intMap);
void generateBooleanContrastPixmapFromRGBMap(string imageFileName, int imageWidth, int imageHeight, unsigned char* rgbMap);
	void normaliseRGBMapBasedOnAverageLuminosity(unsigned char* normalisedRgbMap, int imageWidth, int imageHeight, unsigned char* rgbMap);
		double calculateAverageLuminosity(int imageWidth, int imageHeight, unsigned char* rgbMap);
void generateBooleanDiffMapFromRGBMaps(string imageFileName, int imageWidth, int imageHeight, unsigned char* rgbMap1, unsigned char* rgbMap2);

void generatePixmapFromDepthMap24Bit(string imageFileName, int imageWidth, int imageHeight, double* depthMap, double depthScale, double depthOffset);
void calculate24BitDepthPixmapPixelFromDepth(double depth, double depthScale, double depthOffset, colour* depthMap24BitPixelValue);



void writeImage(string imageFileName, pixmap* pm);
void readImage(string imageFileName, unsigned char* rgbMap);

//methods taken from ORoperations.cpp;
void createRGBMapFromPixmapImage(pixmap* objectImage, unsigned char* rgbMap);
	void calculateColourFromPixmapPixel(pixmap* pm, int pixelPositionInPixmap, colour* col);
void createDepthMapFromDepth24BitPixmapImage(pixmap* depth24BitPixMap, double* depthMap, double depthScale, double depthOffset);
	double calculateDepthFrom24BitDepthValue(colour* depthMap24BitPixelValue, double depthScale, double depthOffset);
void createLuminosityMapFromPixmapImage(pixmap* objectImage, double* luminosityMap);
	double calculateLuminosityLevelFromPixmapPixel(pixmap* pm, int pixelPositionInPixmap);
void createLuminosityMapFromRGBMap(int imageWidth, int imageHeight, unsigned char* rgbMap, double* luminosityMap);
	double calculateLuminosityLevelFromRGBMap(int x, int y, int imageWidth, unsigned char* rgbMap);
		double calculateLuminosityLevelFromRGBVal(colour* rgbVal);
void createLuminosityContrastMapFromRGBMap(int imageWidth, int imageHeight, unsigned char* rgbMap, double* luminosityContrastMap);
void createContrastMapFromMap(int imageWidth, int imageHeight, double* luminosityMap, double* contrastMap);
	double calculateContrastLevelWithinKernel(int pixelX, int pixelY, double* luminosityMap, int kernelWidth, int kernelHeight, int imageWidth, int imageHeight);

	double calculateContrastLevelWithinKernelRGBComponent(int pixelX, int pixelY, unsigned char* rgbMap, int rgbComponent, int kernelWidth, int kernelHeight, int imageWidth, int imageHeight);



void createLuminosityContrastBooleanMap(int imageWidth, int imageHeight, double* luminosityContrastMap, bool* luminosityContrastBooleanMap);
void createLuminosityBooleanMap(int imageWidth, int imageHeight, double* luminosityMap, bool* luminosityBooleanMap);

#ifndef USE_OR
void fillInRTRulesExternVariables();
#endif

#endif


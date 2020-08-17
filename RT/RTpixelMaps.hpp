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
 * File Name: RTpixelMaps.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2020 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3n7c 17-August-2020
 * /
 *******************************************************************************/


#ifndef HEADER_RT_PIXELMAPS
#define HEADER_RT_PIXELMAPS

#include "RTglobalDefs.hpp"
#include "SHAREDvars.hpp"
#include "RTppm.hpp"
#include "RTviewinfo.hpp"



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


class RTpixelMapsClass
{
	private: RTppmClass RTppm;
	private: SHAREDvarsClass SHAREDvars;
	public: void printRGBMap(int imageWidth, const int imageHeight, unsigned char* rgbMap);

	private: double calculateLuminosityLevelFromColour(const colour* col);

	public: void setBooleanMapValue(const int x, const int y, const int imageWidth, bool booleanVal, bool* booleanMap);
	public: bool getBooleanMapValue(const int x, const int y, const int imageWidth, const bool* booleanMap);

	public: void setIntMapValue(const int x, const int y, const int imageWidth, int intVal, int* intMap);
	private: int getIntMapValue(const int x, const int y, const int imageWidth, const int* intMap);

	public: unsigned char getRGBMapValue(const int x, const int y, const int imageWidth, const int rgb, const unsigned char* rgbMap);
	public: void getRGBMapValues(int x, int y, int imageWidth, unsigned char* rgbMap, colour* col);
	public: void setRGBMapValues(const int x, const int y, const int imageWidth, colour* col, unsigned char* rgbMap);
	public: void setRGBMapValue(const int x, const int y, const int imageWidth, const int rgb, unsigned char* rgbMap, int rgbVal);

	public: void setNormalMapValue(const int x, const int y, const int imageWidth, vec* normalVal, double* normalMap);
	public: void getNormalMapValue(int x, int y, int imageWidth, double* normalMap, vec* normalVal);
	public: void setPointMapValue(const int x, const int y, const int imageWidth, vec* pointVal, double* pointMap);
	public: void getPointMapValue(int x, int y, int imageWidth, double* pointMap, vec* pointVal);
		public: void setVectorMapValue(const int x, const int y, const int imageWidth, vec* vectorVal, double* vectorMap);
		public: void getVectorMapValue(int x, int y, int imageWidth, double* vectorMap, vec* vectorVal);

	public: void setLumOrContrastOrDepthMapValue(const int x, const int y, const int imageWidth, double contrastVal, double* contrastMap);
	public: double getLumOrContrastOrDepthMapValue(const int x, const int y, const int imageWidth, const double* contrastMap);

	public: void generatePixmapFromRGBmap(const string imageFileName, int imageWidth, const int imageHeight, unsigned char* rgbMap);
	public: void generatePixmapFromLuminosityContrastMap(const string imageFileName, const int imageWidth, const int imageHeight, const double* contrastMap);
	public: void generatePixmapFromDepthMapOrDepthContrastMap(const string imageFileName, const int imageWidth, const int imageHeight, const double* depthMap);
	public: void generatePixmapFromDepthMapOrDepthContrastMapAdvanced(const string imageFileName, const int imageWidth, const int imageHeight, const double* depthMap, const double noHitDepth, const double estimateMaxDepth);
	public: void generateRGBMapFromDepthMapOrDepthContrastMap(const int imageWidth, const int imageHeight, const double* depthMap, unsigned char* rgbMap);
	public: void generateRGBMapFromDepthMapOrDepthContrastMapAdvanced(const int imageWidth, const int imageHeight, const double* depthMap, unsigned char* rgbMap, const double noHitDepth, const double estimateMaxDepth);
	public: void generatePixmapFromNormalMap(const string imageFileName, int imageWidth, const int imageHeight, double* normalMap);
	private: void generateRGBMapFromNormalMap(int imageWidth, const int imageHeight, double* normalMap, unsigned char* rgbMap);
	public: void generatePixmapFromLuminosityMap(const string imageFileName, const int imageWidth, const int imageHeight, const double* luminosityMap);
	public: void generatePixmapFromBooleanMap(const string imageFileName, const int imageWidth, const int imageHeight, const bool* booleanMap);
	private: void generatePixmapFromEnumIntMap(const string filename, const int imageWidth, const int imageHeight, const int* intMap);
	public: void generateBooleanContrastPixmapFromRGBMap(const string imageFileName, int imageWidth, const int imageHeight, unsigned char* rgbMap);
	#ifdef USE_OR
		private: void normaliseRGBMapBasedOnAverageLuminosity(unsigned char* normalisedRgbMap, int imageWidth, const int imageHeight, unsigned char* rgbMap);
			private: double calculateAverageLuminosity(int imageWidth, const int imageHeight, unsigned char* rgbMap);
	#endif
	public: void generateBooleanDiffMapFromRGBMaps(const string imageFileName, int imageWidth, const int imageHeight, unsigned char* rgbMap1, unsigned char* rgbMap2);

	public: void generatePixmapFromDepthMap24Bit(const string imageFileName, const int imageWidth, const int imageHeight, const double* depthMap, const double depthScale, const double depthOffset);
	public: void calculate24BitDepthPixmapPixelFromDepth(const double depth, const double depthScale, const double depthOffset, colour* depthMap24BitPixelValue);



	public: void writeImage(const string imageFileName, pixmap* pm);
	public: void readImage(const string imageFileName, unsigned char* rgbMap);

//methods taken from ORoperations.cpp;
	public: void createRGBMapFromPixmapImage(pixmap* objectImage, unsigned char* rgbMap);
		private: void calculateColourFromPixmapPixel(pixmap* pm, int pixelPositionInPixmap, colour* col);
	public: void createDepthMapFromDepth24BitPixmapImage(pixmap* depth24BitPixMap, double* depthMap, const double depthScale, const double depthOffset);
		public: double calculateDepthFrom24BitDepthValue(const colour* depthMap24BitPixelValue, const double depthScale, const double depthOffset);
	private: void createLuminosityMapFromPixmapImage(pixmap* objectImage, double* luminosityMap);
		private: double calculateLuminosityLevelFromPixmapPixel(const pixmap* pm, const int pixelPositionInPixmap);
	public: void createLuminosityMapFromRGBMap(int imageWidth, const int imageHeight, unsigned char* rgbMap, double* luminosityMap);
		public: double calculateLuminosityLevelFromRGBMap(int x, int y, int imageWidth, unsigned char* rgbMap);
			public: double calculateLuminosityLevelFromRGBVal(const colour* rgbVal);
	private: void createLuminosityContrastMapFromRGBMap(int imageWidth, const int imageHeight, unsigned char* rgbMap, double* luminosityContrastMap);
	public: void createContrastMapFromMap(const int imageWidth, const int imageHeight, const double* luminosityMap, double* contrastMap);
		private: double calculateContrastLevelWithinKernel(const int pixelX, const int pixelY, const double* luminosityMap, const int kernelWidth, const int kernelHeight, const int imageWidth, const int imageHeight);

		private: double calculateContrastLevelWithinKernelRGBComponent(const int pixelX, const int pixelY, const unsigned char* rgbMap, const int rgbComponent, const int kernelWidth, const int kernelHeight, const int imageWidth, const int imageHeight);



	public: void createLuminosityContrastBooleanMap(const int imageWidth, const int imageHeight, const double* luminosityContrastMap, bool* luminosityContrastBooleanMap);
	public: void createLuminosityBooleanMap(const int imageWidth, const int imageHeight, const double* luminosityMap, bool* luminosityBooleanMap);

#ifndef USE_OR
	public: void fillInRTRulesExternVariables();
#endif

};

#endif


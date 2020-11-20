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
 * File Name: RTppm.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2020 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3o4a 17-November-2020
 * /
 *******************************************************************************/


#ifndef HEADER_RT_PPM
#define HEADER_RT_PPM

#include "SHAREDglobalDefs.hpp"

#define JPEG_EXTENSION ".jpg"
#define PPM_EXTENSION ".ppm"

#define RGB_MAP_PPM_EXTENSION ".rgb.ppm"
#define NORMALMAP_PPM_EXTENSION ".normal.ppm"
#define LUMINOSITY_MAP_PPM_EXTENSION ".luminosity.ppm"
#define LUMINOSITY_BOOLEAN_MAP_PPM_EXTENSION ".luminosity.boolean.ppm"
#define LUMINOSITY_CONTRAST_MAP_PPM_EXTENSION ".luminosity.contrast.ppm"
#define LUMINOSITY_CONTRAST_BOOLEAN_MAP_PPM_EXTENSION ".luminosity.contrast.boolean.ppm"
#define DEPTHMAP_PPM_EXTENSION ".depth.ppm"
#define DEPTH_CONTRAST_MAP_PPM_EXTENSION ".depth.contrast.ppm"
#define DEPTH_CONTRAST_BOOLEAN_MAP_PPM_EXTENSION ".depth.contrast.boolean.ppm"
#define DEPTH_GRADIENT_MAP_PPM_EXTENSION ".depth.gradient.ppm"
#define DEPTH_GRADIENT_CONTRAST_MAP_PPM_EXTENSION ".depth.gradient.contrast.ppm"
#define DEPTH_GRADIENT_CONTRAST_BOOLEAN_MAP_PPM_EXTENSION ".depth.gradient.contrast.boolean.ppm"
#define LUMINOSITY_CONTRAST_MINUS_DEPTH_CONTRAST_BOOLEAN_MAP_PPM_EXTENSION ".luminositycontrastminusdepthcontrast.boolean.ppm"
#define POINT_NORMAL_CONTRAST_MAP_PPM_EXTENSION ".pointnormalcontrast.ppm"
#define POINT_NORMAL_CONTRAST_BOOLEAN_MAP_PPM_EXTENSION ".pointnormalcontrast.boolean.ppm"
#define RGB_DEV_MAP_PPM_EXTENSION ".rgbdev.ppm"
#define RGB_BOOLEAN_CONTRAST_MAP_PPM_EXTENSION ".rgb.contrast.boolean.ppm"

#define RGB_MAP_PPM_EXTENSION_PART ".rgb"
#define NORMALMAP_PPM_EXTENSION_PART ".normal"
#define LUMINOSITY_MAP_PPM_EXTENSION_PART ".luminosity"
#define LUMINOSITY_BOOLEAN_MAP_PPM_EXTENSION_PART ".luminosity.boolean"
#define LUMINOSITY_CONTRAST_MAP_PPM_EXTENSION_PART ".luminosity.contrast"
#define LUMINOSITY_CONTRAST_BOOLEAN_MAP_PPM_EXTENSION_PART ".luminosity.contrast.boolean"
#define DEPTHMAP_PPM_EXTENSION_PART ".depth"
#define DEPTHMAP24BIT_PPM_EXTENSION_PART ".depth24bit"
#define DEPTH_CONTRAST_MAP_PPM_EXTENSION_PART ".depth.contrast"
#define DEPTH_CONTRAST_BOOLEAN_MAP_PPM_EXTENSION_PART ".depth.contrast.boolean"
#define DEPTH_GRADIENT_MAP_PPM_EXTENSION_PART ".depth.gradient"
#define DEPTH_GRADIENT_CONTRAST_MAP_PPM_EXTENSION_PART ".depth.gradient.contrast"
#define DEPTH_GRADIENT_CONTRAST_BOOLEAN_MAP_PPM_EXTENSION_PART ".depth.gradient.contrast.boolean"
#define LUMINOSITY_CONTRAST_MINUS_DEPTH_CONTRAST_BOOLEAN_MAP_PPM_EXTENSION_PART ".luminositycontrastminusdepthcontrast.boolean"
#define POINT_NORMAL_CONTRAST_MAP_PPM_EXTENSION_PART ".pointnormalcontrast"
#define POINT_NORMAL_CONTRAST_BOOLEAN_MAP_PPM_EXTENSION_PART ".pointnormalcontrast.boolean"
#define FEATUREMAP_PPM_EXTENSION_PART ".featuresRaw"
#define FEATURESMAP_PPM_EXTENSION_PART ".features"
#define TRANSFORMED_FEATURES_NEARBY_EXTENSION_PART ".transformedFeaturesNearby"
#define TRANSFORMED_FEATURES_ALL_EXTENSION_PART ".transformedFeaturesAll"
#define TRANSFORMED_FEATURES_OT_EXTENSION_PART ".transformedFeaturesOT"
#define TFD_EXTENSION ".tfd"	//transformed feature data
#define RGB_DEV_MAP_PPM_EXTENSION_PART ".rgbdev"
#define RGB_BOOLEAN_CONTRAST_MAP_PPM_EXTENSION_PART ".rgb.contrast.boolean"

/*
  This structure represents a 24bit pixmap.
  The address of the pixel at (x, y) is calculated
  with &pm->pix[((int64_t)pm->wide*y + x)*3];
 */

typedef struct{
	int wide, high;
	uchar* pix;
}pixmap;

class RTppmClass
{
	public: void placepointPPM(pixmap* pm, const int x, const int y, int r, int g, int b);

	public: pixmap* newPixmap(const int wide, const int high);  /*create a new blank pixmap*/

	public: pixmap* loadPPM(const string fname);         /*load a ppm file into a pixmap*/	/*if fname is NULL, open standard input*/

	public: void writePPM(const string fname, const pixmap* pm); /*write a pixmap to a ppm file*/	 /*if fname is NULL, write to stdout*/

	public: void freePixmap(pixmap* pm);           /*free the memory occupied by a pixmap*/

	private: uchar* calcPixelAddress(const pixmap* pm, const int x, const int y);
};	/*Calculate the address of the rgb pixel at (x, y) in the pixmap*/

#endif

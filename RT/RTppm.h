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
 * File Name: RTppm.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3c2a 19-October-2012
 *
 *******************************************************************************/

#ifndef HEADER_RT_PPM
#define HEADER_RT_PPM

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
  with &pm->pix[((long)pm->wide*y + x)*3];
 */

typedef struct{
  int wide, high;
  unsigned char *pix;
}pixmap;

void placepoint_ppm(pixmap *pm, int x, int y, int r, int g, int b);

pixmap *new_pixmap(int wide, int high);  /*create a new blank pixmap*/

pixmap *load_ppm(char *fname);         /*load a ppm file into a pixmap*/	/*if fname is NULL, open standard input*/
				       
void write_ppm(char *fname, pixmap *pm); /*write a pixmap to a ppm file*/	 /*if fname is NULL, write to stdout*/
					
void free_pixmap(pixmap *pm);           /*free the memory occupied by a pixmap*/

unsigned char* calc_pixel_address(pixmap *pm, int x, int y);	/*Calculate the address of the rgb pixel at (x, y) in the pixmap*/

#endif

/*******************************************************************************
 *
 * File Name: RTglobalsDefs.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3a7a 06-June-2012
 * Description: RT specific global definitions
 *
 *******************************************************************************/

#ifndef HEADER_RT_GLOBAL_DEFS
#define HEADER_RT_GLOBAL_DEFS

#include "SHAREDglobalDefs.h"

#define RT_NO_TEXT_FEEDBACK

#define RGB_RED (0)
#define RGB_GREEN (1)
#define RGB_BLUE (2)
#define RGB_NUM (3)

#define MAX_RGB_VAL (255)
#define MAX_LUMINOSITY (MAX_RGB_VAL*RGB_NUM)
#define MAX_NORMAL (1.0)

#define CONTRAST_MAP_GENERATION_KERNEL_WIDTH_NO_INTERPIXEL (3)
#define CONTRAST_MAP_GENERATION_KERNEL_HEIGHT_NO_INTERPIXEL (3)
#define CONTRAST_MAP_GENERATION_KERNEL_WIDTH_INTERPIXEL (2)
#define CONTRAST_MAP_GENERATION_KERNEL_HEIGHT_INTERPIXEL (2)


//RT_SHARED_VARS...

extern bool OR_USE_CONTRAST_CALC_METHOD_C;		//OR_USE_CONTIGUOUS_REGION_FIND_CENTRED_FEATURES_SUBPIXEL_ACCURACY may be more recommended with OR_USE_CONTRAST_CALC_METHOD_B
extern bool OR_USE_CONTRAST_CALC_METHOD_B;		//OR_USE_CONTIGUOUS_REGION_FIND_CENTRED_FEATURES_SUBPIXEL_ACCURACY may be more recommended with OR_USE_CONTRAST_CALC_METHOD_B

extern double LUMINOSITY_CONTRAST_FRACTION_THRESHOLD;

extern double LUMINOSITY_FRACTION_THRESHOLD;
extern double ESTIMATE_MAX_DEPTH_T_REAL;

extern double MAX_LUMINOSITY_CONTRAST;
extern double MAX_NORMAL_CONTRAST;

extern double EDGE_LUMINOSITY_CONTRAST_THRESHOLD;
extern double EDGE_LUMINOSITY_THRESHOLD;


//RT_PIXEL_MAPS...

extern int DEFAULT_CONTRAST_MAP_GENERATION_KERNEL_WIDTH;
extern int DEFAULT_CONTRAST_MAP_GENERATION_KERNEL_HEIGHT;





#endif

/*******************************************************************************
 *
 * File Name: RTglobalsDefs.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3a7a 06-June-2012
 * Description: RT specific global definitions
 *
 *******************************************************************************/


#include "RTglobalDefs.h"

//RT_SHARED_VARS...	//general contrast threshold constraints
bool OR_USE_CONTRAST_CALC_METHOD_C;		//OR_USE_CONTIGUOUS_REGION_FIND_CENTRED_FEATURES_SUBPIXEL_ACCURACY may be more recommended with OR_USE_CONTRAST_CALC_METHOD_B 
bool OR_USE_CONTRAST_CALC_METHOD_B;		//OR_USE_CONTIGUOUS_REGION_FIND_CENTRED_FEATURES_SUBPIXEL_ACCURACY may be more recommended with OR_USE_CONTRAST_CALC_METHOD_B

double LUMINOSITY_CONTRAST_FRACTION_THRESHOLD;

double LUMINOSITY_FRACTION_THRESHOLD;
double ESTIMATE_MAX_DEPTH_T_REAL;

double MAX_LUMINOSITY_CONTRAST;
double MAX_NORMAL_CONTRAST;

double EDGE_LUMINOSITY_CONTRAST_THRESHOLD;
double EDGE_LUMINOSITY_THRESHOLD;

//RT_PIXEL_MAPS...

int DEFAULT_CONTRAST_MAP_GENERATION_KERNEL_WIDTH;
int DEFAULT_CONTRAST_MAP_GENERATION_KERNEL_HEIGHT;



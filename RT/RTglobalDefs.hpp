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
 * File Name: RTglobalsDefs.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2019 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3n1c 10-August-2019
 * Description: RT specific global definitions
 * /
 *******************************************************************************/


#ifndef HEADER_RT_GLOBAL_DEFS
#define HEADER_RT_GLOBAL_DEFS

#include "SHAREDglobalDefs.hpp"

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




	/**********
	OR RAYTRACER ACCURACY RESOLUTION VARIABLES
	***********/

#define RT_CONVERT_LDR_OBJECT_SCALES_PROPERLY
#define RT_CONVERT_LDR_OBJECT_ROTATION_PROPERLY

//#define TRY_UNTESTED_SOFTWARE	//all the following are seriously untested
#ifdef TRY_UNTESTED_SOFTWARE
	#define RT_CONVERT_LDR_OBJECT_TRANSLATION_PROPERLY_VERSIONB (untested - may overcome no draw centre pixel line/column of object issue with RT_CONVERT_LDR_OBJECT_TRANSLATION_PROPERLY)
#else
	#define RT_CONVERT_LDR_OBJECT_TRANSLATION_PROPERLY
#endif



#endif

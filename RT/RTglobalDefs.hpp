 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: RTglobalsDefs.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3q1a 05-June-2022
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

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
 * File Name: RTglobalsDefs.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3c8a 13-October-2013
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

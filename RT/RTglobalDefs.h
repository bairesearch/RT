/*******************************************************************************
 *
 * File Name: RTglobalsDefs.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3a7e 12-June-2012
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


#endif

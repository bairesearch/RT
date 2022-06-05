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
 * File Name: RTviewinfo.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3p5a 14-March-2022
 * /
 *******************************************************************************/


#ifndef HEADER_RT_VIEWINFO
#define HEADER_RT_VIEWINFO

#include "RTglobalDefs.hpp"
#include "SHAREDvars.hpp"

#define TAL_FILE_HEADER_IMAGE_SIZE "IMAGESIZE"
#define TAL_FILE_HEADER_EYE "EYE"
#define TAL_FILE_HEADER_VIEWAT "VIEWAT"
#define TAL_FILE_HEADER_VIEWUP "VIEWUP"
#define TAL_FILE_HEADER_FOCAL "FOCAL"
#define TAL_FILE_HEADER_VIEWSIZE "VIEWSIZE"
#define TAL_FILE_HEADER_POINTSOURCE "POINTSOURCE"


#ifdef COMPILE_ANN_WITH_RT
	#define TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_WIDTH 320
	#define TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_HEIGHT 200
	#define TAL_FILE_HEADER_DEFAULT_EYE_X 2.5
	#define TAL_FILE_HEADER_DEFAULT_EYE_Y 2
	#define TAL_FILE_HEADER_DEFAULT_EYE_Z 7
	#define TAL_FILE_HEADER_DEFAULT_VIEWAT_X 2.5
	#define TAL_FILE_HEADER_DEFAULT_VIEWAT_Y 2
	#define TAL_FILE_HEADER_DEFAULT_VIEWAT_Z 0
	#define TAL_FILE_HEADER_DEFAULT_VIEWUP_X 0
	#define TAL_FILE_HEADER_DEFAULT_VIEWUP_Y 100
	#define TAL_FILE_HEADER_DEFAULT_VIEWUP_Z 0
	#define TAL_FILE_HEADER_DEFAULT_FOCAL 4.0
	#define TAL_FILE_HEADER_DEFAULT_VIEWSIZE_WIDTH 4
	#define TAL_FILE_HEADER_DEFAULT_VIEWSIZE_HEIGHT 3
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_X 20
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Y -10
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Z 20
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_COLOUR "white"
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE " 20 -10 20 white"
#elif defined COMPILE_RT
	#define TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_WIDTH 320
	#define TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_HEIGHT 240
	#define TAL_FILE_HEADER_DEFAULT_EYE_X 20
	#define TAL_FILE_HEADER_DEFAULT_EYE_Y 20
	#define TAL_FILE_HEADER_DEFAULT_EYE_Z 20
	#define TAL_FILE_HEADER_DEFAULT_VIEWAT_X 0
	#define TAL_FILE_HEADER_DEFAULT_VIEWAT_Y 0
	#define TAL_FILE_HEADER_DEFAULT_VIEWAT_Z 0
	#define TAL_FILE_HEADER_DEFAULT_VIEWUP_X 0
	#define TAL_FILE_HEADER_DEFAULT_VIEWUP_Y 0
	#define TAL_FILE_HEADER_DEFAULT_VIEWUP_Z 100
	#define TAL_FILE_HEADER_DEFAULT_FOCAL 4.0
	#define TAL_FILE_HEADER_DEFAULT_VIEWSIZE_WIDTH 4
	#define TAL_FILE_HEADER_DEFAULT_VIEWSIZE_HEIGHT 3
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_X 20
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Y -10
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Z 20
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_COLOUR "white"
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE " 20 -10 20 white"
#elif defined COMPILE_TH_RT
		//adjusted for raytracing a very small cube at 0,0
	#define TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_WIDTH 320	//640
	#define TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_HEIGHT 240	//480
	#define TAL_FILE_HEADER_DEFAULT_EYE_X 5
	#define TAL_FILE_HEADER_DEFAULT_EYE_Y 5
	#define TAL_FILE_HEADER_DEFAULT_EYE_Z 5
	#define TAL_FILE_HEADER_DEFAULT_VIEWAT_X 0
	#define TAL_FILE_HEADER_DEFAULT_VIEWAT_Y 0
	#define TAL_FILE_HEADER_DEFAULT_VIEWAT_Z 0
	#define TAL_FILE_HEADER_DEFAULT_VIEWUP_X 0
	#define TAL_FILE_HEADER_DEFAULT_VIEWUP_Y 0
	#define TAL_FILE_HEADER_DEFAULT_VIEWUP_Z 100
	#define TAL_FILE_HEADER_DEFAULT_FOCAL 4.0
	#define TAL_FILE_HEADER_DEFAULT_VIEWSIZE_WIDTH 4
	#define TAL_FILE_HEADER_DEFAULT_VIEWSIZE_HEIGHT 3
	//#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE " 15 20 10 white"
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE " 20 -10 20 white"
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_X 20
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Y -10
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Z 20
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_COLOUR "white"
#elif defined COMPILE_TH_ANN_WITH_LRRC
		//adjusted for raytracing a neural network
	#define TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_WIDTH 640	//320 or 640
	#define TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_HEIGHT 480	//200 or 480
	#define TAL_FILE_HEADER_DEFAULT_EYE_X 4
	#define TAL_FILE_HEADER_DEFAULT_EYE_Y 3
	#define TAL_FILE_HEADER_DEFAULT_EYE_Z 20
	#define TAL_FILE_HEADER_DEFAULT_VIEWAT_X 4
	#define TAL_FILE_HEADER_DEFAULT_VIEWAT_Y 3
	#define TAL_FILE_HEADER_DEFAULT_VIEWAT_Z 0
	#define TAL_FILE_HEADER_DEFAULT_VIEWUP_X 4
	#define TAL_FILE_HEADER_DEFAULT_VIEWUP_Y 10
	#define TAL_FILE_HEADER_DEFAULT_VIEWUP_Z 0
	#define TAL_FILE_HEADER_DEFAULT_FOCAL 6.0
	#define TAL_FILE_HEADER_DEFAULT_VIEWSIZE_WIDTH 4
	#define TAL_FILE_HEADER_DEFAULT_VIEWSIZE_HEIGHT 3
	//#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE " 15 20 10 white"
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE " 20 -10 20 white"
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_X 20
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Y -10
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Z 20
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_COLOUR "white"
#elif defined USE_ATOR_METHOD_3DOD
		//adjusted for raytracing a neural network
	#define TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_WIDTH 640	//320 or 640
	#define TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_HEIGHT 480	//200 or 480
	#define TAL_FILE_HEADER_DEFAULT_EYE_X 4
	#define TAL_FILE_HEADER_DEFAULT_EYE_Y 3
	#define TAL_FILE_HEADER_DEFAULT_EYE_Z 20
	#define TAL_FILE_HEADER_DEFAULT_VIEWAT_X 4
	#define TAL_FILE_HEADER_DEFAULT_VIEWAT_Y 3
	#define TAL_FILE_HEADER_DEFAULT_VIEWAT_Z 0
	#define TAL_FILE_HEADER_DEFAULT_VIEWUP_X 4
	#define TAL_FILE_HEADER_DEFAULT_VIEWUP_Y 10
	#define TAL_FILE_HEADER_DEFAULT_VIEWUP_Z 0
	#define TAL_FILE_HEADER_DEFAULT_FOCAL 6.0
	#define TAL_FILE_HEADER_DEFAULT_VIEWSIZE_WIDTH 4
	#define TAL_FILE_HEADER_DEFAULT_VIEWSIZE_HEIGHT 3
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE "-20 20 20 white"	//only thing used by ATOR
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_X 20
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Y -10
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Z 20
	#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_COLOUR "white"
#else
	//#define USE_VERY_LARGE_SCENE_FILE
	//#define USE_VERY_SMALL_SCENE_FILE
	#define USE_NN_SCENE_FILE
	#ifdef USE_VERY_LARGE_SCENE_FILE
		//adjust view space for a large scene
		#define TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_WIDTH 320
		#define TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_HEIGHT 240
		#define TAL_FILE_HEADER_DEFAULT_EYE_X -1700
		#define TAL_FILE_HEADER_DEFAULT_EYE_Y -180
		#define TAL_FILE_HEADER_DEFAULT_EYE_Z 180
		#define TAL_FILE_HEADER_DEFAULT_VIEWAT_X -1613
		#define TAL_FILE_HEADER_DEFAULT_VIEWAT_Y -115
		#define TAL_FILE_HEADER_DEFAULT_VIEWAT_Z 204
		#define TAL_FILE_HEADER_DEFAULT_VIEWUP_X 0
		#define TAL_FILE_HEADER_DEFAULT_VIEWUP_Y 0
		#define TAL_FILE_HEADER_DEFAULT_VIEWUP_Z 100
		#define TAL_FILE_HEADER_DEFAULT_FOCAL 4.0
		#define TAL_FILE_HEADER_DEFAULT_VIEWSIZE_WIDTH 16
		#define TAL_FILE_HEADER_DEFAULT_VIEWSIZE_HEIGHT 12
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE " -1613 -115 204 white"
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_X -1613
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Y -115
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Z 204
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_COLOUR "white"

	#elif defined USE_VERY_SMALL_SCENE_FILE
		//adjust view space for a very small scene
		#define TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_WIDTH 1024
		#define TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_HEIGHT 768
		#define TAL_FILE_HEADER_DEFAULT_EYE_X 15
		#define TAL_FILE_HEADER_DEFAULT_EYE_Y 20
		#define TAL_FILE_HEADER_DEFAULT_EYE_Z 10
		#define TAL_FILE_HEADER_DEFAULT_VIEWAT_X 0
		#define TAL_FILE_HEADER_DEFAULT_VIEWAT_Y 0
		#define TAL_FILE_HEADER_DEFAULT_VIEWAT_Z 0
		#define TAL_FILE_HEADER_DEFAULT_VIEWUP_X 0
		#define TAL_FILE_HEADER_DEFAULT_VIEWUP_Y 0
		#define TAL_FILE_HEADER_DEFAULT_VIEWUP_Z 100
		#define TAL_FILE_HEADER_DEFAULT_FOCAL 4.0
		#define TAL_FILE_HEADER_DEFAULT_VIEWSIZE_WIDTH 4
		#define TAL_FILE_HEADER_DEFAULT_VIEWSIZE_HEIGHT 3
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE " 20 -10 20 white"
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_X 20
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Y -10
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Z 20
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_COLOUR "white"

	#elif defined USE_NN_SCENE_FILE
		//adjust view space for a small scene
		#define TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_WIDTH 640
		#define TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_HEIGHT 480
		#define TAL_FILE_HEADER_DEFAULT_EYE_X 4
		#define TAL_FILE_HEADER_DEFAULT_EYE_Y 3
		#define TAL_FILE_HEADER_DEFAULT_EYE_Z 20
		#define TAL_FILE_HEADER_DEFAULT_VIEWAT_X 4
		#define TAL_FILE_HEADER_DEFAULT_VIEWAT_Y 3
		#define TAL_FILE_HEADER_DEFAULT_VIEWAT_Z 0
		#define TAL_FILE_HEADER_DEFAULT_VIEWUP_X 4
		#define TAL_FILE_HEADER_DEFAULT_VIEWUP_Y 10
		#define TAL_FILE_HEADER_DEFAULT_VIEWUP_Z 0
		#define TAL_FILE_HEADER_DEFAULT_FOCAL 4.0
		#define TAL_FILE_HEADER_DEFAULT_VIEWSIZE_WIDTH 4
		#define TAL_FILE_HEADER_DEFAULT_VIEWSIZE_HEIGHT 3
		//#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE " 15 20 10 white"
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE " 20 -10 20 white"
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_X 20
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Y -10
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Z 20
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_COLOUR "white"

	#else
		//adjust view space for a small scene
		#define TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_WIDTH 32
		#define TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_HEIGHT 24
		#define TAL_FILE_HEADER_DEFAULT_EYE_X 15
		#define TAL_FILE_HEADER_DEFAULT_EYE_Y 20
		#define TAL_FILE_HEADER_DEFAULT_EYE_Z 10
		#define TAL_FILE_HEADER_DEFAULT_VIEWAT_X 0
		#define TAL_FILE_HEADER_DEFAULT_VIEWAT_Y 0
		#define TAL_FILE_HEADER_DEFAULT_VIEWAT_Z 0
		#define TAL_FILE_HEADER_DEFAULT_VIEWUP_X 0
		#define TAL_FILE_HEADER_DEFAULT_VIEWUP_Y 0
		#define TAL_FILE_HEADER_DEFAULT_VIEWUP_Z 100
		#define TAL_FILE_HEADER_DEFAULT_FOCAL 4.0
		#define TAL_FILE_HEADER_DEFAULT_VIEWSIZE_WIDTH 4
		#define TAL_FILE_HEADER_DEFAULT_VIEWSIZE_HEIGHT 3
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE " 20 -10 20 white"
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_X 20
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Y -10
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Z 20
		#define TAL_FILE_HEADER_DEFAULT_POINTSOURCE_COLOUR "white"
	#endif
#endif


#define TAL_FILE_COLOUR_RGB_PADDER "rgb:"

#define TAL_FILE_COLOUR_BLACK "black"
#define TAL_FILE_COLOUR_BLUE "blue"
#define TAL_FILE_COLOUR_GREEN "green"
#define TAL_FILE_COLOUR_CYAN "cyan"
#define TAL_FILE_COLOUR_RED "red"
#define TAL_FILE_COLOUR_MAGENTA "magenta"
#define TAL_FILE_COLOUR_BROWN "brown"
#define TAL_FILE_COLOUR_LIGHTGREY "lightgrey"
#define TAL_FILE_COLOUR_DARKGREY "darkgrey"
#define TAL_FILE_COLOUR_YELLOW "yellow"
#define TAL_FILE_COLOUR_WHITE "white"
#define TAL_FILE_COLOUR_ORANGE "orange"
#define TAL_FILE_COLOUR_PURPLE "purple"

#define TAL_FILE_COLOUR_BLACK_RGB "000000"
#define TAL_FILE_COLOUR_BLUE_RGB "0000C0"
#define TAL_FILE_COLOUR_GREEN_RGB "006000"
#define TAL_FILE_COLOUR_CYAN_RGB "00F0F0"
#define TAL_FILE_COLOUR_RED_RGB "F00000"
#define TAL_FILE_COLOUR_MAGENTA_RGB "FF00FF"
#define TAL_FILE_COLOUR_BROWN_RGB "C06000"
#define TAL_FILE_COLOUR_LIGHTGREY_RGB "C0C0C0"
#define TAL_FILE_COLOUR_DARKGREY_RGB "606060"
#define TAL_FILE_COLOUR_YELLOW_RGB "FFFF00"
#define TAL_FILE_COLOUR_WHITE_RGB "FFFFFF"
#define TAL_FILE_COLOUR_ORANGE_RGB "FF0600"
#define TAL_FILE_COLOUR_PURPLE_RGB "6000FF"

#define TAL_FILE_TYPE_BRICK "BRICK"
#define TAL_FILE_TYPE_PLATE "PLATE"
#define TAL_FILE_TYPE_TILE "TILE"
#define TAL_FILE_TYPE_DECAL "DECAL"
#define TAL_FILE_TYPE_BASEPLATE "BASEPLATE"
#define TAL_FILE_TYPE_PRIM_QUAD "PRIM_QUAD"
#define TAL_FILE_TYPE_PRIM_TRI "PRIM_TRI"
#define TAL_FILE_TYPE_SPHERE "SPHERE"
#define TAL_FILE_TYPE_CYLINDER "CYLINDER"
#define TAL_FILE_TYPE_RECT_PRISM "RECT_PRISM"
#define TAL_FILE_TYPE_PRIM_LINE "PRIM_LINE"
#define TAL_FILE_TYPE_CIRCLE "TAL_FILE_TYPE_CIRCLE"



#define TAL_FILE_REF_WIDTH "width "
#define TAL_FILE_REF_LENGTH " length "
#define TAL_FILE_REF_HEIGHT " height "

#define TAL_FILE_REF_END "end"

/*
 * RTviewInfo
 * View frame parameters
 */

class RTviewInfo
{
public:

	RTviewInfo(void);
	~RTviewInfo(void);

	int imageWidth;			//IMAGESIZE
	int imageHeight;		//IMAGESIZE

	vec eye;			//EYE
	vec viewAt;			//VIEWAT
	vec viewUp;			//VIEWUP

	double focalLength;		//FOCAL

	double viewWidth, viewHeight;	//VIEWSIZE

	double depthScale;		//added by RBB 30 Nov 09 [ mapping between depthmap bits and pov (defines resolution and maximum depth range/coverage of depth map)]
	string objectName;		//not currently required to be used, as object name is passed explicitly between functions
	string imageExtensionName;	//eg .png
	string depthExtensionName;	//eg .depth.png

	double xOffset;
	double yOffset;
};



#endif

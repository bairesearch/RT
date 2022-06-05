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
 * File Name: LDjpeg.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2021 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3p4c 07-August-2021
 * /
 *******************************************************************************/


#ifndef HEADER_LD_JPEG
#define HEADER_LD_JPEG

#include "SHAREDglobalDefs.hpp"
#ifdef USE_ATOR
	#include "ATORglobalDefs.hpp"
#include "SHAREDvars.hpp"
#include "jpeglib.h"
#include "jmemsys.h"
#endif

class LDjpegClass
{
	private: SHAREDvarsClass SHAREDvars;
	#ifdef ATOR_VERBOSE_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_COMPARISON_DCT_TABLES_TO_HTML
	public: void setPointerToDCTtableHTMLoutputString(string* pointer);
	#endif

	public: int readVerySmallHighlyCompressedJPEGfileAndStoreDCTcoefficients(const string filename, schar dctCoeffArrayY[], schar dctCoeffArrayYcr[], schar dctCoeffArrayYcb[], const int dctCoeffArrayHeight, const int dctCoeffArrayWidth, const bool printOutput);
};

#endif

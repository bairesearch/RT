 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: LDjpeg.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3q1a 05-June-2022
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

/*******************************************************************************
 *
 * File Name: LDjpeg.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2010 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3a6b 30-Apr-2012
 *
 *******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;

#include "SHAREDglobalDefs.h"


#ifdef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_COMPARISON_DCT_TABLES_TO_HTML
void setpointerToDCTTableHTMLOutputString(string * pointer);
#endif

int readVerySmallHighlyCompressedJPEGfileAndStoreDCTcoefficients (char * filename, signed char dctCoeffArrayY[], signed char dctCoeffArrayYCr[], signed char dctCoeffArrayYCb[], int dctCoeffArrayHeight, int dctCoeffArrayWidth, bool storeDataInArrays);



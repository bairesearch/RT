/*******************************************************************************
 *
 * File Name: SHAREDvars.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2010 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3a6b 30-Apr-2012
 *
 *******************************************************************************/

#ifndef HEADER_SHARED_VARS
#define HEADER_SHARED_VARS

#include "SHAREDglobalDefs.h"



#define MAP_VALUE_OUT_OF_RANGE (8888888.0)


#define TRAIN (1)
#define TEST (0)
#define TRAIN_AND_TEST (2)

#define RT_RAYTRACE_NO_HIT_DEPTH_T (10000000.0)
#define RT_RAYTRACE_NO_HIT_POINT_X (0.0)
#define RT_RAYTRACE_NO_HIT_POINT_Y (0.0)
#define RT_RAYTRACE_NO_HIT_POINT_Z (0.0)






#define TRUE (1)
#define FALSE (0)

#define REALLY_FAR_AWAY (99999999999.9)
#define REALLY_LARGE_DOUBLE (1000000.0)
#define REALLY_LARGE_INT (1000000)
#define REALLY_SMALL_DOUBLE (-1000000.0)

#define OR_METHOD2DOD_DIMENSIONS (2)
#define OR_METHOD3DOD_DIMENSIONS (3)

/* common definitions */
typedef struct { unsigned char r, g, b; } colour;
typedef struct { double x, y, z; } vec;
typedef struct { vec a; vec b; vec c; } mat;

#ifdef COMPILE_OLC
	#define DOUBLE_MIN_PRECISION 0.005
#else
	#define DOUBLE_MIN_PRECISION 0.00001
#endif

long getTimeAsLong();

bool compareDoubles(double a, double b);
bool compareDoublesArbitraryError(double a, double b, double error);

int maxInt(int a, int b);	//should be turned into a macro instead
int minInt(int a, int b);	//should be turned into a macro instead

double minDouble(double a, double b);	//should be turned into a macro instead
double maxDouble(double a, double b);	//should be turned into a macro instead

double absDouble(double val);

int exists_argument(int argc,char **argv,char *keystr);
float get_float_argument(int argc,char **argv,char *keystr);
char *get_char_argument(int argc,char **argv,char *keystr);

void copyColours(colour * colToModify, colour * colToCopy);

#endif

/*******************************************************************************
 *
 * File Name: RToperations.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3a8a 14-June-2012
 *
 *******************************************************************************/


#ifndef HEADER_RT_OPERATIONS
#define HEADER_RT_OPERATIONS

//#define MISS (-1)
#define LINE_INTERSECTION_BOUNDARY_ERROR_ALLOWED (0.01)


/*
RToperations.h

@author Richard Baxter
@version 9-10-03 1:54pm

[Assignment 3 MULT3004]

all Mathematical functions (Vector/Matrix operations) required by the raytracer
*/

#include "SHAREDvars.h"
#include "SHAREDvector.h"
//#include "math.h"



	/*4x4 matrix manipulation methods*/

typedef struct { double x; double y; double z; double w;} advanced_vec;

typedef struct { advanced_vec a; advanced_vec b; advanced_vec c; advanced_vec d;} advanced_mat;


void makeAdvancedMatrix(advanced_mat* matxAdv, mat* matx, int type);
void multAdvancedMatrix(advanced_mat* matxAdv1, advanced_mat* matxAdv2, advanced_mat* matxAdv);
void createIdentityMatrixAdvanced(advanced_mat* matx);
void createInverseTranslationMatrix(double xpos, double ypos, double zpos, advanced_mat* matx);
void createTranslationMatrix(double xpos, double ypos, double zpos, advanced_mat* matx);
void createScaleMatrix(double width, double length, double height, advanced_mat* matx);
void createInverseScaleMatrix(double width, double length, double height, advanced_mat* matx);
void createRotationxMatrix(double rotation, advanced_mat* matx);
void createInverseRotationxMatrix(double rotation, advanced_mat* matx);
void createRotationyMatrix(double rotation, advanced_mat* matx);
void createInverseRotationyMatrix(double rotation, advanced_mat* matx);
void createRotationzMatrix(double rotation, advanced_mat* matx);
void createInverseRotationzMatrix(double rotation, advanced_mat* matx);
void invertAdvancedMatrix(advanced_mat* matx);
void transposeAdvancedMatrix(advanced_mat* matx);
void multAdvancedMatrixByVector(advanced_vec* vecAdv1, advanced_mat* matxAdv1, advanced_vec* vecAdv);
double toRadians(double degrees);
void toAdvancedVector(vec* vec, int type, advanced_vec* vecAdv);
void fromAdvancedVector(advanced_vec* vecAdv, vec* vec);
void createAdvancedVector(advanced_vec* vec);



double findSmallestValue(double val1, double val2, double val3);
double findGreatestValue(double val1, double val2, double val3);
	/*finds the smallest/largest value of 3 given scalars*/

int findPositionOfSmallestValueAdvanced(double *array, unsigned int size);
int findPositionOfGreatestValueAdvanced(double *array, unsigned int size);

int findIntersectLineWithTri(vec * pt1, vec * pt2, vec * pt3, vec * linept1, vec * linept2, vec * pt_int, vec * norm, double * t);
	int checkSameClockDir(vec * pt1, vec * pt2, vec * pt3, vec * norm);
int findIntersectLineWithLine(vec * linept1, vec * linept2, vec * povpt1, vec * povpt2, vec * pt_int, vec * norm, double * t);
	bool findIntersectLineWithLine2D(vec* povpt1, vec* povpt2, vec* linept1, vec* linept2, vec * pt_int);
int findIntersectLineWithQuad(vec * pt1, vec * pt2, vec * pt3, vec * pt4, vec * linept1, vec * linept2, vec * pt_int, vec * norm, double * t);






double findSmallestValueAdvanced(double val1, double val2);
double findSmallestValue(double val1, double val2);
double findGreatestValueAdvanced(double val1, double val2);
double findGreatestValue(double val1, double val2);

int findPositionOfSmallestValueWhichHits(double *array, int *hitsArray, unsigned int size);
int findPositionOfGreatestValueWhichHits(double *array, int *hitsArray, unsigned int size);

#endif

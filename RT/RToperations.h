/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation. The use of
 * intermediary programs or interfaces including file i/o is considered
 * remote network interaction. This does not imply such arrangements
 * do not constitute derivative works.
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
 * File Name: RToperations.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3f3a 10-July-2015
 *
 *******************************************************************************/


#ifndef HEADER_RT_OPERATIONS
#define HEADER_RT_OPERATIONS

//#define MISS (-1)
#define LINE_INTERSECTION_BOUNDARY_ERROR_ALLOWED (0.01)


#include "SHAREDvars.h"
#include "SHAREDvector.h"
//#include "math.h"

	/*4x4 matrix manipulation methods*/

typedef struct { double x; double y; double z; double w;} advancedVec;

typedef struct { advancedVec a; advancedVec b; advancedVec c; advancedVec d;} advancedMat;


void makeAdvancedMatrix(advancedMat* matxAdv, mat* matx, int type);
void multAdvancedMatrix(advancedMat* matxAdv1, advancedMat* matxAdv2, advancedMat* matxAdv);
void createIdentityMatrixAdvanced(advancedMat* matx);
void createInverseTranslationMatrix(double xpos, double ypos, double zpos, advancedMat* matx);
void createTranslationMatrix(double xpos, double ypos, double zpos, advancedMat* matx);
void createScaleMatrix(double width, double length, double height, advancedMat* matx);
void createInverseScaleMatrix(double width, double length, double height, advancedMat* matx);
void createRotationxMatrix(double rotation, advancedMat* matx);
void createInverseRotationxMatrix(double rotation, advancedMat* matx);
void createRotationyMatrix(double rotation, advancedMat* matx);
void createInverseRotationyMatrix(double rotation, advancedMat* matx);
void createRotationzMatrix(double rotation, advancedMat* matx);
void createInverseRotationzMatrix(double rotation, advancedMat* matx);
void invertAdvancedMatrix(advancedMat* matx);
void transposeAdvancedMatrix(advancedMat* matx);
void multAdvancedMatrixByVector(advancedVec* vecAdv1, advancedMat* matxAdv1, advancedVec* vecAdv);
double toRadians(double degrees);
void toAdvancedVector(vec* vec, int type, advancedVec* vecAdv);
void fromAdvancedVector(advancedVec* vecAdv, vec* vec);
void createAdvancedVector(advancedVec* vec);


double findSmallestValue(double val1, double val2, double val3);
double findGreatestValue(double val1, double val2, double val3);
	/*finds the smallest/largest value of 3 given scalars*/

int findPositionOfSmallestValueAdvanced(double* array, unsigned int size);
int findPositionOfGreatestValueAdvanced(double* array, unsigned int size);

int findIntersectLineWithTri(vec* pt1, vec* pt2, vec* pt3, vec* linept1, vec* linept2, vec* pt_int, vec* norm, double* t);
	int checkSameClockDir(vec* pt1, vec* pt2, vec* pt3, vec* norm);
int findIntersectLineWithLine(vec* linept1, vec* linept2, vec* povpt1, vec* povpt2, vec* pt_int, vec* norm, double* t);
	bool findIntersectLineWithLine2D(vec* povpt1, vec* povpt2, vec* linept1, vec* linept2, vec* pt_int);
int findIntersectLineWithQuad(vec* pt1, vec* pt2, vec* pt3, vec* pt4, vec* linept1, vec* linept2, vec* pt_int, vec* norm, double* t);



double findSmallestValueAdvanced(double val1, double val2);
double findSmallestValue(double val1, double val2);
double findGreatestValueAdvanced(double val1, double val2);
double findGreatestValue(double val1, double val2);

int findPositionOfSmallestValueWhichHits(double* array, int* hitsArray, unsigned int size);
int findPositionOfGreatestValueWhichHits(double* array, int* hitsArray, unsigned int size);

#endif

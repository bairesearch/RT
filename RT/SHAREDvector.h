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
 * File Name: SHAREDvector.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3e7d 27-January-2015
 *
 *******************************************************************************/


#ifndef HEADER_SHARED_VECTOR
#define HEADER_SHARED_VECTOR

#include "SHAREDvars.h"
#include "SHAREDglobalDefs.h"		//needed so as to know if USE_RT is defined

#ifdef USE_RT
#define RELAXED_DOUBLE_MIN_PRECISION 0.03
#endif

#define PI (3.14159265)
#define ZERO 0.0
#define ONE 1.0
#define NOT_FOUND -1

#define AXIS_X (1)
#define AXIS_Y (2)
#define AXIS_Z (3)

void initialiseVector(vec* vect);

void calculateNormalOfTri(vec* pt1, vec* pt2, vec* pt3, vec* normal);

void calculateRotationVectorFromDeformationMatrix(mat* deformationMatrix, vec* rotationVector);
void generateLookAtRotationMatrix(vec* at, vec* eye, vec* up, mat* rotationMatrix);
void transposeMatrix(mat* matx);

double calculateInteriorAngleOfAPolygonVertex(vec* pt1Centre, vec* pt2, vec* pt3);

double calculateAreaOfTriangle3D(vec* pt1, vec* pt2, vec* pt3);
double calculateAreaOfTriangle(vec* pt1, vec* pt2, vec* pt3);
	double calculateDeterminant3By3(mat* matrix);

double absDouble2(double val);


void createRotationMatrix2D(mat* matrix, double rotation);
void createXAxisShearMatrix2D(mat* matrix, double shear);
double calculateAngleBetweenVectors2D(vec* vect1, vec* vect2);
void createScaleMatrix2D(mat* matrix, double scaleFactor);
void createYAxisScaleMatrix2D(mat* matrix, double scaleFactor);

void calculateMidPointBetweenTwoPoints(vec* pt1, vec* pt2, vec* midPoint);
	void calculateMidDiffBetweenTwoPoints(vec* pt1, vec* pt2, vec* midDiff);
void calculateNormal(vec* pt1, vec* pt2, vec* normal);

	//from RToperations.h

void subtractVectorsRT(vec* vect1, vec* vect2, vec* vect);
	/*vect = vect1 - vect2*/

void addVectorsRT(vec* vect1, vec* vect2, vec* vect);
	/*adds 2 vectors together*/

void multiplyVectorByScalarRT(vec* vect1, double multiplyer, vec* vect);
	/*multiply a vector by a scalar*/

void divideVectorByScalarRT(vec* vect1, double divisor, vec* vect);

void copyVectorRT(vec* vecNew, vec* vecToCopy);

void normaliseVectorRT(vec* vect1, vec* vect);


void normaliseVector(vec* vect1);
	/*normalises a vector*/

void negativeVector(vec* vect1, vec* vect);
	/*finds the negative of a vector*/

double dotProduct(vec* vect1, vec* vect2);
	/*finds the dot product of 2 vectors*/

void crossProduct(vec* vect1, vec* vect2, vec* vect);
	/*vect = vect1 x vect2; finds the cross product of 2 vectors*/

void makeMatrix(vec* vect1, vec* vect2, vec* vect3, mat* matx);
	/*creates a 3x3 matrix from 3 vectors*/

void multMatrixByVector(mat* matx, vec* vect1, vec* vect);
	/*multiplies a matrix by a vector*/

void createVector(vec* vec);

void createIdentityMatrixRT(mat* matx);

double findMagnitudeOfVector(vec* vect1);








bool compareVectors(vec* vecA, vec* vecB);
bool compareVectorsArbitraryError(vec* vecA, vec* vecB, double error);

bool compareMatricies(mat* matA, mat* matB);
void copyVectors(vec* vecNew, vec* vecToCopy);
void copyMatricies(mat* matNew, mat* matToCopy);
void multiplyVectorByMatrix(vec* vecNew, vec* vecToMultiply, mat* matrix);

	//semi shared
void multiplyMatricies(mat* matNew, mat* mat1, mat* mat2);
void subtractVectors(vec* vecNew, vec* a, vec* b);
void addVectors(vec* vecNew, vec* a, vec* b);
void multiplyVectorByScalar(vec* vec, double scalar);
void createIdentityMatrix(mat* matrix);

double calculateTheDistanceBetweenTwoPointsXYOnly(vec* positionOfUnit1, vec* positionOfUnit2);
double calculateTheDistanceBetweenTwoPoints(vec* positionOfUnit1, vec* positionOfUnit2);
	double calculateTheDistanceBetweenTwoPoints(double positionXOfUnit1, double positionXOfUnit2, double positionYOfUnit1, double positionYOfUnit2, double positionZOfUnit1, double positionZOfUnit2);
	double calculateTheDistanceBetweenTwoPoints2D(double positionXOfUnit1, double positionXOfUnit2, double positionYOfUnit1, double positionYOfUnit2);


void createRotatationMatrix(mat* matrix, int rotationAxis, double rotationRadians);
void createRotationMatrixX(mat* matrix, double rotation);
void createRotationMatrixY(mat* matrix, double rotation);
void createRotationMatrixZ(mat* matrix, double rotation);
double convertDegreesToRadian(double degrees);
double convertRadianToDegrees(double radian);
//void rotateMatrix(mat* matrix, char rotationAxis, double rotationDegrees);
void copyMatrixTwoIntoMatrixOne(mat* mat1, mat* mat2);
void scaleMatrix(mat* matrix, double scaleFactor);

double calculateAngleOfVector3D(vec* vect1, int axis);



//From OLCoperations.h

void find2DintersectionPoint(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy, double* intersectionX, double* intersectionY, bool* interceptionFound, bool* interceptionPointFound);	//NB an interception may be a line and not a point
	double calcDistanceBetweenTwoPoints2D(double x1, double y1, double x2, double y2);
	bool solve2DlineEquationWithTwoPoints(double x1, double y1, double x2, double y2, double* m, double* i);
	bool determineIfPointLiesOnLine2D(double x1, double y1, double x2, double y2, double x3, double y3);
	bool find2DintersectionPointOfTwoLines(double m1, double i1, double m2, double i2, double* xIntersection, double* yIntersection);
	bool twoPointsAreTheSame2D(double x1, double y1, double x2, double y2);
	bool determineIfPointLiesOnAKnownLine2D(double m1, double i1, double x3, double y3);

#ifdef USE_RT
	//required for raytracing operations
bool compareDoublesRelaxed(double a, double b);
bool determineIfPointLiesOnAKnownLine2Drelaxed(double m1, double i1, double x3, double y3);
bool twoPointsAreTheSame2Drelaxed(double x1, double y1, double x2, double y2);
#endif

#endif





 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: RTraytracer.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3q1a 05-June-2022
 * Description: contains methods to raytrace a primitive through a given point (x, y)
 *              on the screen with the given RTsceneInfo structure and accompanying
 *              perspective information.
 * /
 *******************************************************************************/


#ifndef HEADER_RT_RAYTRACER
#define HEADER_RT_RAYTRACER


#include "RTparser.hpp"		/*required for view info definitions*/
#include "RToperations.hpp"	/*required for vector/colour and matrix definitions*/
#include "RTpixelMaps.hpp"	//for max depth val


//#define RT_T_TRANSFORM_TEST	//TEMP

#define PRIM_LINE_CALC_QUAD_REDUCTION_WIDTH (RELAXED_DOUBLE_MIN_PRECISION)

#define RT_METHOD2


class RTsceneInfo
{
public:

	RTsceneInfo(void);
	~RTsceneInfo(void);

	advancedMat standardMatrix;
	advancedMat reverseMatrix;
	RTpieceInfo pi;
	RTdimensionsInfo di;
	double tIn, tOut;		//temporary var.
	vec p, n;			//temporary vars. p, p1, normal to face

	RTsceneInfo* nextScene;
};


class RTraytracerClass
{
	private: RToperationsClass RToperations;
	private: SHAREDvectorClass SHAREDvector;
	public: void rayTrace(const RTviewInfo* vi, RTsceneInfo* si, mat* tildaMat, vec* uvn);
	/*ray traces an object*/
	private: void calculateCylinder(vec* p0, vec* p1, double* tInOut, vec* norm, advancedMat* finalReverseMatrix, advancedMat* relevantFinalReverseMatrix);
	private: void calculateCube(vec* p0, vec* p1, double* tInOut, vec* norm, advancedMat* finalReverseMatrix, advancedMat* relevantFinalReverseMatrix);
	private: void calculateSphere(vec* p0, vec* p1, double* tInOut, vec* norm, advancedMat* finalReverseMatrix, advancedMat* relevantFinalReverseMatrix);
	private: void calculatePrimQuad(vec* p0, vec* p1, double* tInOut, const RTpieceInfo* pi, vec* norm, advancedMat* finalReverseMatrix, advancedMat* relevantFinalReverseMatrix);
	private: void calculatePrimTri(vec* p0, vec* p1, double* tInOut, const RTpieceInfo* pi, vec* norm, advancedMat* finalReverseMatrix, advancedMat* relevantFinalReverseMatrix);
	private: void calculatePrimLine(vec* p0, vec* p1, double* tInOut, const RTpieceInfo* pi, const vec* norm, advancedMat* finalReverseMatrix, advancedMat* relevantFinalReverseMatrix);
	private: void calculatePrimLineNEW(vec* p0, vec* p1, double* tInOut, RTpieceInfo* pi, vec* norm, advancedMat* finalReverseMatrix, advancedMat* relevantFinalReverseMatrix);

#ifndef RT_T_TRANSFORM_TEST
	private: void drawPoint(RTsceneInfo* si, advancedMat* reverseMatrix, double tInDash, double tOutDash, vec* p0Dash, vec* p1Dash, vec* norm);
#else
	//private: void drawPointTest(RTsceneInfo* si, advancedMat* reverseMatrix, double tInDash, double tOutDash, vec* p0Dash, vec* p1Dash, vec* norm, vec* p0, vec* p1);
#endif

	private: void drawPointNoLighting(RTsceneInfo* si, const advancedMat* reverseMatrix, double tIn, double tOut, const vec* p0, const vec* p1, const vec* norm);

	public: void calculatePointUsingTInWorld(double tInWorld, vec* p0, vec* p1, RTviewInfo* vi, vec* p, vec* uvn);
};


#endif


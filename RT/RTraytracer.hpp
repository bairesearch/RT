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
 * File Name: RTraytracer.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2020 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3o1a 05-November-2020
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
//void drawPointTest(RTsceneInfo* si, advancedMat* reverseMatrix, double tInDash, double tOutDash, vec* p0Dash, vec* p1Dash, vec* norm, vec* p0, vec* p1);
#endif

	private: void drawPointNoLighting(RTsceneInfo* si, const advancedMat* reverseMatrix, double tIn, double tOut, const vec* p0, const vec* p1, const vec* norm);

	public: void calculatePointUsingTInWorld(double tInWorld, vec* p0, vec* p1, RTviewInfo* vi, vec* p, vec* uvn);
};


#endif


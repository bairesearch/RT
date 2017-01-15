/*******************************************************************************
 *
 * File Name: RTraytracer.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2010 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3a5g 01-Nov-2011
 *
 *******************************************************************************/

#ifndef HEADER_RT_RAYTRACER
#define HEADER_RT_RAYTRACER




#include "RTparser.h"		/*required for view info definitions*/
#include "RToperations.h"	/*required for vector/colour and matrix definitions*/


//#define RT_T_TRANSFORM_TEST	//TEMP

#define PRIM_LINE_CALC_QUAD_REDUCTION_WIDTH (RELAXED_DOUBLE_MIN_PRECISION)

#define RT_METHOD2


class scene_info
{
public:

	scene_info(void);
	~scene_info(void);

	advanced_mat standardMatrix;
	advanced_mat reverseMatrix;
	piece_info pi;
	dimensions_info di;
	double tIn, tOut;		//temporary var.
	vec p, n;			//temporary vars. p, p1, normal to face

	scene_info *nextScene;
};

/*
typedef struct scene scene_info;
struct scene
{
	advanced_mat standardMatrix;
	advanced_mat reverseMatrix;
	piece_info pi;
	dimensions_info di;
	double tIn, tOut;		//temporary var.
	vec p, n;			//temporary vars. p, p1, normal to face
	scene_info *nextScene;
};
*/

void rayTrace(view_info* vi, scene_info* si, mat* tildaMat, vec* uvn);
	/*ray traces an object*/
void calculateCylinder(vec* p0, vec* p1, double* tInOut, vec * norm, advanced_mat * finalReverseMatrix, advanced_mat * relevantFinalReverseMatrix);
void calculateCube(vec* p0, vec* p1, double* tInOut, vec * norm, advanced_mat * finalReverseMatrix, advanced_mat * relevantFinalReverseMatrix);
void calculateSphere(vec* p0, vec* p1, double* tInOut, vec * norm, advanced_mat * finalReverseMatrix, advanced_mat * relevantFinalReverseMatrix);
void calculatePrimQuad(vec* p0, vec* p1, double* tInOut, piece_info * pi, vec * norm, advanced_mat * finalReverseMatrix, advanced_mat * relevantFinalReverseMatrix);
void calculatePrimTri(vec* p0, vec* p1, double* tInOut, piece_info * pi, vec * norm, advanced_mat * finalReverseMatrix, advanced_mat * relevantFinalReverseMatrix);
void calculatePrimLine(vec* p0, vec* p1, double* tInOut, piece_info * pi, vec * norm, advanced_mat * finalReverseMatrix, advanced_mat * relevantFinalReverseMatrix);
void calculatePrimLineNEW(vec* p0, vec* p1, double* tInOut, piece_info * pi, vec * norm, advanced_mat * finalReverseMatrix, advanced_mat * relevantFinalReverseMatrix);

#ifndef RT_T_TRANSFORM_TEST
void drawPoint(scene_info* si, advanced_mat* reverseMatrix, double tInDash, double tOutDash, vec* p0dash, vec* p1dash, vec * norm);
#else
void drawPoint(scene_info* si, advanced_mat* reverseMatrix, double tInDash, double tOutDash, vec* p0dash, vec* p1dash, vec * norm, vec* p0, vec* p1);
#endif

void drawPointNoLighting(scene_info* si, advanced_mat* reverseMatrix, double tIn, double tOut, vec* p0, vec* p1, vec * norm);

void calculatePointUsingTInWorld(double tInWorld, vec * p0, vec * p1, view_info * vi, vec * p, vec * uvn);


//void calculateCube(scene_info* si, vec* p0, vec* p1, advanced_mat *standardMatrix, advanced_mat *reverseMatrix);
//void calculateCylinder(scene_info* si, vec* p0, vec* p1, advanced_mat *standardMatrix, advanced_mat *reverseMatrix);
//void calculateSphere(scene_info* si, vec* p0, vec* p1, advanced_mat *standardMatrix, advanced_mat *reverseMatrix);


#endif


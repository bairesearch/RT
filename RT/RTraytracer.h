/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation. The use of
 * intermediary programs or interfaces including file i/o is considered
 * remote network interaction.
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
 * File Name: RTraytracer.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3d3a 24-May-2014
 * Description: contains methods to raytrace a primitive through a given point (x, y)
 *              on the screen with the given sceneInfo structure and accompanying
 *              perspective information.
 *
 *******************************************************************************/

#ifndef HEADER_RT_RAYTRACER
#define HEADER_RT_RAYTRACER




#include "RTparser.h"		/*required for view info definitions*/
#include "RToperations.h"	/*required for vector/colour and matrix definitions*/


//#define RT_T_TRANSFORM_TEST	//TEMP

#define PRIM_LINE_CALC_QUAD_REDUCTION_WIDTH (RELAXED_DOUBLE_MIN_PRECISION)

#define RT_METHOD2


class sceneInfo
{
public:

	sceneInfo(void);
	~sceneInfo(void);

	advancedMat standardMatrix;
	advancedMat reverseMatrix;
	pieceInfo pi;
	dimensionsInfo di;
	double tIn, tOut;		//temporary var.
	vec p, n;			//temporary vars. p, p1, normal to face

	sceneInfo *nextScene;
};


void rayTrace(ViewInfo* vi, sceneInfo* si, mat* tildaMat, vec* uvn);
	/*ray traces an object*/
void calculateCylinder(vec* p0, vec* p1, double* tInOut, vec * norm, advancedMat * finalReverseMatrix, advancedMat * relevantFinalReverseMatrix);
void calculateCube(vec* p0, vec* p1, double* tInOut, vec * norm, advancedMat * finalReverseMatrix, advancedMat * relevantFinalReverseMatrix);
void calculateSphere(vec* p0, vec* p1, double* tInOut, vec * norm, advancedMat * finalReverseMatrix, advancedMat * relevantFinalReverseMatrix);
void calculatePrimQuad(vec* p0, vec* p1, double* tInOut, pieceInfo * pi, vec * norm, advancedMat * finalReverseMatrix, advancedMat * relevantFinalReverseMatrix);
void calculatePrimTri(vec* p0, vec* p1, double* tInOut, pieceInfo * pi, vec * norm, advancedMat * finalReverseMatrix, advancedMat * relevantFinalReverseMatrix);
void calculatePrimLine(vec* p0, vec* p1, double* tInOut, pieceInfo * pi, vec * norm, advancedMat * finalReverseMatrix, advancedMat * relevantFinalReverseMatrix);
void calculatePrimLineNEW(vec* p0, vec* p1, double* tInOut, pieceInfo * pi, vec * norm, advancedMat * finalReverseMatrix, advancedMat * relevantFinalReverseMatrix);

#ifndef RT_T_TRANSFORM_TEST
void drawPoint(sceneInfo* si, advancedMat* reverseMatrix, double tInDash, double tOutDash, vec* p0Dash, vec* p1Dash, vec * norm);
#else
void drawPoint(sceneInfo* si, advancedMat* reverseMatrix, double tInDash, double tOutDash, vec* p0Dash, vec* p1Dash, vec * norm, vec* p0, vec* p1);
#endif

void drawPointNoLighting(sceneInfo* si, advancedMat* reverseMatrix, double tIn, double tOut, vec* p0, vec* p1, vec * norm);

void calculatePointUsingTInWorld(double tInWorld, vec * p0, vec * p1, ViewInfo * vi, vec * p, vec * uvn);


#endif


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
 * File Name: LDopengl.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3e2b 29-August-2014
 *
 *******************************************************************************/



#ifndef HEADER_LD_OPENGL
#define HEADER_LD_OPENGL

#include "SHAREDglobalDefs.h"
#include "LDreferenceClass.h"

#define USE_OPENGL_PREDEFINED_OD_MATRIX_OPERATIONS		//this is used by ORmethod.cpp/ORmethod2DOD.cpp/ORmethod3DOD.cpp also
#define USE_OPENGL_PREDEFINED_OD_MATRIX_OPERATIONS_ADV		//this is used by ORmethod.cpp/ORmethod2DOD.cpp/ORmethod3DOD.cpp also

#define RGB_RED (0)
#define RGB_GREEN (1)
#define RGB_BLUE (2)
#define RGB_NUM (3)

#ifdef USE_CS
	//white
	#define OPEN_GL_BACKGROUND_COLOUR_R (1.0)
	#define OPEN_GL_BACKGROUND_COLOUR_G (1.0)
	#define OPEN_GL_BACKGROUND_COLOUR_B (1.0)
#elif defined USE_GIA
	//white
	#define OPEN_GL_BACKGROUND_COLOUR_R (1.0)
	#define OPEN_GL_BACKGROUND_COLOUR_G (1.0)
	#define OPEN_GL_BACKGROUND_COLOUR_B (1.0)
	#define OR_PRINT_ALGORITHM_AND_TIME_DETAILS (0)
	#define OR_PRINT_ALGORITHM_AND_TIME_DETAILS_ALL (0)
	#define OR_PRINT_ALGORITHM_PROGRESS (0)
	#define OR_GENERATE_IMAGE_COMPARITOR_RESULTS_NO_EXPLICIT_CONFIDENTIAL_WARNINGS (0)

#elif defined USE_OR
	//black? magenta?
	#define OPEN_GL_BACKGROUND_COLOUR_R (0.0)		//255 (ifdef OR_METHOD_USE_SPECIFIC_BG_COLOUR)
	#define OPEN_GL_BACKGROUND_COLOUR_G (0.0)		//0 (ifdef OR_METHOD_USE_SPECIFIC_BG_COLOUR)
	#define OPEN_GL_BACKGROUND_COLOUR_B (0.0)		//255 (ifdef OR_METHOD_USE_SPECIFIC_BG_COLOUR)
#else
	//black
	#define OPEN_GL_BACKGROUND_COLOUR_R (0.0)
	#define OPEN_GL_BACKGROUND_COLOUR_G (0.0)
	#define OPEN_GL_BACKGROUND_COLOUR_B (0.0)
#endif





#define OR_METHOD2DOD_DIMENSIONS (2)
#define OR_METHOD3DOD_DIMENSIONS (3)

#define PI (3.14159265)

extern mat opengl2DmultiplicationMatrix;
extern double opengl2DmatrixTransformation1ScaleFactor;
extern double opengl2DmatrixTransformation2iRotationFactor;
extern double opengl2DmatrixTransformation2iiRotationFactor;
extern double opengl2DmatrixTransformation3aScaleFactor;
extern double opengl2DmatrixTransformation4aShearFactor;
extern double opengl2DmatrixTransformation5aTranslationFactorX;
extern double opengl2DmatrixTransformation5aTranslationFactorY;

extern mat opengl3DmultiplicationMatrix;
extern double opengl3DmatrixTransformation1aXRotationFactor;
extern double opengl3DmatrixTransformation1bYRotationFactor;
extern double opengl3DmatrixTransformation2iZRotationFactor;
extern double opengl3DmatrixTransformation2iiZRotationFactor;
extern double opengl3DmatrixTransformation3TranslationFactorX;
extern double opengl3DmatrixTransformation3TranslationFactorY;
extern double opengl3DmatrixTransformation3TranslationFactorZ;

int initiateOpenGL(int width, int height, int windowPositionX, int windowPositionY, bool confidentialWarnings);
//void setViewPort(int width, int height, double xCentre, double yCentre);	//optional
void setViewPort2Dortho(double left, double right, double bottom, double top);
void setViewPort3D(vec * eyeFacingPoly, vec * viewAtFacingPoly, vec * viewUpFacingPoly, vec * viewPortWidthHeightDepth);
void setViewPort3Ddynamic(vec * eyeFacingPoly, vec * viewAtFacingPoly, vec * viewUpFacingPoly, vec * viewPortWidthHeightDepth);
double maxDouble2(double float1, double float2);
void setViewPort3Dbasic();
void setViewPort3Dortho(double left, double right, double bottom, double top, double back, double forward);


void drawPrimitivesReferenceListToOpenGLandCreateRGBmap(Reference * firstReferenceInPrimitivesReferenceList, int width, int height, unsigned char * rgbMap, int dimension, bool usePredefinedODmatrixOperations);
void drawPrimitivesReferenceListToOpenGL(Reference * firstReferenceInPrimitivesReferenceList, int dimension, bool usePredefinedODmatrixOperations);
	static void draw2DquadsPrimitivesReferenceListToOpenGL();
	static void draw2DquadsPrimitivesReferenceListToOpenGLwithPredefinedMatrixOperations();
	static void draw3DtrisPrimitivesReferenceListToOpenGL();
	static void draw3DtrisPrimitivesReferenceListToOpenGLwithPredefinedMatrixOperations();

void drawPrimitivesReferenceListToOpenGLandCreateRGBmapBasic(Reference * firstReferenceInPrimitivesReferenceList, int width, int height, unsigned char * rgbMap);
	static void draw3DprimitivesReferenceListToOpenGLwithRecursion();
		static void draw3DprimitivesReferenceListToOpenGLrecurse(Reference * firstReferenceInLayer);

static void draw3DprimitivesReferenceListToOpenGL();
static void draw2DPrimitivesReferenceListToOpenGLSingleLayer();	//not used

	void writeScreenToRGBMap(int width, int height, unsigned char * rgbMap);
	void writeScreenToDepthMap(int width, int height, double * depthMap);
	void updateScreen();

void shearMatrix(float shearX, float shearY);

#endif


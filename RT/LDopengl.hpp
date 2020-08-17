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
 * File Name: LDopengl.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2020 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3n7d 17-August-2020
 * /
 *******************************************************************************/


#ifndef HEADER_LD_OPENGL
#define HEADER_LD_OPENGL

#include "SHAREDglobalDefs.hpp"
#include "LDreferenceClass.hpp"

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

class LDopenglClass
{
	public: bool initiateOpenGL(const int width, const int height, const int windowPositionX, const int windowPositionY, const bool confidentialWarnings);
	public: bool exitOpenGL();
	//void setViewPort(int width, int height, double xCentre, double yCentre);	//optional
	public: void setViewPort2Dortho(const double left, const double right, const double bottom, const double top);
	public: void setViewPort3D(const vec* eyeFacingPoly, const vec* viewAtFacingPoly, const vec* viewUpFacingPoly, const vec* viewPortWidthHeightDepth);
	private: void setViewPort3Ddynamic(const vec* eyeFacingPoly, const vec* viewAtFacingPoly, const vec* viewUpFacingPoly, vec* viewPortWidthHeightDepth);
	private: double maxDouble2(double float1, const double float2);
	private: void setViewPort3Dbasic();
	public: void setViewPort3Dortho(const double left, const double right, const double bottom, const double top, const double back, const double forward);


	public: void drawPrimitivesReferenceListToOpenGLandCreateRGBmap(const LDreference* firstReferenceInPrimitivesReferenceList, int width, const int height, unsigned char* rgbMap, const int dimension, const bool usePredefinedODmatrixOperations);
	public: void drawPrimitivesReferenceListToOpenGL(const LDreference* firstReferenceInPrimitivesReferenceList, const int dimension, const bool usePredefinedODmatrixOperations);

	public: void drawPrimitivesReferenceListToOpenGLandCreateRGBmapBasic(const LDreference* firstReferenceInPrimitivesReferenceList, int width, const int height, unsigned char* rgbMap);

		public: void writeScreenToRGBMap(int width, const int height, unsigned char* rgbMap);
		public: void writeScreenToDepthMap(int width, const int height, double* depthMap);
		public: void updateScreen();

	private: void shearMatrix(const float shearX, const float shearY);
};

static void draw2DquadsPrimitivesReferenceListToOpenGL();
static void draw2DquadsPrimitivesReferenceListToOpenGLwithPredefinedMatrixOperations();
static void draw3DtrisPrimitivesReferenceListToOpenGL();
static void draw3DtrisPrimitivesReferenceListToOpenGLwithPredefinedMatrixOperations();

static void draw3DprimitivesReferenceListToOpenGLwithRecursion();
static void draw3DprimitivesReferenceListToOpenGLrecurse(const LDreference* firstReferenceInLayer);

static void draw3DprimitivesReferenceListToOpenGL();
static void draw2DPrimitivesReferenceListToOpenGLSingleLayer();	//not used


#endif


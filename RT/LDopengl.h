/*******************************************************************************
 *
 * File Name: LDopengl.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3a7a 06-June-2012
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

extern mat opengl2DMultiplicationMatrix;
extern double opengl2DMatrixTransformation1ScaleFactor;
extern double opengl2DMatrixTransformation2iRotationFactor;
extern double opengl2DMatrixTransformation2iiRotationFactor;
extern double opengl2DMatrixTransformation3aScaleFactor;
extern double opengl2DMatrixTransformation4aShearFactor;
extern double opengl2DMatrixTransformation5aTranslationFactorX;
extern double opengl2DMatrixTransformation5aTranslationFactorY;

extern mat opengl3DMultiplicationMatrix;
extern double opengl3DMatrixTransformation1aXRotationFactor;
extern double opengl3DMatrixTransformation1bYRotationFactor;
extern double opengl3DMatrixTransformation2iZRotationFactor;
extern double opengl3DMatrixTransformation2iiZRotationFactor;
extern double opengl3DMatrixTransformation3TranslationFactorX;
extern double opengl3DMatrixTransformation3TranslationFactorY;
extern double opengl3DMatrixTransformation3TranslationFactorZ;

int initiateOpenGL(int width, int height, int windowPositionX, int windowPositionY, bool confidentialWarnings);
//void setViewPort(int width, int height, double xCentre, double yCentre);	//optional
void setViewPort2DOrtho(double left, double right, double bottom, double top);
void setViewPort3D(vec * eyeFacingPoly, vec * viewatFacingPoly, vec * viewupFacingPoly, vec * viewportWidthHeightDepth);
void setViewPort3DDynamic(vec * eyeFacingPoly, vec * viewatFacingPoly, vec * viewupFacingPoly, vec * viewportWidthHeightDepth);
void setViewPort3DBasic();
void setViewPort3DOrtho(double left, double right, double bottom, double top, double back, double forward);


void drawPrimitivesReferenceListToOpenGLAndCreateRGBMap(Reference * firstReferenceInPrimitivesReferenceList, int width, int height, unsigned char * rgbMap, int dimension, bool usePredefinedODMatrixOperations);
void drawPrimitivesReferenceListToOpenGL(Reference * firstReferenceInPrimitivesReferenceList, int dimension, bool usePredefinedODMatrixOperations);
	void draw2DQuadsPrimitivesReferenceListToOpenGL();
	void draw2DQuadsPrimitivesReferenceListToOpenGLWithPredefinedMatrixOperations();
	void draw3DTrisPrimitivesReferenceListToOpenGL();
	void draw3DTrisPrimitivesReferenceListToOpenGLWithPredefinedMatrixOperations();

void drawPrimitivesReferenceListToOpenGLAndCreateRGBMapBasic(Reference * firstReferenceInPrimitivesReferenceList, int width, int height, unsigned char * rgbMap);
	void draw3DPrimitivesReferenceListToOpenGLwithRecursion();
		void draw3DPrimitivesReferenceListToOpenGLRecurse(Reference * firstReferenceInLayer);

void draw3DPrimitivesReferenceListToOpenGL();

	void writeScreenToRGBMap(int width, int height, unsigned char * rgbMap);
	void writeScreenToDepthMap(int width, int height, double * depthMap);
	void updateScreen();

void shearMatrix(float shearX, float shearY);

#endif


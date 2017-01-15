/*******************************************************************************
 *
 * File Name: LDopengl.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3a7e 12-June-2012
 *
 *******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;
#include "LDopengl.h"

//#include <GL/gl.h>
//#include <GL/glut.h>
#include <GL/freeglut.h>	//need to use freeglut as it contains extensions functions which glut does not have; glutMainLoopEvent()


#ifdef USE_LD_ABSOLUTE_COLOUR

mat opengl2DMultiplicationMatrix;
double opengl2DMatrixTransformation1ScaleFactor = 0.0;
double opengl2DMatrixTransformation2iRotationFactor = 0.0;
double opengl2DMatrixTransformation2iiRotationFactor = 0.0;
double opengl2DMatrixTransformation3aScaleFactor = 0.0;
double opengl2DMatrixTransformation4aShearFactor = 0.0;
double opengl2DMatrixTransformation5aTranslationFactorX = 0.0;
double opengl2DMatrixTransformation5aTranslationFactorY = 0.0;

mat opengl3DMultiplicationMatrix;
double opengl3DMatrixTransformation1aXRotationFactor = 0.0;
double opengl3DMatrixTransformation1bYRotationFactor = 0.0;
double opengl3DMatrixTransformation2iZRotationFactor = 0.0;
double opengl3DMatrixTransformation2iiZRotationFactor = 0.0;
double opengl3DMatrixTransformation3TranslationFactorX = 0.0;
double opengl3DMatrixTransformation3TranslationFactorY = 0.0;
double opengl3DMatrixTransformation3TranslationFactorZ = 0.0;


//these can no longer be configured dynamically through ORrules.xml
static bool LD_OPENGL_PRINT_ALGORITHM_AND_TIME_DETAILS_ALL = false;
static bool LD_OPENGL_PRINT_ALGORITHM_AND_TIME_DETAILS = false;
static bool LD_OPENGL_PRINT_ALGORITHM_PROGRESS = false;


Reference * firstReferenceInPrimitivesReferenceListGlobal;

// Compute the Shear Matrix
//   OpenGL does not provide a Shear matrix
//   (that I could find yet)
//   Plus it illustrates how to pass ANYWAY
//   Matrix to OpenGL
//     Note: m goes down COLUMNS first...
//        m1, m2, m3, m4 represent m11, m21, m31, m41
//        m5, m6, m7, m8 represent m12, m22, m32, m42
//        etc...
void shearMatrix(float shearX, float shearY)
{
	float m[] = {
		1.0, shearY, 0.0, 0.0,
		shearX, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0 };
	glMultMatrixf(m);
}

void writeScreenToRGBMap(int width, int height, unsigned char * rgbMap)
{
	const int bytesPerPixel = 3;	// RGB
	const int imageSizeInBytes = bytesPerPixel * width * height;

	unsigned char * pixels = new unsigned char[imageSizeInBytes];

		// glReadPixels takes the lower-left corner, while GetViewportOffset gets the top left corner
		//const wxPoint topLeft = GetViewportOffset();
		//const wxPoint lowerLeft(topLeft.x, GetClientSize().GetHeight() - (topLeft.y + height));

	// glReadPixels can align the first pixel in each row at 1-, 2-, 4- and 8-byte boundaries. We
	// have allocated the exact size needed for the image so we have to use 1-byte alignment
	// (otherwise glReadPixels would write out of bounds)
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
		//	glReadPixels(lowerLeft.x, topLeft.y, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);


	// glReadPixels reads the given rectangle from bottom-left to top-right, so we must
	// reverse it

	//unsigned char * rgbMap = new unsigned char[imageSizeInBytes];

	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			//#define USE_OFFICIAL_OPENGL
			//#define USE_GLUT
			#define USE_FREEGLUT
			#ifdef USE_GLUT
			int oldx = (x);	//??
			int oldy = (y); //??
			#elif defined USE_OFFICIAL_OPENGL
			int oldx = ((width-1)-x);	//??
			int oldy = ((height-1)-y);	//??
			#elif defined USE_FREEGLUT
			int oldx = (x);
			int oldy = ((height-1)-y);
			#endif

			rgbMap[y*width*RGB_NUM + x*RGB_NUM + RGB_RED] = pixels[(bytesPerPixel) * (oldx + oldy * width) + RGB_RED];
			rgbMap[y*width*RGB_NUM + x*RGB_NUM + RGB_GREEN] = pixels[(bytesPerPixel) * (oldx + oldy * width) + RGB_GREEN];
			rgbMap[y*width*RGB_NUM + x*RGB_NUM + RGB_BLUE] = pixels[(bytesPerPixel) * (oldx + oldy * width) + RGB_BLUE];

		}
	}

	delete pixels;


}



void writeScreenToDepthMap(int width, int height, double * depthMap)
{
	GLfloat *pixels = new GLfloat[width * height];
	//GLuint *pixels = new GLuint[width * height];
	/*
	glPixelStorei(GL_PACK_ROW_LENGTH, width);
	int rowSkip = 0;
	int pixelSkip = 0;
	glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_PACK_SKIP_ROWS, 0);
	glReadPixels(pixelSkip, rowSkip, width, height, GL_DEPTH_COMPONENT, GL_FLOAT, pixels);
	*/
	//	//?
	//glReadBuffer(GL_BACK);	//?
	//glPixelTransferf(GL_DEPTH_SCALE, 1.0);	//pnr
	//glPixelTransferf(GL_DEPTH_BIAS, 0.0);	//probably not req
	glReadPixels(0, 0, width, height, GL_DEPTH_COMPONENT, GL_FLOAT, pixels);
	//glReadPixels(0, 0, width, height, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, pixels);

	// glReadPixels reads the given rectangle from bottom-left to top-right, so we must
	// reverse it

	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			//#define USE_OFFICIAL_OPENGL
			//#define USE_GLUT
			#define USE_FREEGLUT
			#ifdef USE_GLUT
			int oldx = (x);	//??
			int oldy = (y); //??
			#elif defined USE_OFFICIAL_OPENGL
			int oldx = ((width-1)-x);	//??
			int oldy = ((height-1)-y);	//??
			#elif defined USE_FREEGLUT
			int oldx = (x);
			int oldy = ((height-1)-y);
			#endif

			depthMap[y*width + x] = (pixels[oldx + (oldy * width)]);
			//depthMap[y*width + x] = ((double)(pixels[oldx + (oldy * width)]))/((double)(sizeof(GL_UNSIGNED_INT)));

			if(depthMap[y*width + x] > 0)
			{
				//cout << "depthMap[" << y << "*width + " << x << "] = " << depthMap[y*width + x] << endl;
			#ifdef FIX_OPENGL_3DOD_TIMING_BUG
				cout << depthMap[y*width + x] << endl;
			#endif
			}
		}
	}

	delete pixels;


}


void draw3DTrisPrimitivesReferenceListToOpenGL()
{
	#ifndef  __FREEGLUT_EXT_H__
		cout << "freeglut appears not to be installed" << endl;
	#endif

	glClearColor(OPEN_GL_BACKGROUND_COLOUR_R,OPEN_GL_BACKGROUND_COLOUR_G,OPEN_GL_BACKGROUND_COLOUR_B,0.0);	//use black background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);

	/*
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	*/


	glBegin(GL_TRIANGLES);

	Reference * currentReference = firstReferenceInPrimitivesReferenceListGlobal;
	while(currentReference->next != NULL)
	{
		float r;
		float g;
		float b;

		if(currentReference->absoluteColour < 255)
		{
			colour col;
			convertLdrawColourToDatFileRGB(currentReference->absoluteColour, &col);
			r = col.r;
			g = col.g;
			b = col.b;
		}
		else
		{
			//cout << "h1" << endl;
			unsigned int colourExtracted = currentReference->absoluteColour;
			colourExtracted = colourExtracted - (DAT_FILE_FIRST_RGB_COLOUR << 24);
			r = ((unsigned int)(colourExtracted << 8) >> 24);
			g = ((unsigned int)(colourExtracted << 16) >> 24);
			b = ((unsigned int)(colourExtracted << 24) >> 24);
		}
		r = r / 255.0;
		g = g / 255.0;
		b = b / 255.0;

		glColor3f(r,g,b);
		glVertex3f(currentReference->vertex1absolutePosition.x,currentReference->vertex1absolutePosition.y,currentReference->vertex1absolutePosition.z);
		glVertex3f(currentReference->vertex2absolutePosition.x,currentReference->vertex2absolutePosition.y,currentReference->vertex2absolutePosition.z);
		glVertex3f(currentReference->vertex3absolutePosition.x,currentReference->vertex3absolutePosition.y,currentReference->vertex3absolutePosition.z);

		currentReference = currentReference->next;
	}

	glEnd();
	//glPopMatrix();
	glFlush();

}

//not required for 3D - can use viewport instead of rotating model
void draw3DTrisPrimitivesReferenceListToOpenGLWithPredefinedMatrixOperations()
{
	long time3biNormalisedSnapshotGenerationRaytraceOrOpenGLSnapshotDrawSceneStart;
	if(LD_OPENGL_PRINT_ALGORITHM_AND_TIME_DETAILS)
	{
		if(LD_OPENGL_PRINT_ALGORITHM_AND_TIME_DETAILS_ALL)
		{
			cout << "\t\t\t\t start: 3bi. normalised snapshot generation - raytrace or opengl snapshot - draw scene" << endl;
		}
		time3biNormalisedSnapshotGenerationRaytraceOrOpenGLSnapshotDrawSceneStart = getTimeAsLong();
	}

	#ifndef  __FREEGLUT_EXT_H__
		cout << "freeglut appears not to be installed" << endl;
	#endif

	glClearColor(OPEN_GL_BACKGROUND_COLOUR_R,OPEN_GL_BACKGROUND_COLOUR_G,OPEN_GL_BACKGROUND_COLOUR_B,0.0);	//use black background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();



	#ifdef USE_OPENGL_PREDEFINED_OD_MATRIX_OPERATIONS_ADV

		glTranslatef(opengl3DMatrixTransformation3TranslationFactorX, opengl3DMatrixTransformation3TranslationFactorY, opengl3DMatrixTransformation3TranslationFactorZ);

	GLfloat m[] =
		{(GLfloat)opengl3DMultiplicationMatrix.a.x, (GLfloat)opengl3DMultiplicationMatrix.a.y, (GLfloat)opengl3DMultiplicationMatrix.a.z, 0.0,
		(GLfloat)opengl3DMultiplicationMatrix.b.x, (GLfloat)opengl3DMultiplicationMatrix.b.y, (GLfloat)opengl3DMultiplicationMatrix.b.z, 0.0,
		(GLfloat)opengl3DMultiplicationMatrix.c.x, (GLfloat)opengl3DMultiplicationMatrix.c.y, (GLfloat)opengl3DMultiplicationMatrix.c.z, 0.0,
		0.0, 0.0, 0.0, 1.0 };
		glMultMatrixf(m);

	#else
		glTranslatef(opengl3DMatrixTransformation3TranslationFactorX, opengl3DMatrixTransformation3TranslationFactorY, opengl3DMatrixTransformation3TranslationFactorZ);
		glRotatef(opengl3DMatrixTransformation2iiZRotationFactor/PI*180.0, 0.0, 0.0, 1.0f);
		glRotatef(opengl3DMatrixTransformation2iZRotationFactor/PI*180.0, 0.0, 0.0, 1.0f);
		glRotatef(opengl3DMatrixTransformation1bYRotationFactor/PI*180.0, 0.0, 1.0f, 0.0);
		glRotatef(opengl3DMatrixTransformation1aXRotationFactor/PI*180.0, 1.0f, 0.0, 0.0);


	#endif


	glBegin(GL_TRIANGLES);

	Reference * currentReference = firstReferenceInPrimitivesReferenceListGlobal;
	while(currentReference->next != NULL)
	{


		float r;
		float g;
		float b;

		if(currentReference->absoluteColour < 255)
		{
			colour col;
			convertLdrawColourToDatFileRGB(currentReference->absoluteColour, &col);
			r = col.r;
			g = col.g;
			b = col.b;
		}
		else
		{
			//cout << "h1" << endl;
			unsigned int colourExtracted = currentReference->absoluteColour;
			colourExtracted = colourExtracted - (DAT_FILE_FIRST_RGB_COLOUR << 24);
			r = ((unsigned int)(colourExtracted << 8) >> 24);
			g = ((unsigned int)(colourExtracted << 16) >> 24);
			b = ((unsigned int)(colourExtracted << 24) >> 24);
		}
		r = r / 255.0;
		g = g / 255.0;
		b = b / 255.0;

		glColor3f(r,g,b);
		glVertex3f(currentReference->vertex1absolutePosition.x,currentReference->vertex1absolutePosition.y,currentReference->vertex1absolutePosition.z);
		glVertex3f(currentReference->vertex2absolutePosition.x,currentReference->vertex2absolutePosition.y,currentReference->vertex2absolutePosition.z);
		glVertex3f(currentReference->vertex3absolutePosition.x,currentReference->vertex3absolutePosition.y,currentReference->vertex3absolutePosition.z);

		currentReference = currentReference->next;

	}

	glEnd();
	glPopMatrix();
	glFlush();


	if(LD_OPENGL_PRINT_ALGORITHM_AND_TIME_DETAILS)
	{
		if(LD_OPENGL_PRINT_ALGORITHM_AND_TIME_DETAILS_ALL)
		{
			cout << "\t\t\t\t end: 3bi. normalised snapshot generation - raytrace or opengl snapshot - draw scene" << endl;
		}
		long time3biNormalisedSnapshotGenerationRaytraceOrOpenGLSnapshotDrawSceneEnd;
		time3biNormalisedSnapshotGenerationRaytraceOrOpenGLSnapshotDrawSceneEnd = getTimeAsLong();
		if(LD_OPENGL_PRINT_ALGORITHM_AND_TIME_DETAILS_ALL)
		{
			cout << "\t\t\t\t time3biNormalisedSnapshotGenerationRaytraceOrOpenGLSnapshotDrawScene = " << time3biNormalisedSnapshotGenerationRaytraceOrOpenGLSnapshotDrawSceneEnd-time3biNormalisedSnapshotGenerationRaytraceOrOpenGLSnapshotDrawSceneStart << endl;
		}
	}

	//cout << "h3" << endl;
}




void draw3DPrimitivesReferenceListToOpenGL()
{
	cout << "here" << endl;

	#ifndef  __FREEGLUT_EXT_H__
		cout << "freeglut appears not to be installed" << endl;
	#endif

	glClearColor(OPEN_GL_BACKGROUND_COLOUR_R,OPEN_GL_BACKGROUND_COLOUR_G,OPEN_GL_BACKGROUND_COLOUR_B,0.0);	//use black background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	Reference * currentReference = firstReferenceInPrimitivesReferenceListGlobal;
	while(currentReference->next != NULL)
	{
		float r;
		float g;
		float b;

		if(currentReference->absoluteColour < 255)
		{
			colour col;
			convertLdrawColourToDatFileRGB(currentReference->absoluteColour, &col);
			r = col.r;
			g = col.g;
			b = col.b;
		}
		else
		{
			//cout << "h1" << endl;
			unsigned int colourExtracted = currentReference->absoluteColour;
			colourExtracted = colourExtracted - (DAT_FILE_FIRST_RGB_COLOUR << 24);
			r = ((unsigned int)(colourExtracted << 8) >> 24);
			g = ((unsigned int)(colourExtracted << 16) >> 24);
			b = ((unsigned int)(colourExtracted << 24) >> 24);
		}
		r = r / 255.0;
		g = g / 255.0;
		b = b / 255.0;

		if(currentReference->type == REFERENCE_TYPE_LINE)
		{
			glBegin(GL_LINES);
				glColor3f(r,g,b);
				glVertex3f(currentReference->vertex1absolutePosition.x,currentReference->vertex1absolutePosition.y,currentReference->vertex1absolutePosition.z);
				glVertex3f(currentReference->vertex2absolutePosition.x,currentReference->vertex2absolutePosition.y,currentReference->vertex2absolutePosition.z);
			glEnd();
		}
		else if(currentReference->type == REFERENCE_TYPE_TRI)
		{
			glBegin(GL_TRIANGLES);
				glColor3f(r,g,b);
				glVertex3f(currentReference->vertex1absolutePosition.x,currentReference->vertex1absolutePosition.y,currentReference->vertex1absolutePosition.z);
				glVertex3f(currentReference->vertex2absolutePosition.x,currentReference->vertex2absolutePosition.y,currentReference->vertex2absolutePosition.z);
				glVertex3f(currentReference->vertex3absolutePosition.x,currentReference->vertex3absolutePosition.y,currentReference->vertex3absolutePosition.z);
			glEnd();
		}
		else if(currentReference->type == REFERENCE_TYPE_QUAD)
		{
			glBegin(GL_QUADS);
				glColor3f(r,g,b);
				glVertex3f(currentReference->vertex1absolutePosition.x,currentReference->vertex1absolutePosition.y,currentReference->vertex1absolutePosition.z);
				glVertex3f(currentReference->vertex2absolutePosition.x,currentReference->vertex2absolutePosition.y,currentReference->vertex2absolutePosition.z);
				glVertex3f(currentReference->vertex3absolutePosition.x,currentReference->vertex3absolutePosition.y,currentReference->vertex3absolutePosition.z);
				glVertex3f(currentReference->vertex4absolutePosition.x,currentReference->vertex4absolutePosition.y,currentReference->vertex4absolutePosition.z);
			glEnd();
		}

		currentReference = currentReference->next;
	}

	glPopMatrix();

	glFlush();
}

void draw2DQuadsPrimitivesReferenceListToOpenGLWithPredefinedMatrixOperations()
{
	long time3biNormalisedSnapshotGenerationRaytraceOrOpenGLSnapshotDrawSceneStart;
	if(LD_OPENGL_PRINT_ALGORITHM_AND_TIME_DETAILS)
	{
		if(LD_OPENGL_PRINT_ALGORITHM_AND_TIME_DETAILS_ALL)
		{
			cout << "\t\t\t\t start: 3bi. normalised snapshot generation - raytrace or opengl snapshot - draw scene" << endl;
		}
		time3biNormalisedSnapshotGenerationRaytraceOrOpenGLSnapshotDrawSceneStart = getTimeAsLong();
	}

	#ifndef  __FREEGLUT_EXT_H__
		cout << "freeglut appears not to be installed" << endl;
	#endif

	glClearColor(OPEN_GL_BACKGROUND_COLOUR_R,OPEN_GL_BACKGROUND_COLOUR_G,OPEN_GL_BACKGROUND_COLOUR_B,0.0);	//use black background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	#ifdef USE_OPENGL_PREDEFINED_OD_MATRIX_OPERATIONS_ADV

		//cout << "h2" << endl;

		glTranslatef(opengl2DMatrixTransformation5aTranslationFactorX, opengl2DMatrixTransformation5aTranslationFactorY, 0.0);

	GLfloat m[] =
		{(GLfloat)opengl2DMultiplicationMatrix.a.x, (GLfloat)opengl2DMultiplicationMatrix.a.y, (GLfloat)opengl2DMultiplicationMatrix.a.z, 0.0,
		(GLfloat)opengl2DMultiplicationMatrix.b.x, (GLfloat)opengl2DMultiplicationMatrix.b.y, (GLfloat)opengl2DMultiplicationMatrix.b.z, 0.0,
		(GLfloat)opengl2DMultiplicationMatrix.c.x, (GLfloat)opengl2DMultiplicationMatrix.c.y, (GLfloat)opengl2DMultiplicationMatrix.c.z, 0.0,
		0.0, 0.0, 0.0, 1.0 };
		glMultMatrixf(m);

		/*
		glTranslatef(opengl2DMatrixTransformation5aTranslationFactorX, opengl2DMatrixTransformation5aTranslationFactorY, 0.0);
		shearMatrix(opengl2DMatrixTransformation4aShearFactor, 0.0);
		glScalef(opengl2DMatrixTransformation3aScaleFactor, opengl2DMatrixTransformation3aScaleFactor, opengl2DMatrixTransformation3aScaleFactor);
		glRotatef(opengl2DMatrixTransformation2iiRotationFactor/PI*180.0, 0.0, 0.0, 1.0f);
		glRotatef(opengl2DMatrixTransformation2iRotationFactor/PI*180.0, 0.0, 0.0, 1.0f);
		glScalef(opengl2DMatrixTransformation1ScaleFactor, opengl2DMatrixTransformation1ScaleFactor, opengl2DMatrixTransformation1ScaleFactor);
		*/

	#else
		glTranslatef(opengl2DMatrixTransformation5aTranslationFactorX, opengl2DMatrixTransformation5aTranslationFactorY, 0.0);

		shearMatrix(opengl2DMatrixTransformation4aShearFactor, 0.0);
		glScalef(opengl2DMatrixTransformation3aScaleFactor, opengl2DMatrixTransformation3aScaleFactor, opengl2DMatrixTransformation3aScaleFactor);
		glRotatef(opengl2DMatrixTransformation2iiRotationFactor/PI*180.0, 0.0, 0.0, 1.0f);
		glRotatef(opengl2DMatrixTransformation2iRotationFactor/PI*180.0, 0.0, 0.0, 1.0f);
		glScalef(opengl2DMatrixTransformation1ScaleFactor, opengl2DMatrixTransformation1ScaleFactor, opengl2DMatrixTransformation1ScaleFactor);

	#endif



	glBegin(GL_QUADS);


	Reference * currentReference = firstReferenceInPrimitivesReferenceListGlobal;
	while(currentReference->next != NULL)
	{

		if(currentReference->referenceEnabledMethod2DOD)
		{
			float r;
			float g;
			float b;

			if(currentReference->absoluteColour < 255)
			{
				colour col;
				convertLdrawColourToDatFileRGB(currentReference->absoluteColour, &col);
				r = col.r;
				g = col.g;
				b = col.b;
			}
			else
			{
				//cout << "h1" << endl;
				unsigned int colourExtracted = currentReference->absoluteColour;
				colourExtracted = colourExtracted - (DAT_FILE_FIRST_RGB_COLOUR << 24);
				r = ((unsigned int)(colourExtracted << 8) >> 24);
				g = ((unsigned int)(colourExtracted << 16) >> 24);
				b = ((unsigned int)(colourExtracted << 24) >> 24);
			}
			r = r / 255.0;
			g = g / 255.0;
			b = b / 255.0;

			glColor3f(r,g,b);

			/*
			if(((int)r == 0) && ((int)g == 0) && ((int)b == 0))
			{
				exit(0);
			}
			*/

			/*
			cout << "r = " << r << endl;
			cout << "g = " << g << endl;
			cout << "b = " << b << endl;
			cout << "currentReference->vertex1absolutePosition.x = " << currentReference->vertex1absolutePosition.x << endl;
			cout << "currentReference->vertex1absolutePosition.y = " << currentReference->vertex1absolutePosition.y << endl;
			cout << "currentReference->vertex2absolutePosition.x = " << currentReference->vertex2absolutePosition.x << endl;
			cout << "currentReference->vertex2absolutePosition.y = " << currentReference->vertex2absolutePosition.y << endl;
			cout << "currentReference->vertex3absolutePosition.x = " << currentReference->vertex3absolutePosition.x << endl;
			cout << "currentReference->vertex3absolutePosition.y = " << currentReference->vertex3absolutePosition.y << endl;
			cout << "currentReference->vertex4absolutePosition.x = " << currentReference->vertex4absolutePosition.x << endl;
			cout << "currentReference->vertex4absolutePosition.y = " << currentReference->vertex4absolutePosition.y << endl;
			*/

			glVertex2f(currentReference->vertex1absolutePosition.x,currentReference->vertex1absolutePosition.y);
			glVertex2f(currentReference->vertex2absolutePosition.x,currentReference->vertex2absolutePosition.y);
			glVertex2f(currentReference->vertex3absolutePosition.x,currentReference->vertex3absolutePosition.y);
			glVertex2f(currentReference->vertex4absolutePosition.x,currentReference->vertex4absolutePosition.y);


			//cout << "h2" << endl;
		}

		currentReference = currentReference->next;
	}

	glEnd();

	glPopMatrix();

	glFlush();


	if(LD_OPENGL_PRINT_ALGORITHM_AND_TIME_DETAILS)
	{
		if(LD_OPENGL_PRINT_ALGORITHM_AND_TIME_DETAILS_ALL)
		{
			cout << "\t\t\t\t end: 3bi. normalised snapshot generation - raytrace or opengl snapshot - draw scene" << endl;
		}
		long time3biNormalisedSnapshotGenerationRaytraceOrOpenGLSnapshotDrawSceneEnd;
		time3biNormalisedSnapshotGenerationRaytraceOrOpenGLSnapshotDrawSceneEnd = getTimeAsLong();
		if(LD_OPENGL_PRINT_ALGORITHM_AND_TIME_DETAILS_ALL)
		{
			cout << "\t\t\t\t time3biNormalisedSnapshotGenerationRaytraceOrOpenGLSnapshotDrawScene = " << time3biNormalisedSnapshotGenerationRaytraceOrOpenGLSnapshotDrawSceneEnd-time3biNormalisedSnapshotGenerationRaytraceOrOpenGLSnapshotDrawSceneStart << endl;
		}
	}

	//cout << "h3" << endl;
}


void draw2DQuadsPrimitivesReferenceListToOpenGL()
{
	#ifndef  __FREEGLUT_EXT_H__
		cout << "freeglut appears not to be installed" << endl;
	#endif

	glClearColor(OPEN_GL_BACKGROUND_COLOUR_R,OPEN_GL_BACKGROUND_COLOUR_G,OPEN_GL_BACKGROUND_COLOUR_B,0.0);	//use black background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	glBegin(GL_QUADS);


	Reference * currentReference = firstReferenceInPrimitivesReferenceListGlobal;
	while(currentReference->next != NULL)
	{

		if(currentReference->referenceEnabledMethod2DOD)
		{
			float r;
			float g;
			float b;

			if(currentReference->absoluteColour < 255)
			{
				colour col;
				convertLdrawColourToDatFileRGB(currentReference->absoluteColour, &col);
				r = col.r;
				g = col.g;
				b = col.b;
			}
			else
			{
				//cout << "h1" << endl;
				unsigned int colourExtracted = currentReference->absoluteColour;
				colourExtracted = colourExtracted - (DAT_FILE_FIRST_RGB_COLOUR << 24);
				r = ((unsigned int)(colourExtracted << 8) >> 24);
				g = ((unsigned int)(colourExtracted << 16) >> 24);
				b = ((unsigned int)(colourExtracted << 24) >> 24);
			}
			r = r / 255.0;
			g = g / 255.0;
			b = b / 255.0;

			glColor3f(r,g,b);

			/*
			if(((int)r == 0) && ((int)g == 0) && ((int)b == 0))
			{
				exit(0);
			}
			*/

			/*
			cout << "r = " << r << endl;
			cout << "g = " << g << endl;
			cout << "b = " << b << endl;
			cout << "currentReference->vertex1absolutePosition.x = " << currentReference->vertex1absolutePosition.x << endl;
			cout << "currentReference->vertex1absolutePosition.y = " << currentReference->vertex1absolutePosition.y << endl;
			cout << "currentReference->vertex2absolutePosition.x = " << currentReference->vertex2absolutePosition.x << endl;
			cout << "currentReference->vertex2absolutePosition.y = " << currentReference->vertex2absolutePosition.y << endl;
			cout << "currentReference->vertex3absolutePosition.x = " << currentReference->vertex3absolutePosition.x << endl;
			cout << "currentReference->vertex3absolutePosition.y = " << currentReference->vertex3absolutePosition.y << endl;
			cout << "currentReference->vertex4absolutePosition.x = " << currentReference->vertex4absolutePosition.x << endl;
			cout << "currentReference->vertex4absolutePosition.y = " << currentReference->vertex4absolutePosition.y << endl;
			*/

			glVertex2f(currentReference->vertex1absolutePosition.x,currentReference->vertex1absolutePosition.y);
			glVertex2f(currentReference->vertex2absolutePosition.x,currentReference->vertex2absolutePosition.y);
			glVertex2f(currentReference->vertex3absolutePosition.x,currentReference->vertex3absolutePosition.y);
			glVertex2f(currentReference->vertex4absolutePosition.x,currentReference->vertex4absolutePosition.y);


			//cout << "h2" << endl;
		}

		currentReference = currentReference->next;
	}

	glEnd();

	glPopMatrix();

	glFlush();

	//cout << "h3" << endl;
}



void draw3DPrimitivesReferenceListToOpenGLRecurse(Reference * firstReferenceInLayer)
{
	Reference * currentReference = firstReferenceInLayer;
	while(currentReference->next != NULL)
	{

		if(currentReference->isSubModelReference)
		{
			draw3DPrimitivesReferenceListToOpenGLRecurse(currentReference->firstReferenceWithinSubModel);
		}
		else
		{


		//if(currentReference->referenceEnabledMethod2DOD)
		//{
			float r;
			float g;
			float b;

			if(currentReference->absoluteColour < 255)
			{
				colour col;
				convertLdrawColourToDatFileRGB(currentReference->absoluteColour, &col);
				r = col.r;
				g = col.g;
				b = col.b;
			}
			else
			{
				//cout << "h1" << endl;
				unsigned int colourExtracted = currentReference->absoluteColour;
				colourExtracted = colourExtracted - (DAT_FILE_FIRST_RGB_COLOUR << 24);
				r = ((unsigned int)(colourExtracted << 8) >> 24);
				g = ((unsigned int)(colourExtracted << 16) >> 24);
				b = ((unsigned int)(colourExtracted << 24) >> 24);
			}
			r = r / 255.0;
			g = g / 255.0;
			b = b / 255.0;

			if(currentReference->type == REFERENCE_TYPE_LINE)
			{

				glBegin(GL_LINES);
					glColor3f(r,g,b);
					glVertex3f(currentReference->vertex1absolutePosition.x,currentReference->vertex1absolutePosition.y,currentReference->vertex1absolutePosition.z);
					glVertex3f(currentReference->vertex2absolutePosition.x,currentReference->vertex2absolutePosition.y,currentReference->vertex2absolutePosition.z);
				glEnd();

			}
			else if(currentReference->type == REFERENCE_TYPE_TRI)
			{

				glBegin(GL_TRIANGLES);
					glColor3f(r,g,b);
					glVertex3f(currentReference->vertex1absolutePosition.x,currentReference->vertex1absolutePosition.y,currentReference->vertex1absolutePosition.z);
					glVertex3f(currentReference->vertex2absolutePosition.x,currentReference->vertex2absolutePosition.y,currentReference->vertex2absolutePosition.z);
					glVertex3f(currentReference->vertex3absolutePosition.x,currentReference->vertex3absolutePosition.y,currentReference->vertex3absolutePosition.z);
				glEnd();
			}
			else if(currentReference->type == REFERENCE_TYPE_QUAD)
			{
				//r = 1.0;

				glBegin(GL_QUADS);
					glColor3f(r,g,b);
					glVertex3f(currentReference->vertex1absolutePosition.x,currentReference->vertex1absolutePosition.y,currentReference->vertex1absolutePosition.z);
					glVertex3f(currentReference->vertex2absolutePosition.x,currentReference->vertex2absolutePosition.y,currentReference->vertex2absolutePosition.z);
					glVertex3f(currentReference->vertex3absolutePosition.x,currentReference->vertex3absolutePosition.y,currentReference->vertex3absolutePosition.z);
					glVertex3f(currentReference->vertex4absolutePosition.x,currentReference->vertex4absolutePosition.y,currentReference->vertex4absolutePosition.z);
				glEnd();
			}
		//}

		}

		currentReference = currentReference->next;
	}
}


void draw3DPrimitivesReferenceListToOpenGLwithRecursion()
{
	//cout << "h2" << endl;

	#ifndef  __FREEGLUT_EXT_H__
		cout << "freeglut appears not to be installed" << endl;
	#endif

	glClearColor(OPEN_GL_BACKGROUND_COLOUR_R,OPEN_GL_BACKGROUND_COLOUR_G,OPEN_GL_BACKGROUND_COLOUR_B,0.0);	//use white background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	draw3DPrimitivesReferenceListToOpenGLRecurse(firstReferenceInPrimitivesReferenceListGlobal);


	glPopMatrix();

	glFlush();

	//cout << "h3" << endl;
}





void draw2DPrimitivesReferenceListToOpenGLSingleLayer()
{
	//cout << "h2" << endl;

	#ifndef  __FREEGLUT_EXT_H__
		cout << "freeglut appears not to be installed" << endl;
	#endif

	glClearColor(OPEN_GL_BACKGROUND_COLOUR_R,OPEN_GL_BACKGROUND_COLOUR_G,OPEN_GL_BACKGROUND_COLOUR_B,0.0);	//use black background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();


	Reference * currentReference = firstReferenceInPrimitivesReferenceListGlobal;
	while(currentReference->next != NULL)
	{
		//if(currentReference->referenceEnabledMethod2DOD)
		//{

			float r;
			float g;
			float b;

			if(currentReference->absoluteColour < 255)
			{
				colour col;
				convertLdrawColourToDatFileRGB(currentReference->absoluteColour, &col);
				r = col.r;
				g = col.g;
				b = col.b;
			}
			else
			{
				//cout << "h1" << endl;
				unsigned int colourExtracted = currentReference->absoluteColour;
				colourExtracted = colourExtracted - (DAT_FILE_FIRST_RGB_COLOUR << 24);
				r = ((unsigned int)(colourExtracted << 8) >> 24);
				g = ((unsigned int)(colourExtracted << 16) >> 24);
				b = ((unsigned int)(colourExtracted << 24) >> 24);
			}
			r = r / 255.0;
			g = g / 255.0;
			b = b / 255.0;

			glColor3f(r,g,b);


			if(currentReference->type == REFERENCE_TYPE_LINE)
			{
				//cout << "here" << endl;

				glBegin(GL_LINES);
					glColor3f(r,g,b);
					glVertex2f(currentReference->vertex1absolutePosition.x,currentReference->vertex1absolutePosition.y);
					glVertex2f(currentReference->vertex2absolutePosition.x,currentReference->vertex2absolutePosition.y);
				glEnd();

			}
			else if(currentReference->type == REFERENCE_TYPE_TRI)
			{
				glBegin(GL_TRIANGLES);
					glColor3f(r,g,b);
					glVertex2f(currentReference->vertex1absolutePosition.x,currentReference->vertex1absolutePosition.y);
					glVertex2f(currentReference->vertex2absolutePosition.x,currentReference->vertex2absolutePosition.y);
					glVertex2f(currentReference->vertex3absolutePosition.x,currentReference->vertex3absolutePosition.y);
				glEnd();
			}
			else if(currentReference->type == REFERENCE_TYPE_QUAD)
			{
				//cout << "here2" << endl;

				glBegin(GL_QUADS);
					glColor3f(r,g,b);
					glVertex2f(currentReference->vertex1absolutePosition.x,currentReference->vertex1absolutePosition.y);
					glVertex2f(currentReference->vertex2absolutePosition.x,currentReference->vertex2absolutePosition.y);
					glVertex2f(currentReference->vertex3absolutePosition.x,currentReference->vertex3absolutePosition.y);
					glVertex2f(currentReference->vertex4absolutePosition.x,currentReference->vertex4absolutePosition.y);
				glEnd();
			}
		//}



		currentReference = currentReference->next;
	}

	glPopMatrix();

	glFlush();

	//cout << "h3" << endl;
}





void drawPrimitivesReferenceListToOpenGLAndCreateRGBMap(Reference * firstReferenceInPrimitivesReferenceList, int width, int height, unsigned char * rgbMap, int dimension, bool usePredefinedODMatrixOperations)
{
	if(dimension == OR_METHOD3DOD_DIMENSIONS)
	{
		if(usePredefinedODMatrixOperations)
		{
			firstReferenceInPrimitivesReferenceListGlobal = firstReferenceInPrimitivesReferenceList;
			glutDisplayFunc(draw3DTrisPrimitivesReferenceListToOpenGLWithPredefinedMatrixOperations);
		}
		else
		{
			firstReferenceInPrimitivesReferenceListGlobal = firstReferenceInPrimitivesReferenceList;
			glutDisplayFunc(draw3DTrisPrimitivesReferenceListToOpenGL);
		}
	}
	else if(dimension == OR_METHOD2DOD_DIMENSIONS)
	{
		if(usePredefinedODMatrixOperations)
		{
			firstReferenceInPrimitivesReferenceListGlobal = firstReferenceInPrimitivesReferenceList;
			glutDisplayFunc(draw2DQuadsPrimitivesReferenceListToOpenGLWithPredefinedMatrixOperations);
		}
		else
		{
			firstReferenceInPrimitivesReferenceListGlobal = firstReferenceInPrimitivesReferenceList;
			glutDisplayFunc(draw2DQuadsPrimitivesReferenceListToOpenGL);
		}
	}
	else
	{
		cout << "dimension = " << dimension << endl;
		cout << "Error: illegal number dimensions" << endl;
		exit(0);
	}

	glutMainLoopEvent();

	//glutPostRedisplay();	CHECK THIS - may be required here instead????

	writeScreenToRGBMap(width, height, rgbMap);

	glutPostRedisplay();

	//cout << "h4" << endl;
}

void drawPrimitivesReferenceListToOpenGL(Reference * firstReferenceInPrimitivesReferenceList, int dimension, bool usePredefinedODMatrixOperations)
{
	if(dimension == OR_METHOD3DOD_DIMENSIONS)
	{
		if(usePredefinedODMatrixOperations)
		{
			firstReferenceInPrimitivesReferenceListGlobal = firstReferenceInPrimitivesReferenceList;
			glutDisplayFunc(draw3DTrisPrimitivesReferenceListToOpenGLWithPredefinedMatrixOperations);
		}
		else
		{
			firstReferenceInPrimitivesReferenceListGlobal = firstReferenceInPrimitivesReferenceList;
			glutDisplayFunc(draw3DTrisPrimitivesReferenceListToOpenGL);
		}
	}
	else if(dimension == OR_METHOD2DOD_DIMENSIONS)
	{
		if(usePredefinedODMatrixOperations)
		{
			firstReferenceInPrimitivesReferenceListGlobal = firstReferenceInPrimitivesReferenceList;
			glutDisplayFunc(draw2DQuadsPrimitivesReferenceListToOpenGLWithPredefinedMatrixOperations);
		}
		else
		{
			firstReferenceInPrimitivesReferenceListGlobal = firstReferenceInPrimitivesReferenceList;
			glutDisplayFunc(draw2DQuadsPrimitivesReferenceListToOpenGL);
		}
	}
	else
	{
		cout << "dimension = " << dimension << endl;
		cout << "Error: illegal number dimensions" << endl;
		exit(0);
	}

	glutMainLoopEvent();

	//cout << "h4" << endl;
}



void drawPrimitivesReferenceListToOpenGLAndCreateRGBMapBasic(Reference * firstReferenceInPrimitivesReferenceList, int width, int height, unsigned char * rgbMap)
{
	firstReferenceInPrimitivesReferenceListGlobal = firstReferenceInPrimitivesReferenceList;

	glutDisplayFunc(draw3DPrimitivesReferenceListToOpenGLwithRecursion);

	glutMainLoopEvent();

	writeScreenToRGBMap(width, height, rgbMap);

	glutPostRedisplay();

	//cout << "h4" << endl;
}

void updateScreen()
{
	glutPostRedisplay();

	//cout << "h4" << endl;
}




/*
void setViewPort(double width, double height, double xCentre, double yCentre)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(xCentre, yCentre, width, height);

}
*/

void setViewPort2DOrtho(double left, double right, double bottom, double top)
{
	glMatrixMode(GL_PROJECTION);		//shouldnt this be modelview???
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

double maxDouble2(double float1, double float2)
{
	if(float1 > float2)
	{
		return float1;
	}
	else
	{
		return float2;
	}
}


void setViewPort3DDynamic(vec * eyeFacingPoly, vec * viewatFacingPoly, vec * viewupFacingPoly, vec * viewportWidthHeightDepth)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	double viewportWidth = maxDouble2(viewportWidthHeightDepth->x, viewportWidthHeightDepth->y) * 20.0;
	double viewportHeight = maxDouble2(viewportWidthHeightDepth->x, viewportWidthHeightDepth->y) * 20.0;
	glOrtho(-(viewportWidth)/2.0, (viewportWidth)/2.0, -(viewportHeight)/2.0, (viewportHeight)/2.0, -100, 100);

	gluLookAt(eyeFacingPoly->x, eyeFacingPoly->y, eyeFacingPoly->z, viewatFacingPoly->x, viewatFacingPoly->y, viewatFacingPoly->z, viewupFacingPoly->x, viewupFacingPoly->y, viewupFacingPoly->z);

}

void setViewPort3DBasic()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -5.0, 5.0);

}

void setViewPort3DOrtho(double left, double right, double bottom, double top, double back, double forward)
{
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glMatrixMode(GL_PROJECTION);		//shouldnt this be modelview???
	glLoadIdentity();

	glOrtho(left, right, bottom, top, back, forward);

}

void setViewPort3D(vec * eyeFacingPoly, vec * viewatFacingPoly, vec * viewupFacingPoly, vec * viewportWidthHeightDepth)
{
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glMatrixMode(GL_PROJECTION);		//shouldnt this be modelview???
	glLoadIdentity();

	glOrtho(-(viewportWidthHeightDepth->x)/2.0, (viewportWidthHeightDepth->x)/2.0, -(viewportWidthHeightDepth->y)/2.0, (viewportWidthHeightDepth->y)/2.0, -(viewportWidthHeightDepth->z)/2.0, (viewportWidthHeightDepth->z)/2.0);

	gluLookAt(eyeFacingPoly->x, eyeFacingPoly->y, eyeFacingPoly->z, viewatFacingPoly->x, viewatFacingPoly->y, viewatFacingPoly->z, viewupFacingPoly->x, viewupFacingPoly->y, viewupFacingPoly->z);

}






int initiateOpenGL(int width, int height, int windowPositionX, int windowPositionY, bool confidentialWarnings)
{
	int argc =0;
	glutInit(&argc, NULL);	//&argc, argv
	if(LD_OPENGL_PRINT_ALGORITHM_PROGRESS)
	{
		cout << "glut initialised" << endl;
	}
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	
	glutInitWindowPosition(windowPositionX, windowPositionY);
	glutInitWindowSize(width, height);
	if(confidentialWarnings)
	{
		glutCreateWindow("Generating...");
	}
	else
	{
		glutCreateWindow("BAI OpenGL Hardware Acceleration");
	}
	glEnable(GL_DEPTH_TEST);

	return 1;

}


#endif

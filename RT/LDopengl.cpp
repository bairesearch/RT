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
 * File Name: LDopengl.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3i19d 15-December-2016
 *
 *******************************************************************************/


#include "LDopengl.h"

//#include <GL/gl.h>
//#include <GL/glut.h>
#include <GL/freeglut.h>	//need to use freeglut as it contains extensions functions which glut does not have; glutMainLoopEvent()


#ifdef USE_LD_ABSOLUTE_COLOUR

mat opengl2DmultiplicationMatrix;
double opengl2DmatrixTransformation1ScaleFactor = 0.0;
double opengl2DmatrixTransformation2iRotationFactor = 0.0;
double opengl2DmatrixTransformation2iiRotationFactor = 0.0;
double opengl2DmatrixTransformation3aScaleFactor = 0.0;
double opengl2DmatrixTransformation4aShearFactor = 0.0;
double opengl2DmatrixTransformation5aTranslationFactorX = 0.0;
double opengl2DmatrixTransformation5aTranslationFactorY = 0.0;

mat opengl3DmultiplicationMatrix;
double opengl3DmatrixTransformation1aXRotationFactor = 0.0;
double opengl3DmatrixTransformation1bYRotationFactor = 0.0;
double opengl3DmatrixTransformation2iZRotationFactor = 0.0;
double opengl3DmatrixTransformation2iiZRotationFactor = 0.0;
double opengl3DmatrixTransformation3TranslationFactorX = 0.0;
double opengl3DmatrixTransformation3TranslationFactorY = 0.0;
double opengl3DmatrixTransformation3TranslationFactorZ = 0.0;


//these can no longer be configured dynamically through ORrules.xml
static bool LD_OPENGL_PRINT_ALGORITHM_AND_TIME_DETAILS_ALL = false;
static bool LD_OPENGL_PRINT_ALGORITHM_AND_TIME_DETAILS = false;
static bool LD_OPENGL_PRINT_ALGORITHM_PROGRESS = false;


const LDreference* firstReferenceInPrimitivesReferenceListGlobal;



bool initiateOpenGL(int width, int height, int windowPositionX, int windowPositionY, bool confidentialWarnings)
{
	bool result = true;

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

	return result;

}

bool exitOpenGL()
{
	bool result = true;

	glutDestroyWindow(glutGetWindow());

	/*
	Attempt to work around Sourceforge freeglut bug #206: apply freeglut patch instead
	#ifdef FREEGLUT_MUST_ENTER_MAINLOOP
	//glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	//glutSetOption(GLUT_ACTION_GLUTMAINLOOP_RETURNS, GLUT_ACTION_CONTINUE_EXECUTION)
	glutMainLoop();	//required for ATI only? - sourceforge Freeglut bug #206
	glutLeaveMainLoop();
	#endif
	*/

	return result;
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

void setViewPort2Dortho(double left, double right, double bottom, double top)
{
	glMatrixMode(GL_PROJECTION);		//shouldnt this be modelview???
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

void setViewPort3D(vec* eyeFacingPoly, vec* viewAtFacingPoly, vec* viewUpFacingPoly, vec* viewPortWidthHeightDepth)
{
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glMatrixMode(GL_PROJECTION);		//shouldnt this be modelview???
	glLoadIdentity();

	glOrtho(-(viewPortWidthHeightDepth->x)/2.0, (viewPortWidthHeightDepth->x)/2.0, -(viewPortWidthHeightDepth->y)/2.0, (viewPortWidthHeightDepth->y)/2.0, -(viewPortWidthHeightDepth->z)/2.0, (viewPortWidthHeightDepth->z)/2.0);

	gluLookAt(eyeFacingPoly->x, eyeFacingPoly->y, eyeFacingPoly->z, viewAtFacingPoly->x, viewAtFacingPoly->y, viewAtFacingPoly->z, viewUpFacingPoly->x, viewUpFacingPoly->y, viewUpFacingPoly->z);

}

void setViewPort3Ddynamic(vec* eyeFacingPoly, vec* viewAtFacingPoly, vec* viewUpFacingPoly, vec* viewPortWidthHeightDepth)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	double viewportWidth = maxDouble2(viewPortWidthHeightDepth->x, viewPortWidthHeightDepth->y)* 20.0;
	double viewportHeight = maxDouble2(viewPortWidthHeightDepth->x, viewPortWidthHeightDepth->y)* 20.0;
	glOrtho(-(viewportWidth)/2.0, (viewportWidth)/2.0, -(viewportHeight)/2.0, (viewportHeight)/2.0, -100, 100);

	gluLookAt(eyeFacingPoly->x, eyeFacingPoly->y, eyeFacingPoly->z, viewAtFacingPoly->x, viewAtFacingPoly->y, viewAtFacingPoly->z, viewUpFacingPoly->x, viewUpFacingPoly->y, viewUpFacingPoly->z);

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

void setViewPort3Dbasic()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -5.0, 5.0);

}

void setViewPort3Dortho(double left, double right, double bottom, double top, double back, double forward)
{
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glMatrixMode(GL_PROJECTION);		//shouldnt this be modelview???
	glLoadIdentity();

	glOrtho(left, right, bottom, top, back, forward);

}










void drawPrimitivesReferenceListToOpenGLandCreateRGBmap(const LDreference* firstReferenceInPrimitivesReferenceList, int width, int height, unsigned char* rgbMap, int dimension, bool usePredefinedODmatrixOperations)
{
	if(dimension == OR_METHOD3DOD_DIMENSIONS)
	{
		if(usePredefinedODmatrixOperations)
		{
			firstReferenceInPrimitivesReferenceListGlobal = firstReferenceInPrimitivesReferenceList;
			glutDisplayFunc(draw3DtrisPrimitivesReferenceListToOpenGLwithPredefinedMatrixOperations);
		}
		else
		{
			firstReferenceInPrimitivesReferenceListGlobal = firstReferenceInPrimitivesReferenceList;
			glutDisplayFunc(draw3DtrisPrimitivesReferenceListToOpenGL);
		}
	}
	else if(dimension == OR_METHOD2DOD_DIMENSIONS)
	{
		if(usePredefinedODmatrixOperations)
		{
			firstReferenceInPrimitivesReferenceListGlobal = firstReferenceInPrimitivesReferenceList;
			glutDisplayFunc(draw2DquadsPrimitivesReferenceListToOpenGLwithPredefinedMatrixOperations);
		}
		else
		{
			firstReferenceInPrimitivesReferenceListGlobal = firstReferenceInPrimitivesReferenceList;
			glutDisplayFunc(draw2DquadsPrimitivesReferenceListToOpenGL);
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
}

void drawPrimitivesReferenceListToOpenGL(const LDreference* firstReferenceInPrimitivesReferenceList, int dimension, bool usePredefinedODmatrixOperations)
{
	if(dimension == OR_METHOD3DOD_DIMENSIONS)
	{
		if(usePredefinedODmatrixOperations)
		{
			firstReferenceInPrimitivesReferenceListGlobal = firstReferenceInPrimitivesReferenceList;
			glutDisplayFunc(draw3DtrisPrimitivesReferenceListToOpenGLwithPredefinedMatrixOperations);
		}
		else
		{
			firstReferenceInPrimitivesReferenceListGlobal = firstReferenceInPrimitivesReferenceList;
			glutDisplayFunc(draw3DtrisPrimitivesReferenceListToOpenGL);
		}
	}
	else if(dimension == OR_METHOD2DOD_DIMENSIONS)
	{
		if(usePredefinedODmatrixOperations)
		{
			firstReferenceInPrimitivesReferenceListGlobal = firstReferenceInPrimitivesReferenceList;
			glutDisplayFunc(draw2DquadsPrimitivesReferenceListToOpenGLwithPredefinedMatrixOperations);
		}
		else
		{
			firstReferenceInPrimitivesReferenceListGlobal = firstReferenceInPrimitivesReferenceList;
			glutDisplayFunc(draw2DquadsPrimitivesReferenceListToOpenGL);
		}
	}
	else
	{
		cout << "dimension = " << dimension << endl;
		cout << "Error: illegal number dimensions" << endl;
		exit(0);
	}

	glutMainLoopEvent();
}

static void draw2DquadsPrimitivesReferenceListToOpenGL()
{
	glClearColor(OPEN_GL_BACKGROUND_COLOUR_R,OPEN_GL_BACKGROUND_COLOUR_G,OPEN_GL_BACKGROUND_COLOUR_B,0.0);	//use black background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	glBegin(GL_QUADS);


	const LDreference* currentReference = firstReferenceInPrimitivesReferenceListGlobal;
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
		}

		currentReference = currentReference->next;
	}

	glEnd();

	glPopMatrix();

	glFlush();
}


static void draw2DquadsPrimitivesReferenceListToOpenGLwithPredefinedMatrixOperations()
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

	glClearColor(OPEN_GL_BACKGROUND_COLOUR_R,OPEN_GL_BACKGROUND_COLOUR_G,OPEN_GL_BACKGROUND_COLOUR_B,0.0);	//use black background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	#ifdef USE_OPENGL_PREDEFINED_OD_MATRIX_OPERATIONS_ADV

		glTranslatef(opengl2DmatrixTransformation5aTranslationFactorX, opengl2DmatrixTransformation5aTranslationFactorY, 0.0);

	GLfloat m[] =
		{(GLfloat)opengl2DmultiplicationMatrix.a.x, (GLfloat)opengl2DmultiplicationMatrix.a.y, (GLfloat)opengl2DmultiplicationMatrix.a.z, 0.0,
		(GLfloat)opengl2DmultiplicationMatrix.b.x, (GLfloat)opengl2DmultiplicationMatrix.b.y, (GLfloat)opengl2DmultiplicationMatrix.b.z, 0.0,
		(GLfloat)opengl2DmultiplicationMatrix.c.x, (GLfloat)opengl2DmultiplicationMatrix.c.y, (GLfloat)opengl2DmultiplicationMatrix.c.z, 0.0,
		0.0, 0.0, 0.0, 1.0 };
		glMultMatrixf(m);

		/*
		glTranslatef(opengl2DmatrixTransformation5aTranslationFactorX, opengl2DmatrixTransformation5aTranslationFactorY, 0.0);
		shearMatrix(opengl2DmatrixTransformation4aShearFactor, 0.0);
		glScalef(opengl2DmatrixTransformation3aScaleFactor, opengl2DmatrixTransformation3aScaleFactor, opengl2DmatrixTransformation3aScaleFactor);
		glRotatef(opengl2DmatrixTransformation2iiRotationFactor/PI*180.0, 0.0, 0.0, 1.0f);
		glRotatef(opengl2DmatrixTransformation2iRotationFactor/PI*180.0, 0.0, 0.0, 1.0f);
		glScalef(opengl2DmatrixTransformation1ScaleFactor, opengl2DmatrixTransformation1ScaleFactor, opengl2DmatrixTransformation1ScaleFactor);
		*/

	#else
		glTranslatef(opengl2DmatrixTransformation5aTranslationFactorX, opengl2DmatrixTransformation5aTranslationFactorY, 0.0);

		shearMatrix(opengl2DmatrixTransformation4aShearFactor, 0.0);
		glScalef(opengl2DmatrixTransformation3aScaleFactor, opengl2DmatrixTransformation3aScaleFactor, opengl2DmatrixTransformation3aScaleFactor);
		glRotatef(opengl2DmatrixTransformation2iiRotationFactor/PI*180.0, 0.0, 0.0, 1.0f);
		glRotatef(opengl2DmatrixTransformation2iRotationFactor/PI*180.0, 0.0, 0.0, 1.0f);
		glScalef(opengl2DmatrixTransformation1ScaleFactor, opengl2DmatrixTransformation1ScaleFactor, opengl2DmatrixTransformation1ScaleFactor);

	#endif



	glBegin(GL_QUADS);


	const LDreference* currentReference = firstReferenceInPrimitivesReferenceListGlobal;
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
}


static void draw3DtrisPrimitivesReferenceListToOpenGL()
{
	glClearColor(OPEN_GL_BACKGROUND_COLOUR_R,OPEN_GL_BACKGROUND_COLOUR_G,OPEN_GL_BACKGROUND_COLOUR_B,0.0);	//use black background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);

	/*
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	*/


	glBegin(GL_TRIANGLES);

	const LDreference* currentReference = firstReferenceInPrimitivesReferenceListGlobal;
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
static void draw3DtrisPrimitivesReferenceListToOpenGLwithPredefinedMatrixOperations()
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

	glClearColor(OPEN_GL_BACKGROUND_COLOUR_R,OPEN_GL_BACKGROUND_COLOUR_G,OPEN_GL_BACKGROUND_COLOUR_B,0.0);	//use black background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();



	#ifdef USE_OPENGL_PREDEFINED_OD_MATRIX_OPERATIONS_ADV

		glTranslatef(opengl3DmatrixTransformation3TranslationFactorX, opengl3DmatrixTransformation3TranslationFactorY, opengl3DmatrixTransformation3TranslationFactorZ);

	GLfloat m[] =
		{(GLfloat)opengl3DmultiplicationMatrix.a.x, (GLfloat)opengl3DmultiplicationMatrix.a.y, (GLfloat)opengl3DmultiplicationMatrix.a.z, 0.0,
		(GLfloat)opengl3DmultiplicationMatrix.b.x, (GLfloat)opengl3DmultiplicationMatrix.b.y, (GLfloat)opengl3DmultiplicationMatrix.b.z, 0.0,
		(GLfloat)opengl3DmultiplicationMatrix.c.x, (GLfloat)opengl3DmultiplicationMatrix.c.y, (GLfloat)opengl3DmultiplicationMatrix.c.z, 0.0,
		0.0, 0.0, 0.0, 1.0 };
		glMultMatrixf(m);

	#else
		glTranslatef(opengl3DmatrixTransformation3TranslationFactorX, opengl3DmatrixTransformation3TranslationFactorY, opengl3DmatrixTransformation3TranslationFactorZ);
		glRotatef(opengl3DmatrixTransformation2iiZRotationFactor/PI*180.0, 0.0, 0.0, 1.0f);
		glRotatef(opengl3DmatrixTransformation2iZRotationFactor/PI*180.0, 0.0, 0.0, 1.0f);
		glRotatef(opengl3DmatrixTransformation1bYRotationFactor/PI*180.0, 0.0, 1.0f, 0.0);
		glRotatef(opengl3DmatrixTransformation1aXRotationFactor/PI*180.0, 1.0f, 0.0, 0.0);


	#endif


	glBegin(GL_TRIANGLES);

	const LDreference* currentReference = firstReferenceInPrimitivesReferenceListGlobal;
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
}











void drawPrimitivesReferenceListToOpenGLandCreateRGBmapBasic(const LDreference* firstReferenceInPrimitivesReferenceList, int width, int height, unsigned char* rgbMap)
{
	firstReferenceInPrimitivesReferenceListGlobal = firstReferenceInPrimitivesReferenceList;

	glutDisplayFunc(draw3DprimitivesReferenceListToOpenGLwithRecursion);

	glutMainLoopEvent();

	writeScreenToRGBMap(width, height, rgbMap);

	glutPostRedisplay();
}

static void draw3DprimitivesReferenceListToOpenGLwithRecursion()
{
	glClearColor(OPEN_GL_BACKGROUND_COLOUR_R,OPEN_GL_BACKGROUND_COLOUR_G,OPEN_GL_BACKGROUND_COLOUR_B,0.0);	//use white background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	draw3DprimitivesReferenceListToOpenGLrecurse(firstReferenceInPrimitivesReferenceListGlobal);


	glPopMatrix();

	glFlush();
}


static void draw3DprimitivesReferenceListToOpenGLrecurse(const LDreference* firstReferenceInLayer)
{
	const LDreference* currentReference = firstReferenceInLayer;
	while(currentReference->next != NULL)
	{

		if(currentReference->isSubModelReference)
		{
			draw3DprimitivesReferenceListToOpenGLrecurse(currentReference->firstReferenceWithinSubModel);
		}
		else
		{
		/*
		if(currentReference->referenceEnabledMethod2DOD)
		{
		*/
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
		/*
		}
		*/

		}

		currentReference = currentReference->next;
	}
}
















static void draw3DprimitivesReferenceListToOpenGL()
{
	glClearColor(OPEN_GL_BACKGROUND_COLOUR_R,OPEN_GL_BACKGROUND_COLOUR_G,OPEN_GL_BACKGROUND_COLOUR_B,0.0);	//use black background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	const LDreference* currentReference = firstReferenceInPrimitivesReferenceListGlobal;
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

static void draw2DPrimitivesReferenceListToOpenGLSingleLayer()
{
	glClearColor(OPEN_GL_BACKGROUND_COLOUR_R,OPEN_GL_BACKGROUND_COLOUR_G,OPEN_GL_BACKGROUND_COLOUR_B,0.0);	//use black background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();


	const LDreference* currentReference = firstReferenceInPrimitivesReferenceListGlobal;
	while(currentReference->next != NULL)
	{
		/*
		if(currentReference->referenceEnabledMethod2DOD)
		{
		*/

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
				glBegin(GL_QUADS);
					glColor3f(r,g,b);
					glVertex2f(currentReference->vertex1absolutePosition.x,currentReference->vertex1absolutePosition.y);
					glVertex2f(currentReference->vertex2absolutePosition.x,currentReference->vertex2absolutePosition.y);
					glVertex2f(currentReference->vertex3absolutePosition.x,currentReference->vertex3absolutePosition.y);
					glVertex2f(currentReference->vertex4absolutePosition.x,currentReference->vertex4absolutePosition.y);
				glEnd();
			}
		/*
		}
		*/

		currentReference = currentReference->next;
	}

	glPopMatrix();

	glFlush();
}




















void writeScreenToRGBMap(int width, int height, unsigned char* rgbMap)
{
	const int bytesPerPixel = 3;	// RGB
	const int imageSizeInBytes = bytesPerPixel* width* height;

	unsigned char* pixels = new unsigned char[imageSizeInBytes];

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

	//unsigned char* rgbMap = new unsigned char[imageSizeInBytes];

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

			rgbMap[y*width*RGB_NUM + x*RGB_NUM + RGB_RED] = pixels[(bytesPerPixel)* (oldx + oldy* width) + RGB_RED];
			rgbMap[y*width*RGB_NUM + x*RGB_NUM + RGB_GREEN] = pixels[(bytesPerPixel)* (oldx + oldy* width) + RGB_GREEN];
			rgbMap[y*width*RGB_NUM + x*RGB_NUM + RGB_BLUE] = pixels[(bytesPerPixel)* (oldx + oldy* width) + RGB_BLUE];

		}
	}

	delete pixels;


}

void writeScreenToDepthMap(int width, int height, double* depthMap)
{
	GLfloat* pixels = new GLfloat[width* height];
	//GLuint* pixels = new GLuint[width* height];

	/*
	glPixelStorei(GL_PACK_ROW_LENGTH, width);
	int rowSkip = 0;
	int pixelSkip = 0;
	glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_PACK_SKIP_ROWS, 0);
	glReadPixels(pixelSkip, rowSkip, width, height, GL_DEPTH_COMPONENT, GL_FLOAT, pixels);
	*/

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

			depthMap[y*width + x] = (pixels[oldx + (oldy* width)]);
			//depthMap[y*width + x] = ((double)(pixels[oldx + (oldy* width)]))/((double)(sizeof(GL_UNSIGNED_INT)));

			#ifdef FIX_OPENGL_3DOD_TIMING_BUG
			if(depthMap[y*width + x] > 0)
			{
				#ifdef LD_DEBUG
				//cout << "depthMap[" << y << "*width + " << x << "] = " << depthMap[y*width + x] << endl;
				#endif
				cout << depthMap[y*width + x] << endl;
			}
			#endif
		}
	}

	delete pixels;


}

void updateScreen()
{
	glutPostRedisplay();
}



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










#endif

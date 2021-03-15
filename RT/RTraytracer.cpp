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
 * File Name: RTraytracer.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2021 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3p1a 15-March-2021
 * Description: contains methods to raytrace a primitive through a given point (x, y)
 *              on the screen with the given RTsceneInfo structure and accompanying
 *              perspective information.
 * /
 *******************************************************************************/


#include "RTraytracer.hpp"

#define VERTEX 0
#define VECTOR 1
#define TRUE 1
#define FALSE 0
#define ZERO 0.0
#define MISS 0.0
#define ONE 1.0
#define CALCULATE_NORMAL 1
#define CALCULATE_TIN 0
#define ROUND_OFF 0.0000000000001

#define CYLINDER_ARRAY_SIZE 4
#define SPHERE_ARRAY_SIZE 2


#define HEIGHT_OF_BRICK 1.2 /*6/5*/
#define HEIGHT_OF_PLATE 0.4
#define HEIGHT_OF_TILE 0.4
#define HEIGHT_OF_BASEPLATE 0.133333333
#define STUD_HEIGHT 0.2125 /*17/80*/ /*or NILL if baseplate*/
#define STUDGAP 0.375 /*3/8*/
#define STUDTOSTUDSPACING 1.0
#define STUDDIAMETER 0.625 /*5/8*/
#define HALFSTUDGAP 0.1875 /*3/16*/
#define CEILING THICKNESS 0.1875 /*3/16 OR ..*/
#define STUDDIAM 0.625 /*5/8*/
#define WALLTHICKNESS 0.1875 /*3/16 (NILL IF BASEPLATE)*/
#define OUTERCYLINDERDIAMETER 0.789 /*(NILL IF BASEPLATE)*/
#define INSIDEOFSTUDDIAMETER 0.25 /* 1/4*/
#define INNERCYLINDERDIAMETER 0.625 /*5/8 (NILL IF BASEPLATE)*/
#define WALLTOINSTUD 0.1875 /*3/16 (NILL IF BASEPLATE)[SHOULD BE CALLED INCYLINDER NOT INSTUD]*/
#define WALLTOCYLINDER 0.125 /*1/8 (NILL IF BASEPLATE)*/
#define CYLINDERTOCYLINDER 1.0 /* (NILL IF BASEPLATE)*/
#define CUBE 1
#define CYLINDER 2

RTsceneInfo::RTsceneInfo(void)
{
	nextScene = NULL;
}

RTsceneInfo::~RTsceneInfo(void)
{
	delete nextScene;
}


void RTraytracerClass::rayTrace(const RTviewInfo* vi, RTsceneInfo* si, mat* tildaMat, vec* uvn)
{
	advancedMat finalReverseMatrix;
	advancedMat relevantFinalReverseMatrix;

	/*used for object (eg stud) translation/scaling*/
	advancedMat inverseTranslationMatrix;
	advancedMat inverseScaleMatrix;
	advancedVec tmpAvancedVector;
	advancedMat tmpAdvancedMatrix;	/*used for matrix manipulation*/
	advancedMat tmpAdvancedMatrix2;/*used for matrix manipulation*/
	advancedMat tmpAdvancedMatrix3;/*used for matrix manipulation*/
	advancedMat tempObjectReverseMatrix;
	advancedMat objectReverseMatrix;

	/*translation and scaling is done before rotation*/
	double scalex;
	double scaley;
	double scalez;
	double transx;
	double transy;
	double transz;

	int tempType = 0;
	double tInOutDash[2];
	int across;
	int up;

	vec p;
	vec n;

	advancedVec p0advanced;
	advancedVec p1advanced;
	vec tmp_structure;		/*used for vector manipulation*/
	vec p0_structure;
	vec p1_structure;
	vec* tmp = &tmp_structure;	/*used for vector manipulation*/
	vec* p0 = &p0_structure;
	vec* p1 = &p1_structure;

	advancedVec p0dashadvanced;
	advancedVec p1dashadvanced;
	vec p0dash_structure;
	vec p1dash_structure;
	vec* p0Dash = &p0dash_structure;
	vec* p1Dash = &p1dash_structure;


	/*creating eye and direction*/

	/*p0 = &(vi->eye);
	  p1 = [uTilda vTilda nTilda][uvn] + eye*/
	*p0 = vi->eye;
	SHAREDvector.multMatrixByVector(tildaMat, uvn, tmp);
	SHAREDvector.addVectorsRT(tmp, p0, p1);




	/*************************************************/
	/*BASIC raytrace routine...*/
	/*************************************************/


	/*setting initial current tInOut times. only tInOut[0] is important for this basic routine*/

	tInOutDash[0] = -1;
	tInOutDash[1] = -1;


	scalex = (double)si->di.width;
	scaley = (double)si->di.length;

	/*calculate brick objects default height*/
	if(si->pi.type == BRICK)
	{
		scalez = HEIGHT_OF_BRICK;
	}
	else if(si->pi.type == PLATE)
	{
		scalez = HEIGHT_OF_PLATE;
	}
	else if(si->pi.type == TILE)
	{
		scalez = HEIGHT_OF_TILE;
	}
	else if(si->pi.type == BASEPLATE)
	{
		scalez = HEIGHT_OF_BASEPLATE;
	}
	else if((si->pi.type == RECT_PRISM) || (si->pi.type == CYLINDER) || (si->pi.type == SPHERE))
	{
		//printf("ass");
		scalez = (double)si->di.height;
	}
	else if((si->pi.type == PRIM_QUAD) || (si->pi.type == PRIM_TRI) || (si->pi.type == PRIM_LINE))
	{
		scalez = ONE;
		scalex = ONE;
		scaley = ONE;
	}
	else
	{
		cerr << "CYLINDER = " << CYLINDER << endl;
		cerr << "si->pi.type = " << si->pi.type << endl;
		cerr << "error: part type unknown 1" << endl;
		exit(EXIT_ERROR);
	}

#ifdef RT_CONVERT_LDR_OBJECT_TRANSLATION_PROPERLY
	transx = -scalex/2.0;
	transy = -scaley/2.0;
	transz = -scalez/2.0;
#else
	transx = ZERO;
	transy = ZERO;
	transz = ZERO;
#endif

	RToperations.createInverseScaleMatrix(scalex, scaley, scalez, &inverseScaleMatrix);
	RToperations.createInverseTranslationMatrix(transx, transy, transz, &inverseTranslationMatrix);
	RToperations.multAdvancedMatrix(&inverseScaleMatrix, &inverseTranslationMatrix, &objectReverseMatrix);
	RToperations.multAdvancedMatrix(&objectReverseMatrix, &(si->reverseMatrix), &finalReverseMatrix);


	RToperations.toAdvancedVector(p0, VECTOR, &p0advanced);
	RToperations.toAdvancedVector(p1, VECTOR, &p1advanced);
	RToperations.multAdvancedMatrixByVector(&p0advanced, &finalReverseMatrix, &tmpAvancedVector);
	p0dashadvanced = tmpAvancedVector;
	RToperations.multAdvancedMatrixByVector(&p1advanced, &finalReverseMatrix, &tmpAvancedVector);
	p1dashadvanced = tmpAvancedVector;
	RToperations.fromAdvancedVector(&p0dashadvanced, p0Dash);
	RToperations.fromAdvancedVector(&p1dashadvanced, p1Dash);


	vec norm;	//require to fill in normal information while calculating object - used to draw point at later stage
	norm.x = 0;
	norm.y = 0;
	norm.z = 0;



	if((si->pi.type == BRICK) || (si->pi.type == PLATE) || (si->pi.type == TILE) || (si->pi.type == BASEPLATE) || (si->pi.type == RECT_PRISM))
	{
		calculateCube(p0Dash, p1Dash, tInOutDash, &norm, &finalReverseMatrix, &relevantFinalReverseMatrix);
	}
	else if(si->pi.type == CYLINDER)
	{
		calculateCylinder(p0Dash, p1Dash, tInOutDash, &norm, &finalReverseMatrix, &relevantFinalReverseMatrix);
	}
	else if(si->pi.type == SPHERE)
	{
		calculateSphere(p0Dash, p1Dash, tInOutDash, &norm, &finalReverseMatrix, &relevantFinalReverseMatrix);
			//do: ?proper order of tInOutDash in calculateSphere [ie split up into calc then draw]
	}
	else if(si->pi.type == PRIM_QUAD)
	{
		calculatePrimQuad(p0Dash, p1Dash, tInOutDash, &(si->pi), &norm, &finalReverseMatrix, &relevantFinalReverseMatrix);
	}
	else if(si->pi.type == PRIM_TRI)
	{
		calculatePrimTri(p0Dash, p1Dash, tInOutDash, &(si->pi), &norm, &finalReverseMatrix, &relevantFinalReverseMatrix);
	}
	else if(si->pi.type == PRIM_LINE)
	{
		calculatePrimLine(p0Dash, p1Dash, tInOutDash, &(si->pi), &norm, &finalReverseMatrix, &relevantFinalReverseMatrix);
	}
	else
	{
		cerr << "si->pi.type = " << si->pi.type << endl;
		cerr << "error: part type unknown 2" << endl;
		exit(EXIT_ERROR);
	}

	/*add tins, touts to tree...*/

	if(tInOutDash[0] < 0)
	{
		si -> tIn = RT_RAYTRACE_NO_HIT_DEPTH_T;
		si -> tOut = 0.0;
		SHAREDvector.createVector(&p);
		p.x = RT_RAYTRACE_NO_HIT_POINT_X;
		p.y = RT_RAYTRACE_NO_HIT_POINT_Y;
		p.z = RT_RAYTRACE_NO_HIT_POINT_Z;
		si -> p = p;
		SHAREDvector.createVector(&n);
		si -> n = n;
	}
	else
	{/*finally calculates point and normal*/

		if((si->pi.type == BRICK) || (si->pi.type == PLATE) || (si->pi.type == TILE) || (si->pi.type == BASEPLATE) || (si->pi.type == RECT_PRISM))
		{
			#ifndef RT_T_TRANSFORM_TEST
			drawPoint(si, &relevantFinalReverseMatrix, tInOutDash[0], tInOutDash[1], p0Dash, p1Dash, &norm);
			#else
			//drawPointTest(si, &relevantFinalReverseMatrix, tInOutDash[0], tInOutDash[1], p0Dash, p1Dash, &norm, p0, p1);
			#endif
		}
		else if(si->pi.type == CYLINDER)
		{
			#ifndef RT_T_TRANSFORM_TEST
			drawPoint(si, &relevantFinalReverseMatrix, tInOutDash[0], tInOutDash[1], p0Dash, p1Dash, &norm);
			#else
			//drawPointTest(si, &relevantFinalReverseMatrix, tInOutDash[0], tInOutDash[1], p0Dash, p1Dash, &norm, p0, p1);
			#endif
		}
		else if(si->pi.type == SPHERE)
		{
			#ifndef RT_T_TRANSFORM_TEST
			drawPoint(si, &relevantFinalReverseMatrix, tInOutDash[0], tInOutDash[1], p0Dash, p1Dash, &norm);
			#else
			//drawPointTest(si, &relevantFinalReverseMatrix, tInOutDash[0], tInOutDash[1], p0Dash, p1Dash, &norm, p0, p1);
			#endif
		}
		else if(si->pi.type == PRIM_QUAD)
		{
			#ifndef RT_T_TRANSFORM_TEST
			drawPoint(si, &relevantFinalReverseMatrix, tInOutDash[0], tInOutDash[1], p0Dash, p1Dash, &norm);
			#else
			drawPointTest(si, &relevantFinalReverseMatrix, tInOutDash[0], tInOutDash[1], p0Dash, p1Dash, &norm, p0, p1);
			#endif
		}
		else if(si->pi.type == PRIM_TRI)
		{
			#ifndef RT_T_TRANSFORM_TEST
			drawPoint(si, &relevantFinalReverseMatrix, tInOutDash[0], tInOutDash[1], p0Dash, p1Dash, &norm);
			#else
			//drawPointTest(si, &relevantFinalReverseMatrix, tInOutDash[0], tInOutDash[1], p0Dash, p1Dash, &norm, p0, p1);
			#endif
		}
		else if(si->pi.type == PRIM_LINE)
		{
			#ifndef RT_T_TRANSFORM_TEST
			drawPointNoLighting(si, &relevantFinalReverseMatrix, tInOutDash[0], tInOutDash[1], p0Dash, p1Dash, &norm);
			#else
			//drawPointNoLighting(si, &relevantFinalReverseMatrix, tInOutDash[0], tInOutDash[1], p0Dash, p1Dash, &norm);
			#endif
		}
		else
		{
			cerr << "si->pi.type = " << si->pi.type << endl;
			cerr << "error: part type unknown 3" << endl;
			exit(EXIT_ERROR);

		}

	}
}



void RTraytracerClass::calculateCube(vec* p0, vec* p1, double* tInOut, vec* norm, advancedMat* finalReverseMatrix, advancedMat* relevantFinalReverseMatrix)
{
	vec pdash;
	vec tmp_structure;	/*used for vector manipulation*/
	vec tmp2_structure;	/*used for vector manipulation*/
	vec tmp3_structure;	/*used for vector manipulation*/
	vec* tmp = &tmp_structure;
	vec* tmp2 = &tmp2_structure;
	vec* tmp3 = &tmp3_structure;

	double tempTInOut[2];

	/*defining basic cube dimensions*/
	double CUBEXBOUNDARY1 = ZERO;
	double CUBEXBOUNDARY2 = ONE;
	double CUBEYBOUNDARY1 = ZERO;
	double CUBEYBOUNDARY2 = ONE;
	double CUBEZBOUNDARY1 = ZERO;
	double CUBEZBOUNDARY2 = ONE;

		/*used for normal calculations*/
	/*defining round offs for cube faces. h=high, l=low*/
	double CUBEXBOUNDARY1h = CUBEXBOUNDARY1 + ROUND_OFF;
	double CUBEXBOUNDARY1l = CUBEXBOUNDARY1 - ROUND_OFF;
	double CUBEXBOUNDARY2h = CUBEXBOUNDARY2 + ROUND_OFF;
	double CUBEXBOUNDARY2l = CUBEXBOUNDARY2 - ROUND_OFF;
	double CUBEYBOUNDARY1h = CUBEYBOUNDARY1 + ROUND_OFF;
	double CUBEYBOUNDARY1l = CUBEYBOUNDARY1 - ROUND_OFF;
	double CUBEYBOUNDARY2h = CUBEYBOUNDARY2 + ROUND_OFF;
	double CUBEYBOUNDARY2l = CUBEYBOUNDARY2 - ROUND_OFF;
	double CUBEZBOUNDARY1h = CUBEZBOUNDARY1 + ROUND_OFF;
	double CUBEZBOUNDARY1l = CUBEZBOUNDARY1 - ROUND_OFF;
	double CUBEZBOUNDARY2h = CUBEZBOUNDARY2 + ROUND_OFF;
	double CUBEZBOUNDARY2l = CUBEZBOUNDARY2 - ROUND_OFF;

	/*setting t calcluation values. set default to hit*/
	double denominator;
	int denominatorIsZero = FALSE;
	/*defining scalars*/
	double t, txin, txout, tyin, tyout, tzin, tzout, tin, tout;

	/*defining temporary variables*/
	double tmpd;

	#ifdef RT_METHOD2
	//new by rbb sept 08;
	int txinHits = FALSE;
	int txoutHits = FALSE;
	int tyinHits = FALSE;
	int tyoutHits = FALSE;
	int tzinHits = FALSE;
	int tzoutHits = FALSE;
	#endif

	/*
	To rayTrace, aim to calculate the point p, where the
	ray hits the object, where p = p0 + t(p1 - p0). So first
	must calculate a value for t.

	t calculations...

	sub in x=0, x=1 to find t in/out x values
	sub in y=0, y=1 to find t in/out y values
	sub in z=0, z=1 to find t in/out z values

	Note the denominator checks:
	if x1 - x0 is 0, the ray misses the interesection and
	no pixel will be coloured
	*/

	denominator = (p1->x) - (p0->x);
	if(denominator == 0)
	{
		denominatorIsZero = TRUE;
	}
	else
	{
		txin = (CUBEXBOUNDARY1 - p0->x)/denominator;
		txout = (CUBEXBOUNDARY2 - p0->x)/denominator;

		/*checks to see if the txin is > txout
		if so, the values of txin and txout are swapped*/

			//condition required when parts have been rotated, else flip is mandatory
		if(txin > txout)
		{
			tmpd = txout;
			txout = txin;
			txin = tmpd;
		}
		else
		{//txin < txout

			//nothing needed to be done
		}

	#ifdef RT_METHOD2
			//check if hits - (used later on only for SW diagnostics) - test2
		SHAREDvector.negativeVector(p0, tmp);
		SHAREDvector.addVectorsRT(p1, tmp, tmp2);

		SHAREDvector.multiplyVectorByScalarRT(tmp2, txin, tmp3);
		SHAREDvector.addVectorsRT(p0, tmp3, &pdash);

		txinHits = TRUE;
		if((pdash.x >= CUBEYBOUNDARY1l) && (pdash.x <= CUBEYBOUNDARY2h))
		{

		}
		else
		{
			txinHits = FALSE;
		}
		if((pdash.y >= CUBEYBOUNDARY1l) && (pdash.y <= CUBEYBOUNDARY2h))
		{

		}
		else
		{
			txinHits = FALSE;
		}
		if((pdash.z >= CUBEZBOUNDARY1l) && (pdash.z <= CUBEZBOUNDARY2h))
		{

		}
		else
		{
			txinHits = FALSE;
		}

		SHAREDvector.multiplyVectorByScalarRT(tmp2, txout, tmp3);
		SHAREDvector.addVectorsRT(p0, tmp3, &pdash);

		txoutHits = TRUE;
		if((pdash.x >= CUBEYBOUNDARY1l) && (pdash.x <= CUBEYBOUNDARY2h))
		{

		}
		else
		{
			txoutHits = FALSE;
		}
		if((pdash.y >= CUBEYBOUNDARY1l) && (pdash.y <= CUBEYBOUNDARY2h))
		{

		}
		else
		{
			txoutHits = FALSE;
		}
		if((pdash.z >= CUBEZBOUNDARY1l) && (pdash.z <= CUBEZBOUNDARY2h))
		{

		}
		else
		{
			txoutHits = FALSE;
		}
	#endif

	}

	denominator = (p1->y) - (p0->y);
	if(denominator == 0)
	{
		denominatorIsZero = TRUE;
	}
	else
	{
		tyin = (CUBEYBOUNDARY1 - p0->y)/denominator;
		tyout = (CUBEYBOUNDARY2 - p0->y)/denominator;

			//else flip is mandatory
		if(tyin > tyout)
		{
			tmpd = tyout;
			tyout = tyin;
			tyin = tmpd;
		}

	#ifdef RT_METHOD2
			//check if hits - (used later on only for SW diagnostics) - test2
		SHAREDvector.negativeVector(p0, tmp);
		SHAREDvector.addVectorsRT(p1, tmp, tmp2);

		SHAREDvector.multiplyVectorByScalarRT(tmp2, tyin, tmp3);
		SHAREDvector.addVectorsRT(p0, tmp3, &pdash);

		tyinHits = TRUE;
		if((pdash.x >= CUBEYBOUNDARY1l) && (pdash.x <= CUBEYBOUNDARY2h))
		{

		}
		else
		{
			tyinHits = FALSE;
		}
		if((pdash.y >= CUBEYBOUNDARY1l) && (pdash.y <= CUBEYBOUNDARY2h))
		{

		}
		else
		{
			tyinHits = FALSE;
		}
		if((pdash.z >= CUBEZBOUNDARY1l) && (pdash.z <= CUBEZBOUNDARY2h))
		{

		}
		else
		{
			tyinHits = FALSE;
		}

		SHAREDvector.multiplyVectorByScalarRT(tmp2, tyout, tmp3);
		SHAREDvector.addVectorsRT(p0, tmp3, &pdash);

		tyoutHits = TRUE;
		if((pdash.x >= CUBEYBOUNDARY1l) && (pdash.x <= CUBEYBOUNDARY2h))
		{

		}
		else
		{
			tyoutHits = FALSE;
		}
		if((pdash.y >= CUBEYBOUNDARY1l) && (pdash.y <= CUBEYBOUNDARY2h))
		{

		}
		else
		{
			tyoutHits = FALSE;
		}
		if((pdash.z >= CUBEZBOUNDARY1l) && (pdash.z <= CUBEZBOUNDARY2h))
		{

		}
		else
		{
			tyoutHits = FALSE;
		}
	#endif

	}

	denominator = (p1->z) - (p0->z);
	if(denominator == 0)
	{
		denominatorIsZero = TRUE;
	}
	else
	{
		tzin = (CUBEZBOUNDARY1 - p0->z)/denominator;
		tzout = (CUBEZBOUNDARY2 - p0->z)/denominator;

			//else flip is mandatory
		if(tzin > tzout)
		{
			tmpd = tzout;
			tzout = tzin;
			tzin = tmpd;

		}

	#ifdef RT_METHOD2
			//check if hits - (used later on only for SW diagnostics) - test2
		SHAREDvector.negativeVector(p0, tmp);
		SHAREDvector.addVectorsRT(p1, tmp, tmp2);

		SHAREDvector.multiplyVectorByScalarRT(tmp2, tzin, tmp3);
		SHAREDvector.addVectorsRT(p0, tmp3, &pdash);

		tzinHits = TRUE;
		if((pdash.x >= CUBEYBOUNDARY1l) && (pdash.x <= CUBEYBOUNDARY2h))
		{

		}
		else
		{
			tzinHits = FALSE;
		}
		if((pdash.y >= CUBEYBOUNDARY1l) && (pdash.y <= CUBEYBOUNDARY2h))
		{

		}
		else
		{
			tzinHits = FALSE;
		}
		if((pdash.z >= CUBEZBOUNDARY1l) && (pdash.z <= CUBEZBOUNDARY2h))
		{

		}
		else
		{
			tzinHits = FALSE;
		}

		SHAREDvector.multiplyVectorByScalarRT(tmp2, tzout, tmp3);
		SHAREDvector.addVectorsRT(p0, tmp3, &pdash);

		tzoutHits = TRUE;
		if((pdash.x >= CUBEYBOUNDARY1l) && (pdash.x <= CUBEYBOUNDARY2h))
		{

		}
		else
		{
			tzoutHits = FALSE;
		}
		if((pdash.y >= CUBEYBOUNDARY1l) && (pdash.y <= CUBEYBOUNDARY2h))
		{

		}
		else
		{
			tzoutHits = FALSE;
		}
		if((pdash.z >= CUBEZBOUNDARY1l) && (pdash.z <= CUBEZBOUNDARY2h))
		{

		}
		else
		{
			tzoutHits = FALSE;
		}
	#endif


	}




	if(denominatorIsZero == FALSE)
	{/*ray hits the cube*/

		/*using the tin/tout values, will now find where it hits the cube*/

		/*finds min of tins and max of touts.
		and checks that max of tins < min touts.
		if so, the ray is designated a miss*/


	#ifndef RT_METHOD2

		/* - requires reversal for some reason, must be some defintion reversal earlier
		tin = RToperations.findSmallestValue(txin, tyin, tzin);
		tout = RToperations.findGreatestValue(txout, tyout, tzout);
		*/

		tin = RToperations.findGreatestValue(txin, tyin, tzin);
		tout = RToperations.findSmallestValue(txout, tyout, tzout);

		if(tin > tout)
		{
			tempTInOut[0] = -1;
			tempTInOut[1] = -1;
		}
		else
		{
			tempTInOut[0] = tin;
			tempTInOut[1] = tout;
		}
	#else

		/*test only*/
		double tins[3];
		double touts[3];
		tins[0] = txin;
		tins[1] = tyin;
		tins[2] = tzin;
		touts[0] = txout;
		touts[1] = tyout;
		touts[2] = tzout;

		int tinsHit[3];
		int toutsHit[3];
		tinsHit[0] = txinHits;
		tinsHit[1] = tyinHits;
		tinsHit[2] = tzinHits;
		toutsHit[0] = txoutHits;
		toutsHit[1] = tyoutHits;
		toutsHit[2] = tzoutHits;

		//testonly2;
		int positionIn = -1;
		int positionOut = -1;
		positionIn = RToperations.findPositionOfSmallestValueWhichHits(tins, tinsHit, 3);		//findPositionOfGreatestValueWhichHits: issue found here?
		positionOut = RToperations.findPositionOfGreatestValueWhichHits(touts, toutsHit, 3);		//findPositionOfSmallestValueWhichHits: issue found here?
		tin = tins[positionIn];
		tout = touts[positionOut];


		if(positionIn < 0)
		{
			tempTInOut[0] = -1;
			tempTInOut[1] = -1;
		}
		else
		{
			tempTInOut[0] = tin;
			tempTInOut[1] = tout;
		}
	#endif

	}
	else
	{/*denominatorIsZero = TRUE;*/	/*this is not usually the case*/
		tempTInOut[0] = -1;
		tempTInOut[1] = -1;
	}


		//these operations may only be relevant for a cube; not sure
	if(tempTInOut[0] > 0)
	{

		tInOut[0] = tempTInOut[0];
		tInOut[1] = tempTInOut[1];
		*relevantFinalReverseMatrix = *finalReverseMatrix;
	}
	else
	{
		/*no update*/
	}




	/*NORMAL CALCULATIONS*/

	#ifndef RT_METHOD2
	if(tInOut[0] > 0) 		//condition added as test2
	{
	#endif

		/*added recently, the point is used to calculate lighting*/
		SHAREDvector.negativeVector(p0, tmp);
		SHAREDvector.addVectorsRT(p1, tmp, tmp2);
		SHAREDvector.multiplyVectorByScalarRT(tmp2, tInOut[0], tmp3);
		SHAREDvector.addVectorsRT(p0, tmp3, &pdash);

		/*find normal*/
		if((pdash.x > CUBEXBOUNDARY2l) && (pdash.x < CUBEXBOUNDARY2h))
		{
			norm->x = 1.0;
		}
		else if((pdash.x > CUBEXBOUNDARY1l) && (pdash.x < CUBEXBOUNDARY1h))
		{
			norm->x = -1.0;
		}

		if((pdash.y > CUBEYBOUNDARY2l) && (pdash.y < CUBEYBOUNDARY2h))
		{
			norm->y = 1.0;
		}
		else if((pdash.y > CUBEYBOUNDARY1l) && (pdash.y < CUBEYBOUNDARY1h))
		{
			norm->y = -1.0;
		}

		if((pdash.z > CUBEZBOUNDARY2l) && (pdash.z < CUBEZBOUNDARY2h))
		{
			norm->z = 1.0;
		}
		else if((pdash.z > CUBEZBOUNDARY1l) && (pdash.z < CUBEZBOUNDARY1h))
		{
			norm->z = -1.0;
		}

	#ifndef RT_METHOD2
	}
	#endif
}





/*there are currently minor errors with this method*/

void RTraytracerClass::calculateCylinder(vec* p0, vec* p1, double* tInOut, vec* norm, advancedMat* finalReverseMatrix, advancedMat* relevantFinalReverseMatrix)
{
	vec tmp_structure;	/*used for vector manipulation*/
	vec tmp2_structure;	/*used for vector manipulation*/
	vec tmp3_structure;	/*used for vector manipulation*/
	vec* tmp = &tmp_structure;
	vec* tmp2 = &tmp2_structure;
	vec* tmp3 = &tmp3_structure;


	double tempTInOut[2];


	//int hit12 = FALSE;
	//int hit34 = FALSE;
	int positionIn;	/*a number between 0 and 3, or -1 if never*/
	int positionOut;
	vec pdash[CYLINDER_ARRAY_SIZE];
	double insideSqrt;


	/*defining basic cylinder dimensions*/
	double CYLINDERRADIUSBOUNDARY = ONE/2.0;
	double CYLINDERZBOUNDARY1 = ZERO;
	double CYLINDERZBOUNDARY2 = ONE;
	/*
	double CYLINDERRADIUSBOUNDARY = obj->scale.x;
	double CYLINDERZBOUNDARY1 = obj->trans.z + ZERO;
	double CYLINDERZBOUNDARY2 = obj->trans.z + obj->scale.z;
	*/

	/*setting t calcluation values. set default to hit*/
	double denominator;
	/*defining scalars*/
	double a, b, c;
	double tTopBottom[2];	//in and out
	int tTopBottomHit[2];
	tTopBottomHit[0] = FALSE;
	tTopBottomHit[1] = FALSE;
	double tSide[2];	//in and out
	int tSideHit[2];
	tSideHit[0] = FALSE;
	tSideHit[1] = FALSE;
	/*defining temporary variables*/


	/* [sub line equation into equation for circle...]
	x^2 + y^2 - R^2 = 0
	x^2 + y^2 = R^2

	(R usually equal to 1)

	so,

	t1 = (-b + sqrt(b^2 - 4*a*c)) / (2*a)
	t2 = (-b - sqrt(b^2 - 4*a*c)) / (2*a)

	where;

	a = (P1 - P0)^2 (x comp) + (P1 - P0)^2 (y comp) + (P1 - P0)^2 (z comp)
	b = [2* P0* (P1 - P0)] (x comp) + [2* P0* (P1 - P0)] (y comp) + [2* P0* (P1 - P0)] (z comp)
	c = P0^2 (x comp) + P0^2 (y comp) + P0^2 (z comp) - R
	*/

	a = pow((p1->x - p0->x), 2) + pow((p1->y - p0->y), 2);
	b = (2* p0->x* (p1->x - p0->x)) + (2* p0->y* (p1->y - p0->y));
	c = pow(p0->x, 2) + pow(p0->y, 2) - CYLINDERRADIUSBOUNDARY;

	/*sides of cylinder*/
	insideSqrt = pow(b,2) - (4*a*c);
	denominator = (2*a);
	if((insideSqrt < 0) || (denominator == 0))
	{/*hit12 = FALSE*/
		//tSide[0] = -1;
		//tSide[1] = -1;
		tSideHit[0] = FALSE;
		tSideHit[1] = FALSE;

	}
	else
	{
		double sqrted = sqrt(sqrted);
		tSide[0] = (-b + sqrted) / denominator;
		tSide[1] = (-b - sqrted) / denominator;


			//else flip is mandatory

		if(tSide[0] > tSide[1])	//make sure ins and outs are properly arranged
		{
			double tmpd = tSide[1];
			tSide[1] = tSide[0];
			tSide[0] = tmpd;
		}

		/*
		double tmpd = tSide[1];
		tSide[1] = tSide[0];
		tSide[0] = tmpd;
		*/

		SHAREDvector.negativeVector(p0, tmp);
		SHAREDvector.addVectorsRT(p1, tmp, tmp2);

		SHAREDvector.multiplyVectorByScalarRT(tmp2, tSide[0], tmp3);
		SHAREDvector.addVectorsRT(p0, tmp3, &pdash[0]);

		if((pdash[0].z >= CYLINDERZBOUNDARY1) && (pdash[0].z <= CYLINDERZBOUNDARY2))
		{
			tSideHit[0] = TRUE;
		}
		else
		{
			tSideHit[0] = FALSE;
		}

		SHAREDvector.multiplyVectorByScalarRT(tmp2, tSide[1], tmp3);
		SHAREDvector.addVectorsRT(p0, tmp3, &pdash[1]);

		if((pdash[1].z >= CYLINDERZBOUNDARY1) && (pdash[1].z <= CYLINDERZBOUNDARY2))
		{
			tSideHit[1] = TRUE;
		}
		else
		{
			tSideHit[1] = FALSE;
		}
	}

	/*tops of cylinder*/

	denominator = (p1->z) - (p0->z);
	if(denominator == 0)
	{/*hit34 still FALSE*/
		//tTopBottom[0] = -1;
		//tTopBottom[1] = -1;
		tTopBottomHit[0] = FALSE;
		tTopBottomHit[1] = FALSE;
	}
	else
	{
		tTopBottom[0] = (CYLINDERZBOUNDARY1 - p0->z)/denominator;
		tTopBottom[1] = (CYLINDERZBOUNDARY2 - p0->z)/denominator;


			//else flip is mandatory
		if(tTopBottom[0] > tTopBottom[1])	//make sure ins and outs are properly arranged
		{
			double tmpd = tTopBottom[1];
			tTopBottom[1] = tTopBottom[0];
			tTopBottom[0] = tmpd;
		}
		/*
		double tmpd = tTopBottom[1];
		tTopBottom[1] = tTopBottom[0];
		tTopBottom[0] = tmpd;
		*/

		//tTopBottom[0] =-1;

		SHAREDvector.negativeVector(p0, tmp);
		SHAREDvector.addVectorsRT(p1, tmp, tmp2);

		SHAREDvector.multiplyVectorByScalarRT(tmp2, tTopBottom[0], tmp3);
		SHAREDvector.addVectorsRT(p0, tmp3, &pdash[0]);

		if(pow((pdash[0].x), 2) + pow((pdash[0].y), 2) <= CYLINDERRADIUSBOUNDARY)
		{
			tTopBottomHit[0] = TRUE;

		}
		else
		{//hit34 still FALSE
			tTopBottomHit[0] = FALSE;

		}


		//tTopBottom[1] =-1;

		SHAREDvector.multiplyVectorByScalarRT(tmp2, tTopBottom[1], tmp3);
		SHAREDvector.addVectorsRT(p0, tmp3, &pdash[1]);

		if(pow((pdash[1].x), 2) + pow((pdash[1].y), 2) <= CYLINDERRADIUSBOUNDARY)
		{
			tTopBottomHit[1] = TRUE;
		}
		else
		{
			tTopBottomHit[1] = FALSE;
		}
	}

	//printf("zero = %d", ZERO);


	/*debugging original;
	double tin = findSmallestValueAdvanced(tTopBottom[0], tSide[0]);		//issue found here
	double tout = findGreatestValueAdvanced(tTopBottom[1], tSide[1]);		//issue found here
	*/

	/*debugging new;
	double tin = findGreatestValueAdvanced(tTopBottom[0], tSide[0]);		//issue found here
	double tout = findSmallestValueAdvanced(tTopBottom[1], tSide[1]);		//issue found here
	*/

	//debugging testonly1;
	/*
	double tin = findGreatestValue(tTopBottom[0], tSide[0]);			//issue found here
	double tout = findSmallestValue(tTopBottom[1], tSide[1]);		//issue found here
	*/

	/*debugging:
	//if(tin < 0)
	//{
	//	tempTInOut[0] = -1;
	//	tempTInOut[1] = -1;
	//}
	//else
	//{

		//added condition sept 08
		if(tin < tout)
		{
			tempTInOut[0] = tin;
			tempTInOut[1] = tout;
		}
		else
		{
			tempTInOut[0] = -1;
			tempTInOut[1] = -1;
		}

	//}
	*/


	//METHOD2

	double tins[2];
	double touts[2];
	tins[0] = tTopBottom[0];
	tins[1] = tSide[0];
	touts[0] = tTopBottom[1];
	touts[1] = tSide[1];

	int tinsHit[2];
	int toutsHit[2];
	tinsHit[0] = tTopBottomHit[0];
	tinsHit[1] = tSideHit[0];
	toutsHit[0] = tTopBottomHit[1];
	toutsHit[1] = tSideHit[1];

	//original;
	//positionIn = findPositionOfGreatestValueAdvanced(tins, 2);		//issue found here
	//positionOut = findPositionOfSmallestValueAdvanced(touts, 2);		//issue found here

	//testonly2;
	positionIn = -1;
	positionOut = -1;
	positionIn = RToperations.findPositionOfSmallestValueWhichHits(tins, tinsHit, 2);		//findPositionOfGreatestValueWhichHits		//issue found here
	positionOut = RToperations.findPositionOfGreatestValueWhichHits(touts, toutsHit, 2);		//findPositionOfSmallestValueWhichHits	//issue found here


	//if((positionIn < 0) || (positionOut < 0))	why doesnt thiswork??
	if(positionIn < 0)
	{
		tempTInOut[0] = -1;
		tempTInOut[1] = -1;
	}
	else
	{
		//added condition sept 08
		tempTInOut[0] = tins[positionIn];
		tempTInOut[1] = touts[positionOut];
		/*
		if(tins[positionIn] < touts[positionOut])
		{
			tempTInOut[0] = tins[positionIn];
			tempTInOut[1] = touts[positionOut];
		}
		else
		{

			tempTInOut[0] = -1;
			tempTInOut[1] = -1;
		}
		*/
	}


		//these operations may only be relevant for a cube; not sure
	if(tempTInOut[0] > 0)
	{
		tInOut[0] = tempTInOut[0];
		tInOut[1] = tempTInOut[1];
		*relevantFinalReverseMatrix = *finalReverseMatrix;
	}
	else
	{
		/*no update*/
	}



	if(tInOut[0] > 0)
	{

		/*NORMAL CALCULATIONS*/

			/*used for normal calculations*/
		/*defining round offs for cylinder faces. h=high, l=low*/

		double CYLINDERZBOUNDARY1h = CYLINDERZBOUNDARY1 + ROUND_OFF;
		double CYLINDERZBOUNDARY1l = CYLINDERZBOUNDARY1 - ROUND_OFF;
		double CYLINDERZBOUNDARY2h = CYLINDERZBOUNDARY2 + ROUND_OFF;
		double CYLINDERZBOUNDARY2l = CYLINDERZBOUNDARY2 - ROUND_OFF;

		vec pdashFinal;

		SHAREDvector.negativeVector(p0, tmp);
		SHAREDvector.addVectorsRT(p1, tmp, tmp2);
		SHAREDvector.multiplyVectorByScalarRT(tmp2, tInOut[0], tmp3);
		SHAREDvector.addVectorsRT(p0, tmp3, &pdashFinal);

		//find norm

		if((pdashFinal.z > CYLINDERZBOUNDARY2l) && (pdashFinal.z < CYLINDERZBOUNDARY2h))
		//if(pdashFinal.z > CYLINDERZBOUNDARY2l)
		{
			norm->z = 1.0;
		}
		else if((pdashFinal.z > CYLINDERZBOUNDARY1l) && (pdashFinal.z < CYLINDERZBOUNDARY1h))
		//else if(pdashFinal.z < CYLINDERZBOUNDARY1h)
		{
			norm->z = -1.0;
		}
		else
		{//hits somewhere on the circlar face of the cylinder
			norm->x = pdashFinal.x;
			norm->y = pdashFinal.y;
		}
	}
}






/*this method works fine except the calculated normals
produce a cone like image instead of rounded lighting*/

void RTraytracerClass::calculateSphere(vec* p0, vec* p1, double* tInOut, vec* norm, advancedMat* finalReverseMatrix, advancedMat* relevantFinalReverseMatrix)
{
	vec d; /*= P1 - P0*/

	int positionIn;	/*a number between 0 and 3, or -1 if never*/
	int positionOut;
	vec pdash[CYLINDER_ARRAY_SIZE];
	double sqrted;

	advancedMat reverseMatrixCopy;
	advancedMat standardMatrixCopy;

	vec tmp_structure;	/*used for vector manipulation*/
	vec tmp2_structure;	/*used for vector manipulation*/
	vec tmp3_structure;	/*used for vector manipulation*/
	vec* tmp = &tmp_structure;
	vec* tmp2 = &tmp2_structure;
	vec* tmp3 = &tmp3_structure;

	advancedVec ndashAdvanced;
	advancedVec nAdvanced;
	vec ndash;
	vec n;

	vec p;
	advancedVec pdashAdvanced;
	advancedVec pAdvanced;

	/*defining basic cylinder dimensions*/
	double SPHERERADIUSBOUNDARY = ONE;

	/*setting t calcluation values. set default to hit*/
	double denominator;
	/*defining scalars*/
	double a, b, c;
	double t[SPHERE_ARRAY_SIZE];
	int tHit[SPHERE_ARRAY_SIZE];
	tHit[0] = FALSE;
	tHit[1] = FALSE;
	/*defining temporary variables*/


	/*
	x^2 + y^2 + z^2 - R^2 = 0

	(R usually equal to 1)

	so,

	t1 = (-b + sqrt(b^2 - 4*a*c)) / (2*a)
	t2 = (-b - sqrt(b^2 - 4*a*c)) / (2*a)

	where;

	a = D.D
	b = 2*E.D
	c = E.E - R
	*/

	/*creates d vector*/
	/*
	SHAREDvector.negativeVector(p0, tmp);
	SHAREDvector.addVectorsRT(p1, tmp, &d);
	*/
	SHAREDvector.subtractVectorsRT(p1, p0, &d);
	a = SHAREDvector.dotProduct(&d, &d);
	SHAREDvector.multiplyVectorByScalarRT(p0, 2.0, tmp);
	b = SHAREDvector.dotProduct(tmp, &d);
	c = SHAREDvector.dotProduct(p0, p0) - SPHERERADIUSBOUNDARY;


	sqrted = pow(b,2) - (4*a*c);
	denominator = (2*a);
	if((sqrted < 0) || (denominator == 0))
	{/*hit12 = FALSE*/
		tHit[0] = FALSE;
		tHit[1] = FALSE;
	}
	else
	{
		double aftersqrted = sqrt(sqrted);
		t[0] = (-b + aftersqrted) / denominator;
		t[1] = (-b - aftersqrted) / denominator;

		//printf("\n t[0] = %f", t[0]);
		//printf("\n t[1] = %f", t[1]);

		if(t[0] > t[1])	//make sure ins and outs are properly arranged
		{
			double tmpd = t[1];
			t[1] = t[0];
			t[0] = tmpd;
		}

		tHit[0] = TRUE;
		tHit[1] = TRUE;

		SHAREDvector.negativeVector(p0, tmp);
		SHAREDvector.addVectorsRT(p1, tmp, tmp2);
		SHAREDvector.multiplyVectorByScalarRT(tmp2, t[0], tmp3);
		SHAREDvector.addVectorsRT(p0, tmp3, &pdash[0]);

		SHAREDvector.negativeVector(p0, tmp);
		SHAREDvector.addVectorsRT(p1, tmp, tmp2);
		SHAREDvector.multiplyVectorByScalarRT(tmp2, t[1], tmp3);
		SHAREDvector.addVectorsRT(p0, tmp3, &pdash[1]);
	}

	/*debugging:
	double tins[1];
	double touts[1];
	tins[0] = t[0];
	touts[0] = t[1];

	int tinsHit[1];
	int toutsHit[1];
	tinsHit[0] = tHit[0];
	toutsHit[0] = tHit[1];

	//original
	//positionIn = findPositionOfGreatestValueAdvanced(tins, 2);		//issue found here
	//positionOut = findPositionOfSmallestValueAdvanced(touts, 2);		//issue found here


	//testonly2;
	positionIn = -1;
	positionOut = -1;
	positionIn = findPositionOfSmallestValueWhichHits(tins, tinsHit, 1);		//findPositionOfGreatestValueWhichHits		//issue found here
	positionOut = findPositionOfGreatestValueWhichHits(touts, toutsHit, 1);		//findPositionOfSmallestValueWhichHits	//issue found here

	double tempTInOut[2];
	if(positionIn < 0)
	{
		tempTInOut[0] = -1;
		tempTInOut[1] = -1;
	}
	else
	{
		printf("1");
		tempTInOut[0] = tins[positionIn];
		tempTInOut[1] = touts[positionOut];
	}
	*/

		//these operations may only be relevant for a cube; not sure
	if(tHit[0] == TRUE)
	{
		//printf("2");
		tInOut[0] = t[0];
		tInOut[1] = t[1];
		*relevantFinalReverseMatrix = *finalReverseMatrix;
	}
	else
	{
		/*no update*/
	}


	if(tInOut[0] > 0)
	{
		//printf("3");
		/*NORMAL CALCULATIONS*/
		vec tmp_structure;	/*used for vector manipulation*/
		vec tmp2_structure;	/*used for vector manipulation*/
		vec tmp3_structure;	/*used for vector manipulation*/
		vec* tmp = &tmp_structure;
		vec* tmp2 = &tmp2_structure;
		vec* tmp3 = &tmp3_structure;


		vec pdashFinal;

		SHAREDvector.negativeVector(p0, tmp);
		SHAREDvector.addVectorsRT(p1, tmp, tmp2);
		SHAREDvector.multiplyVectorByScalarRT(tmp2, tInOut[0], tmp3);
		SHAREDvector.addVectorsRT(p0, tmp3, &pdashFinal);

		//find norm
		norm->x = pdashFinal.x;
		norm->y = pdashFinal.y;
		norm->z = pdashFinal.z;
	}

}












void RTraytracerClass::calculatePrimQuad(vec* p0, vec* p1, double* tInOut, const RTpieceInfo* pi, vec* norm, advancedMat* finalReverseMatrix, advancedMat* relevantFinalReverseMatrix)
{
	vec tmp_structure;	/*used for vector manipulation*/
	vec tmp2_structure;	/*used for vector manipulation*/
	vec tmp3_structure;	/*used for vector manipulation*/
	vec* tmp = &tmp_structure;
	vec* tmp2 = &tmp2_structure;
	vec* tmp3 = &tmp3_structure;

	vec intersectionPointQuad;		//NOT USED
	vec intersectionPointNormalQuad;

	double quadAtInAndOut;

	RToperations.findIntersectLineWithQuad(&(pi->vertex1Position), &(pi->vertex2Position), &(pi->vertex3Position), &(pi->vertex4Position), p0, p1, &intersectionPointQuad, &intersectionPointNormalQuad, &quadAtInAndOut);


	double tInAndOut = quadAtInAndOut;

	if(tInAndOut > 0)
	{
		//printf("hereg");
		tInOut[0] = tInAndOut;
		tInOut[1] = tInAndOut;
		*relevantFinalReverseMatrix = *finalReverseMatrix;
	}


	/*NORMAL CALCULATIONS*/

	if(tInOut[0] > 0) 		//condition added as test2
	{
		vec pdash;

		/*added recently, the point is used to calculate lighting*/
		SHAREDvector.negativeVector(p0, tmp);
		SHAREDvector.addVectorsRT(p1, tmp, tmp2);
		SHAREDvector.multiplyVectorByScalarRT(tmp2, tInOut[0], tmp3);
		SHAREDvector.addVectorsRT(p0, tmp3, &pdash);


		/*set normal*/

		SHAREDvector.copyVectorRT(norm, &intersectionPointNormalQuad);
		SHAREDvector.negativeVector(norm, norm);	//???
	}
}

void RTraytracerClass::calculatePrimTri(vec* p0, vec* p1, double* tInOut, const RTpieceInfo* pi, vec* norm, advancedMat* finalReverseMatrix, advancedMat* relevantFinalReverseMatrix)
{
	vec tmp_structure;	/*used for vector manipulation*/
	vec tmp2_structure;	/*used for vector manipulation*/
	vec tmp3_structure;	/*used for vector manipulation*/
	vec* tmp = &tmp_structure;
	vec* tmp2 = &tmp2_structure;
	vec* tmp3 = &tmp3_structure;

	vec intersectionPointTriA;		//NOT USED
	vec intersectionPointNormalTriA;


	int triAIntersectionFound = FALSE;

	double triAtInAndOut;

	if(RToperations.findIntersectLineWithTri(&(pi->vertex1Position), &(pi->vertex2Position), &(pi->vertex3Position), p0, p1, &intersectionPointTriA, &intersectionPointNormalTriA, &triAtInAndOut))
	{
		triAIntersectionFound = TRUE;
	}

	double tInAndOut;
	if(triAIntersectionFound)
	{
		tInAndOut = triAtInAndOut;
	}
	else
	{
		tInAndOut = -1;
	}

	if(tInAndOut > 0)
	{
		//printf("hereg");
		tInOut[0] = tInAndOut;
		tInOut[1] = tInAndOut;
		*relevantFinalReverseMatrix = *finalReverseMatrix;
	}


	/*NORMAL CALCULATIONS*/

	if(tInOut[0] > 0) 		//condition added as test2
	{
		vec pdash;

		/*added recently, the point is used to calculate lighting*/
		SHAREDvector.negativeVector(p0, tmp);
		SHAREDvector.addVectorsRT(p1, tmp, tmp2);
		SHAREDvector.multiplyVectorByScalarRT(tmp2, tInOut[0], tmp3);
		SHAREDvector.addVectorsRT(p0, tmp3, &pdash);


		/*set normal*/

		SHAREDvector.copyVectorRT(norm, &intersectionPointNormalTriA);
		SHAREDvector.negativeVector(norm, norm);	//???
	}
}



	//define a line as 3 quads
void RTraytracerClass::calculatePrimLineNEW(vec* p0, vec* p1, double* tInOut, RTpieceInfo* pi, vec* norm, advancedMat* finalReverseMatrix, advancedMat* relevantFinalReverseMatrix)
{
	vec tmp_structure;	/*used for vector manipulation*/
	vec tmp2_structure;	/*used for vector manipulation*/
	vec tmp3_structure;	/*used for vector manipulation*/
	vec* tmp = &tmp_structure;
	vec* tmp2 = &tmp2_structure;
	vec* tmp3 = &tmp3_structure;

		//[NB a quad is formed out of 2 tris]

	vec intersectionPointQuadA;
	vec intersectionPointQuadB;
	vec intersectionPointQuadC;
	vec intersectionPoint;
	vec intersectionPointNormalQuadA;
	vec intersectionPointNormalQuadB;
	vec intersectionPointNormalQuadC;
	vec intersectionPointNormal;

	vec quada;
	vec quadb;
	vec quadc;

	int quadAIntersectionFound = FALSE;
	int quadBIntersectionFound = FALSE;
	int quadCIntersectionFound = FALSE;
	int quadIntersectionFound = FALSE;

	double tin, tout;
	double quadAtInAndOut;
	double quadBtInAndOut;
	double quadCtInAndOut;

	vec vertex1PositionWithXShift;
	vec vertex1PositionWithYShift;
	vec vertex1PositionWithZShift;
	vec vertex2PositionWithXShift;
	vec vertex2PositionWithYShift;
	vec vertex2PositionWithZShift;

	SHAREDvector.copyVectorRT(&vertex1PositionWithXShift, &(pi->vertex1Position));
	SHAREDvector.copyVectorRT(&vertex1PositionWithYShift, &(pi->vertex1Position));
	SHAREDvector.copyVectorRT(&vertex1PositionWithZShift, &(pi->vertex1Position));
	SHAREDvector.copyVectorRT(&vertex2PositionWithXShift, &(pi->vertex2Position));
	SHAREDvector.copyVectorRT(&vertex2PositionWithYShift, &(pi->vertex2Position));
	SHAREDvector.copyVectorRT(&vertex2PositionWithZShift, &(pi->vertex2Position));

	vertex1PositionWithXShift.x = vertex1PositionWithXShift.x + PRIM_LINE_CALC_QUAD_REDUCTION_WIDTH;
	vertex1PositionWithYShift.y = vertex1PositionWithYShift.y + PRIM_LINE_CALC_QUAD_REDUCTION_WIDTH;
	vertex1PositionWithZShift.z = vertex1PositionWithZShift.z + PRIM_LINE_CALC_QUAD_REDUCTION_WIDTH;
	vertex2PositionWithXShift.x = vertex2PositionWithXShift.x + PRIM_LINE_CALC_QUAD_REDUCTION_WIDTH;
	vertex2PositionWithYShift.y = vertex2PositionWithYShift.y + PRIM_LINE_CALC_QUAD_REDUCTION_WIDTH;
	vertex2PositionWithZShift.z = vertex2PositionWithZShift.z + PRIM_LINE_CALC_QUAD_REDUCTION_WIDTH;


	if(RToperations.findIntersectLineWithQuad(&(pi->vertex1Position), &vertex1PositionWithXShift, &(pi->vertex2Position), &vertex2PositionWithXShift, p0, p1, &intersectionPointQuadA, &intersectionPointNormalQuadA, &quadAtInAndOut))
	{
		quadAIntersectionFound = TRUE;
	}
	if(RToperations.findIntersectLineWithQuad(&(pi->vertex1Position), &vertex1PositionWithYShift, &(pi->vertex2Position), &vertex2PositionWithYShift, p0, p1, &intersectionPointQuadB, &intersectionPointNormalQuadB, &quadBtInAndOut))
	{
		quadBIntersectionFound = TRUE;
	}
	if(RToperations.findIntersectLineWithQuad(&(pi->vertex1Position), &vertex1PositionWithZShift, &(pi->vertex2Position), &vertex2PositionWithZShift, p0, p1, &intersectionPointQuadC, &intersectionPointNormalQuadC, &quadCtInAndOut))
	{
		quadCIntersectionFound = TRUE;
	}

	double tInAndOut;
	if(quadAIntersectionFound)
	{
		//printf("\nfound quad intersectionA");
		quadIntersectionFound = TRUE;
		SHAREDvector.copyVectorRT(&intersectionPointNormal, &intersectionPointNormalQuadA);
		SHAREDvector.copyVectorRT(&intersectionPoint, &intersectionPointQuadA);
		tInAndOut = quadAtInAndOut;
	}
	else if(quadBIntersectionFound)
	{
		//printf("\nfound quad intersectionB");
		quadIntersectionFound = TRUE;
		SHAREDvector.copyVectorRT(&intersectionPointNormal, &intersectionPointNormalQuadB);
		SHAREDvector.copyVectorRT(&intersectionPoint, &intersectionPointQuadB);
		tInAndOut = quadBtInAndOut;
	}
	else if(quadCIntersectionFound)
	{
		//printf("\nfound quad intersectionC");
		quadIntersectionFound = TRUE;
		SHAREDvector.copyVectorRT(&intersectionPointNormal, &intersectionPointNormalQuadC);
		SHAREDvector.copyVectorRT(&intersectionPoint, &intersectionPointQuadC);
		tInAndOut = quadCtInAndOut;
	}
	else
	{
		quadIntersectionFound = FALSE;
		tInAndOut = -1;
	}


	if(tInAndOut > 0)
	{
		//printf("found quad intersection");
		tInOut[0] = tInAndOut;
		tInOut[1] = tInAndOut;
		*relevantFinalReverseMatrix = *finalReverseMatrix;
	}

	/*NORMAL CALCULATIONS*/

	if(tInOut[0] > 0) 		//condition added as test2
	{
		vec pdash;

		/*added recently, the point is used to calculate lighting*/
		SHAREDvector.negativeVector(p0, tmp);
		SHAREDvector.addVectorsRT(p1, tmp, tmp2);
		SHAREDvector.multiplyVectorByScalarRT(tmp2, tInOut[0], tmp3);
		SHAREDvector.addVectorsRT(p0, tmp3, &pdash);


		/*set normal*/
		SHAREDvector.copyVectorRT(norm, &intersectionPointNormal);
	}
}


void RTraytracerClass::calculatePrimLine(vec* p0, vec* p1, double* tInOut, const RTpieceInfo* pi, const vec* norm, advancedMat* finalReverseMatrix, advancedMat* relevantFinalReverseMatrix)
{
	vec tmp_structure;	/*used for vector manipulation*/
	vec tmp2_structure;	/*used for vector manipulation*/
	vec tmp3_structure;	/*used for vector manipulation*/
	vec* tmp = &tmp_structure;
	vec* tmp2 = &tmp2_structure;
	vec* tmp3 = &tmp3_structure;

	vec intersectionPoint;
	vec intersectionPointNormal;
	vec vectorP1MinusP0;
	SHAREDvector.subtractVectorsRT(p1, p0, &vectorP1MinusP0);

	int lineIntersectionFound = FALSE;
	double linetInAndOut;

	if(RToperations.findIntersectLineWithLine(&(pi->vertex1Position), &(pi->vertex2Position), p0, p1, &intersectionPoint, &intersectionPointNormal, &linetInAndOut))
	{
		lineIntersectionFound = TRUE;
	}

	double tInAndOut;
	if(lineIntersectionFound)
	{
		tInAndOut = linetInAndOut;
	}
	else
	{
		tInAndOut = -1;
	}

	if(tInAndOut > 0)
	{
		//printf("hereg");
		tInOut[0] = tInAndOut;
		tInOut[1] = tInAndOut;
		*relevantFinalReverseMatrix = *finalReverseMatrix;
	}


	/*NORMAL CALCULATIONS*/
	/*
	if(tInOut[0] > 0) 		//condition added as test2
	{
		vec pdash;

		negativeVector(p0, tmp);
		addVectorsRT(p1, tmp, tmp2);
		multiplyVectorByScalarRT(tmp2, tInOut[0], tmp3);
		addVectorsRT(p0, tmp3, &pdash);


		//set normal

		copyVectorRT(norm, &intersectionPointNormal);
		negativeVector(norm, norm);
	}
	*/
}








#ifndef RT_T_TRANSFORM_TEST
void RTraytracerClass::drawPoint(RTsceneInfo* si, advancedMat* reverseMatrix, double tInDash, double tOutDash, vec* p0Dash, vec* p1Dash, vec* norm)
#else
//void drawPointTest(RTsceneInfo* si, advancedMat* reverseMatrix, double tInDash, double tOutDash, vec* p0Dash, vec* p1Dash, vec* norm, vec* p0, vec* p1)
#endif
{
	advancedMat reverseMatrixCopy;
	advancedMat standardMatrixCopy;


	vec tmp_structure;	/*used for vector manipulation*/
	vec tmp2_structure;	/*used for vector manipulation*/
	vec tmp3_structure;	/*used for vector manipulation*/
	vec* tmp = &tmp_structure;
	vec* tmp2 = &tmp2_structure;
	vec* tmp3 = &tmp3_structure;

	advancedVec ndashAdvanced;
	advancedVec nAdvanced;
	vec ndash;
	vec n;

	vec pdash;
	vec p;
	advancedVec pdashAdvanced;
	advancedVec pAdvanced;





	/*POINT CALCULATIONS*/

	/*added recently, the point is used to calculate lighting*/
	SHAREDvector.negativeVector(p0Dash, tmp);
	SHAREDvector.addVectorsRT(p1Dash, tmp, tmp2);
	SHAREDvector.multiplyVectorByScalarRT(tmp2, tInDash, tmp3);
	SHAREDvector.addVectorsRT(p0Dash, tmp3, &pdash);


	RToperations.toAdvancedVector(&pdash, 0, &pdashAdvanced);

	/*this is not needed
	standardMatrixCopy = *standardMatrix;
	RToperations.transposeAdvancedMatrix(&standardMatrixCopy);
	*/

	RToperations.multAdvancedMatrixByVector(&pdashAdvanced, reverseMatrix, &pAdvanced);
	RToperations.fromAdvancedVector(&pAdvanced, &p);

#ifndef RT_T_TRANSFORM_TEST
	si -> tIn = tInDash;
	si -> tOut = tOutDash;

#else
	//store t in world coordinates - and calculate p using tworld;
	vec pMinusP0;
	SHAREDvector.subtractVectorsRT(&p, p0, &pMinusP0);
	vec p1MinusP0;
	SHAREDvector.subtractVectorsRT(p1, p0, &p1MinusP0);
	double tIn = pMinusP0.x / p1MinusP0.x;
	si -> tIn = tIn;
	si -> tOut = 0.0;	//not calculated here
#endif
	/*this is not needed
	SHAREDvector.normaliseVector(&p);
	*/

	si -> p = p;


	/*NORMAL CALCULATIONS*/

	RToperations.createAdvancedVector(&ndashAdvanced);
	/*creates a 0,0,0,1 advanced vector*/
	ndashAdvanced.w = 0;
	/*creates a 0,0,0,0 advanced vector*/
	/*since vector last var = 1 if position, 0 if vector*/

	//replaced by RBB 2x sept 08
	RToperations.toAdvancedVector(norm, 0, &ndashAdvanced);

	reverseMatrixCopy = *reverseMatrix;
	RToperations.transposeAdvancedMatrix(&reverseMatrixCopy);	/*this doesnt do anything*/
	RToperations.multAdvancedMatrixByVector(&ndashAdvanced, &reverseMatrixCopy, &nAdvanced);
	RToperations.fromAdvancedVector(&nAdvanced, &n);

	/*important*/
	SHAREDvector.normaliseVector(&n);

	si -> n = n;

}


	//norm is not used
void RTraytracerClass::drawPointNoLighting(RTsceneInfo* si, const advancedMat* reverseMatrix, double tIn, double tOut, const vec* p0, const vec* p1, const vec* norm)
{
	si -> tIn = tIn;
	si -> tOut = tOut;
}


	//added October 08
void RTraytracerClass::calculatePointUsingTInWorld(double tInWorld, vec* p0, vec* p1, RTviewInfo* vi, vec* p, vec* uvn)
{
	//1. create tilda matrix

		/*declaration of variables for tildaMatrix calculation*/

	mat tildaMat_structure;
	mat* tildaMat = &tildaMat_structure;

	vec wTilda_structure;
	vec vTilda_structure;
	vec nTilda_structure;
	vec uTilda_structure;
	vec tmp_structure;		/*used for vector manipulation*/
	vec tmp2_structure;
	vec tmp3_structure;

	/*defining vectors*/
	vec* wTilda = &wTilda_structure;
	vec* vTilda = &vTilda_structure;
	vec* nTilda = &nTilda_structure;
	vec* uTilda = &uTilda_structure;
	vec* tmp = &tmp_structure;	/*used for vector manipulation*/
	vec* tmp2 = &tmp2_structure;
	vec* tmp3 = &tmp3_structure;

		/*defining the nTilda, uTilda, vTilda vectors*/

	/*nTilda = (eye - viewAt)*/
	SHAREDvector.negativeVector(&(vi->viewAt), tmp);
	SHAREDvector.addVectorsRT(tmp,(&(vi->eye)), nTilda);
	SHAREDvector.normaliseVector(nTilda);

	/*wTilda = (viewUp - eye)*/
	SHAREDvector.negativeVector(&(vi->eye), tmp);
	SHAREDvector.addVectorsRT(tmp,(&(vi->viewUp)), wTilda);
	SHAREDvector.normaliseVector(wTilda);

	/*uTilda = wTilda x nTilda*/
	SHAREDvector.crossProduct(wTilda, nTilda, uTilda);
	SHAREDvector.normaliseVector(uTilda);

	/*vTilda = nTilda x uTilda*/
	SHAREDvector.crossProduct(nTilda, uTilda, vTilda);
	SHAREDvector.normaliseVector(vTilda);

		/*calculation of tildaMatrix*/

	/*creating the uTilda vTilda nTilda matrix from the u, v, n vectors*/
	SHAREDvector.makeMatrix(uTilda, vTilda, nTilda, tildaMat);




	//2. create p0 and p1 points

	/*creating eye and direction*/
	/*NB p0 = &(vi->eye);*/
	*p0 = vi->eye;
	/*p1 = [uTilda vTilda nTilda][uvn] + eye*/
	SHAREDvector.multMatrixByVector(tildaMat, uvn, tmp);
	SHAREDvector.addVectorsRT(tmp, p0, p1);




	//3. Point Calculation

	/*added recently, the point is used to calculate lighting*/
	SHAREDvector.negativeVector(p0, tmp);
	SHAREDvector.addVectorsRT(p1, tmp, tmp2);
	SHAREDvector.multiplyVectorByScalarRT(tmp2, tInWorld, tmp3);
	SHAREDvector.addVectorsRT(p0, tmp3, p);

}






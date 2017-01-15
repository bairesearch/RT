/*******************************************************************************
 * 
 * This file is part of BAIPROJECT.
 * 
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation.
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
 * File Name: RTpixelMaps.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3d2b 14-April-2014
 *
 *******************************************************************************/

#include "RTpixelMaps.h"



#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;

#ifdef USE_OR
#include "ORglobalDefs.h"
#else
int DEFAULT_CONTRAST_MAP_GENERATION_KERNEL_WIDTH;
int DEFAULT_CONTRAST_MAP_GENERATION_KERNEL_HEIGHT;

double MAX_LUMINOSITY_CONTRAST;
double MAX_NORMAL_CONTRAST;

double LUMINOSITY_CONTRAST_FRACTION_THRESHOLD;
double LUMINOSITY_FRACTION_THRESHOLD;

double EDGE_LUMINOSITY_CONTRAST_THRESHOLD;   //OLD = ~0.07*MAX_LUMINOSITY_CONTRAST = ~ ((20.0/254.0)*MAX_LUMINOSITY_CONTRAST)
double EDGE_LUMINOSITY_THRESHOLD;

double ESTIMATE_MAX_DEPTH_T_REAL;
#endif

#ifndef USE_OR
void fillInRTRulesExternVariables()
{
	DEFAULT_CONTRAST_MAP_GENERATION_KERNEL_WIDTH = (CONTRAST_MAP_GENERATION_KERNEL_WIDTH_NO_INTERPIXEL);
	DEFAULT_CONTRAST_MAP_GENERATION_KERNEL_HEIGHT = (CONTRAST_MAP_GENERATION_KERNEL_HEIGHT_NO_INTERPIXEL);

	MAX_LUMINOSITY_CONTRAST = (MAX_LUMINOSITY);
	MAX_NORMAL_CONTRAST = (MAX_NORMAL*3.0);

	LUMINOSITY_CONTRAST_FRACTION_THRESHOLD = (0.05);
	LUMINOSITY_FRACTION_THRESHOLD = (0.01);

	EDGE_LUMINOSITY_CONTRAST_THRESHOLD = (MAX_LUMINOSITY_CONTRAST*LUMINOSITY_CONTRAST_FRACTION_THRESHOLD);   //OLD = ~0.07*MAX_LUMINOSITY_CONTRAST = ~ ((20.0/254.0)*MAX_LUMINOSITY_CONTRAST)
	EDGE_LUMINOSITY_THRESHOLD = (MAX_LUMINOSITY*LUMINOSITY_FRACTION_THRESHOLD);

	ESTIMATE_MAX_DEPTH_T_REAL = (20.0);

}
#endif

void printRGBMap(int imageWidth, int imageHeight, unsigned char * rgbMap)
{
	cout << "printRGBMap()" << endl;

	//fill luminosityMap
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			colour col;
			getRGBMapValues(x, y, imageWidth, rgbMap, &col);

			cout << int(col.r) << "\t" << int(col.g) << "\t" << int(col.b) << "\t" <<  endl;
		}
	}
}


double calculateLuminosityLevelFromColour(colour * col)
{
	double luminosity = (col->r+col->g+col->b);

	return luminosity;
}



void setBooleanMapValue(int x, int y, int imageWidth, bool booleanVal, bool * booleanMap)
{
	booleanMap[y*imageWidth + x] = booleanVal;
}

bool getBooleanMapValue(int x, int y, int imageWidth, bool * booleanMap)
{
	return booleanMap[y*imageWidth + x];
}


void setIntMapValue(int x, int y, int imageWidth, int intVal, int * intMap)
{
	intMap[y*imageWidth + x] = intVal;
}

int getIntMapValue(int x, int y, int imageWidth, int * intMap)
{
	return intMap[y*imageWidth + x];
}




unsigned char getRGBMapValue(int x, int y, int imageWidth, int rgb, unsigned char * rgbMap)
{
	return rgbMap[y*imageWidth*RGB_NUM + x*RGB_NUM + rgb];
}

void getRGBMapValues(int x, int y, int imageWidth, unsigned char * rgbMap, colour * col)
{
	col->r = rgbMap[y*imageWidth*RGB_NUM + x*RGB_NUM + RGB_RED];
	col->g = rgbMap[y*imageWidth*RGB_NUM + x*RGB_NUM + RGB_GREEN];
	col->b = rgbMap[y*imageWidth*RGB_NUM + x*RGB_NUM + RGB_BLUE];
}

void setRGBMapValues(int x, int y, int imageWidth, colour * col, unsigned char * rgbMap)
{
	/*
	printf("\ncol->r = %d", col->r);
	printf("\ncol->g = %d", col->g);
	printf("\ncol->b = %d", col->b);
	*/

	rgbMap[y*imageWidth*RGB_NUM + x*RGB_NUM + RGB_RED] = col->r;
	rgbMap[y*imageWidth*RGB_NUM + x*RGB_NUM + RGB_GREEN] = col->g;
	rgbMap[y*imageWidth*RGB_NUM + x*RGB_NUM + RGB_BLUE] = col->b;
}

void setRGBMapValue(int x, int y, int imageWidth, int rgb, unsigned char * rgbMap, int rgbVal)
{
	rgbMap[y*imageWidth*RGB_NUM + x*RGB_NUM + rgb] = rgbVal;
}


void setNormalMapValue(int x, int y, int imageWidth, vec * normalVal, double * normalMap)
{
	setVectorMapValue(x, y, imageWidth, normalVal, normalMap);
}

void getNormalMapValue(int x, int y, int imageWidth, double * normalMap, vec * normalVal)
{
	getVectorMapValue(x, y, imageWidth, normalMap, normalVal);
}

void setPointMapValue(int x, int y, int imageWidth, vec * pointVal, double * pointMap)
{
	setVectorMapValue(x, y, imageWidth, pointVal, pointMap);
}

void getPointMapValue(int x, int y, int imageWidth, double * pointMap, vec * pointVal)
{
	getVectorMapValue(x, y, imageWidth, pointMap, pointVal);
}


void setVectorMapValue(int x, int y, int imageWidth, vec * vectorVal, double * vectorMap)
{
	vectorMap[y*imageWidth*VEC_MAP_VEC_NUM_DIMENSIONS + x*VEC_MAP_VEC_NUM_DIMENSIONS + VEC_MAP_VEC_X] = vectorVal->x;
	vectorMap[y*imageWidth*VEC_MAP_VEC_NUM_DIMENSIONS + x*VEC_MAP_VEC_NUM_DIMENSIONS + VEC_MAP_VEC_Y] = vectorVal->y;
	vectorMap[y*imageWidth*VEC_MAP_VEC_NUM_DIMENSIONS + x*VEC_MAP_VEC_NUM_DIMENSIONS + VEC_MAP_VEC_Z] = vectorVal->z;
}
void getVectorMapValue(int x, int y, int imageWidth, double * vectorMap, vec * vectorVal)
{
	vectorVal->x = vectorMap[y*imageWidth*VEC_MAP_VEC_NUM_DIMENSIONS + x*VEC_MAP_VEC_NUM_DIMENSIONS + VEC_MAP_VEC_X];
	vectorVal->y = vectorMap[y*imageWidth*VEC_MAP_VEC_NUM_DIMENSIONS + x*VEC_MAP_VEC_NUM_DIMENSIONS + VEC_MAP_VEC_Y];
	vectorVal->z = vectorMap[y*imageWidth*VEC_MAP_VEC_NUM_DIMENSIONS + x*VEC_MAP_VEC_NUM_DIMENSIONS + VEC_MAP_VEC_Z];
}










void setLumOrContrastOrDepthMapValue(int x, int y, int imageWidth, double contrastVal, double * contrastMap)
{
	contrastMap[y*imageWidth + x] = contrastVal;
}

double getLumOrContrastOrDepthMapValue(int x, int y, int imageWidth, double * contrastMap)
{
	return contrastMap[y*imageWidth + x];
}


#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_CONTRAST_THRESHOLD_METHOD_3_LUMINOSITY_ONLY
void generateBooleanContrastPixmapFromRGBMap(char * imageFileName, int imageWidth, int imageHeight, unsigned char * rgbMap)
{
	int x,y;
	pixmap* pm;

	double * luminosityMap = new double[imageWidth*imageHeight];		//CHECK THIS; these maps need to be created inside ORmethod.cpp main loop for efficiency
	double * luminosityContrastMap = new double[imageWidth*imageHeight];	//CHECK THIS; these maps need to be created inside ORmethod.cpp main loop for efficiency
	createLuminosityMapFromRGBMap(imageWidth, imageHeight, rgbMap, luminosityMap);
	createContrastMapFromMap(imageWidth, imageHeight, luminosityMap, luminosityContrastMap);

	pm = newPixmap(imageWidth, imageHeight);

	for(y = 0; y < imageHeight; y++)
	{
  		for(x = 0; x < imageWidth; x++)
		{
			colour black;
			black.r = 0;
			black.g = 0;
			black.b = 0;
			placepointPPM(pm, x, y, black.r, black.g, black.b);
		}
	}

	for(y = 0; y < imageHeight; y++)
	{
  		for(x = 0; x < imageWidth; x++)
		{
			colour booleanContrastRGBColour;
			booleanContrastRGBColour.r = 0;
			booleanContrastRGBColour.g = 0;
			booleanContrastRGBColour.b = 0;

			double contrastVal = getLumOrContrastOrDepthMapValue(x, y, imageWidth, luminosityContrastMap);

			int contrastThreshold;

			#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_CONTRAST_THRESHOLD
			contrastThreshold = EDGE_LUMINOSITY_CONTRAST_THRESHOLD*OR_IMAGE_COMPARISON_DECISION_TREE_CONTRAST_THRESHOLD_FACTOR;	//needs to be dynamic based upon normalisation based upon average rgb values in image
			#else
			contrastThreshold = 0;
			#endif

			if(contrastVal > contrastThreshold)
			{
				booleanContrastRGBColour.r = MAX_RGB_VAL;
				booleanContrastRGBColour.g = MAX_RGB_VAL;
				booleanContrastRGBColour.b = MAX_RGB_VAL;
			}

			placepointPPM(pm, x, y, booleanContrastRGBColour.r, booleanContrastRGBColour.g, booleanContrastRGBColour.b);
		}
	}

	writeImage(imageFileName, pm);
}

#elif defined OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_CONTRAST_THRESHOLD_METHOD_2_ALL_RGB_COMPONENTS
void generateBooleanContrastPixmapFromRGBMap(char * imageFileName, int imageWidth, int imageHeight, unsigned char * rgbMap)
{
	int x,y;
	pixmap* pm;

	pm = newPixmap(imageWidth, imageHeight);

	for(y = 0; y < imageHeight; y++)
	{
  		for(x = 0; x < imageWidth; x++)
		{
			colour black;
			black.r = 0;
			black.g = 0;
			black.b = 0;
			placepointPPM(pm, x, y, black.r, black.g, black.b);
		}
	}

	for(y = 0; y < imageHeight; y++)
	{
  		for(x = 0; x < imageWidth; x++)
		{
			colour booleanContrastRGBColour;
			booleanContrastRGBColour.r = 0;
			booleanContrastRGBColour.g = 0;
			booleanContrastRGBColour.b = 0;

			for(int col=0; col<RGB_NUM; col++)
			{

				double contrastVal = calculateContrastLevelWithinKernelRGBComponent(x, y, rgbMap, col, RGB_CONTRAST_BOOLEAN_MAP_GENERATION_KERNEL_WIDTH, RGB_CONTRAST_BOOLEAN_MAP_GENERATION_KERNEL_HEIGHT, imageWidth, imageHeight);

				int contrastThreshold;

				#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_CONTRAST_THRESHOLD
				contrastThreshold = (EDGE_LUMINOSITY_CONTRAST_THRESHOLD*OR_IMAGE_COMPARISON_DECISION_TREE_CONTRAST_THRESHOLD_FACTOR)/RGB_NUM;	//needs to be dynamic based upon normalisation based upon average rgb values in image
				#else
				contrastThreshold = 0;
				#endif

				if(col == 0)
				{
					if(contrastVal > contrastThreshold)
					{
						booleanContrastRGBColour.r = MAX_RGB_VAL;
					}

				}
				else if(col == 1)
				{
					if(contrastVal > contrastThreshold)
					{
						booleanContrastRGBColour.g = MAX_RGB_VAL;
					}
				}
				else if(col == 2)
				{
					if(contrastVal > contrastThreshold)
					{
						booleanContrastRGBColour.b = MAX_RGB_VAL;
					}
				}
			}

			placepointPPM(pm, x, y, booleanContrastRGBColour.r, booleanContrastRGBColour.g, booleanContrastRGBColour.b);
		}
	}

	writeImage(imageFileName, pm);
}

#elif defined OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_CONTRAST_THRESHOLD_METHOD_1_ALL_RGB_COMPONENTS_WITH_DIRECTION
void generateBooleanContrastPixmapFromRGBMap(char * imageFileName, int imageWidth, int imageHeight, unsigned char * rgbMap)
{
	#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_NORMALISE_RGB_MAP
	double averageLuminosity = calculateAverageLuminosity(imageWidth, imageHeight, rgbMap);
	double averageNormalisedLuminosity = MAX_LUMINOSITY*OR_IMAGE_COMPARISON_DECISION_TREE_NORMALISE_RGB_MAP_AVERAGED_NORMALISED_LUMINOSITY_FRACTION;
	double contrastThresholdNormalisationFactor = averageLuminosity/averageNormalisedLuminosity;
	/*
	unsigned char * normalisedRgbMap = new unsigned char[imageWidth*imageHeight*RGB_NUM];
	void normaliseRGBMapBasedOnAverageLuminosity(normalisedRgbMap, imageWidth, imageHeight, rgbMap)
	rgbMap = normalisedRgbMap;
	*/
	#endif

	int x,y;
	pixmap* pm;

	pm = newPixmap(imageWidth*2, imageHeight*2);

	for(y = 0; y < imageHeight*2; y++)
	{
  		for(x = 0; x < imageWidth*2; x++)
		{
			colour black;
			black.r = 0;
			black.g = 0;
			black.b = 0;
			placepointPPM(pm, x, y, black.r, black.g, black.b);
		}
	}

	for(y = 0; y < imageHeight-1; y++)
	{
  		for(x = 0; x < imageWidth-1; x++)
		{

			colour colCurrent;
			getRGBMapValues(x, y, imageWidth,rgbMap,&colCurrent);

			colour colNext[2];
			getRGBMapValues(x+1, y, imageWidth, rgbMap, &(colNext[0]));
			getRGBMapValues(x, y+1, imageWidth, rgbMap, &(colNext[1]));


			for(int comparisonDirection=0; comparisonDirection<2; comparisonDirection++)
			{
				colour booleanContrastRGBColour;
				booleanContrastRGBColour.r = 0;
				booleanContrastRGBColour.g = 0;
				booleanContrastRGBColour.b = 0;

				for(int col=0; col<RGB_NUM; col++)
				{
					double contrastThreshold;

					#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_APPLY_CONTRAST_THRESHOLD
						#ifdef OR_IMAGE_COMPARISON_DECISION_TREE_NORMALISE_RGB_MAP
						contrastThreshold = (OR_IMAGE_COMPARISON_DECISION_TREE_RGB_CONTRAST_THRESHOLD_FRACTION*MAX_RGB_VAL)*contrastThresholdNormalisationFactor;	//WRONG: normalisation should apply to entire image, not individual snapshots..
						#else
						contrastThreshold = (OR_IMAGE_COMPARISON_DECISION_TREE_RGB_CONTRAST_THRESHOLD_FRACTION*MAX_RGB_VAL);
						//contrastThreshold = (LUMINOSITY_CONTRAST_FRACTION_THRESHOLD*MAX_LUMINOSITY)*OR_IMAGE_COMPARISON_DECISION_TREE_CONTRAST_THRESHOLD_FACTOR;	//OLD
						#endif
					#else
					contrastThreshold = 0.0;
					#endif

					if(col == 0)
					{
						if(colCurrent.r > (colNext[comparisonDirection].r + contrastThreshold))
						{
							booleanContrastRGBColour.r = MAX_RGB_VAL;
						}
						else if(colCurrent.r <= (colNext[comparisonDirection].r - contrastThreshold))
						{
							booleanContrastRGBColour.r = DARK_RED_R;	//MAX_RGB_VAL/2;
						}
						else
						{

						}

					}
					else if(col == 1)
					{
						if(colCurrent.g > (colNext[comparisonDirection].g + contrastThreshold))
						{
							booleanContrastRGBColour.g = MAX_RGB_VAL;
						}
						else if(colCurrent.g <= (colNext[comparisonDirection].g - contrastThreshold))
						{
							booleanContrastRGBColour.g = DARK_GREEN_G;	//MAX_RGB_VAL/2;
						}
						else
						{

						}
					}
					else if(col == 2)
					{
						if(colCurrent.b > (colNext[comparisonDirection].b + contrastThreshold))
						{
							booleanContrastRGBColour.b = MAX_RGB_VAL;
						}
						else if(colCurrent.b <= (colNext[comparisonDirection].b - contrastThreshold))
						{
							booleanContrastRGBColour.b = DARK_BLUE_B;	//MAX_RGB_VAL/2;
						}
						else
						{

						}
					}
				}

				if(comparisonDirection == 0)
				{
					placepointPPM(pm, (x*2)+1, y*2, booleanContrastRGBColour.r, booleanContrastRGBColour.g, booleanContrastRGBColour.b);
				}
				else
				{
					placepointPPM(pm, (x*2), (y*2)+1, booleanContrastRGBColour.r, booleanContrastRGBColour.g, booleanContrastRGBColour.b);
				}
			}
		}
	}

	writeImage(imageFileName, pm);
}
#endif

void generateBooleanDiffMapFromRGBMaps(char * imageFileName, int imageWidth, int imageHeight, unsigned char * rgbMap1, unsigned char * rgbMap2)
{
	pixmap* pm;
	pm = newPixmap(imageWidth, imageHeight);

	for(int y = 0; y < imageHeight; y++)
	{
  		for(int  x = 0; x < imageWidth; x++)
		{
			colour colCurrent1;
			getRGBMapValues(x, y, imageWidth, rgbMap1, &colCurrent1);
			colour colCurrent2;
			getRGBMapValues(x, y, imageWidth, rgbMap2, &colCurrent2);

			colour booleanColDiff;
			booleanColDiff.r = 0;
			booleanColDiff.g = 0;
			booleanColDiff.b = 0;

			for(int col=0; col<RGB_NUM; col++)
			{
				if(col == 0)
				{
					int rDiff = abs(colCurrent1.r - colCurrent2.r);
					if((rDiff == MAX_RGB_VAL) || (rDiff == DARK_RED_R))	//positive <-> 0 || negative <-> 0: can be compensated by inserting data into multiple bins
					{
						booleanColDiff.r = MAX_RGB_VAL;
					}
					else if(rDiff == (MAX_RGB_VAL-DARK_RED_R))		//positive <-> negative: cannot be compensated by inserting data into multiple bins
					{
						booleanColDiff.r = DARK_RED_R;
					}
					else if(rDiff == 0)					//no difference: multiple bins not required
					{
						booleanColDiff.r = 0;
					}
					else
					{
						cout << "error: rDiff = " << rDiff << endl;
					}

				}
				else if(col == 1)
				{
					int gDiff = abs(colCurrent1.g - colCurrent2.g);
					if((gDiff == MAX_RGB_VAL) || (gDiff == DARK_GREEN_G))
					{
						booleanColDiff.g = MAX_RGB_VAL;
					}
					else if(gDiff == (MAX_RGB_VAL-DARK_GREEN_G))
					{
						booleanColDiff.g = DARK_GREEN_G;
					}
					else if(gDiff == 0)
					{
						booleanColDiff.g = 0;
					}
					else
					{
						cout << "error: gDiff = " << gDiff << endl;
					}
				}
				else if(col == 2)
				{
					int bDiff = abs(colCurrent1.b - colCurrent2.b);
					if((bDiff == MAX_RGB_VAL) || (bDiff == DARK_BLUE_B))
					{
						booleanColDiff.b = MAX_RGB_VAL;
					}
					else if(bDiff == (MAX_RGB_VAL-DARK_BLUE_B))
					{
						booleanColDiff.b = DARK_BLUE_B;
					}
					else if(bDiff == 0)
					{
						booleanColDiff.b = 0;
					}
					else
					{
						cout << "error: bDiff = " << bDiff << endl;
					}
				}
			}

			placepointPPM(pm, x, y, booleanColDiff.r, booleanColDiff.g, booleanColDiff.b);

		}
	}

	writeImage(imageFileName, pm);
}

/*
void createBooleanDiffMapFromRGBMaps(bool * diffbooleanDiffMap, int imageWidth, int imageHeight, unsigned char * rgbMap1, unsigned char * rgbMap2)
{
	for(int y = 0; y < imageHeight; y++)
	{
  		for(int  x = 0; x < imageWidth; x++)
		{
			colour colCurrent1;
			getRGBMapValues(x, y, imageWidth, rgbMap1, &colCurrent);
			colour colCurrent2;
			getRGBMapValues(x, y, imageWidth, rgbMap2, &colCurrent);

			bool diff = false;

			for(int col=0; col<RGB_NUM; col++)
			{
				if(col == 0)
				{
					if(colCurrent.r != colCurrent2.r)
					{
						diff = true;
					}

				}
				else if(col == 1)
				{
					if(colCurrent.g != colCurrentg.r)
					{
						diff = true;
					}
				}
				else if(col == 2)
				{
					if(colCurrent.b != colCurrentb.r)
					{
						diff = true;
					}
				}
			}

			setBooleanMapValue(x, y, imageWidth, diff, diffbooleanDiffMap);

		}
	}

}
*/

#ifdef USE_OR
void normaliseRGBMapBasedOnAverageLuminosity(unsigned char * normalisedRgbMap, int imageWidth, int imageHeight, unsigned char * rgbMap)
{
	double averageLuminosity = calculateAverageLuminosity(imageWidth, imageHeight, rgbMap);
	double averageNormalisedLuminosity = MAX_LUMINOSITY*OR_IMAGE_COMPARISON_DECISION_TREE_NORMALISE_RGB_MAP_AVERAGED_NORMALISED_LUMINOSITY_FRACTION;
	double normalisationFactor = averageNormalisedLuminosity/averageLuminosity;

	for(int y = 0; y < imageHeight; y++)
	{
  		for(int x = 0; x < imageWidth; x++)
		{
			colour col;
			getRGBMapValues(x, y, imageWidth, rgbMap, &col);

			colour colNormalised;
			colNormalised.r = col.r * normalisationFactor;
			colNormalised.g = col.g * normalisationFactor;
			colNormalised.b = col.b * normalisationFactor;

			setRGBMapValues(x, y, imageWidth, &colNormalised, normalisedRgbMap);
		}
	}
}

double calculateAverageLuminosity(int imageWidth, int imageHeight, unsigned char * rgbMap)
{
	double * luminosityMap = new double[imageWidth*imageHeight];		//CHECK THIS; these maps need to be created inside ORmethod.cpp main loop for efficiency
	createLuminosityMapFromRGBMap(imageWidth, imageHeight, rgbMap, luminosityMap);

	double totalLuminosity = 0.0;
	for(int y = 0; y < imageHeight; y++)
	{
  		for(int x = 0; x < imageWidth; x++)
		{
			double currentLuminosity = getLumOrContrastOrDepthMapValue(x, y, imageWidth, luminosityMap);
			totalLuminosity = totalLuminosity + currentLuminosity;
		}
	}

	double averageLuminosity = totalLuminosity/(imageWidth*imageHeight);
	return averageLuminosity;
}
#endif

void generatePixmapFromRGBmap(char * imageFileName, int imageWidth, int imageHeight, unsigned char * rgbMap)
{
	int x,y;
	pixmap* pm;

	pm = newPixmap(imageWidth, imageHeight);

	for(y = 0; y < imageHeight; y++)
	{
  		for(x = 0; x < imageWidth; x++)
		{

			colour col;
			getRGBMapValues(x, y, imageWidth,rgbMap,&col);
			placepointPPM(pm, x, y, col.r, col.g, col.b);
		}
	}

	writeImage(imageFileName, pm);
}



void generatePixmapFromEnumIntMap(char * filename, int imageWidth, int imageHeight, int * intMap)
{
	int x,y;
	pixmap* pm;

	pm = newPixmap(imageWidth, imageHeight);

	for(y = 0; y < imageHeight; y++)
	{
  		for(x = 0; x < imageWidth; x++)
		{
			int intVal;
			intVal = getIntMapValue(x, y, imageWidth, intMap);

			colour intValueColourRepresentation;
			if(intVal == 0)
			{
				intValueColourRepresentation.r = 0.0;
				intValueColourRepresentation.g = 0.0;
				intValueColourRepresentation.b = 0.0;
			}
			else if(intVal == 1)
			{
				intValueColourRepresentation.r = GREEN_R;
				intValueColourRepresentation.g = GREEN_G;
				intValueColourRepresentation.b = GREEN_B;
			}
			else if(intVal == 2)
			{
				intValueColourRepresentation.r = BLUE_R;
				intValueColourRepresentation.g = BLUE_G;
				intValueColourRepresentation.b = BLUE_B;
			}
			else if(intVal == 3)
			{
				intValueColourRepresentation.r = DARK_RED_R;
				intValueColourRepresentation.g = DARK_RED_G;
				intValueColourRepresentation.b = DARK_RED_B;
			}
			else if(intVal == 4)
			{
				intValueColourRepresentation.r = DARK_GREEN_R;
				intValueColourRepresentation.g = DARK_GREEN_G;
				intValueColourRepresentation.b = DARK_GREEN_B;
			}
			else if(intVal == 5)
			{
				intValueColourRepresentation.r = DARK_BLUE_R;
				intValueColourRepresentation.g = DARK_BLUE_G;
				intValueColourRepresentation.b = DARK_BLUE_B;
			}
			else if(intVal == 6)
			{
				intValueColourRepresentation.r = YELLOW_R;
				intValueColourRepresentation.g = YELLOW_G;
				intValueColourRepresentation.b = YELLOW_B;
			}
			else if(intVal == 7)
			{
				intValueColourRepresentation.r = CYAN_R;
				intValueColourRepresentation.g = CYAN_G;
				intValueColourRepresentation.b = CYAN_B;
			}
			else if(intVal == 8)
			{
				intValueColourRepresentation.r = MAGENTA_R;
				intValueColourRepresentation.g = MAGENTA_G;
				intValueColourRepresentation.b = MAGENTA_B;
			}
			else
			{
				//error;
				intValueColourRepresentation.r = RED_R;
				intValueColourRepresentation.g = RED_G;
				intValueColourRepresentation.b = RED_B;
			}

			placepointPPM(pm, x, y, intValueColourRepresentation.r, intValueColourRepresentation.g, intValueColourRepresentation.b);
		}
	}

	writeImage(filename, pm);
}









void generatePixmapFromLuminosityContrastMap(char * imageFileName, int imageWidth, int imageHeight, double * contrastMap)
{
	int x,y;
	pixmap* pm;

	pm = newPixmap(imageWidth, imageHeight);

	for(y = 0; y < imageHeight; y++)
	{
  		for(x = 0; x < imageWidth; x++)
		{
			double contrast;
			contrast = getLumOrContrastOrDepthMapValue(x, y, imageWidth, contrastMap);
			int contrastNormalised;
			#ifdef USE_OR
			if(OR_USE_CONTRAST_CALC_METHOD_C)
			{
				if(contrast != MAP_VALUE_OUT_OF_RANGE)
				{
					contrastNormalised = minInt((int)(contrast/MAX_LUMINOSITY_CONTRAST*MAX_RGB_VAL), MAX_RGB_VAL);
					#ifdef USE_CONTRAST_PIXMAP_INVERSE
					contrastNormalised = -(contrastNormalised-MAX_RGB_VAL);
					#endif

				}
				else
				{
					contrastNormalised = 0;
				}
			}
			else
			{
			#endif
				contrastNormalised = minInt((int)(contrast/MAX_LUMINOSITY_CONTRAST*MAX_RGB_VAL), MAX_RGB_VAL);
				#ifdef USE_CONTRAST_PIXMAP_INVERSE
				contrastNormalised = -(contrastNormalised-MAX_RGB_VAL);
				#endif
			#ifdef USE_OR
			}
			#endif
			placepointPPM(pm, x, y, contrastNormalised, contrastNormalised, contrastNormalised);
		}
	}

	writeImage(imageFileName, pm);
}

void generateRGBMapFromDepthMapOrDepthContrastMap(int imageWidth, int imageHeight, double * depthMap, unsigned char * rgbMap)
{
	for(int y = 0; y < imageHeight; y++)
	{
  		for(int x = 0; x < imageWidth; x++)
		{
			double depthOrDepthContrastVal;
			depthOrDepthContrastVal = getLumOrContrastOrDepthMapValue(x, y, imageWidth, depthMap);
			int depthOrDepthContrastValNormalised;
			#ifdef USE_OR
			if(OR_USE_CONTRAST_CALC_METHOD_C)
			{
				if(depthOrDepthContrastVal != MAP_VALUE_OUT_OF_RANGE)
				{
					//printf("\n %f", tAtSurface);
					if(depthOrDepthContrastVal == RT_RAYTRACE_NO_HIT_DEPTH_T)
					{
						depthOrDepthContrastVal = ESTIMATE_MAX_DEPTH_T_REAL;
					}
					depthOrDepthContrastValNormalised = minInt((int)(depthOrDepthContrastValNormalised/ESTIMATE_MAX_DEPTH_T_REAL*MAX_RGB_VAL), MAX_RGB_VAL);
					#ifdef USE_CONTRAST_PIXMAP_INVERSE
					depthOrDepthContrastValNormalised = -(depthOrDepthContrastValNormalised-MAX_RGB_VAL);
					#endif
				}
				else
				{
					depthOrDepthContrastValNormalised = 0.0;
				}
			}
			else
			{
			#endif
				//printf("\n %f", tAtSurface);
				if(depthOrDepthContrastVal == RT_RAYTRACE_NO_HIT_DEPTH_T)
				{
					depthOrDepthContrastVal = ESTIMATE_MAX_DEPTH_T_REAL;
				}
				depthOrDepthContrastValNormalised = minInt((int)(depthOrDepthContrastValNormalised/ESTIMATE_MAX_DEPTH_T_REAL*MAX_RGB_VAL), MAX_RGB_VAL);
				#ifdef USE_CONTRAST_PIXMAP_INVERSE
				depthOrDepthContrastValNormalised = -(depthOrDepthContrastValNormalised-MAX_RGB_VAL);
				#endif
			#ifdef USE_OR
			}
			#endif

			colour col;
			col.r = depthOrDepthContrastValNormalised;
			col.g = depthOrDepthContrastValNormalised;
			col.b = depthOrDepthContrastValNormalised;
			setRGBMapValues(x, y, imageWidth, &col, rgbMap);
		}
	}
}





void generateRGBMapFromDepthMapOrDepthContrastMapAdvanced(int imageWidth, int imageHeight, double * depthMap, unsigned char * rgbMap, double noHitDepth, double estimateMaxDepth)
{
	for(int y = 0; y < imageHeight; y++)
	{
  		for(int x = 0; x < imageWidth; x++)
		{
			double depthOrDepthContrastVal;
			depthOrDepthContrastVal = getLumOrContrastOrDepthMapValue(x, y, imageWidth, depthMap);
			int depthOrDepthContrastValNormalised;

			#ifdef USE_OR
			if(OR_USE_CONTRAST_CALC_METHOD_C)
			{
				if(depthOrDepthContrastVal != MAP_VALUE_OUT_OF_RANGE)
				{

					//printf("\n %f", tAtSurface);

					if(depthOrDepthContrastVal == noHitDepth)
					{
						depthOrDepthContrastVal = estimateMaxDepth;
					}
					depthOrDepthContrastValNormalised = minInt((int)(depthOrDepthContrastVal/estimateMaxDepth*MAX_RGB_VAL), MAX_RGB_VAL);
				#ifdef USE_CONTRAST_PIXMAP_INVERSE
					depthOrDepthContrastValNormalised = -(depthOrDepthContrastValNormalised-MAX_RGB_VAL);
				#endif

				}
				else
				{
					depthOrDepthContrastValNormalised = 0.0;
				}
			}
			else
			{
			#endif
				//printf("\n %f", tAtSurface);

				if(depthOrDepthContrastVal == noHitDepth)
				{
					depthOrDepthContrastVal = estimateMaxDepth;
				}
				depthOrDepthContrastValNormalised = minInt((int)(depthOrDepthContrastVal/estimateMaxDepth*MAX_RGB_VAL), MAX_RGB_VAL);
			#ifdef USE_CONTRAST_PIXMAP_INVERSE
				depthOrDepthContrastValNormalised = -(depthOrDepthContrastValNormalised-MAX_RGB_VAL);
			#endif

			#ifdef USE_OR
			}
			#endif


			colour col;
			col.r = depthOrDepthContrastValNormalised;
			col.g = depthOrDepthContrastValNormalised;
			col.b = depthOrDepthContrastValNormalised;
			setRGBMapValues(x, y, imageWidth, &col, rgbMap);
		}
	}
}



void generatePixmapFromDepthMapOrDepthContrastMap(char * imageFileName, int imageWidth, int imageHeight, double * depthMap)
{
	int x,y;
	pixmap* pm;

	pm = newPixmap(imageWidth, imageHeight);

	for(y = 0; y < imageHeight; y++)
	{
  		for(x = 0; x < imageWidth; x++)
		{
			int depthOrDepthContrastValueNormalised;
			double depthOrDepthContrastValue;
			depthOrDepthContrastValue = getLumOrContrastOrDepthMapValue(x, y, imageWidth, depthMap);

			#ifdef USE_OR
			if(OR_USE_CONTRAST_CALC_METHOD_C)
			{
				if(depthOrDepthContrastValue != MAP_VALUE_OUT_OF_RANGE)
				{
					//temp;
					/*
					if(strcmp(imageFileName, "cubeinitialViewMapViewIndex0.depth.train.ppm") == 0)
					{
						printf("\n %f", depthOrDepthContrastValue);
					}
					*/

					if(depthOrDepthContrastValue == RT_RAYTRACE_NO_HIT_DEPTH_T)
					{
						depthOrDepthContrastValue = ESTIMATE_MAX_DEPTH_T_REAL;
					}
					depthOrDepthContrastValueNormalised = minInt((int)(depthOrDepthContrastValue/ESTIMATE_MAX_DEPTH_T_REAL*MAX_RGB_VAL), MAX_RGB_VAL);
					#ifdef USE_CONTRAST_PIXMAP_INVERSE
					depthOrDepthContrastValueNormalised = -(depthOrDepthContrastValueNormalised-MAX_RGB_VAL);
					#endif

				}
				else
				{
					depthOrDepthContrastValueNormalised = 0.0;
				}
			}
			else
			{
			#endif
				if(depthOrDepthContrastValue == RT_RAYTRACE_NO_HIT_DEPTH_T)
				{
					depthOrDepthContrastValue = ESTIMATE_MAX_DEPTH_T_REAL;
				}
				depthOrDepthContrastValueNormalised = minInt((int)(depthOrDepthContrastValue/ESTIMATE_MAX_DEPTH_T_REAL*MAX_RGB_VAL), MAX_RGB_VAL);
				#ifdef USE_CONTRAST_PIXMAP_INVERSE
				depthOrDepthContrastValueNormalised = -(depthOrDepthContrastValueNormalised-MAX_RGB_VAL);
				#endif

			#ifdef USE_OR
			}
			#endif

			placepointPPM(pm, x, y, depthOrDepthContrastValueNormalised, depthOrDepthContrastValueNormalised, depthOrDepthContrastValueNormalised);
		}
	}

	writeImage(imageFileName, pm);
}

void generatePixmapFromDepthMapOrDepthContrastMapAdvanced(char * imageFileName, int imageWidth, int imageHeight, double * depthMap, double noHitDepth, double estimateMaxDepth)
{
	int x,y;
	pixmap* pm;

	pm = newPixmap(imageWidth, imageHeight);

	for(y = 0; y < imageHeight; y++)
	{
  		for(x = 0; x < imageWidth; x++)
		{

			int depthOrDepthContrastValueNormalised;
			double depthOrDepthContrastValue;
			depthOrDepthContrastValue = getLumOrContrastOrDepthMapValue(x, y, imageWidth, depthMap);

			#ifdef USE_OR
			if(OR_USE_CONTRAST_CALC_METHOD_C)
			{
				if(depthOrDepthContrastValue != MAP_VALUE_OUT_OF_RANGE)
				{

					//printf("\n %f", tAtSurface);

					if(depthOrDepthContrastValue == noHitDepth)
					{
						depthOrDepthContrastValue = estimateMaxDepth;
					}
					depthOrDepthContrastValueNormalised = minInt((int)(depthOrDepthContrastValue/estimateMaxDepth*MAX_RGB_VAL), MAX_RGB_VAL);
					#ifdef USE_CONTRAST_PIXMAP_INVERSE
					depthOrDepthContrastValueNormalised = -(depthOrDepthContrastValue-MAX_RGB_VAL);
					#endif
				}
				else
				{
					depthOrDepthContrastValueNormalised = 0.0;
				}
			}
			else
			{
			#endif
				//printf("\n %f", tAtSurface);

				if(depthOrDepthContrastValue == noHitDepth)
				{
					depthOrDepthContrastValue = estimateMaxDepth;
				}
				depthOrDepthContrastValueNormalised = minInt((int)(depthOrDepthContrastValue/estimateMaxDepth*MAX_RGB_VAL), MAX_RGB_VAL);
				#ifdef USE_CONTRAST_PIXMAP_INVERSE
				depthOrDepthContrastValueNormalised = -(depthOrDepthContrastValue-MAX_RGB_VAL);
				#endif

			#ifdef USE_OR
			}
			#endif

			placepointPPM(pm, x, y, depthOrDepthContrastValueNormalised, depthOrDepthContrastValueNormalised, depthOrDepthContrastValueNormalised);
		}
	}

	writeImage(imageFileName, pm);
}



void generateRGBMapFromNormalMap(int imageWidth, int imageHeight, double * normalMap, unsigned char * rgbMap)
{
	for(int y = 0; y < imageHeight; y++)
	{
  		for(int x = 0; x < imageWidth; x++)
		{
			vec norm;
			getNormalMapValue(x, y, imageWidth,normalMap,&norm);

			colour col;
			col.r = (int)(norm.x*MAX_RGB_VAL);			//(int)((norm.x+1.0)*128.0)
			col.g = (int)(norm.y*MAX_RGB_VAL);			//(int)((norm.y+1.0)*128.0)
			col.b = (int)(norm.z*MAX_RGB_VAL);			//(int)((norm.z+1.0)*128.0)
			setRGBMapValues(x, y, imageWidth, &col, rgbMap);

		}
	}
}


void generatePixmapFromNormalMap(char * imageFileName, int imageWidth, int imageHeight, double * normalMap)
{
	int x,y;
	pixmap* pm;

	pm = newPixmap(imageWidth, imageHeight);

	for(y = 0; y < imageHeight; y++)
	{
  		for(x = 0; x < imageWidth; x++)
		{
			vec norm;
			getNormalMapValue(x, y, imageWidth,normalMap,&norm);
			placepointPPM(pm, x, y, (int)(norm.x*MAX_RGB_VAL), (int)(norm.y*MAX_RGB_VAL), (int)(norm.z*MAX_RGB_VAL));
			//placepointPPM(nm, x, y, (int)((norm.x+1.0)*128.0), (int)((norm.y+1.0)*128.0), (int)((norm.z+1.0)*128.0));
		}
	}

	writeImage(imageFileName, pm);
}

void generatePixmapFromLuminosityMap(char * imageFileName, int imageWidth, int imageHeight, double * luminosityMap)
{
	int x,y;
	pixmap* pm;

	pm = newPixmap(imageWidth, imageHeight);

	for(y = 0; y < imageHeight; y++)
	{
  		for(x = 0; x < imageWidth; x++)
		{
			double luminosity;
			luminosity = getLumOrContrastOrDepthMapValue(x, y, imageWidth, luminosityMap);
			int luminosityNormalised = minInt((int)(luminosity/MAX_LUMINOSITY*MAX_RGB_VAL), MAX_RGB_VAL);
		#ifdef USE_CONTRAST_PIXMAP_INVERSE
			luminosityNormalised = -(luminosityNormalised-MAX_RGB_VAL);
		#endif
			placepointPPM(pm, x, y, luminosityNormalised, luminosityNormalised, luminosityNormalised);
		}
	}

	writeImage(imageFileName, pm);
}



void generatePixmapFromBooleanMap(char * imageFileName, int imageWidth, int imageHeight, bool * booleanMap)
{
	int x,y;
	pixmap* pm;

	pm = newPixmap(imageWidth, imageHeight);

	for(y = 0; y < imageHeight; y++)
	{
  		for(x = 0; x < imageWidth; x++)
		{
		#ifdef USE_BOOLEAN_PIXMAP_DOT_ENHANCEMENT
			#ifdef USE_BOOLEAN_PIXMAP_INVERSE
				int r = MAX_RGB_VAL;
				int g = MAX_RGB_VAL;
				int b = MAX_RGB_VAL;
			#else
				int r = 0;
				int g = 0;
				int b = 0;
			#endif
				placepointPPM(pm, x, y, r, g, b);
		#else
			bool val = getBooleanMapValue(x, y, imageWidth, booleanMap);
			int r;
			int g;
			int b;

			if(val == true)
			{
			#ifdef USE_BOOLEAN_PIXMAP_INVERSE
				r = MAX_RGB_VAL;
				g = MAX_RGB_VAL;
				b = MAX_RGB_VAL;
			#else
				r = 0;
				g = 0;
				b = 0;
			#endif

				placepointPPM(pm, x, y, MAX_RGB_VAL, MAX_RGB_VAL, MAX_RGB_VAL);
			}
			else
			{
			#ifdef USE_BOOLEAN_PIXMAP_INVERSE
				r = 0;
				g = 0;
				b = 0;
			#else
				r = MAX_RGB_VAL;
				g = MAX_RGB_VAL;
				b = MAX_RGB_VAL;
			#endif
				placepointPPM(pm, x, y, 0, 0, 0);
			}

		#endif

		}
	}

#ifdef USE_BOOLEAN_PIXMAP_DOT_ENHANCEMENT
	for(y = 0; y < imageHeight; y++)
	{
  		for(x = 0; x < imageWidth; x++)
		{
			bool val;
			val = getBooleanMapValue(x, y, imageWidth, booleanMap);
			int r = 0;
			int g = 0;
			int b = 0;
			if(val == true)
			{
				r = BOOLEAN_PIXMAP_DOT_RED;
				g = BOOLEAN_PIXMAP_DOT_GREEN;
				b = BOOLEAN_PIXMAP_DOT_BLUE;
				for(int ky = y-BOOLEAN_PIXMAP_DOT_ENHANCEMENT; ky <= y+BOOLEAN_PIXMAP_DOT_ENHANCEMENT; ky++)
				{
					for(int kx = x-BOOLEAN_PIXMAP_DOT_ENHANCEMENT; kx <= x+BOOLEAN_PIXMAP_DOT_ENHANCEMENT; kx++)
					{
						if((ky >= 0) && (ky < imageHeight))
						{
							if((kx >= 0) && (kx < imageWidth))
							{
								placepointPPM(pm, kx, ky, r, g, b);
							}
						}
					}
				}
			}
		}
	}
#endif

	writeImage(imageFileName, pm);
}


void writeImage(char * imageFileName, pixmap * pm)
{
	writePPM(imageFileName, pm);
	freePixmap(pm);
}

void readImage(char * imageFileName, unsigned char * rgbMap)
{
	pixmap * rgbPixMap;
	#ifdef RT_DEBUG
	//cout << "rgbPixMap = loadPPM(" << imageFileName << ");" << endl;
	#endif
	rgbPixMap = loadPPM(imageFileName);

	#ifdef RT_DEBUG
	//cout << "createRGBMapFromPixmapImage(rgbPixMap, rgbMap);" << endl;
	#endif
	createRGBMapFromPixmapImage(rgbPixMap, rgbMap);

	freePixmap(rgbPixMap);
}

void readImage(string * imageFileName, unsigned char * rgbMap)
{
	char * imageFileNameCharStar = const_cast<char*>(imageFileName->c_str());

	pixmap * rgbPixMap;
	#ifdef RT_DEBUG
	//cout << "rgbPixMap = loadPPM(" << imageFileName << ");" << endl;
	#endif
	rgbPixMap = loadPPM(imageFileNameCharStar);

	#ifdef RT_DEBUG
	//cout << "createRGBMapFromPixmapImage(rgbPixMap, rgbMap);" << endl;
	#endif
	createRGBMapFromPixmapImage(rgbPixMap, rgbMap);

	freePixmap(rgbPixMap);
}






















void generatePixmapFromDepthMap24Bit(char * imageFileName, int imageWidth, int imageHeight, double * depthMap, double depthScale, double depthOffset)
{
	int x,y;
	pixmap* pm;

	pm = newPixmap(imageWidth, imageHeight);

	for(y = 0; y < imageHeight; y++)
	{
  		for(x = 0; x < imageWidth; x++)
		{
			int depthOrDepthContrastValueNormalised;
			double depthOrDepthContrastValue;
			depthOrDepthContrastValue = getLumOrContrastOrDepthMapValue(x, y, imageWidth, depthMap);

			if(depthOrDepthContrastValue == RT_RAYTRACE_NO_HIT_DEPTH_T)
			{
				depthOrDepthContrastValue = ESTIMATE_MAX_DEPTH_T_REAL;
			}

			colour depthMap24BitPixelValue;
			calculate24BitDepthPixmapPixelFromDepth(depthOrDepthContrastValue, depthScale, depthOffset, &depthMap24BitPixelValue);

			placepointPPM(pm, x, y, depthMap24BitPixelValue.r, depthMap24BitPixelValue.g, depthMap24BitPixelValue.b);
		}
	}

	writeImage(imageFileName, pm);
}



void createDepthMapFromDepth24BitPixmapImage(pixmap * depth24BitPixMap, double * depthMap, double depthScale, double depthOffset)
{

	int imageWidth = depth24BitPixMap->wide;
	int imageHeight =  depth24BitPixMap->high;

	//fill luminosityMap
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			int pixelPositionInPixmap = y*imageWidth*3+x*3;
			colour depthMap24BitPixelValue;
			calculateColourFromPixmapPixel(depth24BitPixMap, pixelPositionInPixmap, &depthMap24BitPixelValue);
			double depth = calculateDepthFrom24BitDepthValue(&depthMap24BitPixelValue, depthScale, depthOffset);

			if(depth == ESTIMATE_MAX_DEPTH_T_REAL)
			{
				depth = RT_RAYTRACE_NO_HIT_DEPTH_T;
			}

			setLumOrContrastOrDepthMapValue(x, y, imageWidth, depth, depthMap);
		}
	}
}


double calculateDepthFrom24BitDepthValue(colour * depthMap24BitPixelValue, double depthScale, double depthOffset)
{
	double depth = 0.0;
	depth = depth + double(depthMap24BitPixelValue->r)*(MAX_RGB_VAL+1)*(MAX_RGB_VAL+1);
	depth = depth + double(depthMap24BitPixelValue->g)*(MAX_RGB_VAL+1);
	depth = depth + double(depthMap24BitPixelValue->b);
	depth = (depth * depthScale) - depthOffset;
	return depth;
}


void calculate24BitDepthPixmapPixelFromDepth(double depth, double depthScale, double depthOffset, colour * depthMap24BitPixelValue)
{
	if(depth < 0 )
	{
		exit(0);
	}
	int depthInt24Bit = (depth + depthOffset) / depthScale;
	//depthInt24Bit = depthInt24Bit%((MAX_RGB_VAL+1)*(MAX_RGB_VAL+1)*(MAX_RGB_VAL+1));
	depthMap24BitPixelValue->r = depthInt24Bit/((MAX_RGB_VAL+1)*(MAX_RGB_VAL+1));

	int redRemainder = depthInt24Bit%((MAX_RGB_VAL+1)*(MAX_RGB_VAL+1));
	depthMap24BitPixelValue->g = redRemainder/(MAX_RGB_VAL+1);

	int greenRemainder = redRemainder%(MAX_RGB_VAL+1);
	depthMap24BitPixelValue->b = greenRemainder;
}




void createRGBMapFromPixmapImage(pixmap * objectImage, unsigned char * rgbMap)
{

	int imageWidth = objectImage->wide;
	int imageHeight =  objectImage->high;

	//fill luminosityMap
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			int pixelPositionInPixmap = y*imageWidth*3+x*3;
			colour col;
			calculateColourFromPixmapPixel(objectImage, pixelPositionInPixmap, &col);
			setRGBMapValues(x, y, imageWidth, &col, rgbMap);
		}
	}
}


void calculateColourFromPixmapPixel(pixmap * pm, int pixelPositionInPixmap, colour * col)
{
	col->r = pm->pix[(int)pixelPositionInPixmap];
	col->g = pm->pix[(int)pixelPositionInPixmap+1];
	col->b = pm->pix[(int)pixelPositionInPixmap+2];
}



void createLuminosityMapFromPixmapImage(pixmap * objectImage, double * luminosityMap)
{
	int imageWidth = objectImage->wide;
	int imageHeight =  objectImage->high;

	//fill luminosityMap
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			int pixelPositionInPixmap = y*imageWidth*3+x*3;
			setLumOrContrastOrDepthMapValue(x, y, imageWidth, calculateLuminosityLevelFromPixmapPixel(objectImage, pixelPositionInPixmap), luminosityMap);

		}
	}
}

double calculateLuminosityLevelFromPixmapPixel(pixmap * pm, int pixelPositionInPixmap)
{
	double luminosity;

	unsigned char r = pm->pix[(int)pixelPositionInPixmap];
	unsigned char g = pm->pix[(int)pixelPositionInPixmap+1];
	unsigned char b = pm->pix[(int)pixelPositionInPixmap+2];

	luminosity = (r+g+b);

	return luminosity;
}


void createLuminosityMapFromRGBMap(int imageWidth, int imageHeight, unsigned char * rgbMap, double * luminosityMap)
{
	//fill luminosityMap
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			double luminosityLevel = calculateLuminosityLevelFromRGBMap(x, y, imageWidth, rgbMap);
			setLumOrContrastOrDepthMapValue(x, y, imageWidth, luminosityLevel, luminosityMap);
		}
	}
}

double calculateLuminosityLevelFromRGBMap(int x, int y, int imageWidth, unsigned char * rgbMap)
{
	double luminosity;

	#ifdef OLDcalculateLuminosityLevelFromRGBMap
		unsigned char r = getRGBMapValue(x, y, imageWidth, RGB_RED, rgbMap);
		unsigned char g = getRGBMapValue(x, y, imageWidth, RGB_GREEN, rgbMap);
		unsigned char b = getRGBMapValue(x, y, imageWidth, RGB_BLUE, rgbMap);
		luminosity = (r+g+b);
	#else
		colour col;
		getRGBMapValues(x, y, imageWidth, rgbMap, &col);
		luminosity = calculateLuminosityLevelFromRGBVal(&col);
	#endif


	return luminosity;
}

double calculateLuminosityLevelFromRGBVal(colour * rgbVal)
{
	double luminosity;

	unsigned char r = rgbVal->r;
	unsigned char g = rgbVal->g;
	unsigned char b = rgbVal->b;

	luminosity = (r+g+b);

	return luminosity;
}





	//WARNING; no depth check!
void createLuminosityContrastMapFromRGBMap(int imageWidth, int imageHeight, unsigned char * rgbMap, double * luminosityContrastMap)
{
	double * luminosityMap = new double[imageWidth*imageHeight];

	createLuminosityMapFromRGBMap(imageWidth, imageHeight, rgbMap, luminosityMap);

	createContrastMapFromMap(imageWidth, imageHeight, luminosityMap, luminosityContrastMap);

	delete luminosityMap;
}


void createContrastMapFromMap(int imageWidth, int imageHeight, double * luminosityMap, double * contrastMap)
{
	int kernelWidth = DEFAULT_CONTRAST_MAP_GENERATION_KERNEL_WIDTH;
	int kernelHeight = DEFAULT_CONTRAST_MAP_GENERATION_KERNEL_HEIGHT;

	//now lead a 3x3 kernel across image and calculate areas of high contrast
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			double contrastVal = calculateContrastLevelWithinKernel(x, y, luminosityMap, kernelWidth, kernelHeight, imageWidth, imageHeight);
			setLumOrContrastOrDepthMapValue(x, y, imageWidth, contrastVal, contrastMap);
		}
	}
}





double calculateContrastLevelWithinKernel(int pixelX, int pixelY, double * luminosityMap, int kernelWidth, int kernelHeight, int imageWidth, int imageHeight)
{
	double contrastLevel = 0.0;

	if((kernelWidth >= 3) && (kernelHeight >= 3))
	{//luminosity contrast map is defined for pixels
		double centrePixelPositionInLummapLuminosity = getLumOrContrastOrDepthMapValue(pixelX, pixelY, imageWidth, luminosityMap);

		for(int y = pixelY-(kernelHeight/2); y<= pixelY+(kernelHeight/2); y++)
		{
			for(int x = pixelX-(kernelWidth/2); x<= pixelX+(kernelWidth/2); x++)
			{
				if((y >= 0) && (y <imageHeight))
				{//check kernel pix is within image

					if((x >= 0) && (x <imageWidth))
					{//check kernel pix is within image

						if((x == pixelX) && (y == pixelY))
						{

						}
						else
						{
							//calc diff lum diff between centre pixel and current surrounding kernel pixel
							double kernelCurrentPixelPositionInLummapLuminosity = getLumOrContrastOrDepthMapValue(x, y, imageWidth, luminosityMap);
							double currentContrastLevel = absDouble(centrePixelPositionInLummapLuminosity - kernelCurrentPixelPositionInLummapLuminosity);
							#ifdef USE_OR
							if(OR_USE_CONTRAST_CALC_METHOD_B)
							{
								contrastLevel = contrastLevel + currentContrastLevel;
							}
							else
							{
							#endif
								contrastLevel = maxDouble(contrastLevel, currentContrastLevel);
							#ifdef USE_OR
							}
							#endif
						}
					}
				}
			}
		}
	}
	else if((kernelWidth == 2) && (kernelHeight == 2))
	{//NEW: luminosity contrast map is defined for interpixels, with the last row and last column of the contrast map being null defined

		if(pixelY < (imageHeight-1))
		{//check kernel pix is within image

			if(pixelX < (imageWidth-1))
			{//check kernel pix is within image

				for(int y = pixelY; y<= pixelY+1; y++)
				{
					double pixelLuminosityMeasurement = getLumOrContrastOrDepthMapValue(pixelX, y, imageWidth, luminosityMap);
					double adjacentPixelLuminosityMeasurement = getLumOrContrastOrDepthMapValue(pixelX+1, y, imageWidth, luminosityMap);

					double currentContrastLevel = absDouble(pixelLuminosityMeasurement - adjacentPixelLuminosityMeasurement);

					contrastLevel = contrastLevel + currentContrastLevel;
				}

				for(int x = pixelX; x<= pixelX+1; x++)
				{
					double pixelLuminosityMeasurement = getLumOrContrastOrDepthMapValue(x, pixelY, imageWidth, luminosityMap);
					double adjacentPixelLuminosityMeasurement = getLumOrContrastOrDepthMapValue(x, pixelY+1, imageWidth, luminosityMap);

					double currentContrastLevel = absDouble(pixelLuminosityMeasurement - adjacentPixelLuminosityMeasurement);

					contrastLevel = contrastLevel + currentContrastLevel;
				}
			}
			else
			{
				contrastLevel = MAP_VALUE_OUT_OF_RANGE;
			}
		}
		else
		{
			contrastLevel = MAP_VALUE_OUT_OF_RANGE;
		}
	}
	else
	{
		cout << "error: invalid contrast map generation kernel width and/or height" << endl;
		exit(0);
	}

	return contrastLevel;
}




double calculateContrastLevelWithinKernelRGBComponent(int pixelX, int pixelY, unsigned char * rgbMap, int rgbComponent, int kernelWidth, int kernelHeight, int imageWidth, int imageHeight)
{
	double contrastLevel = 0.0;

	if((kernelWidth >= 3) && (kernelHeight >= 3))
	{//luminosity contrast map is defined for pixels
		double centrePixelPositionInLummapLuminosity = getRGBMapValue(pixelX, pixelY, imageWidth, rgbComponent, rgbMap);

		for(int y = pixelY-(kernelHeight/2); y<= pixelY+(kernelHeight/2); y++)
		{
			for(int x = pixelX-(kernelWidth/2); x<= pixelX+(kernelWidth/2); x++)
			{
				if((y >= 0) && (y <imageHeight))
				{//check kernel pix is within image

					if((x >= 0) && (x <imageWidth))
					{//check kernel pix is within image

						if((x == pixelX) && (y == pixelY))
						{

						}
						else
						{
							//calc diff lum diff between centre pixel and current surrounding kernel pixel

							double kernelCurrentPixelPositionInLummapLuminosity = getRGBMapValue(x, y, imageWidth, rgbComponent, rgbMap);
							double currentContrastLevel = absDouble(centrePixelPositionInLummapLuminosity - kernelCurrentPixelPositionInLummapLuminosity);
							#ifdef USE_OR
							if(OR_USE_CONTRAST_CALC_METHOD_B)
							{
								contrastLevel = contrastLevel + currentContrastLevel;
							}
							else
							{
							#endif
								contrastLevel = maxDouble(contrastLevel, currentContrastLevel);
							#ifdef USE_OR
							}
							#endif
						}
					}
				}
			}
		}
	}
	else if((kernelWidth == 2) && (kernelHeight == 2))
	{//NEW: luminosity contrast map is defined for interpixels, with the last row and last column of the contrast map being null defined

		if(pixelY < (imageHeight-1))
		{//check kernel pix is within image

			if(pixelX < (imageWidth-1))
			{//check kernel pix is within image

				for(int y = pixelY; y<= pixelY+1; y++)
				{
					double pixelLuminosityMeasurement = getRGBMapValue(pixelX, y, imageWidth, rgbComponent, rgbMap);
					double adjacentPixelLuminosityMeasurement = getRGBMapValue(pixelX+1, y, imageWidth, rgbComponent, rgbMap);

					double currentContrastLevel = absDouble(pixelLuminosityMeasurement - adjacentPixelLuminosityMeasurement);

					contrastLevel = contrastLevel + currentContrastLevel;
				}

				for(int x = pixelX; x<= pixelX+1; x++)
				{
					double pixelLuminosityMeasurement = getRGBMapValue(x, pixelY, imageWidth, rgbComponent, rgbMap);
					double adjacentPixelLuminosityMeasurement = getRGBMapValue(x, pixelY+1, imageWidth, rgbComponent, rgbMap);

					double currentContrastLevel = absDouble(pixelLuminosityMeasurement - adjacentPixelLuminosityMeasurement);

					contrastLevel = contrastLevel + currentContrastLevel;
				}
			}
			else
			{
				contrastLevel = MAP_VALUE_OUT_OF_RANGE;
			}
		}
		else
		{
			contrastLevel = MAP_VALUE_OUT_OF_RANGE;
		}
	}
	else
	{
		cout << "error: invalid contrast map generation kernel width and/or height" << endl;
		exit(0);
	}

	return contrastLevel;
}













void createLuminosityContrastBooleanMap(int imageWidth, int imageHeight, double * luminosityContrastMap, bool * luminosityContrastBooleanMap)
{
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			double luminosityContrastVal = getLumOrContrastOrDepthMapValue(x, y, imageWidth, luminosityContrastMap);
			bool luminosityContrastValPassedThreshold;

			if(luminosityContrastVal > EDGE_LUMINOSITY_CONTRAST_THRESHOLD)
			{
				#ifdef USE_OR
				if(OR_USE_CONTRAST_CALC_METHOD_C)
				{
					if(luminosityContrastVal != MAP_VALUE_OUT_OF_RANGE)
					{
						luminosityContrastValPassedThreshold = true;
					}
					else
					{
						luminosityContrastValPassedThreshold = false;
					}
				}
				else
				{
				#endif
					luminosityContrastValPassedThreshold = true;
				#ifdef USE_OR
				}
				#endif
			}
			else
			{
				luminosityContrastValPassedThreshold = false;
			}
			setBooleanMapValue(x, y, imageWidth, luminosityContrastValPassedThreshold, luminosityContrastBooleanMap);
		}
	}
}

void createLuminosityBooleanMap(int imageWidth, int imageHeight, double * luminosityMap, bool * luminosityBooleanMap)
{
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			double luminosityVal = getLumOrContrastOrDepthMapValue(x, y, imageWidth, luminosityMap);
			bool luminosityValPassedThreshold;
			if(luminosityVal > EDGE_LUMINOSITY_THRESHOLD)
			{
				luminosityValPassedThreshold = true;
			}
			else
			{
				luminosityValPassedThreshold = false;
			}
			setBooleanMapValue(x, y, imageWidth, luminosityValPassedThreshold, luminosityBooleanMap);
		}
	}
}







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
 * File Name: RTppm.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3e5b 03-September-2014
 *
 *******************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include "RTppm.h"

/*new 24bit pixmap*/
pixmap *newPixmap(int wide, int high)
{
	pixmap *pm = (pixmap*)malloc(sizeof(pixmap));
	if(!pm) 
	{
		return NULL;
	}

	pm->wide = wide;
	pm->high = high;
	pm->pix = (unsigned char*) malloc((long)wide*high*3);

	if(!pm->pix)
	{
		free(pm);
		return NULL;
	}
	return pm;
}

void freePixmap(pixmap *pm)
{
	free(pm->pix);
	free(pm);
}

pixmap *loadPPM(string fname)
{
	FILE *f;
	int high, wide;
	pixmap *npm;
	char c;

	if(fname != "")
	{
		f = fopen(fname.c_str(), "rb");
	}
	else
	{
		f = stdin;
	}
	if(!f)
	{ /*die("couldn't open file\n");*/
		return NULL;
	}

	fscanf(f, "P6 %c", &c);
	if(c == '#')
	{ /*Eat the comment.*/
		while(fgetc(f) != '\n')
		{
		}
	}
	else
	{  /*Oops, no comment after all.*/
		ungetc(c, f);
	}

	if(fscanf(f, "%i %i 255", &wide, &high) != 2)
	{
		return NULL;
	}

	fgetc(f);  /*eat the trailing white space*/

	npm = newPixmap(wide, high);

	if(!npm)
	{
		freePixmap(npm);
		fclose(f);
		return NULL;
	}

	if(fread(npm->pix, (long)wide*high*3,1, f) != 1)
	{
		freePixmap(npm);
		fclose(f);
		return NULL;
	}

	fclose(f);
	return npm;
}

void writePPM(string fname, pixmap *pm)
{
	FILE *f;

	if(fname != "")
	{
		f = fopen(fname.c_str(), "wb");
	}
	else
	{
		f = stdout;
	}
	if(!f)
	{
		return;
	}

	fprintf(f, "P6 %i %i 255 ", pm->wide, pm->high);
	fwrite(pm->pix, (long)pm->wide*pm->high*3, 1, f);
	fclose(f);
}

unsigned char* calcPixelAddress(pixmap *pm, int x, int y)
{
	return &pm->pix[((long)pm->wide*y + x)*3];
}

void placepointPPM(pixmap *pm, int x, int y, int r, int g, int b)
{
	int position = y*(pm->wide)*3+x*3;

	pm->pix[(int)position] = r;
	pm->pix[(int)position+1] = g;
	pm->pix[(int)position+2] = b;
}

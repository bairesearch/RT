 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: RTppm.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3q1a 05-June-2022
 * /
 *******************************************************************************/


#include "RTppm.hpp"

/*new 24bit pixmap*/
pixmap* RTppmClass::newPixmap(const int wide, const int high)
{
	pixmap* pm = (pixmap*)malloc(sizeof(pixmap));
	if(!pm)
	{
		return NULL;
	}

	pm->wide = wide;
	pm->high = high;
	pm->pix = (uchar*) malloc((int64_t)wide*high*3);

	if(!pm->pix)
	{
		free(pm);
		return NULL;
	}
	return pm;
}

void RTppmClass::freePixmap(pixmap* pm)
{
	free(pm->pix);
	free(pm);
}

pixmap* RTppmClass::loadPPM(const string fname)
{
	FILE* f;
	int high, wide;
	pixmap* npm;
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

	if(fread(npm->pix, (int64_t)wide*high*3,1, f) != 1)
	{
		freePixmap(npm);
		fclose(f);
		return NULL;
	}

	fclose(f);
	return npm;
}

void RTppmClass::writePPM(const string fname, const pixmap* pm)
{
	FILE* f;

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
	fwrite(pm->pix, (int64_t)pm->wide*pm->high*3, 1, f);
	fclose(f);
}

uchar* RTppmClass::calcPixelAddress(const pixmap* pm, const int x, const int y)
{
	return &pm->pix[((int64_t)pm->wide*y + x)*3];
}

void RTppmClass::placepointPPM(pixmap* pm, const int x, const int y, int r, int g, int b)
{
	int position = y*(pm->wide)*3+x*3;

	pm->pix[(int)position] = r;
	pm->pix[(int)position+1] = g;
	pm->pix[(int)position+2] = b;
}

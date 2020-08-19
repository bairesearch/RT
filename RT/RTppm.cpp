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
 * File Name: RTppm.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2020 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3n7e 17-August-2020
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
	pm->pix = (unsigned char*) malloc((int64_t)wide*high*3);

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

unsigned char* RTppmClass::calcPixelAddress(const pixmap* pm, const int x, const int y)
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

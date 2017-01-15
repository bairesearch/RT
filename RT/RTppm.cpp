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
 * File Name: RTppm.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3a11b 09-July-2012
 *
 *******************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include "RTppm.h"

/*new 24bit pixmap*/
pixmap *new_pixmap(int wide, int high)
{
  pixmap *pm = (pixmap*)malloc(sizeof(pixmap));
  if(!pm) return NULL;

  pm->wide = wide;
  pm->high = high;
  pm->pix = (unsigned char*) malloc((long)wide*high*3);

  if(!pm->pix){
    free(pm);
    return NULL;
  }
  return pm;
}

void free_pixmap(pixmap *pm)
{
  free(pm->pix);
  free(pm);
}

pixmap *load_ppm(char *fname)
{
  FILE *f;
  int high, wide;
  pixmap *npm;
  char c;

  if (fname != NULL)
    f = fopen(fname, "rb");
  else
    f = stdin;
  if(!f){ /*die("couldn't open file\n");*/
    return NULL;
  }

  fscanf(f, "P6 %c", &c);
  if(c == '#'){ /*Eat the comment.*/
   while(fgetc(f) != '\n') ;
  }else{  /*Oops, no comment after all.*/
    ungetc(c, f);
  }

  if(fscanf(f, "%i %i 255", &wide, &high) != 2){
    return NULL;
  }

  fgetc(f);  /*eat the trailing white space*/

  npm = new_pixmap(wide, high);

  if(!npm){
    free_pixmap(npm);
    fclose(f);
    return NULL;
  }

  if(fread(npm->pix, (long)wide*high*3,1, f) != 1){
    free_pixmap(npm);
    fclose(f);
    return NULL;
  }

  fclose(f);
  return npm;
}

void write_ppm(char *fname, pixmap *pm)
{
  FILE *f;

  if (fname != NULL)
    f = fopen(fname, "wb");
  else
    f = stdout;
  if(!f) return;

  fprintf(f, "P6 %i %i 255 ", pm->wide, pm->high);
  fwrite(pm->pix, (long)pm->wide*pm->high*3, 1, f);
  fclose(f);
}

unsigned char* calc_pixel_address(pixmap *pm, int x, int y)
{
  return &pm->pix[((long)pm->wide*y + x)*3];
}

void placepoint_ppm(pixmap *pm, int x, int y, int r, int g, int b)
{
	int position = y*(pm->wide)*3+x*3;
	/*
	unsigned char *position = calc_pixel_address(pm, x, y);


	int position = y*(pm->wide)*3+x*3;
	if(position > (pm->wide*pm->high*3))
	{
		printf("the point given does not lie on the pixmap");
		exit(0);
	}*/

	pm->pix[(int)position] = r;
	pm->pix[(int)position+1] = g;
	pm->pix[(int)position+2] = b;
}

/*
pixmap
*load_ppm(char *fname){
  FILE *f;
  int high, wide;
  pixmap *npm;
  char c;

  if (fname != NULL)
    f = fopen(fname, "rb");
  else
    f = stdin;
  if(!f){
   	printf("load_ppm error");
	exit(0);
    return NULL;
  }

  fscanf(f, "P6 %c", &c);
  if(c == '#'){
   while(fgetc(f) != '\n') ;
  }else{
    ungetc(c, f);
  }

  if(fscanf(f, "%i %i 255", &wide, &high) != 2){
   	printf("load_ppm error");
	exit(0);
    return NULL;
  }

  fgetc(f);

  npm = new_pixmap(wide, high);

  if(!npm){
   	printf("load_ppm error");
	exit(0);
    free_pixmap(npm);
    fclose(f);
    return NULL;
  }

  if(fread(npm->pix, (long)wide*high*3,1, f) != 1){
  	printf("load_ppm error");
	exit(0);
    free_pixmap(npm);
    fclose(f);
    return NULL;
  }

  fclose(f);
  return npm;
}
*/


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
 * File Name: RTparser.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3d1a 13-April-2014
 * Description: A simple parser for TAL files 
 *
 *******************************************************************************/





#ifndef HEADER_RT_PARSER
#define HEADER_RT_PARSER


#include <stdio.h>
#include "SHAREDvars.h"
#include "RTviewinfo.h"


#define TAL_EXTENSION ".tal"




typedef enum {
	POINTSOURCE, DIRECTIONAL,
} lightType;


/*
 * lightSource
 * Light source parameters
 */
class lightSource
{
public:

	lightSource(void);
	~lightSource(void);

	lightType type;

	vec pos;
	colour col;
};



typedef enum {
	/*BRICK, PLATE, TILE, DECAL, BASEPLATE, PRIM_QUAD, PRIM_TRI, SPHERE, CYLINDER, RECT_PRISM, UNKNOWN, - doesnt work G++ bug*/
	BASEPLATE, BRICK, CYLINDER, DECAL, PRIM_LINE, PLATE, PRIM_QUAD, PRIM_TRI, RECT_PRISM, TILE, SPHERE, UNKNOWN,

} pieceType;


/*
 * pieceInfo
 * standard attributes common to all pieces
 */
class pieceInfo
{
public:
	pieceInfo(void);
	~pieceInfo(void);

	pieceType type;		// the type of the piece

	colour col;			// the colour of the piece
	vec pos;			// position of the piece's origin

	double xrot; 			// rotations (in degrees) about the x, y and z axes respectively - not used for primitive parts
	double yrot;
	double zrot;

	vec vertex1Position;	//only used for PRIM_QUAD/PRIM_TRI
	vec vertex2Position;	//only used for PRIM_QUAD/PRIM_TRI
	vec vertex3Position;	//only used for PRIM_QUAD/PRIM_TRI
	vec vertex4Position;	//only used for PRIM_QUAD/PRIM_TRI
};


/*
 * brick_info, plate_info, tile_info, decalInfo, baseplate_info
 * structures to hold additional information about specific types of piece
 */



/* dimensionsInfo */
class dimensionsInfo
{
public:
	dimensionsInfo(void);
	~dimensionsInfo(void);

	double width;		// width of the object
	double length;		// length of the object
	double height;		// height of the object [not used for all objects, eg bricks dont use this but use a default height instead]
	int translucent;	// nonzero if TRANSLUCENT option is specified [OPTIONAL]
	int transparency;
	int is_invisible;	// nonzero if INVISIBLE was specified [not used for most objects, only used for baseplate]
};



/* decalInfo */
class decalInfo
{
public:
	decalInfo(void);
	~decalInfo(void);

	double width;		// width of the decal in the scene
	double length;		// length of the decal

	char *filename;		// name of the image to use

	int haveTransparent;	// nonzero if TRANSPARENTCOLOUR specified
	colour transparentcolour;	// the colour, if specified
};


/*
 * unknownInfo
 * Generic structure used to hold "unknown" commands; i.e., those not
 * handled above.  Parameters are stored as an array of
 * null-terminated char arrays, one element per parameter supplied.
 */
class unknownInfo
{
public:
	unknownInfo(void);
	~unknownInfo(void);

	char *commandString;	// the name of the unknown command

	int param_count;	// how many parameters
	char **params;		// the parameters
};


/*
 * Initialise the parser to take input from the given file.
 */
void initParser(FILE *f);



/*
 * Read in the viewport initialisation section from the input file;
 * return nonzero unless this fails.
 * Only meaningful if we're in the viewport initialisation section!
 */
int readViewport();


/* Return the details of the viewport description. */
ViewInfo *get_view_info();



/*
 * Read in the next light source command from the input file;
 * return nonzero until no more light sources are found.
 * Only meaningful if we're in the light sources section.
 */
int nextLightSource();


/* Return the details of the last light source read in. */
lightSource *get_light_info();



/*
 * Read the next scene description command from the input file;
 * return nonzero unless end of file is reached.
 * Only meaningful if we're in the scene description section.
 */
int nextSceneCommand();


/*
 * Return a pointer to a `pieceInfo' structure containing the details
 * of the last scene description command read in.
 * Beware -- this and the other get_*_info routines below return the
 * same structure every time, so you will have to copy any data out
 * each time or it will be overwritten!
 */
pieceInfo *getPieceInfo();

/*
 * Return a pointer to a `dimensionsInfo' structure.  Only meaningful if
 * the last scene description command was not a decal or unknown
 */
dimensionsInfo *getDimensionsInfo();



	//not tested;
/*
 * Return a pointer to a `decalInfo' structure.  Only meaningful if
 * the last scene description command was a DECAL.
 */
decalInfo *getDecalInfo();

/*
 * Return a pointer to an `unknownInfo' structure.  Only meaningful
 * if the last scene description command was not known to the parser.
 */
unknownInfo *getUnknownInfo();

void exitParser();


#endif

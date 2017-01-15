/*******************************************************************************
 * 
 * This file is part of OpenGIA.
 * 
 * OpenGIA is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation.
 * 
 * OpenGIA is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 * 
 * You should have received a copy of the GNU Affero General Public License
 * version 3 along with OpenGIA.  If not, see <http://www.gnu.org/licenses/>
 * for a copy of the AGPLv3 License.
 * 
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: RTparser.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3a12a 31-July-2012
 *
 *******************************************************************************/





#ifndef HEADER_RT_PARSER
#define HEADER_RT_PARSER

/*
#ifdef RTDEBUG
	#include <string>
	#include <iostream>
	#include <fstream>
	#include <time.h>
	#include <math.h>
	using namespace std;
#endif
*/


#include <stdio.h>
#include "SHAREDvars.h"
#include "RTviewinfo.h"


#define TAL_EXTENSION ".tal"




typedef enum {
	POINTSOURCE, DIRECTIONAL,
} light_type;


/*
 * light_source
 * Light source parameters
 */

class light_source
{
public:

	light_source(void);
	~light_source(void);

	light_type type;

	vec pos;
	colour col;
};
/*
typedef struct {
	light_type type;

	vec pos;
	colour col;
} light_source;
*/


typedef enum {
	/*BRICK, PLATE, TILE, DECAL, BASEPLATE, PRIM_QUAD, PRIM_TRI, SPHERE, CYLINDER, RECT_PRISM, UNKNOWN, - doesnt work G++ bug*/
	BASEPLATE, BRICK, CYLINDER, DECAL, PRIM_LINE, PLATE, PRIM_QUAD, PRIM_TRI, RECT_PRISM, TILE, SPHERE, UNKNOWN,

} piece_type;


/*
 * piece_info
 * standard attributes common to all pieces
 */
class piece_info
{
public:
	piece_info(void);
	~piece_info(void);

	piece_type type;		// the type of the piece

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
typedef struct {
	piece_type type;		// the type of the piece

	colour col;			// the colour of the piece
	vec pos;			// position of the piece's origin

	double xrot; 			// rotations (in degrees) about the x, y and z axes respectively - not used for primitive parts
	double yrot;
	double zrot;

	vec vertex1Position;	//only used for PRIM_QUAD/PRIM_TRI
	vec vertex2Position;	//only used for PRIM_QUAD/PRIM_TRI
	vec vertex3Position;	//only used for PRIM_QUAD/PRIM_TRI
	vec vertex4Position;	//only used for PRIM_QUAD/PRIM_TRI

} piece_info;
*/


/*
 * brick_info, plate_info, tile_info, decal_info, baseplate_info
 * structures to hold additional information about specific types of piece
 */




/*ADDED RB 11:43 15/9/03*/

/* dimensions_info */
class dimensions_info
{
public:
	dimensions_info(void);
	~dimensions_info(void);

	double width;		// width of the object
	double length;		// length of the object
	double height;		// height of the object [not used for all objects, eg bricks dont use this but use a default height instead]
	int translucent;	// nonzero if TRANSLUCENT option is specified [OPTIONAL]
	int transparency;
	int is_invisible;	// nonzero if INVISIBLE was specified [not used for most objects, only used for baseplate]
};
/*
typedef struct {
	double width;		// width of the object
	double length;		// length of the object
	double height;		// height of the object [not used for all objects, eg bricks dont use this but use a default height instead]
	int translucent;	// nonzero if TRANSLUCENT option is specified [OPTIONAL]
	int transparency;
	int is_invisible;	// nonzero if INVISIBLE was specified [not used for most objects, only used for baseplate]
} dimensions_info;
*/



/* decal_info */
class decal_info
{
public:
	decal_info(void);
	~decal_info(void);

	double width;		// width of the decal in the scene
	double length;		// length of the decal

	char *filename;		// name of the image to use

	int have_transparent;	// nonzero if TRANSPARENTCOLOUR specified
	colour transparentcolour;	// the colour, if specified
};
/*
typedef struct {
	double width;		// width of the decal in the scene
	double length;		// length of the decal

	char *filename;		// name of the image to use

	int have_transparent;	// nonzero if TRANSPARENTCOLOUR specified
	colour transparentcolour;	// the colour, if specified
} decal_info;
*/


/*
 * unknown_info
 * Generic structure used to hold "unknown" commands; i.e., those not
 * handled above.  Parameters are stored as an array of
 * null-terminated char arrays, one element per parameter supplied.
 */
class unknown_info
{
public:
	unknown_info(void);
	~unknown_info(void);

	char *command_string;	// the name of the unknown command

	int param_count;	// how many parameters
	char **params;		// the parameters
};
 /*
typedef struct {
	char *command_string;	// the name of the unknown command

	int param_count;	// how many parameters
	char **params;		// the parameters
} unknown_info;
*/


/*
 * Initialise the parser to take input from the given file.
 */
void init_parser(FILE *f);



/*
 * Read in the viewport initialisation section from the input file;
 * return nonzero unless this fails.
 * Only meaningful if we're in the viewport initialisation section!
 */
int read_viewport();


/* Return the details of the viewport description. */
view_info *get_view_info();



/*
 * Read in the next light source command from the input file;
 * return nonzero until no more light sources are found.
 * Only meaningful if we're in the light sources section.
 */
int next_light_source();


/* Return the details of the last light source read in. */
light_source *get_light_info();



/*
 * Read the next scene description command from the input file;
 * return nonzero unless end of file is reached.
 * Only meaningful if we're in the scene description section.
 */
int next_scene_command();


/*
 * Return a pointer to a `piece_info' structure containing the details
 * of the last scene description command read in.
 * Beware -- this and the other get_*_info routines below return the
 * same structure every time, so you will have to copy any data out
 * each time or it will be overwritten!
 */
piece_info *get_piece_info();

/*
 * Return a pointer to a `dimensions_info' structure.  Only meaningful if
 * the last scene description command was not a decal or unknown
 */
dimensions_info *get_dimensions_info();



	//not tested;
/*
 * Return a pointer to a `decal_info' structure.  Only meaningful if
 * the last scene description command was a DECAL.
 */
decal_info *get_decal_info();

/*
 * Return a pointer to an `unknown_info' structure.  Only meaningful
 * if the last scene description command was not known to the parser.
 */
unknown_info *get_unknown_info();

void exit_parser();


#endif

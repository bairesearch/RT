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
 * File Name: RTparser.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3m13c 22-February-2018
 * Description: A simple parser for TAL files
 * /
 *******************************************************************************/


#ifndef HEADER_RT_PARSER
#define HEADER_RT_PARSER

#include "SHAREDvars.hpp"
#include "RTviewinfo.hpp"


#define TAL_EXTENSION ".tal"




typedef enum {
	POINTSOURCE, DIRECTIONAL,
} lightType;


/*
 * RTlightSource
 * Light source parameters
 */
class RTlightSource
{
public:

	RTlightSource(void);
	~RTlightSource(void);

	lightType type;

	vec pos;
	colour col;
};



typedef enum {
	/*BRICK, PLATE, TILE, DECAL, BASEPLATE, PRIM_QUAD, PRIM_TRI, SPHERE, CYLINDER, RECT_PRISM, UNKNOWN, - doesnt work G++ bug*/
	BASEPLATE, BRICK, CYLINDER, DECAL, PRIM_LINE, PLATE, PRIM_QUAD, PRIM_TRI, RECT_PRISM, TILE, SPHERE, UNKNOWN,

} pieceType;


/*
 * RTpieceInfo
 * standard attributes common to all pieces
 */
class RTpieceInfo
{
public:
	RTpieceInfo(void);
	~RTpieceInfo(void);

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
 * brick_info, plate_info, tile_info, RTdecalInfo, baseplate_info
 * structures to hold additional information about specific types of piece
 */



/* RTdimensionsInfo*/
class RTdimensionsInfo
{
public:
	RTdimensionsInfo(void);
	~RTdimensionsInfo(void);

	double width;		// width of the object
	double length;		// length of the object
	double height;		// height of the object [not used for all objects, eg bricks dont use this but use a default height instead]
	int translucent;	// nonzero if TRANSLUCENT option is specified [OPTIONAL]
	int transparency;
	int is_invisible;	// nonzero if INVISIBLE was specified [not used for most objects, only used for baseplate]
};



/* RTdecalInfo*/
class RTdecalInfo
{
public:
	RTdecalInfo(void);
	~RTdecalInfo(void);

	double width;		// width of the decal in the scene
	double length;		// length of the decal

	char* filename;		// name of the image to use

	int haveTransparent;	// nonzero if TRANSPARENTCOLOUR specified
	colour transparentcolour;	// the colour, if specified
};


/*
 * RTunknownInfo
 * Generic structure used to hold "unknown" commands; i.e., those not
 * handled above.  Parameters are stored as an array of
 * null-terminated char arrays, one element per parameter supplied.
 */
class RTunknownInfo
{
public:
	RTunknownInfo(void);
	~RTunknownInfo(void);

	char* commandString;	// the name of the unknown command

	int param_count;	// how many parameters
	char* *params;		// the parameters
};


/*
 * Initialise the parser to take input from the given file.
 */
class RTparserClass
{
	public: void initParser(FILE* f);



/*
 * Read in the viewport initialisation section from the input file;
 * return nonzero unless this fails.
 * Only meaningful if we're in the viewport initialisation section!
 */
	public: int readViewport();


/* Return the details of the viewport description.*/
	public: RTviewInfo* get_view_info();



/*
 * Read in the next light source command from the input file;
 * return nonzero until no more light sources are found.
 * Only meaningful if we're in the light sources section.
 */
	public: int nextLightSource();


/* Return the details of the last light source read in.*/
	public: RTlightSource* get_light_info();



/*
 * Read the next scene description command from the input file;
 * return nonzero unless end of file is reached.
 * Only meaningful if we're in the scene description section.
 */
	public: int nextSceneCommand();


/*
 * Return a pointer to a `RTpieceInfo' structure containing the details
 * of the last scene description command read in.
 * Beware -- this and the other get_*_info routines below return the
 * same structure every time, so you will have to copy any data out
 * each time or it will be overwritten!
 */
	public: RTpieceInfo* getPieceInfo();

/*
 * Return a pointer to a `RTdimensionsInfo' structure.  Only meaningful if
 * the last scene description command was not a decal or unknown
 */
	public: RTdimensionsInfo* getDimensionsInfo();



	//not tested;
/*
 * Return a pointer to a `RTdecalInfo' structure.  Only meaningful if
 * the last scene description command was a DECAL.
 */
	private: RTdecalInfo* getDecalInfo();

/*
 * Return a pointer to an `RTunknownInfo' structure.  Only meaningful
 * if the last scene description command was not known to the parser.
 */
	private: RTunknownInfo* getUnknownInfo();

	public: void exitParser();
};


#endif

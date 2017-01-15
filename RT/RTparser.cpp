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
 * File Name: RTparser.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3c3h 19-November-2012
 * Description: A simple parser for TAL files
 *
 *******************************************************************************/



#include "RTparser.h"
#include <stdlib.h>
#include <string.h>

/* TRUE if string  s  is  S1  or  S2  */
#define string_is(s, S1, S2)	\
	(((s) != NULL) && ((strcmp(s, (S1)) == 0) || (strcmp(s, (S2)) == 0)))



static int is_initialised;	/* safety net for invigilant users! */
static int have_error;		/* have we encountered an error since init? */

static FILE *infile;		/* input file pointer */

static char *current_command;	/* name of current command */
static char *current_option;	/* internal use only! */

static char com_buf[256];


lightSource::lightSource(void)
{
}

lightSource::~lightSource(void)
{
}

pieceInfo::pieceInfo(void)
{
}

pieceInfo::~pieceInfo(void)
{
}

dimensionsInfo::dimensionsInfo(void)
{
}

dimensionsInfo::~dimensionsInfo(void)
{
}

decalInfo::decalInfo(void)
{
}

decalInfo::~decalInfo(void)
{
}

unknownInfo::unknownInfo(void)
{
}

unknownInfo::~unknownInfo(void)
{
}



static int parse_error(const char *msg)
{
	fprintf(stderr, "parse error: %s, current command is %s\n",
		msg, current_command);
	have_error = 1;

	return 0;
}

/*Read one byte in hex (between 0 and FF) from the string s*/
static int read_hex_byte(char *s)
{
	char	digit[3];
	int	num;

	digit[2] = '\0';

	digit[0] = s[0];
	digit[1] = s[1];
	sscanf(digit, "%x", &num);
	return	num;
}

/* Read a string of up to 255 non-whitespace chars */
static char* read_string()
{
	static char buf[256];

	if (fscanf(infile, " %255s", buf) == 1)
		return buf;
	else
		return 0;
}

void print_colour(colour *c);

/* convenience function */
static void next_option()
{
	current_option = read_string();
}


enum{ NUM_COLOURS = 13};

static char	*col_name[NUM_COLOURS] =
	{TAL_FILE_COLOUR_BLACK, TAL_FILE_COLOUR_BLUE, TAL_FILE_COLOUR_GREEN, TAL_FILE_COLOUR_CYAN, TAL_FILE_COLOUR_RED, TAL_FILE_COLOUR_MAGENTA, TAL_FILE_COLOUR_BROWN, TAL_FILE_COLOUR_LIGHTGREY, TAL_FILE_COLOUR_DARKGREY, TAL_FILE_COLOUR_YELLOW, TAL_FILE_COLOUR_WHITE, TAL_FILE_COLOUR_ORANGE, TAL_FILE_COLOUR_PURPLE};

static char	*col_value[NUM_COLOURS] =
	{TAL_FILE_COLOUR_BLACK_RGB, TAL_FILE_COLOUR_BLUE_RGB, TAL_FILE_COLOUR_GREEN_RGB, TAL_FILE_COLOUR_CYAN_RGB, TAL_FILE_COLOUR_RED_RGB, TAL_FILE_COLOUR_MAGENTA_RGB, TAL_FILE_COLOUR_BROWN_RGB, TAL_FILE_COLOUR_LIGHTGREY_RGB, TAL_FILE_COLOUR_DARKGREY_RGB, TAL_FILE_COLOUR_YELLOW_RGB, TAL_FILE_COLOUR_WHITE_RGB, TAL_FILE_COLOUR_ORANGE_RGB, TAL_FILE_COLOUR_PURPLE_RGB};

/* Read a colour (three values between 0 and 255) from infile */
static colour read_colour()
{
	colour c;
	int r, g, b;
	char *name;
	char	digit[3];
	int i;

	int foundColourMatch = 0;

	next_option();
	name = current_option;

	for(i = 0; i < NUM_COLOURS; i++){
		if(strcmp(name, col_name[i]) == 0){
			name = col_value[i];
			foundColourMatch = 1;
			break;
		}
	}

	if(foundColourMatch)
	{//FORMAT; blue
		c.r = read_hex_byte(name);
		c.g = read_hex_byte(name+2);
		c.b = read_hex_byte(name+4);
	}
	else
	{//FORMAT; rgb:FF00FF
		c.r = read_hex_byte(name+4);
		c.g = read_hex_byte(name+6);
		c.b = read_hex_byte(name+8);
	}

	return c;
}

/* Read a vector (three doubles) from infile */
static vec read_vec()
{
	vec v;

	if (fscanf(infile, " %lg %lg %lg", &v.x, &v.y, &v.z) != 3)
		parse_error("could not read vector");
	return v;
}

/* Read a double from infile */
static double read_double()
{
	double d;

	if (fscanf(infile, " %lg", &d) != 1)
		parse_error("could not read double");

	return d;
}

/* Read a positive integer from infile */
static int read_int()
{
	int i;

	if (fscanf(infile, " %d", &i) != 1)
		parse_error("could not read positive integer");

	return i;
}


/* Read commands until a non-comment is found.  Sets current_command. */
static void next_command()
{
	int c;

	while ((current_command = read_string())) {

		if (current_command != NULL
		 && (strcmp(current_command, "COMMENT") == 0
		 ||  strcmp(current_command, "comment") == 0
		 ||  strcmp(current_command, "#") == 0)) {

			/* discard rest of line */
			while ((c = getc(infile)) != EOF)
				if (c == '\n') break;

		} else {
			/* this is a non-comment command */
			sprintf(com_buf, "%s", current_command);
			current_command = com_buf;
			break;
		}
	}
}


/* Initialise the parser to take input from the given file */
void initParser(FILE *f)
{
	is_initialised = 1;
	have_error = 0;
	infile = f;
	current_command = "";
	current_option = "";
}

void exitParser()
{
	fclose(infile);
}



static dimensionsInfo	_dimensions_info;
static ViewInfo	_view_info;
static lightSource	_light_source;
static pieceInfo	_piece_info;

	//not tested
static decalInfo	_decal_info;
static unknownInfo	_unknown_info;


/* Read in the viewport initialisation section */
int readViewport()
{
	next_command();
	if (string_is(current_command, "IMAGESIZE", "imagesize")) {
		_view_info.imageWidth = read_int();
		_view_info.imageHeight = read_int();
	} else
		return parse_error("IMAGESIZE expected");

	next_command();
	if (string_is(current_command, "EYE", "eye")) {
		_view_info.eye = read_vec();
	} else
		return parse_error("EYE expected");

	next_command();
	if (string_is(current_command, "VIEWAT", "viewAt")) {
		_view_info.viewAt = read_vec();
	} else
		return parse_error("VIEWAT expected");

	next_command();
	if (string_is(current_command, "VIEWUP", "viewUp")) {
		_view_info.viewUp = read_vec();
	} else
		return parse_error("VIEWUP expected");

	next_command();
	if (string_is(current_command, "FOCAL", "focal")) {
		_view_info.focalLength = read_double();
	} else
		return parse_error("FOCAL expected");

	next_command();
	if (string_is(current_command, "VIEWSIZE", "viewsize")) {
		_view_info.viewWidth = read_double();
		_view_info.viewHeight = read_double();
	} else
		return parse_error("VIEWSIZE expected");

	return 1;
}


ViewInfo *get_view_info()
{
	return &_view_info;
}



int nextLightSource()
{
	next_command();
	if (string_is(current_command, "POINTSOURCE", "pointsource"))
		_light_source.type = POINTSOURCE;
	else if (string_is(current_command, "DIRECTIONAL", "directional"))
		_light_source.type = DIRECTIONAL;
	else
		return 0;

	_light_source.pos = read_vec();
	_light_source.col = read_colour();

	return 1;
}


lightSource *get_light_info()
{
	return &_light_source;
}





static void read_options(pieceType type);



int nextSceneCommand()
{
	if (current_command == NULL)
		return 0;
	if (string_is(current_command, TAL_FILE_TYPE_BRICK, "brick"))
		_piece_info.type = BRICK;
	else if (string_is(current_command, TAL_FILE_TYPE_PLATE, "plate"))
		_piece_info.type = PLATE;
	else if (string_is(current_command, TAL_FILE_TYPE_TILE, "tile"))
		_piece_info.type = TILE;
	else if (string_is(current_command, TAL_FILE_TYPE_DECAL, "decal"))
		_piece_info.type = DECAL;
	else if (string_is(current_command, TAL_FILE_TYPE_BASEPLATE, "baseplate"))
		_piece_info.type = BASEPLATE;
	else if (string_is(current_command, TAL_FILE_TYPE_PRIM_QUAD, "prim_quad"))
		_piece_info.type = PRIM_QUAD;
	else if (string_is(current_command, TAL_FILE_TYPE_PRIM_TRI, "prim_tri"))
		_piece_info.type = PRIM_TRI;
	else if (string_is(current_command, TAL_FILE_TYPE_SPHERE, "sphere"))
		_piece_info.type = SPHERE;
	else if (string_is(current_command, TAL_FILE_TYPE_CYLINDER, "cylinder"))
		_piece_info.type = CYLINDER;
	else if (string_is(current_command, TAL_FILE_TYPE_RECT_PRISM, "rect_prism"))
		_piece_info.type = RECT_PRISM;
	else if (string_is(current_command, TAL_FILE_TYPE_PRIM_LINE, "prim_line"))
		_piece_info.type = PRIM_LINE;
	else
		_piece_info.type = UNKNOWN;

	_piece_info.col = read_colour();

	if(_piece_info.type == PRIM_QUAD)
	{
		_piece_info.vertex1Position = read_vec();
		_piece_info.vertex2Position = read_vec();
		_piece_info.vertex3Position = read_vec();
		_piece_info.vertex4Position = read_vec();
		_piece_info.xrot = 0.0;
		_piece_info.yrot = 0.0;
		_piece_info.zrot = 0.0;
		_piece_info.pos.x = 0.0;
		_piece_info.pos.y = 0.0;
		_piece_info.pos.z = 0.0;
	}
	else if(_piece_info.type == PRIM_TRI)
	{
		_piece_info.vertex1Position = read_vec();
		_piece_info.vertex2Position = read_vec();
		_piece_info.vertex3Position = read_vec();
		_piece_info.xrot = 0.0;
		_piece_info.yrot = 0.0;
		_piece_info.zrot = 0.0;
		_piece_info.pos.x = 0.0;
		_piece_info.pos.y = 0.0;
		_piece_info.pos.z = 0.0;
	}
	else if(_piece_info.type == PRIM_LINE)
	{
		_piece_info.vertex1Position = read_vec();
		_piece_info.vertex2Position = read_vec();
		_piece_info.xrot = 0.0;
		_piece_info.yrot = 0.0;
		_piece_info.zrot = 0.0;
		_piece_info.pos.x = 0.0;
		_piece_info.pos.y = 0.0;
		_piece_info.pos.z = 0.0;
	}
	else
	{
		//not used for prim quad or prim tri
		_piece_info.pos = read_vec();
		_piece_info.xrot = read_double();
		_piece_info.yrot = read_double();
		_piece_info.zrot = read_double();
		read_options(_piece_info.type);
	}

	while(!string_is(current_option, "END", "end")) next_option();
	next_command();

	return 1;
}

/*Read in unknown piece.*/
void read_unknown(void)
{
	char	**params;
	int	param_count;

	_unknown_info.commandString = strdup(current_command);

	params = (char**)malloc(0);
	next_option();
	param_count = 0;

	while(!string_is(current_option, "END", "end")){
		params = (char**)realloc(params, (param_count+1)*sizeof(char*));
		params[param_count] = strdup(current_option);
		param_count++;
		next_option();
	}

	_unknown_info.param_count = param_count;
	_unknown_info.params = params;
}

static void mandatory_option(char *s)
{
 	next_option();
	if(strcmp(s, current_option))
		parse_error("mandatory option missing");
}


void read_options(pieceType type)
{
	if((type == BRICK) || (type == PLATE) || (type == TILE) || (type == BASEPLATE))
	{
		mandatory_option("width");
		_dimensions_info.width = read_double();
		mandatory_option("length");
		_dimensions_info.length = read_double();
		next_option();
		if(strcmp("translucent", current_option) == 0)
		{
			_dimensions_info.translucent = TRUE;
			_dimensions_info.transparency = read_double(); /*if translucent, read the transparency value*/
			//next_option();
		}
		/* only used for baseplate;
                 next_option();
		_dimensions_info.is_invisible = (strcmp("invisible", current_option) == 0);
		*/

	}
	else if((type == RECT_PRISM) || (type == CYLINDER) || (type == SPHERE))	//new part types added by RBB
	{
		mandatory_option("width");
		_dimensions_info.width = read_double();
		mandatory_option("length");
		_dimensions_info.length = read_double();
		mandatory_option("height");
		_dimensions_info.height = read_double();
		next_option();
		if(strcmp("translucent", current_option) == 0)
		{
			_dimensions_info.translucent = TRUE;
			_dimensions_info.transparency = read_double(); /*if translucent, read the transparency value*/
			//next_option();
		}


	}
	else if(type == DECAL)	//not tested
	{
		mandatory_option("width");
		_decal_info.width = read_double();
		mandatory_option("length");
		_decal_info.length = read_double();
		mandatory_option("image");
		next_option();
		_decal_info.filename = strdup(current_option);
		next_option();
		_decal_info.haveTransparent =
			(strcmp("translucent_colour",
				current_option) == 0);
		if(_decal_info.haveTransparent){
			_decal_info.transparentcolour = read_colour();
		}
	}
	else if(type == UNKNOWN)		//not tested
	{
		read_unknown();
	}
}

dimensionsInfo *getDimensionsInfo() { return &_dimensions_info; }
pieceInfo *getPieceInfo() { return &_piece_info; }

	//not tested
decalInfo *getDecalInfo() { return &_decal_info; }
unknownInfo *getUnknownInfo() { return &_unknown_info; }

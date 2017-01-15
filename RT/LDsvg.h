/*******************************************************************************
 *
 * File Name: LDsvg.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3a7b 09-June-2012
 *
 *******************************************************************************/



#ifndef HEADER_LD_SVG
#define HEADER_LD_SVG

#include "SHAREDglobalDefs.h"
#include "SHAREDvars.h"
#include "LDreferenceClass.h"

void writeSVGFooter(ofstream * writeFileObject);
void writeSVGHeader(ofstream * writeFileObject);
void writeSVGLine(ofstream * writeFileObject, vec * pos1, vec * pos2, int col);
void writeSVGBox(ofstream * writeFileObject, vec * pos, double width, double height, int col, double boxOutlineWidth, bool useEllipse);
void writeSVGText(ofstream * writeFileObject, string text, vec * pos, int fontSize, int col);
void writeSVGBoxTransparent(ofstream * writeFileObject, vec * pos, double width, double height, int col, double boxOutlineWidth, bool useEllipse, double fillOpacity);

#endif


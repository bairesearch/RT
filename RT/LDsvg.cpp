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
 * File Name: LDsvg.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3c2a 19-October-2012
 *
 *******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;

#include "LDsvg.h"

bool writeSVGFile(string xmlFileName, XMLParserTag * firstTagInXMLFile)
{
	bool result = true;

	ofstream writeFileObject(xmlFileName.c_str());

	writeSVGHeader(&writeFileObject);

	if(!addTagLayerToFileObject(firstTagInXMLFile, &writeFileObject, 0))
	{
		result = false;
	}

	writeSVGFooter(&writeFileObject);

	//Added by RBB 30 August 2009 - required for Windows SW to re-read xml files
	writeFileObject.put(CHAR_NEWLINE); //(s.cStr())[i]

	writeFileObject.close();

	return result;
}


void writeSVGHeader(ofstream * writeFileObject)
{
	//string headerString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\"><svg version=\"1.1\" viewBox=\"-100 -100 1920 1400\" preserveAspectRatio=\"xMidYMid\" fill-rule=\"evenodd\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">";
	string headerString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\"><svg version=\"1.1\" viewBox=\"-400 -100 10000 2000\" preserveAspectRatio=\"xMidYMid\" fill-rule=\"evenodd\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">";
	for(int i = 0; i<headerString.length(); i++)
	{
		writeFileObject->put(headerString[i]);
	}
}

void writeSVGFooter(ofstream * writeFileObject)
{
	string footerString = "</svg>";
	for(int i = 0; i<footerString.length(); i++)
	{
		writeFileObject->put(footerString[i]);
	}
}



void writeSVGBox(XMLParserTag ** currentTag, vec * pos, double width, double height, int col, double boxOutlineWidth, bool useEllipse)
{
	colour colourrgb;
 	convertLdrawColourToDatFileRGB(col, &colourrgb);

	string boxOutlineWidthString;
	string xPosString;
	string yPosString;
	string widthString;
	string heightString;
	string rString;
	string gString;
	string bString;
	char boxOutlineWidthcharstar[10];
	char xPosStringcharstar[10];
	char yPosStringcharstar[10];
	char widthStringcharstar[10];
	char heightStringcharstar[10];
	char rStringcharstar[10];
	char gStringcharstar[10];
	char bStringcharstar[10];
	sprintf(boxOutlineWidthcharstar, "%0.3f", boxOutlineWidth);
	sprintf(xPosStringcharstar, "%d", (int)(pos->x - (width/2)));	//%d
	sprintf(yPosStringcharstar, "%d", (int)(pos->y - (height/2)));
	sprintf(rStringcharstar, "%d", (unsigned char)colourrgb.r);
	sprintf(gStringcharstar, "%d", (unsigned char)colourrgb.g);
	sprintf(bStringcharstar, "%d", (unsigned char)colourrgb.b);
	sprintf(widthStringcharstar, "%d", (int)width);
	sprintf(heightStringcharstar, "%d", (int)height);

	boxOutlineWidthString = boxOutlineWidthcharstar;
	xPosString = xPosStringcharstar;
	yPosString = yPosStringcharstar;
	rString = rStringcharstar;
	gString = gStringcharstar;
	bString = bStringcharstar;
	widthString = widthStringcharstar;
	heightString = heightStringcharstar;

	string svgText = "";

	if(useEllipse)
	{
		XMLParserTag * currentTagInBlock = *currentTag;
		currentTagInBlock->name = "ellipse";
		XMLParserAttribute * currentAttributeInBlock = currentTagInBlock->firstAttribute;
		currentAttributeInBlock->name = "cx";
		currentAttributeInBlock->value = xPosString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();		
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "cy";
		currentAttributeInBlock->value = yPosString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();		
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "rx";
		currentAttributeInBlock->value = widthString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();		
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "ry";
		currentAttributeInBlock->value = heightString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();			
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "fill";
		currentAttributeInBlock->value = "rgb(" + rString + "," + gString + "," + bString + ")";
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();	
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "stroke";
		currentAttributeInBlock->value = "black";
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();	
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "stroke-width";
		currentAttributeInBlock->value = boxOutlineWidthString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();			
								
		(*currentTag)->nextTag = new XMLParserTag();
		(*currentTag) = (*currentTag)->nextTag;

		//svgText = "<ellipse cx=\"" + xPosString + "\" cy=\"" + yPosString + "\" rx=\"" + widthString + "\" ry=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" />";
	}
	else
	{
		XMLParserTag * currentTagInBlock = *currentTag;
		currentTagInBlock->name = "rect";
		XMLParserAttribute * currentAttributeInBlock = currentTagInBlock->firstAttribute;
		currentAttributeInBlock->name = "x";
		currentAttributeInBlock->value = xPosString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();		
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "y";
		currentAttributeInBlock->value = yPosString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();		
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "width";
		currentAttributeInBlock->value = widthString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();		
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "height";
		currentAttributeInBlock->value = heightString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();			
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "fill";
		currentAttributeInBlock->value = "rgb(" + rString + "," + gString + "," + bString + ")";
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();	
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "stroke";
		currentAttributeInBlock->value = "black";
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();	
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "stroke-width";
		currentAttributeInBlock->value = boxOutlineWidthString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();		
	
		(*currentTag)->nextTag = new XMLParserTag();
		(*currentTag) = (*currentTag)->nextTag;
			
		//svgText = "<rect x=\"" + xPosString + "\" y=\"" + yPosString + "\" width=\"" + widthString + "\" height=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" />";
	}
}

void writeSVGBoxTransparent(XMLParserTag ** currentTag, vec * pos, double width, double height, int col, double boxOutlineWidth, bool useEllipse, double fillOpacity)
{
	colour colourrgb;
 	convertLdrawColourToDatFileRGB(col, &colourrgb);

	string boxOutlineWidthString;
	string xPosString;
	string yPosString;
	string widthString;
	string heightString;
	string rString;
	string gString;
	string bString;
	char boxOutlineWidthcharstar[10];
	char xPosStringcharstar[10];
	char yPosStringcharstar[10];
	char widthStringcharstar[10];
	char heightStringcharstar[10];
	char rStringcharstar[10];
	char gStringcharstar[10];
	char bStringcharstar[10];
	sprintf(boxOutlineWidthcharstar, "%0.3f", boxOutlineWidth);
	sprintf(xPosStringcharstar, "%d", (int)(pos->x - (width/2)));	//%d
	sprintf(yPosStringcharstar, "%d", (int)(pos->y - (height/2)));
	sprintf(rStringcharstar, "%d", (unsigned char)colourrgb.r);
	sprintf(gStringcharstar, "%d", (unsigned char)colourrgb.g);
	sprintf(bStringcharstar, "%d", (unsigned char)colourrgb.b);
	sprintf(widthStringcharstar, "%d", (int)width);
	sprintf(heightStringcharstar, "%d", (int)height);

	boxOutlineWidthString = boxOutlineWidthcharstar;
	xPosString = xPosStringcharstar;
	yPosString = yPosStringcharstar;
	rString = rStringcharstar;
	gString = gStringcharstar;
	bString = bStringcharstar;
	widthString = widthStringcharstar;
	heightString = heightStringcharstar;

	string svgText = "";

	char fillOpacityStringcharstar[10];
	sprintf(fillOpacityStringcharstar, "%0.3f", fillOpacity);
	string fillOpacityString = fillOpacityStringcharstar;

	if(useEllipse)
	{
		XMLParserTag * currentTagInBlock = *currentTag;
		currentTagInBlock->name = "ellipse";
		XMLParserAttribute * currentAttributeInBlock = currentTagInBlock->firstAttribute;
		currentAttributeInBlock->name = "cx";
		currentAttributeInBlock->value = xPosString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();		
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "cy";
		currentAttributeInBlock->value = yPosString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();		
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "rx";
		currentAttributeInBlock->value = widthString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();		
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "ry";
		currentAttributeInBlock->value = heightString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();			
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "fill";
		currentAttributeInBlock->value = "rgb(" + rString + "," + gString + "," + bString + ")";
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();	
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "stroke";
		currentAttributeInBlock->value = "black";
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();	
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "stroke-width";
		currentAttributeInBlock->value = boxOutlineWidthString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();	
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "fill-opacity";
		currentAttributeInBlock->value = fillOpacityString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();		
								
		(*currentTag)->nextTag = new XMLParserTag();
		(*currentTag) = (*currentTag)->nextTag;

		//svgText = "<ellipse cx=\"" + xPosString + "\" cy=\"" + yPosString + "\" rx=\"" + widthString + "\" ry=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" fill-opacity=\"" + fillOpacityString + "\" />";
	}
	else
	{
		XMLParserTag * currentTagInBlock = *currentTag;
		currentTagInBlock->name = "rect";
		XMLParserAttribute * currentAttributeInBlock = currentTagInBlock->firstAttribute;
		currentAttributeInBlock->name = "x";
		currentAttributeInBlock->value = xPosString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();		
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "y";
		currentAttributeInBlock->value = yPosString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();		
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "width";
		currentAttributeInBlock->value = widthString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();		
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "height";
		currentAttributeInBlock->value = heightString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();			
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "fill";
		currentAttributeInBlock->value = "rgb(" + rString + "," + gString + "," + bString + ")";
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();	
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "stroke";
		currentAttributeInBlock->value = "black";
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();	
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "stroke-width";
		currentAttributeInBlock->value = boxOutlineWidthString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();	
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "fill-opacity";
		currentAttributeInBlock->value = fillOpacityString;
		currentAttributeInBlock->nextAttribute = new XMLParserAttribute();	
		
		(*currentTag)->nextTag = new XMLParserTag();
		(*currentTag) = (*currentTag)->nextTag;			
	
		//svgText = "<rect x=\"" + xPosString + "\" y=\"" + yPosString + "\" width=\"" + widthString + "\" height=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" fill-opacity=\"" + fillOpacityString + "\" />";
	}
}




void writeSVGLine(XMLParserTag ** currentTag, vec * pos1, vec * pos2, int col)
{
	colour colourrgb;
 	convertLdrawColourToDatFileRGB(col, &colourrgb);

	string xPosString;
	string yPosString;
	string xPos2String;
	string yPos2String;
	string rString;
	string gString;
	string bString;
	char xPosStringcharstar[10];
	char yPosStringcharstar[10];
	char xPos2Stringcharstar[10];
	char yPos2Stringcharstar[10];
	char rStringcharstar[10];
	char gStringcharstar[10];
	char bStringcharstar[10];
	sprintf(xPosStringcharstar, "%d", (int)pos1->x);	//%d
	sprintf(yPosStringcharstar, "%d", (int)pos1->y);
	sprintf(xPos2Stringcharstar, "%d", (int)pos2->x);
	sprintf(yPos2Stringcharstar, "%d", (int)pos2->y);
	sprintf(rStringcharstar, "%d", (unsigned char)colourrgb.r);
	sprintf(gStringcharstar, "%d", (unsigned char)colourrgb.g);
	sprintf(bStringcharstar, "%d", (unsigned char)colourrgb.b);
	xPosString = xPosStringcharstar;
	yPosString = yPosStringcharstar;
	xPos2String = xPos2Stringcharstar;
	yPos2String = yPos2Stringcharstar;
	rString = rStringcharstar;
	gString = gStringcharstar;
	bString = bStringcharstar;

	XMLParserTag * currentTagInBlock = *currentTag;
	currentTagInBlock->name = "g";
	XMLParserAttribute * currentAttributeInBlock = currentTagInBlock->firstAttribute;
	currentAttributeInBlock->name = "stroke";
	currentAttributeInBlock->value = "rgb(" + rString + "," + gString + "," + bString + ")";
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();
	
	currentTagInBlock->firstLowerLevelTag = new XMLParserTag();
	currentTagInBlock = currentTagInBlock->firstLowerLevelTag;
	currentTagInBlock->nextTag = new XMLParserTag();	
	currentTagInBlock->name = "line";
	currentAttributeInBlock = currentTagInBlock->firstAttribute;
	currentAttributeInBlock->name = "x1";
	currentAttributeInBlock->value = xPosString;
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();		
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
	currentAttributeInBlock->name = "y1";
	currentAttributeInBlock->value = yPosString;
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();		
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
	currentAttributeInBlock->name = "x2";
	currentAttributeInBlock->value = xPos2String;
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();		
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
	currentAttributeInBlock->name = "y2";
	currentAttributeInBlock->value = yPos2String;
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();			
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
	currentAttributeInBlock->name = "stroke-width";
	currentAttributeInBlock->value = "1";
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();	
			
	(*currentTag)->nextTag = new XMLParserTag();
	(*currentTag) = (*currentTag)->nextTag;
	
	//string svgText = "<g stroke=\"rgb(" + rString + "," + gString + "," + bString + ")\"><line x1=\"" + xPosString + "\" y1=\"" + yPosString + "\" x2=\"" + xPos2String + "\" y2=\"" + yPos2String + "\" stroke-width=\"1\" /></g>";

}



void writeSVGText(XMLParserTag ** currentTag, string text, vec * pos, int fontSize, int col)
{
	colour colourrgb;
 	convertLdrawColourToDatFileRGB(col, &colourrgb);

	string xPosString;
	string yPosString;
	string fontSizeString;
	string rString;
	string gString;
	string bString;
	char xPosStringcharstar[10];
	char yPosStringcharstar[10];
	char fontSizeStringcharstar[10];
	char rStringcharstar[10];
	char gStringcharstar[10];
	char bStringcharstar[10];
	sprintf(fontSizeStringcharstar, "%d", fontSize);
	sprintf(xPosStringcharstar, "%d", (int)pos->x);
	sprintf(yPosStringcharstar, "%d", (int)pos->y);
	sprintf(rStringcharstar, "%d", (unsigned char)colourrgb.r);
	sprintf(gStringcharstar, "%d", (unsigned char)colourrgb.g);
	sprintf(bStringcharstar, "%d", (unsigned char)colourrgb.b);
	xPosString = xPosStringcharstar;
	yPosString = yPosStringcharstar;
	fontSizeString = fontSizeStringcharstar;
	rString = rStringcharstar;
	gString = gStringcharstar;
	bString = bStringcharstar;
	
	XMLParserTag * currentTagInBlock = *currentTag;
	currentTagInBlock->name = "g";
	XMLParserAttribute * currentAttributeInBlock = currentTagInBlock->firstAttribute;
	currentAttributeInBlock->name = "style";
	currentAttributeInBlock->value = "font-family:Arial;font-size:" + fontSizeString + "px;font-weight:400";
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();
	
	currentTagInBlock->firstLowerLevelTag = new XMLParserTag();
	currentTagInBlock = currentTagInBlock->firstLowerLevelTag;
	currentTagInBlock->nextTag = new XMLParserTag();	
	currentTagInBlock->name = "g";
	currentAttributeInBlock = currentTagInBlock->firstAttribute;
	currentAttributeInBlock->name = "style";
	currentAttributeInBlock->value = "stroke:none;fill:rgb(" + rString + "," + gString + "," + bString + ")";
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();

	currentTagInBlock->firstLowerLevelTag = new XMLParserTag();
	currentTagInBlock = currentTagInBlock->firstLowerLevelTag;
	currentTagInBlock->nextTag = new XMLParserTag();	
	currentTagInBlock->name = "text";

	currentTagInBlock->firstLowerLevelTag = new XMLParserTag();
	currentTagInBlock = currentTagInBlock->firstLowerLevelTag;
	currentTagInBlock->nextTag = new XMLParserTag();	
	currentTagInBlock->name = "tspan";
	currentTagInBlock->value = text;
	currentAttributeInBlock = currentTagInBlock->firstAttribute;
	currentAttributeInBlock->name = "x";
	currentAttributeInBlock->value = xPosString;
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();		
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
	currentAttributeInBlock->name = "y";
	currentAttributeInBlock->value = yPosString;
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();	
	
	(*currentTag)->nextTag = new XMLParserTag();
	(*currentTag) = (*currentTag)->nextTag;
	 		
	//string svgText = "<g style=\"font-family:Arial;font-size:" + fontSizeString + "px;font-weight:400\"><g style=\"stroke:none;fill:rgb(" + rString + "," + gString + "," + bString + ")\"><text><tspan x=\"" + xPosString + "\" y=\"" + yPosString + "\">" + text + "</tspan></text></g></g>";
}




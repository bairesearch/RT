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
 * File Name: LDsvg.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3d4a 8-June-2014
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

bool writeSVGfile(string xmlFileName, XMLparserTag * firstTagInXMLfile)
{
	return writeSVGfile(xmlFileName, firstTagInXMLfile, -100, 1920, -100, 1400);
}

bool writeSVGfile(string xmlFileName, XMLparserTag * firstTagInXMLfile, int viewBoxMinX, int viewBoxMaxX, int viewBoxMinY, int viewBoxMaxY)
{
	bool result = true;

	ofstream writeFileObject(xmlFileName.c_str());

	writeSVGheader(&writeFileObject, viewBoxMinX, viewBoxMaxX, viewBoxMinY, viewBoxMaxY);

	if(!addTagLayerToFileObject(firstTagInXMLfile, &writeFileObject, 0))
	{
		result = false;
	}

	writeSVGfooter(&writeFileObject);

	//Added by RBB 30 August 2009 - required for Windows SW to re-read xml files
	writeFileObject.put(CHAR_NEWLINE); //(s.cStr())[i]

	writeFileObject.close();

	return result;
}


void writeSVGheader(ofstream * writeFileObject, int viewBoxMinX, int viewBoxMaxX, int viewBoxMinY, int viewBoxMaxY)
{
	int width = viewBoxMaxX-viewBoxMinX;
	int height = viewBoxMaxY-viewBoxMinY;
	char widthString[10];
	char heightString[10];
	char viewBoxMinXstring[10];
	char viewBoxMaxXstring[10];
	char viewBoxMinYstring[10];
	char viewBoxMaxYstring[10];
	sprintf(widthString, "%d", width);
	sprintf(heightString, "%d", height);
	sprintf(viewBoxMinXstring, "%d", viewBoxMinX);
	sprintf(viewBoxMaxXstring, "%d", viewBoxMaxX);
	sprintf(viewBoxMinYstring, "%d", viewBoxMinY);
	sprintf(viewBoxMaxYstring, "%d", viewBoxMaxY);

	//string headerString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\"><svg xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape" version=\"1.1\" viewBox=\"-100 -100 1920 1400\" preserveAspectRatio=\"xMidYMid\" fill-rule=\"evenodd\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">";
	string headerString = "";
	headerString = headerString + "<?xml version=\"1.0\" encoding=\"UTF-8\"?><!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\"><svg xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" version=\"1.1\" width=\"" + widthString + "\" height=\"" + heightString + "\" viewBox=\"" + viewBoxMinXstring + " " + viewBoxMinYstring + " " + viewBoxMaxXstring + " " + viewBoxMaxYstring + "\" preserveAspectRatio=\"xMidYMid\" fill-rule=\"evenodd\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">";	//NB xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" is required to support inkscape connectors
	for(int i = 0; i<headerString.length(); i++)
	{
		writeFileObject->put(headerString[i]);
	}
}

void writeSVGfooter(ofstream * writeFileObject)
{
	string footerString = "</svg>";
	for(int i = 0; i<footerString.length(); i++)
	{
		writeFileObject->put(footerString[i]);
	}
}



void writeSVGbox(XMLparserTag ** currentTag, vec * pos, double width, double height, int col, double boxOutlineWidth, bool useEllipse)
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
		XMLparserTag * currentTagInBlock = *currentTag;
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

		(*currentTag)->nextTag = new XMLparserTag();
		(*currentTag) = (*currentTag)->nextTag;

		//svgText = "<ellipse cx=\"" + xPosString + "\" cy=\"" + yPosString + "\" rx=\"" + widthString + "\" ry=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" />";
	}
	else
	{
		XMLparserTag * currentTagInBlock = *currentTag;
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

		(*currentTag)->nextTag = new XMLparserTag();
		(*currentTag) = (*currentTag)->nextTag;

		//svgText = "<rect x=\"" + xPosString + "\" y=\"" + yPosString + "\" width=\"" + widthString + "\" height=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" />";
	}
}

void writeSVGboxTransparent(XMLparserTag ** currentTag, vec * pos, double width, double height, int col, double boxOutlineWidth, bool useEllipse, double fillOpacity)
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
		XMLparserTag * currentTagInBlock = *currentTag;
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

		(*currentTag)->nextTag = new XMLparserTag();
		(*currentTag) = (*currentTag)->nextTag;

		//svgText = "<ellipse cx=\"" + xPosString + "\" cy=\"" + yPosString + "\" rx=\"" + widthString + "\" ry=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" fill-opacity=\"" + fillOpacityString + "\" />";
	}
	else
	{
		XMLparserTag * currentTagInBlock = *currentTag;
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

		(*currentTag)->nextTag = new XMLparserTag();
		(*currentTag) = (*currentTag)->nextTag;

		//svgText = "<rect x=\"" + xPosString + "\" y=\"" + yPosString + "\" width=\"" + widthString + "\" height=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" fill-opacity=\"" + fillOpacityString + "\" />";
	}
}




void writeSVGline(XMLparserTag ** currentTag, vec * pos1, vec * pos2, int col)
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

	XMLparserTag * currentTagInBlock = *currentTag;
	currentTagInBlock->name = "g";
	XMLParserAttribute * currentAttributeInBlock = currentTagInBlock->firstAttribute;
	currentAttributeInBlock->name = "stroke";
	currentAttributeInBlock->value = "rgb(" + rString + "," + gString + "," + bString + ")";
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();

	currentTagInBlock->firstLowerLevelTag = new XMLparserTag();
	currentTagInBlock = currentTagInBlock->firstLowerLevelTag;
	currentTagInBlock->nextTag = new XMLparserTag();
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

	(*currentTag)->nextTag = new XMLparserTag();
	(*currentTag) = (*currentTag)->nextTag;

	//string svgText = "<g stroke=\"rgb(" + rString + "," + gString + "," + bString + ")\"><line x1=\"" + xPosString + "\" y1=\"" + yPosString + "\" x2=\"" + xPos2String + "\" y2=\"" + yPos2String + "\" stroke-width=\"1\" /></g>";

}



void writeSVGtext(XMLparserTag ** currentTag, string text, vec * pos, int fontSize, int col)
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

	XMLparserTag * currentTagInBlock = *currentTag;
	currentTagInBlock->name = "g";
	XMLParserAttribute * currentAttributeInBlock = currentTagInBlock->firstAttribute;
	currentAttributeInBlock->name = "style";
	currentAttributeInBlock->value = "font-family:Arial;font-size:" + fontSizeString + "px;font-weight:400";
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();

	currentTagInBlock->firstLowerLevelTag = new XMLparserTag();
	currentTagInBlock = currentTagInBlock->firstLowerLevelTag;
	currentTagInBlock->nextTag = new XMLparserTag();
	currentTagInBlock->name = "g";
	currentAttributeInBlock = currentTagInBlock->firstAttribute;
	currentAttributeInBlock->name = "style";
	currentAttributeInBlock->value = "stroke:none;fill:rgb(" + rString + "," + gString + "," + bString + ")";
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();

	currentTagInBlock->firstLowerLevelTag = new XMLparserTag();
	currentTagInBlock = currentTagInBlock->firstLowerLevelTag;
	currentTagInBlock->nextTag = new XMLparserTag();
	currentTagInBlock->name = "text";

	currentTagInBlock->firstLowerLevelTag = new XMLparserTag();
	currentTagInBlock = currentTagInBlock->firstLowerLevelTag;
	currentTagInBlock->nextTag = new XMLparserTag();
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

	(*currentTag)->nextTag = new XMLparserTag();
	(*currentTag) = (*currentTag)->nextTag;

	//string svgText = "<g style=\"font-family:Arial;font-size:" + fontSizeString + "px;font-weight:400\"><g style=\"stroke:none;fill:rgb(" + rString + "," + gString + "," + bString + ")\"><text><tspan x=\"" + xPosString + "\" y=\"" + yPosString + "\">" + text + "</tspan></text></g></g>";
}

XMLparserTag * writeSVGgroup(XMLparserTag ** currentTag, string * groupID)
{
	XMLparserTag * nextTagOnOriginalLayer = NULL;

	XMLparserTag * currentTagInBlock = *currentTag;
	currentTagInBlock->name = "g";
	XMLParserAttribute * currentAttributeInBlock = currentTagInBlock->firstAttribute;
	currentAttributeInBlock->name = "id";
	currentAttributeInBlock->value = *groupID;
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();

	currentTagInBlock->firstLowerLevelTag = new XMLparserTag();
	currentTagInBlock = currentTagInBlock->firstLowerLevelTag;

	(*currentTag)->nextTag = new XMLparserTag();
	nextTagOnOriginalLayer = (*currentTag)->nextTag;

	(*currentTag) = (*currentTag)->firstLowerLevelTag;	//set current tag to first tag in group

	return nextTagOnOriginalLayer;
}

void writeSVGconnector(XMLparserTag ** currentTag, vec * pos1, vec * pos2, int col, string * startGroupID, string * endGroupID, double width)
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
	char strokeWidthcharstar[10];
	sprintf(xPosStringcharstar, "%d", (int)pos1->x);	//%d
	sprintf(yPosStringcharstar, "%d", (int)pos1->y);
	sprintf(xPos2Stringcharstar, "%d", (int)pos2->x);
	sprintf(yPos2Stringcharstar, "%d", (int)pos2->y);
	sprintf(strokeWidthcharstar, "%0.1f", width);
	string hexString = convertColourRGBtoHexString(&colourrgb);
	xPosString = xPosStringcharstar;
	yPosString = yPosStringcharstar;
	xPos2String = xPos2Stringcharstar;
	yPos2String = yPos2Stringcharstar;

	XMLparserTag * currentTagInBlock = *currentTag;
	currentTagInBlock->name = "path";
	XMLParserAttribute * currentAttributeInBlock = currentTagInBlock->firstAttribute;
	currentAttributeInBlock->name = "style";
	string pathStyleValue = "";
	pathStyleValue = pathStyleValue + "fill:none;stroke:#" + hexString + ";stroke-width:" + strokeWidthcharstar + "px;stroke-opacity:1";
	currentAttributeInBlock->value = pathStyleValue;
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;

	currentAttributeInBlock->name = "d";
	string pathDtagValue = "";
	pathDtagValue = pathDtagValue + "M " + xPosString + "," + yPosString + " " + xPos2String + "," + yPos2String;
	currentAttributeInBlock->value = pathDtagValue;
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;

	currentAttributeInBlock->name = "id";
	string pathIdValue = "";
	pathIdValue = pathIdValue + "path" + *startGroupID + *endGroupID;	//pathIdValue = pathIdValue + "path-" + *startGroupID + "-" + *endGroupID;
	currentAttributeInBlock->value = pathIdValue;
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;

	currentAttributeInBlock->name = "inkscape:connector-type";
	currentAttributeInBlock->value = "polyline";
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;

	currentAttributeInBlock->name = "inkscape:connection-start";
	string pathConnectionStartValue = "";
	pathConnectionStartValue = pathConnectionStartValue + "#" + *startGroupID;
	currentAttributeInBlock->value = pathConnectionStartValue;
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;

	currentAttributeInBlock->name = "inkscape:connection-end";
	string pathConnectionEndValue = "";
	pathConnectionEndValue = pathConnectionEndValue + "#" + *endGroupID;
	currentAttributeInBlock->value = pathConnectionEndValue;
	currentAttributeInBlock->nextAttribute = new XMLParserAttribute();
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;

	(*currentTag)->nextTag = new XMLparserTag();
	(*currentTag) = (*currentTag)->nextTag;
}

string convertColourRGBtoHexString(colour * colourRGB)
{
	string hexString = "";

	char rHex[255];
	sprintf(rHex, "%.2X", colourRGB->r);
	hexString = hexString + rHex;

	char gHex[255];
	sprintf(gHex, "%.2X", colourRGB->g);
	hexString = hexString + gHex;

	char bHex[255];
	sprintf(bHex, "%.2X", colourRGB->b);
	hexString = hexString + bHex;

	//cout << "hexString = " << hexString << endl;

	return hexString;

}


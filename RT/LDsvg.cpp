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
 * Project Version: 3a13a 24-Sept-2012
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

void writeSVGHeader(ofstream * writeFileObject)
{
	string headerString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\"><svg version=\"1.1\" viewBox=\"-100 -100 1920 1400\" preserveAspectRatio=\"xMidYMid\" fill-rule=\"evenodd\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">";
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



void writeSVGBox(ofstream * writeFileObject, vec * pos, double width, double height, int col, double boxOutlineWidth, bool useEllipse)
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
		svgText = "<ellipse cx=\"" + xPosString + "\" cy=\"" + yPosString + "\" rx=\"" + widthString + "\" ry=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" />";
	}
	else
	{
		svgText = "<rect x=\"" + xPosString + "\" y=\"" + yPosString + "\" width=\"" + widthString + "\" height=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" />";
	}

	for(int i = 0; i<svgText.length(); i++)
	{
		writeFileObject->put(svgText[i]);
	}
}

void writeSVGBoxTransparent(ofstream * writeFileObject, vec * pos, double width, double height, int col, double boxOutlineWidth, bool useEllipse, double fillOpacity)
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
		svgText = "<ellipse cx=\"" + xPosString + "\" cy=\"" + yPosString + "\" rx=\"" + widthString + "\" ry=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" fill-opacity=\"" + fillOpacityString + "\" />";
	}
	else
	{
		svgText = "<rect x=\"" + xPosString + "\" y=\"" + yPosString + "\" width=\"" + widthString + "\" height=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" fill-opacity=\"" + fillOpacityString + "\" />";
	}

	for(int i = 0; i<svgText.length(); i++)
	{
		writeFileObject->put(svgText[i]);
	}
}




void writeSVGLine(ofstream * writeFileObject, vec * pos1, vec * pos2, int col)
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

	string svgText = "<g stroke=\"rgb(" + rString + "," + gString + "," + bString + ")\"><line x1=\"" + xPosString + "\" y1=\"" + yPosString + "\" x2=\"" + xPos2String + "\" y2=\"" + yPos2String + "\" stroke-width=\"1\" /></g>";

	for(int i = 0; i<svgText.length(); i++)
	{
		writeFileObject->put(svgText[i]);
	}

}



void writeSVGText(ofstream * writeFileObject, string text, vec * pos, int fontSize, int col)
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

	string svgText = "<g style=\"font-family:Arial;font-size:" + fontSizeString + "px;font-weight:400\"><g style=\"stroke:none;fill:rgb(" + rString + "," + gString + "," + bString + ")\"><text><tspan x=\"" + xPosString + "\" y=\"" + yPosString + "\">" + text + "</tspan></text></g></g>";

	for(int i = 0; i<svgText.length(); i++)
	{
		writeFileObject->put(svgText[i]);
	}

}




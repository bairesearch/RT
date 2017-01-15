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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3h9a 09-December-2015
 *
 *******************************************************************************/


#include "LDsvg.h"

bool writeSVGfile(string xmlFileName, XMLparserTag* firstTagInXMLfile)
{
	return writeSVGfile(xmlFileName, firstTagInXMLfile, -100, 1920, -100, 1400);
}

bool writeSVGfile(string xmlFileName, XMLparserTag* firstTagInXMLfile, int viewBoxMinX, int viewBoxMaxX, int viewBoxMinY, int viewBoxMaxY)
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


void writeSVGheader(ofstream* writeFileObject, int viewBoxMinX, int viewBoxMaxX, int viewBoxMinY, int viewBoxMaxY)
{
	int width = viewBoxMaxX-viewBoxMinX;
	int height = viewBoxMaxY-viewBoxMinY;

	string widthString = convertIntToString(width);
	string heightString = convertIntToString(height);
	string viewBoxMinXstring = convertIntToString(viewBoxMinX);
	string viewBoxMaxXstring = convertIntToString(viewBoxMaxX);
	string viewBoxMinYstring = convertIntToString(viewBoxMinY);
	string viewBoxMaxYstring = convertIntToString(viewBoxMaxY);

	//string headerString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\"><svg xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape" version=\"1.1\" viewBox=\"-100 -100 1920 1400\" preserveAspectRatio=\"xMidYMid\" fill-rule=\"evenodd\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">";
	string headerString = "";
	headerString = headerString + "<?xml version=\"1.0\" encoding=\"UTF-8\"?><!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\"><svg xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" version=\"1.1\" width=\"" + widthString + "\" height=\"" + heightString + "\" viewBox=\"" + viewBoxMinXstring + " " + viewBoxMinYstring + " " + viewBoxMaxXstring + " " + viewBoxMaxYstring + "\" preserveAspectRatio=\"xMidYMid\" fill-rule=\"evenodd\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">";	//NB xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" is required to support inkscape connectors
	for(int i = 0; i<headerString.length(); i++)
	{
		writeFileObject->put(headerString[i]);
	}
}

void writeSVGfooter(ofstream* writeFileObject)
{
	string footerString = "</svg>";
	for(int i = 0; i<footerString.length(); i++)
	{
		writeFileObject->put(footerString[i]);
	}
}



void writeSVGbox(XMLparserTag** currentTag, vec* pos, double width, double height, int col, double boxOutlineWidth, bool useEllipse)
{
	colour colourrgb;
 	convertLdrawColourToDatFileRGB(col, &colourrgb);

	string boxOutlineWidthString = convertDoubleToString(boxOutlineWidth, "%0.3f");
	string xPosString = convertIntToString((int)(pos->x - (width/2)));	//%d
	string yPosString = convertIntToString((int)(pos->y - (height/2)));
	string rString = convertIntToString((unsigned char)colourrgb.r);
	string gString = convertIntToString((unsigned char)colourrgb.g);
	string bString = convertIntToString((unsigned char)colourrgb.b);
	string widthString = convertIntToString((int)width);
	string heightString = convertIntToString((int)height);

	string svgText = "";

	if(useEllipse)
	{
		XMLparserTag* currentTagInBlock = *currentTag;
		currentTagInBlock->name = "ellipse";
		XMLparserAttribute* currentAttributeInBlock = currentTagInBlock->firstAttribute;
		currentAttributeInBlock->name = "cx";
		currentAttributeInBlock->value = xPosString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "cy";
		currentAttributeInBlock->value = yPosString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "rx";
		currentAttributeInBlock->value = widthString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "ry";
		currentAttributeInBlock->value = heightString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "fill";
		currentAttributeInBlock->value = "rgb(" + rString + "," + gString + "," + bString + ")";
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "stroke";
		currentAttributeInBlock->value = "black";
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "stroke-width";
		currentAttributeInBlock->value = boxOutlineWidthString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();

		(*currentTag)->nextTag = new XMLparserTag();
		(*currentTag) = (*currentTag)->nextTag;

		//svgText = "<ellipse cx=\"" + xPosString + "\" cy=\"" + yPosString + "\" rx=\"" + widthString + "\" ry=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" />";
	}
	else
	{
		XMLparserTag* currentTagInBlock = *currentTag;
		currentTagInBlock->name = "rect";
		XMLparserAttribute* currentAttributeInBlock = currentTagInBlock->firstAttribute;
		currentAttributeInBlock->name = "x";
		currentAttributeInBlock->value = xPosString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "y";
		currentAttributeInBlock->value = yPosString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "width";
		currentAttributeInBlock->value = widthString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "height";
		currentAttributeInBlock->value = heightString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "fill";
		currentAttributeInBlock->value = "rgb(" + rString + "," + gString + "," + bString + ")";
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "stroke";
		currentAttributeInBlock->value = "black";
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "stroke-width";
		currentAttributeInBlock->value = boxOutlineWidthString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();

		(*currentTag)->nextTag = new XMLparserTag();
		(*currentTag) = (*currentTag)->nextTag;

		//svgText = "<rect x=\"" + xPosString + "\" y=\"" + yPosString + "\" width=\"" + widthString + "\" height=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" />";
	}
}

void writeSVGboxTransparent(XMLparserTag** currentTag, vec* pos, double width, double height, int col, double boxOutlineWidth, bool useEllipse, double fillOpacity)
{
	colour colourrgb;
 	convertLdrawColourToDatFileRGB(col, &colourrgb);

	string boxOutlineWidthString = convertDoubleToString(boxOutlineWidth, "%0.3f");
	string xPosString = convertIntToString((int)(pos->x - (width/2)));	//%d
	string yPosString = convertIntToString((int)(pos->y - (height/2)));
	string rString = convertIntToString((unsigned char)colourrgb.r);
	string gString = convertIntToString((unsigned char)colourrgb.g);
	string bString = convertIntToString((unsigned char)colourrgb.b);
	string widthString = convertIntToString((int)width);
	string heightString = convertIntToString((int)height);

	string svgText = "";

	string fillOpacityString = convertDoubleToString(fillOpacity, "%0.3f");

	if(useEllipse)
	{
		XMLparserTag* currentTagInBlock = *currentTag;
		currentTagInBlock->name = "ellipse";
		XMLparserAttribute* currentAttributeInBlock = currentTagInBlock->firstAttribute;
		currentAttributeInBlock->name = "cx";
		currentAttributeInBlock->value = xPosString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "cy";
		currentAttributeInBlock->value = yPosString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "rx";
		currentAttributeInBlock->value = widthString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "ry";
		currentAttributeInBlock->value = heightString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "fill";
		currentAttributeInBlock->value = "rgb(" + rString + "," + gString + "," + bString + ")";
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "stroke";
		currentAttributeInBlock->value = "black";
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "stroke-width";
		currentAttributeInBlock->value = boxOutlineWidthString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "fill-opacity";
		currentAttributeInBlock->value = fillOpacityString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();

		(*currentTag)->nextTag = new XMLparserTag();
		(*currentTag) = (*currentTag)->nextTag;

		//svgText = "<ellipse cx=\"" + xPosString + "\" cy=\"" + yPosString + "\" rx=\"" + widthString + "\" ry=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" fill-opacity=\"" + fillOpacityString + "\" />";
	}
	else
	{
		XMLparserTag* currentTagInBlock = *currentTag;
		currentTagInBlock->name = "rect";
		XMLparserAttribute* currentAttributeInBlock = currentTagInBlock->firstAttribute;
		currentAttributeInBlock->name = "x";
		currentAttributeInBlock->value = xPosString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "y";
		currentAttributeInBlock->value = yPosString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "width";
		currentAttributeInBlock->value = widthString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "height";
		currentAttributeInBlock->value = heightString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "fill";
		currentAttributeInBlock->value = "rgb(" + rString + "," + gString + "," + bString + ")";
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "stroke";
		currentAttributeInBlock->value = "black";
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "stroke-width";
		currentAttributeInBlock->value = boxOutlineWidthString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
		currentAttributeInBlock->name = "fill-opacity";
		currentAttributeInBlock->value = fillOpacityString;
		currentAttributeInBlock->nextAttribute = new XMLparserAttribute();

		(*currentTag)->nextTag = new XMLparserTag();
		(*currentTag) = (*currentTag)->nextTag;

		//svgText = "<rect x=\"" + xPosString + "\" y=\"" + yPosString + "\" width=\"" + widthString + "\" height=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" fill-opacity=\"" + fillOpacityString + "\" />";
	}
}




void writeSVGline(XMLparserTag** currentTag, vec* pos1, vec* pos2, int col)
{
	colour colourrgb;
 	convertLdrawColourToDatFileRGB(col, &colourrgb);

	string xPosString = convertIntToString((int)pos1->x);	//%d
	string yPosString = convertIntToString((int)pos1->y);
	string xPos2String = convertIntToString((int)pos2->x);
	string yPos2String = convertIntToString((int)pos2->y);
	string rString = convertIntToString((unsigned char)colourrgb.r);
	string gString = convertIntToString((unsigned char)colourrgb.g);
	string bString = convertIntToString((unsigned char)colourrgb.b);

	XMLparserTag* currentTagInBlock = *currentTag;
	currentTagInBlock->name = "g";
	XMLparserAttribute* currentAttributeInBlock = currentTagInBlock->firstAttribute;
	currentAttributeInBlock->name = "stroke";
	currentAttributeInBlock->value = "rgb(" + rString + "," + gString + "," + bString + ")";
	currentAttributeInBlock->nextAttribute = new XMLparserAttribute();

	currentTagInBlock->firstLowerLevelTag = new XMLparserTag();
	currentTagInBlock = currentTagInBlock->firstLowerLevelTag;
	currentTagInBlock->nextTag = new XMLparserTag();
	currentTagInBlock->name = "line";
	currentAttributeInBlock = currentTagInBlock->firstAttribute;
	currentAttributeInBlock->name = "x1";
	currentAttributeInBlock->value = xPosString;
	currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
	currentAttributeInBlock->name = "y1";
	currentAttributeInBlock->value = yPosString;
	currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
	currentAttributeInBlock->name = "x2";
	currentAttributeInBlock->value = xPos2String;
	currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
	currentAttributeInBlock->name = "y2";
	currentAttributeInBlock->value = yPos2String;
	currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
	currentAttributeInBlock->name = "stroke-width";
	currentAttributeInBlock->value = "1";
	currentAttributeInBlock->nextAttribute = new XMLparserAttribute();

	(*currentTag)->nextTag = new XMLparserTag();
	(*currentTag) = (*currentTag)->nextTag;

	//string svgText = "<g stroke=\"rgb(" + rString + "," + gString + "," + bString + ")\"><line x1=\"" + xPosString + "\" y1=\"" + yPosString + "\" x2=\"" + xPos2String + "\" y2=\"" + yPos2String + "\" stroke-width=\"1\" /></g>";

}



void writeSVGtext(XMLparserTag** currentTag, string text, vec* pos, int fontSize, int col)
{
	colour colourrgb;
 	convertLdrawColourToDatFileRGB(col, &colourrgb);

	string fontSizeString = convertIntToString(fontSize);
	string xPosString = convertIntToString((int)pos->x);
	string yPosString = convertIntToString((int)pos->y);
	string rString = convertIntToString((unsigned char)colourrgb.r);
	string gString = convertIntToString((unsigned char)colourrgb.g);
	string bString = convertIntToString((unsigned char)colourrgb.b);

	XMLparserTag* currentTagInBlock = *currentTag;
	currentTagInBlock->name = "g";
	XMLparserAttribute* currentAttributeInBlock = currentTagInBlock->firstAttribute;
	currentAttributeInBlock->name = "style";
	currentAttributeInBlock->value = "font-family:Arial;font-size:" + fontSizeString + "px;font-weight:400";
	currentAttributeInBlock->nextAttribute = new XMLparserAttribute();

	currentTagInBlock->firstLowerLevelTag = new XMLparserTag();
	currentTagInBlock = currentTagInBlock->firstLowerLevelTag;
	currentTagInBlock->nextTag = new XMLparserTag();
	currentTagInBlock->name = "g";
	currentAttributeInBlock = currentTagInBlock->firstAttribute;
	currentAttributeInBlock->name = "style";
	currentAttributeInBlock->value = "stroke:none;fill:rgb(" + rString + "," + gString + "," + bString + ")";
	currentAttributeInBlock->nextAttribute = new XMLparserAttribute();

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
	currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
	currentAttributeInBlock->name = "y";
	currentAttributeInBlock->value = yPosString;
	currentAttributeInBlock->nextAttribute = new XMLparserAttribute();

	(*currentTag)->nextTag = new XMLparserTag();
	(*currentTag) = (*currentTag)->nextTag;

	//string svgText = "<g style=\"font-family:Arial;font-size:" + fontSizeString + "px;font-weight:400\"><g style=\"stroke:none;fill:rgb(" + rString + "," + gString + "," + bString + ")\"><text><tspan x=\"" + xPosString + "\" y=\"" + yPosString + "\">" + text + "</tspan></text></g></g>";
}

XMLparserTag* writeSVGgroup(XMLparserTag** currentTag, string* groupID)
{
	XMLparserTag* nextTagOnOriginalLayer = NULL;

	XMLparserTag* currentTagInBlock = *currentTag;
	currentTagInBlock->name = "g";
	XMLparserAttribute* currentAttributeInBlock = currentTagInBlock->firstAttribute;
	currentAttributeInBlock->name = "id";
	currentAttributeInBlock->value = *groupID;
	currentAttributeInBlock->nextAttribute = new XMLparserAttribute();

	currentTagInBlock->firstLowerLevelTag = new XMLparserTag();
	currentTagInBlock = currentTagInBlock->firstLowerLevelTag;

	(*currentTag)->nextTag = new XMLparserTag();
	nextTagOnOriginalLayer = (*currentTag)->nextTag;

	(*currentTag) = (*currentTag)->firstLowerLevelTag;	//set current tag to first tag in group

	return nextTagOnOriginalLayer;
}

void writeSVGconnector(XMLparserTag** currentTag, vec* pos1, vec* pos2, int col, string* startGroupID, string* endGroupID, double width)
{
	colour colourrgb;
 	convertLdrawColourToDatFileRGB(col, &colourrgb);

	string xPosString = convertIntToString((int)pos1->x);	//%d
	string yPosString = convertIntToString((int)pos1->y);
	string xPos2String = convertIntToString((int)pos2->x);
	string yPos2String = convertIntToString((int)pos2->y);
	string strokeWidth = convertDoubleToString(width, "%0.1f");
	string hexString = convertColourRGBtoHexString(&colourrgb);

	XMLparserTag* currentTagInBlock = *currentTag;
	currentTagInBlock->name = "path";
	XMLparserAttribute* currentAttributeInBlock = currentTagInBlock->firstAttribute;
	currentAttributeInBlock->name = "style";
	string pathStyleValue = "";
	pathStyleValue = pathStyleValue + "fill:none;stroke:#" + hexString + ";stroke-width:" + strokeWidth + "px;stroke-opacity:1";
	currentAttributeInBlock->value = pathStyleValue;
	currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;

	currentAttributeInBlock->name = "d";
	string pathDtagValue = "";
	pathDtagValue = pathDtagValue + "M " + xPosString + "," + yPosString + " " + xPos2String + "," + yPos2String;
	currentAttributeInBlock->value = pathDtagValue;
	currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;

	currentAttributeInBlock->name = "id";
	string pathIdValue = "";
	pathIdValue = pathIdValue + "path" +* startGroupID +* endGroupID;	//pathIdValue = pathIdValue + "path-" +* startGroupID + "-" +* endGroupID;
	currentAttributeInBlock->value = pathIdValue;
	currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;

	currentAttributeInBlock->name = "inkscape:connector-type";
	currentAttributeInBlock->value = "polyline";
	currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;

	currentAttributeInBlock->name = "inkscape:connection-start";
	string pathConnectionStartValue = "";
	pathConnectionStartValue = pathConnectionStartValue + "#" +* startGroupID;
	currentAttributeInBlock->value = pathConnectionStartValue;
	currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;

	currentAttributeInBlock->name = "inkscape:connection-end";
	string pathConnectionEndValue = "";
	pathConnectionEndValue = pathConnectionEndValue + "#" +* endGroupID;
	currentAttributeInBlock->value = pathConnectionEndValue;
	currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
	currentAttributeInBlock = currentAttributeInBlock->nextAttribute;

	(*currentTag)->nextTag = new XMLparserTag();
	(*currentTag) = (*currentTag)->nextTag;
}

string convertColourRGBtoHexString(colour* colourRGB)
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


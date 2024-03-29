 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: LDsvg.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3q1a 05-June-2022
 * /
 *******************************************************************************/


#include "LDsvg.hpp"

bool LDsvgClass::writeSVGfile(const string xmlFileName, const XMLparserTag* firstTagInXMLfile)
{
	return writeSVGfile(xmlFileName, firstTagInXMLfile, -100, 1920, -100, 1400);
}

bool LDsvgClass::writeSVGfile(const string xmlFileName, const XMLparserTag* firstTagInXMLfile, const int viewBoxMinX, const int viewBoxMaxX, const int viewBoxMinY, const int viewBoxMaxY)
{
	bool result = true;

	string writeFileString = "";
	if(!writeSVGfile(&writeFileString, firstTagInXMLfile, viewBoxMinX, viewBoxMaxX, viewBoxMinY, viewBoxMaxY))
	{
		result = false;
	}

	SHAREDvars.writeStringToFile(xmlFileName, &writeFileString);

	return result;
}

bool LDsvgClass::writeSVGfile(string* writeFileString, const XMLparserTag* firstTagInXMLfile, const int viewBoxMinX, const int viewBoxMaxX, const int viewBoxMinY, const int viewBoxMaxY)
{
	bool result = true;

	writeSVGheader(writeFileString, viewBoxMinX, viewBoxMaxX, viewBoxMinY, viewBoxMaxY);

	if(!XMLparserClass.addTagLayerToFileObject(firstTagInXMLfile, writeFileString, 0))
	{
		result = false;
	}

	writeSVGfooter(writeFileString);

	//Added by RBB 30 August 2009 - required for Windows SW to re-read xml files
	*writeFileString = *writeFileString + CHAR_NEWLINE;

	return result;
}



void LDsvgClass::writeSVGheader(string* writeFileString, const int viewBoxMinX, const int viewBoxMaxX, const int viewBoxMinY, const int viewBoxMaxY)
{
	int width = viewBoxMaxX-viewBoxMinX;
	int height = viewBoxMaxY-viewBoxMinY;

	string widthString = SHAREDvars.convertIntToString(width);
	string heightString = SHAREDvars.convertIntToString(height);
	string viewBoxMinXstring = SHAREDvars.convertIntToString(viewBoxMinX);
	string viewBoxMaxXstring = SHAREDvars.convertIntToString(viewBoxMaxX);
	string viewBoxMinYstring = SHAREDvars.convertIntToString(viewBoxMinY);
	string viewBoxMaxYstring = SHAREDvars.convertIntToString(viewBoxMaxY);

	//string headerString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\"><svg xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape" version=\"1.1\" viewBox=\"-100 -100 1920 1400\" preserveAspectRatio=\"xMidYMid\" fill-rule=\"evenodd\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">";
	string headerString = "";
	headerString = headerString + "<?xml version=\"1.0\" encoding=\"UTF-8\"?><!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\"><svg xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" version=\"1.1\" width=\"" + widthString + "\" height=\"" + heightString + "\" viewBox=\"" + viewBoxMinXstring + " " + viewBoxMinYstring + " " + viewBoxMaxXstring + " " + viewBoxMaxYstring + "\" preserveAspectRatio=\"xMidYMid\" fill-rule=\"evenodd\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">";	//NB xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" is required to support inkscape connectors
	for(int i = 0; i<headerString.length(); i++)
	{
		*writeFileString = *writeFileString + headerString[i];
	}
}

void LDsvgClass::writeSVGfooter(string* writeFileString)
{
	string footerString = "</svg>";
	for(int i = 0; i<footerString.length(); i++)
	{
		*writeFileString = *writeFileString + footerString[i];
	}
}



void LDsvgClass::writeSVGboxTransparent(XMLparserTag** currentTag, const vec* pos, const double width, const double height, const int col, const double boxOutlineWidth, const bool useEllipse, const double fillOpacity)
{
	bool transparent = true;
	writeSVGbox2(currentTag, pos, width, height, col, boxOutlineWidth, useEllipse, transparent, fillOpacity);
}
void LDsvgClass::writeSVGbox(XMLparserTag** currentTag, const vec* pos, const double width, const double height, const int col, const double boxOutlineWidth, const bool useEllipse)
{
	bool transparent = false;
	double fillOpacityNOTUSED;
	writeSVGbox2(currentTag, pos, width, height, col, boxOutlineWidth, useEllipse, transparent, fillOpacityNOTUSED);
}
void LDsvgClass::writeSVGbox2(XMLparserTag** currentTag, const vec* pos, const double width, const double height, const int col, const double boxOutlineWidth, const bool useEllipse, bool transparent, const double fillOpacity)
{
	colour colourrgb;
 	LDreferenceClass.convertLdrawColourToDatFileRGB(col, &colourrgb);
	writeSVGbox3(currentTag, pos, width, height, colourrgb, boxOutlineWidth, useEllipse, transparent, fillOpacity);
}
void LDsvgClass::writeSVGbox3(XMLparserTag** currentTag, const vec* pos, const double width, const double height, const colour colourrgb, const double boxOutlineWidth, const bool useEllipse, bool transparent, const double fillOpacity)
{
	string boxOutlineWidthString = SHAREDvars.convertDoubleToString(boxOutlineWidth, "%0.3f");
	string xPosString = SHAREDvars.convertIntToString((int)(pos->x - (width/2)));	//%d
	string yPosString = SHAREDvars.convertIntToString((int)(pos->y - (height/2)));
	string rString = SHAREDvars.convertIntToString((uchar)colourrgb.r);
	string gString = SHAREDvars.convertIntToString((uchar)colourrgb.g);
	string bString = SHAREDvars.convertIntToString((uchar)colourrgb.b);
	string widthString = SHAREDvars.convertIntToString((int)width);
	string heightString = SHAREDvars.convertIntToString((int)height);

	string svgText = "";

	string fillOpacityString;
	if(transparent)
	{
		fillOpacityString = SHAREDvars.convertDoubleToString(fillOpacity, "%0.3f");
	}

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
		if(transparent)
		{
			currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
			currentAttributeInBlock->name = "fill-opacity";
			currentAttributeInBlock->value = fillOpacityString;
			currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		}

		(*currentTag)->nextTag = new XMLparserTag();
		(*currentTag) = (*currentTag)->nextTag;

		/*
		if(transparent)
		{
			//svgText = "<ellipse cx=\"" + xPosString + "\" cy=\"" + yPosString + "\" rx=\"" + widthString + "\" ry=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" fill-opacity=\"" + fillOpacityString + "\" />";
		}
		else
		{
			//svgText = "<ellipse cx=\"" + xPosString + "\" cy=\"" + yPosString + "\" rx=\"" + widthString + "\" ry=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" />";
		}
		*/
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
		if(transparent)
		{		
			currentAttributeInBlock = currentAttributeInBlock->nextAttribute;
			currentAttributeInBlock->name = "fill-opacity";
			currentAttributeInBlock->value = fillOpacityString;
			currentAttributeInBlock->nextAttribute = new XMLparserAttribute();
		}
		
		(*currentTag)->nextTag = new XMLparserTag();
		(*currentTag) = (*currentTag)->nextTag;

		/*
		if(transparent)
		{
			//svgText = "<rect x=\"" + xPosString + "\" y=\"" + yPosString + "\" width=\"" + widthString + "\" height=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" fill-opacity=\"" + fillOpacityString + "\" />";
		}
		else
		{
			//svgText = "<rect x=\"" + xPosString + "\" y=\"" + yPosString + "\" width=\"" + widthString + "\" height=\"" + heightString + "\" fill=\"rgb(" + rString + "," + gString + "," + bString + ")\" stroke=\"black\" stroke-width=\"" + boxOutlineWidthString + "\" />";		
		}
		*/
	}
}



void LDsvgClass::writeSVGline(XMLparserTag** currentTag, const vec* pos1, const vec* pos2, const int col)
{
	colour colourrgb;
 	LDreferenceClass.convertLdrawColourToDatFileRGB(col, &colourrgb);	
	writeSVGline(currentTag, pos1, pos2, colourrgb);
}

void LDsvgClass::writeSVGline(XMLparserTag** currentTag, const vec* pos1, const vec* pos2, const colour colourrgb)
{
	string xPosString = SHAREDvars.convertIntToString((int)pos1->x);	//%d
	string yPosString = SHAREDvars.convertIntToString((int)pos1->y);
	string xPos2String = SHAREDvars.convertIntToString((int)pos2->x);
	string yPos2String = SHAREDvars.convertIntToString((int)pos2->y);
	string rString = SHAREDvars.convertIntToString((uchar)colourrgb.r);
	string gString = SHAREDvars.convertIntToString((uchar)colourrgb.g);
	string bString = SHAREDvars.convertIntToString((uchar)colourrgb.b);

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


void LDsvgClass::writeSVGtext(XMLparserTag** currentTag, const string text, const vec* pos, const int fontSize, const int col)
{
	writeSVGtext(currentTag, text, pos, fontSize, col, false);
}

void LDsvgClass::writeSVGtext(XMLparserTag** currentTag, const string text, const vec* pos, const int fontSize, const int col, bool svgTinySpec)
{
	colour colourrgb;
 	LDreferenceClass.convertLdrawColourToDatFileRGB(col, &colourrgb);

	string fontSizeString = SHAREDvars.convertIntToString(fontSize);
	string xPosString = SHAREDvars.convertIntToString((int)pos->x);
	string yPosString = SHAREDvars.convertIntToString((int)pos->y);
	string rString = SHAREDvars.convertIntToString((uchar)colourrgb.r);
	string gString = SHAREDvars.convertIntToString((uchar)colourrgb.g);
	string bString = SHAREDvars.convertIntToString((uchar)colourrgb.b);

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

	if(!svgTinySpec)
	{
		currentTagInBlock->firstLowerLevelTag = new XMLparserTag();
		currentTagInBlock = currentTagInBlock->firstLowerLevelTag;
		currentTagInBlock->nextTag = new XMLparserTag();
		currentTagInBlock->name = "tspan";
	}
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

XMLparserTag* LDsvgClass::writeSVGgroup(XMLparserTag** currentTag, const string* groupID)
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

void LDsvgClass::writeSVGconnector(XMLparserTag** currentTag, const vec* pos1, const vec* pos2, const int col, const string* startGroupID, const string* endGroupID, const double width)
{
	colour colourrgb;
 	LDreferenceClass.convertLdrawColourToDatFileRGB(col, &colourrgb);

	string xPosString = SHAREDvars.convertIntToString((int)pos1->x);	//%d
	string yPosString = SHAREDvars.convertIntToString((int)pos1->y);
	string xPos2String = SHAREDvars.convertIntToString((int)pos2->x);
	string yPos2String = SHAREDvars.convertIntToString((int)pos2->y);
	string strokeWidth = SHAREDvars.convertDoubleToString(width, "%0.1f");
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

string LDsvgClass::convertColourRGBtoHexString(const colour* colourRGB)
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

	return hexString;

}


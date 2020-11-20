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
 * File Name: LDsvg.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2020 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3o4a 17-November-2020
 * /
 *******************************************************************************/


#ifndef HEADER_LD_SVG
#define HEADER_LD_SVG

#include "SHAREDglobalDefs.hpp"
#include "SHAREDvars.hpp"
#include "LDreferenceClass.hpp"
#include "XMLparserClass.hpp"

class LDsvgClass
{
	private: XMLparserClassClass XMLparserClass;
	private: SHAREDvarsClass SHAREDvars;
	private: LDreferenceClassClass LDreferenceClass;
	public: bool writeSVGfile(const string xmlFileName, const XMLparserTag* firstTagInXMLfile);
		public: bool writeSVGfile(const string xmlFileName, const XMLparserTag* firstTagInXMLfile, const int viewBoxMinX, const int viewBoxMaxX, const int viewBoxMinY, const int viewBoxMaxY);
			public: bool writeSVGfile(string* writeFileString, const XMLparserTag* firstTagInXMLfile, const int viewBoxMinX, const int viewBoxMaxX, const int viewBoxMinY, const int viewBoxMaxY);
				private: void writeSVGheader(string* writeFileString, const int viewBoxMinX, const int viewBoxMaxX, const int viewBoxMinY, const int viewBoxMaxY);
				private: void writeSVGfooter(string* writeFileString);

	public: void writeSVGboxTransparent(XMLparserTag** currentTag, const vec* pos, const double width, const double height, const int col, const double boxOutlineWidth, const bool useEllipse, const double fillOpacity);
	public: void writeSVGbox(XMLparserTag** currentTag, const vec* pos, const double width, const double height, const int col, const double boxOutlineWidth, const bool useEllipse);
		public: void writeSVGbox2(XMLparserTag** currentTag, const vec* pos, const double width, const double height, const int col, const double boxOutlineWidth, const bool useEllipse, bool transparent, const double fillOpacity);
			public: void writeSVGbox3(XMLparserTag** currentTag, const vec* pos, const double width, const double height, const colour colourrgb, const double boxOutlineWidth, const bool useEllipse, bool transparent, const double fillOpacity);
	public: void writeSVGline(XMLparserTag** currentTag, const vec* pos1, const vec* pos2, const int col);
		public: void writeSVGline(XMLparserTag** currentTag, const vec* pos1, const vec* pos2, const colour colourrgb);
	public: void writeSVGtext(XMLparserTag** currentTag, const string text, const vec* pos, const int fontSize, const int col);	
		public: void writeSVGtext(XMLparserTag** currentTag, const string text, const vec* pos, const int fontSize, const int col, bool svgTinySpec);
	

	public: XMLparserTag* writeSVGgroup(XMLparserTag** currentTag, const string* groupID);
	public: void writeSVGconnector(XMLparserTag** currentTag, const vec* pos1, const vec* pos2, const int col, const string* startGroupID, const string* endGroupID, const double width);
	public: string convertColourRGBtoHexString(const colour* colourRGB);
};

#endif


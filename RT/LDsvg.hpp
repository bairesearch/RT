 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: LDsvg.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3q1a 05-June-2022
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


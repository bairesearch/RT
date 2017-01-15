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
 * File Name: LDsvg.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3j1b 14-January-2017
 *
 *******************************************************************************/


#ifndef HEADER_LD_SVG
#define HEADER_LD_SVG

#include "SHAREDglobalDefs.h"
#include "SHAREDvars.h"
#include "LDreferenceClass.h"
#include "XMLparserClass.h"

class LDsvgClass
{
	private: XMLparserClassClass XMLparserClass;
	private: SHAREDvarsClass SHAREDvars;
	private: LDreferenceClassClass LDreferenceClass;
	public: bool writeSVGfile(const string xmlFileName, const XMLparserTag* firstTagInXMLfile);
	public: bool writeSVGfile(const string xmlFileName, const XMLparserTag* firstTagInXMLfile, const int viewBoxMinX, const int viewBoxMaxX, const int viewBoxMinY, const int viewBoxMaxY);
		private: void writeSVGheader(ofstream* writeFileObject, const int viewBoxMinX, const int viewBoxMaxX, const int viewBoxMinY, const int viewBoxMaxY);
		private: void writeSVGfooter(ofstream* writeFileObject);
	public: void writeSVGline(XMLparserTag** currentTag, const vec* pos1, const vec* pos2, const int col);
	public: void writeSVGbox(XMLparserTag** currentTag, const vec* pos, const double width, const double height, const int col, const double boxOutlineWidth, const bool useEllipse);
	public: void writeSVGtext(XMLparserTag** currentTag, const string text, const vec* pos, const int fontSize, const int col);
	public: void writeSVGboxTransparent(XMLparserTag** currentTag, const vec* pos, const double width, const double height, const int col, const double boxOutlineWidth, const bool useEllipse, const double fillOpacity);
	public: XMLparserTag* writeSVGgroup(XMLparserTag** currentTag, const string* groupID);
	public: void writeSVGconnector(XMLparserTag** currentTag, const vec* pos1, const vec* pos2, const int col, const string* startGroupID, const string* endGroupID, const double width);
	public: string convertColourRGBtoHexString(const colour* colourRGB);
};

#endif


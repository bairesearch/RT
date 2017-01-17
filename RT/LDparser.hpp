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
 * File Name: LDparser.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3j2a 17-January-2017
 *
 *******************************************************************************/


#ifndef HEADER_LD_PARSER
#define HEADER_LD_PARSER

#include "LDreferenceClass.hpp"
#include "SHAREDvector.hpp"

#ifdef LINUX
	#define DEFAULT_PARTS_DIRECTORY_FULL_PATH "/usr/share/local/LDRAW/PARTS/"
	#define DEFAULT_PRIMITIVES_DIRECTORY_FULL_PATH "/usr/share/local/LDRAW/P/"
#else
	#define DEFAULT_PARTS_DIRECTORY_FULL_PATH "C:/Program Files/LDraw/PARTS/"
	#define DEFAULT_PRIMITIVES_DIRECTORY_FULL_PATH "C:/Program Files/LDraw/P/"
#endif

#define LD_PARSER_ALLOW_WHITE_SPACE (true)

//generic parser
class LDparserClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: SHAREDvectorClass SHAREDvector;
	public: bool parseFile(string parseFileName, LDreference* initialReference, LDreference* parentReference, const bool recurseIntoPartsDir);

	private: double calcModXPosBasedUponRotate(const vec* childRelativePosition, const mat* parentReferenceDeformationMatrix);
	private: double calcModYPosBasedUponRotate(const vec* childRelativePosition, const mat* parentReferenceDeformationMatrix);
	private: double calcModZPosBasedUponRotate(const vec* childRelativePosition, const mat* parentReferenceDeformationMatrix);

	private: string removeWhiteSpaceFromString(const string s);
};


#endif

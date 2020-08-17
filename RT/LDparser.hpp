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
 * File Name: LDparser.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2020 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3n7d 17-August-2020
 * /
 *******************************************************************************/


#ifndef HEADER_LD_PARSER
#define HEADER_LD_PARSER

#include "LDreferenceClass.hpp"
#include "SHAREDvector.hpp"
#ifdef USE_LRRC
#include "LRRCparser.hpp"
#endif

#ifndef COMPILE_UNREAL_PROJECT
#ifdef LINUX
	#define DEFAULT_PARTS_DIRECTORY_FULL_PATH "/usr/share/local/LDRAW/PARTS/"
	#define DEFAULT_PARTS_PRIMITIVES_DIRECTORY_FULL_PATH "/usr/share/local/LDRAW/P/"
#else
	#define DEFAULT_PARTS_DIRECTORY_FULL_PATH "D:/Program Files (x86)/LDraw/PARTS/parts/"
	#define DEFAULT_PARTS_PRIMITIVES_DIRECTORY_FULL_PATH "D:/Program Files (x86)/LDraw/PARTS/p/"
#endif
#endif

#define LD_PARSER_ALLOW_WHITE_SPACE (true)

//generic parser
class LDparserClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: SHAREDvectorClass SHAREDvector;
	#ifdef USE_LRRC
	private: LRRCmodelClassClass LRRCmodelClass;
	private: LRRCparserClass LRRCparser;
	#endif
	public: bool parseFile(string parseFileName, LDreference* initialReference, LDreference* parentReference, const bool recurseIntoPartsDir);

	public: double calcModXPosBasedUponRotate(const vec* childRelativePosition, const mat* parentReferenceDeformationMatrix);
	public: double calcModYPosBasedUponRotate(const vec* childRelativePosition, const mat* parentReferenceDeformationMatrix);
	public: double calcModZPosBasedUponRotate(const vec* childRelativePosition, const mat* parentReferenceDeformationMatrix);

	private: string removeWhiteSpaceFromString(const string s);
};


#endif

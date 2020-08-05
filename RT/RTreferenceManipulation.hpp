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
 * File Name: RTreferenceManipulation.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2020 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3n3a 28-May-2020
 * /
 *******************************************************************************/


#ifndef HEADER_RT_REFERENCE_MANIPULATION
#define HEADER_RT_REFERENCE_MANIPULATION

#define CHAR_NEWLINE '\n'

#include "LDreferenceClass.hpp"
#include "RTviewinfo.hpp"
#include "LDreferenceManipulation.hpp"
#include "SHAREDvector.hpp"
#include "RToperations.hpp"

class RTreferenceManipulationClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: LDreferenceManipulationClass LDreferenceManipulation;
	private: SHAREDvectorClass SHAREDvector;
	private: RToperationsClass RToperations;
	public: bool write2DReferenceListCollapsedTo1DToFileRayTraceFormat(string fileName, LDreference* firstReference, const bool useCustomViewInfo, const RTviewInfo* vi, const bool useCustomLightSource, const vec* lightSourcePosition, const string lightSourceColour);
		private: bool writeRayTraceFormatHeaderInfo(ofstream* writeFileObject, const bool useCustomViewInfo, const RTviewInfo* vi, const bool useCustomLightSource, const vec* lightSourcePosition, const string lightSourceColour);
		private: bool write2DReferencesLayerToFileObjectRayTraceFormat(ofstream* writeFileObject, LDreference* firstReferenceInLayer);
			private: bool addReferenceToFileObjectRayTraceFormat(ofstream* writeFileObject, LDreference* currentReference);
};

#endif

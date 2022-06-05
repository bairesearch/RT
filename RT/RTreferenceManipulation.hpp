 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: RTreferenceManipulation.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3q1a 05-June-2022
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

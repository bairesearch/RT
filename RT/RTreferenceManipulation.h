/*******************************************************************************
 *
 * File Name: RTreferenceManipulation.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3a7b 09-June-2012
 *
 *******************************************************************************/

#ifndef HEADER_RT_REFERENCE_MANIPULATION
#define HEADER_RT_REFERENCE_MANIPULATION

#define CHAR_NEWLINE '\n'

#include "LDreferenceClass.h"
#include "RTviewinfo.h"

bool write2DReferenceListCollapsedTo1DToFileRayTraceFormat(char * fileName, Reference * firstReference, bool useCustomViewInfo, view_info * vi, bool useCustomLightSource, vec * lightSourcePosition, char * lightSourceColour);
	bool writeRayTraceFormatHeaderInfo(ofstream * writeFileObject, bool useCustomViewInfo, view_info * vi, bool useCustomLightSource, vec * lightSourcePosition, char * lightSourceColour);
	bool write2DReferencesLayerToFileObjectRayTraceFormat(ofstream * writeFileObject, Reference * firstReferenceInLayer);
		bool addReferenceToFileObjectRayTraceFormat(ofstream * writeFileObject, Reference * currentReference);

#endif

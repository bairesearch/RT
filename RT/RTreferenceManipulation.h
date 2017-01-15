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
 * File Name: RTreferenceManipulation.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3f7c 16-August-2015
 *
 *******************************************************************************/


#ifndef HEADER_RT_REFERENCE_MANIPULATION
#define HEADER_RT_REFERENCE_MANIPULATION

#define CHAR_NEWLINE '\n'

#include "LDreferenceClass.h"
#include "RTviewinfo.h"

bool write2DReferenceListCollapsedTo1DToFileRayTraceFormat(string fileName, LDreference* firstReference, bool useCustomViewInfo, RTviewInfo* vi, bool useCustomLightSource, vec* lightSourcePosition, string lightSourceColour);
	bool writeRayTraceFormatHeaderInfo(ofstream* writeFileObject, bool useCustomViewInfo, RTviewInfo* vi, bool useCustomLightSource, vec* lightSourcePosition, string lightSourceColour);
	bool write2DReferencesLayerToFileObjectRayTraceFormat(ofstream* writeFileObject, LDreference* firstReferenceInLayer);
		bool addReferenceToFileObjectRayTraceFormat(ofstream* writeFileObject, LDreference* currentReference);

#endif

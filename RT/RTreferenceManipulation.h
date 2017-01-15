/*******************************************************************************
 * 
 * This file is part of BAIPROJECT.
 * 
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation.
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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3c1a 11-October-2012
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

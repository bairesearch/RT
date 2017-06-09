/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is licensed under the GNU Affero General Public License
 * version 3, as published by the Free Software Foundation. The use of
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
 * File Name: RTreferenceManipulation.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3l1d 01-June-2017
 *
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

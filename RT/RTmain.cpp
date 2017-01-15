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
 * File Name: RTmain.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3h14a 11-December-2015
 *
 *******************************************************************************/


#include "RTmain.h"
#include "RTscene.h"
#include "LDparser.h"
#include "RTreferenceManipulation.h"
#include "LDreferenceManipulation.h"

#ifndef LINUX
	#include <windows.h>
#endif




static char errmessage[] = "Usage:  OpenRT.exe [options]"
"\n"
"\n\twhere options are any of the following"
"\n"
"\n\t-lighting [int]   : lighting type (0 = basic, 2 = ambient diffuse specular) (def: 2)"
"\n"
"\n\t-oppm [string]     : .ppm output filename (def: 3Dscene.ppm)"
"\n"
"\n\t-iotal [string]     : .tal intermediary input/output filename (def: 3Dscene.tal)"
"\n"
"\n\t-ildr [string]     : .ldr input filename (def: 3Dscene.ldr)"
"\n\t-width [int]      : image width in pixels (def: 320)"
"\n\t-height [int]     : image height in pixels (def: 200)"
"\n\t-vieweyex [float] : viewport position of eye x (def: 20)"
"\n\t-vieweyey [float] : viewport position of eye y (def: 20)"
"\n\t-vieweyez [float] : viewport position of eye z (def: 20)"
"\n\t-viewatx [float]  : viewport position of object x (def: 0)"
"\n\t-viewaty [float]  : viewport position of object y (def: 0)"
"\n\t-viewatz [float]  : viewport position of object z (def: 0)"
"\n\t-viewupx [float]  : viewport vertical orientation of eye x (def: 0)"
"\n\t-viewupy [float]  : viewport vertical orientation of eye y (def: 0)"
"\n\t-viewupz [float]  : viewport vertical orientation of eye z (def: 100)"
"\n\t-viewfocal [float]: viewport focal distance (def: 4)"
"\n\t-viewsizew [float]: viewport width (def: 4)"
"\n\t-viewsizeh [float]: viewport height (def: 3)"
"\n"
"\n\t-lightx [float]   : position of light point source x (def: 20)"
"\n\t-lighty [float]   : position of light point source y (def: -10)"
"\n\t-lightz [float]   : position of light point source z (def: 20)"
"\n\t-lightcol [string]: light point source colour (def: white)"
"\n"
"\n\t-workingfolder [string] : working directory name for input files (def: same as exe)"
"\n\t-exefolder [string]     : exe directory name for executables; OpenRT.exe (def: same as exe)"
"\n\t-tempfolder [string]    : temp directory name for temporary and output files (def: same as exe)"
"\n"
"\n\t-version          : print version"
"\n"
"\n\tThe program performs raytracing of the given vector graphics file (.ldr or .tal),"
"\n \tand produces a .ppm output file of the rendered scene."
"\n"
"\n";

int main(int argc,char* *argv)
{
	bool result = true;

	int version;
	int lightingMode = LIGHTING_MODE_AMBIENT_DIFFUSE_SPECULAR;

	RTviewInfo viewinfo;
	viewinfo.imageWidth = TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_WIDTH;
	viewinfo.imageHeight = TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_HEIGHT;
	viewinfo.eye.x = TAL_FILE_HEADER_DEFAULT_EYE_X;		//CHECK THIS; preferably the eye moves around the object
	viewinfo.eye.y = TAL_FILE_HEADER_DEFAULT_EYE_Y;
	viewinfo.eye.z = TAL_FILE_HEADER_DEFAULT_EYE_Z;
	viewinfo.viewAt.x = TAL_FILE_HEADER_DEFAULT_VIEWAT_X;
	viewinfo.viewAt.y = TAL_FILE_HEADER_DEFAULT_VIEWAT_Y;
	viewinfo.viewAt.z = TAL_FILE_HEADER_DEFAULT_VIEWAT_Z;
	viewinfo.viewUp.x = TAL_FILE_HEADER_DEFAULT_VIEWUP_X;
	viewinfo.viewUp.y = TAL_FILE_HEADER_DEFAULT_VIEWUP_Y;
	viewinfo.viewUp.z = TAL_FILE_HEADER_DEFAULT_VIEWUP_Z;
	viewinfo.focalLength = TAL_FILE_HEADER_DEFAULT_FOCAL;
	viewinfo.viewWidth = TAL_FILE_HEADER_DEFAULT_VIEWSIZE_WIDTH;
	viewinfo.viewHeight = TAL_FILE_HEADER_DEFAULT_VIEWSIZE_HEIGHT;

 	bool useCustomLightSource = true;
	vec lightSourcePosition;
	lightSourcePosition.x = TAL_FILE_HEADER_DEFAULT_POINTSOURCE_X;
	lightSourcePosition.y = TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Y;
	lightSourcePosition.z = TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Z;
	string lightSourceColour = TAL_FILE_HEADER_DEFAULT_POINTSOURCE_COLOUR;

	/*==============================================================
	* Interpret parameters from Command-line Arguments
	*==============================================================
	*/

	string topLevelSceneFileName = "3Dscene.ldr";
	string topLevelSceneFileNameCollapsed = "3Dscene.ldr";
	string topLevelSceneFileNameCollapsedForRayTracing = "3Dscene.tal";
	string imageFileName = "3Dscene.ppm";

	bool useLDRfile = false;

	if ((argumentExists(argc,argv,"-iotal")) || (argumentExists(argc,argv,"-ildr")))
	{
		if (argumentExists(argc,argv,"-iotal"))
		topLevelSceneFileNameCollapsedForRayTracing=getStringArgument(argc,argv,"-iotal");

		if (argumentExists(argc,argv,"-ildr"))
		{
			topLevelSceneFileName=getStringArgument(argc,argv,"-ildr");
			useLDRfile = true;
		}

		if (argumentExists(argc,argv,"-lighting"))
		lightingMode=getFloatArgument(argc,argv,"-lighting");

		if (argumentExists(argc,argv,"-oppm"))
		imageFileName=getStringArgument(argc,argv,"-oppm");

		if (argumentExists(argc,argv,"-width"))
		viewinfo.imageWidth=getFloatArgument(argc,argv,"-width");

		if (argumentExists(argc,argv,"-height"))
		viewinfo.imageHeight=getFloatArgument(argc,argv,"-height");

		if (argumentExists(argc,argv,"-vieweyex"))
		viewinfo.eye.x=getFloatArgument(argc,argv,"-vieweyex");

		if (argumentExists(argc,argv,"-vieweyey"))
		viewinfo.eye.y=getFloatArgument(argc,argv,"-vieweyey");

		if (argumentExists(argc,argv,"-vieweyez"))
		viewinfo.eye.z=getFloatArgument(argc,argv,"-vieweyez");

		if (argumentExists(argc,argv,"-viewatx"))
		viewinfo.viewAt.x=getFloatArgument(argc,argv,"-viewatx");

		if (argumentExists(argc,argv,"-viewaty"))
		viewinfo.viewAt.y=getFloatArgument(argc,argv,"-viewaty");

		if (argumentExists(argc,argv,"-viewatz"))
		viewinfo.viewAt.z=getFloatArgument(argc,argv,"-viewatz");

		if (argumentExists(argc,argv,"-viewupx"))
		viewinfo.viewUp.x=getFloatArgument(argc,argv,"-viewupx");

		if (argumentExists(argc,argv,"-viewupy"))
		viewinfo.viewUp.y=getFloatArgument(argc,argv,"-viewupy");

		if (argumentExists(argc,argv,"-viewupz"))
		viewinfo.viewUp.z=getFloatArgument(argc,argv,"-viewupz");

		if (argumentExists(argc,argv,"-viewfocal"))
		viewinfo.focalLength=getFloatArgument(argc,argv,"-viewfocal");

		if (argumentExists(argc,argv,"-viewsizew"))
		viewinfo.viewWidth=getFloatArgument(argc,argv,"-viewsizew");

		if (argumentExists(argc,argv,"-viewsizeh"))
		viewinfo.viewHeight=getFloatArgument(argc,argv,"-viewsizeh");

		if (argumentExists(argc,argv,"-lightx"))
		lightSourcePosition.x=getFloatArgument(argc,argv,"-lightx");

		if (argumentExists(argc,argv,"-lighty"))
		lightSourcePosition.y=getFloatArgument(argc,argv,"-lighty");

		if (argumentExists(argc,argv,"-lightz"))
		lightSourcePosition.z=getFloatArgument(argc,argv,"-lightz");

		if (argumentExists(argc,argv,"-lightcol"))
		lightSourceColour=getStringArgument(argc,argv,"-lightcol");

		string currentFolder = "";
		currentFolder = getCurrentDirectory();

		if (argumentExists(argc,argv,"-workingfolder"))
		{
			workingFolder=getStringArgument(argc,argv,"-workingfolder");
		}
		else
		{
			workingFolder = currentFolder;
		}
		if (argumentExists(argc,argv,"-exefolder"))
		{
			exeFolder=getStringArgument(argc,argv,"-exefolder");
		}
		else
		{
			exeFolder = currentFolder;
		}
		if (argumentExists(argc,argv,"-tempfolder"))
		{
			tempFolder=getStringArgument(argc,argv,"-tempfolder");
		}
		else
		{
			tempFolder = currentFolder;
		}

		setCurrentDirectory(workingFolder);

		if (argumentExists(argc,argv,"-version"))
		{
			cout << "OpenRT.exe - Project Version: 3h14a 11-December-2015" << endl;
			exit(1);
		}
	}
	else
	{
		printf(errmessage);
		exit(1);
	}

	//setLightingMode(LIGHTING_MODE_BASIC);

	if(useLDRfile)
	{
		LDreference* initialReferenceInSceneFile = new LDreference();
		LDreference* topLevelReferenceInSceneFile = new LDreference(topLevelSceneFileName, 1, true);	//The information in this object is not required or meaningful, but needs to be passed into the parseFile/parseReferenceList recursive function
		if(!parseFile(topLevelSceneFileName, initialReferenceInSceneFile, topLevelReferenceInSceneFile, true))
		{//file does not exist
			cout << "The file: " << topLevelSceneFileName << " does not exist in the directory" << endl;
			exit(0);
		}

		setCurrentDirectory(tempFolder);

		write2DreferenceListCollapsedTo1DtoFile(topLevelSceneFileNameCollapsed, initialReferenceInSceneFile);
		write2DReferenceListCollapsedTo1DToFileRayTraceFormat(topLevelSceneFileNameCollapsedForRayTracing, initialReferenceInSceneFile, true, &viewinfo, useCustomLightSource, &lightSourcePosition, lightSourceColour);

	}

	setLightingMode(lightingMode);
	rayTraceScene(topLevelSceneFileNameCollapsedForRayTracing, imageFileName, true, false, NULL, NULL, NULL, NULL);

	return (int)result;
}


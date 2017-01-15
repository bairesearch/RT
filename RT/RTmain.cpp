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
 * File Name: RTmain.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3a13a 24-Sept-2012
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
"\n\t-exefolder [string]     : exe directory name for executables OpenRT.exe and (def: same as exe)"
"\n\t-tempfolder [string]    : temp directory name for temporary and output files (def: same as exe)"
"\n"
"\n\t-version          : print version"
"\n"
"\n\tThe program performs raytracing of the given vector graphics file (.ldr or .tal),"
"\n \tand produces a .ppm output file of the rendered scene."
"\n"
"\n";

int main(int argc,char **argv)
{
	bool result = true;

	int version;
	int lightingMode = LIGHTING_MODE_AMBIENT_DIFFUSE_SPECULAR;

	view_info viewinfo;
	viewinfo.imgwidth = TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_WIDTH;
	viewinfo.imgheight = TAL_FILE_HEADER_DEFAULT_IMAGE_SIZE_HEIGHT;
	viewinfo.eye.x = TAL_FILE_HEADER_DEFAULT_EYE_X;		//CHECK THIS; preferably the eye moves around the object
	viewinfo.eye.y = TAL_FILE_HEADER_DEFAULT_EYE_Y;
	viewinfo.eye.z = TAL_FILE_HEADER_DEFAULT_EYE_Z;
	viewinfo.viewat.x = TAL_FILE_HEADER_DEFAULT_VIEWAT_X;
	viewinfo.viewat.y = TAL_FILE_HEADER_DEFAULT_VIEWAT_Y;
	viewinfo.viewat.z = TAL_FILE_HEADER_DEFAULT_VIEWAT_Z;
	viewinfo.viewup.x = TAL_FILE_HEADER_DEFAULT_VIEWUP_X;
	viewinfo.viewup.y = TAL_FILE_HEADER_DEFAULT_VIEWUP_Y;
	viewinfo.viewup.z = TAL_FILE_HEADER_DEFAULT_VIEWUP_Z;
	viewinfo.focal_length = TAL_FILE_HEADER_DEFAULT_FOCAL;
	viewinfo.viewwidth = TAL_FILE_HEADER_DEFAULT_VIEWSIZE_WIDTH;
	viewinfo.viewheight = TAL_FILE_HEADER_DEFAULT_VIEWSIZE_HEIGHT;

 	bool useCustomLightSource = true;
	vec lightSourcePosition;
	lightSourcePosition.x = TAL_FILE_HEADER_DEFAULT_POINTSOURCE_X;
	lightSourcePosition.y = TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Y;
	lightSourcePosition.z = TAL_FILE_HEADER_DEFAULT_POINTSOURCE_Z;
	char * lightSourceColour = new char[10];
	strcpy(lightSourceColour, TAL_FILE_HEADER_DEFAULT_POINTSOURCE_COLOUR);

	/*==============================================================
	* Interpret parameters from Command-line Arguments
	*==============================================================
	*/

	char * topLevelSceneFileName = new char[100];
	strcpy(topLevelSceneFileName, "3Dscene.ldr");
	char * topLevelSceneFileNameCollapsed = new char[100];
	strcpy(topLevelSceneFileNameCollapsed, "3Dscene.ldr");
	char * topLevelSceneFileNameCollapsedForRayTracing = new char[100];
	strcpy(topLevelSceneFileNameCollapsedForRayTracing, "3Dscene.tal");
	char * imageFileName = new char[100];
	strcpy(imageFileName, "3Dscene.ppm");

	bool useLDRfile = false;

	if ((exists_argument(argc,argv,"-iotal")) || (exists_argument(argc,argv,"-ildr")))
	{
		if (exists_argument(argc,argv,"-iotal"))
		topLevelSceneFileNameCollapsedForRayTracing=get_char_argument(argc,argv,"-iotal");

		if (exists_argument(argc,argv,"-ildr"))
		{
			topLevelSceneFileName=get_char_argument(argc,argv,"-ildr");
			useLDRfile = true;
		}

		if (exists_argument(argc,argv,"-lighting"))
		lightingMode=get_float_argument(argc,argv,"-lighting");

		if (exists_argument(argc,argv,"-oppm"))
		imageFileName=get_char_argument(argc,argv,"-oppm");

		if (exists_argument(argc,argv,"-width"))
		viewinfo.imgwidth=get_float_argument(argc,argv,"-width");

		if (exists_argument(argc,argv,"-height"))
		viewinfo.imgheight=get_float_argument(argc,argv,"-height");

		if (exists_argument(argc,argv,"-vieweyex"))
		viewinfo.eye.x=get_float_argument(argc,argv,"-vieweyex");

		if (exists_argument(argc,argv,"-vieweyey"))
		viewinfo.eye.y=get_float_argument(argc,argv,"-vieweyey");

		if (exists_argument(argc,argv,"-vieweyez"))
		viewinfo.eye.z=get_float_argument(argc,argv,"-vieweyez");

		if (exists_argument(argc,argv,"-viewatx"))
		viewinfo.viewat.x=get_float_argument(argc,argv,"-viewatx");

		if (exists_argument(argc,argv,"-viewaty"))
		viewinfo.viewat.y=get_float_argument(argc,argv,"-viewaty");

		if (exists_argument(argc,argv,"-viewatz"))
		viewinfo.viewat.z=get_float_argument(argc,argv,"-viewatz");

		if (exists_argument(argc,argv,"-viewupx"))
		viewinfo.viewup.x=get_float_argument(argc,argv,"-viewupx");

		if (exists_argument(argc,argv,"-viewupy"))
		viewinfo.viewup.y=get_float_argument(argc,argv,"-viewupy");

		if (exists_argument(argc,argv,"-viewupz"))
		viewinfo.viewup.z=get_float_argument(argc,argv,"-viewupz");

		if (exists_argument(argc,argv,"-viewfocal"))
		viewinfo.focal_length=get_float_argument(argc,argv,"-viewfocal");

		if (exists_argument(argc,argv,"-viewsizew"))
		viewinfo.viewwidth=get_float_argument(argc,argv,"-viewsizew");

		if (exists_argument(argc,argv,"-viewsizeh"))
		viewinfo.viewheight=get_float_argument(argc,argv,"-viewsizeh");

		if (exists_argument(argc,argv,"-lightx"))
		lightSourcePosition.x=get_float_argument(argc,argv,"-lightx");

		if (exists_argument(argc,argv,"-lighty"))
		lightSourcePosition.y=get_float_argument(argc,argv,"-lighty");

		if (exists_argument(argc,argv,"-lightz"))
		lightSourcePosition.z=get_float_argument(argc,argv,"-lightz");

		if (exists_argument(argc,argv,"-lightcol"))
		lightSourceColour=get_char_argument(argc,argv,"-lightcol");

		char currentFolder[EXE_FOLDER_PATH_MAX_LENGTH];
		#ifdef LINUX
		getcwd(currentFolder, EXE_FOLDER_PATH_MAX_LENGTH);
		#else
		::GetCurrentDirectory(EXE_FOLDER_PATH_MAX_LENGTH, currentFolder);
		#endif

		if (exists_argument(argc,argv,"-workingfolder"))
		{
			workingFolderCharStar=get_char_argument(argc,argv,"-workingfolder");
		}
		else
		{
			workingFolderCharStar = currentFolder;
		}
		if (exists_argument(argc,argv,"-exefolder"))
		{
			exeFolderCharStar=get_char_argument(argc,argv,"-exefolder");
		}
		else
		{
			exeFolderCharStar = currentFolder;
		}
		if (exists_argument(argc,argv,"-tempfolder"))
		{
			tempFolderCharStar=get_char_argument(argc,argv,"-tempfolder");
		}
		else
		{
			tempFolderCharStar = currentFolder;
		}

		#ifdef LINUX
		chdir(workingFolderCharStar);
		#else
		::SetCurrentDirectory(workingFolderCharStar);
		#endif

		if (exists_argument(argc,argv,"-version"))
		{
			cout << "OpenRT.exe - Project Version: 3a13a 24-Sept-2012" << endl;
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
		Reference * initialReferenceInSceneFile = new Reference();
		Reference * topLevelReferenceInSceneFile = new Reference(topLevelSceneFileName, 1, true);	//The information in this object is not required or meaningful, but needs to be passed into the parseFile/parseReferenceList recursive function
		if(!parseFile(topLevelSceneFileName, initialReferenceInSceneFile, topLevelReferenceInSceneFile, true))
		{//file does not exist
			cout << "The file: " << topLevelSceneFileName << " does not exist in the directory" << endl;
			exit(0);
		}

		#ifdef LINUX
		chdir(tempFolderCharStar);
		#else
		::SetCurrentDirectory(tempFolderCharStar);
		#endif

		write2DReferenceListCollapsedTo1DToFile(topLevelSceneFileNameCollapsed, initialReferenceInSceneFile);
		write2DReferenceListCollapsedTo1DToFileRayTraceFormat(topLevelSceneFileNameCollapsedForRayTracing, initialReferenceInSceneFile, true, &viewinfo, useCustomLightSource, &lightSourcePosition, lightSourceColour);

	}

	setLightingMode(lightingMode);
	rayTraceScene(topLevelSceneFileNameCollapsedForRayTracing, imageFileName, true, false, NULL, NULL, NULL, NULL);

	return (int)result;
}


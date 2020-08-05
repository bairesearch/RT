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
 * File Name: RTmain.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2020 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3n4a 02-June-2020
 * /
 *******************************************************************************/


#include "RTmain.hpp"

#ifndef LINUX
	#include <windows.h>
#endif




static char errmessage[] = "Usage:  RT.exe [options]"
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
"\n\t-inputfolder [string]   : input directory name for input files (def: same as exe)"
"\n\t-exefolder [string]     : exe directory name for executables; RT.exe (def: same as exe)"
"\n\t-outputfolder [string]  : output directory name for temporary and output files (def: same as exe)"
"\n"
"\n\t-version          : print version"
"\n"
"\n\tThe program performs raytracing of the given vector graphics file (.ldr or .tal),"
"\n \tand produces a .ppm output file of the rendered scene."
"\n"
"\n";

int main(const int argc, const char** argv)
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

	if((SHAREDvarsClass().argumentExists(argc,argv,"-iotal")) || (SHAREDvarsClass().argumentExists(argc,argv,"-ildr")))
	{
		if(SHAREDvarsClass().argumentExists(argc,argv,"-iotal"))
		topLevelSceneFileNameCollapsedForRayTracing=SHAREDvarsClass().getStringArgument(argc,argv,"-iotal");

		if(SHAREDvarsClass().argumentExists(argc,argv,"-ildr"))
		{
			topLevelSceneFileName=SHAREDvarsClass().getStringArgument(argc,argv,"-ildr");
			useLDRfile = true;
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-lighting"))
		{
			lightingMode=SHAREDvarsClass().getFloatArgument(argc,argv,"-lighting");
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-oppm"))
		{
			imageFileName=SHAREDvarsClass().getStringArgument(argc,argv,"-oppm");
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-width"))
		{
			viewinfo.imageWidth=SHAREDvarsClass().getFloatArgument(argc,argv,"-width");
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-height"))
		{
			viewinfo.imageHeight=SHAREDvarsClass().getFloatArgument(argc,argv,"-height");
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-vieweyex"))
		{
			viewinfo.eye.x=SHAREDvarsClass().getFloatArgument(argc,argv,"-vieweyex");
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-vieweyey"))
		{
			viewinfo.eye.y=SHAREDvarsClass().getFloatArgument(argc,argv,"-vieweyey");
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-vieweyez"))
		{
			viewinfo.eye.z=SHAREDvarsClass().getFloatArgument(argc,argv,"-vieweyez");
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-viewatx"))
		{
			viewinfo.viewAt.x=SHAREDvarsClass().getFloatArgument(argc,argv,"-viewatx");
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-viewaty"))
		{
			viewinfo.viewAt.y=SHAREDvarsClass().getFloatArgument(argc,argv,"-viewaty");
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-viewatz"))
		{
			viewinfo.viewAt.z=SHAREDvarsClass().getFloatArgument(argc,argv,"-viewatz");
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-viewupx"))
		{
			viewinfo.viewUp.x=SHAREDvarsClass().getFloatArgument(argc,argv,"-viewupx");
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-viewupy"))
		{
			viewinfo.viewUp.y=SHAREDvarsClass().getFloatArgument(argc,argv,"-viewupy");
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-viewupz"))
		{
			viewinfo.viewUp.z=SHAREDvarsClass().getFloatArgument(argc,argv,"-viewupz");
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-viewfocal"))
		{
			viewinfo.focalLength=SHAREDvarsClass().getFloatArgument(argc,argv,"-viewfocal");
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-viewsizew"))
		{
			viewinfo.viewWidth=SHAREDvarsClass().getFloatArgument(argc,argv,"-viewsizew");
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-viewsizeh"))
		{
			viewinfo.viewHeight=SHAREDvarsClass().getFloatArgument(argc,argv,"-viewsizeh");
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-lightx"))
		{
			lightSourcePosition.x=SHAREDvarsClass().getFloatArgument(argc,argv,"-lightx");
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-lighty"))
		{
			lightSourcePosition.y=SHAREDvarsClass().getFloatArgument(argc,argv,"-lighty");
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-lightz"))
		{
			lightSourcePosition.z=SHAREDvarsClass().getFloatArgument(argc,argv,"-lightz");
		}

		if(SHAREDvarsClass().argumentExists(argc,argv,"-lightcol"))
		{
			lightSourceColour=SHAREDvarsClass().getStringArgument(argc,argv,"-lightcol");
		}

		string currentFolder = "";
		currentFolder = SHAREDvarsClass().getCurrentDirectory();

		if(SHAREDvarsClass().argumentExists(argc,argv,"-inputfolder"))
		{
			inputFolder=SHAREDvarsClass().getStringArgument(argc,argv,"-inputfolder");
		}
		else
		{
			inputFolder = currentFolder;
		}
		if(SHAREDvarsClass().argumentExists(argc,argv,"-exefolder"))
		{
			exeFolder=SHAREDvarsClass().getStringArgument(argc,argv,"-exefolder");
		}
		else
		{
			exeFolder = currentFolder;
		}
		if(SHAREDvarsClass().argumentExists(argc,argv,"-outputfolder"))
		{
			outputFolder=SHAREDvarsClass().getStringArgument(argc,argv,"-outputfolder");
		}
		else
		{
			outputFolder = currentFolder;
		}

		SHAREDvarsClass().setCurrentDirectory(inputFolder);

		if(SHAREDvarsClass().argumentExists(argc,argv,"-version"))
		{
			cout << "RT.exe - Project Version: 3n4a 02-June-2020" << endl;
			exit(EXIT_OK);
		}
	}
	else
	{
		cerr << errmessage << endl;
		exit(EXIT_ERROR);
	}

	//RTsceneClass().setLightingMode(LIGHTING_MODE_BASIC);

	if(useLDRfile)
	{
		LDreference* initialReferenceInSceneFile = new LDreference();
		LDreference* topLevelReferenceInSceneFile = new LDreference(topLevelSceneFileName, 1, true);	//The information in this object is not required or meaningful, but needs to be passed into the parseFile/parseReferenceList recursive function
		if(!LDparserClass().parseFile(topLevelSceneFileName, initialReferenceInSceneFile, topLevelReferenceInSceneFile, true))
		{//file does not exist
			cerr << "The file: " << topLevelSceneFileName << " does not exist in the directory" << endl;
			exit(EXIT_ERROR);
		}

		SHAREDvarsClass().setCurrentDirectory(outputFolder);

		LDreferenceManipulationClass().write2DreferenceListCollapsedTo1DtoFile(topLevelSceneFileNameCollapsed, initialReferenceInSceneFile);
		RTreferenceManipulationClass().write2DReferenceListCollapsedTo1DToFileRayTraceFormat(topLevelSceneFileNameCollapsedForRayTracing, initialReferenceInSceneFile, true, &viewinfo, useCustomLightSource, &lightSourcePosition, lightSourceColour);

	}

	RTsceneClass().setLightingMode(lightingMode);
	RTsceneClass().rayTraceScene(topLevelSceneFileNameCollapsedForRayTracing, imageFileName, true, false, NULL, NULL, NULL, NULL);

	return (int)result;
}


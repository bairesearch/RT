/*******************************************************************************
 *
 * File Name: SHAREDglobalsDefs.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 3a7b 09-June-2012
 * Requirements: requires text parsed by RelEx (available in .CFF format <relations>)
 * Description: Generic Construct Functions: shared global definitions (configure to compile different BAI projects)
 *
 *******************************************************************************/

#ifndef HEADER_SHARED_GLOBAL_DEFS
#define HEADER_SHARED_GLOBAL_DEFS

//required for string and atof
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;
	
	
	/**********
	SOURCE PROJECT VARIABLES;
	***********/

	//current/active tests;
#define COMPILE_OR		//compileOR.bat -> OR.exe
//#define COMPILE_GIA		//compileGIA.bat -> GIA.exe
//#define COMPILE_GIA_WITH_CE
//#define COMPILE_CS		//compileCS.bat -> CS.exe
//#define COMPILE_RT		//compileRT.bat -> RT.exe
//#define COMPILE_ANN_WITH_RT	//compileANNwithRT.bat -> ANN.exe
//#define COMPILE_ANN		//compileANN.bat -> ANN.exe
//#define COMPILE_LRRC		//compileLRRC.bat -> LRRC.exe
//#define COMPILE_OLC		//compileOLC.bat -> OLC.exe

//inactive tests;
//#define COMPILE_TH_OR_IMAGE_CATEGORISTION_NN	//ORTHimageCategorisationNN.exe
//#define COMPILE_LRRC_WITH_ANN		[compilation broken; requires updating]
//#define COMPILE_TH_ANN_WITH_LRRC	[compilation broken; requires updating]

	//old tests
//#define COMPILE_TH_OR_METHOD_2DOD
//#define COMPILE_TH_OR_METHOD_3DOD
//#define COMPILE_TH_RT
//#define COMPILE_TH_OR_METHOD_2DOD_WITH_ANN
//#define COMPILE_TH_OR_METHOD_3DOD_WITH_ANN



	/**********
	OS DEPENDENT VARIABLES;
	***********/

#define LINUX
#ifndef LINUX
	//else assume windows (affects default parts directory only - this is ISO C++ so it should compile on any platform)
	//#include <windows.h>
#endif

		
	

#define EXE_FOLDER_PATH_MAX_LENGTH (1000)
extern char * exeFolderCharStar;
extern char * workingFolderCharStar;
extern char * tempFolderCharStar;




	/**********
	COMPILATION TYPE DEPENDENT VARIABLES;
	***********/
	
	
#ifdef COMPILE_GIA_WITH_CE
	#define USE_GIA
	#define USE_CE
#endif
#ifdef COMPILE_GIA
	#define USE_GIA
#endif
#ifdef USE_GIA
	#define USE_RT
#endif



#ifdef COMPILE_CS
	#define USE_CS
#endif
#ifdef USE_CS
	#define USE_RT
#endif



#ifdef COMPILE_OR
	#define USE_OR
#endif
#ifdef COMPILE_TH_OR_IMAGE_CATEGORISTION_NN
	#define USE_OR
	#define USE_ANN
#endif
#ifdef COMPILE_TH_OR_METHOD_2DOD
	#define USE_OR
#endif
#ifdef COMPILE_TH_OR_METHOD_3DOD
	#define USE_OR
	#define OR_METHOD3DOD_TEST
#endif
#ifdef COMPILE_TH_OR_METHOD_2DOD_WITH_ANN
	#define USE_ANN
	#define USE_OR
#endif
#ifdef COMPILE_TH_OR_METHOD_3DOD_WITH_ANN
	#define USE_ANN
	#define USE_OR
#endif
#ifdef USE_OR
	#define USE_RT
#endif



//OLD;
#ifdef OR_USE_OR_NEURAL_NETWORK_COMPARITOR
	#define OR_TEST_ORI_AND_POS_NOISE_DURING_TRANING_AND_TESTING
	#define OR_MANY_NUMBER_OF_OUTPUT_FILES
#endif



#ifdef COMPILE_ANN
	#define USE_ANN
#endif
#ifdef COMPILE_ANN_WITH_RT
	#define USE_ANN
	#define USE_RT
#endif



#ifdef COMPILE_RT
	#define USE_RT
#endif
#ifdef COMPILE_TH_RT
	#define USE_RT
#endif



#ifdef COMPILE_LRRC
	#define USE_LRRC
#endif
#ifdef COMPILE_LRRC_WITH_ANN
	#define USE_LRRC
	#define USE_ANN
	#define USE_RT
#endif
#ifdef COMPILE_TH_ANN_WITH_LRRC
	#define USE_LRRC
	#define USE_ANN
	#define TH_USE_ANN_TEST_HARNESS
	#define USE_RT
#endif



	//ANN, LRRC, + OR;
//Test variables (need optimisation)
#define MAX_ANN_BACK_PROPAGATION_ERROR (1000.0)



	//ASCII variables
#define CHAR_TAB '\t'
#define CHAR_COMMA ','
#define CHAR_NEWLINE '\n'
#define CHAR_OPEN_BRACKET '('
#define CHAR_CLOSE_BRACKET ')'
#define CHAR_OPEN_SQUARE_BRACKET '['
#define CHAR_CLOSE_SQUARE_BRACKET ']'
#define CHAR_DASH '-'
#define CHAR_VERTICAL_BAR '|'
#define CHAR_UNDERSCORE '_'
#define CHAR_SPACE ' '
#define CHAR_END_OF_STRING '\0'
#define CHAR_DEL (127)
#define CHAR_IRRELEVANT (CHAR_DEL)

#define STRING_TAB "\t"
#define STRING_NEW_LINE "\n"
#define STRING_SPACE " "



#endif

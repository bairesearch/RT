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
 * File Name: SHAREDvars.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3e7e 27-January-2015
 *
 *******************************************************************************/


#ifndef HEADER_SHARED_VARS
#define HEADER_SHARED_VARS

#include "SHAREDglobalDefs.h"

#define MAP_VALUE_OUT_OF_RANGE (8888888.0)


#define TRAIN (1)
#define TEST (0)
#define TRAIN_AND_TEST (2)

#define RT_RAYTRACE_NO_HIT_DEPTH_T (10000000.0)
#define RT_RAYTRACE_NO_HIT_POINT_X (0.0)
#define RT_RAYTRACE_NO_HIT_POINT_Y (0.0)
#define RT_RAYTRACE_NO_HIT_POINT_Z (0.0)






#define TRUE (1)
#define FALSE (0)

#define REALLY_FAR_AWAY (99999999999.9)
#define REALLY_LARGE_DOUBLE (1000000.0)
#define REALLY_LARGE_INT (1000000)
#define REALLY_SMALL_DOUBLE (-1000000.0)

#define OR_METHOD2DOD_DIMENSIONS (2)
#define OR_METHOD3DOD_DIMENSIONS (3)

/* common definitions*/
typedef struct { unsigned char r, g, b; } colour;
typedef struct { double x, y, z; } vec;
typedef struct { vec a; vec b; vec c; } mat;

#ifdef COMPILE_OLC
	#define DOUBLE_MIN_PRECISION 0.005
#else
	#define DOUBLE_MIN_PRECISION 0.00001
#endif

long getTimeAsLong();

bool compareDoubles(double a, double b);
bool compareDoublesArbitraryError(double a, double b, double error);

int maxInt(int a, int b);	//should be turned into a macro instead
int minInt(int a, int b);	//should be turned into a macro instead

double minDouble(double a, double b);	//should be turned into a macro instead
double maxDouble(double a, double b);	//should be turned into a macro instead

double absDouble(double val);

#ifdef SHARED_SUPPORT_DEPRECIATED_CODE
int argumentExists(int argc, char* *argv, char* keystr);
float getFloatArgument(int argc, char* *argv, char* keystr);
char* getCharArgument(int argc,char* *argv,char* keystr);
#endif
bool argumentExists(int argc, char* *argv, string keystr);
float getFloatArgument(int argc, char* *argv, string keystr);
string getStringArgument(int argc, char* *argv, string keystr);
void getStringArrayArgument(int argc, char* *argv, string keystr, vector<string>* inputFileNamesVector);
void changeDirectoryString(string newDirectory);
string getCurrentDirectoryString();

void getCurrentDirectory(char* folder);
void setCurrentDirectory(const char* folder);
void createDirectory(const char* folder);
bool directoryExists(const char* folder);

void copyColours(colour* colToModify, colour* colToCopy);

bool isWhiteSpace(char c);
string convertStringToLowerCase(string* arbitraryCaseString);

string convertIntToString(int integer);
string convertBoolToString(bool boolean);
string convertLongToString(long number);

bool textInTextArray(string text, string* textArray, int arraySize);
bool textInTextArray(string text, string* textArray, int arraySize, int* arrayIndexOfResultFound);
bool charInCharArray(char c, char* charArray, int arraySize);
bool intInIntArray(int iTest, int* intArray, int arraySize);
string replaceAllOccurancesOfString(string* textOrig, string stringToFind, string replacementString);
string replaceAllOccurancesOfString(string* textOrig, string stringToFind, string replacementString, bool* foundAtLeastOneInstance);

void writeByteArrayToFile(const char* fileName, char* fileByteArray, int fileByteArraySize);
void writeStringToFileObject(string s, ofstream* writeFileObject);
void writeStringToFile(string* fileName, string* s);

string getFileContents(string inputFileName);

#endif

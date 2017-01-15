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
 * File Name: SHAREDvars.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3c8a 13-October-2013
 *
 *******************************************************************************/

#include "SHAREDvars.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#ifdef LINUX
#include <sys/time.h>
#else
#include <time.h>
#include <windows.h>
#endif
#include <math.h>
#include <vector>
using namespace std;

long getTimeAsLong()
{
	#ifdef LINUX
	struct timeval tv;
	struct timezone tz;
	struct tm *tm;
	gettimeofday(&tv, &tz);
	tm=localtime(&tv.tv_sec);
	long timeAsLong = long(tm->tm_hour) * 60 * 60 * 1000000 + long(tm->tm_min) * 60 * 1000000 + long(tm->tm_sec) * 1000000 + long(tv.tv_usec);	//time in microseconds
	return timeAsLong;

	#else

	SYSTEMTIME systemTime;
	GetSystemTime(&systemTime);

	FILETIME fileTime;
	SystemTimeToFileTime(&systemTime, &fileTime);

	ULARGE_INTEGER uli;
	uli.LowPart = fileTime.dwLowDateTime; // could use memcpy here!
	uli.HighPart = fileTime.dwHighDateTime;

	ULONGLONG systemTimeIn_ms(uli.QuadPart/10000);

	//cout << "systemTimeIn_ms = " << systemTimeIn_ms << endl;

	return systemTimeIn_ms;

	#endif


}

void copyColours(colour * colToModify, colour * colToCopy)
{
	colToModify->r = colToCopy->r;
	colToModify->g = colToCopy->g;
	colToModify->b = colToCopy->b;
}


bool compareDoublesArbitraryError(double a, double b, double error)
{
	bool result;
	if((a < (b+error)) && (a > (b-error)))
	{
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}


bool compareDoubles(double a, double b)
{
	bool result;
	if((a < (b+DOUBLE_MIN_PRECISION)) && (a > (b-DOUBLE_MIN_PRECISION)))
	{
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}


//generic functions

int maxInt(int a, int b)
{
	if(a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int minInt(int a, int b)
{
	if(a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

double minDouble(double a, double b)
{
	if(a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}
double maxDouble(double a, double b)
{
	if(a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

double absDouble(double val)
{
	if(val < 0.0)
	{
		return (-val);
	}
	else
	{
		return val;
	}
}

#ifdef SHARED_SUPPORT_DEPRECIATED_CODE

int argumentExists(int argc, char **argv, char *keystr)
{
	for(int i=1; i<argc; i++)
	{
		//cout << "argv[i] = " << argv[i] << endl;
		if(strcmp(argv[i],keystr) == 0)
		{
			return 1;
		}
	}
	return 0;
}

float getFloatArgument(int argc, char **argv, char *keystr)
{
	float result=0.0;
	bool foundArgument = false;

	for(int i=1; i<argc; i++)
	{
		if(!foundArgument)
		{	
			if(strcmp(argv[i], keystr) == 0)
			{
				result = atof(argv[i+1]);
				foundArgument = true;
			}
		}
	}
	if(!foundArgument)
	{
		fprintf(stderr,"Error: getFloatArgument(%s)\n",keystr);
		result = -999999999.0F;
		return result;
	}
	else 
	{
		return result;
	}
	result;
}

char *getCharArgument(int argc,char **argv,char *keystr)
{
	char *result;
	bool foundArgument = false;

	result=(char *) malloc(4096);
	result[0]=0;

	for(int i=1; i<argc; i++)
	{
		if(!foundArgument)
		{
			if(strcmp(argv[i], keystr) == 0)
			{
				sprintf(result,"%s",argv[i+1]);
				foundArgument = true;
			}
		}
	}
	if(!foundArgument)
	{
		fprintf(stderr,"Error: getCharArgument(%s)\n",keystr);
	}
	return result;
}
#endif

bool argumentExists(int argc, char **argv, string keystr)
{
	for(int i=1; i<argc; i++)
	{
		//cout << "argv[i] = " << argv[i] << endl;
		if(string(argv[i]) == keystr)
		{
			return true;
		}
	}
	return false;
}

float getFloatArgument(int argc, char **argv, string keystr)
{
	float result=0.0;
	bool foundArgument = false;

	for(int i=1; i<argc; i++)
	{
		if(!foundArgument)
		{	
			if(string(argv[i]) == keystr)
			{
				result = atof(argv[i+1]);
				foundArgument = true;
			}
		}
	}
	if(!foundArgument)
	{
		cout << "Error: getFloatArgument(" << keystr << ")" << endl;
		result = -999999999.0F;
		return result;
	}
	else 
	{
		return result;
	}
}

string getStringArgument(int argc, char **argv, string keystr)
{
	string stringArgument = "";
	bool foundArgument = false;
	for(int i=1;i<argc;i++)
	{
		//cout << "argument " << i << " = " << argv[i] << endl;
		if(!foundArgument)
		{
			if(string(argv[i]) == keystr)
			{
				stringArgument = string(argv[i+1]);
				foundArgument = true;
			}
		}
	}
	if(!foundArgument)
	{
		cout << "Error: getStringArgument(" << keystr << ")" << endl;
	}
	return stringArgument;
}

void getStringArrayArgument(int argc, char **argv, string keystr, vector<string> * inputFileNamesVector)
{
	bool foundArgument = false;
	for(int i=1;i<argc;i++)
	{
		//cout << "argument " << i << " = " << argv[i] << endl;
		if(!foundArgument)
		{
			if(string(argv[i]) == keystr)
			{
				int j=1;
				while(((argv[i+j])[0] != CHAR_DASH) && (i+j < argc))
				{
					string stringArgument = string(argv[i+j]);
					//cout << "stringArgument = " << stringArgument << endl;				
					inputFileNamesVector->push_back(stringArgument);
					foundArgument = true;
					j++;
				}
			}
		}
	}
	if(!foundArgument)
	{
		cout << "Error: getStringArrayArgument(" << keystr << ")" << endl;
	}
}

void changeDirectory(string newDirectory)
{
	char * newDirectoryCharStar = const_cast<char*>(newDirectory.c_str());
	#ifdef LINUX
	chdir(newDirectoryCharStar);
	#else
	::SetCurrentDirectory(newDirectoryCharStar);
	#endif	
}

string getCurrentDirectory()
{
	char currentFolderCharStar[EXE_FOLDER_PATH_MAX_LENGTH];
	#ifdef LINUX
	getcwd(currentFolderCharStar, EXE_FOLDER_PATH_MAX_LENGTH);
	#else
	::GetCurrentDirectory(EXE_FOLDER_PATH_MAX_LENGTH, currentFolderCharStar);
	#endif
	string currentFolder = string(currentFolderCharStar);
	return currentFolder;
}				

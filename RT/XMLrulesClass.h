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
 * File Name: XMLrulesClass.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: XML Functions
 * Project Version: 3c4b 01-December-2012
 *
 *******************************************************************************/

#ifndef HEADER_XML_RULES_CLASS
#define HEADER_XML_RULES_CLASS

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;

#include "SHAREDglobalDefs.h"
#include "XMLparserClass.h"


class RulesClass
{
private:
	/*There are currently no private attributes of this class*/
public:

	RulesClass(void); // constructor
	~RulesClass();	// and destructor.

	string name;	//attribute1;

	string stringValue;	//attribute2;
	double fractionalValue;
	int attribute4;
	int attribute5;
	int attribute6;
	int attribute7;
	int attribute8;

	RulesClass * next;
};

//High Level

#ifdef USE_CS
bool parseCSrulesXMLfile();
	bool parseCSRulesTag(XMLparserTag * currentTag);
#endif

#ifdef USE_GIA
bool parseGIArulesXMLfile();
	bool parseGIARulesTag(XMLparserTag * currentTag);
#endif

#ifdef USE_OR
bool parseORrulesXMLfile();
	bool parseORrulesTag(XMLparserTag * currentTag);
#endif

bool parseANNrulesXMLfile();
	bool parseANNrulesTag(XMLparserTag * currentTag);

bool addRulesClassObjectsBasedOnSectionTag(XMLparserTag * currentTag, string sectionTagName, RulesClass * firstReferenceToObjectClass, string tagName, int numberOfAttributes, string attributeName1, string attributeName2, string attributeName3, string attributeName4, string attributeName5, string attributeName6, string attributeName7, string attributeName8);
bool addRulesClassObjectBasedOnTag(XMLparserTag * currentTag, RulesClass * currentReferenceToObjectClass, string tagName, int numberOfAttributes, string attributeName1, string attributeName2, string attributeName3, string attributeName4, string attributeName5, string attributeName6, string attributeName7, string attributeName8);

extern RulesClass * ANNrulesSprite;	//common sprite xml file is ANNrules.xml
#ifdef USE_CS
extern RulesClass * CSrulesSprite;
extern RulesClass * CSrulesDraw;
#endif
#ifdef USE_GIA
extern RulesClass * GIArulesSprite;
extern RulesClass * GIArulesDraw;
#endif
#ifdef USE_OR
extern RulesClass * ORrulesObjectRecognition;
#endif


#endif

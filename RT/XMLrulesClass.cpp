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
 * File Name: XMLrulesClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: XML Functions
 * Project Version: 3c7a 11-August-2013
 *
 *******************************************************************************/

#include "XMLrulesClass.h"

//xml comments not yet supported by this parser

RulesClass * ANNrulesSprite;	//common sprite xml file is ANNrules.xml
#ifdef USE_CS
RulesClass * CSrulesSprite;
RulesClass * CSrulesDraw;
#endif
#ifdef USE_GIA
RulesClass * GIArulesSprite;
RulesClass * GIArulesDraw;
XMLparserTag * GIAfirstTagInXMLfile;
#endif
#ifdef USE_OR
RulesClass * ORrulesObjectRecognition;
#endif

static string nullString;
static bool nullBool;
static RulesClass nullRulesObject;

RulesClass::RulesClass(void)
{
	name = "";					//attribute 1

	stringValue = "";				//attribute 2 - this attribute may not be used by the object
	fractionalValue = 0.0;				//attribute 3 - this attribute may not be used by the object
	attribute4 = 0;				//attribute 4 - this attribute may not be used by the object
	attribute5 = 0;				//attribute 5 - this attribute may not be used by the object
	attribute6 = 0;				//attribute 6 - this attribute may not be used by the object
	attribute7 = 0;				//attribute 7 - this attribute may not be used by the object
	attribute8 = 0;				//attribute 8 - this attribute may not be used by the object

	next = NULL;

	/*
	defenceMod = 0;				//this attribute may not be used by the object

	closeCombatAttackMod = 0;	//this attribute may not be used by the object
	mountedAttackBonus = 0;		//this attribute may not be used by the object

	longDistanceAttackMod = 0;	//this attribute may not be used by the object
	longDistanceRange = 0;		//this attribute may not be used by the object

	*/
}

RulesClass::~RulesClass()
{
	if(next != NULL)
	{
		delete next;
	}
}


#ifdef USE_GIA
bool parseGIArulesXMLfile()
{
	bool result = true;

 	GIAfirstTagInXMLfile = new XMLparserTag();	//the firstTagInXMLfile object must be initialised here (in XMLrulesClass.cpp scope). if it is initialised in XMLparserClass.cpp else it will be come corrupted,
	if(!readXMLfile(GIA_RULES_XML_FILE_NAME, GIAfirstTagInXMLfile))
 	{
		result = false;
	}

	XMLparserTag * currentTag = GIAfirstTagInXMLfile;

	GIArulesSprite = new RulesClass();
	GIArulesDraw = new RulesClass();

	if(!parseGIARulesTag(currentTag))
	{
		result = false;
	}
	
	return result;
}

bool parseGIARulesTag(XMLparserTag * currentTag)
{
	bool result = true;

	XMLparserTag * currentTagUpdated = currentTag;
	currentTagUpdated = parseTagDownALevel(currentTagUpdated, RULES_XML_TAG_rules, &result);
	if(result)
	{
		if(!addRulesClassObjectsBasedOnSectionTag(currentTagUpdated, RULES_XML_TAG_sprite, GIArulesSprite, RULES_XML_TAG_miscellaneousItem, 3, RULES_XML_ATTRIBUTE_name, RULES_XML_ATTRIBUTE_stringValue, RULES_XML_ATTRIBUTE_fractionalValue, nullString, nullString, nullString, nullString, nullString))
		{
			result = false;
		}
		currentTagUpdated=currentTagUpdated->nextTag;
		if(!addRulesClassObjectsBasedOnSectionTag(currentTagUpdated, RULES_XML_TAG_draw, GIArulesDraw, RULES_XML_TAG_miscellaneousItem, 3, RULES_XML_ATTRIBUTE_name, RULES_XML_ATTRIBUTE_stringValue, RULES_XML_ATTRIBUTE_fractionalValue, nullString, nullString, nullString, nullString, nullString))
		{
			result = false;
		}
	}

	return result;
}
#endif


#ifdef USE_CS
bool parseCSrulesXMLfile()
{
	bool result = true;

 	XMLparserTag * firstTagInXMLfile = new XMLparserTag();	//the firstTagInXMLfile object must be initialised here (in XMLrulesClass.cpp scope). if it is initialised in XMLparserClass.cpp else it will be come corrupted,
 	if(!readXMLfile(CS_RULES_XML_FILE_NAME, firstTagInXMLfile))
 	{
		result = false;
	}

	XMLparserTag * currentTag = firstTagInXMLfile;

	CSrulesSprite = new RulesClass();
	CSrulesDraw = new RulesClass();

	if(!parseCSRulesTag(currentTag))
	{
		result = false;
	}

	delete firstTagInXMLfile;


	return result;
}

bool parseCSRulesTag(XMLparserTag * currentTag)
{
	bool result = true;

	XMLparserTag * currentTagUpdated = currentTag;
	currentTagUpdated = parseTagDownALevel(currentTagUpdated, RULES_XML_TAG_rules, &result);
	if(result)
	{
		if(!addRulesClassObjectsBasedOnSectionTag(currentTagUpdated, RULES_XML_TAG_sprite, CSrulesSprite, RULES_XML_TAG_miscellaneousItem, 3, RULES_XML_ATTRIBUTE_name, RULES_XML_ATTRIBUTE_stringValue, RULES_XML_ATTRIBUTE_fractionalValue, nullString, nullString, nullString, nullString, nullString))
		{
			result = false;
		}
		currentTagUpdated=currentTagUpdated->nextTag;
		if(!addRulesClassObjectsBasedOnSectionTag(currentTagUpdated, RULES_XML_TAG_draw, CSrulesDraw, RULES_XML_TAG_miscellaneousItem, 3, RULES_XML_ATTRIBUTE_name, RULES_XML_ATTRIBUTE_stringValue, RULES_XML_ATTRIBUTE_fractionalValue, nullString, nullString, nullString, nullString, nullString))
		{
			result = false;
		}
	}

	return result;
}
#endif




#ifdef USE_OR
bool parseORrulesXMLfile()
{
	bool result = true;

 	XMLparserTag * firstTagInXMLfile = new XMLparserTag();	//the firstTagInXMLfile object must be initialised here (in XMLrulesClass.cpp scope). if it is initialised in XMLparserClass.cpp else it will be come corrupted,
 	if(!readXMLfile(OR_RULES_XML_FILE_NAME, firstTagInXMLfile))
 	{
		result = false;
	}

	XMLparserTag * currentTag = firstTagInXMLfile;

	ORrulesObjectRecognition = new RulesClass();

	if(!parseORrulesTag(currentTag))
	{
		result = false;
	}

	delete firstTagInXMLfile;


	return result;
}

bool parseORrulesTag(XMLparserTag * currentTag)
{
	bool result = true;

	XMLparserTag * currentTagUpdated = currentTag;
	currentTagUpdated = parseTagDownALevel(currentTagUpdated, RULES_XML_TAG_rules, &result);
	if(result)
	{
		if(!addRulesClassObjectsBasedOnSectionTag(currentTagUpdated, RULES_XML_TAG_objectRecognition, ORrulesObjectRecognition, RULES_XML_TAG_miscellaneousItem, 3, RULES_XML_ATTRIBUTE_name, RULES_XML_ATTRIBUTE_stringValue, RULES_XML_ATTRIBUTE_fractionalValue, nullString, nullString, nullString, nullString, nullString))
		{
			result = false;
		}
	}

	return result;
}
#endif




bool parseANNrulesXMLfile()
{
	bool result = true;

 	XMLparserTag * firstTagInXMLfile = new XMLparserTag();	//the firstTagInXMLfile object must be initialised here (in XMLrulesClass.cpp scope). if it is initialised in XMLparserClass.cpp else it will be come corrupted,
 	if(!readXMLfile(ANN_RULES_XML_FILE_NAME, firstTagInXMLfile))
 	{
		result = false;
	}

	/*
	#define TEMP_XML_FILE_NAME "temp.xml"
 	if(!writeXMLfile(TEMP_XML_FILE_NAME, firstTagInXMLfile))
 	{
		result = false;
	}
	*/

	XMLparserTag * currentTag = firstTagInXMLfile;

	ANNrulesSprite = new RulesClass();

	if(!parseANNrulesTag(currentTag))
	{
		result = false;
	}

	delete firstTagInXMLfile;

	return result;
}




//Top Level
bool parseANNrulesTag(XMLparserTag * currentTag)
{
	bool result = true;

	XMLparserTag * currentTagUpdated = currentTag;
	currentTagUpdated = parseTagDownALevel(currentTagUpdated, RULES_XML_TAG_rules, &result);
	if(result)
	{
		if(!addRulesClassObjectsBasedOnSectionTag(currentTagUpdated, RULES_XML_TAG_sprite, ANNrulesSprite, RULES_XML_TAG_miscellaneousItem, 3, RULES_XML_ATTRIBUTE_name, RULES_XML_ATTRIBUTE_stringValue, RULES_XML_ATTRIBUTE_fractionalValue, nullString, nullString, nullString, nullString, nullString))
		{
			result = false;
		}
	}

	return result;
}







bool addRulesClassObjectsBasedOnSectionTag(XMLparserTag * currentTag, string sectionTagName, RulesClass * firstReferenceToObjectClass, string tagName, int numberOfAttributes, string attributeName1, string attributeName2, string attributeName3, string attributeName4, string attributeName5, string attributeName6, string attributeName7, string attributeName8)
{
	bool result = true;

	if(currentTag->name == sectionTagName)
	{
		XMLparserTag * currentLowerLevelTag = currentTag->firstLowerLevelTag;

		RulesClass * currentReferenceToObjectClass = firstReferenceToObjectClass;

		while(currentLowerLevelTag->nextTag != NULL)
		{
			if(!addRulesClassObjectBasedOnTag(currentLowerLevelTag, currentReferenceToObjectClass, tagName, numberOfAttributes, attributeName1, attributeName2, attributeName3, attributeName4, attributeName5, attributeName6, attributeName7, attributeName8))
			{
				result = false;
			}
			else
			{
				/*
				cout << "name = " << currentReferenceToObjectClass->name << endl;
				cout << "stringValue = " << currentReferenceToObjectClass->stringValue << endl;
				cout << "fractionalValue = " << currentReferenceToObjectClass->fractionalValue << endl;
				cout << "attribute4 = " << currentReferenceToObjectClass->attribute4 << endl;
				cout << "attribute5 = " << currentReferenceToObjectClass->attribute5 << endl;
				cout << "attribute6 = " << currentReferenceToObjectClass->attribute6 << endl;
				cout << "attribute7 = " << currentReferenceToObjectClass->attribute7 << endl;
				cout << "attribute8 = " << currentReferenceToObjectClass->attribute8 << endl;
				*/

				RulesClass * newObject = new RulesClass();
				currentReferenceToObjectClass->next = newObject;
				currentReferenceToObjectClass = currentReferenceToObjectClass->next;
			}

			currentLowerLevelTag = currentLowerLevelTag->nextTag;
		}
	}
	else
	{
		result = false;
		cout << "parse error; sectionTagName expected = " <<  sectionTagName << ". section tag name found = " << currentTag->name << endl;
	}
	currentTag = currentTag->nextTag;

	return result;

}


bool addRulesClassObjectBasedOnTag(XMLparserTag * currentTag, RulesClass * currentReferenceToObjectClass, string tagName, int numberOfAttributes, string attributeName1, string attributeName2, string attributeName3, string attributeName4, string attributeName5, string attributeName6, string attributeName7, string attributeName8)
{
	bool result = true;

	XMLParserAttribute * currentAttribute = currentTag->firstAttribute;

	int attributeNumber = 1;
	while(currentAttribute->nextAttribute != NULL)
	{
		if(attributeNumber == 1)
		{
			if(currentAttribute->name != attributeName1)
			{
				result = false;
				cout << "parse error; currentAttribute->name != attributeName1.  currentAttribute->name = " <<  currentAttribute->name << ". attributeName1 = " << attributeName1 << endl;
			}
			else
			{
				currentReferenceToObjectClass->name = currentAttribute->value;
			}
		}
		else if(attributeNumber == 2)
		{
			if(currentAttribute->name != attributeName2)
			{
				result = false;
				cout << "parse error; currentAttribute->name != attributeName2.  currentAttribute->name = " <<  currentAttribute->name << ". attributeName2 = " << attributeName2 << endl;
			}
			else
			{
				currentReferenceToObjectClass->stringValue = currentAttribute->value;
			}
		}
		else if(attributeNumber == 3)
		{
			if(currentAttribute->name != attributeName3)
			{
				result = false;
				cout << "parse error; currentAttribute->name != attributeName3.  currentAttribute->name = " <<  currentAttribute->name << ". attributeName3 = " << attributeName3 << endl;
			}
			else
			{
				currentReferenceToObjectClass->fractionalValue = atof(currentAttribute->value.c_str());
			}
		}
		else if(attributeNumber == 4)
		{
			if(currentAttribute->name != attributeName4)
			{
				result = false;
				cout << "parse error; currentAttribute->name != attributeName4.  currentAttribute->name = " <<  currentAttribute->name << ". attributeName4 = " << attributeName4 << endl;
			}
			else
			{
				currentReferenceToObjectClass->attribute4 = int(atof(currentAttribute->value.c_str()));
			}
		}
		else if(attributeNumber == 5)
		{
			if(currentAttribute->name != attributeName5)
			{
				result = false;
				cout << "parse error; currentAttribute->name != attributeName5.  currentAttribute->name = " <<  currentAttribute->name << ". attributeName5 = " << attributeName5 << endl;
			}
			else
			{
				currentReferenceToObjectClass->attribute5 = int(atof(currentAttribute->value.c_str()));
			}
		}
		else if(attributeNumber == 6)
		{
			if(currentAttribute->name != attributeName6)
			{
				result = false;
				cout << "parse error; currentAttribute->name != attributeName6.  currentAttribute->name = " <<  currentAttribute->name << ". attributeName6 = " << attributeName6 << endl;
			}
			else
			{
				currentReferenceToObjectClass->attribute6 = int(atof(currentAttribute->value.c_str()));
			}
		}
		else if(attributeNumber == 7)
		{
			if(currentAttribute->name != attributeName7)
			{
				result = false;
				cout << "parse error; currentAttribute->name != attributeName7.  currentAttribute->name = " <<  currentAttribute->name << ". attributeName7 = " << attributeName7 << endl;
			}
			else
			{
				currentReferenceToObjectClass->attribute7 = int(atof(currentAttribute->value.c_str()));
			}
		}
		else if(attributeNumber == 8)
		{
			if(currentAttribute->name != attributeName8)
			{
				result = false;
				cout << "parse error; currentAttribute->name != attributeName8.  currentAttribute->name = " <<  currentAttribute->name << ". attributeName8 = " << attributeName8 << endl;
			}
			else
			{
				currentReferenceToObjectClass->attribute8 = int(atof(currentAttribute->value.c_str()));
			}
		}
		attributeNumber++;

		currentAttribute = currentAttribute->nextAttribute;
	}

	if((attributeNumber-1) != numberOfAttributes)
	{
		result = false;
		cout << "(attributeNumber-1) != numberOfAttributes, (attributeNumber-1) =  " <<  (attributeNumber-1) << ". numberOfAttributes = " << numberOfAttributes << endl;
	}

	return result;
}









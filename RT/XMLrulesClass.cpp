/*******************************************************************************
 *
 * File Name: XMLrulesClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2010 Baxter AI (baxterai.com)
 * Project: XML Functions
 * Project Version: 3a6b 30-Apr-2012
 *
 *******************************************************************************/

#include "XMLrulesClass.h"

//xml comments not yet supported by this parser

#define ANN_RULES_XML_FILE_NAME "ANNrules.xml"
#define LRRC_RULES_XML_FILE_NAME "LRRCrules.xml"
#define CS_RULES_XML_FILE_NAME "CSrules.xml"
#define OR_RULES_XML_FILE_NAME "ORrules.xml"
#define GIA_RULES_XML_FILE_NAME "GIArules.xml"

#define RULES_XML_TAG_rules ((string)"rules")
#ifdef USE_LRRC
#define RULES_XML_TAG_unitTypeDetails ((string)"unitTypeDetails")
#define RULES_XML_TAG_part ((string)"part")
#define RULES_XML_TAG_unitCombatDetails ((string)"unitCombatDetails")
#define RULES_XML_TAG_armour ((string)"armour")
#define RULES_XML_TAG_head ((string)"head")
#define RULES_XML_TAG_torso ((string)"torso")
#define RULES_XML_TAG_shield ((string)"shield")
#define RULES_XML_TAG_weapons ((string)"weapons")
#define RULES_XML_TAG_closeCombat ((string)"closeCombat")
#define RULES_XML_TAG_longDistance ((string)"longDistance")
#define RULES_XML_TAG_other ((string)"other")
#define RULES_XML_TAG_buildingDetails ((string)"buildingDetails")
#define RULES_XML_TAG_terrainDefenceDetails ((string)"terrainDefenceDetails")
#define RULES_XML_TAG_unitTypeCatagories ((string)"unitTypeCatagories")
#define RULES_XML_TAG_unitType ((string)"unitType")
#define RULES_XML_TAG_miscellaneous ((string)"miscellaneous")
#endif
#define RULES_XML_TAG_miscellaneousItem ((string)"miscellaneousItem")
#define RULES_XML_TAG_sprite ((string)"sprite")
#ifdef USE_CS
#define RULES_XML_TAG_draw ((string)"draw")
#endif
#ifdef USE_GIA
#define RULES_XML_TAG_draw ((string)"draw")
#endif
#ifdef USE_OR
#define RULES_XML_TAG_objectRecognition ((string)"objectRecognition")
#endif

#define RULES_XML_ATTRIBUTE_name ((string)"name")
#ifdef USE_LRRC
#define RULES_XML_ATTRIBUTE_partID ((string)"partID")
#define RULES_XML_ATTRIBUTE_partIDLen ((string)"partIDLen")
#define RULES_XML_ATTRIBUTE_defenceMod ((string)"defenceMod")
#define RULES_XML_ATTRIBUTE_closeCombatAttackMod ((string)"closeCombatAttackMod")
#define RULES_XML_ATTRIBUTE_mountedAttackBonus ((string)"mountedAttackBonus")
#define RULES_XML_ATTRIBUTE_attackBonusAgainstMounted ((string)"attackBonusAgainstMounted")
#define RULES_XML_ATTRIBUTE_longDistanceAttackMod ((string)"longDistanceAttackMod")
#define RULES_XML_ATTRIBUTE_longDistanceRange ((string)"longDistanceRange")
#define RULES_XML_ATTRIBUTE_enum ((string)"enum")
#define RULES_XML_ATTRIBUTE_maxTravel ((string)"maxTravel")
#define RULES_XML_ATTRIBUTE_buildingMod ((string)"buildingMod")
#endif
#define RULES_XML_ATTRIBUTE_stringValue ((string)"stringValue")
#define RULES_XML_ATTRIBUTE_fractionalValue ((string)"fractionalValue")


/*
#define RULES_XML_TAG_rules "rules"
#define RULES_XML_TAG_unitTypeDetails "unitTypeDetails"
#define RULES_XML_TAG_part "part"
#define RULES_XML_TAG_unitCombatDetails "unitCombatDetails"
#define RULES_XML_TAG_armour "armour"
#define RULES_XML_TAG_head "head"
#define RULES_XML_TAG_torso "torso"
#define RULES_XML_TAG_shield "shield"
#define RULES_XML_TAG_weapons "weapons"
#define RULES_XML_TAG_closeCombat "closeCombat"
#define RULES_XML_TAG_longDistance "longDistance"
#define RULES_XML_TAG_other "other"
#define RULES_XML_TAG_buildingDetails "LRRCrulesBuildingDetails"
#define RULES_XML_TAG_terrainDefenceDetails "terrainDefenceDetails"
#define RULES_XML_TAG_unitTypeCatagories "LRRCrulesUnitTypeCatagories"
#define RULES_XML_TAG_unitType "unitType"
#define RULES_XML_TAG_miscellaneousItem "miscellaneousItem"

#define RULES_XML_ATTRIBUTE_name "name"
#define RULES_XML_ATTRIBUTE_partID "stringValue"
#define RULES_XML_ATTRIBUTE_partIDLen "partIDLen"
#define RULES_XML_ATTRIBUTE_defenceMod "defenceMod"
#define RULES_XML_ATTRIBUTE_closeCombatAttackMod "closeCombatAttackMod"
#define RULES_XML_ATTRIBUTE_mountedAttackBonus "mountedAttackBonus"
#define RULES_XML_ATTRIBUTE_attackBonusAgainstMounted "attackBonusAgainstMounted"
#define RULES_XML_ATTRIBUTE_longDistanceAttackMod "longDistanceAttackMod"
#define RULES_XML_ATTRIBUTE_longDistanceRange "longDistanceRange"
#define RULES_XML_ATTRIBUTE_enum "enum"
#define RULES_XML_ATTRIBUTE_maxTravel "maxTravel"
#define RULES_XML_ATTRIBUTE_value "value"
*/

#ifdef USE_LRRC
RulesClass * LRRCrulesUnitTypeDetails;
RulesClass * LRRCrulesUnitCombatDetailsDefenceHead;
RulesClass * LRRCrulesUnitCombatDetailsDefenceTorso;
RulesClass * LRRCrulesUnitCombatDetailsDefenceShield;
RulesClass * LRRCrulesUnitCombatDetailsAttackCloseCombat;
RulesClass * LRRCrulesUnitCombatDetailsAttackLongDistance;
RulesClass * LRRCrulesBuildingDetails;
RulesClass * LRRCrulesTerrainDetails;
RulesClass * LRRCrulesUnitTypeCatagories;
RulesClass * LRRCrulesMiscellaneous;
RulesClass * LRRCrulesSprite;
#endif
RulesClass * ANNrulesSprite;	//common sprite xml file is ANNrules.xml
#ifdef USE_CS
RulesClass * CSrulesSprite;
RulesClass * CSrulesDraw;
#endif
#ifdef USE_GIA
RulesClass * GIArulesSprite;
RulesClass * GIArulesDraw;
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
bool parseGIARulesXMLFile()
{
	bool result = true;

 	XMLParserTag * firstTagInXMLFile = new XMLParserTag();	//the firstTagInXMLFile object must be initialised here (in XMLrulesClass.cpp scope). if it is initialised in XMLParserClass.cpp else it will be come corrupted,
 	if(!readXMLFile(GIA_RULES_XML_FILE_NAME, firstTagInXMLFile))
 	{
		result = false;
	}

	XMLParserTag * currentTag = firstTagInXMLFile;

	GIArulesSprite = new RulesClass();
	GIArulesDraw = new RulesClass();

	if(!parseGIARulesTag(currentTag))
	{
		result = false;
	}

	delete firstTagInXMLFile;


	return result;
}

bool parseGIARulesTag(XMLParserTag * currentTag)
{
	bool result = true;

	XMLParserTag * currentTagUpdated = currentTag;
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
bool parseCSRulesXMLFile()
{
	bool result = true;

 	XMLParserTag * firstTagInXMLFile = new XMLParserTag();	//the firstTagInXMLFile object must be initialised here (in XMLrulesClass.cpp scope). if it is initialised in XMLParserClass.cpp else it will be come corrupted,
 	if(!readXMLFile(CS_RULES_XML_FILE_NAME, firstTagInXMLFile))
 	{
		result = false;
	}

	XMLParserTag * currentTag = firstTagInXMLFile;

	CSrulesSprite = new RulesClass();
	CSrulesDraw = new RulesClass();

	if(!parseCSRulesTag(currentTag))
	{
		result = false;
	}

	delete firstTagInXMLFile;


	return result;
}

bool parseCSRulesTag(XMLParserTag * currentTag)
{
	bool result = true;

	XMLParserTag * currentTagUpdated = currentTag;
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
bool parseORRulesXMLFile()
{
	bool result = true;

 	XMLParserTag * firstTagInXMLFile = new XMLParserTag();	//the firstTagInXMLFile object must be initialised here (in XMLrulesClass.cpp scope). if it is initialised in XMLParserClass.cpp else it will be come corrupted,
 	if(!readXMLFile(OR_RULES_XML_FILE_NAME, firstTagInXMLFile))
 	{
		result = false;
	}

	XMLParserTag * currentTag = firstTagInXMLFile;

	ORrulesObjectRecognition = new RulesClass();

	if(!parseORRulesTag(currentTag))
	{
		result = false;
	}

	delete firstTagInXMLFile;


	return result;
}

bool parseORRulesTag(XMLParserTag * currentTag)
{
	bool result = true;

	XMLParserTag * currentTagUpdated = currentTag;
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




bool parseANNRulesXMLFile()
{
	bool result = true;

 	XMLParserTag * firstTagInXMLFile = new XMLParserTag();	//the firstTagInXMLFile object must be initialised here (in XMLrulesClass.cpp scope). if it is initialised in XMLParserClass.cpp else it will be come corrupted,
 	if(!readXMLFile(ANN_RULES_XML_FILE_NAME, firstTagInXMLFile))
 	{
		result = false;
	}

	/*
	#define TEMP_XML_FILE_NAME "temp.xml"
 	if(!writeXMLFile(TEMP_XML_FILE_NAME, firstTagInXMLFile))
 	{
		result = false;
	}
	*/

	XMLParserTag * currentTag = firstTagInXMLFile;

	ANNrulesSprite = new RulesClass();

	if(!parseANNRulesTag(currentTag))
	{
		result = false;
	}

	delete firstTagInXMLFile;

	return result;
}




//Top Level
bool parseANNRulesTag(XMLParserTag * currentTag)
{
	bool result = true;

	XMLParserTag * currentTagUpdated = currentTag;
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






#ifdef USE_LRRC


bool parseLRRCRulesXMLFile()
{
	bool result = true;

 	XMLParserTag * firstTagInXMLFile = new XMLParserTag();	//the firstTagInXMLFile object must be initialised here (in XMLrulesClass.cpp scope). if it is initialised in XMLParserClass.cpp else it will be come corrupted,
 	if(!readXMLFile(LRRC_RULES_XML_FILE_NAME, firstTagInXMLFile))
 	{
		result = false;
	}

	/*
	#define TEMP_XML_FILE_NAME "temp.xml"
 	if(!writeXMLFile(TEMP_XML_FILE_NAME, firstTagInXMLFile))
 	{
		result = false;
	}
	*/

	XMLParserTag * currentTag = firstTagInXMLFile;

	LRRCrulesUnitTypeDetails = new RulesClass();
	LRRCrulesUnitCombatDetailsDefenceHead = new RulesClass();
	LRRCrulesUnitCombatDetailsDefenceTorso = new RulesClass();
	LRRCrulesUnitCombatDetailsDefenceShield = new RulesClass();
	LRRCrulesUnitCombatDetailsAttackCloseCombat = new RulesClass();
	LRRCrulesUnitCombatDetailsAttackLongDistance = new RulesClass();
	LRRCrulesBuildingDetails = new RulesClass();
	LRRCrulesTerrainDetails = new RulesClass();
	LRRCrulesUnitTypeCatagories = new RulesClass();
	LRRCrulesMiscellaneous = new RulesClass();
	LRRCrulesSprite = new RulesClass();




	if(!parseLRRCRulesTag(currentTag))
	{
		result = false;
	}

	delete firstTagInXMLFile;


	/*
	RulesClass * currentReferenceToObjectClass;

	currentReferenceToObjectClass = LRRCrulesUnitTypeDetails;
	while(currentReferenceToObjectClass->next != NULL)
	{
		cout << "name = " << currentReferenceToObjectClass->name << endl;
		cout << "stringValue = " << currentReferenceToObjectClass->stringValue << endl;
		cout << "fractionalValue = " << currentReferenceToObjectClass->fractionalValue << endl;
		cout << "attribute4 = " << currentReferenceToObjectClass->attribute4 << endl;
		cout << "attribute5 = " << currentReferenceToObjectClass->attribute5 << endl;
		cout << "attribute6 = " << currentReferenceToObjectClass->attribute6 << endl;
		cout << "attribute7 = " << currentReferenceToObjectClass->attribute7 << endl;
		cout << "attribute8 = " << currentReferenceToObjectClass->attribute8 << endl;
		currentReferenceToObjectClass = currentReferenceToObjectClass->next;
	}

	currentReferenceToObjectClass = LRRCrulesUnitCombatDetailsDefenceHead;
	while(currentReferenceToObjectClass->next != NULL)
	{
		cout << "name = " << currentReferenceToObjectClass->name << endl;
		cout << "stringValue = " << currentReferenceToObjectClass->stringValue << endl;
		cout << "fractionalValue = " << currentReferenceToObjectClass->fractionalValue << endl;
		cout << "attribute4 = " << currentReferenceToObjectClass->attribute4 << endl;
		cout << "attribute5 = " << currentReferenceToObjectClass->attribute5 << endl;
		cout << "attribute6 = " << currentReferenceToObjectClass->attribute6 << endl;
		cout << "attribute7 = " << currentReferenceToObjectClass->attribute7 << endl;
		cout << "attribute8 = " << currentReferenceToObjectClass->attribute8 << endl;
		currentReferenceToObjectClass = currentReferenceToObjectClass->next;
	}

	currentReferenceToObjectClass = LRRCrulesUnitCombatDetailsDefenceTorso;
	while(currentReferenceToObjectClass->next != NULL)
	{
		cout << "name = " << currentReferenceToObjectClass->name << endl;
		cout << "stringValue = " << currentReferenceToObjectClass->stringValue << endl;
		cout << "fractionalValue = " << currentReferenceToObjectClass->fractionalValue << endl;
		cout << "attribute4 = " << currentReferenceToObjectClass->attribute4 << endl;
		cout << "attribute5 = " << currentReferenceToObjectClass->attribute5 << endl;
		cout << "attribute6 = " << currentReferenceToObjectClass->attribute6 << endl;
		cout << "attribute7 = " << currentReferenceToObjectClass->attribute7 << endl;
		cout << "attribute8 = " << currentReferenceToObjectClass->attribute8 << endl;
		currentReferenceToObjectClass = currentReferenceToObjectClass->next;
	}

	currentReferenceToObjectClass = LRRCrulesUnitCombatDetailsDefenceShield;
	while(currentReferenceToObjectClass->next != NULL)
	{
		cout << "name = " << currentReferenceToObjectClass->name << endl;
		cout << "stringValue = " << currentReferenceToObjectClass->stringValue << endl;
		cout << "fractionalValue = " << currentReferenceToObjectClass->fractionalValue << endl;
		cout << "attribute4 = " << currentReferenceToObjectClass->attribute4 << endl;
		cout << "attribute5 = " << currentReferenceToObjectClass->attribute5 << endl;
		cout << "attribute6 = " << currentReferenceToObjectClass->attribute6 << endl;
		cout << "attribute7 = " << currentReferenceToObjectClass->attribute7 << endl;
		cout << "attribute8 = " << currentReferenceToObjectClass->attribute8 << endl;
		currentReferenceToObjectClass = currentReferenceToObjectClass->next;
	}

	currentReferenceToObjectClass = LRRCrulesUnitCombatDetailsAttackCloseCombat;
	while(currentReferenceToObjectClass->next != NULL)
	{
		cout << "name = " << currentReferenceToObjectClass->name << endl;
		cout << "stringValue = " << currentReferenceToObjectClass->stringValue << endl;
		cout << "fractionalValue = " << currentReferenceToObjectClass->fractionalValue << endl;
		cout << "attribute4 = " << currentReferenceToObjectClass->attribute4 << endl;
		cout << "attribute5 = " << currentReferenceToObjectClass->attribute5 << endl;
		cout << "attribute6 = " << currentReferenceToObjectClass->attribute6 << endl;
		cout << "attribute7 = " << currentReferenceToObjectClass->attribute7 << endl;
		cout << "attribute8 = " << currentReferenceToObjectClass->attribute8 << endl;
		currentReferenceToObjectClass = currentReferenceToObjectClass->next;
	}

	currentReferenceToObjectClass = LRRCrulesUnitCombatDetailsAttackLongDistance;
	while(currentReferenceToObjectClass->next != NULL)
	{
		cout << "name = " << currentReferenceToObjectClass->name << endl;
		cout << "stringValue = " << currentReferenceToObjectClass->stringValue << endl;
		cout << "fractionalValue = " << currentReferenceToObjectClass->fractionalValue << endl;
		cout << "attribute4 = " << currentReferenceToObjectClass->attribute4 << endl;
		cout << "attribute5 = " << currentReferenceToObjectClass->attribute5 << endl;
		cout << "attribute6 = " << currentReferenceToObjectClass->attribute6 << endl;
		cout << "attribute7 = " << currentReferenceToObjectClass->attribute7 << endl;
		cout << "attribute8 = " << currentReferenceToObjectClass->attribute8 << endl;
		currentReferenceToObjectClass = currentReferenceToObjectClass->next;
	}

	currentReferenceToObjectClass = LRRCrulesBuildingDetails;
	while(currentReferenceToObjectClass->next != NULL)
	{
		cout << "name = " << currentReferenceToObjectClass->name << endl;
		cout << "stringValue = " << currentReferenceToObjectClass->stringValue << endl;
		cout << "fractionalValue = " << currentReferenceToObjectClass->fractionalValue << endl;
		cout << "attribute4 = " << currentReferenceToObjectClass->attribute4 << endl;
		cout << "attribute5 = " << currentReferenceToObjectClass->attribute5 << endl;
		cout << "attribute6 = " << currentReferenceToObjectClass->attribute6 << endl;
		cout << "attribute7 = " << currentReferenceToObjectClass->attribute7 << endl;
		cout << "attribute8 = " << currentReferenceToObjectClass->attribute8 << endl;
		currentReferenceToObjectClass = currentReferenceToObjectClass->next;
	}


	currentReferenceToObjectClass = LRRCrulesTerrainDetails;
	while(currentReferenceToObjectClass->next != NULL)
	{
		cout << "name = " << currentReferenceToObjectClass->name << endl;
		cout << "stringValue = " << currentReferenceToObjectClass->stringValue << endl;
		cout << "fractionalValue = " << currentReferenceToObjectClass->fractionalValue << endl;
		cout << "attribute4 = " << currentReferenceToObjectClass->attribute4 << endl;
		cout << "attribute5 = " << currentReferenceToObjectClass->attribute5 << endl;
		cout << "attribute6 = " << currentReferenceToObjectClass->attribute6 << endl;
		cout << "attribute7 = " << currentReferenceToObjectClass->attribute7 << endl;
		cout << "attribute8 = " << currentReferenceToObjectClass->attribute8 << endl;
		currentReferenceToObjectClass = currentReferenceToObjectClass->next;
	}


	currentReferenceToObjectClass = LRRCrulesUnitTypeCatagories;
	while(currentReferenceToObjectClass->next != NULL)
	{
		cout << "name = " << currentReferenceToObjectClass->name << endl;
		cout << "stringValue = " << currentReferenceToObjectClass->stringValue << endl;
		cout << "fractionalValue = " << currentReferenceToObjectClass->fractionalValue << endl;
		cout << "attribute4 = " << currentReferenceToObjectClass->attribute4 << endl;
		cout << "attribute5 = " << currentReferenceToObjectClass->attribute5 << endl;
		cout << "attribute6 = " << currentReferenceToObjectClass->attribute6 << endl;
		cout << "attribute7 = " << currentReferenceToObjectClass->attribute7 << endl;
		cout << "attribute8 = " << currentReferenceToObjectClass->attribute8 << endl;
		currentReferenceToObjectClass = currentReferenceToObjectClass->next;
	}


	currentReferenceToObjectClass = LRRCrulesMiscellaneous;
	while(currentReferenceToObjectClass->next != NULL)
	{
		cout << "name = " << currentReferenceToObjectClass->name << endl;
		cout << "stringValue = " << currentReferenceToObjectClass->stringValue << endl;
		cout << "fractionalValue = " << currentReferenceToObjectClass->fractionalValue << endl;
		cout << "attribute4 = " << currentReferenceToObjectClass->attribute4 << endl;
		cout << "attribute5 = " << currentReferenceToObjectClass->attribute5 << endl;
		cout << "attribute6 = " << currentReferenceToObjectClass->attribute6 << endl;
		cout << "attribute7 = " << currentReferenceToObjectClass->attribute7 << endl;
		cout << "attribute8 = " << currentReferenceToObjectClass->attribute8 << endl;
		currentReferenceToObjectClass = currentReferenceToObjectClass->next;
	}


	currentReferenceToObjectClass = LRRCrulesSprite;
	while(currentReferenceToObjectClass->next != NULL)
	{
		cout << "name = " << currentReferenceToObjectClass->name << endl;
		cout << "stringValue = " << currentReferenceToObjectClass->stringValue << endl;
		cout << "fractionalValue = " << currentReferenceToObjectClass->fractionalValue << endl;
		cout << "attribute4 = " << currentReferenceToObjectClass->attribute4 << endl;
		cout << "attribute5 = " << currentReferenceToObjectClass->attribute5 << endl;
		cout << "attribute6 = " << currentReferenceToObjectClass->attribute6 << endl;
		cout << "attribute7 = " << currentReferenceToObjectClass->attribute7 << endl;
		cout << "attribute8 = " << currentReferenceToObjectClass->attribute8 << endl;
		currentReferenceToObjectClass = currentReferenceToObjectClass->next;
	}
	*/

	return result;
}

bool parseLRRCRulesTag(XMLParserTag * currentTag)
{
	bool result = true;

	XMLParserTag * currentTagUpdated = currentTag;
	currentTagUpdated = parseTagDownALevel(currentTagUpdated, RULES_XML_TAG_rules, &result);
	if(result)
	{
		if(!addRulesClassObjectsBasedOnSectionTag(currentTagUpdated, RULES_XML_TAG_unitTypeDetails, LRRCrulesUnitTypeDetails, RULES_XML_TAG_part, 3, RULES_XML_ATTRIBUTE_name, RULES_XML_ATTRIBUTE_partID, RULES_XML_ATTRIBUTE_partIDLen, nullString, nullString, nullString, nullString, nullString))
		{
			result = false;
		}
		currentTagUpdated=currentTagUpdated->nextTag;
		if(!parseTagUnitCombatDetails(currentTagUpdated))
		{
			result = false;
		}
		currentTagUpdated=currentTagUpdated->nextTag;
		if(!addRulesClassObjectsBasedOnSectionTag(currentTagUpdated, RULES_XML_TAG_buildingDetails, LRRCrulesBuildingDetails, RULES_XML_TAG_part, 4, RULES_XML_ATTRIBUTE_name, RULES_XML_ATTRIBUTE_partID, RULES_XML_ATTRIBUTE_partIDLen, RULES_XML_ATTRIBUTE_buildingMod, nullString, nullString, nullString, nullString))
		{
			result = false;
		}
		currentTagUpdated=currentTagUpdated->nextTag;
		if(!addRulesClassObjectsBasedOnSectionTag(currentTagUpdated, RULES_XML_TAG_terrainDefenceDetails, LRRCrulesTerrainDetails, RULES_XML_TAG_part, 3, RULES_XML_ATTRIBUTE_name, RULES_XML_ATTRIBUTE_partID, RULES_XML_ATTRIBUTE_partIDLen, nullString, nullString, nullString, nullString, nullString))
		{
			result = false;
		}
		currentTagUpdated=currentTagUpdated->nextTag;
		if(!addRulesClassObjectsBasedOnSectionTag(currentTagUpdated, RULES_XML_TAG_unitTypeCatagories, LRRCrulesUnitTypeCatagories, RULES_XML_TAG_unitType, 5, RULES_XML_ATTRIBUTE_name, RULES_XML_ATTRIBUTE_stringValue, RULES_XML_ATTRIBUTE_enum, RULES_XML_ATTRIBUTE_maxTravel, RULES_XML_ATTRIBUTE_defenceMod, nullString, nullString, nullString))
		{
			result = false;
		}
		currentTagUpdated=currentTagUpdated->nextTag;
		if(!addRulesClassObjectsBasedOnSectionTag(currentTagUpdated, RULES_XML_TAG_miscellaneous, LRRCrulesMiscellaneous, RULES_XML_TAG_miscellaneousItem, 3, RULES_XML_ATTRIBUTE_name, RULES_XML_ATTRIBUTE_stringValue, RULES_XML_ATTRIBUTE_fractionalValue, nullString, nullString, nullString, nullString, nullString))
		{
			result = false;
		}
		currentTagUpdated=currentTagUpdated->nextTag;
		if(!addRulesClassObjectsBasedOnSectionTag(currentTagUpdated, RULES_XML_TAG_sprite, LRRCrulesSprite, RULES_XML_TAG_miscellaneousItem, 3, RULES_XML_ATTRIBUTE_name, RULES_XML_ATTRIBUTE_stringValue, RULES_XML_ATTRIBUTE_fractionalValue, nullString, nullString, nullString, nullString, nullString))
		{
			result = false;
		}
	}

	return result;
}




bool parseTagUnitCombatDetails(XMLParserTag * currentTag)
{
	bool result = true;

	XMLParserTag * currentTagUpdated = currentTag;
	currentTagUpdated = parseTagDownALevel(currentTagUpdated, RULES_XML_TAG_unitCombatDetails, &result);
	if(result)
	{
		if(!parseTagArmour(currentTagUpdated))
		{
			result = false;
		}
		currentTagUpdated=currentTagUpdated->nextTag;
		if(!parseTagWeapons(currentTagUpdated))
		{
			result = false;
		}
	}

	return result;
}

bool parseTagArmour(XMLParserTag * currentTag)
{
	bool result = true;

	XMLParserTag * currentTagUpdated = currentTag;
	currentTagUpdated = parseTagDownALevel(currentTagUpdated, RULES_XML_TAG_armour, &result);
	if(result)
	{
		if(!parseTagHead(currentTagUpdated))
		{
			result = false;
		}
		currentTagUpdated=currentTagUpdated->nextTag;
		if(!parseTagTorso(currentTagUpdated))
		{
			result = false;
		}
		currentTagUpdated=currentTagUpdated->nextTag;
		if(!parseTagShield(currentTagUpdated))
		{
			result = false;
		}
	}

	return result;
}

bool parseTagHead(XMLParserTag * currentTag)
{
	bool result = true;

	addRulesClassObjectsBasedOnSectionTag(currentTag, RULES_XML_TAG_head, LRRCrulesUnitCombatDetailsDefenceHead, RULES_XML_TAG_part, 4, RULES_XML_ATTRIBUTE_name, RULES_XML_ATTRIBUTE_partID, RULES_XML_ATTRIBUTE_partIDLen, RULES_XML_ATTRIBUTE_defenceMod, nullString, nullString, nullString, nullString);

	return result;
}

bool parseTagTorso(XMLParserTag * currentTag)
{
	bool result = true;

	addRulesClassObjectsBasedOnSectionTag(currentTag, RULES_XML_TAG_torso, LRRCrulesUnitCombatDetailsDefenceTorso, RULES_XML_TAG_part, 4, RULES_XML_ATTRIBUTE_name, RULES_XML_ATTRIBUTE_partID, RULES_XML_ATTRIBUTE_partIDLen, RULES_XML_ATTRIBUTE_defenceMod, nullString, nullString, nullString, nullString);

	return result;
}

bool parseTagShield(XMLParserTag * currentTag)
{
	bool result = true;

	addRulesClassObjectsBasedOnSectionTag(currentTag, RULES_XML_TAG_shield, LRRCrulesUnitCombatDetailsDefenceShield, RULES_XML_TAG_part, 4, RULES_XML_ATTRIBUTE_name, RULES_XML_ATTRIBUTE_partID, RULES_XML_ATTRIBUTE_partIDLen, RULES_XML_ATTRIBUTE_defenceMod, nullString, nullString, nullString, nullString);

	return result;
}


bool parseTagWeapons(XMLParserTag * currentTag)
{
	bool result = true;

	XMLParserTag * currentTagUpdated = currentTag;
	currentTagUpdated = parseTagDownALevel(currentTagUpdated, RULES_XML_TAG_weapons, &result);
	if(result)
	{
		if(!parseTagCloseCombat(currentTagUpdated))
		{
			result = false;
		}
		currentTagUpdated=currentTagUpdated->nextTag;
		if(!parseTagLongDistanceCombat(currentTagUpdated))
		{
			result = false;
		}
	}

	return result;
}

bool parseTagCloseCombat(XMLParserTag * currentTag)
{
	bool result = true;

	addRulesClassObjectsBasedOnSectionTag(currentTag, RULES_XML_TAG_closeCombat, LRRCrulesUnitCombatDetailsAttackCloseCombat, RULES_XML_TAG_part, 6, RULES_XML_ATTRIBUTE_name, RULES_XML_ATTRIBUTE_partID, RULES_XML_ATTRIBUTE_partIDLen, RULES_XML_ATTRIBUTE_closeCombatAttackMod, RULES_XML_ATTRIBUTE_mountedAttackBonus, RULES_XML_ATTRIBUTE_attackBonusAgainstMounted, nullString, nullString);

	return result;
}

bool parseTagLongDistanceCombat(XMLParserTag * currentTag)
{
	bool result = true;

	addRulesClassObjectsBasedOnSectionTag(currentTag, RULES_XML_TAG_longDistance, LRRCrulesUnitCombatDetailsAttackLongDistance, RULES_XML_TAG_part, 5, RULES_XML_ATTRIBUTE_name, RULES_XML_ATTRIBUTE_partID, RULES_XML_ATTRIBUTE_partIDLen, RULES_XML_ATTRIBUTE_longDistanceAttackMod, RULES_XML_ATTRIBUTE_longDistanceRange, nullString, nullString, nullString);

	return result;
}

#endif


bool addRulesClassObjectsBasedOnSectionTag(XMLParserTag * currentTag, string sectionTagName, RulesClass * firstReferenceToObjectClass, string tagName, int numberOfAttributes, string attribute1Name, string attribute2Name, string attribute3Name, string attribute4Name, string attribute5Name, string attribute6Name, string attribute7Name, string attribute8Name)
{
	bool result = true;

	if(currentTag->name == sectionTagName)
	{
		XMLParserTag * currentLowerLevelTag = currentTag->firstLowerLevelTag;

		RulesClass * currentReferenceToObjectClass = firstReferenceToObjectClass;

		while(currentLowerLevelTag->nextTag != NULL)
		{
			if(!addRulesClassObjectBasedOnTag(currentLowerLevelTag, currentReferenceToObjectClass, tagName, numberOfAttributes, attribute1Name, attribute2Name, attribute3Name, attribute4Name, attribute5Name, attribute6Name, attribute7Name, attribute8Name))
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


bool addRulesClassObjectBasedOnTag(XMLParserTag * currentTag, RulesClass * currentReferenceToObjectClass, string tagName, int numberOfAttributes, string attribute1Name, string attribute2Name, string attribute3Name, string attribute4Name, string attribute5Name, string attribute6Name, string attribute7Name, string attribute8Name)
{
	bool result = true;
	//currentReferenceToObjectClass->tagName = currentTag->name;

	XMLParserAttribute * currentAttribute = currentTag->firstAttribute;

	int attributeNumber = 1;
	while(currentAttribute->nextAttribute != NULL)
	{
		if(attributeNumber == 1)
		{
			if(currentAttribute->name != attribute1Name)
			{
				result = false;
				cout << "parse error; currentAttribute->name != attribute1Name.  currentAttribute->name = " <<  currentAttribute->name << ". attribute1Name = " << attribute1Name << endl;
			}
			else
			{
				currentReferenceToObjectClass->name = currentAttribute->value;
			}
		}
		else if(attributeNumber == 2)
		{
			if(currentAttribute->name != attribute2Name)
			{
				result = false;
				cout << "parse error; currentAttribute->name != attribute2Name.  currentAttribute->name = " <<  currentAttribute->name << ". attribute2Name = " << attribute2Name << endl;
			}
			else
			{
				currentReferenceToObjectClass->stringValue = currentAttribute->value;
			}
		}
		else if(attributeNumber == 3)
		{
			if(currentAttribute->name != attribute3Name)
			{
				result = false;
				cout << "parse error; currentAttribute->name != attribute3Name.  currentAttribute->name = " <<  currentAttribute->name << ". attribute3Name = " << attribute3Name << endl;
			}
			else
			{
				currentReferenceToObjectClass->fractionalValue = atof(currentAttribute->value.c_str());
			}
		}
		else if(attributeNumber == 4)
		{
			if(currentAttribute->name != attribute4Name)
			{
				result = false;
				cout << "parse error; currentAttribute->name != attribute4Name.  currentAttribute->name = " <<  currentAttribute->name << ". attribute4Name = " << attribute4Name << endl;
			}
			else
			{
				currentReferenceToObjectClass->attribute4 = int(atof(currentAttribute->value.c_str()));
			}
		}
		else if(attributeNumber == 5)
		{
			if(currentAttribute->name != attribute5Name)
			{
				result = false;
				cout << "parse error; currentAttribute->name != attribute5Name.  currentAttribute->name = " <<  currentAttribute->name << ". attribute5Name = " << attribute5Name << endl;
			}
			else
			{
				currentReferenceToObjectClass->attribute5 = int(atof(currentAttribute->value.c_str()));
			}
		}
		else if(attributeNumber == 6)
		{
			if(currentAttribute->name != attribute6Name)
			{
				result = false;
				cout << "parse error; currentAttribute->name != attribute6Name.  currentAttribute->name = " <<  currentAttribute->name << ". attribute6Name = " << attribute6Name << endl;
			}
			else
			{
				currentReferenceToObjectClass->attribute6 = int(atof(currentAttribute->value.c_str()));
			}
		}
		else if(attributeNumber == 7)
		{
			if(currentAttribute->name != attribute7Name)
			{
				result = false;
				cout << "parse error; currentAttribute->name != attribute7Name.  currentAttribute->name = " <<  currentAttribute->name << ". attribute7Name = " << attribute7Name << endl;
			}
			else
			{
				currentReferenceToObjectClass->attribute7 = int(atof(currentAttribute->value.c_str()));
			}
		}
		else if(attributeNumber == 8)
		{
			if(currentAttribute->name != attribute8Name)
			{
				result = false;
				cout << "parse error; currentAttribute->name != attribute8Name.  currentAttribute->name = " <<  currentAttribute->name << ". attribute8Name = " << attribute8Name << endl;
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









/*******************************************************************************
 *
 * File Name: XMLrulesClass.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: XML Functions
 * Project Version: 3a8a 14-June-2012
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
#include "XMLParserClass.h"


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

	/*
	int defenceMod;

	int closeCombatAttackMod;
	int mountedAttackBonus;

	int longDistanceAttackMod;
	int longDistanceRange;
	*/

	RulesClass * next;
};
//there really should be child classes of RulesClass called LRRCrulesUnitTypeDetails, unitCombatDetailsAttack, and unitCombatDetailsDefence that inherit rulesObject and include unique parameters


/*
struct XMLTagAttributes
{
	int fractionalValue;
	int numberOfPartsInUnit;

	int defenceMod;

	int closeCombatAttackMod;
	int mountedAttackBonus;

	int longDistanceAttackMod;
	int longDistanceRange;
};
typdef XMLTagAttributes objectAttributes
*/

//High Level

#ifdef USE_CS
bool parseCSRulesXMLFile();
	bool parseCSRulesTag(XMLParserTag * currentTag);
#endif

#ifdef USE_GIA
bool parseGIARulesXMLFile();
	bool parseGIARulesTag(XMLParserTag * currentTag);
#endif

#ifdef USE_OR
bool parseORRulesXMLFile();
	bool parseORRulesTag(XMLParserTag * currentTag);
#endif

bool parseANNRulesXMLFile();
	bool parseANNRulesTag(XMLParserTag * currentTag);

#ifdef USE_LRRC
bool parseLRRCRulesXMLFile();
#endif
	#ifdef USE_LRRC
	bool parseLRRCRulesTag(XMLParserTag * currentTag);
		bool parseTagUnitCombatDetails(XMLParserTag * currentTag);
			bool parseTagArmour(XMLParserTag * currentTag);
				bool parseTagHead(XMLParserTag * currentTag);
				bool parseTagTorso(XMLParserTag * currentTag);
				bool parseTagShield(XMLParserTag * currentTag);
			bool parseTagWeapons(XMLParserTag * currentTag);
				bool parseTagCloseCombat(XMLParserTag * currentTag);
				bool parseTagLongDistanceCombat(XMLParserTag * currentTag);
	#endif


bool addRulesClassObjectsBasedOnSectionTag(XMLParserTag * currentTag, string sectionTagName, RulesClass * firstReferenceToObjectClass, string tagName, int numberOfAttributes, string attribute1Name, string attribute2Name, string attribute3Name, string attribute4Name, string attribute5Name, string attribute6Name, string attribute7Name, string attribute8Name);
bool addRulesClassObjectBasedOnTag(XMLParserTag * currentTag, RulesClass * currentReferenceToObjectClass, string tagName, int numberOfAttributes, string attribute1Name, string attribute2Name, string attribute3Name, string attribute4Name, string attribute5Name, string attribute6Name, string attribute7Name, string attribute8Name);


//bool parseSectionTagAndAddObjectsWithAttributes(RulesClass * firstReferenceToObjectClass, string parentTagName, int numberOfAttributes, string attribute1Name, string attribute2Name, string attribute3Name, string attribute4Name, string attribute5Name, string attribute6Name, string attribute7Name, string attribute8Name);
//bool parseTagAndAddObjectWithAttributes(RulesClass * firstReferenceToObjectClass, int numberOfAttributes, string attribute1Name, string attribute2Name, string attribute3Name, string attribute4Name, string attribute5Name, string attribute6Name, string attribute7Name, string attribute8Name);

#ifdef USE_LRRC
extern RulesClass * LRRCrulesUnitTypeDetails;
extern RulesClass * LRRCrulesUnitCombatDetailsDefenceHead;
extern RulesClass * LRRCrulesUnitCombatDetailsDefenceTorso;
extern RulesClass * LRRCrulesUnitCombatDetailsDefenceShield;
extern RulesClass * LRRCrulesUnitCombatDetailsAttackCloseCombat;
extern RulesClass * LRRCrulesUnitCombatDetailsAttackLongDistance;
extern RulesClass * LRRCrulesBuildingDetails;
extern RulesClass * LRRCrulesTerrainDetails;
extern RulesClass * LRRCrulesUnitTypeCatagories;
extern RulesClass * LRRCrulesMiscellaneous;
extern RulesClass * LRRCrulesSprite;
#endif
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

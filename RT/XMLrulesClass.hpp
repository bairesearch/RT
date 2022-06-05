 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: XMLrulesClass.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: XML Functions
 * Project Version: 3q1a 05-June-2022
 * /
 *******************************************************************************/


#ifndef HEADER_XML_RULES_CLASS
#define HEADER_XML_RULES_CLASS

#include "SHAREDglobalDefs.hpp"
#include "XMLparserClass.hpp"
#include "SHAREDvars.hpp"

#define ANN_RULES_XML_FILE_NAME "ANNrules.xml"
#define CS_RULES_XML_FILE_NAME "CSrules.xml"
#define ATOR_RULES_XML_FILE_NAME "ATORrules.xml"
#define GIA_RULES_XML_FILE_NAME "GIArules.xml"
#define GIA_SYN_REL_TRANSLATOR_RULES_XML_FILE_NAME "GIAsynRelTranslatorRules.xml"
#define GIA_POS_REL_TRANSLATOR_RULES_XML_FILE_NAME "GIAposRelTranslatorRules.xml"
#define NLC_RULES_XML_FILE_NAME "NLCrules.xml"

#define RULES_XML_TAG_rules ((string)"rules")
#define RULES_XML_TAG_miscellaneousItem ((string)"miscellaneousItem")
#define RULES_XML_TAG_sprite ((string)"sprite")
#ifdef USE_CS
#define RULES_XML_TAG_draw ((string)"draw")
#endif
#ifdef USE_GIA
#define RULES_XML_TAG_draw ((string)"draw")
#endif
#ifdef USE_ATOR
#define RULES_XML_TAG_objectRecognition ((string)"objectRecognition")
#endif

#define RULES_XML_ATTRIBUTE_name ((string)"name")
#define RULES_XML_ATTRIBUTE_stringValue ((string)"stringValue")
#define RULES_XML_ATTRIBUTE_fractionalValue ((string)"fractionalValue")

class XMLrulesClass
{
private:
	/*There are currently no private attributes of this class*/
public:

	XMLrulesClass(void); // constructor
	~XMLrulesClass();	// and destructor.

	string name;	//attribute1;

	string stringValue;	//attribute2;
	double fractionalValue;
	int attribute4;
	int attribute5;
	int attribute6;
	int attribute7;
	int attribute8;

	XMLrulesClass* next;
};

//High Level

class XMLrulesClassClass
{
	private: XMLparserClassClass XMLparserClass;
	private: SHAREDvarsClass SHAREDvars;
	
	#ifdef USE_NLC
	public: bool parseNLCrulesXMLfile();
	#endif

	#ifdef USE_GIA
	public: bool parseGIArulesXMLfile();
		private: bool parseGIARulesTag(XMLparserTag* currentTag);
	#endif

	#ifdef USE_CS
	public: bool parseCSrulesXMLfile();
		private: bool parseCSRulesTag(XMLparserTag* currentTag);
	#endif

	#ifdef USE_ATOR
	public: bool parseATORrulesXMLfile();
		private: bool parseATORrulesTag(XMLparserTag* currentTag);
	#endif

	#ifdef USE_ANN
	public: bool parseANNrulesXMLfile();
		private: bool parseANNrulesTag(XMLparserTag* currentTag);
	#endif

	public: bool addRulesClassObjectsBasedOnSectionTag(XMLparserTag* currentTag, const string sectionTagName, XMLrulesClass* firstReferenceToObjectClass, const string tagName, const int numberOfAttributes, const string attributeName1, const string attributeName2, const string attributeName3, const string attributeName4, const string attributeName5, const string attributeName6, const string attributeName7, const string attributeName8);
	private: bool addRulesClassObjectBasedOnTag(XMLparserTag* currentTag, XMLrulesClass* currentReferenceToObjectClass, const string tagName, const int numberOfAttributes, const string attributeName1, const string attributeName2, const string attributeName3, const string attributeName4, const string attributeName5, const string attributeName6, const string attributeName7, const string attributeName8);
};

extern XMLrulesClass* ANNrulesSprite;	//common sprite xml file is ANNrules.xml
#ifdef USE_CS
extern XMLrulesClass* CSrulesSprite;
extern XMLrulesClass* CSrulesDraw;
extern XMLparserTag* CSfirstTagInXMLfile;
#endif
#ifdef USE_GIA
extern XMLrulesClass* GIArulesSprite;
extern XMLrulesClass* GIArulesDraw;
extern XMLparserTag* GIAfirstTagInXMLfile;
extern XMLparserTag* GIAsynRelTranslatorFirstTagInXMLfile;
extern XMLparserTag* GIAposRelTranslatorFirstTagInXMLfile;
#endif
#ifdef USE_ATOR
extern XMLrulesClass* ATORrulesObjectRecognition;
#endif
#ifdef USE_NLC
extern XMLparserTag* NLCfirstTagInXMLfile;
#endif

#endif

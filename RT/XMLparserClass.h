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
 * File Name: XMLparserClass.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: XML Functions
 * Project Version: 3i19c 15-December-2016
 *
 *******************************************************************************/


#ifndef HEADER_XML_PARSER_CLASS
#define HEADER_XML_PARSER_CLASS

#include "SHAREDglobalDefs.h"


#define XML_WRITE_STANDARD_XML_HEADER

//#define XML_PARSER_DISPLAY_COMMENTS_WHEN_PARSING

//#define XML_DEBUG

#ifdef USE_GIA
	/*yet untested without GIA;
	#define XML_PARSER_DO_NOT_ALLOW_CHAR_TAG_END_SLASH_INSIDE_ATTRIBUTE_VALUE
	#define XML_PARSER_DO_NOT_ALLOW_TABS_OR_NEWLINES_WITHIN_TAG_VALUE
	*/
#else
	#define XML_PARSER_DO_NOT_ALLOW_SUBTAGS_WITH_SAME_NAME_AS_PARENT_TAG		//new 5 April 2012 - to support Stanford NLP Core XML files with embedded <coreference><coreference> tags, where the first of these should actually be "<coreferences>"
	#define XML_PARSER_DO_NOT_ALLOW_CHAR_TAG_END_SLASH_WITHOUT_PRECEEDING_SPACE	//new 5 April 2012 - to support Stanford NLP Core XML files with end tag immediately following tag name, without a preceeding space eg <basic-dependencies/>
	#define XML_PARSER_DO_NOT_ALLOW_CHAR_TAG_END_SLASH_INSIDE_ATTRIBUTE_VALUE
	#define XML_PARSER_DO_NOT_ALLOW_TABS_OR_NEWLINES_WITHIN_TAG_VALUE
	#define XML_PARSER_DO_NOT_ALLOW_TAG_VALUE_TO_BE_DEFINED_AFTER_SUBTAG		//added 3i16a for Doxygen support, eg " *" in "<type><ref refid="classGIArelation" kindref="compound">GIArelation</ref> *</type>"
#endif

#define XML_FILE_MAX_SIZE (100000000)		//100MB




class XMLparserAttribute
{
private:
	/*There are currently no private attributes of this class*/
public:

	XMLparserAttribute(void); // constructor
	~XMLparserAttribute();	// and destructor.

	string name;
	string value;

	XMLparserAttribute* nextAttribute;


};





class XMLparserTag
{
private:
	/*There are currently no private attributes of this class*/
public:

	XMLparserTag(void); // constructor
	~XMLparserTag();	// and destructor.

	string name;
	string value;

	XMLparserTag* nextTag;
	XMLparserTag* firstLowerLevelTag;

	XMLparserAttribute* firstAttribute;
	XMLparserAttribute* currentAttribute;	//temporary variable used for attribute list creation

};


XMLparserTag* parseTagDownALevel(XMLparserTag* currentTag, string sectionTagName, bool* result);

bool readXMLfile(string xmlFileName, XMLparserTag* firstTagInXMLfile);
bool parseTagOpen(ifstream* parseFileObject, XMLparserTag* currentTag, string parentTagName, bool isSubTag, int treeLayer);
	bool parseTagName(ifstream* parseFileObject, XMLparserTag* currentTag, string parentTagName, bool isSubTag, int treeLayer);
		bool parseTagAttributeName(ifstream* parseFileObject, XMLparserTag* currentTag, string parentTagName, bool isSubTag, int treeLayer);
			bool parseTagAttributeValue(ifstream* parseFileObject, XMLparserTag* currentTag, string parentTagName, bool isSubTag, int treeLayer);
		bool parseTagValueAssumingExistenceOfSubtagsAndClose(ifstream* parseFileObject, XMLparserTag* currentTag, int treeLayer);
		bool parseTagComment(ifstream* parseFileObject, char type);
		bool processTagClose(ifstream* parseFileObject, XMLparserTag** currentTag, string parentTagName, bool isSubTag, int treeLayer, bool endTagFound, bool parsingAttributeName, string tagName);
		XMLparserTag* createNewTag(XMLparserTag* currentTag);

//Low Level
bool isBlankChar(ifstream* parseFileObject, char c);
bool isBlankCharTabOrNewLine(ifstream* parseFileObject, char c);
void throwGenericXMLParseError();
bool getAttribute(XMLparserTag* tag, string attributeName, string* attributeValueFound);
XMLparserAttribute* createNewAttribute(XMLparserAttribute* currentAttribute);

bool writeXMLfileInefficient(string xmlFileName, XMLparserTag* firstTagInXMLfile);
void writeXMLHeader(ofstream* writeFileObject);	//not used?
bool writeXMLfile(string xmlFileName, XMLparserTag* firstTagInXMLfile);
	bool addTagLayerToFileObject(XMLparserTag* firstTagInCurrentLayer, ofstream* writeFileObject, int treeLayer);
		void incrementLineAndAddTabsToFileObject(ofstream* writeFileObject, int treeLayer);
		void addTabsToFileObject(ofstream* writeFileObject, int treeLayer);
	bool addTagLayerToByteArrayInefficient(XMLparserTag* firstTagInCurrentLayer, char* XMLfileByteArray, long* XMLfileByteArrayCurrentPosition, int treeLayer);
		void incrementLineAndAddTabsToByteArrayInefficient(char* XMLfileByteArray, long* XMLfileByteArrayCurrentPosition, int treeLayer);
		void addTabsToByteArrayInefficient(char* XMLfileByteArray, long* XMLfileByteArrayCurrentPosition, int treeLayer);
		void writeStringToByteArrayInefficient(string s, char* XMLfileByteArray, long* XMLfileByteArrayCurrentPosition);

#endif

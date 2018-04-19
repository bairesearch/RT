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
 * File Name: XMLparserClass.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: XML Functions
 * Project Version: 3m13d 22-February-2018
 * /
 *******************************************************************************/


#ifndef HEADER_XML_PARSER_CLASS
#define HEADER_XML_PARSER_CLASS

#include "SHAREDglobalDefs.hpp"
#include "SHAREDvars.hpp"	//required for writeByteArrayToFile/writeStringToFileObject

#define CHAR_TAG_OPEN '<'
#define CHAR_TAG_OPEN_STR "<"
#define CHAR_TAG_CLOSE '>'
#define CHAR_TAG_CLOSE_STR ">"
#define CHAR_TAG_END '/'
#define CHAR_TAG_END_STR "/"
#define CHAR_TAG_XML_DEF '$'
#define STRING_TAG_COMMENT_OPEN "--"
#define STRING_TAG_COMMENT_CLOSE "--"
#define STRING_TAG_XML_DEF_FULL "?xml version=\"1.0\" encoding=\"UTF-8\"?"
#define CHAR_TAG_ATTRIBUTE_VAL_OPEN '"'
#define CHAR_TAG_ATTRIBUTE_VAL_OPEN_STR "\""
#define CHAR_TAG_ATTRIBUTE_VAL_CLOSE '"'
#define CHAR_TAG_ATTRIBUTE_VAL_CLOSE_STR "\""
#define CHAR_TAG_ATTRIBUTE_VAL_EQUALS '='
#define CHAR_TAG_ATTRIBUTE_VAL_EQUALS_STR "="


#define XML_WRITE_STANDARD_XML_HEADER

//#define XML_PARSER_DISPLAY_COMMENTS_WHEN_PARSING

#define XML_DEBUG_LINECOUNT
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

	#ifdef XML_DEBUG_LINECOUNT
	int charCount;
	int lineCount;
	#endif
	
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
	
	#ifdef XML_DEBUG_LINECOUNT
	int charCount;
	int lineCount;
	#endif
	
	XMLparserAttribute* firstAttribute;
	XMLparserAttribute* currentAttribute;	//temporary variable used for attribute list creation

};


class XMLparserClassClass
{
	private: SHAREDvarsClass SHAREDvars;
	public: XMLparserTag* parseTagDownALevel(XMLparserTag* currentTag, const string sectionTagName, bool* result);

	public: bool readXMLfile(const string xmlFileName, XMLparserTag* firstTagInXMLfile);
	private: bool parseTagOpen(ifstream* parseFileObject, XMLparserTag* currentTag, const string parentTagName, const bool isSubTag, int treeLayer);
		private: bool parseTagName(ifstream* parseFileObject, XMLparserTag* currentTag, const string parentTagName, const bool isSubTag, int treeLayer);
			private: bool parseTagAttributeName(ifstream* parseFileObject, XMLparserTag* currentTag, const string parentTagName, const bool isSubTag, int treeLayer);
				private: bool parseTagAttributeValue(ifstream* parseFileObject, XMLparserTag* currentTag, const string parentTagName, const bool isSubTag, const int treeLayer);
			private: bool parseTagValueAssumingExistenceOfSubtagsAndClose(ifstream* parseFileObject, XMLparserTag* currentTag, int treeLayer);
			private: bool parseTagComment(ifstream* parseFileObject, const char type);
			private: bool processTagClose(ifstream* parseFileObject, XMLparserTag** currentTag, const string parentTagName, const bool isSubTag, int treeLayer, const bool endTagFound, const bool parsingAttributeName, const string tagName);
			private: XMLparserTag* createNewTag(XMLparserTag* currentTag);

//Low Level
	private: bool isBlankChar(const ifstream* parseFileObject, const char c);
	private: bool isBlankCharTabOrNewLine(const ifstream* parseFileObject, const char c);
	private: void throwGenericXMLParseError();
	public: bool getAttribute(XMLparserTag* tag, const string attributeName, string* attributeValueFound);
	public: XMLparserAttribute* createNewAttribute(XMLparserAttribute* currentAttribute);

	private: bool writeXMLfileInefficient(const string xmlFileName, const XMLparserTag* firstTagInXMLfile);
	private: void writeXMLHeader(string* writeFileString);	//not used?
	public: bool writeXMLfile(const string xmlFileName, const XMLparserTag* firstTagInXMLfile);
		public: bool addTagLayerToFileObject(const XMLparserTag* firstTagInCurrentLayer, string* writeFileString, const int treeLayer);
			private: void incrementLineAndAddTabsToFileObject(string* writeFileString, const int treeLayer);
			private: void addTabsToFileObject(string* writeFileString, const int treeLayer);
		private: bool addTagLayerToByteArrayInefficient(const XMLparserTag* firstTagInCurrentLayer, char* XMLfileByteArray, long* XMLfileByteArrayCurrentPosition, const int treeLayer);
			private: void incrementLineAndAddTabsToByteArrayInefficient(char* XMLfileByteArray, long* XMLfileByteArrayCurrentPosition, const int treeLayer);
			private: void addTabsToByteArrayInefficient(char* XMLfileByteArray, long* XMLfileByteArrayCurrentPosition, const int treeLayer);
			private: void writeStringToByteArrayInefficient(string s, char* XMLfileByteArray, long* XMLfileByteArrayCurrentPosition);
};

#endif

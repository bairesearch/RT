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
 * File Name: XMLParserClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: XML Functions
 * Project Version: 3a12a 31-July-2012
 *
 *******************************************************************************/




#include "XMLParserClass.h"



#define XML_FILE_NAME "rules.xml"


#define CHAR_TAG_OPEN '<'
#define CHAR_TAG_OPEN_STR "<"
#define CHAR_TAG_CLOSE '>'
#define CHAR_TAG_CLOSE_STR ">"
#define CHAR_TAG_END '/'
#define CHAR_TAG_END_STR "/"
#define CHAR_TAG_XML_DEF '$'
#define CHAR_EXCLAMATION '!'
#define CHAR_QUESTIONMARK '?'
#define STRING_TAG_COMMENT_OPEN "--"
#define STRING_TAG_COMMENT_CLOSE "--"
#define STRING_TAG_XML_DEF_FULL "?xml version=\"1.0\" encoding=\"UTF-8\"?"
#define CHAR_TAG_ATTRIBUTE_VAL_OPEN '"'
#define CHAR_TAG_ATTRIBUTE_VAL_OPEN_STR "\""
#define CHAR_TAG_ATTRIBUTE_VAL_CLOSE '"'
#define CHAR_TAG_ATTRIBUTE_VAL_CLOSE_STR "\""
#define CHAR_TAG_ATTRIBUTE_VAL_EQUALS '='
#define CHAR_TAG_ATTRIBUTE_VAL_EQUALS_STR "="


static int charCount;
static int lineCount;

/*
string tagName;
string attributeName;
string attributeValue;
string tagValue;
*/

XMLParserAttribute::XMLParserAttribute(void)
{
	name = "";
	value = "";

	nextAttribute = NULL;
}

XMLParserAttribute::~XMLParserAttribute()
{
	//cout << "delete attribute = " << name << ": " << value << endl;

	if(nextAttribute != NULL)
	{
		delete nextAttribute;
	}

}




XMLParserTag::XMLParserTag(void)
{
	name = "";
	value = "";

	nextTag = NULL;
	firstLowerLevelTag = NULL;

	firstAttribute = new XMLParserAttribute();
	currentAttribute = firstAttribute;
}

XMLParserTag::~XMLParserTag()
{

	//cout << "delete tag = " << name << ": " << value << endl;
	//currentAttribute = NULL;	
	if(firstAttribute != NULL)
	{
		//cout << "firstAttribute->name = " << firstAttribute->name << endl;
		delete firstAttribute;	//this causes crash for some reason... (coincidental memory allocation?)
	}	
	if(firstLowerLevelTag != NULL)
	{
		//cout << "firstLowerLevelTag->name = " << firstLowerLevelTag->name << endl;
		delete firstLowerLevelTag;
	}
	if(nextTag != NULL)
	{
		delete nextTag;
	}

}


XMLParserTag * parseTagDownALevel(XMLParserTag * currentTag, string sectionTagName, bool * result)
{
	*result = true;

	XMLParserTag * updatedCurrentTag;

	if(currentTag->name != sectionTagName)
	{
		*result = false;
		cout << "parse error; lower level sectionTagName expected = " <<  sectionTagName << ". section tag name found currentTag->name = " << currentTag->name << endl;
		updatedCurrentTag = currentTag;
	}
	else
	{
		//cout << "parseTagDownALevel() " << sectionTagName << endl;
		//cout << "currentTag->value " << currentTag->value << endl;
		if(currentTag->firstLowerLevelTag != NULL)
		{
			//cout << "currentTag->firstLowerLevelTag->value " << currentTag->firstLowerLevelTag->value << endl;
			updatedCurrentTag = currentTag->firstLowerLevelTag;
		}
		else
		{
			updatedCurrentTag = NULL;
		}
	}

	return updatedCurrentTag;

}



bool writeXMLFileInefficient(string xmlFileName, XMLParserTag * firstTagInXMLFile)
{
	bool result = true;

	charCount = 0;		//this variable needs to start being used
	lineCount = 1;

	long XMLFileByteArrayCurrentPosition = 0;
	long XMLFileByteArraySize = XML_FILE_MAX_SIZE;
	char * XMLFileByteArray = new char[XMLFileByteArraySize];

	if(!addTagLayerToByteArrayInefficient(firstTagInXMLFile, XMLFileByteArray, &XMLFileByteArrayCurrentPosition, 0))
	{
		result = false;
	}

	XMLFileByteArray[XMLFileByteArrayCurrentPosition] = CHAR_NEWLINE;	//need to add a new line onto the end of the file
	XMLFileByteArrayCurrentPosition++;

	writeByteArrayToFile(xmlFileName.c_str(), XMLFileByteArray, XMLFileByteArrayCurrentPosition);

	delete XMLFileByteArray;

	return result;
}


void writeXMLHeader(ofstream * writeFileObject)
{
	string headerString = "";
	headerString = headerString + "<" + STRING_TAG_XML_DEF_FULL + ">";
	for(int i = 0; i<headerString.length(); i++)
	{
		writeFileObject->put(headerString[i]);
	}
}


bool writeXMLFile(string xmlFileName, XMLParserTag * firstTagInXMLFile)
{
	bool result = true;

	ofstream writeFileObject(xmlFileName.c_str());

	#ifdef XML_WRITE_STANDARD_XML_HEADER
	writeXMLHeader(&writeFileObject);
	#endif

	if(!addTagLayerToFileObject(firstTagInXMLFile, &writeFileObject, 0))
	{
		result = false;
	}

	//Added by RBB 30 August 2009 - required for Windows SW to re-read xml files
	writeFileObject.put(CHAR_NEWLINE); //(s.cStr())[i]

	writeFileObject.close();

	return result;
}



bool addTagLayerToFileObject(XMLParserTag * firstTagInCurrentLayer, ofstream * writeFileObject, int treeLayer)
{
	bool result = true;

	XMLParserTag * currentTag = firstTagInCurrentLayer;

	while(currentTag->nextTag != NULL)
	{

		bool tagHasAttributes = false;
		bool tagHasValue = false;
		bool tagHasLowerLevelTags = false;
		if(currentTag->firstAttribute->nextAttribute != NULL)
		{//tag has attributes
			tagHasAttributes = true;
		}
		if(currentTag->value != "")
		{//tag has value
			tagHasValue = true;
		}
		if(currentTag->firstLowerLevelTag != NULL)
		{//tag has lower level tags
			tagHasLowerLevelTags = true;
		}

		//cout << "h2" << endl;
		incrementLineAndAddTabsToFileObject(writeFileObject, treeLayer);
		string tagOpeningString = CHAR_TAG_OPEN_STR + currentTag->name;
		writeStringToFileObject(tagOpeningString, writeFileObject);
		if(tagHasAttributes)
		{
			XMLParserAttribute * currentAttribute = currentTag->firstAttribute;
			while(currentAttribute->nextAttribute != NULL)
			{
				string attributeString = " " + currentAttribute->name + CHAR_TAG_ATTRIBUTE_VAL_EQUALS_STR + CHAR_TAG_ATTRIBUTE_VAL_OPEN_STR + currentAttribute->value + CHAR_TAG_ATTRIBUTE_VAL_CLOSE_STR;
				writeStringToFileObject(attributeString, writeFileObject);

				currentAttribute = currentAttribute->nextAttribute;
				//cout << "hereAA" << endl;
			}
		}

		if(tagHasLowerLevelTags || tagHasValue)
		{
			string firstTagClosingString = CHAR_TAG_CLOSE_STR;
			writeStringToFileObject(firstTagClosingString, writeFileObject);

			if(tagHasLowerLevelTags)
			{
				//cout << "hereLL" << endl;
				if(!addTagLayerToFileObject(currentTag->firstLowerLevelTag, writeFileObject, (treeLayer+1)))
				{
					result = false;
				}
			}
			if(tagHasValue)
			{
				//cout << "hereVV" << endl;

				addTabsToFileObject(writeFileObject, treeLayer);
				string tagValueString = currentTag->value;
				writeStringToFileObject(tagValueString, writeFileObject);
			}

			incrementLineAndAddTabsToFileObject(writeFileObject, treeLayer);
			string endTagString = CHAR_TAG_OPEN_STR;
			endTagString = endTagString + CHAR_TAG_END_STR;
			endTagString = endTagString + ((string)(currentTag->name));
			endTagString = endTagString + CHAR_TAG_CLOSE_STR;

			//endTagString[1] = CHAR_TAG_END;	 //work around as CHAR_TAG_END_STR does not work
			writeStringToFileObject(endTagString, writeFileObject);

		}
		else
		{
			string tagEndAndClose = " ";
			tagEndAndClose = tagEndAndClose + CHAR_TAG_END_STR;
			tagEndAndClose = tagEndAndClose + CHAR_TAG_CLOSE_STR;
			//tagEndAndClose[0] = CHAR_TAG_END;		//work around as CHAR_TAG_END_STR does not work
			writeStringToFileObject(tagEndAndClose, writeFileObject);

		}

		currentTag = currentTag->nextTag;
	}

	return result;

}

void incrementLineAndAddTabsToFileObject(ofstream * writeFileObject, int treeLayer)
{
	writeFileObject->put(CHAR_NEWLINE); //(s.cStr())[i]

	for(int i=0; i < treeLayer; i++)
	{
		writeFileObject->put(CHAR_TAB); //(s.cStr())[i]
	}

}

void addTabsToFileObject(ofstream * writeFileObject, int treeLayer)
{
	for(int i=0; i < treeLayer; i++)
	{
		writeFileObject->put(CHAR_TAB); //(s.cStr())[i]
	}

}

void writeStringToFileObject(string s, ofstream * writeFileObject)
{
	for(int i=0; i < s.size(); i++)
	{
		writeFileObject->put(s[i]); //(s.cStr())[i]
	}
}




bool addTagLayerToByteArrayInefficient(XMLParserTag * firstTagInCurrentLayer, char * XMLFileByteArray, long * XMLFileByteArrayCurrentPosition, int treeLayer)
{
	bool result = true;

	XMLParserTag * currentTag = firstTagInCurrentLayer;

	while(currentTag->nextTag != NULL)
	{

		bool tagHasAttributes = false;
		bool tagHasValue = false;
		bool tagHasLowerLevelTags = false;
		if(currentTag->firstAttribute->nextAttribute != NULL)
		{//tag has attributes
			tagHasAttributes = true;
		}
		if(currentTag->value != "")
		{//tag has value
			tagHasValue = true;
		}
		if(currentTag->firstLowerLevelTag != NULL)
		{//tag has lower level tags
			tagHasLowerLevelTags = true;
		}

		//cout << "h2" << endl;
		incrementLineAndAddTabsToByteArrayInefficient(XMLFileByteArray, XMLFileByteArrayCurrentPosition, treeLayer);
		string tagOpeningString = CHAR_TAG_OPEN_STR + currentTag->name;
		writeStringToByteArrayInefficient(tagOpeningString, XMLFileByteArray, XMLFileByteArrayCurrentPosition);
		if(tagHasAttributes)
		{
			XMLParserAttribute * currentAttribute = currentTag->firstAttribute;
			while(currentAttribute->nextAttribute != NULL)
			{
				string attributeString = " " + currentAttribute->name + CHAR_TAG_ATTRIBUTE_VAL_EQUALS_STR + CHAR_TAG_ATTRIBUTE_VAL_OPEN_STR + currentAttribute->value + CHAR_TAG_ATTRIBUTE_VAL_CLOSE_STR;
				writeStringToByteArrayInefficient(attributeString, XMLFileByteArray, XMLFileByteArrayCurrentPosition);

				currentAttribute = currentAttribute->nextAttribute;
				//cout << "hereAA" << endl;
			}
		}

		if(tagHasLowerLevelTags || tagHasValue)
		{
			string firstTagClosingString = CHAR_TAG_CLOSE_STR;
			writeStringToByteArrayInefficient(firstTagClosingString, XMLFileByteArray, XMLFileByteArrayCurrentPosition);

			if(tagHasLowerLevelTags)
			{
				//cout << "hereLL" << endl;
				if(!addTagLayerToByteArrayInefficient(currentTag->firstLowerLevelTag, XMLFileByteArray, XMLFileByteArrayCurrentPosition, (treeLayer+1)))
				{
					result = false;
				}
			}
			if(tagHasValue)
			{
				//cout << "hereVV" << endl;

				addTabsToByteArrayInefficient(XMLFileByteArray, XMLFileByteArrayCurrentPosition, treeLayer);
				string tagValueString = currentTag->value;
				writeStringToByteArrayInefficient(tagValueString, XMLFileByteArray, XMLFileByteArrayCurrentPosition);
			}

			incrementLineAndAddTabsToByteArrayInefficient(XMLFileByteArray, XMLFileByteArrayCurrentPosition, treeLayer);
			string endTagString = CHAR_TAG_OPEN_STR;
			endTagString = endTagString + CHAR_TAG_END_STR;
			endTagString = endTagString + ((string)(currentTag->name));
			endTagString = endTagString + CHAR_TAG_CLOSE_STR;

			//endTagString[1] = CHAR_TAG_END;	 //work around as CHAR_TAG_END_STR does not work
			writeStringToByteArrayInefficient(endTagString, XMLFileByteArray, XMLFileByteArrayCurrentPosition);

		}
		else
		{
			string tagEndAndClose = " ";
			tagEndAndClose = tagEndAndClose + CHAR_TAG_END_STR;
			tagEndAndClose = tagEndAndClose + CHAR_TAG_CLOSE_STR;
			//tagEndAndClose[0] = CHAR_TAG_END;		//work around as CHAR_TAG_END_STR does not work
			writeStringToByteArrayInefficient(tagEndAndClose, XMLFileByteArray, XMLFileByteArrayCurrentPosition);

		}

		currentTag = currentTag->nextTag;
	}

	return result;

}

void incrementLineAndAddTabsToByteArrayInefficient(char * XMLFileByteArray, long * XMLFileByteArrayCurrentPosition, int treeLayer)
{
	XMLFileByteArray[*XMLFileByteArrayCurrentPosition] = CHAR_NEWLINE;
	*XMLFileByteArrayCurrentPosition = (*XMLFileByteArrayCurrentPosition + 1);

	for(int i=0; i < treeLayer; i++)
	{
		XMLFileByteArray[*XMLFileByteArrayCurrentPosition] = CHAR_TAB;
		*XMLFileByteArrayCurrentPosition = (*XMLFileByteArrayCurrentPosition + 1);
	}

}

void addTabsToByteArrayInefficient(char * XMLFileByteArray, long * XMLFileByteArrayCurrentPosition, int treeLayer)
{
	for(int i=0; i < treeLayer; i++)
	{
		XMLFileByteArray[*XMLFileByteArrayCurrentPosition] = CHAR_TAB;
		*XMLFileByteArrayCurrentPosition = (*XMLFileByteArrayCurrentPosition + 1);
	}

}


void writeStringToByteArrayInefficient(string s, char * XMLFileByteArray, long * XMLFileByteArrayCurrentPosition)
{
	for(int i=0; i < s.size(); i++)
	{
		XMLFileByteArray[*XMLFileByteArrayCurrentPosition] = s[i]; //(s.cStr())[i]
		*XMLFileByteArrayCurrentPosition = (*XMLFileByteArrayCurrentPosition + 1);
	}
}



void writeByteArrayToFile(const char * fileName, char * fileByteArray, int fileByteArraySize)
{
	ofstream parseFileObject(fileName);

	// Exactly 8 bytes written
	parseFileObject.write(fileByteArray, (sizeof(char)*fileByteArraySize));

	parseFileObject.close();

}



bool readXMLFile(string xmlFileName, XMLParserTag * firstTagInXMLFile)
{
	bool result = true;

	charCount = 0;		//this variable needs to start being used
	lineCount = 1;

	ifstream parseFileObject(xmlFileName.c_str());
	if(!parseFileObject.rdbuf( )->is_open( ))
	{
		//xml file does not exist in current directory.
		cout << "Error: XML File does not exist in current directory: " << xmlFileName << endl;
		result = false;
	}
	else
	{
		//firstTagInXMLFile = new XMLParserTag();

		if(!parseTagOpen(&parseFileObject, firstTagInXMLFile, "noCurrentTagName", false, 0))
		{
			result = false;
		}
	}


	return result;
}


bool parseTagValueAssumingExistenceOfSubtabsAndClose(ifstream * parseFileObject, XMLParserTag * tag, XMLParserTag * subTag, string tagName, int treeLayer)
{
	//cout << "DEBUG: entered parseTagValueAssumingExistenceOfSubtabsAndClose(), tag->name = " << tag->name << ". subTag->name = " << subTag->name << ". tagName = " << tagName << ". treeLayer = " << treeLayer << endl;

	bool result = true;
	char currentToken;
	string tagValue="";
	//tagValue="";
	//delete &tagValue;

	bool finishedParsingObject = false;

	//cout << "h1" << endl;

	while(!finishedParsingObject && result)
	{
		if(!(parseFileObject->get(currentToken)))
		{
			result = false;
		}
		charCount++;

		if(currentToken == CHAR_TAG_OPEN)
		{
			tag->value = tagValue;
			//cout << "DEBUG: entering parseTagName(). treeLayer = " << treeLayer << endl;
			parseTagName(parseFileObject, subTag, tagName, true, ++treeLayer);
			finishedParsingObject = true;
		}
	#ifdef XML_PARSER_DO_NOT_ALLOW_TABS_OR_NEWLINES_WITHIN_TAG_VALUE
		else if(isBlankCharTabOrNewLine(parseFileObject, currentToken))
		{//NB spaces are added to the value however tabs and new lines are not

		}
	#endif
		else
		{
			//cout << "tagValue = " << tagValue << endl;
			tagValue = tagValue+currentToken;

		}
	}
	return result;

}


bool parseTagOpen(ifstream * parseFileObject, XMLParserTag * currentTag, string parentTagName, bool isASubTag, int treeLayer)
{
	//cout << "DEBUG: entered parseTagOpen(), currentTag->name = " << currentTag->name << ". parentTagName = " << parentTagName << ". isASubTag = " << isASubTag << ". treeLayer = " << treeLayer << endl;

	bool result = true;
	char currentToken;

	bool finishedParsingObject = false;
	while(!finishedParsingObject && result)
	{
		if(!(parseFileObject->get(currentToken)))
		{
			result = false;
		}
		charCount++;

		if(isBlankChar(parseFileObject, currentToken))
		{

		}
		else if(currentToken == CHAR_TAG_OPEN)
		{
			//cout << "DEBUG: entering parseTagName(). treeLayer = " << treeLayer << endl;
			parseTagName(parseFileObject, currentTag, parentTagName, isASubTag, treeLayer);
			finishedParsingObject = true;
		}
		else
		{

			cout << "currentToken = " << currentToken << (int)currentToken << endl;
			cout << "XML_PARSER_ERROR 1: invalid tag opening" << endl;
			throwGenericXMLParseError();
			result = false;
		}
	}
	return result;

}


//NB this current XML parser accepts <! .... > as a comment, <!-- .... --> is not required
bool parseTagComment(ifstream * parseFileObject)
{
	bool result = true;
	char currentToken;

	bool finishedParsingObject = false;
	while(!finishedParsingObject && result)
	{
		if(!(parseFileObject->get(currentToken)))
		{
			result = false;
		}
		charCount++;

		if(currentToken == CHAR_TAG_CLOSE)
		{
			finishedParsingObject = true;
		}
		else
		{
			//display comments when parsing:
			#ifdef XML_PARSER_DISPLAY_COMMENTS_WHEN_PARSING
			cout << currentToken;
			#endif
		}
	}
	return result;

}



bool parseTagName(ifstream * parseFileObject, XMLParserTag * currentTag, string parentTagName, bool isASubTag, int treeLayer)
{
	//cout << "DEBUG: entered parseTagName(), currentTag->name = " << currentTag->name << ". parentTagName = " << parentTagName << ". isASubTag = " << isASubTag << ". treeLayer = " << treeLayer << endl;

	bool result = true;
	char currentToken;
	string tagName="";
	//tagName="";
	//delete &tagName;

	bool finishedParsingObject = false;
	bool endTagFound = false;

	while(!finishedParsingObject && result)
	{
		if(!(parseFileObject->get(currentToken)))
		{
			result = false;
		}

		charCount++;

		if(isBlankChar(parseFileObject, currentToken))
		{
			if(!endTagFound)
			{
				currentTag->name = tagName;
				//NOT YET - wait till know if a sub tag exists: XMLParserTag newTag = new XMLParserTag();
				//NOT YET - wait till know if a sub tag exists: currentTag->nextTag = currentTag->nextTag;

				//cout << "DEBUG: entering parseTagAttributeName. treeLayer = " << treeLayer << endl;

				if(!parseTagAttributeName(parseFileObject, currentTag, parentTagName, isASubTag, treeLayer))
				{
					result = false;
				}

				finishedParsingObject = true;
			}
			else
			{
				cout << "XML_PARSER_ERROR 2: end tag found containing white space" << endl;
				throwGenericXMLParseError();
				result = false;
			}
		}
		else if(currentToken == CHAR_TAG_END)
		{
			#ifdef XML_PARSER_DO_NOT_ALLOW_CHAR_TAG_END_SLASH_WITHOUT_PRECEEDING_SPACE
			if(tagName != "")
			{
				cout << "XML_PARSER_ERROR 3: incorrect end tag indicator detected" << endl;
				throwGenericXMLParseError();
				result = false;
			}
			else
			{
			#endif
				endTagFound = true;
			#ifdef XML_PARSER_DO_NOT_ALLOW_CHAR_TAG_END_SLASH_WITHOUT_PRECEEDING_SPACE
			}
			#endif
		}
		else if((currentToken == CHAR_EXCLAMATION) || (currentToken == CHAR_QUESTIONMARK))
		{
			if(tagName == "")
			{
				if(!parseTagComment(parseFileObject))
				{
					result = false;
				}
				parseTagOpen(parseFileObject, currentTag, parentTagName, isASubTag, treeLayer);
				finishedParsingObject = true;
			}
			else
			{
				cout << "XML_PARSER_ERROR 4: invalid comment openining" << endl;
				throwGenericXMLParseError();
				result = false;
			}
		}
		else if(currentToken == CHAR_TAG_CLOSE)
		{
			if(tagName == "")
			{
				cout << "XML_PARSER_ERROR 5: empty tag name" << endl;
				throwGenericXMLParseError();
				result = false;
			}
			else
			{
				if(!isASubTag)
				{
					currentTag->name = tagName;
					if(endTagFound)
					{
						//cout << "DEBUG 1: tagWithEndFound, tagName = " << tagName << endl;
					}
					else
					{
						//cout << "DEBUG 2: tagWithoutEndFound, tagName = " << tagName << endl;

						XMLParserTag * newLowerLevelTag = new XMLParserTag();
						currentTag->firstLowerLevelTag = newLowerLevelTag;
						if(!parseTagValueAssumingExistenceOfSubtabsAndClose(parseFileObject, currentTag, currentTag->firstLowerLevelTag, tagName, treeLayer))
						{//go up a level in the tree
							result = false;
						}
					}

					//cout << "DEBUG 2b: continue parsing at same level. treeLayer = " << treeLayer << endl;
					XMLParserTag * newTag = new XMLParserTag();
					currentTag->nextTag = newTag;
					currentTag = currentTag->nextTag;
					parseTagOpen(parseFileObject, currentTag, parentTagName, isASubTag, treeLayer);
				}
				else
				{
					if(endTagFound)
					{
						if(tagName == parentTagName)
						{
							//finished parsing subtags within the value of this tag
							//cout << "DEBUG 3: tagWithEndFound, tagName = " << tagName << endl;
						}
						#ifdef XML_PARSER_DO_NOT_ALLOW_CHAR_TAG_END_SLASH_WITHOUT_PRECEEDING_SPACE
						else
						{//subtab+end detected with no attributes - this is illegal
							cout << "XML_PARSER_ERROR 6: subtab+end detected with no attributes - this is illegal" << endl;
							throwGenericXMLParseError();
							result = false;
						}
						#else
						else
						{
							//subtab+end detected without attributes
							//cout << "DEBUG 3b: tagWithoutAttributesAndWithEndFound, tagName = " << currentTag->name << endl;

							//NB currentTag->name has not already been filled
							currentTag->name = tagName;

							XMLParserTag * newTag = new XMLParserTag();
							currentTag->nextTag = newTag;
							currentTag = currentTag->nextTag;
							parseTagOpen(parseFileObject, currentTag, parentTagName, isASubTag, treeLayer);
						}
						#endif
					}
					else
					{
						#ifdef XML_PARSER_DO_NOT_ALLOW_SUBTAGS_WITH_SAME_NAME_AS_PARENT_TAG
						if(tagName == parentTagName)
						{
							cout << "XML_PARSER_ERROR 7: subtab detected with same name as parent tab - this is illegal" << endl;
							throwGenericXMLParseError();
							result = false;
						}
						else
						{
						#endif
							currentTag->name = tagName;
							//cout << "DEBUG 4: tagWithoutEndFound, tagName = " << tagName << endl;

							XMLParserTag * newLowerLevelTag = new XMLParserTag();
							currentTag->firstLowerLevelTag = newLowerLevelTag;
							if(!parseTagValueAssumingExistenceOfSubtabsAndClose(parseFileObject, currentTag, currentTag->firstLowerLevelTag, tagName, treeLayer))
							{//go up a level in the tree
								result = false;
							}

							//cout << "DEBUG 4b: continue parsing at same level. treeLayer = " << treeLayer << endl;

							XMLParserTag * newTag = new XMLParserTag();
							currentTag->nextTag = newTag;
							currentTag = currentTag->nextTag;
							parseTagOpen(parseFileObject, currentTag, parentTagName, isASubTag, treeLayer);
						#ifdef XML_PARSER_DO_NOT_ALLOW_SUBTAGS_WITH_SAME_NAME_AS_PARENT_TAG
						}
						#endif
					}
				}

				finishedParsingObject = true;
			}
		}
		else
		{
			tagName = tagName+currentToken;
		}
	}

	return result;

}

bool parseTagAttributeName(ifstream * parseFileObject, XMLParserTag * currentTag, string parentTagName, bool isASubTag, int treeLayer)
{
	//cout << "DEBUG: entered parseTagAttributeName(), currentTag->name = " << currentTag->name << ". parentTagName = " << parentTagName << ". isASubTag = " << isASubTag << ". treeLayer = " << treeLayer << endl;

	bool result = true;
	char currentToken;
	string attributeName="";
	//attributeName="";
	//delete &attributeName;

	bool endTagFound = false;

	bool finishedParsingObject = false;


	//cout << "DEBUG: parseTagAttributeName" << endl;


	while(!finishedParsingObject && result)
	{
		if(!(parseFileObject->get(currentToken)))
		{
			result = false;
		}
		charCount++;

		if(isBlankChar(parseFileObject, currentToken))
		{
			if(attributeName != "")
			{
				cout << "XML_PARSER_ERROR 8: invalid attribute name, attributeName = " << attributeName << ". currentTag->name = " << currentTag->name << ". parentTagName = " << parentTagName <<  endl;
				throwGenericXMLParseError();
				result = false;
			}
		}
		else if(currentToken == CHAR_TAG_END)
		{
			if(attributeName != "")
			{
				cout << "XML_PARSER_ERROR 9: invalid attribute name" << endl;
				throwGenericXMLParseError();
				result = false;
			}
			else
			{
				endTagFound = true;
			}
		}
		else if(currentToken == CHAR_TAG_CLOSE)
		{
			if(attributeName != "")
			{
				cout << "XML_PARSER_ERROR 10: invalid attribute name, attributeName = " << attributeName << ". currentTag->name = " << currentTag->name << ". parentTagName = " << parentTagName <<  endl;
				throwGenericXMLParseError();
				result = false;
			}
			else
			{
				if(!isASubTag)
				{
					//NB currentTag->name has already been filled in in parseTagName()
					if(endTagFound)
					{
						//cout << "DEBUG 5: tagWithAttributesAndEndFound, tagName = " << currentTag->name << endl;
					}
					else
					{
						//cout << "DEBUG 6: tagWithAttributesAndWithoutEndFound, tagName = " << currentTag->name << endl;
						XMLParserTag * newLowerLevelTag = new XMLParserTag();
						currentTag->firstLowerLevelTag = newLowerLevelTag;
						if(!parseTagValueAssumingExistenceOfSubtabsAndClose(parseFileObject, currentTag, currentTag->firstLowerLevelTag, currentTag->name, treeLayer))
						{//go up a level in the tree
							result = false;
						}
					}

					//cout << "DEBUG 6b: continue parsing at same level. treeLayer = " << treeLayer << endl;

					XMLParserTag * newTag = new XMLParserTag();
					currentTag->nextTag = newTag;
					currentTag = currentTag->nextTag;
					parseTagOpen(parseFileObject, currentTag, parentTagName, isASubTag, treeLayer);

				}
				else
				{
					if(endTagFound)
					{
						if(currentTag->name == parentTagName)
						{
							//finished parsing subtags within the value of this tag
							//cout << "DEBUG 7: tagWithAttributesAndWithEndFound, tagName = " << currentTag->name << endl;
						}
						else
						{//subtab+end detected with attributes
							//cout << "DEBUG 8: tagWithAttributesAndWithEndFound, tagName = " << currentTag->name << endl;

							//NB currentTag->name has already been filled in in parseTagName()

							XMLParserTag * newTag = new XMLParserTag();
							currentTag->nextTag = newTag;
							currentTag = currentTag->nextTag;
							parseTagOpen(parseFileObject, currentTag, parentTagName, isASubTag, treeLayer);
						}
					}
					else
					{
						if(currentTag->name == parentTagName)
						{
							cout << "XML_PARSER_ERROR 11: subtab detected with same name as parent tab - this is illegal" << endl;
							throwGenericXMLParseError();
							result = false;
						}
						else
						{
							//cout << "DEBUG 9: tagWithAttributesAndWithoutEndFound, tagName = " << currentTag->name << endl;

							//NB currentTag->name has already been filled in in parseTagName()

							XMLParserTag * newLowerLevelTag = new XMLParserTag();
							currentTag->firstLowerLevelTag = newLowerLevelTag;
							if(!parseTagValueAssumingExistenceOfSubtabsAndClose(parseFileObject, currentTag, currentTag->firstLowerLevelTag, currentTag->name, treeLayer))
							{//go up a level in the tree
								result = false;
							}

							//cout << "DEBUG 9b: continue parsing at same level. treeLayer = " << treeLayer << endl;

							XMLParserTag * newTag = new XMLParserTag();
							currentTag->nextTag = newTag;
							currentTag = currentTag->nextTag;
							parseTagOpen(parseFileObject, currentTag, parentTagName, isASubTag, treeLayer);
						}
					}
				}

				finishedParsingObject = true;
			}
		}
		else if(currentToken == CHAR_TAG_ATTRIBUTE_VAL_EQUALS)
		{
			if(attributeName != "")
			{
				currentTag->currentAttribute->name = attributeName;
				//NOT YET - wait till attribute value is parser: XMLParserAttribute newAttribute = new XMLParserAttribute()
				//NOT YET - wait till attribute value is parser: currentTag->currentAttribute = currentTag->currentAttribute->nextAttribute;
				if(!parseTagAttributeValue(parseFileObject, currentTag, parentTagName, isASubTag, treeLayer))
				{
					result = false;
				}

				finishedParsingObject = true;
			}
			else
			{
				cout << "XML_PARSER_ERROR 12: empty attribute name" << endl;
				throwGenericXMLParseError();
				result = false;
			}
		}
		else
		{
			attributeName = attributeName+currentToken;
		}
	}

	return result;
}


bool parseTagAttributeValue(ifstream * parseFileObject, XMLParserTag * currentTag, string parentTagName, bool isASubTag, int treeLayer)
{
	//cout << "DEBUG: entered parseTagAttributeValue(), currentTag->name = " << currentTag->name << ". parentTagName = " << parentTagName << ". isASubTag = " << isASubTag << ". treeLayer = " << treeLayer << endl;

	bool result = true;
	char currentToken;

	string attributeValue = "";
	//attributeValue = "";
	//delete &attributeValue;

	bool attributeValueOpenedYet = false;

	bool finishedParsingObject = false;
	while(!finishedParsingObject && result)
	{
		if(!(parseFileObject->get(currentToken)))
		{
			result = false;
		}
		//cout << "\n\t" << currentToken << endl;
		//cout << currentToken << endl;
		charCount++;

		if(isBlankChar(parseFileObject, currentToken))
		{
			if(attributeValueOpenedYet)
			{
				attributeValue = attributeValue+currentToken;
			}
			else
			{
				//do nothing - white space
			}
		}
	#ifdef XML_PARSER_DO_NOT_ALLOW_CHAR_TAG_END_SLASH_INSIDE_ATTRIBUTE_VALUE
		else if(currentToken == CHAR_TAG_END)
		{
			cout << "XML_PARSER_ERROR 13: invalid attribute value" << endl;
			throwGenericXMLParseError();
			result = false;
		}
	#endif
		else if(currentToken == CHAR_TAG_CLOSE)
		{
			cout << "XML_PARSER_ERROR 14: invalid attribute value" << endl;
			throwGenericXMLParseError();
			result = false;
		}
		else if(currentToken == CHAR_TAG_ATTRIBUTE_VAL_OPEN)
		{
			if(!attributeValueOpenedYet)
			{
				attributeValueOpenedYet = true;
			}
			else
			{
				if(attributeValue != "")
				{
					//cout << "empty attribute value detected" << endl;
				}


				currentTag->currentAttribute->value = attributeValue;
				XMLParserAttribute * newAttribute = new XMLParserAttribute();
				currentTag->currentAttribute->nextAttribute = newAttribute;
				currentTag->currentAttribute = currentTag->currentAttribute->nextAttribute;
				//cout << "DEBUG: rentering parseTagAttributeName after recording an attribute. treeLayer = " << treeLayer << endl;

				if(!parseTagAttributeName(parseFileObject, currentTag, parentTagName, isASubTag, treeLayer))
				{
					result = false;
				}
				finishedParsingObject = true;

			}
		}
		else
		{
			//cout << "\ncurrentToken = " << currentToken << endl;
			//cout << "\n1attributeValue = " << attributeValue << endl;					//cout << "ERROR DETECTED HERE @ > 500 function recursive iterations - LIMITED STACK SIZE / FUNCTION RECURSIVE ITERATIONS???\n\n:

			attributeValue = attributeValue+currentToken;

			//cout << "\n2attributeValue = " << attributeValue << endl;
		}
	}

	return result;
}





//Low Level
////////////////////////////////////////////////////////////////////////////////

bool isBlankCharTabOrNewLine(ifstream * parseFileObject, char c)
{
	bool result;

	if(c == CHAR_NEWLINE)
	{
		lineCount++;
		charCount=0;
		result = true;
	}
	else if(c == CHAR_TAB)
	{
		result = true;
	}
	else
	{
		result = false;
	}
	return result;
}

bool isBlankChar(ifstream * parseFileObject, char c)
{
	bool result;

/*
	#define LF 0x0A
	#define CR 0x0D

	if(c == LF)
	{
		cout << 'here' << endl;

		char currentToken;
		if(!(parseFileObject->get(currentToken)))
		{
			result = false;
		}
		if(c != CR)
		{
			cout << "error: not ASCII XML file" << endl;
		}

		lineCount++;
		charCount=0;
		result = true;
	}
*/
	if(c == CHAR_NEWLINE)
	{
		lineCount++;
		charCount=0;
		result = true;
	}
	else if(c == CHAR_TAB)
	{
		result = true;
	}
	else if(c == CHAR_SPACE)
	{
		result = true;
	}
	else
	{
		result = false;
	}
	return result;
}

void throwGenericXMLParseError()
{
	cout << "Error: Parsing XML File: Line = " << lineCount << ", Character = " << charCount << endl;
}






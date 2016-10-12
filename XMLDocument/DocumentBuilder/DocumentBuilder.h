#ifndef XMLDOCBUILD_H
#define XMLDOCBUILD_H
/////////////////////////////////////////////////////////////////////
//  DocumentBuilder.h -    Makes call to the Tokenizer and         //
//                           XmlElementParts                       //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2013                                 //
//  Platform:      Dell, Windows 8.1                               //
//  Application:   Scope analysis, OOD Assignment 2, Spring2015    //
//  Author:		   Ankur Pandey                                    //
/////////////////////////////////////////////////////////////////////

/*
Module Operations:
==================
This module defines a class that provides services necessary to parse xml files and string and build AST tree from it.

Public Interface:
=================
DocumentBuilder docbuild;
sPtr pDocEement_ = docbuild.parse(std::string path, bool checkFile); // Parsing xml file and string and returning shared ptr

Build Process:
==============
Required files
- XmlElement.h, XmlElement.cpp , 
  xmlElementParts.h ,xmlElementParts.cpp,
  Tokenizer.h, Tokenizer.cpp,
  DocumentBuilder.h, DocumentBuilder.cpp

Build commands
- devenv DocumentBuilder.vcxproj

Maintenance History:
====================
ver 1.0 : 18 March 2015
- first release
*/

#include <memory>
#include <string>
#include "../XmlElement/XmlElement.h"
#include "../XmlElementParts/Tokenizer.h"
#include "../XmlElementParts/xmlElementParts.h"

namespace XmlProcessing
{
	class DocumentBuilder
	{
	public:

		using sPtr = std::shared_ptr < AbstractXmlElement > ;
		using sPtrVector = std::vector < sPtr > ;

		enum ElementType { XmlDeclarElement = 1, ProcInstrElement, CommentElement, TaggedElement }; // storeElement Enum
		std::string strippingTag(std::string& str); // Stripping Tag from element
		void addAttrib(sPtr& element, const std::string& attVal); // Add Attribute and Value to Elements
		void XmlTreeBuilder(XmlParts& parts, sPtr& root); // Build Xml Tree for different Element
		void parsebyElement(sPtr &element, XmlParts& parts, ElementType eleType); //Parsing based on Element case
		std::string parseString(std::string& str, char stChar, char endChar); // getting subString from startchar and endChar
		void ASTbuilder(sPtr& pDocElement_, sPtr& rootEle, sPtrVector& elements, bool isDeclarEle); // Building AST tree
		void XmlTreeBuilderDiffElement(std::string part, bool& isNoChildEle, sPtr& child); //getting child for Different Element
		void strippingTagAndRestString(std::string& bracketSkipStr, std::string& tag, size_t startIndex, size_t endIndex); //stripping Tag And Rest of String
		sPtr parse(std::string path, bool checkFile); // // Parsing xml file and string and returning shared ptr

	private:

	};
}
#endif

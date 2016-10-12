#ifndef DISPLAY_H
#define DISPLAY_H
/////////////////////////////////////////////////////////////////////
//  Display.h - Display Xml Document Project                       //
//                                                                 //
//  ver 1.0                                                        //

/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module defines a class that provides services necessary to display Xml Document Project.

Public Interface:
=================
Display display;
display.printAttributeAndValue(attributePtr attibuts_); // Print Attribute And Values for Element
display.printQuery(std::vector<sPtr> element_); // Print Queried Elements
display.printXmlDoc(sPtr& pDocElement); // Print AST tree 
display.printHeader(std::string header); // Print Header String in Specific Format
display.printString(std::string str); // Print String

Build Process:
==============
Required files
- XmlDocument.h, XmlDocument.cpp,
  Display.h, Display.cpp

Build commands
- devenv Display.vcxproj /debug rebuild

Maintenance History:
====================
ver 1.0 : 18 March 2015
- first release
*/
#include "../XMLDocument/XmlDocument.h"

namespace XmlProcessing
{
	class Display
	{
	public:
		using sPtr = std::shared_ptr < AbstractXmlElement > ;
		using attributePtr = std::vector < std::pair<std::string, std::string> > ;

		void printAttributeAndValue(attributePtr attibuts_);// Print Attribute And Values for Element
		void printQuery(std::vector<sPtr> element_); // Print Queried Elements
		void printXmlDoc(sPtr& pDocElement); // Print AST tree 
		void printHeader(std::string header); // Print Header String in Specific Format
		void printString(std::string str); // Print String

	private:
	};
}
#endif




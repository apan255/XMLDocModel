#ifndef EXE_H
#define EXE_H
/////////////////////////////////////////////////////////////////////
//  Executive.h - Makes call to the XMLDocument, Display           //
//                                                           	   //

/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module defines a class that provides services necessary to execute Xml Document Project.

Public Interface:
=================
Executive exe;
display.dispRequirements(XmlProcessing::XmlDocument& doc); // Print Project Requirements

Build Process:
==============
Required files
- XmlDocument.h, XmlDocument.cpp, 
  Display.h, Display.cpp,
  Executive.h, Executive.cpp

Build commands
- devenv Executive.vcxproj /debug rebuild

Maintenance History:
====================
ver 1.0 : 18 March 2015
- first release
*/

#include "../XMLDocument/XmlDocument.h"
#include "../Display/Display.h"

namespace XmlProcessing
{
	class Executive
	{
	public:
		void dispRequirements(XmlProcessing::XmlDocument& doc, std::string& fileName);    // Print Project Requirements

	private:
		void demoRequirement6(XmlProcessing::XmlDocument& doc);                                 // Print Project Requirement 6
		void demoRequirement7(XmlProcessing::XmlDocument& doc);                                 // Print Project Requirement 7
		void demoRequirement8(XmlProcessing::XmlDocument& doc);                                 // Print Project Requirement 8
		void demoRequirement9(XmlProcessing::XmlDocument& doc);                                 // Print Project Requirement 9
		void demoRequirement4(XmlProcessing::XmlDocument& doc);                                 // Print Project Requirement 4
		void demoRequirement5(XmlProcessing::XmlDocument& doc);                                 // Print Project Requirement 5
		void demoRequirement10(XmlProcessing::XmlDocument& doc, std::string& fileName);   // Print Project Requirement 10 and 3
		void demoRequirement11(XmlProcessing::XmlDocument& doc);                                // Print Project Requirement 11 and 3
		void tempString(std::string& stringName);                                               // get Temporary XML String
		void demoRequirement7Delete(XmlProcessing::XmlDocument& doc);                           // Print Project Requirement 7 Delete Case
	};
}
#endif




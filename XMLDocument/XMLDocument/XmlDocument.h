#ifndef XMLDOCUM_H
#define XMLDOCUM_H
///////////////////////////////////////////////////////////////////
// XmlDocument.h - a container of XmlElement nodes               //
// Ver 1.4                                                       //
// Application: Help for CSE687 Pr#2, Spring 2015                //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013   //
// Author:      Jim Fawcett, CST 4-187, 443-3948                 //
//              jfawcett@twcny.rr.com                            //
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* =================
* This package is intended to help students in CSE687 - Object Oriented Design
* get started with Project #2 - XML Document Model.  It uses C++11 constructs,
* most noteably std::shared_ptr.  The XML Document Model is essentially
* a program-friendly wrapper around an Abstract Syntax Tree (AST) used to
* contain the results of parsing XML markup.
*
* Abstract Syntax Trees, defined in this package, are unordered trees with
* two types of nodes:
*   Terminal nodes     - nodes with no children
*   Non-Terminal nodes - nodes which may have a finite number of children
* They are often used to contain the results of parsing some language.
*
* The elements defined in the companion package, XmlElement, will be used in
* the AST defined in this package.  They are:
*   AbstractXmlElement - base for all the XML Element types
*   DocElement         - XML element with children designed to hold prologue, Xml root, and epilogue
*   TaggedElement      - XML element with tag, attributes, child elements
*   TextElement        - XML element with only text, no markup
*   CommentElement     - XML element with comment markup and text
*   ProcInstrElement   - XML element with markup and attributes but no children
*   XmlDeclarElement   - XML declaration element with attributes
*
* Required Files:
* =================
*   - XmlDocument.h, XmlDocument.cpp,
*     XmlElement.h, XmlElement.cpp,
*     DocumentBuilder.h, DocumentBuilder.cpp,

* Build Process:
* =================
*   devenv XmlDocument.sln /debug rebuild
*
* Maintenance History:
* =================
* ver 1.4 : 19 Mar 15
* - Added public interface to add and delete attribute and Also Project requirement
* ver 1.3 : 9 Mar 15
* - Added public interface to addchild, deletechild
* ver 1.2 : 18 Feb 15
* - Added queries return XmlDocument references so they can be chained, e.g., doc.element("foobar").descendents();
* ver 1.1 : 14 Feb 15
* - minor changes to comments, method arguments
* Ver 1.0 : 11 Feb 15
* - first release
*/

#include <memory>
#include <string>
#include "../XmlElement/XmlElement.h"
#include "../DocumentBuilder/DocumentBuilder.h"


namespace XmlProcessing
{
	class XmlDocument
	{
	public:
		using sPtr = std::shared_ptr < AbstractXmlElement > ;
		using attributePtr = std::vector < std::pair<std::string, std::string> >;

		XmlDocument(const std::string& src, bool CheckFile);     // XmlDocument Constructer with filename or String
		XmlDocument();                                           // XmlDocument Default Constructer
		XmlDocument& XmlDocument::operator=(XmlDocument&& pdoc); // Move Assignment operator 
		XmlDocument(XmlDocument&& pdoc);                         // Move Constructor 

		XmlDocument& element(const std::string& tag);           // found_[0] contains first element (DFS order) with tag
		XmlDocument& elements(const std::string& tag);          // found_ contains all elements with tag
		XmlDocument& children(const std::string& tag = "");     // found_ contains sPtrs to children of prior found_[0] 
		XmlDocument& descendents(const std::string& tag = "");  // found_ contains sPtrs to descendents of prior found_[0]
		std::vector<sPtr>& select();                            // return reference to found_.  Use std::move(found_) to clear found_
		
		XmlDocument& getAtrributeById(const std::string& attributename, std::string value = ""); // get Atrribute based on Id
		attributePtr getAttributesByTag(const std::vector<sPtr>& elements);                      // get Atrribute based on Tag

		bool XmlDocument::addAttribute(std::vector<sPtr>& element, const std::string& attrib, const std::string& val); // Add Attribute to specific element
		bool XmlDocument::deleteAttribute(std::vector<sPtr>& element, const std::string& attrib);                      // Delete Attribute from specific element
		bool XmlDocument::addChild(std::vector<sPtr>& element, const std::string& tag);                                // Add child based on TAG
		bool XmlDocument::deleteChild(std::vector<sPtr>& element, const std::string& tag);                             // Delete child based on TAG 

		void XmlDocument::save(std::string& filepath, bool isFile); // Save modified AST tree to string or file
		std::string& getWhichConstuctor();                          // Helper Function to return which Constructor Called
		XmlDocument& addRootElement();                              //  Add root element if AST is empty
		sPtr& getpDoc();                                            // Return reference to AST 

	private:
		void depthFirstSearchTag(const std::string& tag, bool recursivelySearch); // Do depthFirstSearch for specific Tag
		void depthFirstSearchDescendents(sPtr rootEle);                           // Do Depth First Search for Descendents

		sPtr pDocElement_;         // AST that holds procInstr, comments, XML root, and more comments
		std::vector<sPtr> found_;  // query results
		std::string whichConstuctor; // Store whichConstuctor Called
	};
}
#endif

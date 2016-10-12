///////////////////////////////////////////////////////////////////
// XmlDocument.cpp - a container of XmlElement nodes             //
// Ver 1.4                                                       //
// Application: Help for CSE687 Pr#2, Spring 2015                //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013   //
// Author:      Jim Fawcett, CST 4-187, 443-3948                 //
//              jfawcett@twcny.rr.com                            //
///////////////////////////////////////////////////////////////////

#include <iostream>
#include "XmlDocument.h"
#include <iomanip>
#include <string>
#include <stack>

//----< XmlDocument Constructer with filename or String >-----------------------------
XmlProcessing::XmlDocument::XmlDocument(const std::string& src, bool checkFile)
{
	whichConstuctor = " Inside Normal Constructor";
	sPtr pDocTemp = std::move(pDocElement_);
	XmlProcessing::DocumentBuilder docbuilder;
	if (checkFile == true){
		pDocElement_ = docbuilder.parse(src, true);
	}else{
		pDocElement_ = docbuilder.parse(src, false);
	}
	addRootElement();
}

//----< XmlDocument Default Constructer  >----------------------------------------------
XmlProcessing::XmlDocument::XmlDocument(){
	whichConstuctor = " Inside normal Constructor";
}

//------< Move Assignment operator  >----------------------------------------------------
XmlProcessing::XmlDocument& XmlProcessing::XmlDocument::operator=(XmlDocument&& pdoc){
	if (this == &pdoc) return *this;
	pDocElement_ = std::move(pdoc.pDocElement_);
	pdoc.pDocElement_ = nullptr;
	found_.clear();
	found_ = std::move(pdoc.found_);
	whichConstuctor = " Inside Move Assignment Operation";
	return *this;
}

//------< Move Constructor  >-------------------------------------------------------------
XmlProcessing::XmlDocument::XmlDocument(XmlDocument&& pdoc) : pDocElement_(std::move(pdoc.pDocElement_)), found_(std::move(pdoc.found_)){
	pdoc.pDocElement_ = nullptr;
	pdoc.found_.clear();
	whichConstuctor = " Inside Move Constructor";
}

//------< Return reference to found_.  Use std::move(found_) to clear found_  >------------
std::vector<XmlProcessing::XmlDocument::sPtr>& XmlProcessing::XmlDocument::select()
{
	return (std::move(found_));
}

//------< Helper Function to return which Constructor Called >--------------------------------
std::string& XmlProcessing::XmlDocument::getWhichConstuctor(){
	return whichConstuctor;
}

//------< found_[0] contains first element (DFS order) with tag >------------------------------
XmlProcessing::XmlDocument& XmlProcessing::XmlDocument::element(const std::string& tag)
{
	std::vector<sPtr> temp = std::move(found_);
	depthFirstSearchTag(tag, false);
	return *this;
}

//------< found_ contains all elements with tag >----------------------------------------------
XmlProcessing::XmlDocument& XmlProcessing::XmlDocument::elements(const std::string& tag)
{
	std::vector<sPtr> temp = std::move(found_);
	depthFirstSearchTag(tag, true);
	return *this;
}

//------< Do depthFirstSearch for specific Tag >------------------------------------------------
void XmlProcessing::XmlDocument::depthFirstSearchTag(const std::string& tag, bool recursivelySearch)
{
	std::stack<sPtr> treeStack;
	treeStack.push(pDocElement_);
	while (treeStack.size() > 0)
	{
		sPtr curNode = treeStack.top();
		if (curNode->value().compare(tag) == 0)
		{
			if (!recursivelySearch){
				found_.push_back(curNode);
				return;
			}
			else{
				found_.push_back(curNode);
			}
		}
		treeStack.pop();
		size_t numChild = curNode->children().size();
		for (size_t i = 0; i < numChild; ++i){
			TextElement* pTxEl = dynamic_cast<TextElement*>(curNode->children()[numChild - i - 1].get());
			treeStack.push(curNode->children()[numChild - i - 1]);
		}
	}
}

//------< found_ contains sPtrs to children of prior found_[0]  >--------------------------------------------
XmlProcessing::XmlDocument& XmlProcessing::XmlDocument::children(const std::string& tag)
{
	std::vector<sPtr> temp = std::move(found_);
	for (auto root : temp)
	{
		if (root)
		{
			for (auto pElement : root->children())
			{
				found_.push_back(pElement);
			}
		}
	}
	return *this;
}

//------< found_ contains sPtrs to descendents of prior found_[0]  >-----------------------------------
XmlProcessing::XmlDocument& XmlProcessing::XmlDocument::descendents(const std::string& tag)
{
	std::vector<sPtr> tempVec = std::move(found_);
	for (auto root : tempVec){
		depthFirstSearchDescendents(root);
	}
	return *this;
}

//------<  Do Depth First Search for Descendents >-------------------------------------------------------
void XmlProcessing::XmlDocument::depthFirstSearchDescendents(sPtr rootEle)
{
	size_t numChild = rootEle->children().size();
	for (size_t i = 0; i < numChild; ++i){
		found_.push_back(rootEle->children()[i]);
		depthFirstSearchDescendents(rootEle->children()[i]);
	}
}

//------<  get Atrribute based on Id >-------------------------------------------------------
XmlProcessing::XmlDocument& XmlProcessing::XmlDocument::getAtrributeById(const std::string& attrib, std::string val)
{
	std::vector<sPtr> tempVec = std::move(found_);
	std::stack<sPtr> treeStack;
	treeStack.push(pDocElement_);
	while (treeStack.size() > 0)
	{
		sPtr curNode = treeStack.top();
		for (auto attribs : curNode->attributes()){
			bool flag = false;
			if (val != ""){
				if (attribs.first.compare(attrib) == 0 && attribs.second.compare(val) == 0){
					found_.push_back(curNode);
					return *this;
				}
			}
			else{
				if (attribs.first.compare(attrib) == 0){
					found_.push_back(curNode);
					return *this;
				}
			}
		}
		treeStack.pop();
		size_t numChildren = curNode->children().size();
		for (size_t i = 0; i < numChildren; ++i){
			TextElement* pTxEl = dynamic_cast<TextElement*>(curNode->children()[numChildren - i - 1].get());
			treeStack.push(curNode->children()[numChildren - i - 1]);
		}
	}
	return *this;
}

//------<  get Atrribute based on Tag >-------------------------------------------------------
XmlProcessing::XmlDocument::attributePtr XmlProcessing::XmlDocument::getAttributesByTag(const std::vector<sPtr>& element)
{
	attributePtr attribs_;
	for (auto elem : element)
	{
		if (dynamic_cast<TaggedElement*>(elem.get()) || dynamic_cast<ProcInstrElement*>(elem.get()))
			for (auto p : elem->attributes())
			{
			std::pair<std::string, std::string> atPair(p.first, p.second);
			attribs_.push_back(atPair);
			}
	}
	return attribs_;
}

//------<  Return reference to AST  >-------------------------------------------------------
XmlProcessing::XmlDocument::sPtr& XmlProcessing::XmlDocument::getpDoc()
{
	return pDocElement_;
}

//------<  Add Attribute to specific element  >-----------------------------------------------
bool XmlProcessing::XmlDocument::addAttribute(std::vector<sPtr>& element, const std::string& attrib, const std::string& val)
{
	for (auto elem : element)
	{
		if (dynamic_cast<TaggedElement*>(elem.get()) || dynamic_cast<ProcInstrElement*>(elem.get())){
			return(elem->addAttrib(attrib, val));
		}
	}
	return false;
}

//------<  Delete Attribute from specific element  >-----------------------------------------------
bool XmlProcessing::XmlDocument::deleteAttribute(std::vector<sPtr>& element, const std::string& attrib)
{
	for (auto elem : element)
	{
		if (dynamic_cast<TaggedElement*>(elem.get()) || dynamic_cast<ProcInstrElement*>(elem.get())){
			return elem->removeAttrib(attrib);
		}
	}
	return false;
}

//------<  Add root element if AST is empty  >-------------------------------------------------------
XmlProcessing::XmlDocument& XmlProcessing::XmlDocument::addRootElement()
{
	if (getpDoc() == nullptr){
	}
	return *this;
}

//------<  Delete child based on TAG  >---------------------------------------------------------------
bool XmlProcessing::XmlDocument::deleteChild(std::vector<sPtr>& element, const std::string& tag)
{
	for (auto elem : element)
	{
		for (auto child : elem->children()){
			if (child->value().compare(tag) == 0)
				return elem->removeChild(child);
		}
	}
	return false;
}

//------<  Add child based on TAG  >---------------------------------------------------------------
bool XmlProcessing::XmlDocument::addChild(std::vector<sPtr>& element, const std::string& tag)
{
	for (auto elem : element)
	{
		if (dynamic_cast<TaggedElement*>(elem.get())){
			sPtr child = makeTaggedElement(tag);
			return elem->addChild(child);
		}
	}
	return false;
}

//------<  Save modified AST tree to string or file  >-------------------------------------------------
void XmlProcessing::XmlDocument::save(std::string& fileorString, bool isFile)
{
	if (isFile){
		std::ofstream fileOut(fileorString);
		fileOut << getpDoc()->toString();
	}
	else{
		fileorString = getpDoc()->toString();
	}
}

#ifdef TEST_XMLDOCU

#include "../Display/Display.h"
//----< Calling Executive Main >-------------------------------------------
int main(int argc, char* argv[])
{
	try{
		XmlProcessing::Display display;
		display.printHeader("Testing XmlDocument File Project");
		XmlProcessing::XmlDocument doc("../../TEST_FOLDER_XMLDocument/LectureNote.xml", true);
		display.printXmlDoc(doc.getpDoc());
		display.printHeader("Testing querie 1 with element LectureNote children");
		std::vector<std::shared_ptr < XmlProcessing::AbstractXmlElement >> element_ = doc.element("LectureNote").children().select();
		display.printQuery(element_);
		display.printHeader("Testing querie 2 with element title children");
		element_ = doc.element("title").children().select();
		display.printQuery(element_);
		display.printHeader("Testing querie 10 with getAttributesValues ");
		element_ = doc.element("LectureNote").select();
		XmlProcessing::XmlDocument::attributePtr attPtr = doc.getAttributesByTag(element_);
		display.printAttributeAndValue(attPtr);
		display.printHeader("Testing querie 11 with getAtrributeById ");
		element_ = doc.getAtrributeById("Company").select();
		attPtr = doc.getAttributesByTag(element_);
		display.printAttributeAndValue(attPtr);
		display.printHeader("Testing 12 Attribute And Value Add ");
		element_ = doc.element("LectureNote").select();
		doc.addAttribute(element_, "Added", "Later");
		display.printXmlDoc(doc.getpDoc());
		display.printHeader("Testing 13  Attribute Delete");
		element_ = doc.getAtrributeById("Company").select();
		doc.deleteAttribute(element_, "Company");
		display.printXmlDoc(doc.getpDoc());
		display.printHeader("Testing 14 Add Child ELement ");
		element_ = doc.element("publisher").select();
		doc.addChild(element_, "NewChild");
		display.printXmlDoc(doc.getpDoc());
		display.printHeader("Testing 16 Delete Child Element");
		element_ = doc.element("author").select();
		doc.deleteChild(element_, "note");
		display.printXmlDoc(doc.getpDoc());
	}
	catch (std::exception& ex){
		std::cout << "\n\n    " << ex.what() << "\n\n";
	}
	return 0;
}
#endif

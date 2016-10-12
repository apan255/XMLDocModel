/////////////////////////////////////////////////////////////////////
//  Executive.cpp - Makes call to the XMLDocument, Display         //
//                                                           	   //

/////////////////////////////////////////////////////////////////////

#include<iostream>
#include <string>
#include "Executive.h"
using namespace XmlProcessing;

//----< Print Project Requirements >----------------------------------------------
void Executive::dispRequirements(XmlProcessing::XmlDocument& doc, std::string& fileName)
{
	XmlProcessing::Display display;
	display.printHeader("DEMONSTRATING REQUIREMENT 11 And 3");
	demoRequirement11(doc);
	display.printString("\n\n Press for next requirement \n\n");
	std::cin.get();

	display.printHeader("DEMONSTRATING REQUIREMENT 5");
	demoRequirement5(doc);
	display.printString("\n\n Press for next requirement \n\n");
	std::cin.get();

	display.printHeader("DEMONSTRATING REQUIREMENT 6");
	demoRequirement6(doc);
	display.printString("\n\n Press for next requirement \n\n");
	std::cin.get();

	display.printHeader("DEMONSTRATING REQUIREMENT 7");
	demoRequirement7(doc);
	display.printString("\n\n Press for next requirement \n\n");
	std::cin.get();

	display.printHeader("DEMONSTRATING REQUIREMENT 8");
	demoRequirement8(doc);
	display.printString("\n\n Press for next requirement \n\n");
	std::cin.get();

	display.printHeader("DEMONSTRATING REQUIREMENT 9");
	demoRequirement9(doc);
	display.printString("\n\n Press for next requirement \n\n");
	std::cin.get();

	display.printHeader("DEMONSTRATING REQUIREMENT 10 And 3");
	demoRequirement10(doc,fileName);
	display.printString("\n\n Press for next requirement \n\n");
	std::cin.get();

	display.printHeader("DEMONSTRATING REQUIREMENT 4");
	demoRequirement4(doc);
	
}

//----< Print Project Requirement 6 >----------------------------------------------
void Executive::demoRequirement6(XmlProcessing::XmlDocument& doc)
{
	XmlProcessing::Display display;
	display.printString("DEMONSTRATING REQUIREMENT 6 Collection of Elements children");
	display.printString("Query : doc.elements(\"title\").select()");
	std::vector<XmlProcessing::XmlDocument::sPtr> element = doc.elements("title").select();
	display.printQuery(element);

	display.printString("\nDEMONSTRATING REQUIREMENT 6 Collection of Elements descendents");
	display.printString(" Query :  doc.element(\"reference\").descendents().select()");
	element = doc.element("reference").descendents().select();;
	display.printQuery(element);

}

//----< Print Project Requirement 7 >----------------------------------------------
void Executive::demoRequirement7(XmlProcessing::XmlDocument& doc)
{
	XmlProcessing::Display display;
	display.printString("DEMONSTRATING REQUIREMENT  7 - Add Child to element found by TAG");
	display.printString("Query : doc.element(\"reference\").addChild(\"Summary\")");
	display.printString("Initial XML Tree");
	display.printXmlDoc(doc.getpDoc());
	std::vector<XmlProcessing::XmlDocument::sPtr> element = doc.elements("reference").select();
	bool isAdded = doc.addChild(element, "Summary");
	if (isAdded){
		display.printString("Sucessfully Added Summary");
		display.printString("Modified XML Tree");
		display.printXmlDoc(doc.getpDoc());
	}
	else{
		display.printString("Not able to add Summary");
	}

	display.printString("\nDEMONSTRATING REQUIREMENT  7 - Add Child to element found by ID");
	display.printString(" Query : doc.getAtrributeById(\"course\").select() ; doc.addChildElement(\"Time\")");
	display.printString("Initial XML Tree");
	display.printXmlDoc(doc.getpDoc());
	element = doc.getAtrributeById("course").select();
	isAdded = doc.addChild(element, "Time");
	if (isAdded){
		display.printString("Sucessfully Added Time");
		display.printString("Modified XML Tree");
		display.printXmlDoc(doc.getpDoc());
	}
	else{
		display.printString("Not able to add Time");
	}
	demoRequirement7Delete(doc);
}

//----< Print Project Requirement 7 Delete >----------------------------------------------
void Executive::demoRequirement7Delete(XmlProcessing::XmlDocument& doc){

	XmlProcessing::Display display;
	display.printString("\n\n Press for next requirement \n\n");
	std::cin.get();
	display.printString("DEMONSTRATING REQUIREMENT  7 - Add Delete to element found by TAG");
	display.printString(" Query : doc.element(\"reference\").deleteChild(\"Summary\")");
	display.printString("Initial XML Tree");
	display.printXmlDoc(doc.getpDoc());
	std::vector<XmlProcessing::XmlDocument::sPtr> element = doc.element("reference").select();;
	bool isdeleted = doc.deleteChild(element, "Summary");
	if (isdeleted){
		display.printString("Sucessfully Delete Summary");
		display.printString("Modified XML Tree");
		display.printXmlDoc(doc.getpDoc());
	}
	else{
		display.printString("Not able to delete Summary");
	}
	display.printString("\nDEMONSTRATING REQUIREMENT  7 - Delete Child to element found by ID");
	display.printString("Query : doc.element(\"course\").deleteChild(\"Time\")");
	display.printString("Initial XML Tree");
	display.printXmlDoc(doc.getpDoc());
	element = doc.getAtrributeById("course").select();
	isdeleted = doc.deleteChild(element, "Time");
	if (isdeleted){
		display.printString("Sucessfully Delete Time");
		display.printString("Modified XML Tree");
		display.printXmlDoc(doc.getpDoc());
	}
	else{
		display.printString("Not able to delete Time");
	}
	std::string stringName = " ";
	display.printString("\nDEMONSTRATING REQUIREMENT 7 ability to add a root element to an empty document tree");
	display.printString("String : " + stringName);
	XmlProcessing::XmlDocument docNew(stringName, false);
	docNew.save(stringName, false);
	display.printString("Modifed XML : " + stringName);
}

//----< Print Project Requirement 8 >----------------------------------------------
void Executive::demoRequirement8(XmlProcessing::XmlDocument& doc)
{
	XmlProcessing::Display display;

	display.printString("DEMONSTRATING REQUIREMENT 8 Name-Value Attribute Pairs");
	display.printString("Query : doc.element(\"note\").select(); doc.getAttributesValues()");
	std::vector<XmlProcessing::XmlDocument::sPtr> element = doc.element("note").select();
	XmlProcessing::XmlDocument::attributePtr attPtr = doc.getAttributesByTag(element);
	display.printAttributeAndValue(attPtr);

	display.printString("\nDEMONSTRATING REQUIREMENT 8 children");
	display.printString("Query : doc.element(\"title\").children().select(); ");
	element = doc.element("title").children().select();
	display.printQuery(element);
}

//----< Print Project Requirement 9 >----------------------------------------------
void Executive::demoRequirement9(XmlProcessing::XmlDocument& doc)
{
	XmlProcessing::Display display;

	display.printString("DEMONSTRATING REQUIREMENT  9 Add Name-Value Attribute Pairs");
	display.printString("Query : doc.element(\"LectureNote\").select(); doc.actionOnAttribute(\"Day\", \"Tuesday\"");
	display.printString("Initial XML Tree");
	display.printXmlDoc(doc.getpDoc());
	std::vector<XmlProcessing::XmlDocument::sPtr> element = doc.element("LectureNote").select();
	bool isAdded = doc.addAttribute(element, "Day", "Tuesday");
	if (isAdded){
		display.printString("Sucessfully Added \"Day\" Attribute and \"tuesday\" Value");
		display.printString("Modified XML Tree");
		display.printXmlDoc(doc.getpDoc());
	}
	else{
		display.printString("Not able to add \"Day\" Attribute and \"tuesday\" Value");
	}

	display.printString("\nDEMONSTRATING REQUIREMENT  9 Delete Name-Value Attribute Pairs");
	display.printString("Query : doc.element(\"LectureNote\").select(); doc.actionOnAttribute(\"Day\")");
	display.printString("Initial XML Tree");
	display.printXmlDoc(doc.getpDoc());
	element = doc.element("LectureNote").select();
	bool isDeleted = doc.deleteAttribute(element, "Day");
	if (isDeleted){
		display.printString("Sucessfully Deleted Day");
		display.printString("Modified XML Tree");
		display.printXmlDoc(doc.getpDoc());
	}
	else{
		display.printString("Not able to delete Day");
	}
}

//----< Print Project Requirement 4 >----------------------------------------------
void Executive::demoRequirement4(XmlProcessing::XmlDocument& doc)
{
	XmlProcessing::XmlDocument doc1;
	XmlProcessing::Display display;
	display.printString("DEMONSTRATING REQUIREMENT 4 Move Construtor");
	display.printString(" XmlProcessing::XmlDocument newdoc(doc); ");
	XmlProcessing::XmlDocument newdoc(std::move(doc1));
	display.printString(newdoc.getWhichConstuctor());

	display.printString("\nDEMONSTRATING REQUIREMENT 4 Assignment Construtor");
	display.printString(" XmlProcessing::XmlDocument docString; docString = std::move(newdoc); ");
	XmlProcessing::XmlDocument docString;
	docString = std::move(newdoc);
	display.printString(docString.getWhichConstuctor());

	display.printString("\n\n\n" + std::string(75, '*'));

}

//----< Print Project Requirement 5 >----------------------------------------------
void Executive::demoRequirement5(XmlProcessing::XmlDocument& doc)
{
	XmlProcessing::Display display;
	display.printString("DEMONSTRATING REQUIREMENT 5 Query By Unique ID attribute");
	display.printString("Query by unique ID - doc.getAtrributeById(\"Company\").select()");
	std::vector<XmlProcessing::XmlDocument::sPtr> element = doc.getAtrributeById("Company").select();
	XmlProcessing::XmlDocument::attributePtr attPtr = doc.getAttributesByTag(element);
	display.printAttributeAndValue(attPtr);

	display.printString("\nDEMONSTRATING REQUIREMENT 5 Query By wrong attribute");
	display.printString("Query by unique ID - doc.getAtrributeById(\"Teacher\").select()");
	element = doc.getAtrributeById("Teacher").select();
	attPtr = doc.getAttributesByTag(element);
	display.printAttributeAndValue(attPtr);
}

//----< Print Project Requirement 11 >----------------------------------------------
void Executive::demoRequirement11(XmlProcessing::XmlDocument& doc)
{
	XmlProcessing::Display display;
	display.printString("DEMONSTRATING REQUIREMENT 11 and 3 Initail Parse Tree from File");
	display.printXmlDoc(doc.getpDoc());
}

//----< get Temporary XML String >----------------------------------------------
void Executive::tempString(std::string& stringName){
	stringName = " <?xml version=\"1.0\"  encoding=\"utf - 8\"> <LectureNote course = \"CSE681\"  NewAttribute = \"Value\"> <title> XML Example # 1 </title> </LectureNote>";
}

//----< Print Project Requirement 10 >----------------------------------------------
void Executive::demoRequirement10(XmlProcessing::XmlDocument& doc, std::string& fileName)
{
	XmlProcessing::Display display;
	display.printString("DEMONSTRATING REQUIREMENT 10 and 3 Writing to Xml File");
	display.printString("Filename: \"../../TEST_FOLDER_XMLDocument/LectureNote.xml\"");
	display.printString(" Query : doc.element(\"reference\").addChild(\"Summary2\")");
	display.printString("Initial XML Tree");
	display.printXmlDoc(doc.getpDoc());
	std::vector<XmlProcessing::XmlDocument::sPtr> element = doc.element("reference").select();;
	bool isadded = doc.addChild(element, "Summary2");
	display.printString("Modified XML Tree");
	doc.save(fileName, true);

	display.printString("\nDEMONSTRATING REQUIREMENT 10 and 3 Reading from Xml File");
	display.printString("Filename: \"../../TEST_FOLDER_XMLDocument/LectureNote.xml\"");
	display.printXmlDoc(doc.getpDoc());

	std::string stringName = " ";
	tempString(stringName);
	XmlProcessing::XmlDocument docString(stringName, false);
	display.printString("\nDEMONSTRATING REQUIREMENT 10  And 3 Reading from string");
	display.printXmlDoc(docString.getpDoc());

	display.printString("\nDEMONSTRATING REQUIREMENT 10 And 3 Writing to string ");
	display.printString(" Query : doc.element(\"LectureNote\").addChild(\"Time2\")");
	element = docString.element("LectureNote").select();;
	docString.addChild(element, "Time2");
	docString.save(stringName, false);
	display.printString("Modified XML String");
	display.printString("String : " + stringName);
}

#ifdef TEST_EXECUTIVE
//----< Calling Executive Main >-------------------------------------------
int main(int argc, char* argv[])
{	
	try{
		Executive executive;
		using sPtr = std::shared_ptr < AbstractXmlElement >;
		if (argc > 2){
			std::string tmp = argv[1];
			std::string tmpString = argv[2];
			if (tmp == "/s" || tmp == "/S"){
				if (tmpString == "") tmpString = " "; //TO DO: For Bug in Tokenizer
				XmlProcessing::XmlDocument doc(tmpString, false);
				executive.dispRequirements(doc, tmpString);
			}
			else if (tmp == "/f" || tmp == "/F"){
				XmlProcessing::XmlDocument doc(tmpString, true);
				executive.dispRequirements(doc, tmpString);
			}

		}
	}
	catch (std::exception& ex){
		std::cout << "\n\n    " << ex.what() << "\n\n";
	}
	return 0;
}
#endif





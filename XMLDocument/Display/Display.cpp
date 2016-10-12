/////////////////////////////////////////////////////////////////////
//  Display.cpp - Display Xml Document Project                     //
//                                                                 //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2013                                 //
//  Platform:      Dell, Windows 8.1                               //
//  Application:   Scope analysis, OOD Assignment 2, Spring2015    //
//  Author:		   Ankur Pandey                                    //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Display.h"

//----< Print AST tree >----------------------------------------------
void XmlProcessing::Display::printXmlDoc(sPtr& pDocElem)
{
	std::cout << "\n\n The XML Tree is: \n" << pDocElem->toString();
	std::cout << "\n\n";
}

//----< Print String >------------------------------------------------
void XmlProcessing::Display::printString(std::string str)
{
	std::cout << "\n" << str;
	std::cout << "\n";
}

//----< Print Header String in Specific Format>------------------------
void XmlProcessing::Display::printHeader(std::string header){
	std::cout << "\n";
	std::cout << std::string(75, '*');
	std::cout << "\n" << header;
	std::cout << "\n" << std::string(75, '*');
	std::cout << "\n";
}

//----< Print Attribute And Values for Element>---------------------------
void  XmlProcessing::Display::printAttributeAndValue(attributePtr attibuts_)
{
	if (attibuts_.size() < 1)
	{
		std::cout << "\n No Attribute value with this element Found";
		return;
	}
	for (auto tmp : attibuts_)
	{
		std::cout << "\n AttributeName is: " << tmp.first << " and value is: " << tmp.second;
	}
}

//----< Print Queried Elements >---------------------------
void XmlProcessing::Display::printQuery(std::vector<sPtr> element_)
{
	if (element_.size() < 1)
	{
		std::cout << "\n No such element Found";
		return;
	}
	for (auto tmp : element_)
	{
		std::cout << "\n" <<"Tag Name: " << tmp->value() ;
	}
}

#ifdef TEST_DISPLAY

#include "../Executive/Executive.h"

//----< Calling Display Main >-------------------------------------------
int main(int argc, char* argv[])
{
	char *argv1[] = { "/s", "../../TEST_FOLDER_XMLDocument/LectureNote.xml" };
	argc = 2;
	try{
		XmlProcessing::Executive executive;
		if (argc >= 2){
			std::string tmp = argv1[0];
			std::string tmpString = argv1[1];
			if (tmp == "/s" || tmp == "/S"){
				std::string TestDocXML = "< ? xml version = \"1.0\" encoding = \"utf-8\" ? > \
							< ? xml - stylesheet type = \"text/xsl\" href = \"style.xsl\" ? > \
							< ? xml - stylesheet type = \"text/xsl\" href = \"style.xsl\" ? > \
							<!--XML test case --> \
							<LectureNote course = \"CSE681\" href = ""> \
							<title>XML Example #1< / title> \
							<reference> \
							<title>Programming Microsoft.Net< / title> \
							<author>Jeff Prosise <note Company = 'Wintellect'>< / note>< / author> \
							<publisher>Microsoft Press< / publisher> \
							<date>2002< / date> \
							<!--XML test case 2 --> \
							< ? xml - stylesheet2 type = \"text/xsl\" href = \"style.xsl\" ? > \
							<page>608< / page> \
							< / reference> \
							<comment>Description of PCDATA< / comment> \
							< / LectureNote>";

				XmlProcessing::XmlDocument doc(TestDocXML, false);
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


/////////////////////////////////////////////////////////////////////
//  DocumentBuilder.cpp -    Makes call to the Tokenizer and       //
//                           XmlElementParts                       //
//  ver 1.0                                                        //

/////////////////////////////////////////////////////////////////////

#include <iostream>
#include "DocumentBuilder.h"
#include <iomanip>

using namespace XmlProcessing;

//----< Add Attribute and Value to Elements >---------------------------
void XmlProcessing::DocumentBuilder::addAttrib(sPtr& element, const std::string& attVal)
{
	size_t index = 0;
	bool isAttribute = false;
	std::string attribute;
	std::string value;
	while (index < attVal.size() && attVal[index] != '\0')
	{
		if (attVal[index] != ' ' && attVal[index] != '=')
		{
			while (attVal[index] != '\0' && attVal[index] != ' ')
			{
				if (!isAttribute){
					attribute += attVal[index];
				}
				else{
					value += attVal[index];
				}
				index++;
			}
			if (isAttribute){
				value = parseString(value, '\"', '\"');
				element->addAttrib(attribute, value);
				attribute = "";
				value = "";
			}
			isAttribute = !isAttribute;
		}
		index++;
	}
}

//----< Stripping Tag from element >------------------------------------------------
std::string XmlProcessing::DocumentBuilder::strippingTag(std::string& bracketSkipStr)
{
	size_t startIndex = 0, endIndex = 0, index = 0;
	bool startCheck = true;
	std::string tag;
	while (index < bracketSkipStr.size() && bracketSkipStr[index] != '\0')
	{
		if (bracketSkipStr[index] != ' ' && bracketSkipStr[index] != '=')
		{
			if (startCheck) startIndex = index;
			startCheck = false;
			while (bracketSkipStr[index] != '\0')
			{
				if (bracketSkipStr[index] == '=')
					break;
				if (bracketSkipStr[index] == ' ' && bracketSkipStr[index + 1] != '=')
					endIndex = index;
				index++;
			}
			break;
		}
		index++;
	}
	strippingTagAndRestString(bracketSkipStr, tag, startIndex, endIndex);

	return tag;
}

//----< stripping Tag And Rest of String >------------------------------------------------
void XmlProcessing::DocumentBuilder::strippingTagAndRestString(std::string& bracketSkipStr, std::string& tag, size_t startIndex, size_t endIndex){
	while (startIndex < endIndex)
	{
		if (bracketSkipStr[startIndex] != ' ')
			tag += bracketSkipStr[startIndex];
		startIndex++;
	}
	std::string tempStr;
	while (endIndex < bracketSkipStr.size() && bracketSkipStr[endIndex] != '\0'){
		tempStr += bracketSkipStr[endIndex++];
	}
	bracketSkipStr = tempStr;
}

//----< getting subString from startchar and endChar >------------------------------------------------
std::string XmlProcessing::DocumentBuilder::parseString(std::string& str, char stChar, char endChar)
{
	size_t start = str.find_first_of(stChar);
	size_t end;
	if (endChar != ' ')
		end = str.find_last_of(endChar);
	else
		end = str.find(" ", start + 1);
	std::string substr = str.substr(start + 1, end - (start + 1));
	return substr;
}

//----< Build Xml Tree for different Element >------------------------------------------------
void XmlProcessing::DocumentBuilder::XmlTreeBuilder(XmlParts& parts, sPtr& root)
{
	if ((parts.show().find("/ >") != std::string::npos)) return;
	std::string str = root->value();
	size_t start = str.find_first_of("< ");
	size_t end = str.find(" ", start + 1);
	std::string starttag = str.substr(start + 1, end - (start + 1));
	std::string endtag = "  < / " + starttag + " >";
	sPtr child = nullptr;
	while (parts.get() && parts.show().compare(endtag) != 0)
	{
		std::string part = parts.show().c_str();
		std::string substr = parseString(part, '<', '>');
		if (part.find("<") != std::string::npos){

			bool isNoChildEle = true;
			XmlTreeBuilderDiffElement(part, isNoChildEle, child);
			root->addChild(child);
			parts.remove(part);
			if (!isNoChildEle)
				XmlTreeBuilder(parts, child);
		}
		else
		{
			child = makeTextElement(substr);
			root->addChild(child);
			parts.remove(part);
		}
	}
}

//----< getting child for Different Element>------------------------------------------------
void XmlProcessing::DocumentBuilder::XmlTreeBuilderDiffElement(std::string part, bool& isNoChildEle, sPtr& child){

	size_t start = part.find("< ?");
	size_t end = part.find_last_of("? >");
	if (start != std::string::npos && end != std::string::npos)
	{
		if (part.find("xml -") == std::string::npos){
			child = makeXmlDeclarElement();
			std::string bracketSkipStr = part.substr(part.find("< ?") + 3, part.find_last_of("? >") - (part.find("< ?") + 5));
			std::string tag = strippingTag(bracketSkipStr);
			addAttrib(child, bracketSkipStr);
		}
		else{
			std::string bracketSkipStr = part.substr(part.find("< ?") + 3, part.find_last_of("? >") - (part.find("< ?") + 5));
			std::string tag = strippingTag(bracketSkipStr);
			child = makeProcInstrElement(tag);
			addAttrib(child, bracketSkipStr);
		}
	}
	else{
		if (part.find("< ! --") != std::string::npos && part.find("-- >") != std::string::npos){
			std::string bracketSkipStr = part.substr(part.find("< ! --") + 6, part.find_last_of("-- >") - (part.find("< ! --") + 9));
			child = makeCommentElement(bracketSkipStr);
		}
		else{
			std::string bracketSkipStr = part.substr(part.find("<") + 1, part.find_last_of(">") - (part.find("<") + 1));
			std::string tag = strippingTag(bracketSkipStr);
			child = makeTaggedElement(tag);
			addAttrib(child, bracketSkipStr);
			isNoChildEle = false;
		}
	}
}

//----< Parsing based on Element case >------------------------------------------------
void XmlProcessing::DocumentBuilder::parsebyElement(sPtr &element, XmlParts& parts, ElementType eleType)
{
	std::string part = parts.show();
	switch (eleType){
	case XmlDeclarElement:{
		element = makeXmlDeclarElement();
		std::string bracketSkipStr = part.substr(part.find("< ?") + 3, part.find_last_of("? >") - (part.find("< ?") + 5));
		std::string tag = strippingTag(bracketSkipStr);
		addAttrib(element, bracketSkipStr);
	}
		break;
	case ProcInstrElement:{
		std::string bracketSkipStr = part.substr(part.find("< ?") + 3, part.find_last_of("? >") - (part.find("< ?") + 5));
		std::string tag = strippingTag(bracketSkipStr);
		element = makeProcInstrElement(tag);
		addAttrib(element, bracketSkipStr);
	}
		break;
	case CommentElement:{
		std::string bracketSkipStr = part.substr(part.find("< ! --") + 6, part.find_last_of("-- >") - (part.find("< ! --") + 9));
		element = makeCommentElement(bracketSkipStr);
	}
		break;
	case TaggedElement:{
		if (!element){
			std::string bracketSkipStr = part.substr(part.find("<") + 1, part.find_last_of(">") - (part.find("<") + 1));
			std::string tag = strippingTag(bracketSkipStr);
			element = makeTaggedElement(tag);
			addAttrib(element, bracketSkipStr);
			parts.remove(parts.show());
		}
		XmlTreeBuilder(parts, element);
	}
		break;
	}
}

//----< Building AST tree >------------------------------------------------
void XmlProcessing::DocumentBuilder::ASTbuilder(sPtr& pDocElement_, sPtr& rootEle, sPtrVector& elements, bool isDeclarEle)
{
	sPtr declarEle;
	if (!isDeclarEle)
	{
		declarEle = makeXmlDeclarElement();
		declarEle->addAttrib("version", "1.0");
		pDocElement_->addChild(declarEle);
	}
	for (auto elem : elements){
		if (elem)
			pDocElement_->addChild(elem);
	}
	if (rootEle && isDeclarEle){
		pDocElement_->addChild(rootEle);
	}
}

//----< Parsing xml file and string and returning shared ptr >-------------------------------
XmlProcessing::DocumentBuilder::sPtr XmlProcessing::DocumentBuilder::parse(std::string path, bool checkFile)
{
	Toker toker(path, checkFile);
	toker.setMode(Toker::xml);
	XmlParts parts(&toker);
	sPtrVector elements;
	sPtr declarEleTemp, rootEle;
	bool isDeclarEle = false;
	sPtr pDocElement_ = makeDocElement(declarEleTemp);
	while (parts.get())
	{
		sPtr declarEle, ProcInstrEle, commentEle;

		std::string part = parts.show();
		size_t start = part.find("< ?");
		size_t end = part.find_last_of("? >");
		if (start != std::string::npos && end != std::string::npos)
		{
			if (part.find("xml -") == std::string::npos){
				parsebyElement(declarEle, parts, XmlDeclarElement);
				isDeclarEle = true;
				elements.push_back(declarEle);
			}
			else{
				parsebyElement(ProcInstrEle, parts, ProcInstrElement);
				elements.push_back(ProcInstrEle);
			}
			parts.remove(parts.show());
		}
		else{
			if (part.find("< ! --") != std::string::npos ){
				parsebyElement(commentEle, parts, CommentElement);
				elements.push_back(commentEle);
				parts.remove(parts.show());
			}
			else{
				parsebyElement(rootEle, parts, TaggedElement);
			}
		}
	}
	ASTbuilder(pDocElement_, rootEle, elements, isDeclarEle);
	return pDocElement_;
}


#ifdef TEST_DOCBUILDER
//----< main function for Document Builder >------------------------------------------------
int main(int argc, char* argv[])
{
    char *argv1[] = { "/f", "../../TEST_FOLDER_XMLDocument/LectureNote.xml" };
	using sPtr = std::shared_ptr < AbstractXmlElement >;
	argc = 2;
	try{
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
				        XmlProcessing::DocumentBuilder docbuilder;
				sPtr pDocElement_;       
				pDocElement_ = docbuilder.parse(TestDocXML, false);
				std::cout << " AST tree is :" << pDocElement_->toString() << "\n\n";
			}else if (tmp == "/f" || tmp == "/F"){
				XmlProcessing::DocumentBuilder docbuilder;
				sPtr pDocElement_;
				pDocElement_ = docbuilder.parse(tmpString, true);
				std::cout << " AST tree is :\n" << pDocElement_->toString() <<"\n\n";
			}
		}
	}
	catch (std::exception& ex){
		std::cout << "\n\n    " << ex.what() << "\n\n";
	}
	return 0;
}
#endif

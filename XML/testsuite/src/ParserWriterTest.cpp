//
// ParserWriterTest.cpp
//
// $Id: //poco/1.3/XML/testsuite/src/ParserWriterTest.cpp#4 $
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "ParserWriterTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/SAX/InputSource.h"
#include "Poco/XML/XMLWriter.h"
#include <sstream>


using Poco::XML::DOMParser;
using Poco::XML::DOMWriter;
using Poco::XML::XMLReader;
using Poco::XML::XMLWriter;
using Poco::XML::Document;
using Poco::XML::AutoPtr;
using Poco::XML::InputSource;


ParserWriterTest::ParserWriterTest(const std::string& name): CppUnit::TestCase(name)
{
}


ParserWriterTest::~ParserWriterTest()
{
}


void ParserWriterTest::testParseWriteXHTML()
{
	std::ostringstream ostr;
	
	DOMParser parser;
	parser.setFeature(XMLReader::FEATURE_NAMESPACE_PREFIXES, false);
	DOMWriter writer;
	AutoPtr<Document> pDoc = parser.parseString(XHTML);
	writer.writeNode(ostr, pDoc);
	
	std::string xml = ostr.str();
	assert (xml == XHTML);
}


void ParserWriterTest::testParseWriteXHTML2()
{
	std::ostringstream ostr;
	
	DOMParser parser;
	parser.setFeature(XMLReader::FEATURE_NAMESPACE_PREFIXES, true);
	DOMWriter writer;
	AutoPtr<Document> pDoc = parser.parseString(XHTML2);
	writer.writeNode(ostr, pDoc);
	
	std::string xml = ostr.str();
	assert (xml == XHTML2);
}


void ParserWriterTest::testParseWriteSimple()
{
	static const std::string simple =
		"<config>\n"
		"\t<prop1>value1</prop1>\n"
		"\t<prop2>value2</prop2>\n"
		"</config>\n";

	std::istringstream istr(simple);
	std::ostringstream ostr;

	DOMParser parser;
	parser.setFeature(DOMParser::FEATURE_FILTER_WHITESPACE, true);
	parser.setFeature(XMLReader::FEATURE_NAMESPACE_PREFIXES, false);
	DOMWriter writer;
	writer.setNewLine("\n");
	writer.setOptions(XMLWriter::PRETTY_PRINT);
	InputSource source(istr);
	AutoPtr<Document> pDoc = parser.parse(&source);
	writer.writeNode(ostr, pDoc);

	unsigned int numChildren = 0;
	Poco::XML::Node* child = pDoc->documentElement()->firstChild();
	while (child) {
		numChildren++;
		child = child->nextSibling();
	}
	assert (numChildren == 2);

	std::string xml = ostr.str();
	assert (xml == simple);
}


void ParserWriterTest::setUp()
{
}


void ParserWriterTest::tearDown()
{
}


CppUnit::Test* ParserWriterTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("ParserWriterTest");

	CppUnit_addTest(pSuite, ParserWriterTest, testParseWriteXHTML);
	CppUnit_addTest(pSuite, ParserWriterTest, testParseWriteXHTML2);
	CppUnit_addTest(pSuite, ParserWriterTest, testParseWriteSimple);

	return pSuite;
}


const std::string ParserWriterTest::XHTML =
	"<!--\n"
	"\tThis is a comment.\n"
	"-->"
	"<ns1:html xml:lang=\"en\" xmlns:ns1=\"http://www.w3.org/1999/xhtml\">\n"
	"\t<ns1:head>\n"
	"\t\t<ns1:link href=\"styles.css\" rel=\"stylesheet\" type=\"text/css\"/>\n"
	"\t\t<?xml-stylesheet href=\"styles.css\" type=\"text/css\"?>\n"
	"\t\t<ns1:title>A XHTML Example</ns1:title>\n"
	"\t</ns1:head>\n"
	"\t<ns1:body>\n"
	"\t\t<ns1:h1>XHTML Example</ns1:h1>\n"
	"\t\t<ns1:p>This is a XHTML example page.</ns1:p>\n"
	"\t\t<ns1:img alt=\"Example Picture\" border=\"0\" height=\"192\" src=\"example.gif\" width=\"256\"/>\n"
	"\t\t<![CDATA[\n"
	"\t\tThe following <tag attr=\"value\">is inside a CDATA section</tag>.\n"
	"\t\t]]>\n"
	"\t</ns1:body>\n"
	"</ns1:html>";


const std::string ParserWriterTest::XHTML2 =
	"<!--\n"
	"\tThis is a comment.\n"
	"-->"
	"<xns:html xml:lang=\"en\" xmlns:xns=\"http://www.w3.org/1999/xhtml\">\n"
	"\t<xns:head>\n"
	"\t\t<xns:link href=\"styles.css\" rel=\"stylesheet\" type=\"text/css\"/>\n"
	"\t\t<?xml-stylesheet href=\"styles.css\" type=\"text/css\"?>\n"
	"\t\t<xns:title>A XHTML Example</xns:title>\n"
	"\t</xns:head>\n"
	"\t<xns:body>\n"
	"\t\t<xns:h1>XHTML Example</xns:h1>\n"
	"\t\t<xns:p>This is a XHTML example page.</xns:p>\n"
	"\t\t<xns:img alt=\"Example Picture\" border=\"0\" height=\"192\" src=\"example.gif\" width=\"256\"/>\n"
	"\t\t<![CDATA[\n"
	"\t\tThe following <tag attr=\"value\">is inside a CDATA section</tag>.\n"
	"\t\t]]>\n"
	"\t</xns:body>\n"
	"</xns:html>";


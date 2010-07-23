//
// ConfigurationMapperTest.cpp
//
// $Id: //poco/1.3/Util/testsuite/src/ConfigurationMapperTest.cpp#2 $
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


#include "ConfigurationMapperTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/Util/ConfigurationMapper.h"
#include "Poco/Util/MapConfiguration.h"
#include "Poco/AutoPtr.h"
#include "Poco/Exception.h"
#include <algorithm>


using Poco::Util::AbstractConfiguration;
using Poco::Util::ConfigurationMapper;
using Poco::Util::MapConfiguration;
using Poco::AutoPtr;


ConfigurationMapperTest::ConfigurationMapperTest(const std::string& name): AbstractConfigurationTest(name)
{
}


ConfigurationMapperTest::~ConfigurationMapperTest()
{
}


void ConfigurationMapperTest::testMapper1()
{
	AutoPtr<AbstractConfiguration> pConf = createConfiguration();
	AutoPtr<AbstractConfiguration> pMapper = new ConfigurationMapper("", "", pConf);
	assert (pMapper->hasProperty("prop5.string1"));
	assert (pMapper->hasProperty("prop5.string1"));

	AbstractConfiguration::Keys keys;
	pMapper->keys(keys);
	assert (keys.size() == 13);
	assert (std::find(keys.begin(), keys.end(), "prop5") != keys.end());

	pMapper->keys("prop5", keys);
	assert (keys.size() == 4);
	assert (std::find(keys.begin(), keys.end(), "string1") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "string2") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "sub1") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "sub2") != keys.end());
	
	assert (pMapper->getString("prop5.string1") == "foo");
	assert (pMapper->getString("prop5.sub1.string1") == "FOO");
	
	pMapper->setString("prop5.string3", "baz");
	assert (pMapper->getString("prop5.string3") == "baz");
	assert (pConf->getString("prop5.string3") == "baz");

	pMapper->remove("prop5.string3");
	assert (!pMapper->hasProperty("prop5.string3"));
	assert (!pConf->hasProperty("prop5.string3"));
}


void ConfigurationMapperTest::testMapper2()
{
	AutoPtr<AbstractConfiguration> pConf = createConfiguration();
	AutoPtr<AbstractConfiguration> pMapper = new ConfigurationMapper("prop5", "root.conf", pConf);

	assert (pMapper->hasProperty("root.conf.string1"));
	assert (pMapper->hasProperty("root.conf.string2"));

	AbstractConfiguration::Keys keys;
	pMapper->keys(keys);
	assert (keys.size() == 1);
	assert (std::find(keys.begin(), keys.end(), "root") != keys.end());

	pMapper->keys("root", keys);
	assert (keys.size() == 1);
	assert (std::find(keys.begin(), keys.end(), "conf") != keys.end());

	pMapper->keys("root.conf", keys);
	assert (keys.size() == 4);
	assert (std::find(keys.begin(), keys.end(), "string1") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "string2") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "sub1") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "sub2") != keys.end());

	assert (pMapper->getString("root.conf.string1") == "foo");
	assert (pMapper->getString("root.conf.sub1.string1") == "FOO");
	
	pMapper->setString("root.conf.string3", "baz");
	assert (pMapper->getString("root.conf.string3") == "baz");
	assert (pConf->getString("prop5.string3") == "baz");

	pMapper->remove("root.conf.string3");
	assert (!pMapper->hasProperty("root.conf.string3"));
	assert (!pConf->hasProperty("prop5.string3"));
}


void ConfigurationMapperTest::testMapper3()
{
	AutoPtr<AbstractConfiguration> pConf = createConfiguration();
	AutoPtr<AbstractConfiguration> pMapper = new ConfigurationMapper("", "root", pConf);

	assert (pMapper->hasProperty("root.prop5.string1"));
	assert (pMapper->hasProperty("root.prop5.string2"));

	AbstractConfiguration::Keys keys;
	pMapper->keys(keys);
	assert (keys.size() == 1);
	assert (std::find(keys.begin(), keys.end(), "root") != keys.end());

	pMapper->keys("root", keys);
	assert (keys.size() == 13);
	assert (std::find(keys.begin(), keys.end(), "prop5") != keys.end());

	pMapper->keys("root.prop5", keys);
	assert (keys.size() == 4);
	assert (std::find(keys.begin(), keys.end(), "string1") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "string2") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "sub1") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "sub2") != keys.end());
	
	assert (pMapper->getString("root.prop5.string1") == "foo");
	assert (pMapper->getString("root.prop5.sub1.string1") == "FOO");
	
	pMapper->setString("root.prop5.string3", "baz");
	assert (pMapper->getString("root.prop5.string3") == "baz");
	assert (pConf->getString("prop5.string3") == "baz");

	pMapper->remove("root.prop5.string3");
	assert (!pMapper->hasProperty("root.prop5.string3"));
	assert (!pConf->hasProperty("prop5.string3"));
}


void ConfigurationMapperTest::testMapper4()
{
	AutoPtr<AbstractConfiguration> pConf = createConfiguration();
	AutoPtr<AbstractConfiguration> pMapper = new ConfigurationMapper("prop5", "", pConf);

	assert (pMapper->hasProperty("string1"));
	assert (pMapper->hasProperty("string2"));

	AbstractConfiguration::Keys keys;
	pMapper->keys(keys);
	assert (keys.size() == 4);
	assert (std::find(keys.begin(), keys.end(), "string1") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "string2") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "sub1") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "sub2") != keys.end());
	
	assert (pMapper->getString("string1") == "foo");
	assert (pMapper->getString("sub1.string1") == "FOO");
	
	pMapper->setString("string3", "baz");
	assert (pMapper->getString("string3") == "baz");
	assert (pConf->getString("prop5.string3") == "baz");

	pMapper->remove("string3");
	assert (!pMapper->hasProperty("string3"));
	assert (!pConf->hasProperty("prop5.string3"));
}


AbstractConfiguration* ConfigurationMapperTest::allocConfiguration() const
{
	return new MapConfiguration;
}


void ConfigurationMapperTest::setUp()
{
}


void ConfigurationMapperTest::tearDown()
{
}


CppUnit::Test* ConfigurationMapperTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("ConfigurationMapperTest");

	AbstractConfigurationTest_addTests(pSuite, ConfigurationMapperTest);
	CppUnit_addTest(pSuite, ConfigurationMapperTest, testMapper1);
	CppUnit_addTest(pSuite, ConfigurationMapperTest, testMapper2);
	CppUnit_addTest(pSuite, ConfigurationMapperTest, testMapper3);
	CppUnit_addTest(pSuite, ConfigurationMapperTest, testMapper4);

	return pSuite;
}

#include "stdafx.h"
#include "TestClass.h"
#include "Tests.h"
#include <exception>

void TestClass::addResult(const char *name, bool status)
{
	printf("    %-40s  [%s]\n", name, status ? "pass" : "fail");
}

void TestClass::addResult(std::string &name, bool status)
{
	addResult(name.c_str(), status);
}

void TestClass::run()
{
	try
	{
		printf("Testing:\n");

		printf("- CameraDriver:\n");
		TestCameraDriver testCameraDriver;
	
		printf("- CameraFile:\n");
		TestCameraFile testCameraFile;
	
		printf("- Detector:\n");
		TestDetector testDetector;
		printf("End.\n");
	}
	catch (std::exception &e)
	{
		printf("Test: exception caught (line %u):\n%s\n", __LINE__, e.what());
	}
}
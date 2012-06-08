#include "stdafx.h"
#include "TestCameraDriver.h"
#include "CameraDriver.h"

TestCameraDriver::TestCameraDriver()
{
	testFactory();
};

void TestCameraDriver::testFactory()
{
	std::unique_ptr<CameraDriver> camera;
	camera.reset(CameraDriver::factory("", ""));
	addResult("creating driver", (bool) camera);
	
	camera.reset(CameraDriver::factory("unknown", ""));
	addResult("creating invalid driver", camera.get() && ! camera->isValid());
}
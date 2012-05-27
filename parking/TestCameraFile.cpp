#include "stdafx.h"
#include "TestCameraFile.h"
#include "CameraFile.h"
#include <cstdio>
#include <fstream>

TestCameraFile::TestCameraFile()
{
	testFactory();
	testImageLoading();
};

void TestCameraFile::testFactory()
{
	std::unique_ptr<CameraDriver> camera;
	
	camera.reset(CameraDriver::factory("file", ""));
	addResult("creating file driver", (bool) camera);
}

void TestCameraFile::testImageLoading()
{
	std::unique_ptr<CameraDriver> camera;
	
	camera.reset(CameraDriver::factory("file", ""));
	addResult("loading invalid file", (bool) camera && ! camera->isValid());

	std::string filename = "image.tmp";
	// create if doesnt exists
	std::fstream fs(filename, std::ios::out | std::ios::trunc);
	fs << std::flush;
	fs.close();

	camera.reset(CameraDriver::factory("file", filename));
	if ( ! camera)
	{
		return;
	}

	addResult("loading valid file", camera->isValid());
	addResult("getting temporary filename", camera->getImagePath() == filename);
}
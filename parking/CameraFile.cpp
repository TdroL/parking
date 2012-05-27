#include "stdafx.h"
#include "CameraFile.h"
#include <fstream>

std::string CameraFile::getImagePath()
{
	return path;
}

bool CameraFile::isValid() const
{
	std::fstream fs(path);
	fs.clear();

	return fs.is_open();
}
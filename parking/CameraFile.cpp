#include "stdafx.h"
#include "CameraFile.h"
#include <cstdio>

std::string CameraFile::getImagePath()
{
	return path;
}

bool CameraFile::isValid()
{
	FILE *f;
	bool status = false;
#ifdef _WIN32
	status = (fopen_s(&f, getImagePath().c_str(), "r") == 0);
#else
	status = ((f = fopen(getImagePath().c_str(), "r")) != 0);
#endif
	fclose(f);
	return status;
}
#include "stdafx.h"
#include "CameraDriver.h"
#include "CameraFile.h"

CameraDriver * CameraDriver::factory(std::string const &type, std::string const &address)
{
	if (type == "file")
	{
		return new CameraFile(address);
	}

	return new CameraDriver;
}

CameraDriver * CameraDriver::factory(const char *type, const char *address)
{
	return CameraDriver::factory(std::string(type), std::string(address));
}

CameraDriver * CameraDriver::factory(std::string const &type, const char *address)
{
	return CameraDriver::factory(std::string(type), std::string(address));
}
	
CameraDriver * CameraDriver::factory(const char *type, std::string const &address)
{
	return CameraDriver::factory(std::string(type), std::string(address));
}
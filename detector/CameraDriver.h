#ifndef CAMERA_DRIVER_H
#define CAMERA_DRIVER_H

#include <string>

class CameraDriver
{
public:
	static CameraDriver * factory(std::string const &type, std::string const &address);
	static CameraDriver * factory(const char *type, const char *address);
	static CameraDriver * factory(std::string const &type, const char *address);
	static CameraDriver * factory(const char *type, std::string const &address);

	virtual std::string getImagePath();
	virtual bool isValid();
	virtual ~CameraDriver() {};
};

#endif
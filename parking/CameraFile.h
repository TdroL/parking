#ifndef CAMERAFILE_H
#define CAMERAFILE_H

#include "CameraDriver.h"

class CameraFile : public CameraDriver
{
public:
	CameraFile(std::string const &address) : path(address) {}
	std::string getImagePath();
	bool isValid() const;
protected:
	std::string path;
};

#endif
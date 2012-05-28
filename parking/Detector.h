#ifndef DETECTOR_H
#define DETECTOR_H

#pragma warning(disable: 4996)

#include <string>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

enum SpotStatus {
	Free,
	Occupied,
	Blocked
};

struct CountStats {
	unsigned int count;
	unsigned int scanned;
};

struct Spot
{
	cv::Point corners[4];
	SpotStatus status;
};

class Detector
{
public:
	Detector();
	~Detector();
	bool loadImage(std::string const &path, double threshold_high = 100.0, double threshold_low = 3.0);
	void loadSpots(Spot *spots, size_t spots_length);
	unsigned int findFreeSpots(double threshold = 0.125);
	CountStats countPoints(size_t index);

	void displayGrid();

	cv::Mat img;
	Spot *spots;
	size_t spots_length;
};


#endif
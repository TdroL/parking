#ifndef DETECTOR_H
#define DETECTOR_H

#pragma warning(disable: 4996)

#include <string>
#include <vector>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

struct CountStats {
	CountStats(unsigned int count_, unsigned int scanned_) : count(count_), scanned(scanned_) {}

	unsigned int count;
	unsigned int scanned;
};

enum SpotStatus {
	Free,
	Occupied,
	Blocked
};

struct Spot
{
	unsigned int id;
	cv::Point corners[4];
	SpotStatus status;
	SpotStatus original_status;

	Spot() {}
	Spot(const Spot &spot)
	{
		for (size_t i = 0; i < 4; i++)
		{
			corners[i].x = spot.corners[i].x;
			corners[i].y = spot.corners[i].y;
		}
	}

	void resetStatus(int status_)
	{
		switch (status_)
		{
		case 1:
			original_status = status = Free;
			return;
		case 2:
			original_status = status = Occupied;
			return;
		case 3:
			original_status = status = Blocked;
			return;
		}
	}

	void setStatus(int status_)
	{
		switch (status_)
		{
		case 1:
			status = Free;
			return;
		case 2:
			status = Occupied;
			return;
		case 3:
			status = Blocked;
			return;
		}
	}

	void setStatus(SpotStatus status_)
	{
		status = status_;
	}
};


class Detector
{
public:
	double scale;
	cv::Mat img;

	bool loadImage(std::string const &path, double threshold_low = 33.0, double threshold_high = 100.0, double scale = 1.0);
	void findFreeSpots(std::vector<Spot *> &spots, double threshold = 0.125);
	bool isPointInside(cv::Point const (&corners)[4], unsigned int x, unsigned int y);
	void scalePoints(cv::Point (&corners)[4]);
	CountStats countPoints(cv::Point const (&corners)[4]);

	void displayGrid(std::vector<Spot *> &spots);
	void drawGrid(cv::Mat &img, std::vector<Spot *> &spots);
};


#endif
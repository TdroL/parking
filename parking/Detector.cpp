#include "stdafx.h"
#include "Detector.h"
#include <algorithm>

Detector::Detector()
	: spots(nullptr), spots_length(0) 
{}

Detector::~Detector()
{
	if (spots != nullptr)
	{
		delete[] spots;
	}
}

bool Detector::loadImage(std::string const &path, double threshold1, double threshold2)
{
	// img.deallocate();
	cv::Mat src = cv::imread(path, 0);

	if ( ! src.data)
	{
		return false;
	}

	Canny(src, img, threshold1, threshold2);

	return (img.data != nullptr);
}

void Detector::loadSpots(Spot *spots_, size_t spots_length_)
{
	if (spots != nullptr)
	{
		delete[] spots;
	}

	spots = spots_;
	spots_length = spots_length_;
}

unsigned int Detector::findFreeSpots(double threshold)
{
	unsigned int count = 0;

	for (size_t i = 0; i < spots_length; i++)
	{
		Spot &spot = spots[i];
		
		if (spot.status == Blocked)
		{
			continue;
		}
		
		CountStats const &stats = countPoints(i);

		double factor = (double) stats.count / (double) stats.scanned;

		if (factor > threshold)
		{
			spot.status = Occupied;
		}
		else
		{
			count++;
			spot.status = Free;
		}
	}

	return count;
}

CountStats Detector::countPoints(size_t index)
{
	cv::Point const (&corners)[4] = spots[index].corners;

	unsigned int xs[4] = { corners[0].x, corners[1].x, corners[2].x, corners[3].x };
	unsigned int ys[4] = { corners[0].y, corners[1].y, corners[2].y, corners[3].y };

	cv::Rect rect;
	rect.x      = *std::min_element(xs, xs + 4);
	rect.width  = *std::max_element(xs, xs + 4);
	rect.y      = *std::min_element(ys, ys + 4);
	rect.height = *std::max_element(ys, ys + 4);

	auto sgn = [] (int a) -> int
	{
		return (a > 0) ? 1 : ((a < 0) ? -1 : 0);
	};

	auto isPointInside = [&corners, &sgn] (unsigned int x, unsigned int y) -> bool
	{
		int last_side = 0;

		for (size_t i = 0; i < 4; i++)
		{
			int x0 = corners[(i + 0) % 4].x;
			int x1 = corners[(i + 1) % 4].x;

			int y0 = corners[(i + 0) % 4].y;
			int y1 = corners[(i + 1) % 4].y;

			int side = (y - y0) * (x1 - x0) - (x - x0) * (y1 - y0);

			if (side == 0)
			{
				continue;
			}

			if (last_side != 0 && sgn(last_side) != sgn(side))
			{
				return false;
			}

			last_side = side;
		}

		return true;
	};

	unsigned int count = 0;
	unsigned int scanned = 0;

	for (int x = rect.x; x < rect.width; x++)
	{
		for (int y = rect.y; y < rect.height; y++)
		{
			if (isPointInside(x, y))
			{
				scanned++;

				if (img.at<uchar>(y, x) == 0xff)
				{
					count++;
				}
			}
		}
	}

	CountStats stats = { count, scanned };
	return stats;
}

void Detector::displayGrid()
{
	cv::Mat dst;
	cvtColor(img, dst, CV_GRAY2RGB);
	
	cv::Scalar color_free(0, 255, 0);
	cv::Scalar color_occupied(255, 0, 0);
	cv::Scalar color_blocked(0, 0, 255);

	auto draw_rect = [] (cv::Mat &img, cv::Point corners[4], cv::Scalar &color)
	{
		cv::line(img, corners[0], corners[1], color, 2, CV_AA);
		cv::line(img, corners[1], corners[2], color, 2, CV_AA);
		cv::line(img, corners[2], corners[3], color, 2, CV_AA);
		cv::line(img, corners[3], corners[0], color, 2, CV_AA);
	};

	for (size_t i = 0; i < spots_length; i++)
	{
		Spot &spot = spots[i];

		switch (spot.status)
		{
		case Free:
			draw_rect(dst, spot.corners, color_free);
			break;
		case Occupied:
			draw_rect(dst, spot.corners, color_occupied);
			break;
		case Blocked:
			draw_rect(dst, spot.corners, color_blocked);
			break;
		}
	}

	cv::namedWindow("Source Canny", 1);
    cv::imshow("Source Canny", dst);

	cv::waitKey(0);
}
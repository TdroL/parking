#include "stdafx.h"
#include "Detector.h"
#include <algorithm>

bool Detector::loadImage(std::string const &path, double threshold_low, double threshold_high, double scale_)
{
	// img.deallocate();
	cv::Mat src = cv::imread(path, 0);

	if ( ! src.data)
	{
		return false;
	}

	scale = scale_;

	if (scale != 1.0)
	{
		cv::resize(src, src, cv::Size(), scale, scale);
	}

	cv::Canny(src, img, threshold_low, threshold_high);

	return (img.data != nullptr);
}

void Detector::scalePoints(cv::Point (&corners)[4])
{
	for (size_t i = 0; i < 4; i++)
	{
		corners[i].x = (int) (corners[i].x * scale);
		corners[i].y = (int) (corners[i].y * scale);
	}
}

void Detector::findFreeSpots(std::vector<Spot *> &spots, double threshold)
{
	for (size_t i = 0, l = spots.size(); i < l; i++)
	{
		Spot &spot = *spots[i];

		if (spot.status == Blocked)
		{
			continue;
		}

		cv::Point corners[4] = {
			spot.corners[0],
			spot.corners[1],
			spot.corners[2],
			spot.corners[3],
		};

		if (scale != 1.0)
		{
			scalePoints(corners);
		}

		CountStats const &stats = countPoints(corners);

		double factor = (double) stats.count / (double) stats.scanned;

		if (factor > threshold)
		{
			spot.setStatus(Occupied);
		}
		else
		{
			spot.setStatus(Free);
		}
	}
}

bool Detector::isPointInside(cv::Point const (&corners)[4], unsigned int x, unsigned int y)
{
	auto sgn = [] (int a) -> int
	{
		return (a > 0) ? 1 : ((a < 0) ? -1 : 0);
	};
	
	// http://local.wasp.uwa.edu.au/~pbourke/geometry/insidepoly/
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

CountStats Detector::countPoints(cv::Point const (&corners)[4])
{
	unsigned int xs[4] = { corners[0].x, corners[1].x, corners[2].x, corners[3].x };
	unsigned int ys[4] = { corners[0].y, corners[1].y, corners[2].y, corners[3].y };

	cv::Rect rect;
	rect.x      = *std::min_element(xs, xs + 4);
	rect.width  = *std::max_element(xs, xs + 4);
	rect.y      = *std::min_element(ys, ys + 4);
	rect.height = *std::max_element(ys, ys + 4);

	unsigned int count = 0;
	unsigned int scanned = 0;

	for (int x = rect.x; x < rect.width; x++)
	{
		for (int y = rect.y; y < rect.height; y++)
		{
			if (isPointInside(corners, x, y))
			{
				scanned++;

				if (*img.ptr(y, x) == (uchar) 0xff)
				{
					count++;
				}
			}
		}
	}

	return CountStats(count, scanned);
}

void Detector::displayGrid(std::vector<Spot *> &spots)
{
	cv::Mat dst;
	cvtColor(img, dst, CV_GRAY2RGB);

	drawGrid(dst, spots);

	cv::namedWindow("Source Canny", 1);
    cv::imshow("Source Canny", dst);

	cv::waitKey(0);
}

void Detector::drawGrid(cv::Mat &img, std::vector<Spot *> &spots)
{
	cv::Scalar color_free(0, 255, 0);
	cv::Scalar color_occupied(0, 128, 255);
	cv::Scalar color_blocked(0, 0, 255);

	auto draw_rect = [&img] (cv::Point corners[4], cv::Scalar &color)
	{
		cv::line(img, corners[0], corners[1], color, 2, CV_AA);
		cv::line(img, corners[1], corners[2], color, 2, CV_AA);
		cv::line(img, corners[2], corners[3], color, 2, CV_AA);
		cv::line(img, corners[3], corners[0], color, 2, CV_AA);
	};

	for (size_t i = 0, l = spots.size(); i < l; i++)
	{
		Spot &spot = *spots[i];

		cv::Point corners[4] = {
			spot.corners[0],
			spot.corners[1],
			spot.corners[2],
			spot.corners[3],
		};

		if (scale != 1.0)
		{
			scalePoints(corners);
		}

		switch (spot.status)
		{
		case Free:
			draw_rect(corners, color_free);
			break;
		case Occupied:
			draw_rect(corners, color_occupied);
			break;
		case Blocked:
			draw_rect(corners, color_blocked);
			break;
		}
	}
}
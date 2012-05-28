// parking.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include "Camera.h"
#include "Detector.h"
#ifdef RUN_TESTS
	#include "Tests.h"
#endif
using namespace std;

/*
#include <cstdio>
#include <fstream> 
#include <cmath>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
*/
/*
using namespace cv;

typedef unsigned int uint;

size_t corners_size = 7;
uint padding = 5;

Scalar color_free(0, 255, 0);
Scalar color_taken(0, 0, 255);

int sgn(int a)
{
	return (a > 0) ? 1 : (a < 0) ? -1 : 0;
}

void draw_rect(Mat &img, uint corners[][2], Scalar &color);
double count_pixels(Mat &img, uint a[2], uint b[2], Scalar &color);
double length(uint a[2], uint b[2]);
size_t file_length(fstream &file);
*/
static unsigned int corners[][4][2] = {
	{ {516, 462}, {548, 480}, {493, 541}, {461, 523} },
	{ {553, 483}, {586, 502}, {531, 564}, {498, 545} },
	{ {457, 528}, {498, 547}, {433, 611}, {401, 592} },
	{ {494, 550}, {527, 569}, {471, 633}, {438, 614} },
	{ {217, 601}, {249, 621}, {192, 688}, {160, 668} },
	{ {255, 623}, {288, 643}, {231, 711}, {198, 691} },
	{ {293, 645}, {326, 665}, {269, 733}, {236, 713} }
};

int main(int argc, _TCHAR* argv[])
{
#ifdef RUN_TESTS
	TestClass tests;
	tests.run();
	system("pause");
	//return EXIT_SUCCESS;
#endif

	string camera_address = "C:/Users/tdroL/Documents/Visual Studio 2010/Projects/parking/assets/preview1.jpg";
	unique_ptr<CameraDriver> camera(CameraDriver::factory("file", camera_address));

	if ( ! camera->isValid())
	{
		printf("Failed to load image from camera\n");
		system("pause");
		return EXIT_FAILURE;
	}

	Detector detector;

	if ( ! detector.loadImage(camera->getImagePath()))
	{
		printf("Failed to load image from temporary file\n");
		system("pause");
		return EXIT_FAILURE;
	}

	size_t spots_length = 7;
	Spot *spots = new Spot[spots_length];

	for (size_t i = 0; i < spots_length; i++)
	{
		Spot &spot = spots[i];

		for (size_t j = 0; j < 4; j++)
		{
			spot.corners[j].x = corners[i][j][0] / 2;
			spot.corners[j].y = corners[i][j][1] / 2;
		}

		spots[i].status = Free;
	}

	detector.loadSpots(spots, spots_length);

	printf("findFreeSpots() = %u\n", detector.findFreeSpots());

	detector.displayGrid();
/*
	fstream info_file("../assets/parking-1/info.txt", ios::out);

	if ( ! info_file.is_open())
	{
		printf("Nie mozna otworzyc pliku info.txt\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	uint cam_count = 0;

	while ( ! info_file.eof())
	{
		char buffer[256];
		info_file.getline(buffer, 256);
		
		if (sscanf(buffer, "cams %u", &cam_count) && cam_count > 0)
		{
			break;
		}
	}

	info_file.close();

	if (cam_count == 0)
	{
		printf("Brak kamer\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	for (int k = 1; k <= 1 cam_count; k++)
	{
		fstream cam_info("", ios::in);
	}

    const char *img = "C:/Users/tdroL/Documents/Visual Studio 2010/Projects/parking/assets/preview1.jpg";
    Mat src = imread(img, 0);

    if ( ! src.data)
    {
		printf("Nie mozna bylo wczytac obrazu");
		system("pause");
		exit(EXIT_FAILURE);
	}

	Mat dst;

	Canny(src, dst, 1, 100, 3);
	cvtColor(src, src, CV_GRAY2RGB);

	vector<Vec4i> lines;
	HoughLinesP(dst, lines, 1, CV_PI/180, 25, 10, 4);

	for (size_t i = 0; i < lines.size(); i++)
    {
        line(src, Point(lines[i][0], lines[i][1]),
			      Point(lines[i][2], lines[i][3]), 
				  color_line, 2, 0);
    }

	cvtColor(dst, dst, CV_GRAY2RGB);

	for (size_t i = 0; i < corners_size; i++)
	{
		double count = 0;

		count += count_pixels(src, corners[i][0], corners[i][2], color_line); // 1
		count += count_pixels(src, corners[i][1], corners[i][3], color_line); // 2

		uint a[2], b[2], c[2], d[2];

		a[0] = (corners[i][0][0] + corners[i][1][0]) / 2;
		a[1] = (corners[i][0][1] + corners[i][1][1]) / 2;

		b[0] = (corners[i][1][0] + corners[i][2][0]) / 2;
		b[1] = (corners[i][1][1] + corners[i][2][1]) / 2;

		c[0] = (corners[i][2][0] + corners[i][3][0]) / 2;
		c[1] = (corners[i][2][1] + corners[i][3][1]) / 2;

		d[0] = (corners[i][3][0] + corners[i][0][0]) / 2;
		d[1] = (corners[i][3][1] + corners[i][0][1]) / 2;

		count += count_pixels(src, a, b, color_line); // 3
		count += count_pixels(src, a, c, color_line); // 4
		count += count_pixels(src, a, d, color_line); // 5

		count += count_pixels(src, b, c, color_line); // 6
		count += count_pixels(src, b, d, color_line); // 7

		count += count_pixels(src, c, d, color_line); // 8

		count += count_pixels(src, a, corners[i][2], color_line); // 9
		count += count_pixels(src, a, corners[i][3], color_line); // 10

		count += count_pixels(src, b, corners[i][0], color_line); // 11
		count += count_pixels(src, b, corners[i][3], color_line); // 12

		count += count_pixels(src, c, corners[i][0], color_line); // 13
		count += count_pixels(src, c, corners[i][1], color_line); // 14

		count += count_pixels(src, d, corners[i][1], color_line); // 15
		count += count_pixels(src, d, corners[i][2], color_line); // 16

		count /= 16;

		printf("Miejsce #%i: %f\n", i, count);

		if (count <= 0.2)
		{
			draw_rect(dst, corners[i], color_free);
		}
		else
		{
			draw_rect(dst, corners[i], color_taken);
		}
	}

	namedWindow("Source Gray", 1);
    imshow("Source Gray", src);

	namedWindow("Source Canny", 1);
    imshow("Source Canny", dst);

	waitKey(0);
*/
    return EXIT_SUCCESS;
}
/*
double count_pixels(Mat &img, uint a[2], uint b[2], Scalar &color)
{
	uint found = 0;
	uint checked = 0;

	uint lx = abs((int) a[0] - (int) b[0]);
	uint ly = abs((int) a[1] - (int) b[1]);

	int sgn_x = sgn((int) a[0] - (int) b[0]);
	int sgn_y = sgn((int) a[1] - (int) b[1]);

	uint step = 3;

	uint px = a[0], py = a[1];

	if (lx > ly)
	{
		// po osi X
		uint sy = step * ly / lx;

		for (uint i = 0, l = lx / 4; i < l; i++)
		{
			uchar *ptr = img.ptr(py, px);

			if (ptr[0] == color[0] && ptr[1] == color[1] && ptr[2] == color[2])
			{
				found++;
			}

			checked++;

			px += -sgn_x * 4;
			py += -sgn_y * sy;
		}
	}
	else
	{
		// po osi Y
		uint sx = step * lx / ly;

		for (uint i = 0, l = ly / 4; i < l; i++)
		{
			uchar *ptr = img.ptr(py, px);

			if (ptr[0] == color[0] && ptr[1] == color[1] && ptr[2] == color[2])
			{
				found++;
			}

			checked++;

			py += -sgn_y * 4;
			px += -sgn_x * sx;
		}
	}

	if (checked == 0)
	{
		return 0;
	}

	return (double) found / (double) checked;
}

void draw_rect(Mat &img, uint corners[][2], Scalar &color)
{
	line(img, Point(corners[0][0], corners[0][1]),
			  Point(corners[1][0], corners[1][1]), 
			  color, 2, CV_AA);

	line(img, Point(corners[1][0], corners[1][1]),
			  Point(corners[2][0], corners[2][1]), 
			  color, 2, CV_AA);

	line(img, Point(corners[2][0], corners[2][1]),
			  Point(corners[3][0], corners[3][1]), 
			  color, 2, CV_AA);

	line(img, Point(corners[3][0], corners[3][1]),
			  Point(corners[0][0], corners[0][1]), 
			  color, 2, CV_AA);
}

double length(uint a[2], uint b[2])
{
	uint p, q;

	p = a[0] - b[0];
	q = a[1] - b[1];

	return sqrt((double) (p*p + q*q));
}

size_t file_length(fstream &is)
{
	streampos current = is.tellg();

	is.seekg (0, ios::end);
	size_t length = is.tellg();
	
	is.seekg (0, current);

	return length;
}
*/
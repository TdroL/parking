// parking.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Camera.h"
#include "Detector.h"
#include <string>
#ifdef RUN_TESTS
	#include "Tests.h"
#endif

#ifdef _DEBUG
	#define EXIT_FAILURE_PAUSE (system("pause"), EXIT_FAILURE)
#else
	#define EXIT_FAILURE_PAUSE EXIT_FAILURE
#endif

using namespace std;

static string camera_type = "file";
static string camera_address = "C:/Users/tdroL/Documents/Visual Studio 2010/Projects/parking/assets/Parking-Lot.jpg"; //preview1.jpg";
static string output_file = "";
static double threshold_high = 100.0;
static double threshold_low = 33.0;
static double threshold_scan = 0.125;
static double scale = 1.0;
//preview1.jpg
/*
const size_t default_corners_length = 7;
static unsigned int default_corners[default_corners_length][4][2] = {
	{ {516/2, 462/2}, {548/2, 480/2}, {493/2, 541/2}, {461/2, 523/2} },
	{ {553/2, 483/2}, {586/2, 502/2}, {531/2, 564/2}, {498/2, 545/2} },
	{ {457/2, 528/2}, {498/2, 547/2}, {433/2, 611/2}, {401/2, 592/2} },
	{ {494/2, 550/2}, {527/2, 569/2}, {471/2, 633/2}, {438/2, 614/2} },
	{ {217/2, 601/2}, {249/2, 621/2}, {192/2, 688/2}, {160/2, 668/2} },
	{ {255/2, 623/2}, {288/2, 643/2}, {231/2, 711/2}, {198/2, 691/2} },
	{ {293/2, 645/2}, {326/2, 665/2}, {269/2, 733/2}, {236/2, 713/2} }
};
*/
//Parking-Lot.jpg
const size_t default_corners_length = 7;
static unsigned int default_corners[default_corners_length][4][2] = {
	{ {389, 326}, {446, 343}, {347, 393}, {289, 370} },
	{ {337, 309}, {384, 324}, {283, 368}, {234, 348} },
	{ {289, 294}, {332, 307}, {230, 346}, {185, 328} },
	{ {245, 280}, {283, 291}, {181, 326}, {141, 311} },
	{ {206, 268}, {240, 278}, {138, 309}, {105, 296} },
	{ {170, 257}, {200, 266}, {101, 294}, { 70, 282} },
	{ {138, 248}, {164, 256}, { 66, 280}, { 40, 271} },
}; 

bool is_num(const char *str)
{
	for (size_t i = 0, l = strlen(str); i < l; i++)
	{
		if (str[i] > '9' || str[i] < '0')
		{
			return false;
		}
	}
	return true;
}

int main(int argc, char *argv[])
{
#ifdef RUN_TESTS
	//TestClass tests;
	//tests.run();
	//system("pause");
	//return EXIT_SUCCESS;
#endif
	
	vector<Spot> corners;

	for (size_t i = 0; i < default_corners_length; i++)
	{
		Spot spot;

		for (size_t j = 0; j < 4; j++)
		{
			spot.corners[j].x = default_corners[i][j][0];
			spot.corners[j].y = default_corners[i][j][1];
		}
		
		corners.push_back(spot);
	}

	for (int i = 1; i < argc; i++)
	{
		string arg = argv[i];

		if (arg == "-a")
		{
			if (i + 1 >= argc || argv[i+1][0] == '-')
			{
				fprintf(stderr, " Usage: -a camera address\n");
				return EXIT_FAILURE_PAUSE;
			}

			camera_address = argv[++i];
		}
		else if (arg == "-t")
		{
			if (i + 1 >= argc || argv[i+1][0] == '-')
			{
				fprintf(stderr, " Usage: -t camera type\n");
				return EXIT_FAILURE_PAUSE;
			}

			camera_type = argv[++i];
		}
		else if (arg == "-o")
		{
			if (i + 1 >= argc || argv[i+1][0] == '-')
			{
				fprintf(stderr, " Usage: -o output file\n");
				return EXIT_FAILURE_PAUSE;
			}

			output_file = argv[++i];
		}
		else if (arg == "-h")
		{
			if (i + 1 >= argc || argv[i+1][0] == '-')
			{
				fprintf(stderr, " Usage: -h threshold high\n");
				return EXIT_FAILURE_PAUSE;
			}

			threshold_high = atof(argv[++i]);
		}
		else if (arg == "-l")
		{
			if (i + 1 >= argc || argv[i+1][0] == '-')
			{
				fprintf(stderr, " Usage: -l threshold low\n");
				return EXIT_FAILURE_PAUSE;
			}

			threshold_low = atof(argv[++i]);
		}
		else if (arg == "-c")
		{
			if (i + 1 >= argc || argv[i+1][0] == '-')
			{
				fprintf(stderr, " Usage: -c scale\n");
				return EXIT_FAILURE_PAUSE;
			}

			scale = atof(argv[++i]);
		}
		else if (arg == "-n")
		{
			if (i + 1 >= argc || argv[i+1][0] == '-')
			{
				fprintf(stderr, " Usage: -n threshold scan\n");
				return EXIT_FAILURE_PAUSE;
			}

			threshold_scan = atof(argv[++i]);
		}
		else if (arg == "-s")
		{
			if (i + 8 >= argc)
			{
				fprintf(stderr, " Usage: -s spots list, regexp format: \"(\\d+ \\d+ \\d+ \\d+)( \\d+ \\d+ \\d+ \\d+)*\"\n");
				return EXIT_FAILURE_PAUSE;
			}

			corners.clear();
			i++;

			size_t numbers_count = 0;

			for (int j = i; j < argc; j++)
			{
				if ( ! is_num(argv[j]))
				{
					break;
				}

				numbers_count++;
			}

			if (numbers_count == 0 || numbers_count % 8 != 0)
			{
				fprintf(stderr, " Error: spots list length must be divisible by 8\n");
				fprintf(stderr, " Usage: -s spots list, regexp format: \"(\\d+ \\d+ \\d+ \\d+ \\d+ \\d+ \\d+ \\d+)( \\d+ \\d+ \\d+ \\d+ \\d+ \\d+ \\d+ \\d+)*\"\n");
				return EXIT_FAILURE_PAUSE;
			}

			for (size_t j = 0; j < numbers_count; j += 8)
			{
				Spot spot;

				for (size_t k = 0; k < 4; k++)
				{
					spot.corners[k].x = atoi(argv[i + j + k*2 + 0]);
					spot.corners[k].y = atoi(argv[i + j + k*2 + 1]);
				}

				corners.push_back(spot);
			}

			i += numbers_count - 1; // -1 because i was incremeted at "i++;"
		}
	}

	unique_ptr<CameraDriver> camera(CameraDriver::factory(camera_type, camera_address));

	if ( ! camera->isValid())
	{
		printf("Failed to load image from camera\n");
		return EXIT_FAILURE_PAUSE;
	}

	Detector detector;

	if ( ! detector.loadImage(camera->getImagePath(), threshold_low, threshold_high, scale))
	{
		printf("Failed to load image from temporary file\n");
		return EXIT_FAILURE_PAUSE;
	}

	vector<Spot *> spots;

	for (size_t i = 0, l = corners.size(); i < l; i++)
	{
		Spot *spot = new Spot(corners[i]);

		spot->resetStatus(Free);

		spots.push_back(spot);
	}

	detector.findFreeSpots(spots, threshold_scan);

	int count = 0;
	for (size_t i = 0, l = spots.size(); i < l; i++)
	{
		count += (spots[i]->status == Free);
	}

	if (output_file.empty())
	{
		detector.displayGrid(spots);
	}
	else
	{
		cv::Mat img;
		cvtColor(detector.img, img, CV_GRAY2RGB);
		detector.drawGrid(img, spots);
		if ( ! imwrite(output_file, img))
		{
			printf("Failed to save image in %s\n", output_file.c_str());
			return EXIT_FAILURE_PAUSE;
		}
	}

	printf("findFreeSpots()=%u\n", count);

    return EXIT_SUCCESS;
}
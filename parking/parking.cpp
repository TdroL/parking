// parking.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Camera.h"
#include "Detector.h"
#include <string>
#ifdef RUN_TESTS
	#include "Tests.h"
#endif
using namespace std;
/*
static unsigned int corners[][4][2] = {
	{ {516/2, 462/2}, {548/2, 480/2}, {493/2, 541/2}, {461/2, 523/2} },
	{ {553/2, 483/2}, {586/2, 502/2}, {531/2, 564/2}, {498/2, 545/2} },
	{ {457/2, 528/2}, {498/2, 547/2}, {433/2, 611/2}, {401/2, 592/2} },
	{ {494/2, 550/2}, {527/2, 569/2}, {471/2, 633/2}, {438/2, 614/2} },
	{ {217/2, 601/2}, {249/2, 621/2}, {192/2, 688/2}, {160/2, 668/2} },
	{ {255/2, 623/2}, {288/2, 643/2}, {231/2, 711/2}, {198/2, 691/2} },
	{ {293/2, 645/2}, {326/2, 665/2}, {269/2, 733/2}, {236/2, 713/2} }
};
*/
static unsigned int corners[][4][2] = {
	{ {389, 326}, {446, 343}, {347, 393}, {289, 370} },
	{ {337, 309}, {384, 324}, {283, 368}, {234, 348} },
	{ {289, 294}, {332, 307}, {230, 346}, {185, 328} },
	{ {245, 280}, {283, 291}, {181, 326}, {141, 311} },
	{ {206, 268}, {240, 278}, {138, 309}, {105, 296} },
	{ {170, 257}, {200, 266}, {101, 294}, { 70, 282} },
	{ {138, 248}, {164, 256}, { 66, 280}, { 40, 271} }
};

int main(int argc, _TCHAR* argv[])
{
#ifdef RUN_TESTS
	TestClass tests;
	tests.run();
	system("pause");
	//return EXIT_SUCCESS;
#endif

	string camera_address = "C:/Users/tdroL/Documents/Visual Studio 2010/Projects/parking/assets/Parking-Lot.jpg"; //preview1.jpg";
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

	vector<Spot *> spots;

	for (size_t i = 0; i < 7; i++)
	{
		Spot *spot = new Spot;

		for (size_t j = 0; j < 4; j++)
		{
			spot->corners[j].x = corners[i][j][0];
			spot->corners[j].y = corners[i][j][1];
		}

		spot->resetStatus(Free);

		spots.push_back(spot);
	}

	detector.findFreeSpots(spots, 0.125 + 0.0625);

	int count = 0;
	for (size_t i = 0, l = spots.size(); i < l; i++)
	{
		count += (spots[i]->status == spots[i]->original_status);
	}

	printf("findFreeSpots() = %u\n", count);

	detector.displayGrid(spots);

    return EXIT_SUCCESS;
}
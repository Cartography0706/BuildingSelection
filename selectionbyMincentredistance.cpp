

#include "stdafx.h"
#include<iostream>


#include <string>
#include <list>
#include <vector>
#include <map>
#include <stack>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/ximgproc.hpp>
#include<ctime>

using namespace std;

using namespace cv;









int main()
{

	int sizepoint = 10000;
	int points[10000][2] = { 0 };
	int numpoint = 0;

	string  inputsuperpixelcentre = "selection/Aselectionoflsc600superpixeltwosegcentrepoint.bmp";
	string  inputbuildingcentre = "selection/buildingswithoutroadscentrepoint.bmp";
	string  cunchu = "selection/Abuilding600MindisResults.bmp";


	double centrepointx = 0;
	double centrepointy = 0;

	Mat srccentrepoint = imread(inputsuperpixelcentre);
	Mat buildingspoint = imread(inputbuildingcentre);
	Mat buildingspointResults = imread(inputbuildingcentre);

	//cv::imshow("dst", srccentrepoint);

	for (int row = 0; row < srccentrepoint.rows; row++)
	{
		for (int col = 0; col < srccentrepoint.cols; col++)
		{
			if (srccentrepoint.at<Vec3b>(row, col)[2] == 255 && srccentrepoint.at<Vec3b>(row, col)[1] == 0 && srccentrepoint.at<Vec3b>(row, col)[0] == 0)
			{
				centrepointx = row;
				centrepointy = col;

				double mindis = 100000;
				int minx = 0;
				int miny = 0;

				for (int row2 = 0; row2 < buildingspoint.rows; row2++)
				{
					for (int col2 = 0; col2 < buildingspoint.cols; col2++)
					{

						if (buildingspoint.at<Vec3b>(row2, col2)[2] == 255 && buildingspoint.at<Vec3b>(row2, col2)[1] == 0 && buildingspoint.at<Vec3b>(row2, col2)[0] == 0)
						{
							double distance;
							distance = powf((row2 - row), 2) + powf((col2 - col), 2);
							distance = sqrtf(distance);

							if (distance < mindis)
							{
								mindis = distance;
								minx = row2;
								miny = col2;
								printf("object%d - mindis:%.2f ", row, mindis);
								printf("\n");

							}

						}



					}
				}


				buildingspointResults.at<Vec3b>(minx, miny)[2] = 0;
				buildingspointResults.at<Vec3b>(minx, miny)[1] = 255;
				buildingspointResults.at<Vec3b>(minx, miny)[0] = 0;



			}


		}
	}



	/*imshow("Contours", drawing);*/

	cv::imwrite(cunchu, buildingspointResults);

}
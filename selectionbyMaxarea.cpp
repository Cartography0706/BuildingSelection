

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


	String superpixel = "selection/buildingswithoutroads.bmp";
	String cunchu = "selection/buildingsareas.bmp";



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	cv::Mat image_gray4 = cv::imread(superpixel, cv::IMREAD_GRAYSCALE);
	cv::Mat image_binary4;

	cv::threshold(image_gray4, image_binary4, 100, 255, cv::THRESH_BINARY);
	std::vector< std::vector< cv::Point> > contours4;
	cv::findContours(
		image_binary4,
		contours4,
		cv::noArray(),
		cv::RETR_LIST,
		cv::CHAIN_APPROX_SIMPLE
		);
	image_binary4 = cv::Scalar::all(0);
	cv::drawContours(image_binary4, contours4, -1, cv::Scalar::all(255));



	//计算轮廓矩
	vector<Moments> mu(contours4.size());
	for (int i = 0; i < contours4.size(); i++)
	{
		mu[i] = moments(contours4[i], false);
	}
	vector<Point2f> mc(contours4.size());
	for (int i = 0; i < contours4.size(); i++)
	{
		mc[i] = Point2d(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);


		points[numpoint][1] = mc[i].x;
		points[numpoint][2] = mc[i].y;
		numpoint = numpoint + 1;
	}


	Mat drawing = Mat::zeros(image_binary4.size(), CV_8UC3);


	//旋转角度
	double angle;
	double ceterx;
	double cetery;
	vector<Vec4i> hierarchy;
	//绘制超像素的质心

	for (int i = 0; i < contours4.size(); i++)
	{
		double area = contourArea(contours4[i]);
		Scalar color = Scalar(0, 255, 255);
		Scalar color2 = Scalar(0, 0, 255);

		drawContours(drawing, contours4, i, color, 1, 8, hierarchy, 0, Point());
		circle(drawing, mc[i], 1, color2, -1, 1, 0);

		double area2 = mu[i].m00;
		
		char tam[100];
		sprintf_s(tam, "%.1f", area);
		putText(drawing, tam, Point(mc[i].x, mc[i].y), FONT_HERSHEY_SIMPLEX, 0.9, cvScalar(0, 255, 0), 1.5);


	


	}
	imshow("Contours", drawing);

	cv::imwrite(cunchu, drawing);

}
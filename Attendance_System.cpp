#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {

	printf("Hello Mani\n");

	Mat quad0 = imread("im3.png", CV_LOAD_IMAGE_COLOR);
	//resize(quad, quad, Size(368, 655));
	
	Mat quad = imread("im2.png", CV_LOAD_IMAGE_COLOR);
	imshow("quad", quad);
	threshold(quad0, quad0, 40, 0, cv::THRESH_TOZERO);
	threshold(quad, quad, 40, 0, cv::THRESH_TOZERO);
	//imshow("thresholded", quad);
	cv::Size size(3, 5);
	//cv::medianBlur(quad, quad, 3);

	//NEW
	GaussianBlur(quad0, quad0, size, 0);
	Mat mask0;
	cv::inRange(quad0, Scalar(0, 0, 0), Scalar(10, 10, 10), mask0);
	bitwise_not(mask0, mask0);
	imshow("mask0", mask0);
	//
	
	GaussianBlur(quad, quad, size, 0);
	Mat mask;
	cv::inRange(quad, Scalar(0, 0, 0), Scalar(10, 10, 10), mask);
	bitwise_not(mask, mask);
	imshow("mask", mask);
	//
	cv::absdiff(mask0, mask, mask);
	imshow("diff", mask);
	//
	int erosion_size = 2;
	Mat element = getStructuringElement(cv::MORPH_CROSS, cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		cv::Point(erosion_size, erosion_size));

	// Apply erosion or dilation on the image
	erode(mask, mask, element);
	dilate(mask, mask, 0, Point(0, 0), 2, 1, 1);
	imshow("Eroded and Dilated", mask);

	//cvtColor(mask, mask, CV_BGR2GRAY);
	vector<Vec3f> circles;
	HoughCircles(mask, circles, CV_HOUGH_GRADIENT, 1, quad0.rows / 3, 35, 20, 0, 0);
	for (size_t i = 0; i < circles.size(); i++) {
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		// circle center  

		myfile << cvRound(circles[i][0]) <<"  " <<cvRound(circles[i][1]) <<endl;
		circle(quad0, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		circle(quad0, center, 40, Scalar(0, 0, 255), 2, 8, 0);
	}
	printf("Circles size: %d", circles.size());
	imshow("Final", quad0);
	waitKey();
	
	return 0;
}

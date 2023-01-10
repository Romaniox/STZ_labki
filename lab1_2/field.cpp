#include "field.h"


Field::Field(uint32_t size) {
	cv::Mat bkgd(size, size, CV_8UC3);
	bkgd /= 255;

	this->background = bkgd;
}


void Field::step(double rx1, double ry1, double rx2, double ry2, double rx3, double ry3) {
	cv::Scalar color_line(36, 28, 237);

	cv::line(this->background, cv::Point(rx1, ry1), cv::Point(rx1, ry1), cv::Scalar(128, 255, 128), 2, cv::LINE_4);
	cv::line(this->background, cv::Point(rx2, ry2), cv::Point(rx2, ry2), cv::Scalar(128, 255, 255), 2, cv::LINE_4);
	cv::line(this->background, cv::Point(rx3, ry3), cv::Point(rx3, ry3), cv::Scalar(255, 128, 128), 2, cv::LINE_4);

	cv::Mat img = this->background.clone();
	cv::circle(img, cv::Point(rx1, ry1), 10, cv::Scalar(0, 251, 57), -1);
	cv::circle(img, cv::Point(rx2, ry2), 10, cv::Scalar(0, 234, 240), -1);
	cv::circle(img, cv::Point(rx3, ry3), 10, cv::Scalar(255, 194, 34), -1);

	cv::imshow("Display window", img);
	cv::waitKey(1);
}

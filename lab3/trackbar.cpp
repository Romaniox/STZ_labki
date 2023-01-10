#include "trackbar.h"


cv::Mat init_img_, edited_img_;
int h_min, h_max, s_min, s_max, v_min, v_max;

void trackbar_act(int, void *) {
    cv::inRange(init_img_,
                cv::Scalar(h_min * 0.5, s_min * 2.55, v_min * 2.55),
                cv::Scalar(h_max * 0.5, s_max * 2.55, v_max * 2.55),
                edited_img_);
    cv::imshow("image", edited_img_);
}


void start_trackbar(const cv::Mat &img) {
    init_img_ = img.clone();
    cv::medianBlur(init_img_, init_img_, 13);
    cv::cvtColor(init_img_, init_img_, cv::COLOR_BGR2HSV);
    edited_img_ = init_img_.clone();

    cv::namedWindow("trackbar", 0);
    cv::resizeWindow("trackbar", 300, 1);

    cv::createTrackbar("h_min", "trackbar", &h_min, 359, trackbar_act);
    cv::createTrackbar("h_max", "trackbar", &h_max, 359, trackbar_act);
    cv::createTrackbar("s_min", "trackbar", &s_min, 100, trackbar_act);
    cv::createTrackbar("s_max", "trackbar", &s_max, 100, trackbar_act);
    cv::createTrackbar("v_min", "trackbar", &v_min, 100, trackbar_act);
    cv::createTrackbar("v_max", "trackbar", &v_max, 100, trackbar_act);
    cv::waitKey(0);
}

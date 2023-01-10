#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include "anti_terrorist_waffen.h"
#include "robotics.h"
#include "trackbar.h"
#include "zavod.h"


int main() {
    //// задание 1 ////
//    cv::Mat init_image = cv::imread("./allababah/ig_1.jpg", cv::IMREAD_GRAYSCALE);
//    get_occupant_pos(init_image);


    //// задание 2 ////
//    cv::Mat init_image = cv::imread("./teplovizor/ntcs_quest_measurement.png");
//    get_engine_pos(init_image);


    //// задание 3 ////
//    cv::Mat init_image = cv::imread("./roboti/roi_robotov_1.jpg");
//    Robots robots(init_image);
//    /*cv::Mat edited_img = robots.find_lamp();*/
//    robots.find_robots();


    //// задание 4 ////
//    cv::Mat init_image = cv::imread("./gk/gk.jpg");
//    cv::Mat tmpl_image = cv::imread("./gk/gk_tmplt.jpg");
//    GK check_zavod(init_image, tmpl_image);
//
//    cv::Mat out_image = check_zavod.get_comparison();
//
//    cv::imshow("123", out_image);
//    cv::waitKey(-1);


    //// TrackBar ////
//    cv::Mat init_image = cv::imread("./roboti/roi_robotov_1.jpg");
//    start_trackbar(init_image);


    return 0;
}

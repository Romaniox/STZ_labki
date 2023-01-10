#include <iostream>
#include <cmath>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/intensity_transform.hpp>

#include "operations.h"

void show_img(const cv::Mat& img) {
    cv::imshow("img", img);
    cv::waitKey(-1);
}

int main() {
    cv::Mat init_image = cv::imread("./test.jpg", cv::IMREAD_GRAYSCALE);

    //// 1 задание ////
//    cv::Mat test_image = init_image.clone();
//    box_flt(test_image, 3);
//
//    show_img(test_image);
    ///////////////////


    //// 2 задание ////
//    cv::Mat test_image = init_image.clone();
//    box_flt(test_image, 3);
//
//    cv::Mat cv_blur_image;
//    cv::blur(init_image, cv_blur_image, cv::Size(3, 3));
//
//    compare_methods(test_image, cv_blur_image);
    ///////////////////


    //// 3 задание ////
//    cv::Mat test_image = init_image.clone();
//
//    cv::TickMeter tm1;
//    tm1.start();
//
//    box_flt(test_image, 3);
//
//    tm1.stop();
//    std::cout << "My method time = " << tm1.getTimeSec() << " sec" << std::endl;
//
//    cv::TickMeter tm2;
//    tm2.start();
//
//    cv::Mat cv_blur_image;
//    cv::blur(init_image, cv_blur_image, cv::Size(3, 3));
//
//    tm2.stop();
//    std::cout << "OpenCV method time = " << tm2.getTimeSec() << " sec" << std::endl;
//
//    //разница между моим фильтром и встренным
//    show_img(test_image - cv_blur_image);
    ///////////////////


    //// 4 задание ////
//    cv::Mat cv_blur_image;
//    cv::blur(init_image, cv_blur_image, cv::Size(3, 3));
//
//    cv::Mat gaus_blur_image;
//    cv::GaussianBlur(init_image, gaus_blur_image, cv::Size(3, 3), 0);
//
//    cv::Mat diff_img = gaus_blur_image - cv_blur_image;
//    cv::intensity_transform::logTransform(diff_img, diff_img);
//
//    show_img(diff_img);
    ///////////////////


    //// 5 задание ////
//    cv::Mat unsharp_gaus = unsharp_mask(init_image, 5, Gaussian);
//    cv::Mat unsharp_box = unsharp_mask(init_image, 5, Box);
//
//    cv::Mat diff_img = unsharp_box - unsharp_gaus;
//    cv::intensity_transform::logTransform(diff_img, diff_img);
//
//    show_img(diff_img);
    ///////////////////


    //// 6 задание ////
//    cv::Mat lap_img = laplas_flt(init_image);
//    cv::Mat res_img = init_image + 0.4 * lap_img;
//
//    show_img(lap_img);
    ///////////////////


    //// 7 задание ////
//    cv::Mat unsharp_gaus = unsharp_mask(init_image, 5, Gaussian);
//    cv::Mat unsharp_box = unsharp_mask(init_image, 5, Box);
//    cv::Mat unsharp_lap = unsharp_mask(init_image, 0.2, Laplacian);
//
//    cv::Mat diff_img = unsharp_gaus - unsharp_lap;
//    cv::intensity_transform::logTransform(diff_img, diff_img);
//
//    show_img(diff_img);
    ///////////////////

    return 0;
}

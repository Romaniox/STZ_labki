#include <iostream>
#include <cmath>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/intensity_transform.hpp>


enum FilterType {
    Box, Gaussian, Laplacian
};

void compare_methods(cv::Mat img1, cv::Mat img2);
uint32_t get_roi_sum(cv::Mat roi);
uint32_t get_roi_sum_lap(cv::Mat roi);
void box_flt(cv::Mat img, uint32_t size);
cv::Mat laplas_flt(const cv::Mat& img);
cv::Mat unsharp_mask(const cv::Mat& img, double k, FilterType filter = Box);


#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

class GK {
public:
    cv::Mat init_img;
    cv::Mat tmplt;
    cv::Mat output_img;
private:
    cv::Mat edited_img;
private:
    enum GKQuality {
        Correct, Defective
    };
private:
    std::vector<std::vector<cv::Point>> contours;
    std::vector<std::vector<cv::Point>> tmplt_contours;
public:
    cv::Mat get_comparison();
private:
    void get_binary();
    void get_contours();
    void compare_two_cnts();
    void drow_results(const std::vector<cv::Point>& cnt, GKQuality quality);
public:
    explicit GK(const cv::Mat &init_img, const cv::Mat &tmplt_img);
    ~GK() = default;
};

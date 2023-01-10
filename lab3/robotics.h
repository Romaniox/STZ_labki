#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

class Robots {
public:
    cv::Mat init_img;
private:
    cv::Mat edited_img;  //blured/HSV image
    cv::Mat bin_img;  //binary segmentation image
    cv::Mat output_img;
private:
    int xc_lamp = 0;  //mass center of lamp
    int yc_lamp = 0;
    cv::Rect rect_lamp;
public:
    void find_robots();
    cv::Mat find_lamp();
private:
    //robot groups
    enum BotCol {
        Red, Green, Blue
    };
    bool is_preprocessed = false;
private:
    void get_preprocessing();
    void draw_robots(BotCol color);
    static void roi_del(cv::Mat roi);
    std::vector<std::vector<cv::Point>> get_robot_contours() const;
    std::vector<uint32_t> find_nearest(std::vector<cv::Moments> moments) const;
    static std::vector<cv::Moments> get_robot_moments(std::vector<std::vector<cv::Point>> contours);
    static std::vector<cv::Moments> get_moments(const cv::Mat &bin_img);
public:
    explicit Robots(const cv::Mat &init_img);
    ~Robots() = default;
};

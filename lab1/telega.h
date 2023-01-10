#pragma once

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>

#include <cstdint>
#include <cmath>

class TelegaBot {
private:
    cv::Mat background;
    cv::Mat bot_img;

    uint32_t x0 = 0;
    uint32_t x = x0;

    double y0 = 0;
    double y = y0;

    double alpha = 10 * 3.1415926;
    double beta = 50.0;
public:
    TelegaBot(cv::Mat background, cv::Mat image);
    ~TelegaBot() = default;

public:
    void show();
    void step();
};


#pragma once
#include <cstdint>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>

class Field {
private:
    cv::Mat background;
public:
    Field(uint32_t size);
     ~Field() = default;
public:
    void step(double rx1, double ry1, double rx2, double ry2, double rx3, double ry3);
};
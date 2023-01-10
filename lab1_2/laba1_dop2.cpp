#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#include "obj.h"
#include "field.h"

#define SIZE 500


int main() {
    //cv::Mat background = cv::imread("./files/cat.jpg");
    //std::cout << background.rows << std::endl;
    //std::cout << background.cols << std::endl;

    //PhysObj obj1(1000, (243.0, 57,0), (0.0, 0.0), (0.0, 0.0));
    double r1[2] = {243.0, 57.0};
    double r2[2] = { 55.0, 201.0 };
    double r3[2] = { 195.0, 225.0 };
    double v[2] = {0.0, 0.0};
    double w[2] = {0.0, 0.0};


    //PhysObj obj1(1000, r1, v, w);
    //PhysObj obj2(1000, r2, v, w);
    //PhysObj obj3(1000, r3, v, w);

    Field image(SIZE);

    PhysObj obj1(1000, 243.0, 57.0, 0.0, 0.0, 0.0, 0.0);
    PhysObj obj2(1000, 55.0, 201.00, 0.0, 0.0, 0.0, 0.0);
    PhysObj obj3(1000, 195.0, 225.0, 0.0, 0.0, 0.0, 0.0);

    while (1) {
        image.step(obj1.rx, obj1.ry, obj2.rx, obj2.ry, obj3.rx, obj3.ry);

        double rx1 = obj1.rx;
        double ry1 = obj1.ry;
        double rx2 = obj2.rx;
        double ry2 = obj2.ry;
        double rx3 = obj3.rx;
        double ry3 = obj3.ry;


        obj1.step(0.01, obj2.m, obj3.m, rx2, ry2, rx3, ry3);
        obj2.step(0.01, obj1.m, obj3.m, rx1, ry1, rx3, ry3);
        obj3.step(0.01, obj1.m, obj2.m, rx1, ry1, rx2, ry2);
    }
    return 0;
}

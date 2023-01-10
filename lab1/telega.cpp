#include "telega.h"


TelegaBot::TelegaBot(cv::Mat background, cv::Mat image) {
    this->background = background;
    this->bot_img = image;
    this->y0 = this->background.rows / 2;
}


void TelegaBot::step() {
    this->x += 1;
    this->y = this->y0 - this->beta * sin(double(this->x / this->alpha));
}


void TelegaBot::show() {
    //check for save
    this->y = (uint32_t) this->y;
    cv::Point px(this->x, this->y);
    cv::Scalar color_line(36, 28, 237);
    cv::Scalar color_circle(232, 162, 0);

    cv::line(this->background, px, px, color_line, 2, cv::LINE_4);

    cv::Mat img = this->background.clone();
//    cv::circle(img, px, 10, color_circle, -1);

    int xpx = 0;
    int ypx = 0;
    for (int i = 0; i < this->bot_img.cols; i++) {
        for (int j = 0; j < this->bot_img.rows; j++) {
            if (this->bot_img.at<cv::Vec3b>(i, j) == cv::Vec3b(0, 0, 0))
                continue;
            xpx = i - (this->bot_img.cols / 2) + this->x;
            ypx = j - (this->bot_img.rows / 2) + this->y;
            if (xpx <= 0 || ypx <= 0 || xpx >= this->background.cols || ypx >= this->background.rows) continue;
            img.at<cv::Vec3b>(ypx, xpx) = this->bot_img.at<cv::Vec3b>(j, i);
        }
    }

    if (this->x == this->background.cols / 2) {
        cv::imwrite("./files/saved.png", img);
    }

    cv::imshow("Display window", img);
    cv::waitKey(10);
}

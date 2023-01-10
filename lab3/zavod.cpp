#include "zavod.h"


GK::GK(const cv::Mat &init_img, const cv::Mat &tmplt_img) {
    this->init_img = init_img.clone();
    this->tmplt = tmplt_img.clone();
    this->output_img = init_img.clone();
}


void GK::get_binary() {
    this->edited_img = this->init_img.clone();
    cv::cvtColor(this->edited_img, this->edited_img, cv::COLOR_BGR2HSV);
    cv::medianBlur(this->edited_img, this->edited_img, 7);

    cv::inRange(this->edited_img, cv::Scalar(0 * 0.5, 0 * 2.55, 12 * 2.55),
                cv::Scalar(359 * 0.5, 35 * 2.55, 93 * 2.55),
                this->edited_img);

    cv::inRange(this->tmplt, cv::Scalar(0 * 0.5, 0 * 2.55, 0 * 2.55),
                cv::Scalar(359 * 0.5, 40 * 2.55, 40 * 2.55),
                this->tmplt);
}


void GK::get_contours() {
    findContours(this->edited_img, this->contours,
                 cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    findContours(this->tmplt, this->tmplt_contours,
                 cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
}


void GK::compare_two_cnts() {
    double cmp_res = 0.0;
    GKQuality gk_quality;
    for (int i = 0; i < this->contours.size(); i++) {
        if (cv::contourArea(this->contours[i]) < 30) continue;
        cmp_res = cv::matchShapes(contours[i], this->tmplt_contours[0], cv::ShapeMatchModes::CONTOURS_MATCH_I2, 0);
        if (cmp_res < 0.9) gk_quality = Defective;
        else gk_quality = Correct;

        this->drow_results(contours[i], gk_quality);
    }
}


void GK::drow_results(const std::vector<cv::Point>& cnt, GKQuality quality) {
    switch (quality) {
        case Correct:
            cv::polylines(this->output_img, cnt, true, cv::Scalar(0, 255, 0), 2, cv::LINE_8);
            break;
        case Defective:
            cv::polylines(this->output_img, cnt, true, cv::Scalar(0, 0, 255), 2, cv::LINE_8);
            break;
    }
}


cv::Mat GK::get_comparison() {
    this->get_binary();
    this->get_contours();
    this->compare_two_cnts();

    return this->output_img;
}

#include "anti_terrorist_waffen.h"


std::vector<cv::Moments> get_moments(const cv::Mat &bin_img) {
    std::vector<std::vector<cv::Point>> contours;
    findContours(bin_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

    std::vector<cv::Moments> mnts(contours.size());
    std::vector<uint32_t> xc(contours.size());
    std::vector<uint32_t> yc(contours.size());
    for (int i = 0; i < contours.size(); i++) {
        mnts[i] = cv::moments(contours[i]);
    }
    return mnts;
}


cv::Mat targeting(cv::Mat bin_img, cv::Mat init_img) {
//    cv::Mat contours_img(bin_img.rows, bin_img.cols, CV_8UC1);
//    cv::polylines(contours_img, contours, false, cv::Scalar(255, 255, 0), 1, cv::LINE_8);
    std::vector<cv::Moments> mnts = get_moments(bin_img);

    std::vector<uint32_t> xc(mnts.size());
    std::vector<uint32_t> yc(mnts.size());
    for (int i = 0; i < mnts.size(); i++) {
        if (mnts[i].m00 <= 30) continue;
        xc[i] = (uint32_t) round(mnts[i].m10 / mnts[i].m00);
        yc[i] = (uint32_t) round(mnts[i].m01 / mnts[i].m00);
    }

    for (int i = 0; i < xc.size(); i++) {
        if (xc[i] == 0 || yc[i] == 0) continue;
        cv::Point px(xc[i], yc[i]);
        cv::circle(init_img, px, 2, cv::Scalar(0, 0, 0), -1);
    }
    return init_img;
}


void get_occupant_pos(const cv::Mat &img) {
    cv:: Mat edited_img = img.clone();
    cv:: Mat init_img = img.clone();

    cv::threshold(img, edited_img,  226.0, 255.0, cv::THRESH_BINARY);

    cv::Mat img_targeted = targeting(edited_img, img);

    cv::imshow("123", img_targeted);
    cv::waitKey(-1);
    }


void get_engine_pos(const cv::Mat &img) {
    cv::Mat hsv_img;
    cv::cvtColor(img, hsv_img, cv::COLOR_BGR2HSV);

    // выделяем красный диапазон
    cv::inRange(hsv_img, cv::Scalar(0 * 0.5, 0 * 2.55, 15 * 2.55), cv::Scalar(60 * 0.5, 100 * 2.55, 100 * 2.55),
                hsv_img);

    cv::Mat img_targeted = targeting(hsv_img, img);

    cv::imshow("123", img_targeted);
    cv::waitKey(-1);
}






#include "robotics.h"


Robots::Robots(const cv::Mat &init_img) {
    this->init_img = init_img.clone();
    this->edited_img = init_img.clone();
    this->output_img = init_img.clone();
    this->bin_img = init_img.clone();
}


std::vector<cv::Moments> Robots::get_moments(const cv::Mat &bin_img) {
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


cv::Mat Robots::find_lamp() {
    if (!this->is_preprocessed) this->get_preprocessing();
    cv::inRange(this->edited_img, cv::Scalar(0 * 0.5, 0 * 2.55, 94 * 2.55), cv::Scalar(67 * 0.5, 4 * 2.55, 100 * 2.55),
                this->bin_img);
    std::vector<cv::Moments> mnts = this->get_moments(this->bin_img);

    std::vector<uint32_t> xc(mnts.size());
    std::vector<uint32_t> yc(mnts.size());
    for (int i = 0; i < mnts.size(); i++) {
        if (mnts[i].m00 <= 30) continue;
        xc[i] = (uint32_t) round(mnts[i].m10 / mnts[i].m00);
        yc[i] = (uint32_t) round(mnts[i].m01 / mnts[i].m00);
    }
    this->xc_lamp = xc[0];
    this->yc_lamp = yc[0];

    this->rect_lamp = cv::Rect(xc[0] - 34, yc[0] - 55, 65, 75);
    cv::rectangle(this->output_img, rect_lamp, cv::Scalar(0, 255, 255));

    return this->output_img;
}


std::vector<std::vector<cv::Point>> Robots::get_robot_contours() const {
    std::vector<std::vector<cv::Point>> contours;
    findContours(this->bin_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    for (int i = contours.size() - 1; i >= 0; i--) {
        if (cv::contourArea(contours[i]) < 30) {
            contours.erase(contours.begin() + i);
        }
    }
    return contours;
}


void Robots::roi_del(cv::Mat roi) {
    cv::MatIterator_<cv::Vec3b> it, end;
    for (it = roi.begin<cv::Vec3b>(), end = roi.end<cv::Vec3b>(); it != end; ++it) {
        (*it)[0] = 0;
        (*it)[1] = 0;
        (*it)[2] = 0;
    }
}


std::vector<cv::Moments> Robots::get_robot_moments(std::vector<std::vector<cv::Point>> contours) {
    std::vector<cv::Moments> mnts(contours.size());
    std::vector<uint32_t> xc(contours.size());
    std::vector<uint32_t> yc(contours.size());
    for (int i = 0; i < contours.size(); i++) {
        mnts[i] = cv::moments(contours[i]);
    }
    return mnts;
}


std::vector<uint32_t> Robots::find_nearest(std::vector<cv::Moments> moments) const {
    std::vector<int> xc(moments.size());
    std::vector<int> yc(moments.size());
    double nearest_dist = 1000000000.0;
    double dist = 0.0;
    uint32_t xc_nearest = 0;
    uint32_t yc_nearest = 0;

    for (int i = 0; i < moments.size(); i++) {
        xc[i] = (int) round(moments[i].m10 / moments[i].m00);
        yc[i] = (int) round(moments[i].m01 / moments[i].m00);
    }
    for (int i = 0; i < moments.size(); i++) {
        dist = sqrt(pow((double) this->xc_lamp - (double) xc[i], 2) + pow((double) this->yc_lamp - (double) yc[i], 2));
        if (dist < nearest_dist) {
            xc_nearest = xc[i];
            yc_nearest = yc[i];
            nearest_dist = dist;
        }
    }
    std::vector<uint32_t> nearest_center_mass(2);
    nearest_center_mass[0] = xc_nearest;
    nearest_center_mass[1] = yc_nearest;

    return nearest_center_mass;
}


void Robots::draw_robots(BotCol color) {
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Moments> moments(contours.size());
    std::vector<uint32_t> nearest_center_mass;
    cv::Point px;

    switch (color) {
        case Green:
            // выделяем зелёных роботов
            cv::inRange(this->edited_img, cv::Scalar(116 * 0.5, 28 * 2.55, 52 * 2.55),
                        cv::Scalar(156 * 0.5, 85 * 2.55, 100 * 2.55),
                        this->bin_img);
            contours = get_robot_contours();
            moments = get_robot_moments(contours);
            nearest_center_mass = find_nearest(moments);
            px = cv::Point(nearest_center_mass[0], nearest_center_mass[1]);
            cv::circle(this->output_img, px, 2, cv::Scalar(0, 0, 0), -1);
            cv::polylines(this->output_img, contours, true, cv::Scalar(0, 255, 0), 2, cv::LINE_8);
            break;

        case Blue:
            // выделяем голубых роботов
            cv::inRange(this->edited_img, cv::Scalar(170 * 0.5, 8 * 2.55, 16 * 2.55),
                        cv::Scalar(228 * 0.5, 93 * 2.55, 96 * 2.55),
                        this->bin_img);
            contours = get_robot_contours();
            moments = get_robot_moments(contours);
            nearest_center_mass = find_nearest(moments);
            px = cv::Point(nearest_center_mass[0], nearest_center_mass[1]);
            cv::circle(this->output_img, px, 2, cv::Scalar(0, 0, 0), -1);
            cv::polylines(this->output_img, contours, true, cv::Scalar(255, 0, 0), 2, cv::LINE_8);

        case Red:
            // выделяем красных роботов
            cv::inRange(this->edited_img, cv::Scalar(0 * 0.5, 16 * 2.55, 24 * 2.55),
                        cv::Scalar(14 * 0.5, 66 * 2.55, 100 * 2.55),
                        this->bin_img);
            cv::Mat red_0 = this->bin_img.clone();

            cv::inRange(this->edited_img, cv::Scalar(354 * 0.5, 0 * 2.55, 0 * 2.55),
                        cv::Scalar(359 * 0.5, 100 * 2.55, 100 * 2.55),
                        this->bin_img);
            this->bin_img = this->bin_img | red_0;
            contours = get_robot_contours();
            moments = get_robot_moments(contours);
            nearest_center_mass = find_nearest(moments);
            px = cv::Point(nearest_center_mass[0], nearest_center_mass[1]);
            cv::circle(this->output_img, px, 2, cv::Scalar(0, 0, 0), -1);
            cv::polylines(this->output_img, contours, true, cv::Scalar(0, 0, 255), 2, cv::LINE_8);
            break;
    }
}


void Robots::get_preprocessing() {
    cv::medianBlur(this->init_img, this->edited_img, 13);
    cv::cvtColor(this->edited_img, this->edited_img, cv::COLOR_BGR2HSV);
    this->is_preprocessed = true;
}


void Robots::find_robots() {
    if (!this->is_preprocessed) this->get_preprocessing();

    this->find_lamp();
//    cv::rectangle(this->output_img, this->rect_lamp, cv::Scalar(0, 255, 255));
    cv::Mat roi = this->edited_img(this->rect_lamp);
    this->roi_del(roi);

    BotCol color;
    color = Green;
    this->draw_robots(color);

    color = Blue;
    this->draw_robots(color);

    color = Red;
    this->draw_robots(color);

    cv::imshow("123", this->output_img);
    cv::waitKey(-1);
}

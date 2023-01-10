#include "operations.h"


void compare_methods(cv::Mat img1, cv::Mat img2) {
    int nRows = img1.rows;
    int nCols = img1.cols;

    uint32_t num_px = nRows * nCols;
    uint32_t num_px_eq = 0;

    uchar *p1, *p2;
    for (uint32_t i = 0; i < nRows; i++) {
        p1 = img1.ptr<uchar>(i);
        p2 = img2.ptr<uchar>(i);

        for (uint32_t j = 0; j < nCols; j++) {
            if (p1[j] == p2[j]) {
                num_px_eq++;
            }
        }
    }
    double acc = (double) num_px_eq / (double) num_px * 100.0;
    std::cout << acc << std::endl;
}


uint32_t get_roi_sum(cv::Mat roi) {
    uint32_t roi_sum = 0;
    cv::MatIterator_<uchar> it, end;
    for (it = roi.begin<uchar>(), end = roi.end<uchar>(); it != end; ++it)
        roi_sum += *it;
    return roi_sum;
}


uint32_t get_roi_sum_lap(cv::Mat roi) {
    int roi_sum = 0;
    cv::MatIterator_<uchar> it;
    it = roi.begin<uchar>();

    roi_sum += *(it + 0) * 0;
    roi_sum += *(it + 1) * -1;
    roi_sum += *(it + 2) * 0;
    roi_sum += *(it + 3) * -1;
    roi_sum += *(it + 4) * 4;
    roi_sum += *(it + 5) * -1;
    roi_sum += *(it + 6) * 0;
    roi_sum += *(it + 7) * -1;
    roi_sum += *(it + 8) * 0;

    return roi_sum;
}


void box_flt(cv::Mat img, uint32_t size) {
    cv::Mat init_img = img.clone();
    uint32_t img_edge = size / 2;

    int nRows = img.rows;
    int nCols = img.cols;

    uchar *p;
    for (int i = 0; i < nRows - size + 1; i++) {
        p = img.ptr<uchar>(i + img_edge);
        for (int j = 0; j < nCols - size + 1; j++) {
            cv::Mat roi = init_img(cv::Rect(j, i, size, size));
            double roi_sum = (double) get_roi_sum(roi) / (size * size);
            roi_sum = round(roi_sum);
            p[j + img_edge] = (uchar) roi_sum;
        }
    }
}


cv::Mat laplas_flt(const cv::Mat& img) {
    cv::Mat init_img = img.clone();
    cv::Mat edited_img = img.clone();

    int nRows = edited_img.rows;
    int nCols = edited_img.cols;

    uchar *p;
    for (int i = 0; i < nRows - 2; i++) {
        p = edited_img.ptr<uchar>(i + 1);
        for (int j = 0; j < nCols - 2; j++) {
            cv::Mat roi = init_img(cv::Rect(j, i, 3, 3));

            double roi_sum = (double) get_roi_sum_lap(roi);
            roi_sum = round(roi_sum);
            p[j + 1] = (uchar) roi_sum;
        }
    }
    return edited_img;
}


cv::Mat unsharp_mask(const cv::Mat& img, double k, FilterType filter) {
    const cv::Mat& init_img = img;
    cv::Mat blur_img;
    switch (filter) {
        case Box:
            cv::blur(img, blur_img, cv::Size(3, 3));
            break;
        case Gaussian:
            cv::GaussianBlur(img, blur_img, cv::Size(3, 3), 0);
            break;
        case Laplacian:
            blur_img = laplas_flt(img);
            cv::Mat sharped_img = init_img + k * blur_img;
            return sharped_img;
    }

    cv::Mat mask_img = init_img - blur_img;
    cv::Mat sharped_img = init_img + (uint32_t)k * mask_img;

    return sharped_img;
}

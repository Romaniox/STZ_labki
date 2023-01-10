#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#include "telega.h"

int main() {
    cv::Mat background = cv::imread("./files/bkg.png");
    cv::Mat bot_img = cv::imread("./files/telega.png");
    TelegaBot telega_bot(background, bot_img);

    for (int i = 1; i < background.cols; i++) {
        telega_bot.step();
        telega_bot.show();
    }
    return 0;
}

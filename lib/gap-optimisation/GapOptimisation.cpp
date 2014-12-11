#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "GapOptimisation.h"

namespace GapOptimisation {

    // Size of the area for which the direction is computed, in pixels (width = height)
    const int WindowSize = 20;

    void drawDirectionField(cv::Mat& im) {
        cv::Mat marker = cv::Mat::zeros(im.size(), CV_8UC1);

        for (int i = 1; i < im.rows-1-WindowSize; i+=WindowSize) {
            for (int j = 1; j < im.cols-1-WindowSize; j+=WindowSize) {
                im.at<uchar>(i+WindowSize/2, j+WindowSize/2) = 1;
            }
        }
    }

}

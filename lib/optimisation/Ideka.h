#ifndef IDEKA_H_INCLUDED
#define IDEKA_H_INCLUDED

#include <opencv2/imgproc/imgproc.hpp>

namespace ideka {

    void binOptimisation(cv::Mat& im);

    void ridgeEnhancement(cv::Mat& im);

    void valleyEnhancement(cv::Mat& im);

    void flagImage(cv::Mat& im);

    void smooth(cv::Mat& im);

}

#endif // IDEKA_H_INCLUDED

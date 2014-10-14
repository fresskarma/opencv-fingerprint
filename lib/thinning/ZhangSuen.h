#ifndef __ZhangSuen_H__
#define __ZhangSuen_H__

#include <opencv2/imgproc/imgproc.hpp>

namespace ZhangSuen {

    /**
     * Perform one thinning iteration.
     * Normally you wouldn't call this function directly from your code.
     *
     * @param  im    Binary image with range = 0-1
     * @param  iter  0=even, 1=odd
     */
    void thinningIteration(cv::Mat& im, int iter);

    /**
     * Function for thinning the given binary image
     *
     * @param  im  Binary image with range = 0-255
     */
    void thinning(cv::Mat& im);

}

#endif

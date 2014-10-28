#ifndef ADAPTIVELOCALTHRESHOLD_H_INCLUDED
#define ADAPTIVELOCALTHRESHOLD_H_INCLUDED

#include <opencv2/imgproc/imgproc.hpp>

namespace localThreshold {

    //ein Bild mit der Adaptive-Local-Threshold-Methode binarisieren
    void binarisation(cv::Mat& im, int numTilesWidth, int numTilesHeight);

    void deltaThresholding(unsigned int thresholds[], int numOfThresholds, unsigned char deltas[], int deltaThreshold);

    void medianThresholding(unsigned int thresholds[], int numOfThresholds);

    void averageThresholding(unsigned int thresholds[], int numOfThresholds);

}


#endif // ADAPTIVELOCALTHRESHOLD_H_INCLUDED



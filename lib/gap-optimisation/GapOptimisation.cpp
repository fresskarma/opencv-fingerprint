#include <vector>
#include <cmath>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "GapOptimisation.h"

namespace GapOptimisation {

    // Size of the area for which the direction is computed, in pixels (width = height)
    const int WindowSize = 20;

    double directionForPixel(cv::Mat& im, cv::Mat& marker, int i, int j, double currentDirection = -1) {
        return 45;
    }


    double calculateDirectionForWindow(cv::Mat& im) {
        cv::Mat marker = cv::Mat::zeros(im.size(), CV_8UC1);
        std::vector<double> directions;

        for(int i=0; i<im.cols; i++) {
            for(int j=0; j<im.rows; j++) {
                uchar px = im.at<uchar>(j,i);

                // Skip white pixels
                if(!px) {
                    continue;
                }

                // We've already processed this pixel
                if(marker.at<uchar>(j, i) == 1) {
                    continue;
                }

                directions.push_back(directionForPixel(im, marker, i, j));
            }
        }

        if(directions.size() < 1) {
            return NAN;
        }

        double direction = 0;
        for(int i=0; i<directions.size(); i++) {
            direction += directions.at(i);
        }

        return direction/directions.size();
    }



    void drawDirectionField(cv::Mat& im) {
        for (int i = 1; i < im.rows-1-WindowSize; i+=WindowSize) {
            for (int j = 1; j < im.cols-1-WindowSize; j+=WindowSize) {
                cv::Rect roi(j, i, WindowSize, WindowSize);

                cv::Mat roiImage = im(roi);
                double direction = calculateDirectionForWindow(roiImage);

                // TODO: Refactor direction drawing into own function
                // direction = i % 360; // for testing
                double xDir = std::cos(direction/180*M_PI);
                double yDir = -1 * std::sin(direction/180*M_PI); // y-Axis is inverted because
                                                                 // in math, +y is typically
                                                                 // considered to go in the top
                                                                 // direction whereas in the image
                                                                 // it goes towards the bottom

                cv::Point p1(
                             WindowSize/2 + ((WindowSize/4)*xDir),
                             WindowSize/2 + ((WindowSize/4)*yDir));
                cv::Point p2(
                             WindowSize/2 - ((WindowSize/4)*xDir),
                             WindowSize/2 - ((WindowSize/4)*yDir));

                cv::line(roiImage, p1, p2, 0);
            }
        }
    }

}

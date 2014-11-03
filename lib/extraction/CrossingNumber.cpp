#include "CrossingNumber.h"
#include "Minutiae.h"

#include <opencv2/core/core.hpp>
#include <iostream>

using namespace cv;

namespace crossingNumber {

void getMinutiae(Mat& im, std::vector<Minutiae>& minutiae, int border ){
    if(border < 1){
        std::cout<<"Randbereich zu klein gewählt!" << std::endl;
        border = 2;
    }

    int ridgeEndingCount = 0;
    int bifurcationCount = 0;
    for(int i = border; i<=(im.cols-border); i++){
        for(int j = border; j<=(im.rows-border); j++){
            int cn = 0;

            //black pixel found?
            if(im.at<uchar>(cv::Point(i, j)) == 0){
                //check 8-Neighborhood for other black pixels, if black -> cn++
                if(im.at<uchar>(cv::Point(i-1, j-1)) == 0){
                    cn++;
                }
                if(im.at<uchar>(cv::Point(i, j-1)) == 0){
                    cn++;
                }
                if(im.at<uchar>(cv::Point(i+1, j-1)) == 0){
                    cn++;
                }
                if(im.at<uchar>(cv::Point(i+1, j)) == 0){
                    cn++;
                }
                if(im.at<uchar>(cv::Point(i+1, j+1)) == 0){
                    cn++;
                }
                if(im.at<uchar>(cv::Point(i, j+1)) == 0){
                    cn++;
                }
                if(im.at<uchar>(cv::Point(i-1, j+1)) == 0){
                    cn++;
                }
                if(im.at<uchar>(cv::Point(i-1, j)) == 0){
                    cn++;
                }
                //std::cout<<"cn = " << cn << std::endl;

                if(cn == 1){
                    Minutiae minut(i, j, Minutiae::Type::RIDGEENDING);
                    minutiae.push_back(minut);
                    ridgeEndingCount++;
                }else if(cn == 3){
                    Minutiae minut(i, j, Minutiae::Type::BIFURCATION);
                    minutiae.push_back(minut);
                    bifurcationCount++;
                }
            }
        }
    }
    std::cout<<"Anzahl gefundener Ridge-Endings: " << ridgeEndingCount << std::endl;
    std::cout<<"Anzahl gefundener Bifurcations: " << bifurcationCount << std::endl;
}



}

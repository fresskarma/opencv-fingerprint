#include "AdaptiveLocalThreshold.h"

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace cv;

namespace localThreshold {

    void binarisation(cv::Mat& im, int numTilesWidth, int numTilesHeight){
        int deltaThreshold = 50;
        int tileWidth = im.cols/numTilesWidth;
        int tileHeight = im.rows/numTilesHeight;
        unsigned int greyValuesAdded = 0;
        unsigned int pixelPerTile = tileWidth * tileHeight;
        unsigned char intensity = 0;
        int numOfTiles = numTilesWidth*numTilesHeight;
        unsigned int thresholds [numOfTiles+numTilesWidth+numTilesHeight+1];  //Randbereiche dazu addiert
        unsigned char deltas [numOfTiles+numTilesWidth+numTilesHeight+1];
        int i, j, k, l, t;
        t = 0;
        //Laplace
        /*int kernel_size = 3;
        int scale = 1;
        int delta = 0;
        int ddepth = CV_16S;
        GaussianBlur( im, im, Size(3,3), 0, 0, BORDER_DEFAULT );
        Laplacian( im, im, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
        convertScaleAbs( im, im );*/
        //Iteration durch das Bild, pro Schritt wird ein Tile analysiert
        for(i = 0; i<=im.cols-tileWidth; i=i+tileWidth){
            for(j = 0; j<=im.rows-tileHeight; j=j+tileHeight){

                unsigned char darkest = 255;
                unsigned char brightest = 0;

                //Iteration durch Tile
                for(k = i; ((k-i)<tileWidth); k++){
                    for(l = j; ((l-j)<tileHeight); l++){
                        //alle Grauwerte aufaddieren
                        intensity = im.at<uchar>(cv::Point(k, l));
                        greyValuesAdded += intensity;

                        //Maximal- und Minimalwert berechnen
                        if(intensity < darkest){
                            darkest = intensity;
                        }else if(intensity>brightest){
                            brightest = intensity;
                        }

                    }
                }
                //Deltas speichern
                deltas[t] = std::abs(brightest-darkest);
                //std::cout << "delta = " << std::abs(brightest-darkest) << std::endl;
                //Druchschnitt der Grauwerte speichern
                thresholds[t] = greyValuesAdded/pixelPerTile;
                //std::cout << "t= " << t << std::endl;
                greyValuesAdded = 0;
                t++;
            }
        }

        int numOfThresholds = t;

        //medianThresholding(thresholds, numOfThresholds);
        //averageThresholding(thresholds, numOfThresholds);
        deltaThresholding(thresholds, numOfThresholds, deltas, deltaThreshold);

        t = 0;
        //2. Iteration durch das Bild, pro Schritt wird ein Tile bearbeitet
        for(i = 0; i<=im.cols-tileWidth; i=i+tileWidth){
            for(j = 0; j<=im.rows-tileHeight; j=j+tileHeight){

                //Threshold auf Tile anwenden
                for(k = i; ((k-i)<tileWidth); k++){
                    for(l = j; ((l-j)<tileHeight); l++){
                        intensity = im.at<uchar>(cv::Point(k, l));
                        if(intensity >= thresholds[t]){
                            im.at<uchar>(l,k) = 255; //white
                        }else{
                            im.at<uchar>(l,k) = 0; //black
                        }

                    }
                }
                t++;

            }
        }
    }

    void deltaThresholding(unsigned int thresholds[], int numOfThresholds, unsigned char deltas[], int deltaThreshold){
        for(int i = 0; i<numOfThresholds; i++){
            if(deltas[i]<deltaThreshold){
                thresholds[i] = 0;
            }
        }
    }

    void medianThresholding(unsigned int thresholds[], int numOfThresholds){
        unsigned int sortedThresholds[numOfThresholds];
        std::copy(thresholds, thresholds + numOfThresholds, sortedThresholds);
        std::sort(sortedThresholds, sortedThresholds + numOfThresholds);
        unsigned int thresholdThreshold = sortedThresholds[numOfThresholds/2];
        //Thresholds bearbeiten
        for(int i = 0; i<numOfThresholds; i++){
            if(thresholds[i]>thresholdThreshold){
                thresholds[i] = 0;
            }
        }
    }

    void averageThresholding(unsigned int thresholds[], int numOfThresholds){
        unsigned int thresholdValues = 0;
        unsigned int thresholdThreshold = 0;

        //Thresholds analysieren
        for(int i = 0; i<numOfThresholds; i++){
            thresholdValues += thresholds[i];
        }
        thresholdThreshold = thresholdValues/numOfThresholds; //Mittelwert der Thresholds
        //Thresholds bearbeiten
        for(int i = 0; i<numOfThresholds; i++){
            if(thresholds[i]>thresholdThreshold){
                thresholds[i] = 0;
            }
        }
    }
}

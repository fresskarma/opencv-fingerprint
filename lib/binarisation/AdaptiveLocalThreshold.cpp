#include "AdaptiveLocalThreshold.h"

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

namespace localThreshold {

    void binarisation(cv::Mat& im, int numTilesWidth, int numTilesHeight){
        int tileWidth = im.cols/numTilesWidth;
        int tileHeight = im.rows/numTilesHeight;
        unsigned int greyValuesAdded = 0;
        unsigned int localThreshold = 0;
        unsigned int numOfPixels = 0;
        unsigned int pixelPerTile = tileWidth * tileHeight;
        unsigned char intensity = 0;
        int i, j, k, l;

        //Iteration durch das Bild, pro Schritt wird ein Tile analysiert und bearbeitet
        for(i = 0; i<=im.cols-tileWidth; i=i+tileWidth){
            for(j = 0; j<=im.rows-tileHeight; j=j+tileHeight){

                //Iteration durch Tile
                for(k = i; ((k-i)<tileWidth)&&(im.cols-i>=tileWidth); k++){
                    for(l = j; ((l-j)<tileHeight)&&(im.rows-i>=tileHeight); l++){
                        //alle Grauwerte aufaddieren
                        intensity = im.at<uchar>(cv::Point(k, l));
                        greyValuesAdded += intensity;
                    }
                }

                //Druchschnitt der Grauwerte berechnen

                localThreshold = greyValuesAdded/pixelPerTile;

                //Threshold auf Tile anwenden
                for(k = i; ((k-i)<tileWidth)&&(im.cols-i>=tileWidth); k++){
                    for(l = j; ((l-j)<tileHeight)&&(im.rows-i>=tileHeight); l++){
                        intensity = im.at<uchar>(cv::Point(k, l));
                        if(intensity >= localThreshold){
                            im.at<uchar>(l,k) = 255; //white
                        }else{
                            im.at<uchar>(l,k) = 0; //black
                        }



                    }
                }

                //für näcchsten Tile zurücksetzen
                greyValuesAdded = 0;
                localThreshold = 0;

            }
        }
    }
}

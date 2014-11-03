#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "AdaptiveLocalThreshold.h"
#include "Ideka.h"
#include "GuoHall.h"
#include "CrossingNumber.h"

using namespace cv;
using namespace std;

int main( int argc, const char* argv[] )
{

	Mat sourceImage = imread("/home/raphael/opencv-fingerprint/src/2.bmp", CV_LOAD_IMAGE_GRAYSCALE);
    if(! sourceImage.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << endl ;
        return -1;
    }

    Mat img = sourceImage.clone();
    localThreshold::binarisation(img, 41, 56);
    cv::threshold(img, img, 50, 255, cv::THRESH_BINARY);
    Mat binImg = img.clone();
    ideka::binOptimisation(img);

    namedWindow( "Originales Bild", WINDOW_AUTOSIZE );  // Create a window for display.
    imshow( "Originales Bild", sourceImage );           // Show our image inside it.
    namedWindow( "Binarisiertes Bild", WINDOW_AUTOSIZE );   // Create a window for display.
    imshow( "Binarisiertes Bild", binImg );                 // Show our image inside it.
    namedWindow( "Optimiertes Bild", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( "Optimiertes Bild", img );                  // Show our image inside it.

    //skeletionizing
    cv::bitwise_not(img, img);    //Inverse for bit-operations
    GuoHall::thinning(img);
    cv::bitwise_not(img, img);
    namedWindow( "Skelettiertes Bild", WINDOW_AUTOSIZE );   // Create a window for display.
    imshow( "Skelettiertes Bild", img );                    // Show our image inside it.

    //Minutiae-Extraction
    vector<Minutiae> minutiae;
    crossingNumber::getMinutiae(img, minutiae, 30);
    cout<<"Anzahl gefundener Minutien: " << minutiae.size() << endl;

    //Visualisation
    Mat minutImg = img.clone();
    cvtColor(img, minutImg, CV_GRAY2RGB);
    for(std::vector<int>::size_type i = 0; i<minutiae.size(); i++){
    //add an transparent square at each minutiae-location
    int squareSize = 5;     //has to be uneven
        Mat roi = minutImg(Rect(minutiae[i].getLocX()-squareSize/2, minutiae[i].getLocY()-squareSize/2, squareSize, squareSize));
        double alpha = 0.3;
        if(minutiae[i].getType() == Minutiae::Type::RIDGEENDING){
            Mat color(roi.size(), CV_8UC3, cv::Scalar(255,0,0));    //blue square for ridgeending
            addWeighted(color, alpha, roi, 1.0 - alpha , 0.0, roi);
        }else if(minutiae[i].getType() == Minutiae::Type::BIFURCATION){
            Mat color(roi.size(), CV_8UC3, cv::Scalar(0,0,255));    //red square for bifurcation
            addWeighted(color, alpha, roi, 1.0 - alpha , 0.0, roi);
        }

    }
    namedWindow( "Minutien", WINDOW_AUTOSIZE );     // Create a window for display.
    imshow( "Minutien", minutImg );                 // Show our image inside it.

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;

}

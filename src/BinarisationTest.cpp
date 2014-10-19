#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "AdaptiveLocalThreshold.h"
#include "Ideka.h"
#include "GuoHall.h"

using namespace cv;
using namespace std;

int main( int argc, const char* argv[] )
{

	Mat sourceImage = imread("/home/raphael/opencv-fingerprint/src/4.bmp", CV_LOAD_IMAGE_GRAYSCALE);
    if(! sourceImage.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    Mat img = sourceImage.clone();
    localThreshold::binarisation(img, 40, 40);
    cv::threshold(img, img, 128, 255, cv::THRESH_BINARY);
    Mat binImg = img.clone();
    ideka::binOptimisation(img);

    namedWindow( "Originales Bild", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Originales Bild", sourceImage );                   // Show our image inside it.
    namedWindow( "Binarisiertes Bild", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Binarisiertes Bild", binImg );
    namedWindow( "Optimiertes Bild", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Optimiertes Bild", img );


    cv::bitwise_not(img, img);    //Inverse for bit-operations
    //skeletionizing
    GuoHall::thinning(img);
    cv::bitwise_not(img, img);
    namedWindow( "Skelettiertes Bild", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Skelettiertes Bild", img );

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;

}

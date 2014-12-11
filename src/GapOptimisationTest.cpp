#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "GapOptimisation.h"

using namespace cv;
using namespace std;

int main( int argc, const char* argv[] ) {
     if(argc != 2) {
        std::cout << "Please provide a target file as the parameter..." << std::endl;
        exit(1);
    }

    Mat sourceImage = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    if(!sourceImage.data) {
        cout <<  "Could not open image" << endl;
        return -1;
    }

    namedWindow("Originales Bild", WINDOW_AUTOSIZE);
    imshow("Originales Bild", sourceImage);
    moveWindow("Originales Bild", 0, 0);

    Mat dirField = sourceImage.clone();
    GapOptimisation::drawDirectionField(dirField);

    namedWindow("Direction Field", WINDOW_AUTOSIZE);
    imshow("Direction Field", dirField);
    moveWindow("Direction Field", sourceImage.cols + 30, 0);


    waitKey(0); // Wait for a keystroke in the window
    return 0;
}

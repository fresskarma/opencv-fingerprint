#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <future>

#include "ZhangSuen.h"
#include "GuoHall.h"

void f1(cv::Mat& source) {
    cv::Mat target(source.size(), CV_8UC1, cv::Scalar(0));
    cv::Mat img = source.clone();

    cv::Mat temp;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));

    // Clear image
    cv::bitwise_and(target, target, target);

    bool done;
    do
    {
        cv::morphologyEx(img, temp, cv::MORPH_OPEN, element);
        cv::bitwise_not(temp, temp);
        cv::bitwise_and(img, temp, temp);
        cv::bitwise_or(target, temp, target);
        cv::erode(img, img, element);

        double max;
        cv::minMaxLoc(img, 0, &max);
        done = (max == 0);
    } while (!done);

    temp.copyTo(source);
}




typedef void (*algorithm_function_ptr_t)(cv::Mat&);

// This leaves the input source unmodified so that we can display the original image
// in `skeletonize`.
void originalImage(cv::Mat& source) {
    return;
}



cv::Mat skeletonize(cv::Mat source, int threshold) {
    algorithm_function_ptr_t algorithms[] = { originalImage, ZhangSuen::thinning, GuoHall::thinning  };
    int num_algorithms = sizeof(algorithms)/sizeof(algorithms[0]);


    cv::Mat img = source.clone();
    cv::threshold(img, img, threshold, 255, cv::THRESH_BINARY);

    //cv::Mat temp(img.size(), CV_8UC1, cv::Scalar(0));
    cv::Mat output(img.size().height, img.size().width * num_algorithms,  CV_8UC1, cv::Scalar(0));

    for(int i=0; i<num_algorithms; i++) {
        cv::Mat temp = img.clone();
        algorithms[i](temp);

        cv::Mat targetArea = output(cv::Rect(img.size().width * i, 0, img.size().width, img.size().height));
        temp.copyTo(targetArea);
    }

    return output;
}



int trackbarValue = 127;
cv::Mat sourceImage;
const char* windowName = "Skeletoinzation Test";



void on_mouse(int event, int x, int y, int flags, void* param) {
    if (event != cv::EVENT_LBUTTONDOWN) {
        return;
    }
    std::cout << "Re-computing with threshold " << trackbarValue << std::endl;
    cv::Mat output = skeletonize(sourceImage, trackbarValue);
    cv::imshow(windowName, output);

}

int main(int argc, const char * argv[]) {
    // First argv is always the binary being executed
    if(argc != 2) {
        std::cout << "Please provide a target file as the parameter..." << std::endl;
        exit(1);
    }

    sourceImage = cv::imread(argv[1], 0);

    // The algorithms assume that the to-be-thinned area
    // is the white (i.e. 1) pixels, thus we invert our input.
    cv::bitwise_not(sourceImage, sourceImage);

    // GUI setup
    cv::namedWindow(windowName);
    cv::createTrackbar("Threshold", windowName, &trackbarValue, 255);
    cv::setMouseCallback(windowName, on_mouse);

    // Thinning
    cv::Mat output = skeletonize(sourceImage, trackbarValue);
    cv::imshow(windowName, output);

    cv::waitKey(0);
    return 0;
}

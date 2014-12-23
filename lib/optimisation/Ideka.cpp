#include "Ideka.h"
#include "GuoHall.h"

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

namespace ideka {
    using namespace cv;

    void binOptimisation(cv::Mat& im){
        ridgeEnhancement(im);
        valleyEnhancement(im);
        //smooth(im);
        //cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
        //morphologyEx( im, im, MORPH_CLOSE, element );
    }

    void ridgeEnhancement(cv::Mat& im){
        cv::Mat source = im.clone();
        cv::bitwise_not(source, source);    //Inverse of the source image for bit-operations

        //smoothing
        smooth(im);

        cv::bitwise_not(im, im);    //Inverse for bit-operations

        //skeletionizing
        GuoHall::thinning(im);

        //dilatation
        cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
        cv::dilate( im, im, element );

        //union
        cv::bitwise_or(im, source, im);

        cv::bitwise_not(im, im);    //back transformation
    }

    void valleyEnhancement(cv::Mat& im){
        cv::Mat im2 = im.clone();   //im2 with inverse flagimage
        cv::Mat source = im.clone();
        cv::Mat flagImg = im.clone();    //Flag-image
        flagImage(flagImg);
        cv::Mat flagImgInv = im.clone();  //flag-image inverse
        cv::bitwise_not(flagImg, flagImgInv);

        //inverse all the images (for bit-operations)
        cv::bitwise_not(im, im);
        cv::bitwise_not(im2, im2);
        cv::bitwise_not(flagImg, flagImg);
        cv::bitwise_not(flagImgInv, flagImgInv);

        //source AND flagImage
        cv::bitwise_and(im, flagImg, im);

        //erode source
        cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
        cv::erode( im2, im2, element );

        //eroded AND inverse flagImage
        cv::bitwise_and(im2, flagImgInv, im2);

        //Union
        cv::bitwise_or(im, im2, im);

        cv::bitwise_not(im, im);    //back transformation

    }

    void flagImage(cv::Mat& im){
        //smoothing
        smooth(im);

        cv::bitwise_not(im, im);    //Inverse for bit-operations

        //skeletionizing
        GuoHall::thinning(im);

        //dilatation
        cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
        cv::dilate( im, im, element );

        cv::bitwise_not(im, im);    //back transformation
    }

    void smooth(cv::Mat& im){
        int numIterations = 1;
        cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
        //closing
        morphologyEx( im, im, MORPH_CLOSE, element, Point(-1,-1), numIterations, BORDER_CONSTANT, morphologyDefaultBorderValue() );

        //opening
        //morphologyEx( im, im, MORPH_CLOSE, element, Point(-1,-1), numIterations, BORDER_CONSTANT, morphologyDefaultBorderValue() );
    }





}

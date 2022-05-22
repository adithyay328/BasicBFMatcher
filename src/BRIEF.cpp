#include <opencv2/opencv.hpp>
#include "BRIEF.hpp"
#include <array>
#include <stdlib.h>
#include <iostream>

// Returns the intensity of the pixel, or the default
// intensity if the coordinate is not in the image
int brief_getIntensity(cv::Mat image, int col, int row) {
    if ( (col >= 0 && col < image.cols) && (row >= 0 && row < image.rows) ) {
        return (int)image.at<uchar>(row, col);
    } else {
        return DEFAULT_INTENSITY;
    }
};

void initPairs(std::array<SamplingPair, DESC_LEN>* pairs, int patchSize) {
    // Initailizing RNG
    srand (time(0));

    // Generating DESC_LEN sampling pairs using RNG
    for(int i = 0; i < DESC_LEN; i++) {
        // Stores an individual sampling pair
        SamplingPair samplePair;
        
        cv::Point pOne, pTwo;
        pOne.x = rand() % patchSize - ( (rand() % patchSize) / 2 );
        pOne.y = rand() % patchSize -  ( (rand() % patchSize) / 2 );

        pTwo.x = rand() % patchSize - ( (rand() % patchSize) / 2 );
        pTwo.y = rand() % patchSize - ( (rand() % patchSize) / 2 );

        samplePair.p1 = pOne;
        samplePair.p2 = pTwo;

        (*pairs)[i] = samplePair;
    }
};

// Implementing both of our constructors
BRIEFDescriptor::BRIEFDescriptor(int pSize) {
    patchSize = pSize;
    
    initPairs(&samplingPairs, patchSize);
}

BRIEFDescriptor::BRIEFDescriptor() {
    patchSize = PATCH_SIZE;
    initPairs(&samplingPairs, patchSize);
}

// Implementing the single point descriptor calculation
std::bitset<DESC_LEN>* BRIEFDescriptor::calcDescriptor(cv::Mat img, cv::Point point) {
    // Converting to gray scale
    cv::Mat img_gray;
    cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY, 1);

    // Declaring the result bitset
    std::bitset<DESC_LEN>* resPointer = new std::bitset<DESC_LEN>();

    // Generating the descriptor bit-by-bit
    for(int i = 0; i < DESC_LEN; i++) {
        // Getting our sampling pair
        SamplingPair sPair = this->samplingPairs[i];

        // Getting each cv point
        cv::Point p1 = sPair.p1;
        cv::Point p2 = sPair.p2;

        // Getting point intensities
        int intOne = brief_getIntensity(img_gray, point.x + p1.x, point.y + p1.y);
        int intTwo = brief_getIntensity(img_gray, point.x + p2.x, point.y + p2.y);
        
        // Setting the bit value to the test output
        (*resPointer)[i] = (intOne < intTwo);
    }

    return resPointer;
};

std::vector<std::bitset<DESC_LEN>>* BRIEFDescriptor::calcDescriptors(cv::Mat img, std::vector<cv::Point>* points) {
    // Declaring our result vector
    std::vector<std::bitset<DESC_LEN>>* resPointer = new std::vector<std::bitset<DESC_LEN>>();
    resPointer -> reserve(points -> size());

    // Iterating over the entire input list and sotring the corresponding
    // descriptor in the result vector
    for(int i = 0; i < points -> size(); i++) {
        std::bitset<DESC_LEN>* desc = this -> calcDescriptor(img, points -> at(i));
        resPointer -> push_back(*desc);
        delete desc;
    }

    return resPointer;
}
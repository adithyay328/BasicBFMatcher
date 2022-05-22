#pragma once

#include <opencv2/opencv.hpp>
#include <list>

// Binary descriptors are stored as bitsets
#include <bitset>

// Descriptor length needs to be known at compile time
const int DESC_LEN = 2048;

// Patch size of descriptor. Represents the length of one side of the
// square patch. This / 2 should be the x and y distance
// between the center and the edges of the patch. This is important
// since we need to run this 
const int PATCH_SIZE = 30;

// This constant defines what intensity is
// returned if a point's coordinates are
// not in an image
const int DEFAULT_INTENSITY = 0;

// This header file describes the API for the BRIEF
// descriptor

// Sampling pairs store the column and row value of both points
struct SamplingPair {
    cv::Point p1, p2;
};

// Apart from the descriptor length, everything else is configurable.
// This limitation is mainly because the 
class BRIEFDescriptor {
    public:
    int patchSize;
    std::array<SamplingPair, DESC_LEN> samplingPairs;

    // Default constructor that uses the default values
    // specified in this header file
    BRIEFDescriptor();
    BRIEFDescriptor(int pSizeVal);

    // Runs descriptor on one point in the image. Takes in the raw BGR
    // image, performs all extra conversions internally.
    std::bitset<DESC_LEN>* calcDescriptor(cv::Mat img, cv::Point point);
    
    // Calculates descriptors for a sequence of points in the image.
    std::vector<std::bitset<DESC_LEN>>* calcDescriptors(cv::Mat img, std::vector<cv::Point>* points);
};

// Image is expected to be BGR, all conversions happen internally
std::list<std::bitset<DESC_LEN>>* briefDescriptor(cv::Mat inputImg, std::list<cv::Point>* keyPoints);
#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <array>

// This header file describes the API for the FAST detector

// Constants for FAST

// Defining our bresenham circle as having
// radius 3. This is just the way this
// detector is configured. Note, this implementation
// of pixel selection only works for radius 3; hasn't
// been generalized just yet
const int BRESRADIUS = 3;

// The number of points that need to be greater or lower.
// This is arbitrary, we can learn it later
const int NUMBEROFINTENSITIES = 11;

// This is the threshold value. Arbitrarily selected
const int THRESH = 10;

// This class represents a FAST detector with a specific
// set of config paramaters. The above constants are the defaults
class FASTDetector {
    public:
    // All configurable params are public
    int numIntens, thresh;

    private: int radius;

    public:
    // Default constructor
    FASTDetector();

    // Constructor with support for custom config vals
    FASTDetector(int numIntensities, int threshVal);

    // The actual detection function. Takes in a BGR image,
    // and returns a vector of points that coresponds to all the features
    // it found.
    std::vector<cv::Point>* detect(cv::Mat image);
};
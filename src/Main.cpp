#include <opencv2/opencv.hpp>

#include "BRIEF.hpp"
#include "FAST.hpp"
#include "BFMatch.hpp"

#include <vector>
#include <bitset>

int main(int argc, char** argv) {
    // Loading image
    if ( argc != 3 ) {
        printf("usage: DisplayImage.out <Image_Path> <Image_Path>\n");
        return -1;
    };

    // Loading the first image
    cv::Mat firstImage;
    firstImage = cv::imread( argv[1], 1 );
    if ( !firstImage.data ) {
        printf("No firstImage data \n");
        return -1;
    };

    // Loading the second image
    cv::Mat secondImage;
    secondImage = cv::imread( argv[2], 1 );
    if ( !secondImage.data ) {
        printf("No secondImage data \n");
        return -1;
    };

    cv::resize(firstImage, firstImage, cv::Size(), 2, 2);
    cv::resize(secondImage, secondImage, cv::Size(), 2, 2);

    // Running FAST on both images
    FASTDetector myFast = FASTDetector();
    std::vector<cv::Point>* imgOneFast = myFast.detect(firstImage);
    std::vector<cv::Point>* imgTwoFast = myFast.detect(secondImage);

    // Running BRIEF on both images
    BRIEFDescriptor myBrief = BRIEFDescriptor();
    std::vector<std::bitset<DESC_LEN>>* imgOneBrief = myBrief.calcDescriptors(firstImage, imgOneFast);
    std::vector<std::bitset<DESC_LEN>>* imgTwoBrief = myBrief.calcDescriptors(secondImage, imgTwoFast);

    // Running bfmatch on first 20 points in img one descriptors
    for(int i = 0; i < 20; i++) {
        std::vector<int>* res = bfMatch(&(imgOneBrief -> at(i)), imgTwoBrief);

        // Visualizing the matches

        // Copying images first to draw on
        cv::Mat firstClone = firstImage.clone();
        cv::Mat secondClone = secondImage.clone();

        // Drawing on first image
        cv::circle(firstClone, imgOneFast -> at(i), 20, cv::Scalar(0, 0, 255), cv::LINE_8);

        // Drawing best 30 matches on second image
        for(int j = 0; j < 30; j++) {
            cv::circle(secondClone, imgTwoFast -> at(res -> at(j)), j, cv::Scalar(0, 0, 255), cv::LINE_8);
        }

        // Showing both images
        cv::imshow("Second", secondClone);
        cv::imshow("First", firstClone);
        cv::waitKey(0);

        cv::destroyAllWindows();
    }
}
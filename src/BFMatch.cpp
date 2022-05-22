#include <list>
#include <vector>
#include <map>
#include <utility>

#include "BFMatch.hpp"
#include "BRIEF.hpp"

std::vector<int>* bfMatch(std::bitset<DESC_LEN>* targetPointer, std::vector<std::bitset<DESC_LEN>>* imTwoDescriptors) {
    // Initializing and reserving space for all values in the result vector
    std::vector<int>* res = new std::vector<int>();
    res -> reserve(imTwoDescriptors -> size());

    // Internally, we're using a map to store a pair of
    // hamming : index, so that when we want to get them all in order,
    // it's as simple as iterating over a map
    std::multimap<int, int> map;

    // Iterating over every descriptor in the second image
    for(int i = 0; i < imTwoDescriptors -> size(); i++) {
        // Calculating the hamming distance between the vectors
        std::bitset<DESC_LEN> xorVal = *targetPointer ^ (imTwoDescriptors -> at(i));
        int hamming = xorVal.count();

        // Putting the hamming:index pair into our map to keep it sorted
        map.insert({hamming, i});
    }

    // Moving values from map to result vector
    for(auto it = map.begin(); it != map.end(); it++) {
        res -> push_back(it -> second);
    }

    return res;
};
#include <list>
#include <vector>
#include <map>

#include "BFMatch.hpp"
#include "BRIEF.hpp"

std::vector<int>* bfMatch(std::bitset<DESC_LEN> target, std::list<std::bitset<DESC_LEN>>& imTwoDescriptors) {
    // Initializing and reserving space for all values in the result vector
    std::vector<int>* res = new std::vector<int>(imTwoDescriptors.size(), 0);

    // Internally, we're using a map to store a pair of
    // hamming : index, so that when we want to get them all in order,
    // it's as simple as iterating over a map
    std::map<int, int> map;

    // Iterating over every point in the 
}
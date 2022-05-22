#pragma once

#include <list>
#include <vector>

// Binary descriptors are stored as bitsets
#include <bitset>

// Need descriptor size from BRIEF
#include "BRIEF.hpp"

// This header file describes the API for the
// Brute Force matching algorithm implemented in
// this program

// Given a target vector and all the descriptors in the other image,
// this function returns all the indices of descriptors, sorted from best
// to worst match.
std::vector<int>* bfMatch(std::bitset<DESC_LEN>* target, std::vector<std::bitset<DESC_LEN>>* imTwoDescriptors);
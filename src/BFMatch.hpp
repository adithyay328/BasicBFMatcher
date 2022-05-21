#pragma once

#include <list>
#include <vector>

// Binary descriptors are stored as bitsets
#include <bits/stdc++.h>

// Need descriptor size from BRIEF
#include "BRIEF.hpp"

// This header file describes the API for the
// Brute Force matching algorithm implemented in
// this program
std::vector<int> bfMatch(std::bitset<DESC_LEN> target, std::list<std::bitset<DESC_LEN>>& imTwoDescriptors);
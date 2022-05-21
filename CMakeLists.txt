cmake_minimum_required(VERSION 3.10)

project(BasicBFMatcher)

# Ensuring that opencv is available to app
FIND_PACKAGE( OpenCV REQUIRED )

add_subdirectory(src)
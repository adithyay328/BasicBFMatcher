add_executable(app Main.cpp FAST.cpp BRIEF.cpp BFMatch.cpp)
TARGET_LINK_LIBRARIES (app ${OpenCV_LIBS})
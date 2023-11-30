// color_replacer.h
#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
// ensure #include "rec_selection.h" comes before #include "pixel_info.h"
#include "rec_selection.h"
#include <vector>

class Selection;  // Forward declaration

class ColorReplacer {
public:
    ColorReplacer(cv::Mat img, Selection& selection);
    void run();
    void saveImage();
    static void onMouse(int event, int x, int y, [[maybe_unused]] int flags, void* userdata);
    void replaceColor();


private:
    cv::Mat image;
    Selection& selection;  // Use a reference to Selection
    bool isMousePressed;
    void replaceWithStoredPixels();
};

// main.cpp
#include <iostream>
#include <opencv2/opencv.hpp>
#include "color_replacer.h"
#include "rec_selection.h"

int main() {
    std::string imagePath = R"(C:\Users\denis\AppData\Local\JetBrains\CLion Projekts\beautifulflowers.jpg)";
    // R"( )"; copy and paste raw file path in parentheses
    // instead of replacing all backslashes with slash
    cv::Mat image = cv::imread(imagePath);
    cv::namedWindow("Image Viewer");

    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image." << std::endl;
        return -1;
    }

    Selection selection(image);

    ColorReplacer colorReplacer(image, selection);

    // this will open the image window and wait for user interaction
    colorReplacer.run();

    // save modified image
    colorReplacer.saveImage();

    return 0;
}

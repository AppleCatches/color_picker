// rec_selection.cpp
#include <iostream>
#include <opencv2/opencv.hpp>
#include "pixel_info.h"
#include "rec_selection.h"

// Implementation of the Selection class member functions
Selection::Selection(const cv::Mat& image) {
    selectedImage = image.clone();
    // Initialize other variables if needed
    selecting = false;
    startX = startY = endX = endY = 0; // Initialize to zero or appropriate default values
}

void Selection::drawSelection(cv::Mat& image) const {
    if (selecting) {
        cv::rectangle(image, cv::Point(startX, startY), cv::Point(endX, endY), cv::Scalar(255, 0, 0), 0);
    }
}


bool Selection::isSelected() const {
    // Implement the logic to check whether a selection is currently active
    return selecting;
}

cv::Vec3b Selection::getReplacementColor() const {
    // Return the replacement color
    return replacementColor;
}

void Selection::startSelection(int x, int y) {
    // Implement the start of selection logic
    startX = x;
    startY = y;
    endX = x; // Initialize endX and endY to the starting point
    endY = y;
    selecting = true;
}

void Selection::endSelection() {
    // Implement the end of selection logic
    selecting = false;
    storeSelectedPixels(selectedImage);
}

void Selection::updateSelection(int x, int y) {
    // Implement the update of selection logic
    endX = x;
    endY = y;
    // Optionally update some visual feedback during selection
}

void Selection::setReplacementColor(const cv::Vec3b& color) {
    replacementColor = color;
}

const std::vector<PixelInfo>& Selection::getSelectedPixels() const {
    return selectedPixels;
}

void Selection::storeSelectedPixels(const cv::Mat& image) {
    // Clear the existing selectedPixels vector
    selectedPixels.clear();

    // Loop through the entire image and store pixel information
    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            PixelInfo pixel{};
            pixel.x = x;
            pixel.y = y;

            // Assuming the image is in BGR format
            cv::Vec3b color = image.at<cv::Vec3b>(y, x);
            pixel.red = color[2];
            pixel.green = color[1];
            pixel.blue = color[0];

            // Check if the pixel is within the rectangular selection
            if (x >= startX && x <= endX && y >= startY && y <= endY) {
                selectedPixels.push_back(pixel);
            }
        }
    }

    std::cout << "Area selected.\n" << std::endl; //stores selected pixels

    if (startX < 0 || startY < 0 || endX >= image.cols || endY >= image.rows) {
        std::cerr << "Error: Invalid selection region." << std::endl;
        return;
    }
}

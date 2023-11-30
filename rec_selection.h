//rec_selection.h
#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
//include #include "pixel_info.h" at the top
#include "pixel_info.h"
#include "color_replacer.h"
#include <vector>

class Selection {
public:
    explicit Selection(const cv::Mat& image);
    void drawSelection(cv::Mat& image) const;
    [[nodiscard]] bool isSelected() const;
    [[nodiscard]] cv::Vec3b getReplacementColor() const;
    void startSelection(int x, int y);
    void endSelection();
    void updateSelection(int x, int y);
    void setReplacementColor(const cv::Vec3b& color);
    [[nodiscard]] const std::vector<PixelInfo>& getSelectedPixels() const;
    void storeSelectedPixels(const cv::Mat& image);

private:
    cv::Mat selectedImage;
    bool selecting;
    int startX;
    int startY;
    int endX;
    int endY;
    std::vector<PixelInfo> selectedPixels;
    cv::Vec3b replacementColor;

};

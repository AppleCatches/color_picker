// color_replacer.cpp
#include "color_replacer.h"
#include "rec_selection.h"

ColorReplacer::ColorReplacer(cv::Mat img, Selection& selection)
        : image(std::move(img)),
          selection(selection),
          isMousePressed(false) {
    cv::setMouseCallback("Image Viewer", onMouse, this);
}


void ColorReplacer::run() {
    while (true) {
        cv::imshow("Image Viewer", image);

        int key = cv::waitKey(0);

        if (key == 32) {
            replaceColor();
            replaceWithStoredPixels();  // Call the replaceWithStoredPixels function
            cv::imshow("Image Viewer", image);
        } else if (key == 'q' || key == 27 || key == -1) {  // Check if the window was closed
            break;

        }
    }
}


void ColorReplacer::saveImage() {
    // Implement the logic to save the modified image
    cv::imwrite("output_image.jpg", image);
}

void ColorReplacer::replaceColor() {
    // Get the selected pixels (for debugging or future use)
    const std::vector<PixelInfo>& selectedPixels = selection.getSelectedPixels();

    // Get the replacement color set by the right mouse button
    cv::Vec3b replacementColor = selection.getReplacementColor();

    // Store the replacement color in the selection for later use
    selection.setReplacementColor(replacementColor);

    // Iterate through selected pixels and replace the color
    for (const auto& pixel : selectedPixels) {
        // Ensure the pixel coordinates are within the image boundaries
        if (pixel.x >= 0 && pixel.x < image.cols && pixel.y >= 0 && pixel.y < image.rows) {
            // Replace the color at the pixel coordinates with the stored replacement color
            auto& pixelColor = image.at<cv::Vec3b>(pixel.y, pixel.x);
            pixelColor = replacementColor;
        }
    }
    cv::imshow("Image Viewer", image);
}


void ColorReplacer::replaceWithStoredPixels() {
    // Get the stored selected pixels
    const std::vector<PixelInfo>& storedPixels = selection.getSelectedPixels();

    // Iterate through stored pixels and replace the color in the original image
    for (const auto& pixel : storedPixels) {
        // Ensure the pixel coordinates are within the image boundaries
        if (pixel.x >= 0 && pixel.x < image.cols && pixel.y >= 0 && pixel.y < image.rows) {
            // Replace the color in the original image at the stored pixel coordinates
            auto& pixelColor = image.at<cv::Vec3b>(pixel.y, pixel.x);
            pixelColor[2] = selection.getReplacementColor().val[2];  // Red channel
            pixelColor[1] = selection.getReplacementColor().val[1];  // Green channel
            pixelColor[0] = selection.getReplacementColor().val[0];  // Blue channel

        }
    }

    cv::imshow("Image Viewer", image);
}


void ColorReplacer::onMouse(int event, int x, int y, [[maybe_unused]] int flags, void* userdata) {
    auto* colorReplacer = static_cast<ColorReplacer*>(userdata);

    switch (event) {
        case cv::EVENT_LBUTTONDOWN:
            colorReplacer->selection.startSelection(x, y);
            colorReplacer->isMousePressed = true;
            break;

        case cv::EVENT_LBUTTONUP:
            colorReplacer->selection.endSelection();
            colorReplacer->isMousePressed = false;
            break;

        case cv::EVENT_MOUSEMOVE:
            if (colorReplacer->isMousePressed) {
                colorReplacer->selection.updateSelection(x, y);
                // Draw the selection on the image
                cv::Mat tempImage = colorReplacer->image.clone();
                colorReplacer->selection.drawSelection(tempImage);
                cv::imshow("Image Viewer", tempImage);
            }
            break;

        case cv::EVENT_RBUTTONDOWN:
            // Right-click logic for selecting, storing, and displaying pixel information
            // (x, y) coordinates
            std::cout << "Right mouse clicked at (" << x << ", " << y << ") " << std::endl;

            if (!colorReplacer->selection.isSelected()) {
                auto clickedColor = colorReplacer->image.at<cv::Vec3b>(y,x);

                // Extract individual color components
                int red = clickedColor[2];
                int green = clickedColor[1];
                int blue = clickedColor[0];

                // Store the selected pixel information
                colorReplacer->selection.setReplacementColor(clickedColor);

                // Display the selected pixel information in RGB values
                std::cout << "Replacement color set to\n" << "R:" << red << ", G:" << green << ", B:" << blue << std::endl;
            }
            break;

        default:
            // add an error/exception
            std::cout << " " << std::endl;
            // break;
            // (if the default keyword is used
            // as the last statement in a switch block,
            // it does not need a break)
    }
}

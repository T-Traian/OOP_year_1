#pragma once
#include "ImageProcessing.h" // Includes Image.h indirectly
#include <algorithm>
#include <cmath>

/**
 * @brief A utility class for drawing various shapes on an Image object.
 */
class Draw {
public:
    /**
     * @brief Draws a circle on the given image.
     * Uses a basic circle drawing algorithm to set pixels along the circle's circumference.
     * @param img The Image object to draw on.
     * @param center The center point of the circle.
     * @param radius The radius of the circle.
     * @param color The grayscale color (0-255) of the circle.
     */
    void drawCircle(Image& img, Point center, int radius, unsigned char color);

    /**
     * @brief Draws a line between two points on the given image.
     * Uses Bresenham's line algorithm for efficient pixel plotting.
     * @param img The Image object to draw on.
     * @param p1 The starting point of the line.
     * @param p2 The ending point of the line.
     * @param color The grayscale color (0-255) of the line.
     */
    void drawLine(Image& img, Point p1, Point p2, unsigned char color);

    /**
     * @brief Draws a rectangle on the given image using a Rectangle object.
     * This overload takes a Rectangle struct to define the region.
     * @param img The Image object to draw on.
     * @param rect The Rectangle object defining the position and dimensions.
     * @param color The grayscale color (0-255) of the rectangle.
     */
    void drawRectangle(Image& img, Rectangle rect, unsigned char color);

    /**
     * @brief Draws a rectangle on the given image using two Point objects.
     * This overload takes the top-left and bottom-right corner points.
     * @param img The Image object to draw on.
     * @param topLeft The top-left corner point of the rectangle.
     * @param bottomRight The bottom-right corner point of the rectangle.
     * @param color The grayscale color (0-255) of the rectangle.
     */
    void drawRectangle(Image& img, Point topLeft, Point bottomRight, unsigned char color);
};

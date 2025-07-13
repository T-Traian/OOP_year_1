#include "Drawing.h"

/**
 * @brief Draws a circle on the given image.
 * Uses a basic circle drawing algorithm to set pixels along the circle's circumference.
 * @param img The Image object to draw on.
 * @param center The center point of the circle.
 * @param radius The radius of the circle.
 * @param color The grayscale color (0-255) of the circle.
 */
void Draw::drawCircle(Image& img, Point center, int radius, unsigned char color) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        if (center.x + x < img.width() && center.x + x >= 0 && center.y + y < img.height() && center.y + y >= 0)
            img.at(center.x + x, center.y + y) = color;
        if (center.x + y < img.width() && center.x + y >= 0 && center.y + x < img.height() && center.y + x >= 0)
            img.at(center.x + y, center.y + x) = color;
        if (center.x - y < img.width() && center.x - y >= 0 && center.y + x < img.height() && center.y + x >= 0)
            img.at(center.x - y, center.y + x) = color;
        if (center.x - x < img.width() && center.x - x >= 0 && center.y + y < img.height() && center.y + y >= 0)
            img.at(center.x - x, center.y + y) = color;
        if (center.x - x < img.width() && center.x - x >= 0 && center.y - y < img.height() && center.y - y >= 0)
            img.at(center.x - x, center.y - y) = color;
        if (center.x - y < img.width() && center.x - y >= 0 && center.y - x < img.height() && center.y - x >= 0)
            img.at(center.x - y, center.y - x) = color;
        if (center.x + y < img.width() && center.x + y >= 0 && center.y - x < img.height() && center.y - x >= 0)
            img.at(center.x + y, center.y - x) = color;
        if (center.x + x < img.width() && center.x + x >= 0 && center.y - y < img.height() && center.y - y >= 0)
            img.at(center.x + x, center.y - y) = color;

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

/**
 * @brief Draws a line between two points on the given image.
 * Uses Bresenham's line algorithm for efficient pixel plotting.
 * @param img The Image object to draw on.
 * @param p1 The starting point of the line.
 * @param p2 The ending point of the line.
 * @param color The grayscale color (0-255) of the line.
 */
void Draw::drawLine(Image& img, Point p1, Point p2, unsigned char color) {
    int dx = std::abs(static_cast<int>(p2.x) - static_cast<int>(p1.x));
    int dy = -std::abs(static_cast<int>(p2.y) - static_cast<int>(p1.y));
    int sx = (p1.x < p2.x) ? 1 : -1;
    int sy = (p1.y < p2.y) ? 1 : -1; 
    int err = dx + dy; 

    while (true) {
        if (p1.x >= 0 && p1.x < img.width() && p1.y >= 0 && p1.y < img.height())
            img.at(p1.x, p1.y) = color;

        if (p1.x == p2.x && p1.y == p2.y) break;

        int e2 = 2 * err; 

        if (e2 >= dy) {
            err += dy;
            p1.x += sx;
        }

        if (e2 <= dx) {
            err += dx;
            p1.y += sy;
        }
    }
}

/**
 * @brief Draws a rectangle on the given image using a Rectangle object.
 * This overload takes a Rectangle struct to define the region.
 * It draws the four lines forming the rectangle.
 * @param img The Image object to draw on.
 * @param rect The Rectangle object defining the position and dimensions.
 * @param color The grayscale color (0-255) of the rectangle.
 */
void Draw::drawRectangle(Image& img, Rectangle rect, unsigned char color) {
    // Draw top line
    drawLine(img, Point(rect.x, rect.y), Point(rect.x + rect.width - 1, rect.y), color);
    // Draw bottom line
    drawLine(img, Point(rect.x, rect.y + rect.height - 1), Point(rect.x + rect.width - 1, rect.y + rect.height - 1), color);
    // Draw left line
    drawLine(img, Point(rect.x, rect.y), Point(rect.x, rect.y + rect.height - 1), color);
    // Draw right line
    drawLine(img, Point(rect.x + rect.width - 1, rect.y), Point(rect.x + rect.width - 1, rect.y + rect.height - 1), color);
}

/**
 * @brief Draws a rectangle on the given image using two Point objects.
 * This overload takes the top-left and bottom-right corner points.
 * It draws the four lines forming the rectangle.
 * @param img The Image object to draw on.
 * @param topLeft The top-left corner point of the rectangle.
 * @param bottomRight The bottom-right corner point of the rectangle.
 * @param color The grayscale color (0-255) of the rectangle.
 */
void Draw::drawRectangle(Image& img, Point topLeft, Point bottomRight, unsigned char color) {
    // Draw top line: from topLeft to (bottomRight.x, topLeft.y)
    drawLine(img, topLeft, Point(bottomRight.x, topLeft.y), color);
    // Draw bottom line: from (topLeft.x, bottomRight.y) to bottomRight
    drawLine(img, Point(topLeft.x, bottomRight.y), bottomRight, color);
    // Draw left line: from topLeft to (topLeft.x, bottomRight.y)
    drawLine(img, topLeft, Point(topLeft.x, bottomRight.y), color);
    // Draw right line: from (bottomRight.x, topLeft.y) to bottomRight
    drawLine(img, Point(bottomRight.x, topLeft.y), bottomRight, color);
}

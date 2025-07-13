#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdexcept>

class Size {
public:
	unsigned int width;
	unsigned int height;

	/**
	 * @brief Constructs a Size object with specified width and height.
	 * @param w The width.
	 * @param h The height.
	 */
	Size(unsigned int w, unsigned int h) : width(w), height(h) {}
};

/**
 * @brief Represents a 2D point with x and y coordinates.
 */
class Point {
public:
	unsigned int x; 
	unsigned int y; 

	/**
	 * @brief Default constructor. Initializes coordinates to (0, 0).
	 */
	Point() : x(0), y(0) {}

	/**
	 * @brief Parameterized constructor. Initializes coordinates to specified values.
	 * @param x The x-coordinate.
	 * @param y The y-coordinate.
	 */
	Point(unsigned int x, unsigned int y) : x(x), y(y) {}

	/**
	 * @brief Overloads the stream insertion operator for Point.
	 * @param os The output stream.
	 * @param pt The Point object to insert.
	 * @return A reference to the output stream.
	 */
	friend std::ostream& operator<<(std::ostream& os, const Point& pt) {
		os << pt.x << " " << pt.y;
		return os;
	}

	/**
	 * @brief Overloads the stream extraction operator for Point.
	 * @param is The input stream.
	 * @param pt The Point object to extract into.
	 * @return A reference to the input stream.
	 */
	friend std::istream& operator>>(std::istream& is, Point& pt) {
		is >> pt.x >> pt.y;
		return is;
	}
};

/**
 * @brief Represents a rectangular region with top-left coordinates, width, and height.
 */
class Rectangle {
public:
	unsigned int x, y, height, width;

	/**
	 * @brief Default constructor. Initializes all fields to 0.
	 */
	Rectangle() : x(0), y(0), height(0), width(0) {}

	/**
	 * @brief Parameterized constructor. Initializes rectangle with specified position and dimensions.
	 * @param x The x-coordinate of the top-left corner.
	 * @param y The y-coordinate of the top-left corner.
	 * @param height The height of the rectangle.
	 * @param width The width of the rectangle.
	 */
	Rectangle(unsigned int x, unsigned int y, unsigned int height, unsigned int width)
		: x(x), y(y), height(height), width(width) {
	}

	/**
	 * @brief Constructs a Rectangle from two Point objects.
	 * @param topLeft The top-left corner point.
	 * @param bottomRight The bottom-right corner point.
	 */
	Rectangle(const Point& topLeft, const Point& bottomRight) {
		x = topLeft.x;
		y = topLeft.y;
		width = bottomRight.x - topLeft.x;
		height = bottomRight.y - topLeft.y;
	}

	/**
	 * @brief Overloads the stream insertion operator for Rectangle.
	 * @param os The output stream.
	 * @param rect The Rectangle object to insert.
	 * @return A reference to the output stream.
	 */
	friend std::ostream& operator<<(std::ostream& os, const Rectangle& rect) {
		os << rect.x << " " << rect.y << " " << rect.width << " " << rect.height;
		return os;
	}

	/**
	 * @brief Overloads the stream extraction operator for Rectangle.
	 * @param is The input stream.
	 * @param rect The Rectangle object to extract into.
	 * @return A reference to the input stream.
	 */
	friend std::istream& operator>>(std::istream& is, Rectangle& rect) {
		is >> rect.x >> rect.y >> rect.width >> rect.height;
		return is;
	}

	/**
	 * @brief Overloads the addition operator to translate the rectangle by a Point.
	 * @param delta The Point representing the translation vector.
	 * @return A new Rectangle translated by the delta.
	 */
	Rectangle operator+(const Point& delta) const;

	/**
	 * @brief Overloads the subtraction operator to translate the rectangle by a Point.
	 * @param delta The Point representing the translation vector.
	 * @return A new Rectangle translated by the negative of the delta.
	 */
	Rectangle operator-(const Point& delta) const;

	/**
	 * @brief Overloads the bitwise AND operator to compute the intersection of two rectangles.
	 * @param other The other Rectangle to intersect with.
	 * @return A new Rectangle representing the intersection.
	 */
	Rectangle operator&(const Rectangle& other) const;

	/**
	 * @brief Overloads the bitwise OR operator to compute the union of two rectangles.
	 * @param other The other Rectangle to unite with.
	 * @return A new Rectangle representing the union.
	 */
	Rectangle operator|(const Rectangle& other) const;
};

/**
 * @brief Represents a grayscale image as a 2D array of pixels.
 * Each pixel can take a value between [0, 255].
 */
class Image {
private:
	unsigned char** m_data;   
	unsigned int m_width;    
	unsigned int m_height;   

public:
	/**
	 * @brief Default constructor. Initializes an empty image.
	 */
	Image();

	/**
	 * @brief Constructor. Initializes an image with specified width and height, allocating memory.
	 * @param width The width of the image.
	 * @param height The height of the image.
	 */
	Image(unsigned int width, unsigned int height);

	/**
	 * @brief Copy constructor. Creates a deep copy of another Image object.
	 * @param other The Image object to copy from.
	 */
	Image(const Image& other);

	/**
	 * @brief Destructor. Releases the memory allocated for the image data.
	 */
	~Image();

	/**
	 * @brief Loads an image from a PGM file.
	 * @param ImagePath The path to the PGM file.
	 * @return True if the image was loaded successfully, false otherwise.
	 */
	bool load(std::string ImagePath);

	/**
	 * @brief Saves the image to a PGM file.
	 * @param ImagePath The path where the PGM file will be saved.
	 * @return True if the image was saved successfully, false otherwise.
	 */
	bool save(std::string ImagePath);

	/**
	 * @brief Copy assignment operator. Performs a deep copy assignment.
	 * @param other The Image object to assign from.
	 * @return A reference to the current Image object.
	 */
	Image& operator=(const Image& other);

	/**
	 * @brief Overloads the addition operator for element-wise image addition.
	 * Images must have the same dimensions. Values are clipped to [0, 255].
	 * @param other The other Image to add.
	 * @return A new Image object representing the sum.
	 * @throws std::runtime_error if images have different dimensions.
	 */
	Image operator+(const Image& other);

	/**
	 * @brief Overloads the subtraction operator for element-wise image subtraction.
	 * Images must have the same dimensions. Values are clipped to [0, 255].
	 * @param other The other Image to subtract.
	 * @return A new Image object representing the difference.
	 * @throws std::runtime_error if images have different dimensions.
	 */
	Image operator-(const Image& other);

	/**
	 * @brief Extracts a region of interest (ROI) from the image using a Rectangle.
	 * Performs a deep copy of the pixels within the ROI.
	 * @param roiImg An Image object to store the extracted ROI.
	 * @param roiRect The Rectangle defining the region of interest.
	 * @return True if the ROI was successfully extracted, false if the ROI is invalid.
	 */
	bool getROI(Image& roiImg, Rectangle roiRect);

	/**
	 * @brief Extracts a region of interest (ROI) from the image using explicit coordinates and dimensions.
	 * Performs a deep copy of the pixels within the ROI.
	 * @param roiImg An Image object to store the extracted ROI.
	 * @param x The x-coordinate of the top-left corner of the ROI.
	 * @param y The y-coordinate of the top-left corner of the ROI.
	 * @param width The width of the ROI.
	 * @param height The height of the ROI.
	 * @return True if the ROI was successfully extracted, false if the ROI is invalid.
	 */
	bool getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height);

	/**
	 * @brief Checks if the image is empty (has no allocated data).
	 * @return True if the image is empty, false otherwise.
	 */
	bool isEmpty() const;

	/**
	 * @brief Returns the size (width and height) of the image.
	 * @return A Size object containing the width and height.
	 */
	Size size() const;

	/**
	 * @brief Returns the width of the image.
	 * @return The width of the image.
	 */
	unsigned int width() const;

	/**
	 * @brief Returns the height of the image.
	 * @return The height of the image.
	 */
	unsigned int height() const;

	/**
	 * @brief Returns a reference to the pixel at the specified coordinates (x, y).
	 * This allows modification of the pixel value.
	 * @param x The x-coordinate of the pixel.
	 * @param y The y-coordinate of the pixel.
	 * @return A reference to the pixel value.
	 */
	unsigned char& at(unsigned int x, unsigned int y);

	/**
	 * @brief Returns a reference to the pixel at the specified Point.
	 * This allows modification of the pixel value.
	 * @param pt The Point object representing the pixel's coordinates.
	 * @return A reference to the pixel value.
	 */
	unsigned char& at(Point pt);

	/**
	 * @brief Returns a const reference to the pixel at the specified coordinates (x, y).
	 * This prevents modification of the pixel value.
	 * @param x The x-coordinate of the pixel.
	 * @param y The y-coordinate of the pixel.
	 * @return A const reference to the pixel value.
	 */
	const unsigned char& at(unsigned int x, unsigned int y) const;

	/**
	 * @brief Returns a pointer to the beginning of the specified row.
	 * @param y The index of the row.
	 * @return A pointer to the first pixel in the row, or nullptr if the row index is out of bounds.
	 */
	unsigned char* row(int y);

	/**
	 * @brief Releases the memory allocated for the image data.
	 * Sets width and height to 0 and m_data to nullptr.
	 */
	void release();

	/**
	 * @brief Overloads the stream insertion operator (<<) to print the image data to an output stream.
	 * Pixels are printed in a 2D grid format.
	 * @param os The output stream.
	 * @param dt The Image object to print.
	 * @return A reference to the output stream.
	 */
	friend std::ostream& operator<<(std::ostream& os, const Image& dt);

	/**
	 * @brief Static method to create an Image filled with zeros (black pixels).
	 * @param width The width of the new image.
	 * @param height The height of the new image.
	 * @return A new Image object filled with zeros.
	 */
	static Image zeros(unsigned int width, unsigned int height);

	/**
	 * @brief Static method to create an Image filled with ones.
	 * @param width The width of the new image.
	 * @param height The height of the new image.
	 * @return A new Image object filled with ones.
	 */
	static Image ones(unsigned int width, unsigned int height);
};

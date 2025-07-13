#include "Image.h"

/**
 * @brief Overloads the addition operator to translate the rectangle by a Point.
 * @param delta The Point representing the translation vector.
 * @return A new Rectangle translated by the delta.
 */
Rectangle Rectangle::operator+(const Point& delta) const {
    return Rectangle(x + delta.x, y + delta.y, height, width);
}

/**
 * @brief Overloads the subtraction operator to translate the rectangle by a Point.
 * @param delta The Point representing the translation vector.
 * @return A new Rectangle translated by the negative of the delta.
 */
Rectangle Rectangle::operator-(const Point& delta) const {
    return Rectangle(x - delta.x, y - delta.y, height, width);
}

/**
 * @brief Overloads the bitwise OR operator to compute the union of two rectangles.
 * @param other The other Rectangle to unite with.
 * @return A new Rectangle representing the union.
 */
Rectangle Rectangle::operator&(const Rectangle& other) const {
    unsigned int newX = std::max(x, other.x);
    unsigned int newY = std::max(y, other.y);
    unsigned int newWidth = std::min(x + width, other.x + other.width) - newX;
    unsigned int newHeight = std::min(y + height, other.y + other.height) - newY; //The Y-axis increases downwards.
    return Rectangle(newX, newY, newHeight, newWidth);
}

/**
 * @brief Overloads the bitwise AND operator to compute the intersection of two rectangles.
 * @param other The other Rectangle to intersect with.
 * @return A new Rectangle representing the intersection.
 */
Rectangle Rectangle::operator|(const Rectangle& other) const {
    unsigned int newX = std::min(x, other.x);
    unsigned int newY = std::min(y, other.y);
    unsigned int newWidth = std::max(x + width, other.x + other.width) - newX;
    unsigned int newHeight = std::max(y + height, other.y + other.height) - newY;
    return Rectangle(newX, newY, newHeight, newWidth);
}

/**
 * @brief Default constructor. Initializes an empty image.
 */
Image::Image() : m_data(nullptr), m_width(0), m_height(0) {
}

/**
 * @brief Constructor. Initializes an image with specified width and height, allocating memory.
 * @param width The width of the image.
 * @param height The height of the image.
 */
Image::Image(unsigned int width, unsigned int height) : m_width(width), m_height(height) {
    m_data = new unsigned char* [m_height];
    for (unsigned int i = 0; i < m_height; i++) {
        m_data[i] = new unsigned char[m_width];
    }
}

/**
 * @brief Copy constructor. Creates a deep copy of another Image object.
 * @param other The Image object to copy from.
 */
Image::Image(const Image& other) : m_height(other.height()), m_width(other.width()) {
    if (other.m_data && m_width > 0 && m_height > 0) {
        m_data = new unsigned char* [m_height];
        for (unsigned int i = 0; i < m_height; ++i) {
            m_data[i] = new unsigned char[m_width];
            for (unsigned int j = 0; j < m_width; ++j) {
                m_data[i][j] = other.m_data[i][j];
            }
        }
    }
    else {
        m_data = nullptr;
        m_width = m_height = 0;
    }
}

/**
 * @brief Destructor. Releases the memory allocated for the image data.
 */
Image::~Image() {
    release();
}

/**
 * @brief Copy assignment operator. Performs a deep copy assignment.
 * @param other The Image object to assign from.
 * @return A reference to the current Image object.
 */
Image& Image::operator= (const Image& other) {
    if (this != &other) {
        if (other.m_data && other.m_width > 0 && other.m_height > 0) {
            release();
            m_width = other.width();
            m_height = other.height();
            m_data = new unsigned char* [m_height];
            for (unsigned int i = 0; i < m_height; ++i) {
                m_data[i] = new unsigned char[m_width];
                for (unsigned int j = 0; j < m_width; ++j) {
                    m_data[i][j] = other.m_data[i][j];
                }
            }
        }
    }
    else
        std::exception("Invalid assignment.");
    return *this;
}

/**
 * @brief Loads an image from a PGM file.
 * @param imagePath The path to the PGM file.
 * @return True if the image was loaded successfully, false otherwise.
 */
bool Image::load(std::string imagePath) {
    std::ifstream file(imagePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << imagePath << std::endl;
        return false;
    }

    std::string magicNumber;
    file >> magicNumber;
    if (magicNumber != "P2") {
        std::cerr << "Invalid magic number: " << magicNumber << ". Expected P2\n";
        return false;
    }

    file >> m_width >> m_height;
    unsigned int maxVal;
    file >> maxVal;

    if (maxVal > 255) {
        std::cerr << "Max value " << maxVal << " is greater than 255.  This code only supports 8-bit grayscale.\n";
        return false;
    }

    m_data = new unsigned char* [m_height];
    for (unsigned int i = 0; i < m_height; ++i) {
        m_data[i] = new unsigned char[m_width];
    }

    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            int pixelValue;
            file >> pixelValue;
            m_data[y][x] = static_cast<unsigned char>(pixelValue);
        }
    }
    file.close();
    return true;
}

/**
 * @brief Saves the image to a PGM file.
 * @param imagePath The path where the PGM file will be saved.
 * @return True if the image was saved successfully, false otherwise.
 */
bool Image::save(const std::string imagePath) {
    std::ofstream file(imagePath);
    if (!file) {
        std::cerr << "Error opening file: " << imagePath << std::endl;
        return false;
    }
    file << "P2\n" << m_width << " " << m_height << "\n255\n";
    for (unsigned int y = 0; y < m_height; y++) {
        for (unsigned int x = 0; x < m_width; x++) {
            file << static_cast<int>(m_data[y][x]) << " ";
        }
        file << "\n";
    }
    return true;
}

/**
 * @brief Overloads the addition operator for element-wise image addition.
 * Images must have the same dimensions. Values are clipped to [0, 255].
 * @param other The other Image to add.
 * @return A new Image object representing the sum.
 * @throws std::runtime_error if images have different dimensions.
 */
Image Image::operator+(const Image& other) {
    if (width() != other.width() || height() != other.height()) {
        throw std::runtime_error("Images must have the same dimensions for addition.");
    }

    Image result(width(), height());
    for (unsigned int y = 0; y < height(); ++y) {
        for (unsigned int x = 0; x < width(); ++x) {
            int sum = at(x, y) + other.at(x, y);
            result.at(x, y) = static_cast<unsigned char>(std::min(sum, 255)); // Clip to 255
        }
    }
    return result;
}

/**
 * @brief Overloads the subtraction operator for element-wise image subtraction.
 * Images must have the same dimensions. Values are clipped to [0, 255].
 * @param other The other Image to subtract.
 * @return A new Image object representing the difference.
 * @throws std::runtime_error if images have different dimensions.
 */
Image Image::operator-(const Image& other) {
    if (width() != other.width() || height() != other.height()) {
        throw std::runtime_error("Images must have the same dimensions for subtraction.");
    }

    Image result(width(), height());
    for (unsigned int y = 0; y < height(); ++y) {
        for (unsigned int x = 0; x < width(); ++x) {
            int diff = at(x, y) - other.at(x, y);
            result.at(x, y) = static_cast<unsigned char>(std::max(diff, 0)); // Clip to 0
        }
    }
    return result;
}

/**
 * @brief Extracts a region of interest (ROI) from the image using explicit coordinates and dimensions.
 * Performs a deep copy of the pixels within the ROI.
 * @param roiImg An Image object to store the extracted ROI.
 * @param x The x-coordinate of the top-left corner of the ROI.
 * @param y The y-coordinate of the top-left corner of the ROI.
 * @param w The width of the ROI.
 * @param h The height of the ROI.
 * @return True if the ROI was successfully extracted, false if the ROI is invalid.
 */
bool Image::getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
    if (x + w > m_width || y + h > m_height) return false;
    roiImg = Image(w, h);
    for (unsigned int i = 0; i < h; ++i) {
        for (unsigned int j = 0; j < w; ++j) {
            roiImg.m_data[i][j] = m_data[y + i][x + j];
        }
    }
    return true;
}

/**
 * @brief Extracts a region of interest (ROI) from the image using a Rectangle.
 * Performs a deep copy of the pixels within the ROI.
 * @param roiImg An Image object to store the extracted ROI.
 * @param roiRect The Rectangle defining the region of interest.
 * @return True if the ROI was successfully extracted, false if the ROI is invalid.
 */
bool Image::getROI(Image& roiImg, Rectangle roiRect) {
    return getROI(roiImg, roiRect.x, roiRect.y, roiRect.width, roiRect.height);
}

/**
 * @brief Releases the memory allocated for the image data.
 * Sets width and height to 0 and m_data to nullptr.
 */
void Image::release() {
    if (m_data) {
        for (unsigned int i = 0; i < m_height; ++i) {
            delete[] m_data[i];
        }
        delete[] m_data;
        m_data = nullptr;
    }
    m_width = 0;
    m_height = 0;
}

/**
 * @brief Returns a pointer to the beginning of the specified row.
 * @param y The index of the row.
 * @return A pointer to the first pixel in the row, or nullptr if the row index is out of bounds.
 */
unsigned char* Image::row(int y) {
    if (y < 0 || y >= m_height) return nullptr;
    return m_data[y];
}

/**
 * @brief Static method to create an Image filled with zeros (black pixels).
 * @param w The width of the new image.
 * @param h The height of the new image.
 * @return A new Image object filled with zeros.
 */
Image Image::zeros(unsigned int w, unsigned int h) { return Image(w, h); }

/**
 * @brief Static method to create an Image filled with ones.
 * @param w The width of the new image.
 * @param h The height of the new image.
 * @return A new Image object filled with ones.
 */
Image Image::ones(unsigned int w, unsigned int h) {
    Image img(w, h);
    for (unsigned int i = 0; i < h; ++i) {
        for (unsigned int j = 0; j < w; ++j) {
            img.m_data[i][j] = 1;
        }
    }
    return img;
}

/**
 * @brief Checks if the image is empty (has no allocated data).
 * @return True if the image is empty, false otherwise.
 */
bool Image::isEmpty() const {
    return m_data == nullptr;
}

/**
 * @brief Returns the size (width and height) of the image.
 * @return A Size object containing the width and height.
 */
Size Image::size() const {
    return Size(m_width, m_height);
}

/**
 * @brief Returns the width of the image.
 * @return The width of the image.
 */
unsigned int Image::width() const {
    return m_width;
}

/**
 * @brief Returns the height of the image.
 * @return The height of the image.
 */
unsigned int Image::height() const {
    return m_height;
}

/**
 * @brief Returns a reference to the pixel at the specified coordinates (x, y).
 * This allows modification of the pixel value.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @return A reference to the pixel value.
 */
unsigned char& Image::at(unsigned int x, unsigned int y) {
    return m_data[y][x];
}

/**
 * @brief Returns a reference to the pixel at the specified Point.
 * This allows modification of the pixel value.
 * @param pt The Point object representing the pixel's coordinates.
 * @return A reference to the pixel value.
 */
unsigned char& Image::at(Point pt) {
    return m_data[pt.y][pt.x];
}

/**
 * @brief Returns a const reference to the pixel at the specified coordinates (x, y).
 * This prevents modification of the pixel value.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @return A const reference to the pixel value.
 */
const unsigned char& Image::at(unsigned int x, unsigned int y) const {
    return m_data[y][x];
}

/**
 * @brief Overloads the stream insertion operator (<<) to print the image data to an output stream.
 * Pixels are printed in a 2D grid format.
 * @param os The output stream.
 * @param dt The Image object to print.
 * @return A reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, const Image& dt) {
    for (unsigned int i = 0; i < dt.height(); ++i) {
        for (unsigned int j = 0; j < dt.width(); ++j) {
            os << static_cast<int>(dt.at(j, i)) << " ";
        }
        os << std::endl;
    }
    return os;
}

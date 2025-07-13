#pragma once
#include "Image.h"
#include <vector>
#include <cmath>

/**
 * @brief Base class for image processing operations.
 * Defines a pure virtual process method that subclasses must implement.
 */
class ImageProcessing {
public:
    /**
     * @brief Pure virtual method to apply an image processing operation.
     * @param src The source image (input).
     * @param dst The destination image (output).
     */
    virtual void process(const Image& src, Image& dst) = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~ImageProcessing() {}
};

/**
 * @brief Implements brightness and contrast adjustment.
 * The operation is defined by F(x,y) = alpha * I(x,y) + beta,
 * where I(x,y) is the input pixel, F(x,y) is the output pixel.
 * alpha controls contrast (gain), beta controls brightness (bias).
 */
class BrightnessAndContrast : public ImageProcessing {
private:
    float alpha; // The gain parameter for contrast adjustment.
    int beta;    // The bias parameter for brightness adjustment.

public:
    /**
     * @brief Constructor. Initializes the BrightnessAndContrast object with alpha and beta values.
     * @param alpha The gain (contrast) value. Default is 1.0.
     * @param beta The bias (brightness) value. Default is 0.
     */
    BrightnessAndContrast(float alpha = 1.0f, int beta = 0);

    /**
     * @brief Applies brightness and contrast adjustment to the image.
     * Pixels values are clipped to the range [0, 255].
     * @param src The source image.
     * @param dst The destination image where the processed result will be stored.
     */
    void process(const Image& src, Image& dst) override;
};

/**
 * @brief Implements gamma correction.
 * The operation is defined by F(x,y) = I(x,y)^gamma.
 * Used to correct the overall brightness with a non-linear transformation.
 */
class GammaCorrection : public ImageProcessing {
private:
    float gamma; // The gamma encoding factor.

public:
    /**
     * @brief Constructor. Initializes the GammaCorrection object with a gamma value.
     * @param gamma The gamma encoding factor. Default is 1.0.
     */
    GammaCorrection(float gamma = 1.0f);

    /**
     * @brief Applies gamma correction to the image.
     * Pixel values are normalized to [0, 1], gamma corrected, then scaled back to [0, 255].
     * Values are clipped to the range [0, 255].
     * @param src The source image.
     * @param dst The destination image where the processed result will be stored.
     */
    void process(const Image& src, Image& dst) override;
};

/**
 * @brief Implements image convolution using a specified kernel.
 * Convolutions are used to extract features or apply filters (e.g., blur, edge detection).
 */
class ImageConvolution : public ImageProcessing {
private:
    std::vector<std::vector<float>> kernel; // The convolutional kernel (filter).

public:
    /**
     * @brief Constructor. Initializes the ImageConvolution object with a 2D kernel.
     * @param kernel A 2D vector representing the convolutional kernel.
     */
    ImageConvolution(const std::vector<std::vector<float>>& kernel);

    /**
     * @brief Applies convolution to the image using the stored kernel.
     * Handles image bounds and normalizes the sum by the sum of kernel weights.
     * @param src The source image.
     * @param dst The destination image where the processed result will be stored.
     */
    void process(const Image& src, Image& dst) override;
};

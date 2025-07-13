#include "ImageProcessing.h"

/**
 * @brief Constructor. Initializes the BrightnessAndContrast object with alpha and beta values.
 * @param alpha The gain (contrast) value.
 * @param beta The bias (brightness) value.
 */
BrightnessAndContrast::BrightnessAndContrast(float alpha, int beta) : alpha(alpha), beta(beta) {}

/**
 * @brief Applies brightness and contrast adjustment to the image.
 * Pixels values are clipped to the range [0, 255].
 * @param src The source image.
 * @param dst The destination image where the processed result will be stored.
 */
void BrightnessAndContrast::process(const Image& src, Image& dst) {
    if (src.isEmpty()) {
        return;
    }

    if (dst.width() != src.width() || dst.height() != src.height())
    {
        dst.release();
        dst = Image(src.width(), src.height()); 
    }

    for (unsigned int y = 0; y < src.height(); ++y) {
        for (unsigned int x = 0; x < src.width(); ++x) {
            float adjusted = src.at(y, x) * alpha + beta;
            if (adjusted < 0) adjusted = 0;
            if (adjusted > 255) adjusted = 255;
            dst.at(y, x) = static_cast<unsigned char>(adjusted);
        }
    }
}

/**
 * @brief Constructor. Initializes the GammaCorrection object with a gamma value.
 * @param gamma The gamma encoding factor.
 */
GammaCorrection::GammaCorrection(float gamma) : gamma(gamma) {}

/**
 * @brief Applies gamma correction to the image.
 * Pixel values are normalized to [0, 1], gamma corrected, then scaled back to [0, 255].
 * Values are clipped to the range [0, 255].
 * @param src The source image.
 * @param dst The destination image where the processed result will be stored.
 */
void GammaCorrection::process(const Image& src, Image& dst) {
    if (src.isEmpty()) {
        return;
    }

    if (dst.width() != src.width() || dst.height() != src.height())
    {
        dst.release();
        dst = Image(src.width(), src.height());
    }
    for (unsigned int y = 0; y < src.height(); ++y) {
        for (unsigned int x = 0; x < src.width(); ++x) {
            double normalized_input = static_cast<double>(src.at(x, y)) / 255.0;
            double temp = pow(normalized_input, 1.0 / gamma) * 255.0;
            if (temp > 255) temp = 255;
            if (temp < 0) temp = 0;
            dst.at(x, y) = static_cast<unsigned char>(temp);
        }
    }
}

/**
 * @brief Constructor. Initializes the ImageConvolution object with a 2D kernel.
 * @param kernel A 2D vector representing the convolutional kernel.
 */
ImageConvolution::ImageConvolution(const std::vector<std::vector<float>>& kernel) : kernel(kernel) {}

/**
 * @brief Applies convolution to the image using the stored kernel.
 * Handles image bounds and normalizes the sum by the sum of kernel weights.
 * @param src The source image.
 * @param dst The destination image where the processed result will be stored.
 */
void ImageConvolution::process(const Image& src, Image& dst) {
    if (src.isEmpty() || kernel.empty()) {
        dst.release();
        return;
    }

    const int kWidth = kernel[0].size();
    const int kHeight = kernel.size();
    const int kCenterX = kWidth / 2;
    const int kCenterY = kHeight / 2;


    if (dst.width() != src.width() || dst.height() != src.height()) {
        dst.release(); 
        dst = Image(src.width(), src.height());
    }

    for (int y = 0; y < src.height(); y++) {
        for (int x = 0; x < src.width(); x++) {
            float sum = 0.0;
            float kernelSum = 0.0; 

            for (int i = 0; i < kHeight; i++) {
                for (int j = 0; j < kWidth; j++) {
                    int srcX = x + (j - kCenterX);
                    int srcY = y + (i - kCenterY);

                    if (srcX >= 0 && srcX < src.width() && srcY >= 0 && srcY < src.height()) {
                        sum += kernel[i][j] * src.at(srcX, srcY);
                        kernelSum += kernel[i][j];
                    }
                }
            }

            // Normalize the sum by the sum of kernel weights used.
            // This prevents the image from becoming brighter/darker overall unless intended by the kernel.
            if (kernelSum == 0) {
                dst.at(x, y) = 0; 
            }
            else {
                float result = sum / kernelSum;
                if (result < 0) result = 0;
                if (result > 255) result = 255;
                dst.at(x, y) = static_cast<unsigned char>(result);
            }
        }
    }
}

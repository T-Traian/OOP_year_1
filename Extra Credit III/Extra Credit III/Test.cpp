#include "Image.h"
#include "ImageProcessing.h"
#include "Drawing.h"
#include "Test.h"

// Helper function to compare two images (similar to before)
bool compareImages(const Image& img1, const Image& img2) {
    if (img1.width() != img2.width() || img1.height() != img2.height()) {
        return false;
    }
    for (unsigned int y = 0; y < img1.height(); ++y) {
        for (unsigned int x = 0; x < img1.width(); ++x) {
            if (img1.at(x, y) != img2.at(x, y)) {
                return false;
            }
        }
    }
    return true;
}

void testImageConstructorAndBasic() {
    Image img1;
    assert(img1.isEmpty());
    assert(img1.width() == 0);
    assert(img1.height() == 0);

    Image img2(10, 10);
    assert(!img2.isEmpty());
    assert(img2.width() == 10);
    assert(img2.height() == 10);

    std::cout << "Image Constructor and Basic tests passed\n";
}

void testImageCopyConstructor() {
    Image img1(5, 5);
    for (unsigned int y = 0; y < img1.height(); ++y) {
        for (unsigned int x = 0; x < img1.width(); ++x) {
            img1.at(x, y) = static_cast<unsigned char>(x + y);
        }
    }

    Image img2 = img1;
    assert(compareImages(img1, img2));

    std::cout << "Image Copy Constructor tests passed\n";
}

void testImageAssignmentOperator() {
    Image img1(5, 5);
    for (unsigned int y = 0; y < img1.height(); ++y) {
        for (unsigned int x = 0; x < img1.width(); ++x) {
            img1.at(x, y) = static_cast<unsigned char>(x * y);
        }
    }

    Image img2(10, 10);
    img2 = img1;
    assert(compareImages(img1, img2));

    std::cout << "Image Assignment Operator tests passed\n";
}

void testImageLoadAndSave() {
    // Create a simple PGM for testing
    std::ofstream tempFile("temp.pgm");
    tempFile << "P2\n5 5\n255\n";
    for (int i = 0; i < 25; ++i) {
        tempFile << i << " ";
    }
    tempFile.close();

    Image img;
    assert(img.load("temp.pgm"));
    assert(img.width() == 5);
    assert(img.height() == 5);

    Image img2(5, 5);
    int count = 0;
    for (unsigned int y = 0; y < img2.height(); ++y) {
        for (unsigned int x = 0; x < img2.width(); ++x) {
            img2.at(x, y) = static_cast<unsigned char>(count++);
        }
    }
    assert(compareImages(img, img2));

    assert(img.save("temp_save.pgm"));

    //Cleanup
    std::remove("temp.pgm");
    std::remove("temp_save.pgm");

    std::cout << "Image Load and Save tests passed\n";
}

void testImageAddition() {
    Image img1(2, 2);
    img1.at(0, 0) = 10; img1.at(1, 0) = 20;
    img1.at(0, 1) = 30; img1.at(1, 1) = 40;

    Image img2(2, 2);
    img2.at(0, 0) = 5; img2.at(1, 0) = 15;
    img2.at(0, 1) = 25; img2.at(1, 1) = 35;

    Image result = img1 + img2;

    assert(result.at(0, 0) == 15);
    assert(result.at(1, 0) == 35);
    assert(result.at(0, 1) == 55);
    assert(result.at(1, 1) == 75);
    result.release();

    std::cout << "Image Addition tests passed\n";
}

void testImageSubtraction() {
    Image img1(2, 2);
    img1.at(0, 0) = 20; img1.at(1, 0) = 30;
    img1.at(0, 1) = 40; img1.at(1, 1) = 50;

    Image img2(2, 2);
    img2.at(0, 0) = 15; img2.at(1, 0) = 25;
    img2.at(0, 1) = 35; img2.at(1, 1) = 45;

    Image result = img1 - img2;

    assert(result.at(0, 0) == 5);
    assert(result.at(1, 0) == 5);
    assert(result.at(0, 1) == 5);
    assert(result.at(1, 1) == 5);

	result.release();

    std::cout << "Image Subtraction tests passed\n";
}

void testImageGetROI() {
    Image img(4, 4);
    int count = 0;
    for (unsigned int y = 0; y < img.height(); ++y) {
        for (unsigned int x = 0; x < img.width(); ++x) {
            img.at(x, y) = static_cast<unsigned char>(count++);
        }
    }

    Image roiImg;
    assert(img.getROI(roiImg, 1, 1, 2, 2));
    assert(roiImg.width() == 2);
    assert(roiImg.height() == 2);
    assert(roiImg.at(0, 0) == 5);
    assert(roiImg.at(1, 0) == 6);
    assert(roiImg.at(0, 1) == 9);
    assert(roiImg.at(1, 1) == 10);

    Image roiImg2;
    Rectangle rect(1, 1, 2, 2);
    assert(img.getROI(roiImg2, rect));
    assert(compareImages(roiImg, roiImg2));
	roiImg2.release();
    roiImg.release();

    std::cout << "Image GetROI tests passed\n";
}

void testBrightnessAndContrast() {
    Image src(2, 2);
    src.at(0, 0) = 50;
    src.at(1, 0) = 100;
    src.at(0, 1) = 150;
    src.at(1, 1) = 200;

    Image expectedDst(2, 2);
    BrightnessAndContrast bc(1.5f, 10); // Example values

    // Manually calculate expected results (mimicking the code's behavior)
    expectedDst.at(0, 0) = static_cast<unsigned char>(50 * 1.5f + 10); // 85
    expectedDst.at(1, 0) = static_cast<unsigned char>(100 * 1.5f + 10); // 160
    expectedDst.at(0, 1) = static_cast<unsigned char>(150 * 1.5f + 10); // 235
    expectedDst.at(1, 1) = static_cast<unsigned char>(255); // Clipped to 255

    Image dst;
    bc.process(src, dst);

    assert(compareImages(dst, expectedDst));
	dst.release();

    std::cout << "Brightness and Contrast tests passed\n";
}

void testGammaCorrection() {
    Image src(2, 2);
    src.at(0, 0) = 50;
    src.at(1, 0) = 100;
    src.at(0, 1) = 150;
    src.at(1, 1) = 200;

    Image expectedDst(2, 2);
    // Calculate expected values manually (integer math, rounding as in your code)
    expectedDst.at(0, 0) = static_cast<unsigned char>(pow(50.0 / 255.0, 1.0 / 2.2) * 255.0); // ~22
    expectedDst.at(1, 0) = static_cast<unsigned char>(pow(100.0 / 255.0, 1.0 / 2.2) * 255.0); // ~47
    expectedDst.at(0, 1) = static_cast<unsigned char>(pow(150.0 / 255.0, 1.0 / 2.2) * 255.0); // ~83
    expectedDst.at(1, 1) = static_cast<unsigned char>(pow(200.0 / 255.0, 1.0 / 2.2) * 255.0); // ~128

    Image dst;
    GammaCorrection gc(2.2);
    gc.process(src, dst);

    assert(compareImages(dst, expectedDst));

	dst.release();

    std::cout << "Gamma Correction tests passed\n";
}

void testImageConvolution() {
    Image src(3, 3);
    src.at(0, 0) = 1;
    src.at(1, 0) = 1;
    src.at(2, 0) = 1;
    src.at(0, 1) = 1;
    src.at(1, 1) = 1;
    src.at(2, 1) = 1;
    src.at(0, 2) = 1;
    src.at(1, 2) = 1;
    src.at(2, 2) = 1;

    // Create a 3x3 kernel (mean blur)
    std::vector<std::vector<float>> kernel = {
        {1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f},
        {1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f},
        {1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f}
    };

    Image dst(3, 3);
    ImageConvolution conv(kernel);
    conv.process(src, dst);

    // Check the result.  For a 3x3 image of all 1s, convolving with a 3x3 mean blur
    // kernel will result in an image of all 1s.
    for (int y = 0; y < dst.height(); ++y) {
        for (int x = 0; x < dst.width(); ++x) {
            assert(dst.at(x, y) == 1);
        }
    }
    dst.release();
    std::cout << "Image Convolution tests passed\n";
}

void testDrawCircle() {
    Image img(5, 5);
    Draw d;
    d.drawCircle(img, Point(2, 2), 2, 255);

    assert(img.at(2, 0) == 255);
    assert(img.at(1, 1) == 255);
    assert(img.at(3, 1) == 255);
    assert(img.at(0, 2) == 255);
    assert(img.at(4, 2) == 255);
    assert(img.at(1, 3) == 255);
    assert(img.at(3, 3) == 255);
    assert(img.at(2, 4) == 255);

    std::cout << "Draw Circle tests passed\n";
}

void testDrawLine() {
    Image img(5, 5);
    Draw d;
    d.drawLine(img, Point(0, 0), Point(4, 4), 255);

    assert(img.at(0, 0) == 255);
    assert(img.at(1, 1) == 255);
    assert(img.at(2, 2) == 255);
    assert(img.at(3, 3) == 255);
    assert(img.at(4, 4) == 255);

    std::cout << "Draw Line tests passed\n";
}

void testDrawRectangle() {
    Image img(5, 5);
    Draw d;
    d.drawRectangle(img, Rectangle(1, 1, 3, 3), 255);

    for (int i = 1; i <= 3; ++i) {
        assert(img.at(i, 1) == 255);
        assert(img.at(i, 3) == 255);
        assert(img.at(1, i) == 255);
        assert(img.at(3, i) == 255);
    }

    std::cout << "Draw Rectangle tests passed\n";
}

void testDrawRectanglePoints() {
    Image img(5, 5);
    Draw d;
    d.drawRectangle(img, Point(1, 1), Point(3, 3), 255);

    for (int i = 1; i <= 3; ++i) {
        assert(img.at(i, 1) == 255);
        assert(img.at(i, 3) == 255);
        assert(img.at(1, i) == 255);
        assert(img.at(3, i) == 255);
    }

    std::cout << "Draw Rectangle (Points) tests passed\n";
}


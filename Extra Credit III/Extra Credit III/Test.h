#pragma once 

#include "Image.h"
#include "ImageProcessing.h"
#include "Drawing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

// Helper function declaration
bool compareImages(const Image& img1, const Image& img2);

// Test function declarations
void testImageConstructorAndBasic();
void testImageCopyConstructor();
void testImageAssignmentOperator();
void testImageLoadAndSave();
void testImageAddition();
void testImageSubtraction();
void testImageGetROI();
void testBrightnessAndContrast();
void testGammaCorrection();
void testImageConvolution();
void testDrawCircle();
void testDrawLine();
void testDrawRectangle();
void testDrawRectanglePoints();
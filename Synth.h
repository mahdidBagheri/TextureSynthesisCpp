//
// Created by mahdi on 1/27/2023.
//

#ifndef TEXTURESYNTHESIS_SYNTH_H
#define TEXTURESYNTHESIS_SYNTH_H

#endif //TEXTURESYNTHESIS_SYNTH_H

#define OPENCV_TRAITS_ENABLE_DEPRECATED
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat read_texture(string);
Mat synth_texture(Mat,int, int);

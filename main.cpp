#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "Synth.cpp"

int main()
{

    cv::Mat frame;
    std::string path = "F:\\edu\\machineVisionProjects\\TextureSynthesis\\texture1.jpg";
    frame = cv::imread(path, cv::IMREAD_COLOR); // Read the file

    Synth* synth = new Synth();

    cv::Mat texture = synth->read_texture(path);
    long hight = 2500;
    long width = 2500;
    cv::Mat siynthesis_image = synth->synth_texture(texture, width, hight);
    //imshow("synth",siynthesis_image);
    //waitKey(0);
    return 0;
}

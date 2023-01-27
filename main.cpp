#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

int main()
{

    cv::Mat frame;
    frame = cv::imread("F:\\edu\\machineVisionProjects\\TextureSynthesis\\me.jpg", cv::IMREAD_COLOR); // Read the file

    cv::namedWindow("Window", cv::WINDOW_AUTOSIZE); // Create a window for display.
    cv::imshow("Window", frame); // Show our image inside it.

    cv::waitKey(0); // Wait for a keystroke in the window
    return 0;
}

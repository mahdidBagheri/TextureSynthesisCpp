//
// Created by mahdi on 1/27/2023.
//

#define OPENCV_TRAITS_ENABLE_DEPRECATED
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>


using namespace cv;
using namespace std;

class Synth
{
public:

    Mat read_texture(string path)
    {
        Mat texture = imread(path, COLOR_RGB2BGR);
        return texture;
    }

    Mat synth_texture(Mat texture, long width, long hight)
    {
        int kernel_size = 5;
        cv::Mat convas = cv::Mat::zeros(cv::Size(width, hight), CV_8UC3);

        convas = add_base_texture(convas, texture, (long)((hight - texture.rows)/2), (long)((width - texture.cols) / 2), texture.rows, texture.cols);
        vector<Point> black_pxl_idxs;

        do
        {

            auto convas_filtered = filter_convas(convas, kernel_size=kernel_size);
            black_pxl_idxs = calc_black_pixl_idxs(convas, convas_filtered);
            Point idx = black_pxl_idxs.back();
            black_pxl_idxs.pop_back();
            convas = synth_idx(convas, idx, kernel_size=kernel_size);


        } while (black_pxl_idxs.size() > 0);


        //convas(Range(0, 0), Range(605, 806)) = texture;

        Mat resized_down;
        //resize down
        resize(convas, resized_down, Size(500, 500), INTER_LINEAR);
        imshow("1", resized_down);
        waitKey(0);

        return convas;

    }

    Mat add_base_texture(Mat convas, Mat base_texture, long pxl_i, long pxl_j, long h, long w)
    {
        for (long i = pxl_i; i < pxl_i + h; i++)
        {
            for (long j = pxl_j; j < pxl_j + w; j++)
            {
                auto p = base_texture.at<cv::Vec3b>(i - pxl_i, j - pxl_j);
                convas.at<Vec3b>(i, j).val[0] = p.val[0];
                convas.at<Vec3b>(i, j).val[1] = p.val[1];
                convas.at<Vec3b>(i, j).val[2] = p.val[2];
            }
        }
        int a = 0;
        return convas;
    }

    Mat filter_convas(Mat convas,int kernel_size=3)
    {

        Mat kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size * kernel_size);

        Mat convas_filtered;

        filter2D(convas, convas_filtered, -1, kernel);

        return convas_filtered;
    }

    vector<Point> calc_black_pixl_idxs(Mat convas, Mat convas_filtered)
    {
        vector<Point> idxs;

        for (int i = 0; i < convas.rows; i++)
        {
            for (int j = 0; j < convas.cols; j++)
            {
                auto R = convas.at<Vec3b>(i, j).val[0];
                auto G = convas.at<Vec3b>(i, j).val[1];
                auto B = convas.at<Vec3b>(i, j).val[2];
                if ( R == 0 && G == 0 && B == 0)
                {
                    auto R_f = convas_filtered.at<Vec3b>(i, j).val[0];
                    auto G_f = convas_filtered.at<Vec3b>(i, j).val[1];
                    auto B_f = convas_filtered.at<Vec3b>(i, j).val[2];
                    if (R_f != 0 || G_f != 0 || B_f != 0)
                    {
                        idxs.push_back(Point(i, j));
                    }
                }
            }
        }
        return idxs;
    }

    Mat synth_idx(Mat convas, Point idx,int kernel_size=3)
    {
        Mat convas_pad, convas_pad_norm;

        Mat rgbchannel[3];

        copyMakeBorder(convas, convas_pad, int(kernel_size/2), int(kernel_size/2), int(kernel_size/2), int(kernel_size/2), BORDER_CONSTANT, Scalar(0));


        split(convas_pad, rgbchannel);



        Rect roi(idx.y - 1, idx.x - 1, kernel_size, kernel_size);
        Mat roi_R, roi_G, roi_B;
        Mat kernel_R, kernel_G,  kernel_B;

        rgbchannel[0].convertTo(rgbchannel[0],CV_32F);
        roi_R = rgbchannel[0](roi);
        kernel_R = roi_R/ (float)(255.0*kernel_size*kernel_size);

        rgbchannel[1].convertTo(rgbchannel[1],CV_32F);
        roi_G = rgbchannel[1](roi);
        kernel_G = roi_G/ (float)(255.0*kernel_size*kernel_size);

        rgbchannel[2].convertTo(rgbchannel[2],CV_32F);
        roi_B = rgbchannel[2](roi);
        kernel_B = roi_B/ (float)(255.0*kernel_size*kernel_size);

        Mat corr, corr_R, corr_G, corr_B;

        matchTemplate(rgbchannel[0], kernel_R,corr_R,TM_CCORR_NORMED  );
        matchTemplate(rgbchannel[1], kernel_G,corr_G,TM_CCORR_NORMED  );
        matchTemplate(rgbchannel[2], kernel_B,corr_B,TM_CCORR_NORMED  );

        corr = (float)(0.33) * corr_R + (float)(0.33) * corr_G + (float)(0.33) * corr_B;

        int a = 0;

        return convas;



    }

    void show(Mat img)
    {
        Mat resized_down;
        //resize down
        resize(img, resized_down, Size(500, 500), INTER_LINEAR);
        imshow("1", resized_down);
        waitKey(0);
    }
};
#include <opencv2/opencv.hpp>
#include <iostream>
#include<cstring>
using namespace cv;
using namespace std;

//输入图像
Mat img;
//灰度值归一化
Mat bgr;
//HSV图像
Mat hsv;
//H
int hmin = 0;
int hmin_Max = 360;
int hmax = 360;
int hmax_Max = 360;
//S
int smin = 0;
int smin_Max = 255;
int smax = 255;
int smax_Max = 255;
//亮度
int vmin = 106;
int vmin_Max = 255;
int vmax = 250;
int vmax_Max = 255;
//显示原图的窗口
char windowName[] = "image";
//输出图像的显示窗口
char dstName[] = "hsv";
//输出图像
Mat dst;
//回调函数
void callBack(int, void*)
{
    //输出图像分配内存
    dst = Mat::zeros(img.size(), CV_32FC3);
    Mat mask;
    inRange(hsv, Scalar(hmin, smin / float(smin_Max), vmin / float(vmin_Max)), Scalar(hmax, smax / float(smax_Max), vmax / float(vmax_Max)), mask);
    //只保留
    for (int r = 0; r < bgr.rows; r++)
    {
        for (int c = 0; c < bgr.cols; c++)
        {
            if (mask.at<uchar>(r, c) == 255)
            {
                dst.at<Vec3f>(r, c) = bgr.at<Vec3f>(r, c);
            }
        }
    }
    //输出图像
    imshow(dstName, dst);
    //保存图像
    dst.convertTo(dst, CV_8UC3, 255.0, 0);
    imwrite("HSV_inRange.jpg", dst);
}
int main()
{
    img = imread("F:\\packages\\packages\\img\\RM.png");    // 这边修改成自己的图片路径，注意双斜杠

    if(img.empty())
    {
        cout << "can't read this image!" << endl;
        return 0;
    }

    imshow("image", img);
    imshow(windowName, img);
    //彩色图像的灰度值归一化
    img.convertTo(bgr, CV_32FC3, 1.0 / 255, 0);
    //颜色空间转换
    cvtColor(bgr, hsv, COLOR_BGR2HSV);
    //定义输出图像的显示窗口
    namedWindow(dstName, WINDOW_GUI_EXPANDED);
    //调节 H
    createTrackbar("h-min", dstName, &hmin, hmin_Max, callBack);
    createTrackbar("h-max", dstName, &hmax, hmax_Max, callBack);
    //调节 S
    createTrackbar("s-min", dstName, &smin, smin_Max, callBack);
    createTrackbar("s-max", dstName, &smax, smax_Max, callBack);
    //调节 V
    createTrackbar("v-min", dstName, &vmin, vmin_Max, callBack);
    createTrackbar("v-max", dstName, &vmax, vmax_Max, callBack);
    callBack(0, 0);
    waitKey(0);
    return 0;
}



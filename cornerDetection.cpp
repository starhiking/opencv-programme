#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc,char**argv)
{

    Mat src = imread("image/lena.jpg");
    Mat gray = Mat::zeros(src.size(),CV_8UC1);
    cvtColor(src,gray,CV_BGR2GRAY);
    imshow("gray image",gray);
    Mat dst;
    cornerHarris(gray,dst,2,3,0.01);
    threshold(dst,dst,0.00001,255,THRESH_BINARY);
    imshow("dst image",dst);
    while(waitKey()!='q');
    return 0;

}
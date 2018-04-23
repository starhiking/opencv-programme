//高斯不同
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc,char**argv)
{
    Mat srcImage = imread("image/lena.jpg");
    Mat grayImage;
    cvtColor(srcImage,grayImage,CV_BGR2GRAY);

    Mat g1,g2,dst;
    GaussianBlur(grayImage,g1,Size(3,3),0,0);
    GaussianBlur(g1,g2,Size(3,3),0,0);

    subtract(g1,g2,dst);
    normalize(dst,dst,255,0,NORM_MINMAX);
    
    imshow("destination Image",dst);

    while(waitKey()!='q');
    return 0;
}
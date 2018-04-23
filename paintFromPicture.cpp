//通过图片画出他的轮廓
#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

const char window_name_1[] = "srcImage from lena";
const char window_name_2[] = "paint result";

int main()
{
    Mat srcImage = imread("image/timg.jpeg");
    
    //resize(srcImage,srcImage,Size(500,500),0,0);
    Mat grayImage,dstImage;
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    
    cvtColor(srcImage,grayImage,CV_BGR2GRAY);
    Canny(grayImage,dstImage,50,200,3,false);
    //imshow("canny image",dstImage);
    findContours(dstImage,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));
    
    Mat finalImage = Mat::zeros(dstImage.size(),CV_8UC3);
    
    for(int i =contours.size()-1;i>0;i--)
    {
        Scalar color = Scalar(255,255,255);
        drawContours(finalImage,contours,i,color,1,8,hierarchy,0,Point());
        imshow(window_name_2,finalImage);

        waitKey(40);
    }   
    
    while(waitKey()!='q'){}
    return 0;
}
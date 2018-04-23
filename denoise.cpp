//利用开操作去除 线和噪音点
#include<iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat ocr = imread("image/ocr.jpg");
    if(!ocr.data)
    {
        cout<<"cannot open the image";
        return -1;
    }
    imshow("src Image",ocr);
    medianBlur(ocr,ocr,9);
    Mat grayImage;
    cvtColor(ocr,grayImage,CV_BGR2GRAY);

    Mat binaryImage = grayImage.clone();
    adaptiveThreshold(grayImage,binaryImage,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY_INV,15,-2);
    //imshow("binary",binaryImage);

    Mat kernel = getStructuringElement(MORPH_RECT,Size(5,5),Point(-1,-1));

    Mat dstImage;
    morphologyEx(binaryImage,dstImage,CV_MOP_OPEN,kernel);
    
    bitwise_not(dstImage,dstImage);

    imshow("effort Image",dstImage);


    while(waitKey()!='q'){}
    return 0;

}
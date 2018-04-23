//创建验证码图片
#include<iostream>
#include"opencv2/opencv.hpp"

using namespace std;
using namespace cv;

const int width = 600;
const int height = 600;

int main(int argc,char**argv)
{
    RNG rng;
    Mat ocr = Mat::zeros(Size(height,width),CV_8UC3);
    bitwise_not(ocr,ocr);
    

    putText(ocr,"ABCD",Point(30,300),CV_FONT_HERSHEY_COMPLEX,3.0,Scalar(230,123,89),8,LINE_8);

    vector<Point> points;

    for(int i = 0;i<30;i++)
    {
        Point point;
        point.x = rng.uniform(0,height);
        point.y = rng.uniform(0,width);
        circle(ocr,point,2,Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255)),FILLED,LINE_8);
    }

    for(int i = 0;i<20;i++)
    {
        line(ocr,Point(rng.uniform(0,height),rng.uniform(0,height)),Point(rng.uniform(0,height),rng.uniform(0,height)),Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255)),1,LINE_8);
    }

    imshow("ocr",ocr);
    imwrite("image/ocr.jpg",ocr);

    
    while(waitKey()!='q'){}
    return 0;
}
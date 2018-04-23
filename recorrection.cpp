//我刚写了一下,我使用第一个算法就能实现第三张图片的校正,
// 你的for循环里面有问题,找到最大的轮廓执行一次就可以,
// 尽管是CV_RETR_EXTERNAL,它找到的轮廓也不止一个

//背景最好是黑色 找接近白色的物体进行纠正
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat srcImage  = imread("image/retification/3.png");
    
    if(srcImage.cols>1000||srcImage.rows>800){    
        pyrDown(srcImage,srcImage);
        pyrDown(srcImage,srcImage);
        pyrDown(srcImage,srcImage);
    }

    Mat grayImage,binaryImage;
    cvtColor(srcImage,grayImage,CV_BGR2GRAY);
    adaptiveThreshold(grayImage,binaryImage,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,7,0);

    vector<vector<Point> > contours;
    //只匹配外框CV_RETR_EXTERNAL,找出最大的轮廓
    findContours(binaryImage,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
    float area = boundingRect(contours[0]).area();int index = 0;
    for(int i = 1;i<contours.size();i++)
    {

        if(boundingRect(contours[i]).area()>area) 
        {
            area = boundingRect(contours[i]).area();
            index = i;
        }
    }
    
    Rect maxRect = boundingRect(contours[index]);
    Mat ROI = binaryImage(maxRect);
    imshow("maxROI",ROI);

    RotatedRect rect = minAreaRect(contours[index]);
    Point2f rectPoint[4];
    rect.points(rectPoint);//获取四个顶点坐标
    double angle = rect.angle;
    angle += 90;
    
    Point2f center = rect.center;
    Mat RoiSrcImg = Mat::zeros(srcImage.size(),srcImage.type());

    drawContours(binaryImage,contours,-1,Scalar(255),CV_FILLED);
    // srcImage.copyTo(RoiSrcImg,binaryImage);
    srcImage.copyTo(RoiSrcImg);

    Mat Matrix = getRotationMatrix2D(center,angle,0.8);//得到旋转矩阵算子
    warpAffine(RoiSrcImg,RoiSrcImg,Matrix,RoiSrcImg.size(),1,0,Scalar(0,0,0));

    imshow("src Image",srcImage);
    imshow("recorrected",RoiSrcImg);

    while(waitKey()!='q'){}
    return 0;
}

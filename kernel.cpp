//测试各种矩阵算子
#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>

using namespace cv;
using namespace std;

int main(int argc,char**argv)
{
    Mat src = imread("image/drink.jpg");
    if(!src.data)
    {
        cout<<"connot open this picture";
        return -1;
    }

    Mat dst1,dst2,dst;

    Mat kernel_x = (Mat_<int>(2,2)<<1,0,0,-1);
    filter2D(src,dst1,-1,kernel_x,Point(-1,-1),0,0);

    Mat kernel_y = (Mat_<int>(2,2)<<0,1,-1,0);
    filter2D(src,dst2,-1,kernel_y,Point(-1,-1),0,0);
    

    Mat kernel = (Mat_<int>(3,3)<<1,0,-1,2,0,-2,1,0,-1);
    filter2D(src,dst,-1,kernel,Point(-1,-1),0,0);

    imshow("kernel",dst);
    
    imshow("kernelx",dst1);

    imshow("kernely",dst2);

    while(waitKey()!='q'){}
    return 0;

}
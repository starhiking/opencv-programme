#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat num[10];
    for(int i =0;i<10;i++)
    {
        ostringstream fileName;
        fileName<<"image/numberImage/"<<i<<".jpg";
        num[i] = imread(fileName.str());
        cout<<i<<' '<<num[i].rows<<' '<<num[i].cols<<endl;
    }

    getchar();
    return 0;
}
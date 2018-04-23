#include<iostream>
#include"opencv2/opencv.hpp"

using namespace std;
using namespace cv;

Mat db[10] ;
const int dbLen = 10;

int main(int argc,char**argv)
{
    //载入数据库 10张数字图片作为模板
    for(int i =0;i<10;i++)
    {
        ostringstream fileName;
        fileName <<"image/numberImage/"<<i<<".jpg";
        db[i] = imread(fileName.str());
    }

    Mat srcImage = imread("image/screenshoot.png");
    if(!srcImage.data)
    {
        cout<<"cannot read this file";
        return -1;
    }
    Mat grayImage = Mat::zeros(srcImage.size(),CV_8UC1);
    cvtColor(srcImage,grayImage,CV_BGR2GRAY);
    
    Mat dstImage = Mat::zeros(grayImage.size(),grayImage.type());
    
    adaptiveThreshold(grayImage,dstImage,255,ADAPTIVE_THRESH_MEAN_C,0,7,0);
    //threshold(grayImage,dstImage,100,255,CV_THRESH_BINARY);
    //imshow("thresholdImage",dstImage);
    // waitKey();
    //二值图求轮廓

    Mat Image = Mat::zeros(srcImage.size(),CV_8UC3);
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(dstImage,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
    drawContours(Image,contours,-1,Scalar(255,255,255));

    Mat copyImage = Image.clone();
    
    Rect rect[64]; //存放10个数字的rect

    //根据contours迭代器遍历每一个轮廓 画出所有最小矩阵
    vector<vector<Point> >::iterator It; int index;
    for( index = 0, It = contours.begin();It < contours.end();It++,index++){                        //画出可包围数字的最小矩形
        
        Point2f vertex[4];  
        rect[index] = boundingRect(*It);
        vertex[0] = rect[index].tl();                                                              //矩阵左上角的点
        vertex[1].x = (float)rect[index].tl().x, vertex[1].y = (float)rect[index].br().y;                 //矩阵左下方的点
        vertex[2] = rect[index].br();                                                              //矩阵右下角的点
        vertex[3].x = (float)rect[index].br().x, vertex[3].y = (float)rect[index].tl().y;                 //矩阵右上方的点

        for(int j = 0; j < 4; j++)
        {
            line(Image,vertex[j], vertex[ (j+1)%4 ],Scalar(0,0,255),1);
        }
        
            
    }

    imshow("line rects",Image);

    for(int t = index -1;t>=0;t--)
    {

        //调整矩阵 与数据库图片大小一致
        Mat tempRect = Mat::zeros(db[0].size(),db[0].type());
        resize(copyImage(rect[t]),tempRect,tempRect.size());
        int rows = tempRect.rows;
        int cols = tempRect.cols*tempRect.channels();
        
        //每个rect在数据库中进行匹配,找出最相近的值
        int Matchresult = 0;//最的小匹配值
        int MatchIndex = 0;//最小匹配值对应的的db序号

        for(int u=0;u<dbLen;u++)
        {
            int same = 0;
            
            for(int v =0;v<rows;v++)
            {
                uchar*data1 = tempRect.ptr<uchar>(v);
                uchar*data2 = db[u].ptr<uchar>(v);
                
                for(int w = 0;w<cols;w+=3)
                {
                    if(data1[w]==data2[w])
                        same++;
                }
            }

            if(same>Matchresult)
            {
                Matchresult = same;
                MatchIndex = u;
            }

            //如果这张图片完全一致 则不匹配其他的图片
            if(same==rows*cols/3)
            {
                break;
            }
        }
        //输出匹配的结果
        cout<<MatchIndex;
    }
    

    // 利用0-9的截图生成10张jpg图片作为模板
    // for(int t = index-1,name = 0;t>=0;t--,name++)
    // {
    //     Mat tempImg;
    //     resize(copyImage(rect[t]),tempImg,Size(30,30));
    //     ostringstream fileName;
    //     fileName <<"image/numberImage/"<<name<<".jpg";
    //     imwrite(fileName.str(),tempImg);
    // }

    while(waitKey()!='q'){}
    return 0; 
}

